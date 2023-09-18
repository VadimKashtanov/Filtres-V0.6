#include "mdl.h"

void copier_constes(Mdl_t * de, Mdl_t * vers) {
	FOR(0, c, de->C) {
		if (de->type[c] == 0) {
			memcpy(
				vers->conste+vers->conste_depart[c],
				de->conste+de->conste_depart[c],
				sizeof(float) * de->n[c] * de->y[c]
			);
		}
	}
};

void copier_poids(Mdl_t * de, Mdl_t * vers) {
	FOR(0, c, de->C) {
		if (de->type[c] == 0) {
			memcpy(
				vers->conste+vers->conste_depart[c],
				de->conste+de->conste_depart[c],
				sizeof(float) * de->n[c] * de->y[c]
			);
		}
	}
};

void copier_ema(Mdl_t * de, Mdl_t * vers) {
	memcpy(vers->ema, de->ema, sizeof(uint) * de->y[0]);
};

void copier_intervalles(Mdl_t * de, Mdl_t * vers) {
	memcpy(vers->intervalles, de->intervalles, sizeof(uint) * de->y[0]);
};