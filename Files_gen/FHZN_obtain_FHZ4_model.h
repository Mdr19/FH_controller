/*
 * File: FHZN_obtain_FHZ4_model.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-May-2021 18:57:58
 */

#ifndef __FHZN_OBTAIN_FHZ4_MODEL_H__
#define __FHZN_OBTAIN_FHZ4_MODEL_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "FHZN_define_model_del_types.h"

/* Function Declarations */
extern void FHZN_obtain_FHZ4_model(const emxArray_FHZ4_DataBuff *dataBuff, const
  emxArray_FHZ4_Int *FHZ_intervals, const emxArray_MFM_Struct *MFM_ident_models,
  double intervals_nr, double min_init_model_intervals, double interval_len,
  double *model_identified, double *model_identified_op_int, double *op_time,
  emxArray_real_T *ni_min_opt, double op_offset[4], double *model_diff_avg,
  double *sp_diff_avg, emxArray_real_T *model_X0, double *n, double *m, double
  *N, double *M, double *h);

#endif

/*
 * File trailer for FHZN_obtain_FHZ4_model.h
 *
 * [EOF]
 */
