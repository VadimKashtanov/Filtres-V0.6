#include "selection.h"

float gain(Mdl_t * mdl, uint l) {
	float _gain = USDT;
	//
	float _f, p0, p1;
	uint t=0;
	//UNE_COURBE(p);
	for (uint i=DEPART; i < PRIXS-1-l; i++) {
		p1 = prixs[i+l];
		p0 = prixs[i];
		//
		_f = /*signe*/( f(mdl, i) );
		//
		if (_gain > 0) {
			_gain += _gain * _f * LEVIER * (p1/p0 - 1.0);
		} else {
			return -USDT;
		}
		i += l;
	//	SUIVIE_COURBE(p, _gain);
	};
	//PLUMER_LA_COURBE(p);

	return _gain - USDT;
};

float prediction(Mdl_t * mdl, uint l) {
	float _prediction = 0.0;
	//
	float _f, p0, p1;
	uint t=0;
	for (uint i=DEPART; i < PRIXS-1-l; i++) {
		p1 = prixs[i+l];
		p0 = prixs[i];
		//
		_f = signe( f(mdl, i) );
		
		if (signe(p1/p0-1.0) == _f)
			_prediction += 1.0;

		//
#define div_par 0*(1+rand()%10)
		//i += div_par;
		i += l;
		t++;
	};
	//printf("%i\n", t);

	return _prediction / (float)t;
	//return gain(mdl, l);
};

float investissement(Mdl_t * mdl, uint l) {
	float _prediction = 0.0;
	//
	float _f, p0, p1;
	uint t=0;
	for (uint i=DEPART; i < PRIXS-1-l; i++) {
		p1 = prixs[i+l];
		p0 = prixs[i];
		//
		_f = f(mdl, i);
		
		if (signe(p1/p0-1.0) == signe(_f))
			_prediction += 1.0;

		//
//#define div_par 0*(1+rand()%10)
//		i += div_par;
		i += l;
		if (_f != 0) t++;		//<<---
	};
	//printf("%i\n", t);

	return _prediction / (float)t;
	//return gain(mdl, l);
};

void gain_pred_invest(
	Mdl_t * mdl, uint l,
	//
	float * _gain,
	float * _pred,
	float * _invest,
	float * _gain_168H)
{
	*_gain = USDT;
	*_pred = 0.0;
	*_invest = 0.0;
	//
	float _f, p0, p1;
	uint t=0, _t=0;
	//UNE_COURBE(p);
	for (uint i=DEPART; i < JUSQUE/*PRIXS*/-1-l; i++) {
		p1 = prixs[i+l];
		p0 = prixs[i];
		//
		_f = f(mdl, i);
		//
		if (*_gain > 0) {
			*_gain += (*_gain) * _f * LEVIER * (p1/p0 - 1.0);
		} else {
			*_gain = 0;
		}

		if (signe(p1/p0-1.0) == signe(_f)) {
			*_pred += 1.0;
			if (_f != 0) *_invest += 1.0;
		}

		i += l;

		t++;
		if (_f != 0) _t++;

		i += 5;//*(1+rand()%10);
	};

	*_gain -= USDT;
	*_pred /= (float)t;
	*_invest /= (float)_t;

	*_gain_168H = USDT;
	FOR(JUSQUE, i, PRIXS-1-l) {
		p1 = prixs[i+l];
		p0 = prixs[i];
		//
		_f = f(mdl, i);
		//
		if (*_gain_168H > 0) {
			*_gain_168H += (*_gain_168H) * _f * 25 * (p1/p0 - 1.0);
		} else {
			*_gain_168H = 0;
		}
		if (*_gain_168H<0) {*_gain_168H=0;break;};
		//
		i += l;
	};
	*_gain_168H -= USDT;
};

float gain_JUSQUE_PRIXS(Mdl_t * mdl, uint l, float __LEVIER) {
	float _gain = USDT;
	//
	float _f, p0, p1;
	uint t=0;
	UNE_COURBE(p);
	for (uint i=JUSQUE; i < PRIXS-1-l; i++) {
		p1 = prixs[i+l];
		p0 = prixs[i];
		//
		_f = /*signe*/( f(mdl, i) );
		//
		if (_gain > 0) {
			_gain += _gain * _f * __LEVIER * (p1/p0 - 1.0);
		} else {
			return -USDT;
		}
		i += l;
		SUIVIE_COURBE(p, _gain);
	};
	PLUMER_LA_COURBE(p);
	gnuplot(prixs + JUSQUE, PRIXS-JUSQUE-2, "prixs 168H");

	return _gain - USDT;
};

float gain_168H(Mdl_t * mdl, uint l) {
	float _gain = USDT;
	//
	float _f, p0, p1;
	uint t=0;
	//UNE_COURBE(p);
	for (uint i=JUSQUE; i < PRIXS-1-l; i++) {
		p1 = prixs[i+l];
		p0 = prixs[i];
		//
		_f = /*signe*/( f(mdl, i) );
		//
		if (_gain > 0) {
			_gain += _gain * _f * 25 * (p1/p0 - 1.0);
		} else {
			return -USDT;
		}
		i += l;
	//	SUIVIE_COURBE(p, _gain);
	};
	//PLUMER_LA_COURBE(p);
	//gnuplot(prixs + JUSQUE, PRIXS-JUSQUE-2, "prixs 168H");

	return _gain - USDT;
}