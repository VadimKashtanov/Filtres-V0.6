#include "selection.h"

void muter_ft(F_t * ft, Env_t env) {
	Mdl_t * Gmdl = ft->mdl[ft->cintu[0]];
	//
	FOR(1, i, S_FILTRES) {
		muter_filtres(
			Gmdl, ft->mdl[ft->cintu[i]],
			env.MUTP_cst, env.COEF_G_cst);
		//plume_mdl(ft->mdl[ft->cintu[i]]);
	}
};

void muter_pt(P_t * pt, Env_t env) {
	F_t * Gft = pt->ft[pt->cintu[0]];
	Mdl_t * Gmdl = Gft->mdl[Gft->cintu[0]];
	//
	FOR(0, i, S_POIDS) {
		FOR(0, j, S_FILTRES) {
			if (!(i == 0 && j == 0)) {
				F_t * ft = pt->ft[pt->cintu[i]];
				//memcpy(ft->mdl[ft->cintu[j]], Gmdl, sizeof(Mdl_t));
				memcpy(ft->mdl[ft->cintu[j]]->conste, Gmdl->conste, sizeof(float) * Gmdl->constes);
				if (i != 0)
					muter_poids(Gmdl, ft->mdl[ft->cintu[j]], env.MUTP_p, env.COEF_G_p);
			}
		}
	}
};

void muter_eig(EIG_t * eig, Env_t env) {
/*	P_t * Gpt = eig->pt[eig->cintu[0]];
	F_t * Gft = Gpt->ft[Gpt->cintu[0]];
	Mdl_t * Gmdl = Gft->mdl[Gft->cintu[0]];
	//
	FOR(0, e, S_EMA_INT_GLISSE) {
		FOR(0, i, S_POIDS) {
			FOR(0, j, S_FILTRES) {
				if (!(i == 0 && j == 0 && e == 0)) {
					P_t * pt = eig->pt[eig->cintu[e]];
					F_t * ft = pt->ft[i];
					memcpy(ft->mdl[ft->cintu[j]], Gmdl, sizeof(Mdl_t));
					if (e != 0) {
						muter_ema(
							Gmdl,
							ft->mdl[ft->cintu[j]], env.MUTP_ema, env.COEF_G_ema);
						muter_intervalle(
							Gmdl,
							ft->mdl[ft->cintu[j]], env.MUTP_int, env.COEF_G_int);
					}
				}
			}
		}
	}*/
};

void eig_muter_tous_ft(EIG_t * eig, Env_t env) {
	FOR(0, i, S_EMA_INT_GLISSE) {
		FOR(0, j, S_POIDS) {
			muter_ft(eig->pt[i]->ft[j], env);
		}
	}
};

void eig_muter_tous_pt(EIG_t * eig, Env_t env) {
	FOR(0, i, S_EMA_INT_GLISSE) {
		muter_pt(eig->pt[i], env);
	}
};