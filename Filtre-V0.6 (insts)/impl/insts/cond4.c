#include "mdl.h"

#define PAREIL_MAIS_x1(depart) do {if (x1 < -0.5) return poid[depart + 0];else if (x1 < 0) return poid[depart + 1];else if (x1 < 0.5) return poid[depart + 2];else return poid[depart + 3];} while (0);

float COND4_f(float * x, float * poid, uint n) {
	if (n != 2) {
		ERR("Pas d'implementation pour COND4 de n=%i", n);
	} else if (n == 2) {
		float x0=x[0], x1=x[1];
		if (x0 < -0.5) {
			PAREIL_MAIS_x1(0);
		} else if (x0 < 0) {
			PAREIL_MAIS_x1(4);
		} else if (x0 < 0.5) {
			PAREIL_MAIS_x1(8);
		} else {
			PAREIL_MAIS_x1(12);
		};
	}
};

#define __ROUGE "\033[41m \033[0m"
#define __VERT  "\033[42m \033[0m"
#define __ROUGE_ROUGE "\033[101m \033[0m"
#define __VERT_VERT  "\033[102m \033[0m"

static char * couleurs[] = {__ROUGE_ROUGE, __ROUGE, __VERT, __VERT_VERT};

void COND4_plume_poids(Mdl_t * mdl, uint c) {
	ptr("COND4 #%i\n", c);
	FOR(0, y, mdl->y[c]) {
		FOR(0, i, 4) {
			FOR(0, j, 4) {
				uint pos = mdl->poid_depart[c] + y*16 + i*4 + j;
				printf("%3.i|  %+f   %s%s\n",
					pos, mdl->poid[pos],
					couleurs[i],
					couleurs[j]
				);
			}
		}
	}
};

void COND4_plume_config(Mdl_t * mdl, uint c) {
	printf("#%2.i COND4 n=%i:\n", c, mdl->n[c]);
	FOR(0, j, mdl->y[c])
		ptr("%3.i|\ty[%i] : cond4(%i,%i)\n", (mdl->y_depart[c]+j), j, j*2, j*2+1);
};