#pragma once

#include "selection.h"

Mdl_t * sel2_filtres(
	Mdl_t * depart, Env_t env,
	uint Gs, uint Ps, uint T, uint bonus);
//Gs=2, Ps=3-4-5

Mdl_t * sel2_poids(
	Mdl_t * depart, Env_t env,
	uint flt_Gs, uint flt_Ps,
	uint flt_T, uint bonus_ft,
	uint p_Gs, uint p_Ps,
	uint p_T, uint bonus_pt);
//Gs=1, Ps=3-4

Mdl_t * sel2_ei(
	Mdl_t * depart, Env_t env,
	uint flt_Gs, uint flt_Ps,
	uint flt_T, uint bonus_ft,
	uint p_Gs, uint p_Ps,
	uint p_T, uint bonus_pt,
	uint ei_Gs, uint ei_Ps,
	uint ei_T, uint bonus_ei);