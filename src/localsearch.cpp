#include <localsearch.h>

using namespace std;

default_random_engine normalGenerator;
normal_distribution<double> normalDistribution(0.0, 0.3);

void neighboursGeneration(vector<float> &weights, const int &component){
	weights[component] += normalDistribution(normalGenerator);
	if(weights[component] > 1){
		weights[component] = 1;
	}else if(weights[component] < 0){
		weights[component] = 0;
	}
}

void LocalSearch(const vector<int> &train, const vector<vector<float>> matrixData, const vector<int> vectorLabel, const int &generatedNeighbours, vector<float> &weights, int iterations){
	int neighbours = 0, evaluations = 0, weightsSize = weights.size();
	bool improvement = false;
	vector<int> index(weightsSize, 0);
	iota(index.begin(), index.end(), 0);
	vector<float> actualSolW(weights.begin(), weights.end()), newSolW(weights.begin(), weights.end());
	float actualSol = -999999, newSol = -999999;
	actualSol = KNN(train, train, matrixData, vectorLabel, actualSolW, 0.2);
	while(evaluations < iterations && neighbours < generatedNeighbours){
		random_shuffle(index.begin(), index.end());
		improvement = false;
		for(int i = 0; i < weightsSize && !improvement; ++i){
			neighboursGeneration(newSolW, index[i]);
			neighbours++;
			newSol =  KNN(train, train, matrixData, vectorLabel, newSolW, 0.2);
			evaluations++;
			if(newSol > actualSol){
				actualSol = newSol;
				actualSolW = newSolW;
				improvement = true;
			}
		}
	}
	weights = actualSolW;
}
