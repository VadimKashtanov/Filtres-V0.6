#include "mdl.h"

float COND2_f(float * x, float * poid, uint n) {
	if (n != 2) {
		ERR("Pas d'implementation pour COND2 de n=%i", n);
	} else if (n == 2) {
		float x0=x[0], x1=x[1];
		if (x0 < 0) {
			if (x1 < 0) return poid[0];
			else return poid[1];
		} else {
			if (x1 < 0) return poid[2];
			else return poid[3];
		}
	}
}

#define __ROUGE "\033[101m \033[0m"
#define __VERT  "\033[102m \033[0m"

void COND2_plume_poids(Mdl_t * mdl, uint c) {
	ptr("COND2 #%i\n", c);
	FOR(0, y, mdl->y[c]) {
		FOR(0, i, 2) {
			FOR(0, j, 2) {
				uint pos = mdl->poid_depart[c] + y*4 + i*2 + j;
				printf("%3.i|  %+f   %s%s\n",
					pos, mdl->poid[pos],
					(i == 0 ? __ROUGE : __VERT),
					(j == 0 ? __ROUGE : __VERT)
				);
			}
		}
	}
};

void COND2_plume_config(Mdl_t * mdl, uint c) {
	printf("#%2.i COND2 n=%i:\n", c, mdl->n[c]);
	FOR(0, j, mdl->y[c])
		ptr("%3.i|\ty[%i] : cond2(%i,%i)\n", (mdl->y_depart[c]+j), j, j*2, j*2+1);
};