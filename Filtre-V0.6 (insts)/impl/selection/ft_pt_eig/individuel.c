#include "selection.h"

Mdl_t * individuel_fp(Mdl_t * depart, Env_t env, uint T_ft) {
	F_t * ft = cr_ft(depart);
	FOR(0, i, T_ft) {
		score_ft(ft, env);
		if (i != T_ft-1) muter_ft(ft, env);
	}
	Mdl_t * ret = copier_mdl(ft_meilleur(ft));
	lib_ft(ft);
	return ret;
};

Mdl_t * individuel_pt(Mdl_t * depart, Env_t env, uint T_ft, uint T_pt) {
	P_t * pt = cr_pt(depart);

	INIT_BARRE(avancement);
	DEPART_BARRE(avancement);

	FOR(0, j, T_pt) {
		FOR(0, i, T_ft) {
			score_pt(pt, env);
			
			if (i != T_ft-1) {
				FOR(0, k, S_POIDS) {
					muter_ft(pt->ft[k], env);
				}
			}

			PROGRESSION(avancement, (float)(j*T_ft + i)/(T_pt*T_ft));
		}
		if (j != T_pt-1) {
			//printf("OK\n");
			muter_pt(pt, env);
		}
	}
	printf("\n");
	Mdl_t * ret = copier_mdl(pt_meilleur(pt));
	lib_pt(pt);
	return ret;
};

Mdl_t * individuel_eig(
	Mdl_t * depart, Env_t env, uint T_ft, uint T_pt, uint T_eig)
{
	EIG_t * eig = cr_eig(depart);

	FOR(0, t0, T_eig) {
		FOR(0, t1, T_pt) {
			FOR(0, t2, T_ft) {
				score_eig(eig, env);

				if (t2 != T_ft-1) {
					eig_muter_tous_ft(eig, env);
				}
			}

			FOR(0, i, S_EMA_INT_GLISSE) {
				Mdl_t * Gpt = pt_meilleur(eig->pt[i]);
				FOR(0, j, S_POIDS) {
				//	if (j == 0) 
				}
			}
		}

		Mdl_t * Geig = eig_meilleur(eig);
		FOR(0, i, S_EMA_INT_GLISSE) {

		}
	}
};