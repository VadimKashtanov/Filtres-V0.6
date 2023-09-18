#include "mdl.h"

float fltr_prix_f(float * x, float * filtre, uint n) {
	float _min=x[0], _max=x[0];
	float _x;
	for (uint i=1; i < n; i++) {
		_x = x[i];
		if (_x > _max) _max = _x;
		if (_x < _min) _min = _x;
	}
	if (_min == _max) {
		_min=0;_max=1;
		for (uint i=0; i < n; i++) x[i]=0.5;
		//ERR("Impossible de normaliser un vecteur uniforme");
	}

	//raise(SIGINT);

	//
	float x_norm[n];

	//
	float _s = 0;
	const float d = _max-_min;
	float tmp, signe;
	for (uint i=0; i < n; i++) {
		x_norm[i] = (x[i]-_min)/d;
	//	printf("%f, ", x_norm[i]);
		_s += sqrtf(1.0f+fabs(x_norm[i] - filtre[i]));
	}
	//printf("\n");
	_s = _s/n - 1;

	//
	float _d = 0.0;
	for (int i=0; i < n-1; i++) {
		_d += powf(1.0f + fabs((x_norm[i+1]-x_norm[i]) - (filtre[i+1]-filtre[i])),2);
	}
	_d = _d/(n-1) - 1;

	//
	return 2*___exp(-_s*_s - _d*_d) - 1.0;	//[0;1] -> [-1;+1]
};

void fltr_prix_plume_constes(Mdl_t * mdl) {
	uint i = 0;	//c==0 car que cette couche peut avoire filtre prixs
	ptr("FLTR_PRIXS #%i\n", i);
	if (mdl->type[i] == 0) {
		uint constantes = constes_FLTR(mdl->n[i]);
		FOR(0, j, mdl->y[i]) {
			ptr(" .y%i:\n", j);
			FOR(0, k, constantes) {
				ptr("%3.i| %f ",
				mdl->conste_depart[i] + j*constantes + k,
				mdl->conste[mdl->conste_depart[i] + j*constantes + k]);
				//
				FOR(0, l, 1+(uint)roundf(mdl->conste[mdl->conste_depart[i] + j*constantes + k]*10)) {
					ptr("\033[105m_\033[0m");
				};
				ptr("\n");
			}
		}
	}
};

void fltr_prix_plume_config(Mdl_t * mdl, uint c) {
	printf("#%3.i FLTR_PRIXS n=%i:\n", c, mdl->n[c]);
	for (uint j=0; j < mdl->y[c]; j++) {
		printf("%3.i|\ty[%i] : ema=%i intervalle=%i\n",
			(mdl->y_depart[c]+j),
			j, mdl->ema[j], mdl->intervalles[j]);
	}
};