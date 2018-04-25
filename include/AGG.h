#ifndef __AGG__H
#define __AGG__H

#include <cmath>
#include <vector>
#include <utility>
#include <iostream>
#include "generador.h"
#include "clasificador.h"


#define TAM_POPULATION    10
#define PMUTATION         0.01
#define PCRUZE            0.7
#define MAXITERATION      15000
#define TOLERANCE         0.00000001

using namespace std;
/***************************************
*   DEFINICIONES DE GENES y FUNCIONES  *
****************************************/
typedef float TipoGen;

/* tipo de dato del cromosoma */
typedef vector<TipoGen> Cromosoma;

/* each member of the population has this form */
typedef struct {
	Cromosoma Genes;
	float Perf;
   int n_e;
} especimen;

/* the best structures are saved in the following record */
typedef struct {
	vector<short int> Gene;
	float Perf;
	int Gen;
	int Trials;
} mejor_ejemplar;


bool operator > (especimen p1, especimen p2);
ostream& operator << (ostream& o,especimen esp);
/**************************************************/

class AG{
protected:
    vector<especimen> population;

	//Necesario para la llamada al KNN y la clasificacion de los datos
	vector<int> trainData;
	vector<int> testData;
	vector<vector<float>> dataMatrix;
	vector<int> realLabels;

	//Utiles
	unsigned int numberOfCharac;
	vector<especimen>::iterator the_best, the_worst;
	especimen predecesor;
public:
	AG();
	AG(  const vector<int> &train,
		 const vector<int> &test,
		 const vector<vector<float>> &matrixData,
		 const vector<int> &vectorLabel);

	//virtual void reemplazar(vector<especimen> new_population);
    vector<especimen>::iterator Torneo(vector<especimen>::iterator p1, vector<especimen>::iterator p2);
	void Mutate();
	pair<especimen,especimen> Crossover(vector<especimen>::iterator padre, vector<especimen>::iterator madre);
	void initialize();
	void OrdenateValue();
};

class AGG: public AG{
private:

public:
	AGG();
	AGG( const vector<int> &train,
		 const vector<int> &test,
		 const vector<vector<float>> &matrixData,
		 const vector<int> &vectorLabel);

	vector<especimen> Selection();
	void Reemplazar();
	vector<especimen>::iterator getBest();
};

class AGE: private AG{
private:

public:
	AGE();
	AGE( const vector<int> &train,
		 const vector<int> &test,
		 const vector<vector<float>> &matrixData,
		 const vector<int> &vectorLabel);

	vector<especimen> Selection();
	void Reemplazar();
	vector<especimen>::iterator getBest();
};


#endif
