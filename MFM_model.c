#include "MFM_model.h"

MFM_model MFM_models[MFM_models_nr];

MFM_model* init_MFM_models_Z3(void)
{
	MFM_models[0].N = 5;
	MFM_models[0].M = 6;
	MFM_models[0].n = 1;
	MFM_models[0].m = 4;
	MFM_models[0].h = 150;

	MFM_models[1].N = 5;
	MFM_models[1].M = 6;
	MFM_models[1].n = 1;
	MFM_models[1].m = 4;
	MFM_models[1].h = 100;

	MFM_models[2].N = 3;
	MFM_models[2].M = 4;
	MFM_models[2].n = 1;
	MFM_models[2].m = 3;
	MFM_models[2].h = 100;

	MFM_models[3].N = 3;
	MFM_models[3].M = 4;
	MFM_models[3].n = 1;
	MFM_models[3].m = 3;
	MFM_models[3].h = 150;

	MFM_models[4].N = 3;
	MFM_models[4].M = 4;
	MFM_models[4].n = 1;
	MFM_models[4].m = 3;
	MFM_models[4].h = 200;

	return &MFM_models;
}

MFM_model* init_MFM_models_Z4(void)
{
	MFM_models[0].N = 5;
	MFM_models[0].M = 6;
	MFM_models[0].n = 1;
	MFM_models[0].m = 4;
	MFM_models[0].h = 150;

	MFM_models[1].N = 5;
	MFM_models[1].M = 6;
	MFM_models[1].n = 1;
	MFM_models[1].m = 4;
	MFM_models[1].h = 100;

	MFM_models[2].N = 3;
	MFM_models[2].M = 4;
	MFM_models[2].n = 1;
	MFM_models[2].m = 3;
	MFM_models[2].h = 100;

	MFM_models[3].N = 3;
	MFM_models[3].M = 4;
	MFM_models[3].n = 1;
	MFM_models[3].m = 3;
	MFM_models[3].h = 150;

	MFM_models[4].N = 3;
	MFM_models[4].M = 4;
	MFM_models[4].n = 1;
	MFM_models[4].m = 3;
	MFM_models[4].h = 50;

	return &MFM_models;
}
