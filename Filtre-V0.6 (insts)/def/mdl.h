#pragma once

#include "marchee.h"

//	Configuration de la forme maximale du Model
#define FLTR_max 10
#define N_max 2  		//combien d'entrees prend l'instruction
#define C_max 10
#define Y_max 20

#define FLTR_PRIX 	0 	//exp(-s*s -d*d);
#define COND2 		1	//--,-+,+-,++
#define COND4 		2	//00,01,02,03, 10,11,12,13, 20,21,22,23, 30,31,32,33,
#define MOY   		3	//(a+b+...)/n

#define poids_COND2(n) 4  //(1 << n)		//2**n    2 etats
#define poids_COND4(n) 16 //(1 << (2*n))	//4**n    4 etats
#define poids_MOY(n)   0  //0

#define constes_FLTR(n) (n)

//
#define POIDS_max   (Y_max*MAX3(poids_COND2(N_max), poids_COND4(N_max), poids_MOY(N_max)))
#define CONSTES_max (constes_FLTR(FLTR_max)*Y_max)

typedef struct {
	//	Config dimentions & entree de la pile
	uint C;
	uint y[C_max], n[C_max], type[C_max];
	uint ema[Y_max], intervalles[Y_max];

	//	Espace de Parametres & Calcules
	uint constes, poids, vars;
	float conste[Y_max*CONSTES_max], poid[Y_max*POIDS_max], var[Y_max*C_max];

	//	Depart de chaque couche dans les espaces
	uint conste_depart[C_max], poid_depart[C_max], y_depart[C_max];
} Mdl_t;

//	Instructions
typedef float (*f_t)(float * x, float * poid, uint n);
typedef void  (*plume_poids_t)(Mdl_t * mdl, uint c);
typedef void  (*plume_config_t)(Mdl_t * mdl, uint c);

#define INSTS 4
extern f_t inst[INSTS];
extern plume_poids_t inst_plume_poids[INSTS];
extern plume_config_t inst_plume_config[INSTS];

//	Instruction Spetiale
float fltr_prix_f(float * x, float * conste, uint n);
void fltr_prix_plume_constes(Mdl_t * mdl);
void fltr_prix_plume_config(Mdl_t * mdl, uint c);

//	Instructions Normales
float COND2_f(float * x, float * conste, uint n);
void COND2_plume_poids(Mdl_t * mdl, uint c);
void COND2_plume_config(Mdl_t * mdl, uint c);
//
float COND4_f(float * x, float * conste, uint n);
void COND4_plume_poids(Mdl_t * mdl, uint c);
void COND4_plume_config(Mdl_t * mdl, uint c);
//
float MOY_f(float * x, float * conste, uint n);
void MOY_plume_poids(Mdl_t * mdl, uint c);
void MOY_plume_config(Mdl_t * mdl, uint c);


//	Allocation Memoire
Mdl_t * cree_mdl(uint C, uint * y, uint * n, uint * type);
void liberer_mdl(Mdl_t * mdl);
Mdl_t * copier_mdl(Mdl_t * mdl);

//	Copies spetiales
void copier_constes(Mdl_t * de, Mdl_t * vers);
void copier_poids(Mdl_t * de, Mdl_t * vers);
void copier_ema(Mdl_t * de, Mdl_t * vers);
void copier_intervalles(Mdl_t * de, Mdl_t * vers);

//  Controle
uint meme_mdl(Mdl_t * A, Mdl_t * B);
uint hash_mdl(Mdl_t * mdl);

//	Memoire dure
void ecrire_mdl(Mdl_t * mdl, char * file);
Mdl_t * lire_mdl(char * file);

//	Plume
void plume_mdl(Mdl_t * mdl);
void comportement(Mdl_t * mdl);

//	Qlqs fonctions directes
float poid_cond_rnd();	//{-1,-.75,-.50,-.25,+0.0,+.25,+.5,+.75,+1}
float poid_cond_le_plus_proche(float x);

//	Calcule f(x)
float f(Mdl_t * mdl, uint depart);