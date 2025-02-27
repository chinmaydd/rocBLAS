/* ************************************************************************
 * Copyright (C) 2016-2024 Advanced Micro Devices, Inc. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell cop-
 * ies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IM-
 * PLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNE-
 * CTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * ************************************************************************ */

#pragma once

#include "check_numerics_matrix.hpp"
#include "check_numerics_vector.hpp"
#include "handle.hpp"

template <typename API_INT, bool CONJ, typename T, typename U, typename V, typename W>
inline rocblas_status rocblas_ger_arg_check(rocblas_handle handle,
                                            API_INT        m,
                                            API_INT        n,
                                            const V*       alpha,
                                            rocblas_stride stride_alpha,
                                            const U*       x,
                                            rocblas_stride offsetx,
                                            API_INT        incx,
                                            rocblas_stride stridex,
                                            const U*       y,
                                            rocblas_stride offsety,
                                            API_INT        incy,
                                            rocblas_stride stridey,
                                            const W*       A,
                                            rocblas_stride offsetA,
                                            API_INT        lda,
                                            rocblas_stride strideA,
                                            API_INT        batch_count)
{
    if(m < 0 || n < 0 || !incx || !incy || lda < m || lda < 1 || batch_count < 0)
        return rocblas_status_invalid_size;

    if(!m || !n || !batch_count)
        return rocblas_status_success;

    if(!alpha)
        return rocblas_status_invalid_pointer;

    if(handle->pointer_mode == rocblas_pointer_mode_host)
    {
        if(*alpha == 0)
            return rocblas_status_success;

        // pointers are validated if they need to be dereferenced
        if(!A || !x || !y)
            return rocblas_status_invalid_pointer;
    }

    return rocblas_status_continue;
}

template <typename T>
ROCBLAS_INTERNAL_EXPORT_NOINLINE rocblas_status
    rocblas_internal_ger_template(rocblas_handle handle,
                                  rocblas_int    m,
                                  rocblas_int    n,
                                  const T*       alpha,
                                  rocblas_stride stride_alpha,
                                  const T*       x,
                                  rocblas_stride offsetx,
                                  rocblas_int    incx,
                                  rocblas_stride stridex,
                                  const T*       y,
                                  rocblas_stride offsety,
                                  rocblas_int    incy,
                                  rocblas_stride stridey,
                                  T*             A,
                                  rocblas_stride offsetA,
                                  rocblas_int    lda,
                                  rocblas_stride strideA,
                                  rocblas_int    batch_count);

template <typename T>
ROCBLAS_INTERNAL_EXPORT_NOINLINE rocblas_status
    rocblas_internal_gerc_template(rocblas_handle handle,
                                   rocblas_int    m,
                                   rocblas_int    n,
                                   const T*       alpha,
                                   rocblas_stride stride_alpha,
                                   const T*       x,
                                   rocblas_stride offsetx,
                                   rocblas_int    incx,
                                   rocblas_stride stridex,
                                   const T*       y,
                                   rocblas_stride offsety,
                                   rocblas_int    incy,
                                   rocblas_stride stridey,
                                   T*             A,
                                   rocblas_stride offsetA,
                                   rocblas_int    lda,
                                   rocblas_stride strideA,
                                   rocblas_int    batch_count);

template <typename T>
ROCBLAS_INTERNAL_EXPORT_NOINLINE rocblas_status
    rocblas_internal_ger_batched_template(rocblas_handle  handle,
                                          rocblas_int     m,
                                          rocblas_int     n,
                                          const T*        alpha,
                                          rocblas_stride  stride_alpha,
                                          const T* const* x,
                                          rocblas_stride  offsetx,
                                          rocblas_int     incx,
                                          rocblas_stride  stridex,
                                          const T* const* y,
                                          rocblas_stride  offsety,
                                          rocblas_int     incy,
                                          rocblas_stride  stridey,
                                          T* const*       A,
                                          rocblas_stride  offsetA,
                                          rocblas_int     lda,
                                          rocblas_stride  strideA,
                                          rocblas_int     batch_count);

template <typename T>
ROCBLAS_INTERNAL_EXPORT_NOINLINE rocblas_status
    rocblas_internal_gerc_batched_template(rocblas_handle  handle,
                                           rocblas_int     m,
                                           rocblas_int     n,
                                           const T*        alpha,
                                           rocblas_stride  stride_alpha,
                                           const T* const* x,
                                           rocblas_stride  offsetx,
                                           rocblas_int     incx,
                                           rocblas_stride  stridex,
                                           const T* const* y,
                                           rocblas_stride  offsety,
                                           rocblas_int     incy,
                                           rocblas_stride  stridey,
                                           T* const*       A,
                                           rocblas_stride  offsetA,
                                           rocblas_int     lda,
                                           rocblas_stride  strideA,
                                           rocblas_int     batch_count);

template <typename T, typename U>
rocblas_status rocblas_ger_check_numerics(const char*    function_name,
                                          rocblas_handle handle,
                                          int64_t        m,
                                          int64_t        n,
                                          U              A,
                                          rocblas_stride offset_a,
                                          int64_t        lda,
                                          rocblas_stride stride_a,
                                          T              x,
                                          rocblas_stride offset_x,
                                          int64_t        inc_x,
                                          rocblas_stride stride_x,
                                          T              y,
                                          rocblas_stride offset_y,
                                          int64_t        inc_y,
                                          rocblas_stride stride_y,
                                          int64_t        batch_count,
                                          const int      check_numerics,
                                          bool           is_input);
