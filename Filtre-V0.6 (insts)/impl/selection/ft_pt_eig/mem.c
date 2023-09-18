#include "selection.h"

F_t   *  cr_ft(Mdl_t * depart) {
	F_t * ret = malloc(sizeof(F_t));
	FOR(0, i, S_FILTRES) ret->mdl[i] = copier_mdl(depart);
	return ret;
};

P_t   *  cr_pt(Mdl_t * depart) {
	P_t * ret = malloc(sizeof(P_t));
	FOR(0, i, S_POIDS) ret->ft[i] = cr_ft(depart);
	return ret;
};

EIG_t * cr_eig(Mdl_t * depart) {
	EIG_t * ret = malloc(sizeof(EIG_t));
	FOR(0, i, S_EMA_INT_GLISSE) ret->pt[i] = cr_pt(depart);
	return ret;
};

void  lib_ft(F_t * ft) {
	FOR(0, i, S_FILTRES) liberer_mdl(ft->mdl[i]);
	free(ft);
};

void  lib_pt(P_t * pt) {
	FOR(0, i, S_POIDS) lib_ft(pt->ft[i]);
	free(pt);
};

void lib_eig(EIG_t * eig) {
	FOR(0, i, S_EMA_INT_GLISSE) lib_pt(eig->pt[i]);
	free(eig);
};