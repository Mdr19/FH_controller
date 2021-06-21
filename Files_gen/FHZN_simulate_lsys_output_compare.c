/*
 * File: FHZN_simulate_lsys_output_compare.c
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
#include "FHZN_simulate_lsys_output_compare.h"
#include "FHZN_define_model_del_emxutil.h"
#include "sum.h"
#include "power.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *A
 *                const emxArray_real_T *B
 *                const emxArray_real_T *C
 *                emxArray_real_T *X0
 *                const emxArray_real_T *input_signals
 *                const emxArray_real_T *real_output
 * Return Type  : double
 */
double c_FHZN_simulate_lsys_output_com(const emxArray_real_T *A, const
  emxArray_real_T *B, const emxArray_real_T *C, emxArray_real_T *X0, const
  emxArray_real_T *input_signals, const emxArray_real_T *real_output)
{
  double sqr_sum;
  int u1;
  int ar;
  emxArray_real_T *output_signal;
  int i54;
  int i;
  emxArray_real_T *dx1;
  emxArray_real_T *dx2;
  emxArray_real_T *dx3;
  emxArray_real_T *b_C;
  emxArray_real_T *c_C;
  emxArray_real_T *d_C;
  emxArray_real_T *e_C;
  emxArray_real_T *f_C;
  emxArray_real_T *g_C;
  emxArray_real_T *h_C;
  emxArray_real_T *i_C;
  emxArray_real_T *b;
  int ib;
  int ia;
  int k;
  unsigned int A_idx_0;
  int m;
  int ic;
  int br;
  double y;
  emxArray_real_T *b_output_signal;
  if ((input_signals->size[0] == 0) || (input_signals->size[1] == 0)) {
    u1 = 0;
  } else {
    ar = input_signals->size[0];
    u1 = input_signals->size[1];
    if (ar >= u1) {
      u1 = ar;
    }
  }

  emxInit_real_T1(&output_signal, 1);
  i54 = output_signal->size[0];
  output_signal->size[0] = u1;
  emxEnsureCapacity((emxArray__common *)output_signal, i54, (int)sizeof(double));
  for (i54 = 0; i54 < u1; i54++) {
    output_signal->data[i54] = 0.0;
  }

  if ((input_signals->size[0] == 0) || (input_signals->size[1] == 0)) {
    u1 = 0;
  } else {
    ar = input_signals->size[0];
    u1 = input_signals->size[1];
    if (ar >= u1) {
      u1 = ar;
    }
  }

  i = 0;
  emxInit_real_T1(&dx1, 1);
  emxInit_real_T1(&dx2, 1);
  emxInit_real_T1(&dx3, 1);
  emxInit_real_T1(&b_C, 1);
  emxInit_real_T1(&c_C, 1);
  emxInit_real_T1(&d_C, 1);
  emxInit_real_T1(&e_C, 1);
  emxInit_real_T1(&f_C, 1);
  emxInit_real_T1(&g_C, 1);
  emxInit_real_T1(&h_C, 1);
  emxInit_real_T1(&i_C, 1);
  emxInit_real_T1(&b, 1);
  while (i <= u1 - 1) {
    if ((A->size[1] == 1) || (X0->size[0] == 1)) {
      i54 = b_C->size[0];
      b_C->size[0] = A->size[0];
      emxEnsureCapacity((emxArray__common *)b_C, i54, (int)sizeof(double));
      ar = A->size[0];
      for (i54 = 0; i54 < ar; i54++) {
        b_C->data[i54] = 0.0;
        ib = A->size[1];
        for (ia = 0; ia < ib; ia++) {
          b_C->data[i54] += A->data[i54 + A->size[0] * ia] * X0->data[ia];
        }
      }
    } else {
      k = A->size[1];
      A_idx_0 = (unsigned int)A->size[0];
      i54 = b_C->size[0];
      b_C->size[0] = (int)A_idx_0;
      emxEnsureCapacity((emxArray__common *)b_C, i54, (int)sizeof(double));
      m = A->size[0];
      ar = b_C->size[0];
      i54 = b_C->size[0];
      b_C->size[0] = ar;
      emxEnsureCapacity((emxArray__common *)b_C, i54, (int)sizeof(double));
      for (i54 = 0; i54 < ar; i54++) {
        b_C->data[i54] = 0.0;
      }

      if (A->size[0] == 0) {
      } else {
        ar = 0;
        while ((m > 0) && (ar <= 0)) {
          for (ic = 1; ic <= m; ic++) {
            b_C->data[ic - 1] = 0.0;
          }

          ar = m;
        }

        br = 0;
        ar = 0;
        while ((m > 0) && (ar <= 0)) {
          ar = -1;
          i54 = br + k;
          for (ib = br; ib + 1 <= i54; ib++) {
            if (X0->data[ib] != 0.0) {
              ia = ar;
              for (ic = 0; ic + 1 <= m; ic++) {
                ia++;
                b_C->data[ic] += X0->data[ib] * A->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          ar = m;
        }
      }
    }

    ar = input_signals->size[1];
    i54 = b->size[0];
    b->size[0] = ar;
    emxEnsureCapacity((emxArray__common *)b, i54, (int)sizeof(double));
    for (i54 = 0; i54 < ar; i54++) {
      b->data[i54] = input_signals->data[i + input_signals->size[0] * i54];
    }

    if ((B->size[1] == 1) || (b->size[0] == 1)) {
      i54 = c_C->size[0];
      c_C->size[0] = B->size[0];
      emxEnsureCapacity((emxArray__common *)c_C, i54, (int)sizeof(double));
      ar = B->size[0];
      for (i54 = 0; i54 < ar; i54++) {
        c_C->data[i54] = 0.0;
        ib = B->size[1];
        for (ia = 0; ia < ib; ia++) {
          c_C->data[i54] += B->data[i54 + B->size[0] * ia] * b->data[ia];
        }
      }
    } else {
      k = B->size[1];
      A_idx_0 = (unsigned int)B->size[0];
      i54 = c_C->size[0];
      c_C->size[0] = (int)A_idx_0;
      emxEnsureCapacity((emxArray__common *)c_C, i54, (int)sizeof(double));
      m = B->size[0];
      ar = c_C->size[0];
      i54 = c_C->size[0];
      c_C->size[0] = ar;
      emxEnsureCapacity((emxArray__common *)c_C, i54, (int)sizeof(double));
      for (i54 = 0; i54 < ar; i54++) {
        c_C->data[i54] = 0.0;
      }

      if (B->size[0] == 0) {
      } else {
        ar = 0;
        while ((m > 0) && (ar <= 0)) {
          for (ic = 1; ic <= m; ic++) {
            c_C->data[ic - 1] = 0.0;
          }

          ar = m;
        }

        br = 0;
        ar = 0;
        while ((m > 0) && (ar <= 0)) {
          ar = -1;
          i54 = br + k;
          for (ib = br; ib + 1 <= i54; ib++) {
            if (b->data[ib] != 0.0) {
              ia = ar;
              for (ic = 0; ic + 1 <= m; ic++) {
                ia++;
                c_C->data[ic] += b->data[ib] * B->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          ar = m;
        }
      }
    }

    i54 = dx1->size[0];
    dx1->size[0] = b_C->size[0];
    emxEnsureCapacity((emxArray__common *)dx1, i54, (int)sizeof(double));
    ar = b_C->size[0];
    for (i54 = 0; i54 < ar; i54++) {
      dx1->data[i54] = b_C->data[i54] + c_C->data[i54];
    }

    i54 = b->size[0];
    b->size[0] = X0->size[0];
    emxEnsureCapacity((emxArray__common *)b, i54, (int)sizeof(double));
    ar = X0->size[0];
    for (i54 = 0; i54 < ar; i54++) {
      b->data[i54] = X0->data[i54] + 0.5 * dx1->data[i54];
    }

    if ((A->size[1] == 1) || (b->size[0] == 1)) {
      i54 = d_C->size[0];
      d_C->size[0] = A->size[0];
      emxEnsureCapacity((emxArray__common *)d_C, i54, (int)sizeof(double));
      ar = A->size[0];
      for (i54 = 0; i54 < ar; i54++) {
        d_C->data[i54] = 0.0;
        ib = A->size[1];
        for (ia = 0; ia < ib; ia++) {
          d_C->data[i54] += A->data[i54 + A->size[0] * ia] * b->data[ia];
        }
      }
    } else {
      k = A->size[1];
      A_idx_0 = (unsigned int)A->size[0];
      i54 = d_C->size[0];
      d_C->size[0] = (int)A_idx_0;
      emxEnsureCapacity((emxArray__common *)d_C, i54, (int)sizeof(double));
      m = A->size[0];
      ar = d_C->size[0];
      i54 = d_C->size[0];
      d_C->size[0] = ar;
      emxEnsureCapacity((emxArray__common *)d_C, i54, (int)sizeof(double));
      for (i54 = 0; i54 < ar; i54++) {
        d_C->data[i54] = 0.0;
      }

      if (A->size[0] == 0) {
      } else {
        ar = 0;
        while ((m > 0) && (ar <= 0)) {
          for (ic = 1; ic <= m; ic++) {
            d_C->data[ic - 1] = 0.0;
          }

          ar = m;
        }

        br = 0;
        ar = 0;
        while ((m > 0) && (ar <= 0)) {
          ar = -1;
          i54 = br + k;
          for (ib = br; ib + 1 <= i54; ib++) {
            if (b->data[ib] != 0.0) {
              ia = ar;
              for (ic = 0; ic + 1 <= m; ic++) {
                ia++;
                d_C->data[ic] += b->data[ib] * A->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          ar = m;
        }
      }
    }

    ar = input_signals->size[1];
    i54 = b->size[0];
    b->size[0] = ar;
    emxEnsureCapacity((emxArray__common *)b, i54, (int)sizeof(double));
    for (i54 = 0; i54 < ar; i54++) {
      b->data[i54] = input_signals->data[i + input_signals->size[0] * i54];
    }

    if ((B->size[1] == 1) || (b->size[0] == 1)) {
      i54 = e_C->size[0];
      e_C->size[0] = B->size[0];
      emxEnsureCapacity((emxArray__common *)e_C, i54, (int)sizeof(double));
      ar = B->size[0];
      for (i54 = 0; i54 < ar; i54++) {
        e_C->data[i54] = 0.0;
        ib = B->size[1];
        for (ia = 0; ia < ib; ia++) {
          e_C->data[i54] += B->data[i54 + B->size[0] * ia] * b->data[ia];
        }
      }
    } else {
      k = B->size[1];
      A_idx_0 = (unsigned int)B->size[0];
      i54 = e_C->size[0];
      e_C->size[0] = (int)A_idx_0;
      emxEnsureCapacity((emxArray__common *)e_C, i54, (int)sizeof(double));
      m = B->size[0];
      ar = e_C->size[0];
      i54 = e_C->size[0];
      e_C->size[0] = ar;
      emxEnsureCapacity((emxArray__common *)e_C, i54, (int)sizeof(double));
      for (i54 = 0; i54 < ar; i54++) {
        e_C->data[i54] = 0.0;
      }

      if (B->size[0] == 0) {
      } else {
        ar = 0;
        while ((m > 0) && (ar <= 0)) {
          for (ic = 1; ic <= m; ic++) {
            e_C->data[ic - 1] = 0.0;
          }

          ar = m;
        }

        br = 0;
        ar = 0;
        while ((m > 0) && (ar <= 0)) {
          ar = -1;
          i54 = br + k;
          for (ib = br; ib + 1 <= i54; ib++) {
            if (b->data[ib] != 0.0) {
              ia = ar;
              for (ic = 0; ic + 1 <= m; ic++) {
                ia++;
                e_C->data[ic] += b->data[ib] * B->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          ar = m;
        }
      }
    }

    i54 = dx2->size[0];
    dx2->size[0] = d_C->size[0];
    emxEnsureCapacity((emxArray__common *)dx2, i54, (int)sizeof(double));
    ar = d_C->size[0];
    for (i54 = 0; i54 < ar; i54++) {
      dx2->data[i54] = d_C->data[i54] + e_C->data[i54];
    }

    i54 = b->size[0];
    b->size[0] = X0->size[0];
    emxEnsureCapacity((emxArray__common *)b, i54, (int)sizeof(double));
    ar = X0->size[0];
    for (i54 = 0; i54 < ar; i54++) {
      b->data[i54] = X0->data[i54] + 0.5 * dx2->data[i54];
    }

    if ((A->size[1] == 1) || (b->size[0] == 1)) {
      i54 = f_C->size[0];
      f_C->size[0] = A->size[0];
      emxEnsureCapacity((emxArray__common *)f_C, i54, (int)sizeof(double));
      ar = A->size[0];
      for (i54 = 0; i54 < ar; i54++) {
        f_C->data[i54] = 0.0;
        ib = A->size[1];
        for (ia = 0; ia < ib; ia++) {
          f_C->data[i54] += A->data[i54 + A->size[0] * ia] * b->data[ia];
        }
      }
    } else {
      k = A->size[1];
      A_idx_0 = (unsigned int)A->size[0];
      i54 = f_C->size[0];
      f_C->size[0] = (int)A_idx_0;
      emxEnsureCapacity((emxArray__common *)f_C, i54, (int)sizeof(double));
      m = A->size[0];
      ar = f_C->size[0];
      i54 = f_C->size[0];
      f_C->size[0] = ar;
      emxEnsureCapacity((emxArray__common *)f_C, i54, (int)sizeof(double));
      for (i54 = 0; i54 < ar; i54++) {
        f_C->data[i54] = 0.0;
      }

      if (A->size[0] == 0) {
      } else {
        ar = 0;
        while ((m > 0) && (ar <= 0)) {
          for (ic = 1; ic <= m; ic++) {
            f_C->data[ic - 1] = 0.0;
          }

          ar = m;
        }

        br = 0;
        ar = 0;
        while ((m > 0) && (ar <= 0)) {
          ar = -1;
          i54 = br + k;
          for (ib = br; ib + 1 <= i54; ib++) {
            if (b->data[ib] != 0.0) {
              ia = ar;
              for (ic = 0; ic + 1 <= m; ic++) {
                ia++;
                f_C->data[ic] += b->data[ib] * A->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          ar = m;
        }
      }
    }

    ar = input_signals->size[1];
    i54 = b->size[0];
    b->size[0] = ar;
    emxEnsureCapacity((emxArray__common *)b, i54, (int)sizeof(double));
    for (i54 = 0; i54 < ar; i54++) {
      b->data[i54] = input_signals->data[i + input_signals->size[0] * i54];
    }

    if ((B->size[1] == 1) || (b->size[0] == 1)) {
      i54 = g_C->size[0];
      g_C->size[0] = B->size[0];
      emxEnsureCapacity((emxArray__common *)g_C, i54, (int)sizeof(double));
      ar = B->size[0];
      for (i54 = 0; i54 < ar; i54++) {
        g_C->data[i54] = 0.0;
        ib = B->size[1];
        for (ia = 0; ia < ib; ia++) {
          g_C->data[i54] += B->data[i54 + B->size[0] * ia] * b->data[ia];
        }
      }
    } else {
      k = B->size[1];
      A_idx_0 = (unsigned int)B->size[0];
      i54 = g_C->size[0];
      g_C->size[0] = (int)A_idx_0;
      emxEnsureCapacity((emxArray__common *)g_C, i54, (int)sizeof(double));
      m = B->size[0];
      ar = g_C->size[0];
      i54 = g_C->size[0];
      g_C->size[0] = ar;
      emxEnsureCapacity((emxArray__common *)g_C, i54, (int)sizeof(double));
      for (i54 = 0; i54 < ar; i54++) {
        g_C->data[i54] = 0.0;
      }

      if (B->size[0] == 0) {
      } else {
        ar = 0;
        while ((m > 0) && (ar <= 0)) {
          for (ic = 1; ic <= m; ic++) {
            g_C->data[ic - 1] = 0.0;
          }

          ar = m;
        }

        br = 0;
        ar = 0;
        while ((m > 0) && (ar <= 0)) {
          ar = -1;
          i54 = br + k;
          for (ib = br; ib + 1 <= i54; ib++) {
            if (b->data[ib] != 0.0) {
              ia = ar;
              for (ic = 0; ic + 1 <= m; ic++) {
                ia++;
                g_C->data[ic] += b->data[ib] * B->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          ar = m;
        }
      }
    }

    i54 = dx3->size[0];
    dx3->size[0] = f_C->size[0];
    emxEnsureCapacity((emxArray__common *)dx3, i54, (int)sizeof(double));
    ar = f_C->size[0];
    for (i54 = 0; i54 < ar; i54++) {
      dx3->data[i54] = f_C->data[i54] + g_C->data[i54];
    }

    i54 = b->size[0];
    b->size[0] = X0->size[0];
    emxEnsureCapacity((emxArray__common *)b, i54, (int)sizeof(double));
    ar = X0->size[0];
    for (i54 = 0; i54 < ar; i54++) {
      b->data[i54] = X0->data[i54] + dx3->data[i54];
    }

    if ((A->size[1] == 1) || (b->size[0] == 1)) {
      i54 = h_C->size[0];
      h_C->size[0] = A->size[0];
      emxEnsureCapacity((emxArray__common *)h_C, i54, (int)sizeof(double));
      ar = A->size[0];
      for (i54 = 0; i54 < ar; i54++) {
        h_C->data[i54] = 0.0;
        ib = A->size[1];
        for (ia = 0; ia < ib; ia++) {
          h_C->data[i54] += A->data[i54 + A->size[0] * ia] * b->data[ia];
        }
      }
    } else {
      k = A->size[1];
      A_idx_0 = (unsigned int)A->size[0];
      i54 = h_C->size[0];
      h_C->size[0] = (int)A_idx_0;
      emxEnsureCapacity((emxArray__common *)h_C, i54, (int)sizeof(double));
      m = A->size[0];
      ar = h_C->size[0];
      i54 = h_C->size[0];
      h_C->size[0] = ar;
      emxEnsureCapacity((emxArray__common *)h_C, i54, (int)sizeof(double));
      for (i54 = 0; i54 < ar; i54++) {
        h_C->data[i54] = 0.0;
      }

      if (A->size[0] == 0) {
      } else {
        ar = 0;
        while ((m > 0) && (ar <= 0)) {
          for (ic = 1; ic <= m; ic++) {
            h_C->data[ic - 1] = 0.0;
          }

          ar = m;
        }

        br = 0;
        ar = 0;
        while ((m > 0) && (ar <= 0)) {
          ar = -1;
          i54 = br + k;
          for (ib = br; ib + 1 <= i54; ib++) {
            if (b->data[ib] != 0.0) {
              ia = ar;
              for (ic = 0; ic + 1 <= m; ic++) {
                ia++;
                h_C->data[ic] += b->data[ib] * A->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          ar = m;
        }
      }
    }

    ar = input_signals->size[1];
    i54 = b->size[0];
    b->size[0] = ar;
    emxEnsureCapacity((emxArray__common *)b, i54, (int)sizeof(double));
    for (i54 = 0; i54 < ar; i54++) {
      b->data[i54] = input_signals->data[i + input_signals->size[0] * i54];
    }

    if ((B->size[1] == 1) || (b->size[0] == 1)) {
      i54 = i_C->size[0];
      i_C->size[0] = B->size[0];
      emxEnsureCapacity((emxArray__common *)i_C, i54, (int)sizeof(double));
      ar = B->size[0];
      for (i54 = 0; i54 < ar; i54++) {
        i_C->data[i54] = 0.0;
        ib = B->size[1];
        for (ia = 0; ia < ib; ia++) {
          i_C->data[i54] += B->data[i54 + B->size[0] * ia] * b->data[ia];
        }
      }
    } else {
      k = B->size[1];
      A_idx_0 = (unsigned int)B->size[0];
      i54 = i_C->size[0];
      i_C->size[0] = (int)A_idx_0;
      emxEnsureCapacity((emxArray__common *)i_C, i54, (int)sizeof(double));
      m = B->size[0];
      ar = i_C->size[0];
      i54 = i_C->size[0];
      i_C->size[0] = ar;
      emxEnsureCapacity((emxArray__common *)i_C, i54, (int)sizeof(double));
      for (i54 = 0; i54 < ar; i54++) {
        i_C->data[i54] = 0.0;
      }

      if (B->size[0] == 0) {
      } else {
        ar = 0;
        while ((m > 0) && (ar <= 0)) {
          for (ic = 1; ic <= m; ic++) {
            i_C->data[ic - 1] = 0.0;
          }

          ar = m;
        }

        br = 0;
        ar = 0;
        while ((m > 0) && (ar <= 0)) {
          ar = -1;
          i54 = br + k;
          for (ib = br; ib + 1 <= i54; ib++) {
            if (b->data[ib] != 0.0) {
              ia = ar;
              for (ic = 0; ic + 1 <= m; ic++) {
                ia++;
                i_C->data[ic] += b->data[ib] * B->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          ar = m;
        }
      }
    }

    i54 = X0->size[0];
    emxEnsureCapacity((emxArray__common *)X0, i54, (int)sizeof(double));
    ar = X0->size[0];
    for (i54 = 0; i54 < ar; i54++) {
      X0->data[i54] = (X0->data[i54] + 0.33333333333333331 * (dx2->data[i54] +
        dx3->data[i54])) + 0.16666666666666666 * (dx1->data[i54] + (h_C->
        data[i54] + i_C->data[i54]));
    }

    if ((C->size[1] == 1) || (X0->size[0] == 1)) {
      y = 0.0;
      for (i54 = 0; i54 < C->size[1]; i54++) {
        y += C->data[C->size[0] * i54] * X0->data[i54];
      }
    } else {
      y = 0.0;
      for (i54 = 0; i54 < C->size[1]; i54++) {
        y += C->data[C->size[0] * i54] * X0->data[i54];
      }
    }

    output_signal->data[i] = y;

    /* sqr_sum=sqr_sum+(output_signal(i)-real_output(i))^2; */
    i++;
  }

  emxFree_real_T(&b);
  emxFree_real_T(&i_C);
  emxFree_real_T(&h_C);
  emxFree_real_T(&g_C);
  emxFree_real_T(&f_C);
  emxFree_real_T(&e_C);
  emxFree_real_T(&d_C);
  emxFree_real_T(&c_C);
  emxFree_real_T(&b_C);
  emxFree_real_T(&dx3);
  emxFree_real_T(&dx2);
  emxFree_real_T(&dx1);
  emxInit_real_T1(&b_output_signal, 1);
  i54 = b_output_signal->size[0];
  b_output_signal->size[0] = output_signal->size[0];
  emxEnsureCapacity((emxArray__common *)b_output_signal, i54, (int)sizeof(double));
  ar = output_signal->size[0];
  for (i54 = 0; i54 < ar; i54++) {
    b_output_signal->data[i54] = output_signal->data[i54] - real_output->
      data[i54];
  }

  b_power(b_output_signal, output_signal);
  sqr_sum = b_sum(output_signal);

  /* { */
  /* figure(12) */
  /* hold off */
  /* hold on */
  /* plot(output_signal) */
  /* plot(real_output) */
  /* } */
  emxFree_real_T(&b_output_signal);
  emxFree_real_T(&output_signal);
  return sqr_sum;
}

/*
 * Arguments    : const emxArray_real_T *A
 *                const emxArray_real_T *B
 *                const emxArray_real_T *C
 *                emxArray_real_T *X0
 *                const emxArray_real_T *input_signals
 *                const emxArray_real_T *real_output
 * Return Type  : double
 */
double d_FHZN_simulate_lsys_output_com(const emxArray_real_T *A, const
  emxArray_real_T *B, const emxArray_real_T *C, emxArray_real_T *X0, const
  emxArray_real_T *input_signals, const emxArray_real_T *real_output)
{
  double sqr_sum;
  int ar;
  int n;
  emxArray_real_T *output_signal;
  int i55;
  int i;
  emxArray_real_T *dx1;
  emxArray_real_T *dx2;
  emxArray_real_T *dx3;
  emxArray_real_T *b_C;
  emxArray_real_T *c_C;
  emxArray_real_T *d_C;
  emxArray_real_T *e_C;
  emxArray_real_T *f_C;
  emxArray_real_T *g_C;
  emxArray_real_T *h_C;
  emxArray_real_T *i_C;
  emxArray_real_T *b;
  int ib;
  int ia;
  int k;
  unsigned int A_idx_0;
  int m;
  int ic;
  int br;
  double y;
  emxArray_real_T *b_output_signal;
  ar = input_signals->size[0];
  if (ar >= 2) {
  } else {
    ar = 2;
  }

  if (input_signals->size[0] == 0) {
    n = 0;
  } else {
    n = ar;
  }

  emxInit_real_T1(&output_signal, 1);
  i55 = output_signal->size[0];
  output_signal->size[0] = n;
  emxEnsureCapacity((emxArray__common *)output_signal, i55, (int)sizeof(double));
  for (i55 = 0; i55 < n; i55++) {
    output_signal->data[i55] = 0.0;
  }

  ar = input_signals->size[0];
  if (ar >= 2) {
  } else {
    ar = 2;
  }

  if (input_signals->size[0] == 0) {
    n = 0;
  } else {
    n = ar;
  }

  i = 0;
  emxInit_real_T1(&dx1, 1);
  emxInit_real_T1(&dx2, 1);
  emxInit_real_T1(&dx3, 1);
  emxInit_real_T1(&b_C, 1);
  emxInit_real_T1(&c_C, 1);
  emxInit_real_T1(&d_C, 1);
  emxInit_real_T1(&e_C, 1);
  emxInit_real_T1(&f_C, 1);
  emxInit_real_T1(&g_C, 1);
  emxInit_real_T1(&h_C, 1);
  emxInit_real_T1(&i_C, 1);
  emxInit_real_T1(&b, 1);
  while (i <= n - 1) {
    if ((A->size[1] == 1) || (X0->size[0] == 1)) {
      i55 = b_C->size[0];
      b_C->size[0] = A->size[0];
      emxEnsureCapacity((emxArray__common *)b_C, i55, (int)sizeof(double));
      ar = A->size[0];
      for (i55 = 0; i55 < ar; i55++) {
        b_C->data[i55] = 0.0;
        ib = A->size[1];
        for (ia = 0; ia < ib; ia++) {
          b_C->data[i55] += A->data[i55 + A->size[0] * ia] * X0->data[ia];
        }
      }
    } else {
      k = A->size[1];
      A_idx_0 = (unsigned int)A->size[0];
      i55 = b_C->size[0];
      b_C->size[0] = (int)A_idx_0;
      emxEnsureCapacity((emxArray__common *)b_C, i55, (int)sizeof(double));
      m = A->size[0];
      ar = b_C->size[0];
      i55 = b_C->size[0];
      b_C->size[0] = ar;
      emxEnsureCapacity((emxArray__common *)b_C, i55, (int)sizeof(double));
      for (i55 = 0; i55 < ar; i55++) {
        b_C->data[i55] = 0.0;
      }

      if (A->size[0] == 0) {
      } else {
        ar = 0;
        while ((m > 0) && (ar <= 0)) {
          for (ic = 1; ic <= m; ic++) {
            b_C->data[ic - 1] = 0.0;
          }

          ar = m;
        }

        br = 0;
        ar = 0;
        while ((m > 0) && (ar <= 0)) {
          ar = 0;
          i55 = br + k;
          for (ib = br; ib + 1 <= i55; ib++) {
            if (X0->data[ib] != 0.0) {
              ia = ar;
              for (ic = 0; ic + 1 <= m; ic++) {
                ia++;
                b_C->data[ic] += X0->data[ib] * A->data[ia - 1];
              }
            }

            ar += m;
          }

          br += k;
          ar = m;
        }
      }
    }

    A_idx_0 = (unsigned int)B->size[0];
    i55 = c_C->size[0];
    c_C->size[0] = (int)A_idx_0;
    emxEnsureCapacity((emxArray__common *)c_C, i55, (int)sizeof(double));
    m = B->size[0];
    ar = c_C->size[0];
    i55 = c_C->size[0];
    c_C->size[0] = ar;
    emxEnsureCapacity((emxArray__common *)c_C, i55, (int)sizeof(double));
    for (i55 = 0; i55 < ar; i55++) {
      c_C->data[i55] = 0.0;
    }

    if (B->size[0] == 0) {
    } else {
      ar = 0;
      while ((m > 0) && (ar <= 0)) {
        for (ic = 1; ic <= m; ic++) {
          c_C->data[ic - 1] = 0.0;
        }

        ar = m;
      }

      br = 0;
      ar = 0;
      while ((m > 0) && (ar <= 0)) {
        ar = 0;
        for (ib = br; ib + 1 <= br + 2; ib++) {
          if (input_signals->data[i + input_signals->size[0] * ib] != 0.0) {
            ia = ar;
            for (ic = 0; ic + 1 <= m; ic++) {
              ia++;
              c_C->data[ic] += input_signals->data[i + input_signals->size[0] *
                ib] * B->data[ia - 1];
            }
          }

          ar += m;
        }

        br += 2;
        ar = m;
      }
    }

    i55 = dx1->size[0];
    dx1->size[0] = b_C->size[0];
    emxEnsureCapacity((emxArray__common *)dx1, i55, (int)sizeof(double));
    ar = b_C->size[0];
    for (i55 = 0; i55 < ar; i55++) {
      dx1->data[i55] = b_C->data[i55] + c_C->data[i55];
    }

    i55 = b->size[0];
    b->size[0] = X0->size[0];
    emxEnsureCapacity((emxArray__common *)b, i55, (int)sizeof(double));
    ar = X0->size[0];
    for (i55 = 0; i55 < ar; i55++) {
      b->data[i55] = X0->data[i55] + 0.5 * dx1->data[i55];
    }

    if ((A->size[1] == 1) || (b->size[0] == 1)) {
      i55 = d_C->size[0];
      d_C->size[0] = A->size[0];
      emxEnsureCapacity((emxArray__common *)d_C, i55, (int)sizeof(double));
      ar = A->size[0];
      for (i55 = 0; i55 < ar; i55++) {
        d_C->data[i55] = 0.0;
        ib = A->size[1];
        for (ia = 0; ia < ib; ia++) {
          d_C->data[i55] += A->data[i55 + A->size[0] * ia] * b->data[ia];
        }
      }
    } else {
      k = A->size[1];
      A_idx_0 = (unsigned int)A->size[0];
      i55 = d_C->size[0];
      d_C->size[0] = (int)A_idx_0;
      emxEnsureCapacity((emxArray__common *)d_C, i55, (int)sizeof(double));
      m = A->size[0];
      ar = d_C->size[0];
      i55 = d_C->size[0];
      d_C->size[0] = ar;
      emxEnsureCapacity((emxArray__common *)d_C, i55, (int)sizeof(double));
      for (i55 = 0; i55 < ar; i55++) {
        d_C->data[i55] = 0.0;
      }

      if (A->size[0] == 0) {
      } else {
        ar = 0;
        while ((m > 0) && (ar <= 0)) {
          for (ic = 1; ic <= m; ic++) {
            d_C->data[ic - 1] = 0.0;
          }

          ar = m;
        }

        br = 0;
        ar = 0;
        while ((m > 0) && (ar <= 0)) {
          ar = 0;
          i55 = br + k;
          for (ib = br; ib + 1 <= i55; ib++) {
            if (b->data[ib] != 0.0) {
              ia = ar;
              for (ic = 0; ic + 1 <= m; ic++) {
                ia++;
                d_C->data[ic] += b->data[ib] * A->data[ia - 1];
              }
            }

            ar += m;
          }

          br += k;
          ar = m;
        }
      }
    }

    A_idx_0 = (unsigned int)B->size[0];
    i55 = e_C->size[0];
    e_C->size[0] = (int)A_idx_0;
    emxEnsureCapacity((emxArray__common *)e_C, i55, (int)sizeof(double));
    m = B->size[0];
    ar = e_C->size[0];
    i55 = e_C->size[0];
    e_C->size[0] = ar;
    emxEnsureCapacity((emxArray__common *)e_C, i55, (int)sizeof(double));
    for (i55 = 0; i55 < ar; i55++) {
      e_C->data[i55] = 0.0;
    }

    if (B->size[0] == 0) {
    } else {
      ar = 0;
      while ((m > 0) && (ar <= 0)) {
        for (ic = 1; ic <= m; ic++) {
          e_C->data[ic - 1] = 0.0;
        }

        ar = m;
      }

      br = 0;
      ar = 0;
      while ((m > 0) && (ar <= 0)) {
        ar = 0;
        for (ib = br; ib + 1 <= br + 2; ib++) {
          if (input_signals->data[i + input_signals->size[0] * ib] != 0.0) {
            ia = ar;
            for (ic = 0; ic + 1 <= m; ic++) {
              ia++;
              e_C->data[ic] += input_signals->data[i + input_signals->size[0] *
                ib] * B->data[ia - 1];
            }
          }

          ar += m;
        }

        br += 2;
        ar = m;
      }
    }

    i55 = dx2->size[0];
    dx2->size[0] = d_C->size[0];
    emxEnsureCapacity((emxArray__common *)dx2, i55, (int)sizeof(double));
    ar = d_C->size[0];
    for (i55 = 0; i55 < ar; i55++) {
      dx2->data[i55] = d_C->data[i55] + e_C->data[i55];
    }

    i55 = b->size[0];
    b->size[0] = X0->size[0];
    emxEnsureCapacity((emxArray__common *)b, i55, (int)sizeof(double));
    ar = X0->size[0];
    for (i55 = 0; i55 < ar; i55++) {
      b->data[i55] = X0->data[i55] + 0.5 * dx2->data[i55];
    }

    if ((A->size[1] == 1) || (b->size[0] == 1)) {
      i55 = f_C->size[0];
      f_C->size[0] = A->size[0];
      emxEnsureCapacity((emxArray__common *)f_C, i55, (int)sizeof(double));
      ar = A->size[0];
      for (i55 = 0; i55 < ar; i55++) {
        f_C->data[i55] = 0.0;
        ib = A->size[1];
        for (ia = 0; ia < ib; ia++) {
          f_C->data[i55] += A->data[i55 + A->size[0] * ia] * b->data[ia];
        }
      }
    } else {
      k = A->size[1];
      A_idx_0 = (unsigned int)A->size[0];
      i55 = f_C->size[0];
      f_C->size[0] = (int)A_idx_0;
      emxEnsureCapacity((emxArray__common *)f_C, i55, (int)sizeof(double));
      m = A->size[0];
      ar = f_C->size[0];
      i55 = f_C->size[0];
      f_C->size[0] = ar;
      emxEnsureCapacity((emxArray__common *)f_C, i55, (int)sizeof(double));
      for (i55 = 0; i55 < ar; i55++) {
        f_C->data[i55] = 0.0;
      }

      if (A->size[0] == 0) {
      } else {
        ar = 0;
        while ((m > 0) && (ar <= 0)) {
          for (ic = 1; ic <= m; ic++) {
            f_C->data[ic - 1] = 0.0;
          }

          ar = m;
        }

        br = 0;
        ar = 0;
        while ((m > 0) && (ar <= 0)) {
          ar = 0;
          i55 = br + k;
          for (ib = br; ib + 1 <= i55; ib++) {
            if (b->data[ib] != 0.0) {
              ia = ar;
              for (ic = 0; ic + 1 <= m; ic++) {
                ia++;
                f_C->data[ic] += b->data[ib] * A->data[ia - 1];
              }
            }

            ar += m;
          }

          br += k;
          ar = m;
        }
      }
    }

    A_idx_0 = (unsigned int)B->size[0];
    i55 = g_C->size[0];
    g_C->size[0] = (int)A_idx_0;
    emxEnsureCapacity((emxArray__common *)g_C, i55, (int)sizeof(double));
    m = B->size[0];
    ar = g_C->size[0];
    i55 = g_C->size[0];
    g_C->size[0] = ar;
    emxEnsureCapacity((emxArray__common *)g_C, i55, (int)sizeof(double));
    for (i55 = 0; i55 < ar; i55++) {
      g_C->data[i55] = 0.0;
    }

    if (B->size[0] == 0) {
    } else {
      ar = 0;
      while ((m > 0) && (ar <= 0)) {
        for (ic = 1; ic <= m; ic++) {
          g_C->data[ic - 1] = 0.0;
        }

        ar = m;
      }

      br = 0;
      ar = 0;
      while ((m > 0) && (ar <= 0)) {
        ar = 0;
        for (ib = br; ib + 1 <= br + 2; ib++) {
          if (input_signals->data[i + input_signals->size[0] * ib] != 0.0) {
            ia = ar;
            for (ic = 0; ic + 1 <= m; ic++) {
              ia++;
              g_C->data[ic] += input_signals->data[i + input_signals->size[0] *
                ib] * B->data[ia - 1];
            }
          }

          ar += m;
        }

        br += 2;
        ar = m;
      }
    }

    i55 = dx3->size[0];
    dx3->size[0] = f_C->size[0];
    emxEnsureCapacity((emxArray__common *)dx3, i55, (int)sizeof(double));
    ar = f_C->size[0];
    for (i55 = 0; i55 < ar; i55++) {
      dx3->data[i55] = f_C->data[i55] + g_C->data[i55];
    }

    i55 = b->size[0];
    b->size[0] = X0->size[0];
    emxEnsureCapacity((emxArray__common *)b, i55, (int)sizeof(double));
    ar = X0->size[0];
    for (i55 = 0; i55 < ar; i55++) {
      b->data[i55] = X0->data[i55] + dx3->data[i55];
    }

    if ((A->size[1] == 1) || (b->size[0] == 1)) {
      i55 = h_C->size[0];
      h_C->size[0] = A->size[0];
      emxEnsureCapacity((emxArray__common *)h_C, i55, (int)sizeof(double));
      ar = A->size[0];
      for (i55 = 0; i55 < ar; i55++) {
        h_C->data[i55] = 0.0;
        ib = A->size[1];
        for (ia = 0; ia < ib; ia++) {
          h_C->data[i55] += A->data[i55 + A->size[0] * ia] * b->data[ia];
        }
      }
    } else {
      k = A->size[1];
      A_idx_0 = (unsigned int)A->size[0];
      i55 = h_C->size[0];
      h_C->size[0] = (int)A_idx_0;
      emxEnsureCapacity((emxArray__common *)h_C, i55, (int)sizeof(double));
      m = A->size[0];
      ar = h_C->size[0];
      i55 = h_C->size[0];
      h_C->size[0] = ar;
      emxEnsureCapacity((emxArray__common *)h_C, i55, (int)sizeof(double));
      for (i55 = 0; i55 < ar; i55++) {
        h_C->data[i55] = 0.0;
      }

      if (A->size[0] == 0) {
      } else {
        ar = 0;
        while ((m > 0) && (ar <= 0)) {
          for (ic = 1; ic <= m; ic++) {
            h_C->data[ic - 1] = 0.0;
          }

          ar = m;
        }

        br = 0;
        ar = 0;
        while ((m > 0) && (ar <= 0)) {
          ar = 0;
          i55 = br + k;
          for (ib = br; ib + 1 <= i55; ib++) {
            if (b->data[ib] != 0.0) {
              ia = ar;
              for (ic = 0; ic + 1 <= m; ic++) {
                ia++;
                h_C->data[ic] += b->data[ib] * A->data[ia - 1];
              }
            }

            ar += m;
          }

          br += k;
          ar = m;
        }
      }
    }

    A_idx_0 = (unsigned int)B->size[0];
    i55 = i_C->size[0];
    i_C->size[0] = (int)A_idx_0;
    emxEnsureCapacity((emxArray__common *)i_C, i55, (int)sizeof(double));
    m = B->size[0];
    ar = i_C->size[0];
    i55 = i_C->size[0];
    i_C->size[0] = ar;
    emxEnsureCapacity((emxArray__common *)i_C, i55, (int)sizeof(double));
    for (i55 = 0; i55 < ar; i55++) {
      i_C->data[i55] = 0.0;
    }

    if (B->size[0] == 0) {
    } else {
      ar = 0;
      while ((m > 0) && (ar <= 0)) {
        for (ic = 1; ic <= m; ic++) {
          i_C->data[ic - 1] = 0.0;
        }

        ar = m;
      }

      br = 0;
      ar = 0;
      while ((m > 0) && (ar <= 0)) {
        ar = 0;
        for (ib = br; ib + 1 <= br + 2; ib++) {
          if (input_signals->data[i + input_signals->size[0] * ib] != 0.0) {
            ia = ar;
            for (ic = 0; ic + 1 <= m; ic++) {
              ia++;
              i_C->data[ic] += input_signals->data[i + input_signals->size[0] *
                ib] * B->data[ia - 1];
            }
          }

          ar += m;
        }

        br += 2;
        ar = m;
      }
    }

    i55 = X0->size[0];
    emxEnsureCapacity((emxArray__common *)X0, i55, (int)sizeof(double));
    ar = X0->size[0];
    for (i55 = 0; i55 < ar; i55++) {
      X0->data[i55] = (X0->data[i55] + 0.33333333333333331 * (dx2->data[i55] +
        dx3->data[i55])) + 0.16666666666666666 * (dx1->data[i55] + (h_C->
        data[i55] + i_C->data[i55]));
    }

    if ((C->size[1] == 1) || (X0->size[0] == 1)) {
      y = 0.0;
      for (i55 = 0; i55 < C->size[1]; i55++) {
        y += C->data[C->size[0] * i55] * X0->data[i55];
      }
    } else {
      y = 0.0;
      for (i55 = 0; i55 < C->size[1]; i55++) {
        y += C->data[C->size[0] * i55] * X0->data[i55];
      }
    }

    output_signal->data[i] = y;

    /* sqr_sum=sqr_sum+(output_signal(i)-real_output(i))^2; */
    i++;
  }

  emxFree_real_T(&b);
  emxFree_real_T(&i_C);
  emxFree_real_T(&h_C);
  emxFree_real_T(&g_C);
  emxFree_real_T(&f_C);
  emxFree_real_T(&e_C);
  emxFree_real_T(&d_C);
  emxFree_real_T(&c_C);
  emxFree_real_T(&b_C);
  emxFree_real_T(&dx3);
  emxFree_real_T(&dx2);
  emxFree_real_T(&dx1);
  emxInit_real_T1(&b_output_signal, 1);
  i55 = b_output_signal->size[0];
  b_output_signal->size[0] = output_signal->size[0];
  emxEnsureCapacity((emxArray__common *)b_output_signal, i55, (int)sizeof(double));
  ar = output_signal->size[0];
  for (i55 = 0; i55 < ar; i55++) {
    b_output_signal->data[i55] = output_signal->data[i55] - real_output->
      data[i55];
  }

  b_power(b_output_signal, output_signal);
  sqr_sum = b_sum(output_signal);

  /* { */
  /* figure(12) */
  /* hold off */
  /* hold on */
  /* plot(output_signal) */
  /* plot(real_output) */
  /* } */
  emxFree_real_T(&b_output_signal);
  emxFree_real_T(&output_signal);
  return sqr_sum;
}

/*
 * File trailer for FHZN_simulate_lsys_output_compare.c
 *
 * [EOF]
 */
