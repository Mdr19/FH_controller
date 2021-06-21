/*
 * File: xgetrf.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-May-2021 18:57:58
 */

#ifndef __XGETRF_H__
#define __XGETRF_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "FHZN_define_model_del_types.h"

/* Function Declarations */
extern void xgetrf(int m, int n, emxArray_real_T *A, int lda, emxArray_int32_T
                   *ipiv, int *info);

#endif

/*
 * File trailer for xgetrf.h
 *
 * [EOF]
 */
