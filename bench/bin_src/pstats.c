/*
 *  Copyright (c) 2003-2010, Mark Borgerding. All rights reserved.
 *  This file is part of KISS FFT - https://github.com/mborgerding/kissfft
 *
 *  SPDX-License-Identifier: BSD-3-Clause
 *  See COPYING file for more information.
 */
//#include <stdio.h>
//#include <stdlib.h>
//#include <sys/times.h>
//#include <sys/types.h>
#include <unistd.h>

#include "pstats.h"
#include <stdint.h>
//#include <time.h>

static uint64_t ms_at_init;

uint64_t get_ms(void)
{
        static volatile unsigned* uppert = 0x10010018;
        static volatile unsigned* lowert = 0x10010008;
        int tmp = 100000;
        long long unsigned result = *uppert;
        result = result <<32;
        result =result + *lowert;
        return ((uint64_t)((double)result/(double)tmp));
}

void pstats_init(void)
{
   
}

static void tms_report(int numffts)
{

}

static void ps_report(void)
{

}

void pstats_report(int numffts)
{

}

