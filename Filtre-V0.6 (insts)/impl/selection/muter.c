#include "selection.h"

void muter_filtres(Mdl_t * G, Mdl_t * P, float proba, float COEF_G) {
	float s[FLTR_max], d[FLTR_max];
	float _max, _min;
	float _max1, _min1;
	uint pos;
	//
	FOR(0, c, G->C) {
		if (G->type[c] == 0) {
			FOR(0, i, G->y[c]) {
				if (rnd() <= proba) {
					s[0] = rnd()-.5;
					d[0] = rnd()-.5;
					if (_max < s[0]) _max = s[0]/2+d[0];
					if (_min < s[0]) _min = s[0]/2+d[0];
					FOR(1, k, G->n[c]) {
						s[k] = s[k-1] + (rnd()-.5);
						if (k % 2 == 0) d[k] = d[k-1] + (rnd()-.5);
						if (_max < s[k]/2+d[k]) _max = s[k]/2+d[k];
						if (_min > s[k]/2+d[k]) _min = s[k]/2+d[k];
					}
					//
					_max1 = 0;
					_min1 = 1;
					FOR(0, k, G->n[c]) {
						pos = G->conste_depart[c] + i*G->n[c] + k;
						P->conste[pos] = COEF_G*G->conste[pos] + (1-COEF_G)*((s[k]/2+d[k])-_min)/(_max-_min);
						if (P->conste[pos] > _max1) _max1 = P->conste[pos];
						if (P->conste[pos] < _min1) _min1 = P->conste[pos];
					};
					FOR(0, k, G->n[c]) {
						pos = G->conste_depart[c] + i*G->n[c] + k;
						P->conste[pos] = (P->conste[pos]-_min1)/(_max1-_min1);
					}
				}
			};
		};
	}
};

void muter_poids(Mdl_t * G, Mdl_t * P, float proba, float COEF_G) {
	FOR(0, i, G->poids) {
		P->poid[i] = G->poid[i];
		//
		if (rnd() <= proba)
			P->poid[i] = poid_cond_le_plus_proche(COEF_G*G->poid[i] + (1-COEF_G)*poid_cond_rnd());
	}
};

void muter_ema(Mdl_t * G, Mdl_t * P, float proba, float COEF_G) {
	FOR(0, i, G->y[0]) {
		P->ema[i] = G->ema[i];
		if (rnd() <= proba)
			P->ema[i] = (uint)roundf(COEF_G*G->ema[i] + (1-COEF_G)*(rand()%NB_DIFF_EMA));
	}
};

void muter_intervalle(Mdl_t * G, Mdl_t * P, float proba, float COEF_G) {
	FOR(0, i, G->y[0]) {
		P->intervalles[i] = G->intervalles[i];
		if (rnd() <= proba)
			P->intervalles[i] = (uint)roundf(COEF_G*G->intervalles[i] + (1-COEF_G)*(rand()%INTERVALLES));
	}
};
