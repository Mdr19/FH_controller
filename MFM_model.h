#pragma once

#define MFM_models_nr 5

typedef struct MFM_model MFM_model;

struct MFM_model
{
	unsigned int N;
	unsigned int M;
	unsigned int n;
	unsigned int m;
	unsigned int h;
	//double* params_vector;
};

MFM_model* init_MFM_models_Z3(void);
MFM_model* init_MFM_models_Z4(void);
