#include "mdl.h"

Mdl_t * cree_mdl(uint C, uint * y, uint * n, uint * type) {
	Mdl_t * mdl = calloc(1, sizeof(Mdl_t));
	memset(mdl, 0, sizeof(Mdl_t));

	//  Conditions d'existance    
	assert(C > 0);
	assert(type[0] == 0);
	assert(y[C-1] == 1);
	assert(n[0] <= FLTR_max);
	assert(n[0] >= N_max);
	assert(y[0] <= Y_max);

	//  Configuration structurelle
	mdl->C = C;
	memcpy(mdl->y, y, sizeof(uint) * C);
	memcpy(mdl->n, n, sizeof(uint) * C);
	memcpy(mdl->type, type, sizeof(uint) * C);
	
	//  Initialisation calcule Tailles des espaces. (Se feront pendant la boucle FOR(1,i,C))
	mdl->constes = constes_FLTR(n[0])*y[0];
	mdl->poids = 0; //type[0] == 0 donc aucuns poids
	mdl->vars = y[0];

	//  Les constes de la couche 0
	FOR(0, i, y[0]) {
		float s=2*(rnd()-.5);
		float d=2*(rnd()-.5);
		FOR(0, k, constes_FLTR(n[0])) {
			s += 2*(rnd()-.5);
			if (k % 2 == 0) d += 2*(rnd()-.5);
			mdl->conste[i*constes_FLTR(n[0]) + k] = s/2 + d;
		}
	}

	//  Ema & Intervalles	
	for (uint i=0; i < y[0]; i++) mdl->ema[i] = 0;//rand() % NB_DIFF_EMA;
	for (uint i=0; i < y[0]; i++) mdl->intervalles[i] = 0;//rand() % INTERVALLES;
	
	//	===== Autres Couches ====
	FOR(1, i, C) {
		if (type[i] == 0) {
			ERR("Impossible d'utiliser FLTR_PRIXS au dela de la 0-eme couche");
		} else if (type[i] == COND2) {
			assert(n[i] == 2);// N_max);
			assert(y[i] == y[i-1]/2);
			//
			mdl->poid_depart[i] = mdl->poids;
			mdl->conste_depart[i] = mdl->constes;
			//
			mdl->poids += y[i] * poids_COND2(n[i]);
			mdl->constes += 0;
			FOR(0, k, y[i] * poids_COND2(n[i]))
				mdl->poid[mdl->poid_depart[i] + k] = poid_cond_rnd();
		} else if (type[i] == COND4) {
			assert(n[i] == 2);//N_max);
			assert(y[i] == y[i-1]/2);
			//
			mdl->poid_depart[i] = mdl->poids;
			mdl->conste_depart[i] = mdl->constes;
			//
			mdl->poids += y[i] * poids_COND4(n[i]);
			mdl->constes += 0;
			FOR(0, k, y[i] * poids_COND4(n[i]))
				mdl->poid[mdl->poid_depart[i] + k] = poid_cond_rnd();
		} else if (type[i] == MOY) {
			assert(n[i] == 2);//N_max);
			assert(y[i] == y[i-1]/2);
			//
			mdl->poid_depart[i] = mdl->poids;
			mdl->conste_depart[i] = mdl->constes;
			//
			mdl->poids += y[i] * poids_MOY(n[i]);
			mdl->constes += 0;
			FOR(0, k, y[i] * poids_MOY(n[i]))
				mdl->poid[mdl->poid_depart[i] + k] = poid_cond_rnd();
		} else {
			ERR("La couche %i n'existe pas", type[i]);        
		}
		//
		mdl->y_depart[i] = mdl->vars;
		mdl->vars += y[i];
	}
	//
	//  Normalisation des constantes
	FOR(0, c, mdl->C) {
		if (mdl->type[c] == 0) {
			FOR(0, i, mdl->y[c]) {
				uint d = mdl->conste_depart[c] + mdl->n[c]*i;
				float _max=mdl->conste[d], _min=mdl->conste[d];
				FOR(1, k, mdl->n[c]) {
					if (_max < mdl->conste[d+k]) _max = mdl->conste[d+k];
					if (_min > mdl->conste[d+k]) _min = mdl->conste[d+k];
				}
				//
				FOR(0, k, mdl->n[c]) {
					mdl->conste[d+k] = (mdl->conste[d+k]-_min)/(_max-_min);
				};
			}
		};
	};
	//
	return mdl;
};

void liberer_mdl(Mdl_t * mdl) {
	free(mdl);
};

Mdl_t * copier_mdl(Mdl_t * mdl) {
	Mdl_t * ret = malloc(sizeof(Mdl_t));
	memcpy(ret, mdl, sizeof(Mdl_t));
	return ret;
};
