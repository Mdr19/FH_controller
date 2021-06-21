/*
 * File: conv.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-May-2021 18:57:58
 */

#ifndef __CONV_H__
#define __CONV_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "FHZN_define_model_del_types.h"

/* Function Declarations */
extern void b_conv(const emxArray_real_T *A, const emxArray_real_T *B,
                   emxArray_real_T *C);
extern void conv(const emxArray_real_T *A, const emxArray_real_T *B,
                 emxArray_real_T *C);

#endif

/*
 * File trailer for conv.h
 *
 * [EOF]
 */
