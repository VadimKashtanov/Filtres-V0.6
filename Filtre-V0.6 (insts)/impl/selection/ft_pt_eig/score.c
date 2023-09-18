#include "selection.h"

static uint pts_par_gain[] = {1,0,1,1,2};
static uint pts_par_pred[] = {1,1,0,2,1};

void score_ft(F_t * ft, Env_t env) {
	//	Scores
	FOR(0, i, S_FILTRES) {
		//ft->gain[i] = gain(ft->mdl[i], env.l);
		//ft->pred[i] = prediction(ft->mdl[i], env.l);
		gain_pred(ft->mdl[i], env.l, ft->gain+i, ft->pred+i);
		//
		ft->cintu[i] = i;
		ft->pts[i] = 0;
	//	ptr("(%f,%f)  ", ft->pred[i], ft->gain[i]);
	}
	//ptr("\n");

	//	Points
	FOR(0, i, S_FILTRES) {
		FOR(0, j, S_FILTRES) {
			if (ft->gain[i] < ft->gain[j])
				ft->pts[j] += pts_par_gain[MODE_DE_SCORE];
			if (ft->pred[i] < ft->pred[j])
				ft->pts[j] += pts_par_pred[MODE_DE_SCORE];
		}
	};

	//	Cintu
	uint c;
	FOR(0, i, S_FILTRES) {
		FOR(i+1, j, S_FILTRES) {
			if (ft->pts[ft->cintu[i]] < ft->pts[ft->cintu[j]]) {
				c = ft->cintu[i];
				ft->cintu[i] = ft->cintu[j];
				ft->cintu[j] = c;
			}
		}
	}
};

void score_pt(P_t * pt, Env_t env) {
	FOR(0, i, S_POIDS) {
		score_ft(pt->ft[i], env);
		pt->pred[i] = pt->ft[i]->pred[pt->ft[i]->cintu[0]];
		pt->gain[i] = pt->ft[i]->gain[pt->ft[i]->cintu[0]];
		pt->cintu[i] = i;
		pt->pts[i] = 0;
		ptr("(%f,%f)  ", pt->pred[i], pt->gain[i]);
	}
	ptr("\n");

	FOR(0, i, S_POIDS) {
		FOR(0, j, S_POIDS) {
			if (pt->gain[i] < pt->gain[j])
				pt->pts[j] += pts_par_gain[MODE_DE_SCORE];
			if (pt->pred[i] < pt->pred[j])
				pt->pts[j] += pts_par_pred[MODE_DE_SCORE];
		}
	};

	uint c;
	FOR(0, i, S_POIDS) {
		FOR(i+1, j, S_POIDS) {
			if (pt->pts[pt->cintu[i]] < pt->pts[pt->cintu[j]]) {
				c = pt->cintu[i];
				pt->cintu[i] = pt->cintu[j];
				pt->cintu[j] = c;
			}
		}
	}
};

void score_eig(EIG_t * eig, Env_t env) {
	FOR(0, i, S_EMA_INT_GLISSE) {
		score_pt(eig->pt[i], env);
		eig->pred[i] = eig->pt[i]->pred[eig->pt[i]->cintu[0]];
		eig->gain[i] = eig->pt[i]->gain[eig->pt[i]->cintu[0]];
		eig->cintu[i] = i;
		eig->pts[i] = 0;
	}

	FOR(0, i, S_EMA_INT_GLISSE) {
		FOR(0, j, S_EMA_INT_GLISSE) {
			if (eig->gain[i] < eig->gain[j])
				eig->pts[j] += pts_par_gain[MODE_DE_SCORE];
			if (eig->pred[i] < eig->pred[j])
				eig->pts[j] += pts_par_pred[MODE_DE_SCORE];
		}
	};

	uint c;
	FOR(0, i, S_EMA_INT_GLISSE) {
		FOR(i+1, j, S_EMA_INT_GLISSE) {
			if (eig->pts[eig->cintu[i]] < eig->pts[eig->cintu[j]]) {
				c = eig->cintu[i];
				eig->cintu[i] = eig->cintu[j];
				eig->cintu[j] = c;
			}
		}
	}
};