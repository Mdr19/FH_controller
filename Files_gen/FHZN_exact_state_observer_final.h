/*
 * File: FHZN_exact_state_observer_final.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-May-2021 18:57:58
 */

#ifndef __FHZN_EXACT_STATE_OBSERVER_FINAL_H__
#define __FHZN_EXACT_STATE_OBSERVER_FINAL_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "FHZN_define_model_del_types.h"

/* Function Declarations */
extern void FHZN_exact_state_observer_final(const emxArray_real_T *A, const
  emxArray_real_T *B, const emxArray_real_T *C, const emxArray_real_T *t, const
  emxArray_real_T *u, const emxArray_real_T *y, emxArray_real_T *X_T);
extern void b_FHZN_exact_state_observer_fin(const emxArray_real_T *A, const
  emxArray_real_T *B, const emxArray_real_T *C, const emxArray_real_T *t, const
  emxArray_real_T *u, const emxArray_real_T *y, emxArray_real_T *X_T);

#endif

/*
 * File trailer for FHZN_exact_state_observer_final.h
 *
 * [EOF]
 */
