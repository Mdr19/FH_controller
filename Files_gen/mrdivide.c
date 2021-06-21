/*
 * File: mrdivide.c
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
#include "mrdivide.h"
#include "FHZN_define_model_del_emxutil.h"
#include "xgetrf.h"
#include "qrsolve.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *A
 *                const emxArray_real_T *B
 *                emxArray_real_T *y
 * Return Type  : void
 */
void mrdivide(const emxArray_real_T *A, const emxArray_real_T *B,
              emxArray_real_T *y)
{
  emxArray_real_T *b_A;
  emxArray_int32_T *ipiv;
  emxArray_real_T *b_B;
  emxArray_real_T *c_A;
  unsigned int unnamed_idx_0;
  unsigned int unnamed_idx_1;
  int jAcol;
  int k;
  int n;
  int jp;
  int nb;
  int j;
  int kBcol;
  int i;
  double temp;
  emxInit_real_T(&b_A, 2);
  emxInit_int32_T(&ipiv, 2);
  emxInit_real_T(&b_B, 2);
  emxInit_real_T(&c_A, 2);
  if ((A->size[0] == 0) || (A->size[1] == 0) || ((B->size[0] == 0) || (B->size[1]
        == 0))) {
    unnamed_idx_0 = (unsigned int)A->size[0];
    unnamed_idx_1 = (unsigned int)B->size[0];
    jAcol = y->size[0] * y->size[1];
    y->size[0] = (int)unnamed_idx_0;
    y->size[1] = (int)unnamed_idx_1;
    emxEnsureCapacity((emxArray__common *)y, jAcol, (int)sizeof(double));
    k = (int)unnamed_idx_0 * (int)unnamed_idx_1;
    for (jAcol = 0; jAcol < k; jAcol++) {
      y->data[jAcol] = 0.0;
    }
  } else if (B->size[0] == B->size[1]) {
    n = B->size[1];
    jAcol = b_A->size[0] * b_A->size[1];
    b_A->size[0] = B->size[0];
    b_A->size[1] = B->size[1];
    emxEnsureCapacity((emxArray__common *)b_A, jAcol, (int)sizeof(double));
    k = B->size[0] * B->size[1];
    for (jAcol = 0; jAcol < k; jAcol++) {
      b_A->data[jAcol] = B->data[jAcol];
    }

    xgetrf(B->size[1], B->size[1], b_A, B->size[1], ipiv, &jp);
    nb = A->size[0];
    jAcol = y->size[0] * y->size[1];
    y->size[0] = A->size[0];
    y->size[1] = A->size[1];
    emxEnsureCapacity((emxArray__common *)y, jAcol, (int)sizeof(double));
    k = A->size[0] * A->size[1];
    for (jAcol = 0; jAcol < k; jAcol++) {
      y->data[jAcol] = A->data[jAcol];
    }

    for (j = 0; j + 1 <= n; j++) {
      jp = nb * j - 1;
      jAcol = n * j;
      for (k = 1; k <= j; k++) {
        kBcol = nb * (k - 1);
        if (b_A->data[(k + jAcol) - 1] != 0.0) {
          for (i = 1; i <= nb; i++) {
            y->data[i + jp] -= b_A->data[(k + jAcol) - 1] * y->data[(i + kBcol)
              - 1];
          }
        }
      }

      temp = 1.0 / b_A->data[j + jAcol];
      for (i = 1; i <= nb; i++) {
        y->data[i + jp] *= temp;
      }
    }

    for (j = B->size[1]; j > 0; j--) {
      jp = nb * (j - 1) - 1;
      jAcol = n * (j - 1) - 1;
      for (k = j + 1; k <= n; k++) {
        kBcol = nb * (k - 1);
        if (b_A->data[k + jAcol] != 0.0) {
          for (i = 1; i <= nb; i++) {
            y->data[i + jp] -= b_A->data[k + jAcol] * y->data[(i + kBcol) - 1];
          }
        }
      }
    }

    for (j = B->size[1] - 2; j + 1 > 0; j--) {
      if (ipiv->data[j] != j + 1) {
        jp = ipiv->data[j] - 1;
        for (jAcol = 0; jAcol + 1 <= nb; jAcol++) {
          temp = y->data[jAcol + y->size[0] * j];
          y->data[jAcol + y->size[0] * j] = y->data[jAcol + y->size[0] * jp];
          y->data[jAcol + y->size[0] * jp] = temp;
        }
      }
    }
  } else {
    jAcol = b_B->size[0] * b_B->size[1];
    b_B->size[0] = B->size[1];
    b_B->size[1] = B->size[0];
    emxEnsureCapacity((emxArray__common *)b_B, jAcol, (int)sizeof(double));
    k = B->size[0];
    for (jAcol = 0; jAcol < k; jAcol++) {
      jp = B->size[1];
      for (j = 0; j < jp; j++) {
        b_B->data[j + b_B->size[0] * jAcol] = B->data[jAcol + B->size[0] * j];
      }
    }

    jAcol = c_A->size[0] * c_A->size[1];
    c_A->size[0] = A->size[1];
    c_A->size[1] = A->size[0];
    emxEnsureCapacity((emxArray__common *)c_A, jAcol, (int)sizeof(double));
    k = A->size[0];
    for (jAcol = 0; jAcol < k; jAcol++) {
      jp = A->size[1];
      for (j = 0; j < jp; j++) {
        c_A->data[j + c_A->size[0] * jAcol] = A->data[jAcol + A->size[0] * j];
      }
    }

    qrsolve(b_B, c_A, b_A);
    jAcol = y->size[0] * y->size[1];
    y->size[0] = b_A->size[1];
    y->size[1] = b_A->size[0];
    emxEnsureCapacity((emxArray__common *)y, jAcol, (int)sizeof(double));
    k = b_A->size[0];
    for (jAcol = 0; jAcol < k; jAcol++) {
      jp = b_A->size[1];
      for (j = 0; j < jp; j++) {
        y->data[j + y->size[0] * jAcol] = b_A->data[jAcol + b_A->size[0] * j];
      }
    }
  }

  emxFree_real_T(&c_A);
  emxFree_real_T(&b_B);
  emxFree_int32_T(&ipiv);
  emxFree_real_T(&b_A);
}

/*
 * File trailer for mrdivide.c
 *
 * [EOF]
 */
