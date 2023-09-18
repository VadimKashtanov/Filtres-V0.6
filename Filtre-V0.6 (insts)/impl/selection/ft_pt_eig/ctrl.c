#include "selection.h"

Mdl_t * ft_meilleur(F_t * ft) {
	return ft->mdl[ft->cintu[0]];
};

Mdl_t * pt_meilleur(P_t * pt) {
	F_t * Gft = pt->ft[pt->cintu[0]];
	return Gft->mdl[Gft->cintu[0]];
};

Mdl_t * eig_meilleur(EIG_t * eig) {
	P_t * Gpt = eig->pt[eig->cintu[0]];
	F_t * Gft = Gpt->ft[Gpt->cintu[0]];
	return Gft->mdl[Gft->cintu[0]];
};