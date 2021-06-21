/*
 * File: FHZN_get_MISO_model.c
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
#include "FHZN_get_MISO_model.h"
#include "FHZN_define_model_del_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *ni_min
 *                double inputs_nr
 *                double n
 *                double m
 *                emxArray_real_T *A
 *                emxArray_real_T *B
 *                emxArray_real_T *C
 *                emxArray_real_T *D
 * Return Type  : void
 */
void FHZN_get_MISO_model(const emxArray_real_T *ni_min, double inputs_nr, double
  n, double m, emxArray_real_T *A, emxArray_real_T *B, emxArray_real_T *C,
  emxArray_real_T *D)
{
  int i7;
  int loop_ub;
  int i;
  int j;
  double k;
  double b_A;
  i7 = A->size[0] * A->size[1];
  A->size[0] = (int)(m - 1.0);
  A->size[1] = (int)(m - 1.0);
  emxEnsureCapacity((emxArray__common *)A, i7, (int)sizeof(double));
  loop_ub = (int)(m - 1.0) * (int)(m - 1.0);
  for (i7 = 0; i7 < loop_ub; i7++) {
    A->data[i7] = 0.0;
  }

  /* disp('Budowa A'); */
  for (i = 0; i < (int)(m - 1.0); i++) {
    for (j = 0; j < (int)(m - 1.0); j++) {
      if (1.0 + (double)i == m - 1.0) {
        A->data[j + A->size[0] * i] = -ni_min->data[j] / ni_min->data[(int)m - 1];
      } else {
        A->data[j + A->size[0] * i] = (1.0 + (double)j == (1.0 + (double)i) +
          1.0);
      }
    }
  }

  /* disp('Budowa B'); */
  i7 = B->size[0] * B->size[1];
  B->size[0] = (int)(m - 1.0);
  B->size[1] = (int)inputs_nr;
  emxEnsureCapacity((emxArray__common *)B, i7, (int)sizeof(double));
  loop_ub = (int)(m - 1.0) * (int)inputs_nr;
  for (i7 = 0; i7 < loop_ub; i7++) {
    B->data[i7] = 0.0;
  }

  k = 1.0;
  for (i = 0; i < (int)inputs_nr; i++) {
    for (j = 0; j < (int)n; j++) {
      b_A = -ni_min->data[(int)(m + k) - 1];
      B->data[j + B->size[0] * i] = b_A / ni_min->data[(int)m - 1];
      k++;
    }
  }

  i7 = C->size[0] * C->size[1];
  C->size[0] = 1;
  C->size[1] = (int)(m - 1.0);
  emxEnsureCapacity((emxArray__common *)C, i7, (int)sizeof(double));
  loop_ub = (int)(m - 1.0);
  for (i7 = 0; i7 < loop_ub; i7++) {
    C->data[i7] = 0.0;
  }

  /* disp('Budowa C'); */
  for (i = 0; i < (int)(m - 1.0); i++) {
    C->data[C->size[0] * i] = (1.0 + (double)i == m - 1.0);
  }

  /* disp('Budowa D'); */
  i7 = D->size[0] * D->size[1];
  D->size[0] = (int)(m - 1.0);
  D->size[1] = (int)inputs_nr;
  emxEnsureCapacity((emxArray__common *)D, i7, (int)sizeof(double));
  loop_ub = (int)(m - 1.0) * (int)inputs_nr;
  for (i7 = 0; i7 < loop_ub; i7++) {
    D->data[i7] = 0.0;
  }
}

/*
 * Arguments    : const emxArray_real_T *ni_min
 *                double n
 *                double m
 *                emxArray_real_T *A
 *                emxArray_real_T *B
 *                emxArray_real_T *C
 *                emxArray_real_T *D
 * Return Type  : void
 */
void b_FHZN_get_MISO_model(const emxArray_real_T *ni_min, double n, double m,
  emxArray_real_T *A, emxArray_real_T *B, emxArray_real_T *C, emxArray_real_T *D)
{
  int i22;
  int loop_ub;
  int i;
  int j;
  double k;
  double b_A;
  i22 = A->size[0] * A->size[1];
  A->size[0] = (int)(m - 1.0);
  A->size[1] = (int)(m - 1.0);
  emxEnsureCapacity((emxArray__common *)A, i22, (int)sizeof(double));
  loop_ub = (int)(m - 1.0) * (int)(m - 1.0);
  for (i22 = 0; i22 < loop_ub; i22++) {
    A->data[i22] = 0.0;
  }

  /* disp('Budowa A'); */
  for (i = 0; i < (int)(m - 1.0); i++) {
    for (j = 0; j < (int)(m - 1.0); j++) {
      if (1.0 + (double)i == m - 1.0) {
        A->data[j + A->size[0] * i] = -ni_min->data[j] / ni_min->data[(int)m - 1];
      } else {
        A->data[j + A->size[0] * i] = (1.0 + (double)j == (1.0 + (double)i) +
          1.0);
      }
    }
  }

  /* disp('Budowa B'); */
  i22 = B->size[0] * B->size[1];
  B->size[0] = (int)(m - 1.0);
  B->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)B, i22, (int)sizeof(double));
  loop_ub = (int)(m - 1.0) << 1;
  for (i22 = 0; i22 < loop_ub; i22++) {
    B->data[i22] = 0.0;
  }

  k = 1.0;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < (int)n; j++) {
      b_A = -ni_min->data[(int)(m + k) - 1];
      B->data[j + B->size[0] * i] = b_A / ni_min->data[(int)m - 1];
      k++;
    }
  }

  i22 = C->size[0] * C->size[1];
  C->size[0] = 1;
  C->size[1] = (int)(m - 1.0);
  emxEnsureCapacity((emxArray__common *)C, i22, (int)sizeof(double));
  loop_ub = (int)(m - 1.0);
  for (i22 = 0; i22 < loop_ub; i22++) {
    C->data[i22] = 0.0;
  }

  /* disp('Budowa C'); */
  for (i = 0; i < (int)(m - 1.0); i++) {
    C->data[C->size[0] * i] = (1.0 + (double)i == m - 1.0);
  }

  /* disp('Budowa D'); */
  i22 = D->size[0] * D->size[1];
  D->size[0] = (int)(m - 1.0);
  D->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)D, i22, (int)sizeof(double));
  loop_ub = (int)(m - 1.0) << 1;
  for (i22 = 0; i22 < loop_ub; i22++) {
    D->data[i22] = 0.0;
  }
}

/*
 * File trailer for FHZN_get_MISO_model.c
 *
 * [EOF]
 */
