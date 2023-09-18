#include "mdl.h"

float MOY_f(float * x, float * poid, uint n) {
	return (x[0]+x[1])/2;
};

void MOY_plume_poids(Mdl_t * mdl, uint y) {
	
};

void MOY_plume_config(Mdl_t * mdl, uint c) {
	printf("#%2.i MOY n=%i:\n", c, mdl->n[c]);
	FOR(0, j, mdl->y[c])
		ptr("%3.i|\ty[%i] : (%i+%i)/2\n", (mdl->y_depart[c]+j), j, j*2, j*2+1);
};