/*
 * File: Iint.c
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
#include "Iint.h"
#include "FHZN_define_model_del_emxutil.h"
#include "inv.h"
#include "eye.h"

/* Function Definitions */

/*
 * disp('FUNKCJA Iint');
 * wykorzystuje siê strukture macierzy p - lower triangular structure
 * Arguments    : const emxArray_real_T *A
 *                double p
 *                const emxArray_real_T *Y
 *                emxArray_real_T *X
 * Return Type  : void
 */
void Iint(const emxArray_real_T *A, double p, const emxArray_real_T *Y,
          emxArray_real_T *X)
{
  int i36;
  int ar;
  emxArray_real_T *Ai;
  emxArray_real_T *b_A;
  emxArray_real_T *alpha;
  emxArray_real_T *b_Y;
  boolean_T guard1 = false;
  int k;
  unsigned int Ai_idx_0;
  int m;
  int ic;
  int br;
  int ib;
  int ia;
  double a;
  int i;
  emxArray_real_T *C;
  emxArray_real_T *b;
  i36 = X->size[0] * X->size[1];
  X->size[0] = Y->size[0];
  X->size[1] = Y->size[1];
  emxEnsureCapacity((emxArray__common *)X, i36, (int)sizeof(double));
  ar = Y->size[0] * Y->size[1];
  for (i36 = 0; i36 < ar; i36++) {
    X->data[i36] = 0.0;
  }

  emxInit_real_T(&Ai, 2);
  emxInit_real_T(&b_A, 2);
  eye(Y->size[0], Y->size[0], Ai);
  i36 = b_A->size[0] * b_A->size[1];
  b_A->size[0] = A->size[0];
  b_A->size[1] = A->size[1];
  emxEnsureCapacity((emxArray__common *)b_A, i36, (int)sizeof(double));
  ar = A->size[0] * A->size[1];
  for (i36 = 0; i36 < ar; i36++) {
    b_A->data[i36] = A->data[i36] + p * Ai->data[i36];
  }

  inv(b_A, Ai);
  emxFree_real_T(&b_A);
  emxInit_real_T1(&alpha, 1);
  emxInit_real_T1(&b_Y, 1);
  guard1 = false;
  if (Ai->size[1] == 1) {
    guard1 = true;
  } else {
    i36 = Y->size[0];
    if (i36 == 1) {
      guard1 = true;
    } else {
      k = Ai->size[1];
      Ai_idx_0 = (unsigned int)Ai->size[0];
      i36 = alpha->size[0];
      alpha->size[0] = (int)Ai_idx_0;
      emxEnsureCapacity((emxArray__common *)alpha, i36, (int)sizeof(double));
      m = Ai->size[0];
      ar = alpha->size[0];
      i36 = alpha->size[0];
      alpha->size[0] = ar;
      emxEnsureCapacity((emxArray__common *)alpha, i36, (int)sizeof(double));
      for (i36 = 0; i36 < ar; i36++) {
        alpha->data[i36] = 0.0;
      }

      if (Ai->size[0] == 0) {
      } else {
        ar = 0;
        while ((m > 0) && (ar <= 0)) {
          for (ic = 1; ic <= m; ic++) {
            alpha->data[ic - 1] = 0.0;
          }

          ar = m;
        }

        br = 0;
        ar = 0;
        while ((m > 0) && (ar <= 0)) {
          ar = -1;
          i36 = br + k;
          for (ib = br; ib + 1 <= i36; ib++) {
            if (Y->data[ib] != 0.0) {
              ia = ar;
              for (ic = 0; ic + 1 <= m; ic++) {
                ia++;
                alpha->data[ic] += Y->data[ib] * Ai->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          ar = m;
        }
      }
    }
  }

  if (guard1) {
    ar = Y->size[0];
    i36 = b_Y->size[0];
    b_Y->size[0] = ar;
    emxEnsureCapacity((emxArray__common *)b_Y, i36, (int)sizeof(double));
    for (i36 = 0; i36 < ar; i36++) {
      b_Y->data[i36] = Y->data[i36];
    }

    i36 = alpha->size[0];
    alpha->size[0] = Ai->size[0];
    emxEnsureCapacity((emxArray__common *)alpha, i36, (int)sizeof(double));
    ar = Ai->size[0];
    for (i36 = 0; i36 < ar; i36++) {
      alpha->data[i36] = 0.0;
      ib = Ai->size[1];
      for (ia = 0; ia < ib; ia++) {
        alpha->data[i36] += Ai->data[i36 + Ai->size[0] * ia] * b_Y->data[ia];
      }
    }
  }

  emxFree_real_T(&b_Y);
  ar = alpha->size[0];
  for (i36 = 0; i36 < ar; i36++) {
    X->data[i36] = alpha->data[i36];
  }

  a = -2.0 * p;
  ar = X->size[0];
  i36 = alpha->size[0];
  alpha->size[0] = ar;
  emxEnsureCapacity((emxArray__common *)alpha, i36, (int)sizeof(double));
  for (i36 = 0; i36 < ar; i36++) {
    alpha->data[i36] = a * X->data[i36];
  }

  i = 1;
  emxInit_real_T1(&C, 1);
  emxInit_real_T1(&b, 1);
  while (i - 1 <= Y->size[1] - 2) {
    ar = Y->size[0];
    i36 = b->size[0];
    b->size[0] = ar;
    emxEnsureCapacity((emxArray__common *)b, i36, (int)sizeof(double));
    for (i36 = 0; i36 < ar; i36++) {
      b->data[i36] = Y->data[i36 + Y->size[0] * i] + alpha->data[i36];
    }

    if ((Ai->size[1] == 1) || (b->size[0] == 1)) {
      i36 = C->size[0];
      C->size[0] = Ai->size[0];
      emxEnsureCapacity((emxArray__common *)C, i36, (int)sizeof(double));
      ar = Ai->size[0];
      for (i36 = 0; i36 < ar; i36++) {
        C->data[i36] = 0.0;
        ib = Ai->size[1];
        for (ia = 0; ia < ib; ia++) {
          C->data[i36] += Ai->data[i36 + Ai->size[0] * ia] * b->data[ia];
        }
      }
    } else {
      k = Ai->size[1];
      Ai_idx_0 = (unsigned int)Ai->size[0];
      i36 = C->size[0];
      C->size[0] = (int)Ai_idx_0;
      emxEnsureCapacity((emxArray__common *)C, i36, (int)sizeof(double));
      m = Ai->size[0];
      ar = C->size[0];
      i36 = C->size[0];
      C->size[0] = ar;
      emxEnsureCapacity((emxArray__common *)C, i36, (int)sizeof(double));
      for (i36 = 0; i36 < ar; i36++) {
        C->data[i36] = 0.0;
      }

      if (Ai->size[0] == 0) {
      } else {
        ar = 0;
        while ((m > 0) && (ar <= 0)) {
          for (ic = 1; ic <= m; ic++) {
            C->data[ic - 1] = 0.0;
          }

          ar = m;
        }

        br = 0;
        ar = 0;
        while ((m > 0) && (ar <= 0)) {
          ar = -1;
          i36 = br + k;
          for (ib = br; ib + 1 <= i36; ib++) {
            if (b->data[ib] != 0.0) {
              ia = ar;
              for (ic = 0; ic + 1 <= m; ic++) {
                ia++;
                C->data[ic] += b->data[ib] * Ai->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          ar = m;
        }
      }
    }

    ar = C->size[0];
    for (i36 = 0; i36 < ar; i36++) {
      X->data[i36 + X->size[0] * i] = C->data[i36];
    }

    a = 2.0 * p;
    i36 = alpha->size[0];
    emxEnsureCapacity((emxArray__common *)alpha, i36, (int)sizeof(double));
    ar = alpha->size[0];
    for (i36 = 0; i36 < ar; i36++) {
      alpha->data[i36] -= a * X->data[i36 + X->size[0] * i];
    }

    i++;
  }

  emxFree_real_T(&b);
  emxFree_real_T(&C);
  emxFree_real_T(&alpha);
  emxFree_real_T(&Ai);
}

/*
 * File trailer for Iint.c
 *
 * [EOF]
 */
