#include "mdl.h"

float f(Mdl_t * mdl, uint depart) {
	uint C = mdl->C;
	uint * type = mdl->type;
	uint * y = mdl->y;
	uint * n = mdl->n;

	uint d;

	//	Filtres N
	float _x[MAX2(FLTR_max, N_max)];	//fltr et les autres couches l'utiliseront donc on doit satisfaire tout le monde

	//  Couche[0], fltr prixs
	float _max, _f;
	FOR(0, i, y[0]) {
		uint _ema = mdl->ema[i];
		uint interv = intervalles[mdl->intervalles[i]];

		//
		FOR(0, j, n[0])
			_x[j] = ema[_ema][depart - j*interv];

		mdl->var[i] = fltr_prix_f(_x, mdl->conste + i*constes_FLTR(n[0]), n[0]);
	};

	//  Autres insts principales

	FOR(1, i, C) {
		d = (C-i);
		FOR(0, j, y[i]) {
			FOR(0, k, n[i]) {
				_x[k] = mdl->var[mdl->y_depart[i-1] + j*n[i] + k];
			}
			float * depart_poid;
			//
			if (mdl->type[i] == COND2) depart_poid = mdl->poid + mdl->poid_depart[i] + j*poids_COND2(mdl->n[i]);
			if (mdl->type[i] == COND4) depart_poid = mdl->poid + mdl->poid_depart[i] + j*poids_COND4(mdl->n[i]);
			if (mdl->type[i] == MOY  ) depart_poid = NULL;
			//
			mdl->var[mdl->y_depart[i] + j] = inst[mdl->type[i]](
				//_x,
				mdl->var + mdl->y_depart[i-1] + j*n[i],
				depart_poid,
				mdl->n[i]
			);
		}
	}
	//
	return mdl->var[mdl->vars-1];
};


















