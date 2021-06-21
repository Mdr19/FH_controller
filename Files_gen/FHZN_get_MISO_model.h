/*
 * File: FHZN_get_MISO_model.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-May-2021 18:57:58
 */

#ifndef __FHZN_GET_MISO_MODEL_H__
#define __FHZN_GET_MISO_MODEL_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "FHZN_define_model_del_types.h"

/* Function Declarations */
extern void FHZN_get_MISO_model(const emxArray_real_T *ni_min, double inputs_nr,
  double n, double m, emxArray_real_T *A, emxArray_real_T *B, emxArray_real_T *C,
  emxArray_real_T *D);
extern void b_FHZN_get_MISO_model(const emxArray_real_T *ni_min, double n,
  double m, emxArray_real_T *A, emxArray_real_T *B, emxArray_real_T *C,
  emxArray_real_T *D);

#endif

/*
 * File trailer for FHZN_get_MISO_model.h
 *
 * [EOF]
 */
