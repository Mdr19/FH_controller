/*
 * File: xtrsm.c
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
#include "xtrsm.h"

/* Function Definitions */

/*
 * Arguments    : int m
 *                int n
 *                const emxArray_real_T *A
 *                int lda
 *                emxArray_real_T *B
 *                int ldb
 * Return Type  : void
 */
void xtrsm(int m, int n, const emxArray_real_T *A, int lda, emxArray_real_T *B,
           int ldb)
{
  int j;
  int jBcol;
  int k;
  int kAcol;
  double x;
  double y;
  int i;
  if ((n == 0) || ((B->size[0] == 0) || (B->size[1] == 0))) {
  } else {
    for (j = 1; j <= n; j++) {
      jBcol = ldb * (j - 1);
      for (k = m - 1; k + 1 > 0; k--) {
        kAcol = lda * k;
        if (B->data[k + jBcol] != 0.0) {
          x = B->data[k + jBcol];
          y = A->data[k + kAcol];
          B->data[k + jBcol] = x / y;
          for (i = 0; i + 1 <= k; i++) {
            B->data[i + jBcol] -= B->data[k + jBcol] * A->data[i + kAcol];
          }
        }
      }
    }
  }
}

/*
 * File trailer for xtrsm.c
 *
 * [EOF]
 */
