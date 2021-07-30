#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <limits.h>
#include <sys/signal.h>

#define static_assert(cond) switch(0) { case 0: case !!(long)(cond): ; }


extern char *malloc();
char heap_memory[0x2000];
int heap_memory_used = 0;
int malloc_count = 0;


#define MALLOC_INFO 0x88000004

char *malloc(int size)
{
  printf("mal0");
	char *p = heap_memory + heap_memory_used;
  printf("mal1");
  //*((int *)(MALLOC_INFO)+0+malloc_count) = heap_memory_used;
	//printf("[malloc(%d) -=> 0x%x (%d..%d)]", size, (int)p, heap_memory_used, heap_memory_used + size);
	heap_memory_used += size;

  //*((int *)(MALLOC_INFO)+1+malloc_count) = heap_memory_used;

  //*((int *)(MALLOC_INFO)+2+malloc_count) = malloc_count;
  malloc_count++;

		//asm volatile ("ebreak");
	return p;
}

char *myMalloc(int size)
{
	char *p = heap_memory + heap_memory_used;
  //*((int *)(MALLOC_INFO)+0+malloc_count) = heap_memory_used;
	//printf("[malloc(%d) -=> 0x%x (%d..%d)]", size, (int)p, heap_memory_used, heap_memory_used + size);
	heap_memory_used += size;

  //*((int *)(MALLOC_INFO)+1+malloc_count) = heap_memory_used;

  //*((int *)(MALLOC_INFO)+2+malloc_count) = malloc_count;
  malloc_count++;

		//asm volatile ("ebreak");
	return p;
}

void myFree(void *ptr)
{
  return;
}

int __attribute__((weak)) main(int argc, char** argv)
{
  //write to uart addr
  int i;
  printf("Main Is missing!!\n");

  return -1;
}

long time()
{
	int cycles;
	asm volatile ("rdcycle %0" : "=r"(cycles));
	// printf("[time() -> %d]", cycles);
	return cycles;
}

long long unsigned  clock()
{
  //long unsigned result = *(int *)(0x10010008);
  //result = (((long unsigned)*(int *)(0x10010018))<<32)|result;
  long long unsigned result = *(unsigned *)(0x10010018);
  result = result <<32;
  result =result + *(unsigned *)(0x10010008);
  return result;
}

long insn()
{
	int insns;
	asm volatile ("rdinstret %0" : "=r"(insns));
	// printf("[insn() -> %d]", insns);
	return insns;
}

void _init(){

    heap_memory_used = 0;
    malloc_count = 0;
    printf("start");
    start_timer();
    int ret = main(0, 0);
    //printf("%lld\n\r",clock());
    //printf("0: %d\n\r",*(unsigned *)(0x10010008));
    printf("done");
     *(int *)(0x20000000) = 1;
    //write to host addr 

}

void start_timer ()
{
  *(int *)(0x10010004) = 0x00;
  *(int *)(0x10010000) = 0x00;
  *(int *)(0x10010000) = 0x20;
  *(int *)(0x10010014) = 0x00;
  *(int *)(0x10010010) = 0x20;
  *(int *)(0x10010010) = 0x00;
  *(int *)(0x10010000) = 0x800;
  *(int *)(0x10010000) = 0x820;
  *(int *)(0x10010000) = 0x880;
}

long long unsigned stop_timer ()
{
  *(int *)(0x10010000) = 0x00;
  long long unsigned result = *(unsigned *)(0x10010018);
  result = result <<32;
  result =result + *(unsigned *)(0x10010008);
  return result;
}

#undef putchar
int putchar(int ch)
{
  int test = *(int *)(0x10000008);
  while((test&0x8) == 0x8)
  {
   test = *(int *)(0x10000008);
  }
  //for(int i =0; i<0xFFFF;i++);


  *(int *)(0x10000004) = ch;
  return 0;
}


static inline void printnum(void (*putch)(int, void**), void **putdat,
                    unsigned long long num, unsigned base, int width, int padc)
{
  unsigned digs[sizeof(num)*CHAR_BIT];
  int pos = 0;

  while (1)
  {
    digs[pos++] = num % base;
    if (num < base)
      break;
    num /= base;
  }

  while (width-- > pos)
    putch(padc, putdat);

  while (pos-- > 0)
    putch(digs[pos] + (digs[pos] >= 10 ? 'a' - 10 : '0'), putdat);
}

static unsigned long long getuint(va_list *ap, int lflag)
{
  if (lflag >= 2)
    return va_arg(*ap, unsigned long long);
  else if (lflag)
    return va_arg(*ap, unsigned long);
  else
    return va_arg(*ap, unsigned int);
}

static long long getint(va_list *ap, int lflag)
{
  if (lflag >= 2)
    return va_arg(*ap, long long);
  else if (lflag)
    return va_arg(*ap, long);
  else
    return va_arg(*ap, int);
}

static void vprintfmt(void (*putch)(int, void**), void **putdat, const char *fmt, va_list ap)
{
  register const char* p;
  const char* last_fmt;
  register int ch, err;
  unsigned long long num;
  int base, lflag, width, precision, altflag;
  float tmp;
  char padc;
    
  while (1) {
    while ((ch = *(unsigned char *) fmt) != '%') {
      if (ch == '\0')
        return;
      fmt++;
      putch(ch, putdat);
    }
    fmt++;

     
    // Process a %-escape sequence
    last_fmt = fmt;
    padc = ' ';
    width = -1;
    precision = -1;
    lflag = 0;
    altflag = 0;
  reswitch:
    switch (ch = *(unsigned char *) fmt++) {

    // flag to pad on the right
    case '-':
      padc = '-';
      goto reswitch;
      
    // flag to pad with 0's instead of spaces
    case '0':
      padc = '0';
      goto reswitch;

    // width field
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      for (precision = 0; ; ++fmt) {
        precision = precision * 10 + ch - '0';
        ch = *fmt;
        if (ch < '0' || ch > '9')
          break;
      }
      goto process_precision;

    case '*':
      precision = va_arg(ap, int);
      goto process_precision;

    case '.':
      if (width < 0)
        width = 0;
      goto reswitch;

    case '#':
      altflag = 1;
      goto reswitch;

    process_precision:
      if (width < 0)
        width = precision, precision = -1;
      goto reswitch;

    // long flag (doubled for long long)
    case 'l':
      lflag++;
      goto reswitch;

    // character
    case 'c':
      putch(va_arg(ap, int), putdat);
      break;

    // string
    case 's':
      if ((p = va_arg(ap, char *)) == NULL)
        p = "(null)";
      if (width > 0 && padc != '-')
        for (width -= strnlen(p, precision); width > 0; width--)
          putch(padc, putdat);
      for (; (ch = *p) != '\0' && (precision < 0 || --precision >= 0); width--) {
        putch(ch, putdat);
        p++;
      }
      for (; width > 0; width--)
        putch(' ', putdat);
      break;

    // (signed) decimal
    case 'd':
      num = getint(&ap, lflag);
      if ((long long) num < 0) {
        putch('-', putdat);
        num = -(long long) num;
      }
      base = 10;
      goto signed_number;

    // unsigned decimal
    case 'u':
      base = 10;
      goto unsigned_number;

    // (unsigned) octal
    case 'o':
      // should do something with padding so it's always 3 octits
      base = 8;
      goto unsigned_number;

    // pointer
    case 'p':
      static_assert(sizeof(long) == sizeof(void*));
      lflag = 1;
      putch('0', putdat);
      putch('x', putdat);
      /* fall through to 'x' */

    // (unsigned) hexadecimal
    case 'f':
      tmp = va_arg(ap, double);
      num = tmp;
      base = 10;
      printnum(putch, putdat, num, base, width, padc);
      putch('.', putdat);
      num = (int)(tmp*10000)%10000;
      printnum(putch, putdat, num, base, width, padc);
      break;


    case 'x':
      base = 16;
    unsigned_number:
      num = getuint(&ap, lflag);
    signed_number:
      printnum(putch, putdat, num, base, width, padc);
      break;

    // escaped '%' character
    case '%':
      putch(ch, putdat);
      break;
      
    // unrecognized escape sequence - just print it literally
    default:
      putch('%', putdat);
      fmt = last_fmt;
      break;
    }
  }
}

int printf(const char* fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);

  vprintfmt((void*)putchar, 0, fmt, ap);
  va_end(ap);
  return 0; // incorrect return value, but who cares, anyway?
}

int sprintf(char* str, const char* fmt, ...)
{
  va_list ap;
  char* str0 = str;
  va_start(ap, fmt);

  void sprintf_putch(int ch, void** data)
  {
    char** pstr = (char**)data;
    **pstr = ch;
    (*pstr)++;
  }

  vprintfmt(sprintf_putch, (void**)&str, fmt, ap);
  *str = 0;

  va_end(ap);
  return str - str0;
}
size_t strlen(const char *s)
{
  const char *p = s;
  while (*p)
    p++;
  return p - s;
}

size_t strnlen(const char *s, size_t n)
{
  const char *p = s;
  while (n-- && *p)
    p++;
  return p - s;
}

int strcmp(const char* s1, const char* s2)
{
  unsigned char c1, c2;

  do {
    c1 = *s1++;
    c2 = *s2++;
  } while (c1 != 0 && c1 == c2);

  return c1 - c2;
}

char* strcpy(char* dest, const char* src)
{
  char* d = dest;
  while ((*d++ = *src++))
    ;
  return dest;
}

long atol(const char* str)
{
  long res = 0;
  int sign = 0;

  while (*str == ' ')
    str++;

  if (*str == '-' || *str == '+') {
    sign = *str == '-';
    str++;
  }

  while (*str) {
    res *= 10;
    res += *str++ - '0';
  }

  return sign ? -res : res;
}

int puts(const char * str){
    printf(str);
    putchar(0xa);
    return 0;
}