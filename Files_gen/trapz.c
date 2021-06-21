/*
 * File: trapz.c
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
#include "trapz.h"
#include "FHZN_define_model_del_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 *                const emxArray_real_T *y
 *                emxArray_real_T *z
 * Return Type  : void
 */
void b_trapz(const emxArray_real_T *x, const emxArray_real_T *y, emxArray_real_T
             *z)
{
  emxArray_real_T *b_x;
  int k;
  int iystart;
  int vlen;
  int i;
  int iy;
  int iz;
  double s;
  int ix;
  double ylast;
  emxInit_real_T(&b_x, 2);
  k = b_x->size[0] * b_x->size[1];
  b_x->size[0] = 1;
  b_x->size[1] = x->size[1];
  emxEnsureCapacity((emxArray__common *)b_x, k, (int)sizeof(double));
  iystart = x->size[0] * x->size[1];
  for (k = 0; k < iystart; k++) {
    b_x->data[k] = x->data[k];
  }

  vlen = y->size[0] - 1;
  for (i = 1; i <= vlen; i++) {
    b_x->data[i - 1] = b_x->data[i] - b_x->data[i - 1];
  }

  k = z->size[0] * z->size[1];
  z->size[0] = 1;
  z->size[1] = y->size[1];
  emxEnsureCapacity((emxArray__common *)z, k, (int)sizeof(double));
  if ((y->size[0] == 0) || (y->size[1] == 0)) {
    k = z->size[0] * z->size[1];
    z->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)z, k, (int)sizeof(double));
    iystart = z->size[1];
    for (k = 0; k < iystart; k++) {
      z->data[z->size[0] * k] = 0.0;
    }
  } else {
    iy = -1;
    iz = -1;
    for (i = 1; i <= y->size[1]; i++) {
      iystart = iy + 1;
      s = 0.0;
      ix = -1;
      iy++;
      ylast = y->data[iystart];
      for (k = 0; k < vlen; k++) {
        iy++;
        if (b_x->size[1] == 0) {
          s += (ylast + y->data[iy]) / 2.0;
        } else {
          ix++;
          s += b_x->data[ix] * ((ylast + y->data[iy]) / 2.0);
        }

        ylast = y->data[iy];
      }

      iz++;
      z->data[iz] = s;
    }
  }

  emxFree_real_T(&b_x);
}

/*
 * Arguments    : const emxArray_real_T *x
 *                const emxArray_real_T *y
 *                emxArray_real_T *z
 * Return Type  : void
 */
void trapz(const emxArray_real_T *x, const emxArray_real_T *y, emxArray_real_T
           *z)
{
  emxArray_real_T *b_x;
  int iy;
  int iystart;
  int vlen;
  int i;
  unsigned int sz[3];
  int k;
  int npages;
  int iz;
  double s;
  int ix;
  double ylast;
  emxInit_real_T(&b_x, 2);
  iy = b_x->size[0] * b_x->size[1];
  b_x->size[0] = 1;
  b_x->size[1] = x->size[1];
  emxEnsureCapacity((emxArray__common *)b_x, iy, (int)sizeof(double));
  iystart = x->size[0] * x->size[1];
  for (iy = 0; iy < iystart; iy++) {
    b_x->data[iy] = x->data[iy];
  }

  vlen = y->size[0] - 1;
  for (i = 1; i <= vlen; i++) {
    b_x->data[i - 1] = b_x->data[i] - b_x->data[i - 1];
  }

  for (iy = 0; iy < 3; iy++) {
    sz[iy] = (unsigned int)y->size[iy];
  }

  iy = z->size[0] * z->size[1] * z->size[2];
  z->size[0] = 1;
  z->size[1] = (int)sz[1];
  z->size[2] = (int)sz[2];
  emxEnsureCapacity((emxArray__common *)z, iy, (int)sizeof(double));
  if ((y->size[0] == 0) || (y->size[1] == 0) || (y->size[2] == 0)) {
    iy = z->size[0] * z->size[1] * z->size[2];
    z->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)z, iy, (int)sizeof(double));
    iystart = z->size[2];
    for (iy = 0; iy < iystart; iy++) {
      i = z->size[1];
      for (k = 0; k < i; k++) {
        z->data[z->size[0] * k + z->size[0] * z->size[1] * iy] = 0.0;
      }
    }
  } else {
    npages = 1;
    k = 3;
    while ((k > 2) && (y->size[2] == 1)) {
      k = 2;
    }

    for (iystart = 2; iystart <= k; iystart++) {
      npages *= y->size[iystart - 1];
    }

    iy = -1;
    iz = -1;
    for (i = 1; i <= npages; i++) {
      iystart = iy + 1;
      s = 0.0;
      ix = -1;
      iy++;
      ylast = y->data[iystart];
      for (k = 0; k < vlen; k++) {
        iy++;
        if (b_x->size[1] == 0) {
          s += (ylast + y->data[iy]) / 2.0;
        } else {
          ix++;
          s += b_x->data[ix] * ((ylast + y->data[iy]) / 2.0);
        }

        ylast = y->data[iy];
      }

      iz++;
      z->data[iz] = s;
    }
  }

  emxFree_real_T(&b_x);
}

/*
 * File trailer for trapz.c
 *
 * [EOF]
 */
