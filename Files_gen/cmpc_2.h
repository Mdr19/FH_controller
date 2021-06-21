/*
 * File: cmpc_2.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-May-2021 18:57:58
 */

#ifndef __CMPC_2_H__
#define __CMPC_2_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "FHZN_define_model_del_types.h"

/* Function Declarations */
extern void cmpc_2(const emxArray_real_T *A, const emxArray_real_T *B, const
                   emxArray_real_T *Bd, const emxArray_real_T *p, const
                   emxArray_real_T *N, double Tp, const emxArray_real_T *Q,
                   const emxArray_real_T *R, boolean_T without_ff,
                   emxArray_real_T *Omega, emxArray_real_T *Psi, emxArray_real_T
                   *Gamma, emxArray_real_T *Al);

#endif

/*
 * File trailer for cmpc_2.h
 *
 * [EOF]
 */
