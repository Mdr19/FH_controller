/*
 * File: FHZN_MFM_model_ident_LSM.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-May-2021 18:57:58
 */

#ifndef __FHZN_MFM_MODEL_IDENT_LSM_H__
#define __FHZN_MFM_MODEL_IDENT_LSM_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "FHZN_define_model_del_types.h"

/* Function Declarations */
extern void FHZN_MFM_model_ident_LSM(double inputs_nr, const emxArray_real_T *u,
  const emxArray_real_T *pv, double h, double n, double m, double N, double M,
  emxArray_real_T *ni_min);
extern void b_FHZN_MFM_model_ident_LSM(const emxArray_real_T *u, const
  emxArray_real_T *pv, double h, double n, double m, double N, double M,
  emxArray_real_T *ni_min);

#endif

/*
 * File trailer for FHZN_MFM_model_ident_LSM.h
 *
 * [EOF]
 */
