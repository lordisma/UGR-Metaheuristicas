#ifndef __MEMETICO_H
#define __MEMETICO_H

#include "AGG.h"
#include "localsearch.h"
#include "generador.h"


using namespace std;

class Memetico: public AGG{
public:
	Memetico();
	Memetico(const vector<int> &train,
		 const vector<int> &test,
		 const vector<vector<float>> &matrixData,
		 const vector<int> &vectorLabel);
	void BL_to_best();
	void BL_to_rand();
	void BL_to_All();
};

#endif
