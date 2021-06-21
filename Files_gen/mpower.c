/*
 * File: mpower.c
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
#include "mpower.h"
#include "FHZN_define_model_del_emxutil.h"
#include "matrix_to_integer_power.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *a
 *                double b
 *                emxArray_real_T *c
 * Return Type  : void
 */
void mpower(const emxArray_real_T *a, double b, emxArray_real_T *c)
{
  emxArray_real_T *b_a;
  int i37;
  int loop_ub;
  unsigned int uv3[2];
  int b_loop_ub;
  int i38;
  if (b == b) {
    if (2.147483647E+9 >= fabs(b)) {
      emxInit_real_T(&b_a, 2);
      i37 = b_a->size[0] * b_a->size[1];
      b_a->size[0] = a->size[0];
      b_a->size[1] = a->size[1];
      emxEnsureCapacity((emxArray__common *)b_a, i37, (int)sizeof(double));
      loop_ub = a->size[0] * a->size[1];
      for (i37 = 0; i37 < loop_ub; i37++) {
        b_a->data[i37] = a->data[i37];
      }

      matrix_to_small_integer_power(b_a, b, c);
      emxFree_real_T(&b_a);
    } else {
      emxInit_real_T(&b_a, 2);
      i37 = b_a->size[0] * b_a->size[1];
      b_a->size[0] = a->size[0];
      b_a->size[1] = a->size[1];
      emxEnsureCapacity((emxArray__common *)b_a, i37, (int)sizeof(double));
      loop_ub = a->size[0] * a->size[1];
      for (i37 = 0; i37 < loop_ub; i37++) {
        b_a->data[i37] = a->data[i37];
      }

      matrix_to_large_integer_power(b_a, b, c);
      emxFree_real_T(&b_a);
    }
  } else {
    for (i37 = 0; i37 < 2; i37++) {
      uv3[i37] = (unsigned int)a->size[i37];
    }

    i37 = c->size[0] * c->size[1];
    c->size[0] = (int)uv3[0];
    c->size[1] = (int)uv3[1];
    emxEnsureCapacity((emxArray__common *)c, i37, (int)sizeof(double));
    loop_ub = c->size[1];
    for (i37 = 0; i37 < loop_ub; i37++) {
      b_loop_ub = c->size[0];
      for (i38 = 0; i38 < b_loop_ub; i38++) {
        c->data[i38 + c->size[0] * i37] = rtNaN;
      }
    }
  }
}

/*
 * File trailer for mpower.c
 *
 * [EOF]
 */
