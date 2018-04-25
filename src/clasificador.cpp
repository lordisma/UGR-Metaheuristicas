#include <clasificador.h>

using namespace std;

float euclideanDistance(const vector<float> &train, const vector<float> &test, const vector<float> &weights, float limit){
	int trainSize = train.size();
	float distance = 0.0;
	for(int i = 0; i < trainSize; ++i){
		if(weights[i] >= limit){
			distance += (weights[i]*((test[i]-train[i])*(test[i]-train[i])));
		}
	}
	return sqrt(distance);
}

float KNN(const vector<int> &train, const vector<int> &test, vector<vector<float>> matrixData, vector<int> vectorLabel, const vector<float> &weights, float limit){
	int success = 0, label = vectorLabel[0], trainSize = train.size(), testSize = test.size();
	float distance = 0.0, minDistance;
	for(int i = 0; i < trainSize; ++i){
		minDistance = 999999;
		for(int j = 0; j < testSize; ++j){
			if(train[i] != test[j]){
				distance = euclideanDistance(matrixData[train[i]], matrixData[test[j]], weights, limit);
				if(distance < minDistance){
					minDistance = distance;
					label = vectorLabel[test[j]];
				}
			}
		}
		if(label == vectorLabel[train[i]]){
			success++;
		}
	}

	//cout << "\n Numero de exitos: " << success;
	return (100.0 * (success * (1.0/trainSize)));
}
