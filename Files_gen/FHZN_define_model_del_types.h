/*
 * File: FHZN_define_model_del_types.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-May-2021 18:57:58
 */

#ifndef __FHZN_DEFINE_MODEL_DEL_TYPES_H__
#define __FHZN_DEFINE_MODEL_DEL_TYPES_H__

/* Include Files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  double *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real_T*/

#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T

typedef struct emxArray_real_T emxArray_real_T;

#endif                                 /*typedef_emxArray_real_T*/

#ifndef typedef_FHZ3_DataBuff
#define typedef_FHZ3_DataBuff

typedef struct {
  emxArray_real_T *input_1;
  emxArray_real_T *input_2;
  emxArray_real_T *input_3;
  emxArray_real_T *output;
  emxArray_real_T *sp_value;
  emxArray_real_T *time;
} FHZ3_DataBuff;

#endif                                 /*typedef_FHZ3_DataBuff*/

#ifndef typedef_FHZ3_Int
#define typedef_FHZ3_Int

typedef struct {
  double op_interval_time;
  boolean_T op_interval;
  double model_diff;
  double model_nr;
  emxArray_real_T *X0;
  boolean_T op_interval_possible;
  double model_del;
  double model_inputs[3];
  double sp_diff;
} FHZ3_Int;

#endif                                 /*typedef_FHZ3_Int*/

#ifndef typedef_FHZ4_DataBuff
#define typedef_FHZ4_DataBuff

typedef struct {
  emxArray_real_T *input_1;
  emxArray_real_T *input_2;
  emxArray_real_T *output;
  emxArray_real_T *sp_value;
  emxArray_real_T *time;
} FHZ4_DataBuff;

#endif                                 /*typedef_FHZ4_DataBuff*/

#ifndef typedef_FHZ4_Int
#define typedef_FHZ4_Int

typedef struct {
  double op_interval_time;
  boolean_T op_interval_possible;
  boolean_T op_interval;
  double model_inputs[2];
  double model_del;
  double model_diff;
  double sp_diff;
  double model_nr;
  emxArray_real_T *X0;
} FHZ4_Int;

#endif                                 /*typedef_FHZ4_Int*/

#ifndef typedef_MFM_Struct
#define typedef_MFM_Struct

typedef struct {
  double n;
  double m;
  double N;
  double M;
  double h;
} MFM_Struct;

#endif                                 /*typedef_MFM_Struct*/

#ifndef struct_emxArray_FHZ3_DataBuff
#define struct_emxArray_FHZ3_DataBuff

struct emxArray_FHZ3_DataBuff
{
  FHZ3_DataBuff *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_FHZ3_DataBuff*/

#ifndef typedef_emxArray_FHZ3_DataBuff
#define typedef_emxArray_FHZ3_DataBuff

typedef struct emxArray_FHZ3_DataBuff emxArray_FHZ3_DataBuff;

#endif                                 /*typedef_emxArray_FHZ3_DataBuff*/

#ifndef struct_emxArray_FHZ3_Int
#define struct_emxArray_FHZ3_Int

struct emxArray_FHZ3_Int
{
  FHZ3_Int *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_FHZ3_Int*/

#ifndef typedef_emxArray_FHZ3_Int
#define typedef_emxArray_FHZ3_Int

typedef struct emxArray_FHZ3_Int emxArray_FHZ3_Int;

#endif                                 /*typedef_emxArray_FHZ3_Int*/

#ifndef struct_emxArray_FHZ4_DataBuff
#define struct_emxArray_FHZ4_DataBuff

struct emxArray_FHZ4_DataBuff
{
  FHZ4_DataBuff *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_FHZ4_DataBuff*/

#ifndef typedef_emxArray_FHZ4_DataBuff
#define typedef_emxArray_FHZ4_DataBuff

typedef struct emxArray_FHZ4_DataBuff emxArray_FHZ4_DataBuff;

#endif                                 /*typedef_emxArray_FHZ4_DataBuff*/

#ifndef struct_emxArray_FHZ4_Int
#define struct_emxArray_FHZ4_Int

struct emxArray_FHZ4_Int
{
  FHZ4_Int *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_FHZ4_Int*/

#ifndef typedef_emxArray_FHZ4_Int
#define typedef_emxArray_FHZ4_Int

typedef struct emxArray_FHZ4_Int emxArray_FHZ4_Int;

#endif                                 /*typedef_emxArray_FHZ4_Int*/

#ifndef struct_emxArray_MFM_Struct
#define struct_emxArray_MFM_Struct

struct emxArray_MFM_Struct
{
  MFM_Struct *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_MFM_Struct*/

#ifndef typedef_emxArray_MFM_Struct
#define typedef_emxArray_MFM_Struct

typedef struct emxArray_MFM_Struct emxArray_MFM_Struct;

#endif                                 /*typedef_emxArray_MFM_Struct*/

#ifndef struct_emxArray__common
#define struct_emxArray__common

struct emxArray__common
{
  void *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray__common*/

#ifndef typedef_emxArray__common
#define typedef_emxArray__common

typedef struct emxArray__common emxArray__common;

#endif                                 /*typedef_emxArray__common*/

#ifndef struct_emxArray_int32_T
#define struct_emxArray_int32_T

struct emxArray_int32_T
{
  int *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_int32_T*/

#ifndef typedef_emxArray_int32_T
#define typedef_emxArray_int32_T

typedef struct emxArray_int32_T emxArray_int32_T;

#endif                                 /*typedef_emxArray_int32_T*/
#endif

/*
 * File trailer for FHZN_define_model_del_types.h
 *
 * [EOF]
 */
