/*
 * File: FHZN_define_model_del_emxutil.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-May-2021 18:57:58
 */

#ifndef __FHZN_DEFINE_MODEL_DEL_EMXUTIL_H__
#define __FHZN_DEFINE_MODEL_DEL_EMXUTIL_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "FHZN_define_model_del_types.h"

/* Function Declarations */
extern void emxEnsureCapacity(emxArray__common *emxArray, int oldNumel, int
  elementSize);
extern void emxFree_FHZ3_DataBuff(emxArray_FHZ3_DataBuff **pEmxArray);
extern void emxFree_FHZ3_Int(emxArray_FHZ3_Int **pEmxArray);
extern void emxFree_FHZ4_DataBuff(emxArray_FHZ4_DataBuff **pEmxArray);
extern void emxFree_FHZ4_Int(emxArray_FHZ4_Int **pEmxArray);
extern void emxFree_MFM_Struct(emxArray_MFM_Struct **pEmxArray);
extern void emxFree_int32_T(emxArray_int32_T **pEmxArray);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxInit_FHZ3_DataBuff(emxArray_FHZ3_DataBuff **pEmxArray, int
  numDimensions);
extern void emxInit_FHZ3_Int(emxArray_FHZ3_Int **pEmxArray, int numDimensions);
extern void emxInit_FHZ4_DataBuff(emxArray_FHZ4_DataBuff **pEmxArray, int
  numDimensions);
extern void emxInit_FHZ4_Int(emxArray_FHZ4_Int **pEmxArray, int numDimensions);
extern void emxInit_MFM_Struct(emxArray_MFM_Struct **pEmxArray, int
  numDimensions);
extern void emxInit_int32_T(emxArray_int32_T **pEmxArray, int numDimensions);
extern void emxInit_int32_T1(emxArray_int32_T **pEmxArray, int numDimensions);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);
extern void emxInit_real_T1(emxArray_real_T **pEmxArray, int numDimensions);
extern void emxInit_real_T2(emxArray_real_T **pEmxArray, int numDimensions);

#endif

/*
 * File trailer for FHZN_define_model_del_emxutil.h
 *
 * [EOF]
 */
