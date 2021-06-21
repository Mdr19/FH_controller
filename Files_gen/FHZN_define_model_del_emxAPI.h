/*
 * File: FHZN_define_model_del_emxAPI.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-May-2021 18:57:58
 */

#ifndef __FHZN_DEFINE_MODEL_DEL_EMXAPI_H__
#define __FHZN_DEFINE_MODEL_DEL_EMXAPI_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "FHZN_define_model_del_types.h"

/* Function Declarations */
extern emxArray_FHZ3_DataBuff *emxCreateND_FHZ3_DataBuff(int numDimensions, int *
  size);
extern emxArray_FHZ3_Int *emxCreateND_FHZ3_Int(int numDimensions, int *size);
extern emxArray_FHZ4_DataBuff *emxCreateND_FHZ4_DataBuff(int numDimensions, int *
  size);
extern emxArray_FHZ4_Int *emxCreateND_FHZ4_Int(int numDimensions, int *size);
extern emxArray_MFM_Struct *emxCreateND_MFM_Struct(int numDimensions, int *size);
extern emxArray_real_T *emxCreateND_real_T(int numDimensions, int *size);
extern emxArray_FHZ3_DataBuff *emxCreateWrapperND_FHZ3_DataBuff(FHZ3_DataBuff
  *data, int numDimensions, int *size);
extern emxArray_FHZ3_Int *emxCreateWrapperND_FHZ3_Int(FHZ3_Int *data, int
  numDimensions, int *size);
extern emxArray_FHZ4_DataBuff *emxCreateWrapperND_FHZ4_DataBuff(FHZ4_DataBuff
  *data, int numDimensions, int *size);
extern emxArray_FHZ4_Int *emxCreateWrapperND_FHZ4_Int(FHZ4_Int *data, int
  numDimensions, int *size);
extern emxArray_MFM_Struct *emxCreateWrapperND_MFM_Struct(MFM_Struct *data, int
  numDimensions, int *size);
extern emxArray_real_T *emxCreateWrapperND_real_T(double *data, int
  numDimensions, int *size);
extern emxArray_FHZ3_DataBuff *emxCreateWrapper_FHZ3_DataBuff(FHZ3_DataBuff
  *data, int rows, int cols);
extern emxArray_FHZ3_Int *emxCreateWrapper_FHZ3_Int(FHZ3_Int *data, int rows,
  int cols);
extern emxArray_FHZ4_DataBuff *emxCreateWrapper_FHZ4_DataBuff(FHZ4_DataBuff
  *data, int rows, int cols);
extern emxArray_FHZ4_Int *emxCreateWrapper_FHZ4_Int(FHZ4_Int *data, int rows,
  int cols);
extern emxArray_MFM_Struct *emxCreateWrapper_MFM_Struct(MFM_Struct *data, int
  rows, int cols);
extern emxArray_real_T *emxCreateWrapper_real_T(double *data, int rows, int cols);
extern emxArray_FHZ3_DataBuff *emxCreate_FHZ3_DataBuff(int rows, int cols);
extern emxArray_FHZ3_Int *emxCreate_FHZ3_Int(int rows, int cols);
extern emxArray_FHZ4_DataBuff *emxCreate_FHZ4_DataBuff(int rows, int cols);
extern emxArray_FHZ4_Int *emxCreate_FHZ4_Int(int rows, int cols);
extern emxArray_MFM_Struct *emxCreate_MFM_Struct(int rows, int cols);
extern emxArray_real_T *emxCreate_real_T(int rows, int cols);
extern void emxDestroyArray_FHZ3_DataBuff(emxArray_FHZ3_DataBuff *emxArray);
extern void emxDestroyArray_FHZ3_Int(emxArray_FHZ3_Int *emxArray);
extern void emxDestroyArray_FHZ4_DataBuff(emxArray_FHZ4_DataBuff *emxArray);
extern void emxDestroyArray_FHZ4_Int(emxArray_FHZ4_Int *emxArray);
extern void emxDestroyArray_MFM_Struct(emxArray_MFM_Struct *emxArray);
extern void emxDestroyArray_real_T(emxArray_real_T *emxArray);
extern void emxInitArray_FHZ3_DataBuff(emxArray_FHZ3_DataBuff **pEmxArray, int
  numDimensions);
extern void emxInitArray_FHZ3_Int(emxArray_FHZ3_Int **pEmxArray, int
  numDimensions);
extern void emxInitArray_FHZ4_DataBuff(emxArray_FHZ4_DataBuff **pEmxArray, int
  numDimensions);
extern void emxInitArray_FHZ4_Int(emxArray_FHZ4_Int **pEmxArray, int
  numDimensions);
extern void emxInitArray_MFM_Struct(emxArray_MFM_Struct **pEmxArray, int
  numDimensions);
extern void emxInitArray_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#endif

/*
 * File trailer for FHZN_define_model_del_emxAPI.h
 *
 * [EOF]
 */
