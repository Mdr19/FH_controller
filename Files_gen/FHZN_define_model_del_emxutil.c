/*
 * File: FHZN_define_model_del_emxutil.c
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
#include "FHZN_define_model_del_emxutil.h"

/* Function Declarations */
static void emxFreeStruct_FHZ3_DataBuff(FHZ3_DataBuff *pStruct);
static void emxFreeStruct_FHZ3_Int(FHZ3_Int *pStruct);
static void emxFreeStruct_FHZ4_DataBuff(FHZ4_DataBuff *pStruct);
static void emxFreeStruct_FHZ4_Int(FHZ4_Int *pStruct);

/* Function Definitions */

/*
 * Arguments    : FHZ3_DataBuff *pStruct
 * Return Type  : void
 */
static void emxFreeStruct_FHZ3_DataBuff(FHZ3_DataBuff *pStruct)
{
  emxFree_real_T(&pStruct->input_1);
  emxFree_real_T(&pStruct->input_2);
  emxFree_real_T(&pStruct->input_3);
  emxFree_real_T(&pStruct->output);
  emxFree_real_T(&pStruct->sp_value);
  emxFree_real_T(&pStruct->time);
}

/*
 * Arguments    : FHZ3_Int *pStruct
 * Return Type  : void
 */
static void emxFreeStruct_FHZ3_Int(FHZ3_Int *pStruct)
{
  emxFree_real_T(&pStruct->X0);
}

/*
 * Arguments    : FHZ4_DataBuff *pStruct
 * Return Type  : void
 */
static void emxFreeStruct_FHZ4_DataBuff(FHZ4_DataBuff *pStruct)
{
  emxFree_real_T(&pStruct->input_1);
  emxFree_real_T(&pStruct->input_2);
  emxFree_real_T(&pStruct->output);
  emxFree_real_T(&pStruct->sp_value);
  emxFree_real_T(&pStruct->time);
}

/*
 * Arguments    : FHZ4_Int *pStruct
 * Return Type  : void
 */
static void emxFreeStruct_FHZ4_Int(FHZ4_Int *pStruct)
{
  emxFree_real_T(&pStruct->X0);
}

/*
 * Arguments    : emxArray__common *emxArray
 *                int oldNumel
 *                int elementSize
 * Return Type  : void
 */
void emxEnsureCapacity(emxArray__common *emxArray, int oldNumel, int elementSize)
{
  int newNumel;
  int i;
  void *newData;
  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }

  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }

    while (i < newNumel) {
      i <<= 1;
    }

    newData = calloc((unsigned int)i, (unsigned int)elementSize);
    if (emxArray->data != NULL) {
      memcpy(newData, emxArray->data, (unsigned int)(elementSize * oldNumel));
      if (emxArray->canFreeData) {
        free(emxArray->data);
      }
    }

    emxArray->data = newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }
}

/*
 * Arguments    : emxArray_FHZ3_DataBuff **pEmxArray
 * Return Type  : void
 */
void emxFree_FHZ3_DataBuff(emxArray_FHZ3_DataBuff **pEmxArray)
{
  int numEl;
  int i;
  if (*pEmxArray != (emxArray_FHZ3_DataBuff *)NULL) {
    if ((*pEmxArray)->data != (FHZ3_DataBuff *)NULL) {
      numEl = 1;
      for (i = 0; i < (*pEmxArray)->numDimensions; i++) {
        numEl *= (*pEmxArray)->size[i];
      }

      for (i = 0; i < numEl; i++) {
        emxFreeStruct_FHZ3_DataBuff(&(*pEmxArray)->data[i]);
      }

      if ((*pEmxArray)->canFreeData) {
        free((void *)(*pEmxArray)->data);
      }
    }

    free((void *)(*pEmxArray)->size);
    free((void *)*pEmxArray);
    *pEmxArray = (emxArray_FHZ3_DataBuff *)NULL;
  }
}

/*
 * Arguments    : emxArray_FHZ3_Int **pEmxArray
 * Return Type  : void
 */
void emxFree_FHZ3_Int(emxArray_FHZ3_Int **pEmxArray)
{
  int numEl;
  int i;
  if (*pEmxArray != (emxArray_FHZ3_Int *)NULL) {
    if ((*pEmxArray)->data != (FHZ3_Int *)NULL) {
      numEl = 1;
      for (i = 0; i < (*pEmxArray)->numDimensions; i++) {
        numEl *= (*pEmxArray)->size[i];
      }

      for (i = 0; i < numEl; i++) {
        emxFreeStruct_FHZ3_Int(&(*pEmxArray)->data[i]);
      }

      if ((*pEmxArray)->canFreeData) {
        free((void *)(*pEmxArray)->data);
      }
    }

    free((void *)(*pEmxArray)->size);
    free((void *)*pEmxArray);
    *pEmxArray = (emxArray_FHZ3_Int *)NULL;
  }
}

/*
 * Arguments    : emxArray_FHZ4_DataBuff **pEmxArray
 * Return Type  : void
 */
void emxFree_FHZ4_DataBuff(emxArray_FHZ4_DataBuff **pEmxArray)
{
  int numEl;
  int i;
  if (*pEmxArray != (emxArray_FHZ4_DataBuff *)NULL) {
    if ((*pEmxArray)->data != (FHZ4_DataBuff *)NULL) {
      numEl = 1;
      for (i = 0; i < (*pEmxArray)->numDimensions; i++) {
        numEl *= (*pEmxArray)->size[i];
      }

      for (i = 0; i < numEl; i++) {
        emxFreeStruct_FHZ4_DataBuff(&(*pEmxArray)->data[i]);
      }

      if ((*pEmxArray)->canFreeData) {
        free((void *)(*pEmxArray)->data);
      }
    }

    free((void *)(*pEmxArray)->size);
    free((void *)*pEmxArray);
    *pEmxArray = (emxArray_FHZ4_DataBuff *)NULL;
  }
}

/*
 * Arguments    : emxArray_FHZ4_Int **pEmxArray
 * Return Type  : void
 */
void emxFree_FHZ4_Int(emxArray_FHZ4_Int **pEmxArray)
{
  int numEl;
  int i;
  if (*pEmxArray != (emxArray_FHZ4_Int *)NULL) {
    if ((*pEmxArray)->data != (FHZ4_Int *)NULL) {
      numEl = 1;
      for (i = 0; i < (*pEmxArray)->numDimensions; i++) {
        numEl *= (*pEmxArray)->size[i];
      }

      for (i = 0; i < numEl; i++) {
        emxFreeStruct_FHZ4_Int(&(*pEmxArray)->data[i]);
      }

      if ((*pEmxArray)->canFreeData) {
        free((void *)(*pEmxArray)->data);
      }
    }

    free((void *)(*pEmxArray)->size);
    free((void *)*pEmxArray);
    *pEmxArray = (emxArray_FHZ4_Int *)NULL;
  }
}

/*
 * Arguments    : emxArray_MFM_Struct **pEmxArray
 * Return Type  : void
 */
void emxFree_MFM_Struct(emxArray_MFM_Struct **pEmxArray)
{
  if (*pEmxArray != (emxArray_MFM_Struct *)NULL) {
    if (((*pEmxArray)->data != (MFM_Struct *)NULL) && (*pEmxArray)->canFreeData)
    {
      free((void *)(*pEmxArray)->data);
    }

    free((void *)(*pEmxArray)->size);
    free((void *)*pEmxArray);
    *pEmxArray = (emxArray_MFM_Struct *)NULL;
  }
}

/*
 * Arguments    : emxArray_int32_T **pEmxArray
 * Return Type  : void
 */
void emxFree_int32_T(emxArray_int32_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_int32_T *)NULL) {
    if (((*pEmxArray)->data != (int *)NULL) && (*pEmxArray)->canFreeData) {
      free((void *)(*pEmxArray)->data);
    }

    free((void *)(*pEmxArray)->size);
    free((void *)*pEmxArray);
    *pEmxArray = (emxArray_int32_T *)NULL;
  }
}

/*
 * Arguments    : emxArray_real_T **pEmxArray
 * Return Type  : void
 */
void emxFree_real_T(emxArray_real_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_real_T *)NULL) {
    if (((*pEmxArray)->data != (double *)NULL) && (*pEmxArray)->canFreeData) {
      free((void *)(*pEmxArray)->data);
    }

    free((void *)(*pEmxArray)->size);
    free((void *)*pEmxArray);
    *pEmxArray = (emxArray_real_T *)NULL;
  }
}

/*
 * Arguments    : emxArray_FHZ3_DataBuff **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void emxInit_FHZ3_DataBuff(emxArray_FHZ3_DataBuff **pEmxArray, int numDimensions)
{
  emxArray_FHZ3_DataBuff *emxArray;
  int i;
  *pEmxArray = (emxArray_FHZ3_DataBuff *)malloc(sizeof(emxArray_FHZ3_DataBuff));
  emxArray = *pEmxArray;
  emxArray->data = (FHZ3_DataBuff *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc((unsigned int)(sizeof(int) * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * Arguments    : emxArray_FHZ3_Int **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void emxInit_FHZ3_Int(emxArray_FHZ3_Int **pEmxArray, int numDimensions)
{
  emxArray_FHZ3_Int *emxArray;
  int i;
  *pEmxArray = (emxArray_FHZ3_Int *)malloc(sizeof(emxArray_FHZ3_Int));
  emxArray = *pEmxArray;
  emxArray->data = (FHZ3_Int *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc((unsigned int)(sizeof(int) * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * Arguments    : emxArray_FHZ4_DataBuff **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void emxInit_FHZ4_DataBuff(emxArray_FHZ4_DataBuff **pEmxArray, int numDimensions)
{
  emxArray_FHZ4_DataBuff *emxArray;
  int i;
  *pEmxArray = (emxArray_FHZ4_DataBuff *)malloc(sizeof(emxArray_FHZ4_DataBuff));
  emxArray = *pEmxArray;
  emxArray->data = (FHZ4_DataBuff *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc((unsigned int)(sizeof(int) * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * Arguments    : emxArray_FHZ4_Int **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void emxInit_FHZ4_Int(emxArray_FHZ4_Int **pEmxArray, int numDimensions)
{
  emxArray_FHZ4_Int *emxArray;
  int i;
  *pEmxArray = (emxArray_FHZ4_Int *)malloc(sizeof(emxArray_FHZ4_Int));
  emxArray = *pEmxArray;
  emxArray->data = (FHZ4_Int *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc((unsigned int)(sizeof(int) * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * Arguments    : emxArray_MFM_Struct **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void emxInit_MFM_Struct(emxArray_MFM_Struct **pEmxArray, int numDimensions)
{
  emxArray_MFM_Struct *emxArray;
  int i;
  *pEmxArray = (emxArray_MFM_Struct *)malloc(sizeof(emxArray_MFM_Struct));
  emxArray = *pEmxArray;
  emxArray->data = (MFM_Struct *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc((unsigned int)(sizeof(int) * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * Arguments    : emxArray_int32_T **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void emxInit_int32_T(emxArray_int32_T **pEmxArray, int numDimensions)
{
  emxArray_int32_T *emxArray;
  int i;
  *pEmxArray = (emxArray_int32_T *)malloc(sizeof(emxArray_int32_T));
  emxArray = *pEmxArray;
  emxArray->data = (int *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc((unsigned int)(sizeof(int) * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * Arguments    : emxArray_int32_T **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void emxInit_int32_T1(emxArray_int32_T **pEmxArray, int numDimensions)
{
  emxArray_int32_T *emxArray;
  int i;
  *pEmxArray = (emxArray_int32_T *)malloc(sizeof(emxArray_int32_T));
  emxArray = *pEmxArray;
  emxArray->data = (int *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc((unsigned int)(sizeof(int) * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * Arguments    : emxArray_real_T **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions)
{
  emxArray_real_T *emxArray;
  int i;
  *pEmxArray = (emxArray_real_T *)malloc(sizeof(emxArray_real_T));
  emxArray = *pEmxArray;
  emxArray->data = (double *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc((unsigned int)(sizeof(int) * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * Arguments    : emxArray_real_T **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void emxInit_real_T1(emxArray_real_T **pEmxArray, int numDimensions)
{
  emxArray_real_T *emxArray;
  int i;
  *pEmxArray = (emxArray_real_T *)malloc(sizeof(emxArray_real_T));
  emxArray = *pEmxArray;
  emxArray->data = (double *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc((unsigned int)(sizeof(int) * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * Arguments    : emxArray_real_T **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void emxInit_real_T2(emxArray_real_T **pEmxArray, int numDimensions)
{
  emxArray_real_T *emxArray;
  int i;
  *pEmxArray = (emxArray_real_T *)malloc(sizeof(emxArray_real_T));
  emxArray = *pEmxArray;
  emxArray->data = (double *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc((unsigned int)(sizeof(int) * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * File trailer for FHZN_define_model_del_emxutil.c
 *
 * [EOF]
 */
