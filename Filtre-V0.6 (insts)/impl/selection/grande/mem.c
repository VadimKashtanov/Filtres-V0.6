#include "selection.h"

static uint pts_par_gain[]      = {1,0,1,1,2,2};
static uint pts_par_pred[]      = {1,1,0,2,1,2};
static uint pts_par_invest[]    = {0,0,0,0,0,1};
static uint pts_par_gain_168H[] = {0,0,0,0,0,2};

Mdl_t * grande(Mdl_t * depart, Env_t env, uint T_ft, uint T_pt, uint T_eig) {
/*	Grande_t * grande = malloc(sizeof(Grande_t));

	//
	FOR(0, k, SE) grande->mdl[k*SP*SF+0] = copier_mdl(depart);
	FOR(1, k, SE) {
		muter_intervalle(
			depart, grande->mdl[k*SP*SF+0],
			env.MUTP_int, env.COEF_G_int);
		muter_ema(
			depart, grande->mdl[k*SP*SF+0],
			env.MUTP_ema, env.COEF_G_ema);
	}
	FOR(0, se, SE) {
		FOR(1, k, SP) grande->mdl[se*SP*SF+k*SF+0] = copier_mdl(grande->mdl[se*SP*SF+0]);
		FOR(1, k, SP) {
			muter_poids(
				grande->mdl[se*SP*SF+0], grande->mdl[se*SP*SF+k*SF+0],
				env.MUTP_p, env.COEF_G_p);
		}


		FOR(0, sp, SP) {
			FOR(0, k, SF) grande->mdl[se*SP*SF+sp*SF+k] = copier_mdl(grande->mdl[se*SP*SF+sp*SF+0]);
			FOR(1, k, SF) {
				muter_filtres(
					grande->mdl[se*SP*SF+sp*SF+0], grande->mdl[se*SP*SF+sp*SF+k],
					env.MUTP_cst, env.COEF_G_cst);
			}
		};

	};


	//	=============== Boucle principale =============
	Mdl_t * Gmdl;
	uint max_pts;
	uint max_i_ft[SE*SP];
	uint max_i_pt[SE];
	uint max_i_eig;
	uint depart;
	FOR(0, t0, T_eig) {
		FOR(0, t1, T_pt) {
			FOR(0, t2, T_ft) {
				//	Score
				FOR(0, i, N_GRANDE) {
					gain_pred_invest(
						grande->mdl[i], env.l,
						grande->gain+i, grande->pred+i, grande->invest+i, grande->gain_168H+i
					);
				};

				//	1 PTS * coef = au dessus d'aun autre modele
				FOR(0, i, N_GRANDE) {
					grande->cintu[i] = i % SF;
					FOR(0, j, N_GRANDE) {
						if (grande->gain[i] < grande->gain[j])
							grande->pts[j] += pts_par_gain[MODE_DE_SCORE];
						if (grande->pred[i] < grande->pred[j])
							grande->pts[j] += pts_par_pred[MODE_DE_SCORE];
						if (grande->invest[i] < grande->invest[j])
							grande->pts[j] += pts_par_invest[MODE_DE_SCORE];
						if (grande->gain_168H[i] < grande->gain_168H[j])
							grande->pts[j] += pts_par_gain_168H[MODE_DE_SCORE];
					}
				};

				//	Mutation
				if (t2 != T_ft) {
					FOR(0, se, SE) {
						FOR(0, sp, SP) {
							depart = se*SP*SF + sp*SF;
							max_pts = 0;
							FOR(0, k, SF) {
								if (max_pts < grande->pts[depart + k]) {
									max_pts = grande->pts[depart + k];
									Gmdl = grande->mdl[depart + k];
									max_i[se*SP+sp] = k;
								}
							}
							Gmdl = grande->mdl[depart + max_i[se*SP+sp]];
							FOR(0, k, SF) {
								if (k != max_i[se*SP+sp])
									muter_filtres(
										Gmdl, grande->mdl[depart+k],
										env.MUTP_cst, env.COEF_G_cst);
							}
						};

					};
				};
			};
			if (t1 != T_pt) {
				FOR(0, se, SE) {
					max_pts = 0;
					FOR(0, )

				}
			}
		};
		if (t0 != T_eig) {

		}
	};*/
};