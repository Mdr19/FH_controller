/*
 * File: FHZN_obtain_MPC_model_FF.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-May-2021 18:57:58
 */

#ifndef __FHZN_OBTAIN_MPC_MODEL_FF_H__
#define __FHZN_OBTAIN_MPC_MODEL_FF_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "FHZN_define_model_del_types.h"

/* Function Declarations */
extern void FHZN_obtain_MPC_model_FF(const double inputs[3], emxArray_real_T
  *params_vector, double n, double m, double N_, double p_, double Tp, double h,
  emxArray_real_T *Omega, emxArray_real_T *Psi, emxArray_real_T *Gamma,
  emxArray_real_T *A, emxArray_real_T *B, emxArray_real_T *Bd, emxArray_real_T
  *C, emxArray_real_T *Q, emxArray_real_T *R, emxArray_real_T *Ap,
  emxArray_real_T *Lzerot, emxArray_real_T *M);

#endif

/*
 * File trailer for FHZN_obtain_MPC_model_FF.h
 *
 * [EOF]
 */
