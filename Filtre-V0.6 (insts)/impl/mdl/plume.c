#include "mdl.h"

void plume_mdl(Mdl_t * mdl) {
	printf("======== Mdl ===========\n");
	printf("-- Configuration --\n");
	FOR(0, c, mdl->C)
		inst_plume_config[mdl->type[c]](mdl, c);
	
	//printf("------ Poids ------\n");
	//FOR(1, c, mdl->C)
	//	inst_plume_poids[mdl->type[c]](mdl, c);

	//printf("---- Constantes ---\n");
	//fltr_prix_plume_constes(mdl);
};

//===============================================

void comportement(Mdl_t * mdl) {
#define T 24

	uint depart = DEPART + (rand() % (PRIXS-DEPART-T-1));

	float f_arr[T];

	float var_par_t[T*mdl->vars];

	for (uint i=0; i < T; i++) {
		f_arr[i] = f(mdl, depart + i);
		memcpy(var_par_t + i*mdl->vars, mdl->var, sizeof(float)*mdl->vars);
	};

	for (uint i=0; i < mdl->vars; i++) {
		printf("%2.i| ", i);
		for (uint t=0; t < T; t++) {
			if (var_par_t[t*mdl->vars + i] >= 0) printf(" ");
			printf("%-3.2f | ", var_par_t[t*mdl->vars + i]);
		}
		printf("\n");
	}

	//gnuplot(ema[1] + depart - 6*6, 6, "ema1");
	//gnuplot(ema[1] + depart + T - 6*6, 6, "ema2");

	gnuplot(prixs + depart, T, "Prixs");
	gnuplot(f_arr, T, "Valeur de f (achat vente)");

	//plume_mdl(mdl);
	//plume_poids(mdl);
	//plume_constes(mdl);
};
