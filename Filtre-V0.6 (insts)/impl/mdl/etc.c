#include "mdl.h"

#define _LONG 9
static float p_cond[_LONG] = {
	-1, -.75, -0.5, -.25, 0, +.25, +0.5, .75, +1
}; 
float poid_cond_rnd() {
	return p_cond[rand() % (_LONG)];
};


float poid_cond_le_plus_proche(float x) {
	float plus_proche = p_cond[0];
	for (uint i=1; i < _LONG; i++) {
		if (fabs(p_cond[i]-x) < fabs(plus_proche-x)) plus_proche = p_cond[i];
	}
	return plus_proche;
};

//