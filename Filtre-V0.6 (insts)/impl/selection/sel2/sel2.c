#include "sel2.h"

static uint   pts_par_gain[] = {1,0,1,1,2,1};
static uint   pts_par_pred[] = {1,1,0,2,1,3};
static uint pts_par_invest[] = {0,0,0,0,0,1};
static uint   pts_par_168H[] = {0,0,0,0,0,1};

Mdl_t * sel2_filtres(
	Mdl_t * depart, Env_t env,
	uint Gs, uint Ps, uint T, uint bonus)
{
	//UNE_COURBE(s)

	//	Les modeles
	uint N = Gs*(Ps+1);
	Mdl_t * mdl[N];
	FOR(0, i, N) mdl[i] = copier_mdl(depart);
	FOR(1, i, N) muter_filtres(
		depart, mdl[i],
		env.MUTP_cst, env.COEF_G_cst);

	//	Les scores
	float   _gain[N];
	float   _pred[N];
	float _invest[N];
	float   _168H[N];
	uint      pts[N];
	uint    cintu[N];

	//
	Mdl_t * Gmdl[Gs];
	FOR(0, t, T) {
		//	Score de chaque model
		FOR(0, i, N) {
			gain_pred_invest(
				mdl[i], env.l,
				_gain+i, _pred+i, _invest+i, _168H+i);
		//	printf("(%2.1f %2.4f %2.4f), ", _gain[i], _pred[i], _invest[i]);//, _168H[i]);
		}
		//printf("\n");

		//	Calcule de points par model
		FOR(0, i, N) {
			pts[i] = 0;
			cintu[i] = i;
			uint bonus_g=1, bonus_p=1, bonus_i=1, bonus_1=1;
			FOR(0, j, N) {
				if (_gain[i] >= _gain[j]) {
					pts[i] += pts_par_gain[MODE_DE_SCORE];
				} else bonus_g = 0;
				if (_pred[i] >= _pred[j]) {
					pts[i] += pts_par_pred[MODE_DE_SCORE];
				} else bonus_p = 0;
				if (_invest[i] >= _invest[j]) {
					pts[i] += pts_par_invest[MODE_DE_SCORE];
				} else bonus_i = 0;
				if (_168H[i] >= _168H[j]) {
					pts[i] += pts_par_168H[MODE_DE_SCORE];
				} else bonus_1 = 0;
			};
			pts[i] += pts_par_gain[MODE_DE_SCORE] * bonus_g * bonus;
			pts[i] += pts_par_pred[MODE_DE_SCORE] * bonus_p * bonus;
			pts[i] += pts_par_invest[MODE_DE_SCORE] * bonus_i * bonus;
			pts[i] += pts_par_168H[MODE_DE_SCORE] * bonus_1 * bonus;
		};

		//	Hierarchie des models par nb de points
		uint c;
		FOR(0, i, N) {
			FOR(i+1, j, N) {
				if (pts[cintu[i]] < pts[cintu[j]]) {
					c = cintu[i];
					cintu[i] = cintu[j];
					cintu[j] = c;
				}
			}
		}

		//	Nouvelle generation
		FOR(0, g, Gs) {
			Gmdl[g] = mdl[cintu[g]];
			FOR(0, p, Ps) {
				muter_filtres(
					Gmdl[g], mdl[cintu[Gs + g*Ps + p]],
					env.MUTP_cst, env.COEF_G_cst);
			};
		};

		//	Suivie de la courbe
	//	SUIVIE_COURBE(s, _pred[cintu[0]]);
	}

	//PLUMER_LA_COURBE(s)

	FOR(1, i, N) liberer_mdl(mdl[cintu[i]]);
	return mdl[cintu[0]];
}

Mdl_t * sel2_poids(
	Mdl_t * depart, Env_t env,
	uint flt_Gs, uint flt_Ps,
	uint flt_T, uint bonus_ft,
	uint Gs, uint Ps,
	uint T, uint bonus_pt)
{
	//UNE_COURBE(s)

	//	Les modeles
	uint N = Gs*(Ps+1);
	Mdl_t * mdl[N];
	FOR(0, i, N) mdl[i] = copier_mdl(depart);
	FOR(1, i, N) {
		muter_poids(
			depart, mdl[i],
			env.MUTP_p, env.COEF_G_p);
	}

	//	Les scores
	float   _gain[N];
	float   _pred[N];
	float _invest[N];
	float   _168H[N];
	uint      pts[N];
	uint    cintu[N];

	//
	Mdl_t * Gmdl[Gs];
	FOR(0, t, T) {
		//	Score de chaque model
		FOR(0, i, N) {
			Mdl_t * m = sel2_filtres(mdl[i], env, flt_Gs, flt_Ps, flt_T, bonus_ft);
			liberer_mdl(mdl[i]);
			mdl[i] = m;
			//
			gain_pred_invest(
				mdl[i], env.l,
				_gain+i, _pred+i, _invest+i, _168H+i);
		//	printf("(%2.1f %2.4f %2.4f %2.4f), ", _gain[i], _pred[i], _invest[i], _168H[i]);
		}
		//printf("\n");

		//	Calcule de points par model
		FOR(0, i, N) {
			pts[i] = 0;
			cintu[i] = i;
			uint bonus_g=1, bonus_p=1, bonus_i=1, bonus_1=1;
			FOR(0, j, N) {
				if (_gain[i] >= _gain[j]) {
					pts[i] += pts_par_gain[MODE_DE_SCORE];
				} else bonus_g = 0;
				if (_pred[i] >= _pred[j]) {
					pts[i] += pts_par_pred[MODE_DE_SCORE];
				} else bonus_p = 0;
				if (_invest[i] >= _invest[j]) {
					pts[i] += pts_par_invest[MODE_DE_SCORE];
				} else bonus_i = 0;
				if (_168H[i] >= _168H[j]) {
					pts[i] += pts_par_168H[MODE_DE_SCORE];
				} else bonus_1 = 0;
			};
			pts[i] += pts_par_gain[MODE_DE_SCORE] * bonus_g * bonus_pt;
			pts[i] += pts_par_pred[MODE_DE_SCORE] * bonus_p * bonus_pt;
			pts[i] += pts_par_invest[MODE_DE_SCORE] * bonus_i * bonus_pt;
			pts[i] += pts_par_168H[MODE_DE_SCORE] * bonus_1 * bonus_pt;
		};

		//	Hierarchie des models par nb de points
		uint c;
		FOR(0, i, N) {
			FOR(i+1, j, N) {
				if (pts[cintu[i]] < pts[cintu[j]]) {
					c = cintu[i];
					cintu[i] = cintu[j];
					cintu[j] = c;
				}
			}
		}

		//	Nouvelle generation
		FOR(0, g, Gs) {
			Gmdl[g] = mdl[cintu[g]];
			FOR(0, p, Ps) {
				muter_poids(
					Gmdl[g], mdl[cintu[Gs + g*Ps + p]],
					env.MUTP_p, env.COEF_G_p);
			};
		};

		//	Suivie de la courbe
	//	SUIVIE_COURBE(s, _pred[cintu[0]]);
	}

	//PLUMER_LA_COURBE(s)

	FOR(1, i, N) liberer_mdl(mdl[cintu[i]]);
	return mdl[cintu[0]];
}

Mdl_t * sel2_ei(
	Mdl_t * depart, Env_t env,
	uint flt_Gs, uint flt_Ps,
	uint flt_T, uint bonus_ft,
	uint p_Gs, uint p_Ps,
	uint p_T, uint bonus_pt,
	uint Gs, uint Ps,
	uint T, uint bonus_ei)
{
	UNE_COURBE(s)

	//	Les modeles
	uint N = Gs*(Ps+1);
	Mdl_t * mdl[N];
	FOR(0, i, N) mdl[i] = copier_mdl(depart);
	FOR(1, i, N) {
		/*muter_ema(
			depart, mdl[i],
			env.MUTP_ema, env.COEF_G_ema);
		muter_intervalle(
			depart, mdl[i],
			env.MUTP_int, env.COEF_G_int);*/
		muter_ema_intervalle(
			depart, mdl[i],
			env);//.MUTP_int, env.COEF_G_int);
	}

	//	Les scores
	float   _gain[N];
	float   _pred[N];
	float _invest[N];
	float   _168H[N];
	uint      pts[N];
	uint    cintu[N];

	INIT_BARRE(a);
	DEPART_BARRE(a);

	//
	Mdl_t * Gmdl[Gs];
	FOR(0, t, T) {
		//	Score de chaque model
		FOR(0, i, N) {
			Mdl_t * m = sel2_poids(
				mdl[i], env,
				flt_Gs, flt_Ps, flt_T, bonus_ft,
				p_Gs, p_Ps, p_T, bonus_pt);
			liberer_mdl(mdl[i]);
			mdl[i] = m;
			//plume_mdl(mdl[i]);
			//
			PROGRESSION(a, ((float)(t*N + i)/(T*N)));
			//
			gain_pred_invest(
				mdl[i], env.l,
				_gain+i, _pred+i, _invest+i, _168H+i);
			//printf("(%2.1f %2.4f %2.4f %2.4f), ", _gain[i], _pred[i], _invest[i], _168H[i]);
		}
		//printf("\n");

		//	Calcule de points par model
		FOR(0, i, N) {
			pts[i] = 0;
			cintu[i] = i;
			uint bonus_g=1, bonus_p=1, bonus_i=1, bonus_1=1;
			FOR(0, j, N) {
				if (_gain[i] >= _gain[j]) {
					pts[i] += pts_par_gain[MODE_DE_SCORE];
				} else bonus_g = 0;
				if (_pred[i] >= _pred[j]) {
					pts[i] += pts_par_pred[MODE_DE_SCORE];
				} else bonus_p = 0;
				if (_invest[i] >= _invest[j]) {
					pts[i] += pts_par_invest[MODE_DE_SCORE];
				} else bonus_i = 0;
				if (_168H[i] >= _168H[j]) {
					pts[i] += pts_par_168H[MODE_DE_SCORE];
				} else bonus_1 = 0;
			};
			pts[i] += pts_par_gain[MODE_DE_SCORE] * bonus_g * bonus_ei;
			pts[i] += pts_par_pred[MODE_DE_SCORE] * bonus_p * bonus_ei;
			pts[i] += pts_par_invest[MODE_DE_SCORE] * bonus_i * bonus_ei;
			pts[i] += pts_par_168H[MODE_DE_SCORE] * bonus_1 * bonus_ei;
		};

		//	Hierarchie des models par nb de points
		uint c;
		FOR(0, i, N) {
			FOR(i+1, j, N) {
				if (pts[cintu[i]] < pts[cintu[j]]) {
					c = cintu[i];
					cintu[i] = cintu[j];
					cintu[j] = c;
				}
			}
		}

		//	Nouvelle generation
		printf("\nScore reel : ");
		FOR(0, g, Gs) {
			Gmdl[g] = mdl[cintu[g]];
			//
			printf("(%f %f) ", prediction(Gmdl[g], env.l), investissement(Gmdl[g], env.l));
			//
			FOR(0, p, Ps) {
				//muter_ema(
				//	Gmdl[g], mdl[cintu[Gs + g*Ps + p]],
				//	env.MUTP_ema, env.COEF_G_ema);
				muter_ema_intervalle(
					Gmdl[g], mdl[cintu[Gs + g*Ps + p]],
					env);//.MUTP_int, env.COEF_G_int);
			};
		};
		printf("\n");
		plume_mdl(Gmdl[0]);

		//	Suivie de la courbe
		SUIVIE_COURBE(s, _pred[cintu[0]]);
	}

	PLUMER_LA_COURBE(s)

	FOR(1, i, N) liberer_mdl(mdl[cintu[i]]);
	return mdl[cintu[0]];
}