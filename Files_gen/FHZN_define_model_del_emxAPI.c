/*
 * File: FHZN_define_model_del_emxAPI.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-May-2021 18:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "FHZN_define_model_del.h"
#include "FHZN_define_model_inputs.h"
#include "FHZN_find_operating_point.h"
#include "FHZN_obtain_FHZ3_model.h"
#include "FHZN_obtain_FHZ3_model_nonzero.h"
#include "FHZN_obtain_FHZ4_model.h"
#include "FHZN_obtain_FHZ4_model_nonzero.h"
#include "FHZN_obtain_MPC_model_FF.h"
#include "FHZN_simulate_FHZ3_system.h"
#include "FHZN_simulate_FHZ4_system.h"
#include "FHZN_define_model_del_emxAPI.h"
#include "FHZN_define_model_del_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : int numDimensions
 *                int *size
 * Return Type  : emxArray_FHZ3_DataBuff *
 */
emxArray_FHZ3_DataBuff *emxCreateND_FHZ3_DataBuff(int numDimensions, int *size)
{
  emxArray_FHZ3_DataBuff *emx;
  int numEl;
  int i;
  emxInit_FHZ3_DataBuff(&emx, numDimensions);
  numEl = 1;
  for (i = 0; i < numDimensions; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }

  emx->data = (FHZ3_DataBuff *)calloc((unsigned int)numEl, sizeof(FHZ3_DataBuff));
  emx->numDimensions = numDimensions;
  emx->allocatedSize = numEl;
  return emx;
}

/*
 * Arguments    : int numDimensions
 *                int *size
 * Return Type  : emxArray_FHZ3_Int *
 */
emxArray_FHZ3_Int *emxCreateND_FHZ3_Int(int numDimensions, int *size)
{
  emxArray_FHZ3_Int *emx;
  int numEl;
  int i;
  emxInit_FHZ3_Int(&emx, numDimensions);
  numEl = 1;
  for (i = 0; i < numDimensions; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }

  emx->data = (FHZ3_Int *)calloc((unsigned int)numEl, sizeof(FHZ3_Int));
  emx->numDimensions = numDimensions;
  emx->allocatedSize = numEl;
  return emx;
}

/*
 * Arguments    : int numDimensions
 *                int *size
 * Return Type  : emxArray_FHZ4_DataBuff *
 */
emxArray_FHZ4_DataBuff *emxCreateND_FHZ4_DataBuff(int numDimensions, int *size)
{
  emxArray_FHZ4_DataBuff *emx;
  int numEl;
  int i;
  emxInit_FHZ4_DataBuff(&emx, numDimensions);
  numEl = 1;
  for (i = 0; i < numDimensions; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }

  emx->data = (FHZ4_DataBuff *)calloc((unsigned int)numEl, sizeof(FHZ4_DataBuff));
  emx->numDimensions = numDimensions;
  emx->allocatedSize = numEl;
  return emx;
}

/*
 * Arguments    : int numDimensions
 *                int *size
 * Return Type  : emxArray_FHZ4_Int *
 */
emxArray_FHZ4_Int *emxCreateND_FHZ4_Int(int numDimensions, int *size)
{
  emxArray_FHZ4_Int *emx;
  int numEl;
  int i;
  emxInit_FHZ4_Int(&emx, numDimensions);
  numEl = 1;
  for (i = 0; i < numDimensions; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }

  emx->data = (FHZ4_Int *)calloc((unsigned int)numEl, sizeof(FHZ4_Int));
  emx->numDimensions = numDimensions;
  emx->allocatedSize = numEl;
  return emx;
}

/*
 * Arguments    : int numDimensions
 *                int *size
 * Return Type  : emxArray_MFM_Struct *
 */
emxArray_MFM_Struct *emxCreateND_MFM_Struct(int numDimensions, int *size)
{
  emxArray_MFM_Struct *emx;
  int numEl;
  int i;
  emxInit_MFM_Struct(&emx, numDimensions);
  numEl = 1;
  for (i = 0; i < numDimensions; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }

  emx->data = (MFM_Struct *)calloc((unsigned int)numEl, sizeof(MFM_Struct));
  emx->numDimensions = numDimensions;
  emx->allocatedSize = numEl;
  return emx;
}

/*
 * Arguments    : int numDimensions
 *                int *size
 * Return Type  : emxArray_real_T *
 */
emxArray_real_T *emxCreateND_real_T(int numDimensions, int *size)
{
  emxArray_real_T *emx;
  int numEl;
  int i;
  emxInit_real_T1(&emx, numDimensions);
  numEl = 1;
  for (i = 0; i < numDimensions; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }

  emx->data = (double *)calloc((unsigned int)numEl, sizeof(double));
  emx->numDimensions = numDimensions;
  emx->allocatedSize = numEl;
  return emx;
}

/*
 * Arguments    : FHZ3_DataBuff *data
 *                int numDimensions
 *                int *size
 * Return Type  : emxArray_FHZ3_DataBuff *
 */
emxArray_FHZ3_DataBuff *emxCreateWrapperND_FHZ3_DataBuff(FHZ3_DataBuff *data,
  int numDimensions, int *size)
{
  emxArray_FHZ3_DataBuff *emx;
  int numEl;
  int i;
  emxInit_FHZ3_DataBuff(&emx, numDimensions);
  numEl = 1;
  for (i = 0; i < numDimensions; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }

  emx->data = data;
  emx->numDimensions = numDimensions;
  emx->allocatedSize = numEl;
  emx->canFreeData = false;
  return emx;
}

/*
 * Arguments    : FHZ3_Int *data
 *                int numDimensions
 *                int *size
 * Return Type  : emxArray_FHZ3_Int *
 */
emxArray_FHZ3_Int *emxCreateWrapperND_FHZ3_Int(FHZ3_Int *data, int numDimensions,
  int *size)
{
  emxArray_FHZ3_Int *emx;
  int numEl;
  int i;
  emxInit_FHZ3_Int(&emx, numDimensions);
  numEl = 1;
  for (i = 0; i < numDimensions; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }

  emx->data = data;
  emx->numDimensions = numDimensions;
  emx->allocatedSize = numEl;
  emx->canFreeData = false;
  return emx;
}

/*
 * Arguments    : FHZ4_DataBuff *data
 *                int numDimensions
 *                int *size
 * Return Type  : emxArray_FHZ4_DataBuff *
 */
emxArray_FHZ4_DataBuff *emxCreateWrapperND_FHZ4_DataBuff(FHZ4_DataBuff *data,
  int numDimensions, int *size)
{
  emxArray_FHZ4_DataBuff *emx;
  int numEl;
  int i;
  emxInit_FHZ4_DataBuff(&emx, numDimensions);
  numEl = 1;
  for (i = 0; i < numDimensions; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }

  emx->data = data;
  emx->numDimensions = numDimensions;
  emx->allocatedSize = numEl;
  emx->canFreeData = false;
  return emx;
}

/*
 * Arguments    : FHZ4_Int *data
 *                int numDimensions
 *                int *size
 * Return Type  : emxArray_FHZ4_Int *
 */
emxArray_FHZ4_Int *emxCreateWrapperND_FHZ4_Int(FHZ4_Int *data, int numDimensions,
  int *size)
{
  emxArray_FHZ4_Int *emx;
  int numEl;
  int i;
  emxInit_FHZ4_Int(&emx, numDimensions);
  numEl = 1;
  for (i = 0; i < numDimensions; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }

  emx->data = data;
  emx->numDimensions = numDimensions;
  emx->allocatedSize = numEl;
  emx->canFreeData = false;
  return emx;
}

/*
 * Arguments    : MFM_Struct *data
 *                int numDimensions
 *                int *size
 * Return Type  : emxArray_MFM_Struct *
 */
emxArray_MFM_Struct *emxCreateWrapperND_MFM_Struct(MFM_Struct *data, int
  numDimensions, int *size)
{
  emxArray_MFM_Struct *emx;
  int numEl;
  int i;
  emxInit_MFM_Struct(&emx, numDimensions);
  numEl = 1;
  for (i = 0; i < numDimensions; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }

  emx->data = data;
  emx->numDimensions = numDimensions;
  emx->allocatedSize = numEl;
  emx->canFreeData = false;
  return emx;
}

/*
 * Arguments    : double *data
 *                int numDimensions
 *                int *size
 * Return Type  : emxArray_real_T *
 */
emxArray_real_T *emxCreateWrapperND_real_T(double *data, int numDimensions, int *
  size)
{
  emxArray_real_T *emx;
  int numEl;
  int i;
  emxInit_real_T1(&emx, numDimensions);
  numEl = 1;
  for (i = 0; i < numDimensions; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }

  emx->data = data;
  emx->numDimensions = numDimensions;
  emx->allocatedSize = numEl;
  emx->canFreeData = false;
  return emx;
}

/*
 * Arguments    : FHZ3_DataBuff *data
 *                int rows
 *                int cols
 * Return Type  : emxArray_FHZ3_DataBuff *
 */
emxArray_FHZ3_DataBuff *emxCreateWrapper_FHZ3_DataBuff(FHZ3_DataBuff *data, int
  rows, int cols)
{
  emxArray_FHZ3_DataBuff *emx;
  int size[2];
  int numEl;
  int i;
  size[0] = rows;
  size[1] = cols;
  emxInit_FHZ3_DataBuff(&emx, 2);
  numEl = 1;
  for (i = 0; i < 2; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }

  emx->data = data;
  emx->numDimensions = 2;
  emx->allocatedSize = numEl;
  emx->canFreeData = false;
  return emx;
}

/*
 * Arguments    : FHZ3_Int *data
 *                int rows
 *                int cols
 * Return Type  : emxArray_FHZ3_Int *
 */
emxArray_FHZ3_Int *emxCreateWrapper_FHZ3_Int(FHZ3_Int *data, int rows, int cols)
{
  emxArray_FHZ3_Int *emx;
  int size[2];
  int numEl;
  int i;
  size[0] = rows;
  size[1] = cols;
  emxInit_FHZ3_Int(&emx, 2);
  numEl = 1;
  for (i = 0; i < 2; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }

  emx->data = data;
  emx->numDimensions = 2;
  emx->allocatedSize = numEl;
  emx->canFreeData = false;
  return emx;
}

/*
 * Arguments    : FHZ4_DataBuff *data
 *                int rows
 *                int cols
 * Return Type  : emxArray_FHZ4_DataBuff *
 */
emxArray_FHZ4_DataBuff *emxCreateWrapper_FHZ4_DataBuff(FHZ4_DataBuff *data, int
  rows, int cols)
{
  emxArray_FHZ4_DataBuff *emx;
  int size[2];
  int numEl;
  int i;
  size[0] = rows;
  size[1] = cols;
  emxInit_FHZ4_DataBuff(&emx, 2);
  numEl = 1;
  for (i = 0; i < 2; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }

  emx->data = data;
  emx->numDimensions = 2;
  emx->allocatedSize = numEl;
  emx->canFreeData = false;
  return emx;
}

/*
 * Arguments    : FHZ4_Int *data
 *                int rows
 *                int cols
 * Return Type  : emxArray_FHZ4_Int *
 */
emxArray_FHZ4_Int *emxCreateWrapper_FHZ4_Int(FHZ4_Int *data, int rows, int cols)
{
  emxArray_FHZ4_Int *emx;
  int size[2];
  int numEl;
  int i;
  size[0] = rows;
  size[1] = cols;
  emxInit_FHZ4_Int(&emx, 2);
  numEl = 1;
  for (i = 0; i < 2; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }

  emx->data = data;
  emx->numDimensions = 2;
  emx->allocatedSize = numEl;
  emx->canFreeData = false;
  return emx;
}

/*
 * Arguments    : MFM_Struct *data
 *                int rows
 *                int cols
 * Return Type  : emxArray_MFM_Struct *
 */
emxArray_MFM_Struct *emxCreateWrapper_MFM_Struct(MFM_Struct *data, int rows, int
  cols)
{
  emxArray_MFM_Struct *emx;
  int size[2];
  int numEl;
  int i;
  size[0] = rows;
  size[1] = cols;
  emxInit_MFM_Struct(&emx, 2);
  numEl = 1;
  for (i = 0; i < 2; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }

  emx->data = data;
  emx->numDimensions = 2;
  emx->allocatedSize = numEl;
  emx->canFreeData = false;
  return emx;
}

/*
 * Arguments    : double *data
 *                int rows
 *                int cols
 * Return Type  : emxArray_real_T *
 */
emxArray_real_T *emxCreateWrapper_real_T(double *data, int rows, int cols)
{
  emxArray_real_T *emx;
  int size[2];
  int numEl;
  int i;
  size[0] = rows;
  size[1] = cols;
  emxInit_real_T1(&emx, 2);
  numEl = 1;
  for (i = 0; i < 2; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }

  emx->data = data;
  emx->numDimensions = 2;
  emx->allocatedSize = numEl;
  emx->canFreeData = false;
  return emx;
}

/*
 * Arguments    : int rows
 *                int cols
 * Return Type  : emxArray_FHZ3_DataBuff *
 */
emxArray_FHZ3_DataBuff *emxCreate_FHZ3_DataBuff(int rows, int cols)
{
  emxArray_FHZ3_DataBuff *emx;
  int size[2];
  int numEl;
  int i;
  size[0] = rows;
  size[1] = cols;
  emxInit_FHZ3_DataBuff(&emx, 2);
  numEl = 1;
  for (i = 0; i < 2; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }

  emx->data = (FHZ3_DataBuff *)calloc((unsigned int)numEl, sizeof(FHZ3_DataBuff));
  emx->numDimensions = 2;
  emx->allocatedSize = numEl;
  return emx;
}

/*
 * Arguments    : int rows
 *                int cols
 * Return Type  : emxArray_FHZ3_Int *
 */
emxArray_FHZ3_Int *emxCreate_FHZ3_Int(int rows, int cols)
{
  emxArray_FHZ3_Int *emx;
  int size[2];
  int numEl;
  int i;
  size[0] = rows;
  size[1] = cols;
  emxInit_FHZ3_Int(&emx, 2);
  numEl = 1;
  for (i = 0; i < 2; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }

  emx->data = (FHZ3_Int *)calloc((unsigned int)numEl, sizeof(FHZ3_Int));
  emx->numDimensions = 2;
  emx->allocatedSize = numEl;
  return emx;
}

/*
 * Arguments    : int rows
 *                int cols
 * Return Type  : emxArray_FHZ4_DataBuff *
 */
emxArray_FHZ4_DataBuff *emxCreate_FHZ4_DataBuff(int rows, int cols)
{
  emxArray_FHZ4_DataBuff *emx;
  int size[2];
  int numEl;
  int i;
  size[0] = rows;
  size[1] = cols;
  emxInit_FHZ4_DataBuff(&emx, 2);
  numEl = 1;
  for (i = 0; i < 2; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }

  emx->data = (FHZ4_DataBuff *)calloc((unsigned int)numEl, sizeof(FHZ4_DataBuff));
  emx->numDimensions = 2;
  emx->allocatedSize = numEl;
  return emx;
}

/*
 * Arguments    : int rows
 *                int cols
 * Return Type  : emxArray_FHZ4_Int *
 */
emxArray_FHZ4_Int *emxCreate_FHZ4_Int(int rows, int cols)
{
  emxArray_FHZ4_Int *emx;
  int size[2];
  int numEl;
  int i;
  size[0] = rows;
  size[1] = cols;
  emxInit_FHZ4_Int(&emx, 2);
  numEl = 1;
  for (i = 0; i < 2; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }

  emx->data = (FHZ4_Int *)calloc((unsigned int)numEl, sizeof(FHZ4_Int));
  emx->numDimensions = 2;
  emx->allocatedSize = numEl;
  return emx;
}

/*
 * Arguments    : int rows
 *                int cols
 * Return Type  : emxArray_MFM_Struct *
 */
emxArray_MFM_Struct *emxCreate_MFM_Struct(int rows, int cols)
{
  emxArray_MFM_Struct *emx;
  int size[2];
  int numEl;
  int i;
  size[0] = rows;
  size[1] = cols;
  emxInit_MFM_Struct(&emx, 2);
  numEl = 1;
  for (i = 0; i < 2; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }

  emx->data = (MFM_Struct *)calloc((unsigned int)numEl, sizeof(MFM_Struct));
  emx->numDimensions = 2;
  emx->allocatedSize = numEl;
  return emx;
}

/*
 * Arguments    : int rows
 *                int cols
 * Return Type  : emxArray_real_T *
 */
emxArray_real_T *emxCreate_real_T(int rows, int cols)
{
  emxArray_real_T *emx;
  int size[2];
  int numEl;
  int i;
  size[0] = rows;
  size[1] = cols;
  emxInit_real_T1(&emx, 2);
  numEl = 1;
  for (i = 0; i < 2; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }

  emx->data = (double *)calloc((unsigned int)numEl, sizeof(double));
  emx->numDimensions = 2;
  emx->allocatedSize = numEl;
  return emx;
}

/*
 * Arguments    : emxArray_FHZ3_DataBuff *emxArray
 * Return Type  : void
 */
void emxDestroyArray_FHZ3_DataBuff(emxArray_FHZ3_DataBuff *emxArray)
{
  emxFree_FHZ3_DataBuff(&emxArray);
}

/*
 * Arguments    : emxArray_FHZ3_Int *emxArray
 * Return Type  : void
 */
void emxDestroyArray_FHZ3_Int(emxArray_FHZ3_Int *emxArray)
{
  emxFree_FHZ3_Int(&emxArray);
}

/*
 * Arguments    : emxArray_FHZ4_DataBuff *emxArray
 * Return Type  : void
 */
void emxDestroyArray_FHZ4_DataBuff(emxArray_FHZ4_DataBuff *emxArray)
{
  emxFree_FHZ4_DataBuff(&emxArray);
}

/*
 * Arguments    : emxArray_FHZ4_Int *emxArray
 * Return Type  : void
 */
void emxDestroyArray_FHZ4_Int(emxArray_FHZ4_Int *emxArray)
{
  emxFree_FHZ4_Int(&emxArray);
}

/*
 * Arguments    : emxArray_MFM_Struct *emxArray
 * Return Type  : void
 */
void emxDestroyArray_MFM_Struct(emxArray_MFM_Struct *emxArray)
{
  emxFree_MFM_Struct(&emxArray);
}

/*
 * Arguments    : emxArray_real_T *emxArray
 * Return Type  : void
 */
void emxDestroyArray_real_T(emxArray_real_T *emxArray)
{
  emxFree_real_T(&emxArray);
}

/*
 * Arguments    : emxArray_FHZ3_DataBuff **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void emxInitArray_FHZ3_DataBuff(emxArray_FHZ3_DataBuff **pEmxArray, int
  numDimensions)
{
  emxInit_FHZ3_DataBuff(pEmxArray, numDimensions);
}

/*
 * Arguments    : emxArray_FHZ3_Int **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void emxInitArray_FHZ3_Int(emxArray_FHZ3_Int **pEmxArray, int numDimensions)
{
  emxInit_FHZ3_Int(pEmxArray, numDimensions);
}

/*
 * Arguments    : emxArray_FHZ4_DataBuff **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void emxInitArray_FHZ4_DataBuff(emxArray_FHZ4_DataBuff **pEmxArray, int
  numDimensions)
{
  emxInit_FHZ4_DataBuff(pEmxArray, numDimensions);
}

/*
 * Arguments    : emxArray_FHZ4_Int **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void emxInitArray_FHZ4_Int(emxArray_FHZ4_Int **pEmxArray, int numDimensions)
{
  emxInit_FHZ4_Int(pEmxArray, numDimensions);
}

/*
 * Arguments    : emxArray_MFM_Struct **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void emxInitArray_MFM_Struct(emxArray_MFM_Struct **pEmxArray, int numDimensions)
{
  emxInit_MFM_Struct(pEmxArray, numDimensions);
}

/*
 * Arguments    : emxArray_real_T **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void emxInitArray_real_T(emxArray_real_T **pEmxArray, int numDimensions)
{
  emxInit_real_T(pEmxArray, numDimensions);
}

/*
 * File trailer for FHZN_define_model_del_emxAPI.c
 *
 * [EOF]
 */
