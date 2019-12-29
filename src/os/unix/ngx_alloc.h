
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGX_ALLOC_H_INCLUDED_
#define _NGX_ALLOC_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>

// 分配内存
void *ngx_alloc(size_t size, ngx_log_t *log);
// 分配内存并全重置为0
void *ngx_calloc(size_t size, ngx_log_t *log);

#define ngx_free          free
/*
 * free是释放，意思是告诉系统，给我的这块RAM我用完了，不再用了，系统可以把它干别的了
 * free之后，系统还没有拿这块RAM干别的事之前，这块RAM的内容可能是不会变的，
 * 依然可以读出原来的内容，因为你的指针a还是指向这块RAM。但要注意，这块RAM
 * 已经不属于你了，读一下内容无所谓，如果往里面写就很危险了
*/

/*
 * Linux has memalign() or posix_memalign()
 * Solaris has memalign()
 * FreeBSD 7.0 has posix_memalign(), besides, early version's malloc()
 * aligns allocations bigger than page size at the page boundary
 */

#if (NGX_HAVE_POSIX_MEMALIGN || NGX_HAVE_MEMALIGN)

void *ngx_memalign(size_t alignment, size_t size, ngx_log_t *log);

#else

#define ngx_memalign(alignment, size, log)  ngx_alloc(size, log)

#endif


extern ngx_uint_t  ngx_pagesize;
extern ngx_uint_t  ngx_pagesize_shift;
extern ngx_uint_t  ngx_cacheline_size;


#endif /* _NGX_ALLOC_H_INCLUDED_ */
