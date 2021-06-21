/*
 * File: FHZN_exact_state_observer_initial.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-May-2021 18:57:58
 */

#ifndef __FHZN_EXACT_STATE_OBSERVER_INITIAL_H__
#define __FHZN_EXACT_STATE_OBSERVER_INITIAL_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "FHZN_define_model_del_types.h"

/* Function Declarations */
extern void c_FHZN_exact_state_observer_ini(const emxArray_real_T *A, const
  emxArray_real_T *B, const emxArray_real_T *C, emxArray_real_T *t, const
  emxArray_real_T *u, const emxArray_real_T *y, emxArray_real_T *X_0);
extern void d_FHZN_exact_state_observer_ini(const emxArray_real_T *A, const
  emxArray_real_T *B, const emxArray_real_T *C, emxArray_real_T *t, const
  emxArray_real_T *u, const emxArray_real_T *y, emxArray_real_T *X_0);

#endif

/*
 * File trailer for FHZN_exact_state_observer_initial.h
 *
 * [EOF]
 */
