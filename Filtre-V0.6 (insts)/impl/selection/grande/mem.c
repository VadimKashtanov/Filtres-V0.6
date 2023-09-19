#include "selection.h"

Grande_t * cr_grad(Mdl_t * depart, Env_t env) {
	Grande_t * grande = malloc(sizeof(Grande_t));

	//
	FOR(0, i, N_GRANDE)
		grande->mdl[i] = copier_mdl(depart);
	
	//
	FOR(0, k, SE) grande->mdl[k*SP+0] = copier_mdl(depart);
	FOR(1, k, SE) {
		muter_intervalle(
			depart, grande->mdl[k*SP+0],
			env.MUTP_int, env.COEF_G_int);
		muter_ema(
			depart, grande->mdl[k*SP+0],
			env.MUTP_ema, env.COEF_G_ema);
	}
	FOR(0, se, SE) {
		FOR(0, k, SP) grande->mdl[se*SP+k*SF+0] = copier_mdl(grande->mdl[se*SP+0]);
		FOR(1, k, SP) {
			muter_poids(
				grande->mdl[se*SP+0], grande->mdl[se*SP+k*SF+0],
				env.MUTP_p, env.COEF_G_p);
		}


		FOR(0, sp, SP) {
			FOR(0, k, SF) grande->mdl[se*SP+sp*SF+k] = copier_mdl(grande->mdl[se*SP+sp*SF+0]);
			FOR(1, k, SF) {
				muter_filtres(
					grande->mdl[se*SP+sp*SF+0], grande->mdl[se*SP+sp*SF+k],
					env.MUTP_cst, env.COEF_G_cst);
			}
		};

	};
};