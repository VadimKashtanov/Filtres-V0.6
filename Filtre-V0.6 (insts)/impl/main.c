#include "sel2.h"

uint C      = 5;
uint type[] = {FLTR_PRIX, COND4, COND4, COND4, COND4};
//
uint y[]    = {       16,     8,     4,     2,     1};
uint n[]    = {        7,     2,     2,     2,     2};

Env_t env = {
	//  Le gagant ne muteras jamais
	.MUTP_cst           =0.30,  .COEF_G_cst           =0.60,
	.MUTP_p             =0.02,	.COEF_G_p             =0.80,
	//
	.MUTP_ema_int       =0.30,  .COEF_G_ema_int       =0.70,

	//  Longeure
	.l=3
};

void score(Mdl_t * mdl) {
	printf("score : %f %f %f %f\n", gain(mdl, env.l), prediction(mdl, env.l), investissement(mdl, env.l), gain_168H(mdl, env.l));
};

__attribute__ ((optimize(0)))
int main_qlq_tests() {
	srand(2);
	charger_les_prixs();

	Mdl_t * mdl = cree_mdl(C, y, n, type);
	plume_mdl(mdl);

	muter_ema_intervalle(mdl, mdl, env);
	//muter_ema(mdl, mdl, env.MUTP_ema, env.COEF_G_ema);

	muter_ema_intervalle(mdl, mdl, env);
	//muter_ema(mdl, mdl, env.MUTP_ema, env.COEF_G_ema);

	plume_mdl(mdl);
};


int main_petits_tests() {
	srand(0);
	charger_les_prixs();

	Mdl_t * mdl = cree_mdl(C, y, n, type);;
	//plume_mdl(mdl);

	uint ft_T = 15;
	uint pt_T = 20;
	uint ei_T = 15;
	//mdl = sel2_filtres(mdl, env, 2, 5,   T);
	mdl = sel2_ei(
		mdl, env,
		//
		//2, 3,
		1, 1,
		ft_T, 0,
		//
		//1, 5,
		1, 3,
		pt_T, 0,
		//
		//1, 2,
		1, 1,
		ei_T, 0);
	plume_mdl(mdl);
	score(mdl);
};

int main_mdl() {
	srand(0);
	charger_les_prixs();	
	
	Mdl_t * depart = cree_mdl(C, y, n, type);
	//score(depart);

//	printf("%f\n", f(depart, DEPART));
//	printf("%f\n", f(depart, DEPART+1));
//	printf("%f\n", f(depart, DEPART+2));

	plume_mdl(depart);

	//gnuplot(prixs + DEPART-20, 3+20, "p");

	comportement(depart);
}

int main_pt() {
	srand(0);
	charger_les_prixs();	
	
	Mdl_t * depart = cree_mdl(C, y, n, type);
	score(depart);
	plume_mdl(depart);

	Mdl_t * res = individuel_pt(depart, env, 50, 10);
	score(res);
	plume_mdl(res);
	comportement(res);

	ecrire_mdl(res, "mdl.bin");
}

int main_ft() {
	srand(0);
	charger_les_prixs();

	//float _max=0;
	//FOR(0, i, 1000) {
	Mdl_t * depart = cree_mdl(C, y, n, type);
		//depart->poid[depart->poids-1-3] = -1;
		//depart->poid[depart->poids-1-2] = -0.5;
		//depart->poid[depart->poids-1-1] = +0.5;
		//depart->poid[depart->poids-1-0] = +1;
	score(depart);
	plume_mdl(depart);
	comportement(depart);
	
	Mdl_t * mdl = individuel_fp(depart, env, 200);
	score(mdl);
	plume_mdl(mdl);
	comportement(mdl);

	ecrire_mdl(mdl, "mdl.bin");
};

int main_eig() {
	srand(0);
	charger_les_prixs();

	Mdl_t * depart = cree_mdl(C, y, n, type);

	EIG_t * eig = cr_eig(depart);
	score_eig(eig, env);

	INIT_BARRE(avancement);
	DEPART_BARRE(avancement);

#define T_EIG 20
	FOR(0, i, T_EIG) {
#define T_POIDS 5//30
		FOR(0, p, T_POIDS) {
#define T_FLTR 10
			FOR(0, cst, T_FLTR) {
				if (cst != T_FLTR-1) eig_muter_tous_ft(eig, env);
				score_eig(eig, env);

				PROGRESSION(avancement, ((float)(i*T_POIDS*T_FLTR + p*T_FLTR + cst)/(T_FLTR*T_POIDS*T_EIG)));
			}
			if (p != T_POIDS-1) eig_muter_tous_pt(eig, env);
		}
		if (i != T_EIG-1) muter_eig(eig, env);
		{
			Mdl_t * meilleur = eig_meilleur(eig);
			ptr("#%i Meilleur : ", i);score(meilleur);
			plume_mdl(meilleur);
		}
	}
	ptr("\n");


	Mdl_t * meilleur = copier_mdl(eig_meilleur(eig));

	score(meilleur);
	comportement(meilleur);
	plume_mdl(meilleur);
	//gain(meilleur, env.l);

	printf(">>> Gains dernieres %iH : %f  levier=%f\n", (PRIXS-JUSQUE), gain_JUSQUE_PRIXS(meilleur, env.l, 10.0), 10.0);
	printf(">>> Gains dernieres %iH : %f  levier=%f\n", (PRIXS-JUSQUE), gain_JUSQUE_PRIXS(meilleur, env.l, 25.0), 25.0);
	printf(">>> Gains dernieres %iH : %f  levier=%f\n", (PRIXS-JUSQUE), gain_JUSQUE_PRIXS(meilleur, env.l, 50.0), 50.0);

	ecrire_mdl(meilleur, "mdl.bin");
};

int main() {
	//main_qlq_tests();
	main_petits_tests();
	//main_mdl();
	//main_pt();
	//main_ft();
	//main_eig();
}