/*
 * File: qrsolve.c
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
#include "qrsolve.h"
#include "FHZN_define_model_del_emxutil.h"
#include "xgeqp3.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *A
 *                const emxArray_real_T *B
 *                emxArray_real_T *Y
 * Return Type  : void
 */
void qrsolve(const emxArray_real_T *A, const emxArray_real_T *B, emxArray_real_T
             *Y)
{
  emxArray_real_T *b_A;
  int i;
  int minmn;
  emxArray_real_T *tau;
  emxArray_int32_T *jpvt;
  int rankR;
  int maxmn;
  double tol;
  emxArray_real_T *b_B;
  int m;
  int mn;
  emxInit_real_T(&b_A, 2);
  i = b_A->size[0] * b_A->size[1];
  b_A->size[0] = A->size[0];
  b_A->size[1] = A->size[1];
  emxEnsureCapacity((emxArray__common *)b_A, i, (int)sizeof(double));
  minmn = A->size[0] * A->size[1];
  for (i = 0; i < minmn; i++) {
    b_A->data[i] = A->data[i];
  }

  emxInit_real_T1(&tau, 1);
  emxInit_int32_T(&jpvt, 2);
  xgeqp3(b_A, tau, jpvt);
  rankR = 0;
  if (b_A->size[0] < b_A->size[1]) {
    minmn = b_A->size[0];
    maxmn = b_A->size[1];
  } else {
    minmn = b_A->size[1];
    maxmn = b_A->size[0];
  }

  if (minmn > 0) {
    tol = (double)maxmn * fabs(b_A->data[0]) * 2.2204460492503131E-16;
    while ((rankR < minmn) && (fabs(b_A->data[rankR + b_A->size[0] * rankR]) >=
            tol)) {
      rankR++;
    }
  }

  minmn = b_A->size[1];
  maxmn = B->size[1];
  i = Y->size[0] * Y->size[1];
  Y->size[0] = minmn;
  Y->size[1] = maxmn;
  emxEnsureCapacity((emxArray__common *)Y, i, (int)sizeof(double));
  minmn *= maxmn;
  for (i = 0; i < minmn; i++) {
    Y->data[i] = 0.0;
  }

  emxInit_real_T(&b_B, 2);
  i = b_B->size[0] * b_B->size[1];
  b_B->size[0] = B->size[0];
  b_B->size[1] = B->size[1];
  emxEnsureCapacity((emxArray__common *)b_B, i, (int)sizeof(double));
  minmn = B->size[0] * B->size[1];
  for (i = 0; i < minmn; i++) {
    b_B->data[i] = B->data[i];
  }

  m = b_A->size[0];
  minmn = b_A->size[0];
  mn = b_A->size[1];
  if (minmn <= mn) {
    mn = minmn;
  }

  for (minmn = 0; minmn + 1 <= mn; minmn++) {
    if (tau->data[minmn] != 0.0) {
      for (maxmn = 0; maxmn + 1 <= B->size[1]; maxmn++) {
        tol = b_B->data[minmn + b_B->size[0] * maxmn];
        for (i = minmn + 1; i + 1 <= m; i++) {
          tol += b_A->data[i + b_A->size[0] * minmn] * b_B->data[i + b_B->size[0]
            * maxmn];
        }

        tol *= tau->data[minmn];
        if (tol != 0.0) {
          b_B->data[minmn + b_B->size[0] * maxmn] -= tol;
          for (i = minmn + 1; i + 1 <= m; i++) {
            b_B->data[i + b_B->size[0] * maxmn] -= b_A->data[i + b_A->size[0] *
              minmn] * tol;
          }
        }
      }
    }
  }

  emxFree_real_T(&tau);
  for (maxmn = 0; maxmn + 1 <= B->size[1]; maxmn++) {
    for (i = 0; i + 1 <= rankR; i++) {
      Y->data[(jpvt->data[i] + Y->size[0] * maxmn) - 1] = b_B->data[i +
        b_B->size[0] * maxmn];
    }

    for (minmn = rankR - 1; minmn + 1 > 0; minmn--) {
      Y->data[(jpvt->data[minmn] + Y->size[0] * maxmn) - 1] /= b_A->data[minmn +
        b_A->size[0] * minmn];
      for (i = 0; i + 1 <= minmn; i++) {
        Y->data[(jpvt->data[i] + Y->size[0] * maxmn) - 1] -= Y->data[(jpvt->
          data[minmn] + Y->size[0] * maxmn) - 1] * b_A->data[i + b_A->size[0] *
          minmn];
      }
    }
  }

  emxFree_real_T(&b_B);
  emxFree_int32_T(&jpvt);
  emxFree_real_T(&b_A);
}

/*
 * File trailer for qrsolve.c
 *
 * [EOF]
 */
