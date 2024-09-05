/* Testing Code */

#include <limits.h>
#include <math.h>

/* Routines used by floation point test code */

/* Convert from bit level representation to floating point number */
float u2f(unsigned u) {
    union {
        unsigned u;
        float f;
    } a;
    a.u = u;
    return a.f;
}

/* Convert from floating point number to bit-level representation */
unsigned f2u(float f) {
    union {
        unsigned u;
        float f;
    } a;
    a.f = f;
    return a.u;
}
//1
long test_bitMatch(long x, long y)
{
    int i;
    long result = 0;
    for (i = 0; i < 64; i++) {
        long mask = 1L << i;
        long bit = (x & mask) == (y & mask);
        result |= bit << i;
    }
    return result;
}
//2
long test_sign(long x) {
    if (x == 0)
        return 0;
    return (x < 0) ? -1L : 1L;
}
long test_isEqual(long x, long y)
{
  return (long) (x == y);
}
long test_anyOddBit(long x) {
  int i;
  for (i = 1; i < 64; i+=2)
      if (x & (1L<<i))
          return 1L;
  return 0L;
}
long test_byteSwap(long x, long n, long m)
{
    unsigned long bytemask = 0L;
    unsigned long nmask, mmask;
    switch(n) {
    case 0:
        bytemask = 0xFFUL;
        break;
    case 1:
        bytemask = 0xFF00UL;
        break;
    case 2:
        bytemask = 0xFF0000UL;
        break;
    case 3:
        bytemask = 0xFF000000UL;
        break;
    case 4:
        bytemask = 0xFF00000000UL;
        break;
    case 5:
        bytemask = 0xFF0000000000UL;
        break;
    case 6:
        bytemask = 0xFF000000000000UL;
        break;
    case 7:
        bytemask = 0xFF00000000000000UL;
        break;
    }
    nmask = x & bytemask;
    nmask >>= 8*n;
    x &= (~bytemask);
    switch(m) {
    case 0:
        bytemask = 0xFFUL;
        break;
    case 1:
        bytemask = 0xFF00UL;
        break;
    case 2:
        bytemask = 0xFF0000UL;
        break;
    case 3:
        bytemask = 0xFF000000UL;
        break;
    case 4:
        bytemask = 0xFF00000000UL;
        break;
    case 5:
        bytemask = 0xFF0000000000UL;
        break;
    case 6:
        bytemask = 0xFF000000000000UL;
        break;
    case 7:
        bytemask = 0xFF00000000000000UL;
        break;
    }
    mmask = x & bytemask;
    mmask >>= 8*m;
    x &= (~bytemask);
    nmask <<= 8*m;
    mmask <<= 8*n;
    return x | nmask | mmask;
}
//3
long test_replaceByte(long x, long n, long c)
{
    switch(n) {
    case 0:
      x = (x & 0xFFFFFFFFFFFFFF00L) | c;
      break;
    case 1:
      x = (x & 0xFFFFFFFFFFFF00FFL) | (c << 8);
      break;
    case 2:
      x = (x & 0xFFFFFFFFFF00FFFFL) | (c << 16);
      break;
    case 3:
      x = (x & 0xFFFFFFFF00FFFFFFL) | (c << 24);
      break;
    case 4:
      x = (x & 0xFFFFFF00FFFFFFFFL) | (c << 32);
      break;
    case 5:
      x = (x & 0xFFFF00FFFFFFFFFFL) | (c << 40);
      break;
    case 6:
      x = (x & 0xFF00FFFFFFFFFFFFL) | (c << 48);
      break;
    default:
      x = (x & 0x00FFFFFFFFFFFFFFL) | (c << 56);
      break;
    }
    return x;
}
long test_logicalShift(long x, long n) {
  unsigned long u = (unsigned long) x;
  unsigned long shifted = u >> n;
  return (long) shifted;
}
long test_conditional(long x, long y, long z)
{
  return x?y:z;
}
long test_remainderPower2(long x, long n)
{
    long p2n = 1L<<n;
    return x%p2n;
}
//4
long test_leftBitCount(long x) {
  long result = 0;
  long i;
  for (i = 63; i >= 0; i--) {
      long bit = (x >> i) & 0x1;
      if (!bit)
          break;
      result ++;
  }
  return result;
}
long test_trueFiveEighths(long x)
{
  return (long) (((__int128) x * 5)/8);
}
long test_bitParity(long x) {
  long result = 0;
  int i;
  for (i = 0; i < 64; i++)
    result ^= (x >> i) & 0x1L;
  return result;
}
