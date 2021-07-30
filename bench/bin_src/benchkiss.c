/*
 *  Copyright (c) 2003-2010, Mark Borgerding. All rights reserved.
 *  This file is part of KISS FFT - https://github.com/mborgerding/kissfft
 *
 *  SPDX-License-Identifier: BSD-3-Clause
 *  See COPYING file for more information.
 *
 * BLUE ORIGIN ADDED HEADER
 * Author(s):       Carson Schubert (carson.schubert14@gmail.com)
 * Date Created:    10.11.2019
 *
 * KissFFT benchmark. This file is modified from the original benchkiss.c.
 * Rather than compile into something that accepts arguments, this program runs
 * all our desired FFT transformations automatically when executed.
 *
 * 1, 2, and 3D complex, forward FFTs are computed in series. Each problem size
 * is run 1000 times and an average per FFT time is calculated.
 */


#include "kiss_fft.h"
#include "kiss_fftr.h"
#include "kiss_fftnd.h"
#include "kiss_fftndr.h"

#define DIM_STRT 2
// define maximums to make memory footprint roughly equivalent
#define NUMFFTS 1000
#define IS_INVERSE 0
#define MIN_REPORTING_TIME_US 10
#define MAX_RUNTIME_S 60

#define ONED_DIM_MAX 512   // 2^20 = 1,048,576 = 1,048,576 * sizeof(kiss_fft_cpx) bytes
#define TWOD_DIM_MAX 32   // 2^10 = 1024 = 1,048,576 * sizeof(kiss_fft_cpx) bytes
#define THREED_DIM_MAX 8  // 2^7 = 128 = 2,097,152 * sizeof(kiss_fft_cpx) bytes

// Determined the maximum needed space from the three buffers and then allocate the largest sized buffer.
#if (ONED_DIM_MAX < TWOD_DIM_MAX)
    #if (TWOD_DIM_MAX < THREED_DIM_MAX)
        #define MAX_SIZE_NEEDED THREED_DIM_MAX
    #else
        #define MAX_SIZE_NEEDED TWOD_DIM_MAX
    #endif
#else
    #if (ONED_DIM_MAX < THREED_DIM_MAX)
        #define MAX_SIZE_NEEDED THREED_DIM_MAX
    #else
        #define MAX_SIZE_NEEDED ONED_DIM_MAX
    #endif
#endif

kiss_fft_cpx BUF_STATIC_BLOB[MAX_SIZE_NEEDED];
kiss_fft_cpx BUF_OUT_STATIC_BLOB[MAX_SIZE_NEEDED];
kiss_fft_cpx * buf;
kiss_fft_cpx * bufout;
    // Note precision is now double so kiss_fft_cpx is now sized 16 bytes.

    // This buffer is used in the kiss_fft_alloc call.
    // The existing logic allocates the follow sized data:
    //    size_t memneeded = sizeof(struct kiss_fft_state) + sizeof(kiss_fft_cpx)*(nfft-1); /* twiddle factors*/
    // We are trying to mimic this allocation.
    //
    // Because we are allocating a fixed sized buffer of type kiss_fft_cpx, we just need to allocate the ONE_DIM_MAX array + the equvalent for the kiss_fft_state.
    // The equivalent of kiss_fft_state in size kiss_fft_cpx means 280 bytes / 16 bytes = 18 elements.
    // Basically, we just need to allocate ONED_DIM_MAX + 18 to have equvalent allocation.
    kiss_fft_cpx BUF_FFT_STATIC_BLOB[ONED_DIM_MAX + 18];

void cleardims(int *dims) {
    memset(dims, 0, 3);
}

void setdims(int *dims, int ndims, int size) {
    int i;
    for (i = 0; i < ndims; i++) {
        dims[i] = size;
    }
}

long long unsigned  mycycle()
{
        static volatile unsigned* uppert = 0x10010018;
        static volatile unsigned* lowert = 0x10010008;
        int tmp = 100000000;
        long long unsigned result = *uppert;
        result = result <<32;
        result =result + *lowert;
        return result;
}

void run1D(int startSize, int maxSize, int numffts) {
    // control vars
    kiss_fft_cpx * buf;
    kiss_fft_cpx * bufout;
    int base_nbytes = sizeof(kiss_fft_cpx);
    int size = startSize;
    char temp[32];
    int i;

    // result variables
    long long unsigned  start, end, totalMicroseconds;
    float totalRuntime, microsecondsPerFFT;
    totalRuntime = 0;
    while (size <= maxSize && totalRuntime < MAX_RUNTIME_S) {
        // calculate total nbytes
        int nbytes = base_nbytes * size;

        buf = BUF_STATIC_BLOB;
        bufout = BUF_OUT_STATIC_BLOB;
        // use regular 1d alloc here
        kiss_fft_cfg st = kiss_fft_alloc(size, IS_INVERSE, 0, 0);

        // memory allocation check
        if (buf == NULL || bufout == NULL || st == NULL) {
            // itoa_int32(nbytes, temp, 10);
            printf("Buffer_Mem_Req", nbytes);
            printf("Memory limit reached.\n\r");
            break;
        }

        // set buf to 0
        memset(buf,0,nbytes);
        // workload
        start_timer();
        start = mycycle();
        for (i=0;i<numffts;++i)
            kiss_fft( st ,buf,bufout );
        end = mycycle();
        // send results only if took > 1s
        totalMicroseconds = (end - start)/ 1e2;
        if (totalMicroseconds > MIN_REPORTING_TIME_US) {
            totalRuntime = (float)totalMicroseconds / ((float)1e6);
            microsecondsPerFFT = (float)totalMicroseconds / ((float) numffts);

            // send config
            printf("Dim %d\n", 1);
            //itoa_int32(size, temp, 10);
            printf("Size %d\n", size);
            //itoa_int32(nbytes, temp, 10);
            printf("Buffer_Mem_Req %d\n", nbytes);
            //dtoa(microsecondsPerFFT, temp, 3);
            printf("%s %f\n", "Microseconds_Per_FFT",microsecondsPerFFT);
            //dtoa(totalRuntime, temp, 3);
            printf("%s %f\n", "totalRuntime", totalRuntime);
        } 

        //free(st);
        //free(buf);
        //free(bufout);
        size *= 2;
    }
}

void runND(int ndims, int startSize, int maxSize, int numffts) {
    // control variables
    int nfft[3];
    kiss_fft_cpx * buf;
    kiss_fft_cpx * bufout;
    int base_nbytes = sizeof(kiss_fft_cpx);
    int size = startSize;
    char temp[32];
    int i;

    // result variables
    long long unsigned  start, end, totalMicroseconds;
    float totalRuntime, microsecondsPerFFT;
    totalRuntime = 0;

    while (size <= maxSize && totalRuntime < MAX_RUNTIME_S) {
        // set up dimensions array
        setdims(nfft, ndims, size);
        // calculate total nbytes
        int k;
        int nbytes = base_nbytes;
        for (k=0;k<ndims;++k)
            nbytes *= nfft[k];

        buf = BUF_STATIC_BLOB;
        bufout = BUF_OUT_STATIC_BLOB;

        // use nd alloc
        kiss_fftnd_cfg st = kiss_fftnd_alloc(nfft, ndims, IS_INVERSE, 0, 0);

        // memory allocation check
        if (buf == NULL || bufout == NULL || st == NULL) {
            // itoa_int32(nbytes, temp, 10);
            printf("Buffer_Mem_Req", nbytes);
            printf("Memory limit reached.\n\r");
            break;
        }

        // set buf to 0
        memset(buf,0,nbytes);

        start_timer();
        // workload
        start = mycycle();
        for (i=0;i<numffts;++i)
            kiss_fftnd( st ,buf,bufout );
        end = mycycle();

        // send results only if took > 1s
        totalMicroseconds = (end - start)/ 1e2;
        if (totalMicroseconds > MIN_REPORTING_TIME_US) {
            totalRuntime = totalMicroseconds / (float)1e6;
            microsecondsPerFFT = (float)totalMicroseconds / ((float) numffts);

            // send config
            printf("Dim %d\n", ndims);
            //itoa_int32(size, temp, 10);
            printf("Size %d\n", size);
            //itoa_int32(nbytes, temp, 10);
            printf("Buffer_Mem_Req %d\n", nbytes);
            //dtoa(microsecondsPerFFT, temp, 3);
            printf("%s %f\n", "Microseconds_Per_FFT",microsecondsPerFFT);
            //dtoa(totalRuntime, temp, 3);
            printf("%s %f\n", "totalRuntime", totalRuntime);
        } 

        // free memory
        //free(st);
        //free(buf);
        //free(bufout);
        cleardims(nfft);
        size *= 2;
    }
}
int main(int argc,char ** argv)
{

    // start workload
    printf("\n\r---- Results ---- \n\r");
    printf("\n\r-- 1D --\n\r");
    run1D(DIM_STRT, ONED_DIM_MAX, NUMFFTS);
        printf("\n\r-- 2D --\n\r");
    runND(2, DIM_STRT, TWOD_DIM_MAX, NUMFFTS);

    printf("\n\r-- 3D --\n\r");
    runND(3, DIM_STRT, THREED_DIM_MAX, NUMFFTS);
    return 0;
}

