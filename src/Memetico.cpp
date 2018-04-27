#include "Memetico.h"

#define PER_BEST 0.1
#define PER_RAND 0.1

Memetico::Memetico(){}

Memetico::Memetico(const vector<int> &train,
   const vector<int> &test,
   const vector<vector<float>> &matrixData,
   const vector<int> &vectorLabel):AG(train,test,matrixData,vectorLabel){}

void Memetico::BL_to_best(){
  int discriminante = ceil( PER_BEST * TAM_POPULATION );
  int limite        = TAM_POPULATION - discriminante;

  for(unsigned int i = 0; i < TAM_POPULATION; i++){
    if( population[i].n_e >= limite){
      LocalSearch(trainData,dataMatrix,realLabels,2*numberOfCharac,population[i].Genes);
      population[i].Perf = KNN(trainData,testData,dataMatrix,realLabels,population[i].Genes,0.2);
    }
  }

  OrdenateValue();
}

void Memetico::BL_to_rand(){
  int tamToChange = ceil( PER_RAND * TAM_POPULATION );
  int pointer     = Randint(0,TAM_POPULATION-1);

  for(unsigned int i = 0; i < tamToChange; i++){
      LocalSearch(trainData,dataMatrix,realLabels,2*numberOfCharac,population[pointer].Genes);
      pointer = pointer + 1;
      pointer = pointer % TAM_POPULATION;
      population[i].Perf = KNN(trainData,testData,dataMatrix,realLabels,population[pointer].Genes,0.2);
  }

  OrdenateValue();
}

void Memetico::BL_to_All(){
  for(unsigned int i = 0; i < TAM_POPULATION; i++){
    LocalSearch(trainData,dataMatrix,realLabels,2*numberOfCharac,population[i].Genes);
    population[i].Perf = KNN(trainData,testData,dataMatrix,realLabels,population[i].Genes,0.2);
  }
  OrdenateValue();
}
