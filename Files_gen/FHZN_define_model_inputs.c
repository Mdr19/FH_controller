/*
 * File: FHZN_define_model_inputs.c
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

/* Function Definitions */

/*
 * Arguments    : double inputs_nr
 *                double corr_tr
 *                double var_tr
 *                const emxArray_real_T *input_signals
 *                const emxArray_real_T *output_signal
 *                emxArray_real_T *model_inputs
 *                double *variance
 *                double *corr
 * Return Type  : void
 */
void FHZN_define_model_inputs(double inputs_nr, double corr_tr, double var_tr,
  const emxArray_real_T *input_signals, const emxArray_real_T *output_signal,
  emxArray_real_T *model_inputs, double *variance, double *corr)
{
  int fm;
  int d;
  int i;
  emxArray_real_T *x;
  emxArray_real_T *b_x;
  emxArray_real_T *b_input_signals;
  int ix;
  int n;
  double xy[4];
  double b_d;
  int k;
  double c_d[2];
  double r;
  fm = model_inputs->size[0] * model_inputs->size[1];
  model_inputs->size[0] = 1;
  model_inputs->size[1] = (int)inputs_nr;
  emxEnsureCapacity((emxArray__common *)model_inputs, fm, (int)sizeof(double));
  d = (int)inputs_nr;
  for (fm = 0; fm < d; fm++) {
    model_inputs->data[fm] = 0.0;
  }

  *variance = 0.0;
  *corr = 0.0;
  i = 0;
  emxInit_real_T(&x, 2);
  emxInit_real_T(&b_x, 2);
  emxInit_real_T1(&b_input_signals, 1);
  while (i <= (int)inputs_nr - 1) {
    d = input_signals->size[0];
    ix = input_signals->size[0];
    fm = b_input_signals->size[0];
    b_input_signals->size[0] = ix;
    emxEnsureCapacity((emxArray__common *)b_input_signals, fm, (int)sizeof
                      (double));
    for (fm = 0; fm < ix; fm++) {
      b_input_signals->data[fm] = input_signals->data[fm + input_signals->size[0]
        * i];
    }

    ix = output_signal->size[0];
    fm = x->size[0] * x->size[1];
    x->size[0] = d;
    x->size[1] = 2;
    emxEnsureCapacity((emxArray__common *)x, fm, (int)sizeof(double));
    for (fm = 0; fm < d; fm++) {
      x->data[fm] = b_input_signals->data[fm];
    }

    for (fm = 0; fm < ix; fm++) {
      x->data[fm + x->size[0]] = output_signal->data[fm];
    }

    fm = b_x->size[0] * b_x->size[1];
    b_x->size[0] = x->size[0];
    b_x->size[1] = 2;
    emxEnsureCapacity((emxArray__common *)b_x, fm, (int)sizeof(double));
    d = x->size[0] * x->size[1];
    for (fm = 0; fm < d; fm++) {
      b_x->data[fm] = x->data[fm];
    }

    n = x->size[0];
    for (fm = 0; fm < 4; fm++) {
      xy[fm] = 0.0;
    }

    if (x->size[0] < 2) {
      for (fm = 0; fm < 4; fm++) {
        xy[fm] = rtNaN;
      }
    } else {
      for (d = 0; d < 2; d++) {
        b_d = 0.0;
        for (ix = 1; ix <= n; ix++) {
          b_d += b_x->data[(ix + b_x->size[0] * d) - 1];
        }

        b_d /= (double)x->size[0];
        for (ix = 0; ix + 1 <= n; ix++) {
          b_x->data[ix + b_x->size[0] * d] -= b_d;
        }
      }

      fm = x->size[0] - 1;
      for (d = 0; d < 2; d++) {
        b_d = 0.0;
        for (k = 0; k + 1 <= n; k++) {
          b_d += b_x->data[k + b_x->size[0] * d] * b_x->data[k + b_x->size[0] *
            d];
        }

        xy[d + (d << 1)] = b_d / (double)fm;
        ix = d + 2;
        while (ix < 3) {
          b_d = 0.0;
          for (k = 0; k + 1 <= n; k++) {
            b_d += b_x->data[k + b_x->size[0]] * b_x->data[k + b_x->size[0] * d];
          }

          xy[1 + (d << 1)] = b_d / (double)fm;
          ix = 3;
        }
      }
    }

    for (k = 0; k < 2; k++) {
      c_d[k] = sqrt(xy[k + (k << 1)]);
    }

    for (d = 0; d < 2; d++) {
      ix = d + 2;
      while (ix < 3) {
        xy[1 + (d << 1)] = xy[1 + (d << 1)] / c_d[1] / c_d[d];
        ix = 3;
      }

      ix = d + 2;
      while (ix < 3) {
        b_d = fabs(xy[1 + (d << 1)]);
        if (b_d > 1.0) {
          xy[1 + (d << 1)] /= b_d;
        }

        xy[2 + d] = xy[1 + (d << 1)];
        ix = 3;
      }

      if (xy[d + (d << 1)] > 0.0) {
        if (xy[d + (d << 1)] < 0.0) {
          xy[d + (d << 1)] = -1.0;
        } else if (xy[d + (d << 1)] > 0.0) {
          xy[d + (d << 1)] = 1.0;
        } else {
          if (xy[d + (d << 1)] == 0.0) {
            xy[d + (d << 1)] = 0.0;
          }
        }
      } else {
        xy[d + (d << 1)] = rtNaN;
      }
    }

    *corr = xy[2];

    /* disp(['Var is equal ' num2str(var(input_signals(:,i))) ' Cor is equal ' num2str(corr)]); */
    fm = input_signals->size[0];
    ix = input_signals->size[0];
    if (ix > 1) {
      d = input_signals->size[0] - 1;
    } else {
      d = input_signals->size[0];
    }

    ix = input_signals->size[0];
    if (ix == 0) {
      *variance = 0.0;
    } else {
      ix = 0;
      b_d = input_signals->data[input_signals->size[0] * i];
      for (k = 2; k <= fm; k++) {
        ix++;
        b_d += input_signals->data[ix + input_signals->size[0] * i];
      }

      b_d /= (double)fm;
      ix = 0;
      r = input_signals->data[input_signals->size[0] * i] - b_d;
      *variance = r * r;
      for (k = 2; k <= fm; k++) {
        ix++;
        r = input_signals->data[ix + input_signals->size[0] * i] - b_d;
        *variance += r * r;
      }

      *variance /= (double)d;
    }

    if ((fabs(xy[2]) > corr_tr) && (*variance > var_tr)) {
      model_inputs->data[model_inputs->size[0] * i] = 1.0;
    }

    i++;
  }

  emxFree_real_T(&b_input_signals);
  emxFree_real_T(&b_x);
  emxFree_real_T(&x);
}

/*
 * File trailer for FHZN_define_model_inputs.c
 *
 * [EOF]
 */
