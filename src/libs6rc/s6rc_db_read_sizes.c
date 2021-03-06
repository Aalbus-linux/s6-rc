/* ISC license. */

#include <sys/types.h>
#include <stdint.h>
#include <skalibs/buffer.h>
#include <skalibs/djbunix.h>
#include <skalibs/unix-transactional.h>
#include <s6-rc/s6rc-db.h>

static inline int s6rc_db_read_sizes_buffer (buffer *b, s6rc_db_t *db)
{
  uint32_t x ;
  if (!s6rc_db_read_uint32(b, &x)) return 0 ;
  db->nshort = x ;
  if (!s6rc_db_read_uint32(b, &x)) return 0 ;
  db->nlong = x ;
  if (!s6rc_db_read_uint32(b, &x)) return 0 ;
  db->stringlen = x ;
  if (!s6rc_db_read_uint32(b, &x)) return 0 ;
  db->nargvs = x ;
  if (!s6rc_db_read_uint32(b, &x)) return 0 ;
  db->ndeps = x ;
  if (!s6rc_db_read_uint32(b, &x)) return 0 ;
  db->nproducers = x ;
  return 1 ;
}

int s6rc_db_read_sizes (int fdcompiled, s6rc_db_t *db)
{
  char buf[24] ;
  buffer b ;
  int fd = open_readatb(fdcompiled, "n") ;
  if (fd < 0) return 0 ;
  buffer_init(&b, &buffer_read, fd, buf, 24) ;
  if (!s6rc_db_read_sizes_buffer(&b, db))
  {
    fd_close(fd) ;
    return 0 ;
  }
  {
    char c ;
    ssize_t r = buffer_get(&b, &c, 1) ;
    fd_close(fd) ;
    return !r ;
  }
}
