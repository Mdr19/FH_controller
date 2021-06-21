/*
 * File: lagc.c
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
#include "lagc.h"
#include "FHZN_define_model_del_emxutil.h"
#include "eye.h"

/* Function Definitions */

/*
 * Generating system matrix Ap
 * Arguments    : double p
 *                double N
 *                emxArray_real_T *Ap
 *                emxArray_real_T *L0
 * Return Type  : void
 */
void lagc(double p, double N, emxArray_real_T *Ap, emxArray_real_T *L0)
{
  int b_Ap;
  int c_Ap;
  int ii;
  int jj;
  double x;
  eye(N, N, Ap);
  b_Ap = Ap->size[0] * Ap->size[1];
  emxEnsureCapacity((emxArray__common *)Ap, b_Ap, (int)sizeof(double));
  b_Ap = Ap->size[0];
  c_Ap = Ap->size[1];
  c_Ap *= b_Ap;
  for (b_Ap = 0; b_Ap < c_Ap; b_Ap++) {
    Ap->data[b_Ap] *= -p;
  }

  for (ii = 0; ii < (int)N; ii++) {
    for (jj = 0; jj < (int)N; jj++) {
      if (1.0 + (double)jj < 1.0 + (double)ii) {
        Ap->data[ii + Ap->size[0] * jj] = -2.0 * p;
      }
    }
  }

  x = sqrt(2.0 * p);
  b_Ap = L0->size[0];
  L0->size[0] = (int)N;
  emxEnsureCapacity((emxArray__common *)L0, b_Ap, (int)sizeof(double));
  c_Ap = (int)N;
  for (b_Ap = 0; b_Ap < c_Ap; b_Ap++) {
    L0->data[b_Ap] = x;
  }
}

/*
 * File trailer for lagc.c
 *
 * [EOF]
 */
