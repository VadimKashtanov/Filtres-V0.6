#include "mdl.h"

//	Le gagant se conserve, le perdant copie le gagant
//	puis mute selon des regles definie dans `Env_t`
//GG=1
//GP=1
typedef struct  {
	//  %[0;1] de chance que P mute
	float MUTP_cst;		//% filtres
	float MUTP_p;		//% poids
	float MUTP_ema;		//% ema
	float MUTP_int;		//% intervalles

	//	%[0;1] d'influence de la valeure du G, quand P mute
	float COEF_G_cst;
	float COEF_G_p;
	float COEF_G_ema;
	float COEF_G_int;
	
	//  u += u*f*levier*( prix[i+l]/prix[i]-1 )
	uint l; //=2;
} Env_t;

//  Fonctions de score
float gain(Mdl_t * mdl, uint l);			//	le gain exacte sur tout le `prix`
float prediction(Mdl_t * mdl, uint l);		//	% de prediction de tendance
float investissement(Mdl_t * mdl, uint l);	//	% de bon placement (donc ignorance de f(x)=0)
float gain_168H(Mdl_t * mdl, uint l);		//	gain dernier semaine avex x25

float gain_JUSQUE_PRIXS(Mdl_t * mdl, uint l, float __LEVIER);

void gain_pred_invest(Mdl_t * mdl, uint l, float * _gain, float * _pred, float * _invest, float * _gain_170H);

//  Fonctions de Mutation
void muter_filtres(Mdl_t * G, Mdl_t * P, float proba, float COEF_G);
void muter_poids(Mdl_t * G, Mdl_t * P, float proba, float COEF_G);
void muter_ema(Mdl_t * G, Mdl_t * P, float proba, float COEF_G);
void muter_intervalle(Mdl_t * G, Mdl_t * P, float proba, float COEF_G);

//couches
//  n
//      y
//			glissades
//          	intervalles
//              	ema
//                      poids
//                          filtres

//	score[i] -> prediction(mdl[i])
//	cintu[i] -> #rang du i-eme mdl

#define MODE_DE_SCORE 5 /*
Valeur du rang dans les points
	0 : 1*pred + 1*gain
	1 : 1*pred
	2 : 	     1*gain
	3 : 2*pred + 1*gain
	4 : 1*pred + 2*gain
	5 : 1*pred + 1*gain + 1*invest + 1*gain_168H
*/

#define S_FILTRES 			4
typedef struct {
	float      gain[S_FILTRES];
	float      pred[S_FILTRES];
	float    invest[S_FILTRES];
	float gain_168H[S_FILTRES];
	uint        pts[S_FILTRES];
	uint      cintu[S_FILTRES];
	Mdl_t *     mdl[S_FILTRES];
} F_t;

#define S_POIDS 			3
typedef struct {
	float      gain[S_POIDS];
	float      pred[S_POIDS];
	float    invest[S_POIDS];
	float gain_168H[S_POIDS];
	uint        pts[S_POIDS];
	uint      cintu[S_POIDS];
	F_t *        ft[S_POIDS];
} P_t;

#define S_EMA_INT_GLISSE  	3
typedef struct poids_filtres {
	float      pred[S_EMA_INT_GLISSE];
	float      gain[S_EMA_INT_GLISSE];
	float    invest[S_EMA_INT_GLISSE];
	float gain_168H[S_EMA_INT_GLISSE];
	uint        pts[S_EMA_INT_GLISSE];
	uint      cintu[S_EMA_INT_GLISSE];
	P_t *        pt[S_EMA_INT_GLISSE];
} EIG_t;

Mdl_t * ft_meilleur(F_t * ft);
Mdl_t * pt_meilleur(P_t * pt);
Mdl_t * eig_meilleur(EIG_t * eig);

F_t   *  cr_ft(Mdl_t * depart);
P_t   *  cr_pt(Mdl_t * depart);
EIG_t * cr_eig(Mdl_t * depart);

void  lib_ft(F_t * ft);
void  lib_pt(P_t * pt);
void lib_eig(EIG_t * eig);

void score_ft(F_t * ft, Env_t env);
void score_pt(P_t * pt, Env_t env);
void score_eig(EIG_t * eig, Env_t env);

void muter_ft(F_t * ft, Env_t env);
void muter_pt(P_t * pt, Env_t env);
void muter_eig(EIG_t * eig, Env_t env);

void eig_muter_tous_ft(EIG_t * eig, Env_t env);
void eig_muter_tous_pt(EIG_t * eig, Env_t env);

/////

Mdl_t * individuel_fp(Mdl_t * depart, Env_t env, uint T_ft);
Mdl_t * individuel_pt(Mdl_t * depart, Env_t env, uint T_ft, uint T_pt);
Mdl_t * individuel_eig(Mdl_t * depart, Env_t env, uint T_ft, uint T_pt, uint T_eig);

//	Pareil que EIG mais en 1 seule structure
#define N_GRANDE S_EMA_INT_GLISSE*S_POIDS*S_FILTRES
#define SE S_EMA_INT_GLISSE
#define SP S_POIDS
#define SF S_FILTRES
typedef struct grande_selection {
	float      pred[N_GRANDE];
	float      gain[N_GRANDE];
	float    invest[N_GRANDE];
	float gain_168H[N_GRANDE];
	uint        pts[N_GRANDE];
	uint      cintu[N_GRANDE];
	Mdl_t *     mdl[N_GRANDE];
} Grande_t;