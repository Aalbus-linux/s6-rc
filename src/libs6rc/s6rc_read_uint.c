/* ISC license. */

#include <errno.h>
#include <skalibs/uint.h>
#include <skalibs/bytestr.h>
#include <skalibs/djbunix.h>

int s6rc_read_uint (char const *file, unsigned int *u)
{
  char buf[UINT_FMT + 1] ;
  register int r = openreadnclose(file, buf, UINT_FMT) ;
  if (r < 0) return (errno == ENOENT) ? 0 : -1 ;
  buf[byte_chr(buf, r, '\n')] = 0 ;
  if (!uint0_scan(buf, u)) return (errno = EINVAL, -1) ;
  return 1 ;
}
