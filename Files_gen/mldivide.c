/*
 * File: mldivide.c
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
#include "mldivide.h"
#include "FHZN_define_model_del_emxutil.h"
#include "xtrsm.h"
#include "xgetrf.h"
#include "qrsolve.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *A
 *                const emxArray_real_T *B
 *                emxArray_real_T *Y
 * Return Type  : void
 */
void mldivide(const emxArray_real_T *A, const emxArray_real_T *B,
              emxArray_real_T *Y)
{
  emxArray_real_T *b_A;
  emxArray_int32_T *ipiv;
  unsigned int unnamed_idx_0;
  unsigned int unnamed_idx_1;
  int jBcol;
  int ip;
  int n;
  int info;
  int nb;
  double temp;
  int kAcol;
  int i;
  emxInit_real_T(&b_A, 2);
  emxInit_int32_T(&ipiv, 2);
  if ((A->size[0] == 0) || (A->size[1] == 0) || ((B->size[0] == 0) || (B->size[1]
        == 0))) {
    unnamed_idx_0 = (unsigned int)A->size[1];
    unnamed_idx_1 = (unsigned int)B->size[1];
    jBcol = Y->size[0] * Y->size[1];
    Y->size[0] = (int)unnamed_idx_0;
    Y->size[1] = (int)unnamed_idx_1;
    emxEnsureCapacity((emxArray__common *)Y, jBcol, (int)sizeof(double));
    ip = (int)unnamed_idx_0 * (int)unnamed_idx_1;
    for (jBcol = 0; jBcol < ip; jBcol++) {
      Y->data[jBcol] = 0.0;
    }
  } else if (A->size[0] == A->size[1]) {
    n = A->size[1];
    jBcol = b_A->size[0] * b_A->size[1];
    b_A->size[0] = A->size[0];
    b_A->size[1] = A->size[1];
    emxEnsureCapacity((emxArray__common *)b_A, jBcol, (int)sizeof(double));
    ip = A->size[0] * A->size[1];
    for (jBcol = 0; jBcol < ip; jBcol++) {
      b_A->data[jBcol] = A->data[jBcol];
    }

    xgetrf(A->size[1], A->size[1], b_A, A->size[1], ipiv, &info);
    jBcol = Y->size[0] * Y->size[1];
    Y->size[0] = B->size[0];
    Y->size[1] = B->size[1];
    emxEnsureCapacity((emxArray__common *)Y, jBcol, (int)sizeof(double));
    ip = B->size[0] * B->size[1];
    for (jBcol = 0; jBcol < ip; jBcol++) {
      Y->data[jBcol] = B->data[jBcol];
    }

    nb = B->size[1];
    for (jBcol = 0; jBcol + 1 < n; jBcol++) {
      if (ipiv->data[jBcol] != jBcol + 1) {
        ip = ipiv->data[jBcol] - 1;
        for (info = 0; info + 1 <= nb; info++) {
          temp = Y->data[jBcol + Y->size[0] * info];
          Y->data[jBcol + Y->size[0] * info] = Y->data[ip + Y->size[0] * info];
          Y->data[ip + Y->size[0] * info] = temp;
        }
      }
    }

    for (info = 1; info <= nb; info++) {
      jBcol = n * (info - 1);
      for (ip = 0; ip + 1 <= n; ip++) {
        kAcol = n * ip;
        if (Y->data[ip + jBcol] != 0.0) {
          for (i = ip + 1; i + 1 <= n; i++) {
            Y->data[i + jBcol] -= Y->data[ip + jBcol] * b_A->data[i + kAcol];
          }
        }
      }
    }

    xtrsm(A->size[1], B->size[1], b_A, A->size[1], Y, A->size[1]);
  } else {
    qrsolve(A, B, Y);
  }

  emxFree_int32_T(&ipiv);
  emxFree_real_T(&b_A);
}

/*
 * File trailer for mldivide.c
 *
 * [EOF]
 */
