/*
 * File: FHZN_obtain_MPC_model_FF.c
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
#include "lagc.h"
#include "Mucon.h"
#include "sum.h"
#include "cmpc_2.h"
#include "eye.h"
#include "FHZN_get_MISO_model.h"

/* Function Definitions */

/*
 * Arguments    : const double inputs[3]
 *                emxArray_real_T *params_vector
 *                double n
 *                double m
 *                double N_
 *                double p_
 *                double Tp
 *                double h
 *                emxArray_real_T *Omega
 *                emxArray_real_T *Psi
 *                emxArray_real_T *Gamma
 *                emxArray_real_T *A
 *                emxArray_real_T *B
 *                emxArray_real_T *Bd
 *                emxArray_real_T *C
 *                emxArray_real_T *Q
 *                emxArray_real_T *R
 *                emxArray_real_T *Ap
 *                emxArray_real_T *Lzerot
 *                emxArray_real_T *M
 * Return Type  : void
 */
void FHZN_obtain_MPC_model_FF(const double inputs[3], emxArray_real_T
  *params_vector, double n, double m, double N_, double p_, double Tp, double h,
  emxArray_real_T *Omega, emxArray_real_T *Psi, emxArray_real_T *Gamma,
  emxArray_real_T *A, emxArray_real_T *B, emxArray_real_T *Bd, emxArray_real_T
  *C, emxArray_real_T *Q, emxArray_real_T *R, emxArray_real_T *Ap,
  emxArray_real_T *Lzerot, emxArray_real_T *M)
{
  boolean_T without_ff;
  int start_model_nr;
  double inputs_nr;
  int k;
  double d13;
  int loop_ub;
  emxArray_real_T *b_params_vector;
  int i26;
  emxArray_real_T *Cc;
  emxArray_real_T *Ac;
  emxArray_real_T *Bc;
  emxArray_real_T *unusedU1;
  unsigned int uv2[2];
  int i27;
  int n_in;
  int i28;
  int i29;
  emxArray_real_T *N;
  emxArray_real_T *L0;
  double cc;
  int k0;
  emxArray_int32_T *r18;
  without_ff = false;
  if (inputs[0] == 0.0) {
    start_model_nr = 1;
    without_ff = true;
  } else {
    start_model_nr = 2;
  }

  inputs_nr = inputs[0];
  for (k = 0; k < 2; k++) {
    inputs_nr += inputs[k + 1];
  }

  /* for i=1:inputs_nr */
  /*    current_inputs=current_inputs+1; */
  /* end */
  d13 = m + inputs_nr * n;
  if (1.0 > d13) {
    loop_ub = 0;
  } else {
    loop_ub = (int)d13;
  }

  emxInit_real_T1(&b_params_vector, 1);
  i26 = b_params_vector->size[0];
  b_params_vector->size[0] = loop_ub;
  emxEnsureCapacity((emxArray__common *)b_params_vector, i26, (int)sizeof(double));
  for (i26 = 0; i26 < loop_ub; i26++) {
    b_params_vector->data[i26] = params_vector->data[i26];
  }

  i26 = params_vector->size[0];
  params_vector->size[0] = b_params_vector->size[0];
  emxEnsureCapacity((emxArray__common *)params_vector, i26, (int)sizeof(double));
  loop_ub = b_params_vector->size[0];
  for (i26 = 0; i26 < loop_ub; i26++) {
    params_vector->data[i26] = b_params_vector->data[i26];
  }

  emxFree_real_T(&b_params_vector);
  emxInit_real_T(&Cc, 2);
  emxInit_real_T(&Ac, 2);
  emxInit_real_T(&Bc, 2);
  emxInit_real_T(&unusedU1, 2);
  FHZN_get_MISO_model(params_vector, inputs_nr, n, m, Ac, Bc, Cc, unusedU1);
  i26 = Cc->size[0] * Cc->size[1];
  Cc->size[0] = 1;
  Cc->size[1] = Ac->size[0];
  emxEnsureCapacity((emxArray__common *)Cc, i26, (int)sizeof(double));
  loop_ub = Ac->size[0];
  for (i26 = 0; i26 < loop_ub; i26++) {
    Cc->data[i26] = 0.0;
  }

  Cc->data[Cc->size[0] * (Ac->size[0] - 1)] = 1.0;

  /* n=rank(Ac); */
  /* X0=[zeros(n,1); obj.signals_intervals(end).original_signals(3,end)-... */
  /*     obj.ident_models(obj.current_model_nr).offset_value(end)]; */
  /* obj.MPC_model.X0=X0; */
  if (start_model_nr > 1) {
    k = Cc->size[1] + 1;
    i26 = Bd->size[0] * Bd->size[1];
    Bd->size[0] = k;
    Bd->size[1] = 1;
    emxEnsureCapacity((emxArray__common *)Bd, i26, (int)sizeof(double));
    k = Cc->size[1] + 1;
    for (i26 = 0; i26 < k; i26++) {
      Bd->data[i26] = 0.0;
    }

    loop_ub = Bc->size[0] - 1;
    for (i26 = 0; i26 <= loop_ub; i26++) {
      Bd->data[i26] = Bc->data[i26];
    }
  } else {
    for (i26 = 0; i26 < 2; i26++) {
      uv2[i26] = (unsigned int)Bc->size[i26];
    }

    i26 = Bd->size[0] * Bd->size[1];
    Bd->size[0] = (int)uv2[0];
    Bd->size[1] = (int)uv2[1];
    emxEnsureCapacity((emxArray__common *)Bd, i26, (int)sizeof(double));
    loop_ub = (int)uv2[0] * (int)uv2[1];
    for (i26 = 0; i26 < loop_ub; i26++) {
      Bd->data[i26] = 0.0;
    }
  }

  if (start_model_nr > Bc->size[1]) {
    i26 = 1;
    i27 = 1;
  } else {
    i26 = start_model_nr;
    i27 = Bc->size[1] + 1;
  }

  n_in = (i27 - i26) - 1;

  /* m1=1; */
  i28 = Bc->size[0];
  i29 = Bc->size[0];
  k = A->size[0] * A->size[1];
  A->size[0] = i28 + 1;
  A->size[1] = i29 + 1;
  emxEnsureCapacity((emxArray__common *)A, k, (int)sizeof(double));
  loop_ub = (i28 + 1) * (i29 + 1);
  for (i28 = 0; i28 < loop_ub; i28++) {
    A->data[i28] = 0.0;
  }

  loop_ub = Ac->size[1];
  for (i28 = 0; i28 < loop_ub; i28++) {
    k = Ac->size[0];
    for (i29 = 0; i29 < k; i29++) {
      A->data[i29 + A->size[0] * i28] = Ac->data[i29 + Ac->size[0] * i28];
    }
  }

  i28 = Bc->size[0];
  loop_ub = Cc->size[1];
  for (i29 = 0; i29 < loop_ub; i29++) {
    A->data[i28 + A->size[0] * i29] = Cc->data[Cc->size[0] * i29];
  }

  i28 = Bc->size[0];
  i29 = B->size[0] * B->size[1];
  B->size[0] = i28 + 1;
  B->size[1] = i27 - i26;
  emxEnsureCapacity((emxArray__common *)B, i29, (int)sizeof(double));
  loop_ub = (i28 + 1) * (i27 - i26);
  for (i28 = 0; i28 < loop_ub; i28++) {
    B->data[i28] = 0.0;
  }

  loop_ub = Bc->size[0] - 1;
  k = i27 - i26;
  for (i28 = 0; i28 < k; i28++) {
    for (i29 = 0; i29 <= loop_ub; i29++) {
      B->data[i29 + B->size[0] * i28] = Bc->data[i29 + Bc->size[0] * ((i26 + i28)
        - 1)];
    }
  }

  i28 = Bc->size[0];
  i29 = C->size[0] * C->size[1];
  C->size[0] = 1;
  C->size[1] = i28 + 1;
  emxEnsureCapacity((emxArray__common *)C, i29, (int)sizeof(double));
  loop_ub = i28 + 1;
  for (i28 = 0; i28 < loop_ub; i28++) {
    C->data[i28] = 0.0;
  }

  i28 = Bc->size[0];
  C->data[C->size[0] * i28] = 1.0;
  i28 = Q->size[0] * Q->size[1];
  Q->size[0] = C->size[1];
  Q->size[1] = C->size[1];
  emxEnsureCapacity((emxArray__common *)Q, i28, (int)sizeof(double));
  loop_ub = C->size[1];
  emxFree_real_T(&Bc);
  for (i28 = 0; i28 < loop_ub; i28++) {
    k = C->size[1];
    for (i29 = 0; i29 < k; i29++) {
      Q->data[i28 + Q->size[0] * i29] = C->data[C->size[0] * i28] * C->data
        [C->size[0] * i29];
    }
  }

  /* K_ob=lqr(A',C',Q,R); */
  eye(B->size[1], B->size[1], R);
  i28 = Cc->size[0] * Cc->size[1];
  Cc->size[0] = 1;
  Cc->size[1] = B->size[1];
  emxEnsureCapacity((emxArray__common *)Cc, i28, (int)sizeof(double));
  loop_ub = B->size[1];
  for (i28 = 0; i28 < loop_ub; i28++) {
    Cc->data[i28] = p_;
  }

  emxInit_real_T(&N, 2);

  /*  0.6 */
  i28 = N->size[0] * N->size[1];
  N->size[0] = 1;
  N->size[1] = B->size[1];
  emxEnsureCapacity((emxArray__common *)N, i28, (int)sizeof(double));
  loop_ub = B->size[1];
  for (i28 = 0; i28 < loop_ub; i28++) {
    N->data[i28] = N_;
  }

  emxInit_real_T1(&L0, 1);

  /* bylo 3 */
  /* Tp=150;     %100  250  150 */
  /* obj.MPC_model.A=A; */
  /* obj.MPC_model.B=B; */
  /* obj.MPC_model.Bd=Bd; */
  /* obj.MPC_model.C=C; */
  /* obj.MPC_model.K_ob=K_ob'; */
  /* obj.MPC_model.Q=Q; */
  /* obj.MPC_model.R=R; */
  /* [obj.MPC_model.Omega,obj.MPC_model.Psi,obj.MPC_model.Gamma,obj.MPC_model.Eae,obj.MPC_model.Ap,obj.MPC_model.phi,obj.MPC_model.phi_d,obj.MPC_model.tau]=cmpc_2(A,B,Bd,p,N,Tp,Q,R); */
  cmpc_2(A, B, Bd, Cc, N, Tp, Q, R, without_ff, Omega, Psi, Gamma, Ap);

  /* obj.MPC_model.ctrl_offset=obj.ident_models(obj.current_model_nr).offset_value(start_model_nr:start_model_nr+size(B,2)-1); */
  /* obj.MPC_model.output_offset=obj.ident_models(obj.current_model_nr).offset_value(end); */
  /* obj.MPC_model.control_signals=obj.ident_models(obj.current_model_nr).inputs_to_ident(2:end); */
  /*  zerowa probka */
  lagc(Cc->data[0], N->data[0], unusedU1, L0);
  i28 = Lzerot->size[0] * Lzerot->size[1];
  Lzerot->size[0] = i27 - i26;
  Lzerot->size[1] = (int)c_sum(N);
  emxEnsureCapacity((emxArray__common *)Lzerot, i28, (int)sizeof(double));
  d13 = c_sum(N);
  loop_ub = (i27 - i26) * (int)d13;
  for (i28 = 0; i28 < loop_ub; i28++) {
    Lzerot->data[i28] = 0.0;
  }

  loop_ub = L0->size[0];
  for (i28 = 0; i28 < loop_ub; i28++) {
    Lzerot->data[Lzerot->size[0] * i28] = L0->data[i28];
  }

  /*  gdy wiecej kolumn w macierzy B */
  cc = N->data[0];
  k0 = 1;
  emxInit_int32_T1(&r18, 1);
  while (k0 - 1 <= n_in - 1) {
    lagc(Cc->data[k0], N->data[k0], unusedU1, L0);
    d13 = N->data[k0];
    i28 = r18->size[0];
    r18->size[0] = (int)floor(d13 - 1.0) + 1;
    emxEnsureCapacity((emxArray__common *)r18, i28, (int)sizeof(int));
    loop_ub = (int)floor(d13 - 1.0);
    for (i28 = 0; i28 <= loop_ub; i28++) {
      r18->data[i28] = (int)(cc + (1.0 + (double)i28)) - 1;
    }

    loop_ub = L0->size[0];
    for (i28 = 0; i28 < loop_ub; i28++) {
      Lzerot->data[k0 + Lzerot->size[0] * r18->data[i28]] = L0->data[i28];
    }

    cc += N->data[k0];
    k0++;
  }

  emxFree_int32_T(&r18);
  emxFree_real_T(&L0);

  /*  for constraints */
  Mucon(Cc, N, i27 - i26, h, Ac, unusedU1);
  i26 = M->size[0] * M->size[1];
  M->size[0] = ((Ac->size[0] + Ac->size[0]) + Lzerot->size[0]) + Lzerot->size[0];
  M->size[1] = Ac->size[1];
  emxEnsureCapacity((emxArray__common *)M, i26, (int)sizeof(double));
  loop_ub = Ac->size[1];
  emxFree_real_T(&unusedU1);
  emxFree_real_T(&N);
  emxFree_real_T(&Cc);
  for (i26 = 0; i26 < loop_ub; i26++) {
    k = Ac->size[0];
    for (i27 = 0; i27 < k; i27++) {
      M->data[i27 + M->size[0] * i26] = Ac->data[i27 + Ac->size[0] * i26];
    }
  }

  loop_ub = Ac->size[1];
  for (i26 = 0; i26 < loop_ub; i26++) {
    k = Ac->size[0];
    for (i27 = 0; i27 < k; i27++) {
      M->data[(i27 + Ac->size[0]) + M->size[0] * i26] = -Ac->data[i27 + Ac->
        size[0] * i26];
    }
  }

  loop_ub = Lzerot->size[1];
  for (i26 = 0; i26 < loop_ub; i26++) {
    k = Lzerot->size[0];
    for (i27 = 0; i27 < k; i27++) {
      M->data[((i27 + Ac->size[0]) + Ac->size[0]) + M->size[0] * i26] =
        Lzerot->data[i27 + Lzerot->size[0] * i26];
    }
  }

  loop_ub = Lzerot->size[1];
  for (i26 = 0; i26 < loop_ub; i26++) {
    k = Lzerot->size[0];
    for (i27 = 0; i27 < k; i27++) {
      M->data[(((i27 + Ac->size[0]) + Ac->size[0]) + Lzerot->size[0]) + M->size
        [0] * i26] = -Lzerot->data[i27 + Lzerot->size[0] * i26];
    }
  }

  emxFree_real_T(&Ac);
}

/*
 * File trailer for FHZN_obtain_MPC_model_FF.c
 *
 * [EOF]
 */
