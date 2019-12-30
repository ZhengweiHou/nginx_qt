
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGX_ARRAY_H_INCLUDED_
#define _NGX_ARRAY_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>

// ####### 数组Array结构定义
typedef struct {
    void        *elts;  // 指向数组第一个元素的指针
    ngx_uint_t   nelts; // 未使用元素的索引
    size_t       size;  // 每个元素的大小，数组创建后就固定死了
    ngx_uint_t   nalloc;// 一共分配了多少个元素(即当前数组的容量)，若不够用，会自动扩容
    ngx_pool_t  *pool;  // 内存池
} ngx_array_t;

// 创建数组
ngx_array_t *ngx_array_create(ngx_pool_t *p, ngx_uint_t n, size_t size);
// 销毁数组
void ngx_array_destroy(ngx_array_t *a);
// 添加一个元素
void *ngx_array_push(ngx_array_t *a);
// 添加多个元素
void *ngx_array_push_n(ngx_array_t *a, ngx_uint_t n);

// 创建数组函数调用该函数，初始化数组
static ngx_inline ngx_int_t
ngx_array_init(ngx_array_t *array, ngx_pool_t *pool, ngx_uint_t n, size_t size)
{
    /*
     * set "array->nelts" before "array->elts", otherwise MSVC thinks
     * that "array->nelts" may be used without having been initialized
     */

    array->nelts = 0;
    array->size = size;
    array->nalloc = n;
    array->pool = pool;

    // 从内存池中分配n*size大小的内存给数组，数组第一个元素指针指向这片内存
    array->elts = ngx_palloc(pool, n * size);
    if (array->elts == NULL) {
        return NGX_ERROR;
    }

    return NGX_OK;
}


#endif /* _NGX_ARRAY_H_INCLUDED_ */
