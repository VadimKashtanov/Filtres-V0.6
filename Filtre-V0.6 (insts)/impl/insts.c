#include "mdl.h"

f_t inst[INSTS] = {
	NULL, COND2_f, COND4_f, MOY_f
};

plume_poids_t inst_plume_poids[INSTS] = {
	NULL, COND2_plume_poids, COND4_plume_poids, MOY_plume_poids
};

plume_config_t inst_plume_config[INSTS] = {
	fltr_prix_plume_config, COND2_plume_config, COND4_plume_config, MOY_plume_config
};