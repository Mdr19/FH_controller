/*
 * File: conv.c
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
#include "conv.h"
#include "FHZN_define_model_del_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *A
 *                const emxArray_real_T *B
 *                emxArray_real_T *C
 * Return Type  : void
 */
void b_conv(const emxArray_real_T *A, const emxArray_real_T *B, emxArray_real_T *
            C)
{
  int nA;
  int nB;
  int nApnB;
  int jA2;
  int jC;
  double s;
  int k;
  nA = A->size[1];
  nB = B->size[1];
  nApnB = A->size[1] + B->size[1];
  if ((A->size[1] == 0) || (B->size[1] == 0)) {
  } else {
    nApnB--;
  }

  jA2 = C->size[0] * C->size[1];
  C->size[0] = 1;
  C->size[1] = nApnB;
  emxEnsureCapacity((emxArray__common *)C, jA2, (int)sizeof(double));
  if ((A->size[1] == 0) || (B->size[1] == 0) || (nApnB == 0)) {
    jA2 = C->size[0] * C->size[1];
    C->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)C, jA2, (int)sizeof(double));
    jC = C->size[1];
    for (jA2 = 0; jA2 < jC; jA2++) {
      C->data[C->size[0] * jA2] = 0.0;
    }
  } else {
    for (jC = 1; jC <= nApnB; jC++) {
      if (nA <= jC) {
        jA2 = nA;
      } else {
        jA2 = jC;
      }

      s = 0.0;
      if (nB < jC + 1) {
        k = (jC - nB) + 1;
      } else {
        k = 1;
      }

      while (k <= jA2) {
        s += A->data[k - 1] * B->data[jC - k];
        k++;
      }

      C->data[jC - 1] = s;
    }
  }
}

/*
 * Arguments    : const emxArray_real_T *A
 *                const emxArray_real_T *B
 *                emxArray_real_T *C
 * Return Type  : void
 */
void conv(const emxArray_real_T *A, const emxArray_real_T *B, emxArray_real_T *C)
{
  int nA;
  int nB;
  int nApnB;
  int jA2;
  int jC;
  double s;
  int k;
  nA = A->size[0];
  nB = B->size[1];
  nApnB = A->size[0] + B->size[1];
  if ((A->size[0] == 0) || (B->size[1] == 0)) {
  } else {
    nApnB--;
  }

  jA2 = C->size[0];
  C->size[0] = nApnB;
  emxEnsureCapacity((emxArray__common *)C, jA2, (int)sizeof(double));
  if ((A->size[0] == 0) || (B->size[1] == 0) || (nApnB == 0)) {
    jC = C->size[0];
    jA2 = C->size[0];
    C->size[0] = jC;
    emxEnsureCapacity((emxArray__common *)C, jA2, (int)sizeof(double));
    for (jA2 = 0; jA2 < jC; jA2++) {
      C->data[jA2] = 0.0;
    }
  } else {
    for (jC = 1; jC <= nApnB; jC++) {
      if (nA <= jC) {
        jA2 = nA;
      } else {
        jA2 = jC;
      }

      s = 0.0;
      if (nB < jC + 1) {
        k = (jC - nB) + 1;
      } else {
        k = 1;
      }

      while (k <= jA2) {
        s += A->data[k - 1] * B->data[jC - k];
        k++;
      }

      C->data[jC - 1] = s;
    }
  }
}

/*
 * File trailer for conv.c
 *
 * [EOF]
 */
