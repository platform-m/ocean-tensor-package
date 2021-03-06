/* ------------------------------------------------------------------------ */
/* Copyright 2018, IBM Corp.                                                */
/*                                                                          */
/* Licensed under the Apache License, Version 2.0 (the "License");          */
/* you may not use this file except in compliance with the License.         */
/* You may obtain a copy of the License at                                  */
/*                                                                          */
/*    http://www.apache.org/licenses/LICENSE-2.0                            */
/*                                                                          */
/* Unless required by applicable law or agreed to in writing, software      */
/* distributed under the License is distributed on an "AS IS" BASIS,        */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. */
/* See the License for the specific language governing permissions and      */
/* limitations under the License.                                           */
/* ------------------------------------------------------------------------ */

#ifndef __OCEAN_EXTERNAL_BLAS_H__
#define __OCEAN_EXTERNAL_BLAS_H__

#ifdef __cplusplus
#define OC_API extern "C"
#else
#define OC_API extern
#endif

typedef enum { OcBlasRowMajor, OcBlasColMajor } OcBlas_Order;
typedef enum { OcBlasNoTrans, OcBlasTrans, OcBlasConjTrans } OcBlas_Transpose;


OC_API void ocblas_sgemm(OcBlas_Order order, OcBlas_Transpose transA,
                         OcBlas_Transpose transB, int m, int n, int k,
                         float alpha, const float *ptrA, int lda, const float *ptrB, int ldb,
                         float beta, float *ptrC, int ldc);

OC_API void ocblas_dgemm(OcBlas_Order order, OcBlas_Transpose transA,
                         OcBlas_Transpose transB, int m, int n, int k,
                         double alpha, const double *ptrA, int lda, const double *ptrB, int ldb,
                         double beta, double *ptrC, int ldc);

OC_API void ocblas_cgemm(OcBlas_Order order, OcBlas_Transpose transA,
                         OcBlas_Transpose transB, int m, int n, int k,
                         const void *alpha, const void *ptrA, int lda, const void *ptrB, int ldb,
                         const void *beta, void *ptrC, int ldc);

OC_API void ocblas_zgemm(OcBlas_Order order, OcBlas_Transpose transA,
                         OcBlas_Transpose transB, int m, int n, int k,
                         const void *alpha, const void *ptrA, int lda, const void *ptrB, int ldb,
                         const void *beta, void *ptrC, int ldc);

#endif
