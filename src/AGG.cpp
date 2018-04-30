#include "AGG.h"

using namespace std;


//FUNCIONES DE LOS ESPECIMENES
bool operator > (especimen p1, especimen p2){ return p1.Perf > p2.Perf;}
ostream& operator << (ostream& o,especimen esp){

  o << "Valor: " << esp.Perf << endl;

  for(unsigned int i = 0; i < esp.Genes.size(); i++){
    o <<" " <<esp.Genes[i];
  }

  o << endl;

  return o;
}
///////////////////////////////////////////////////////////////////////


AG::AG(){/*default constructor*/}
AG::AG(const vector<int> &train,
       const vector<int> &test,
       const vector<vector<float>> &matrixData,
       const vector<int> &vectorLabel):trainData(train),testData(test),dataMatrix(matrixData),realLabels(vectorLabel)
   {numberOfCharac = matrixData[0].size();}

/********************************
*@brief Funcion de torneo la cual devuelve el mas bueno de los presentados a torneo
*
*@parameter iterador del primer padre y iterador al segundo padre
*
*@return el iterador del mejor de los dos padres
*********************************/
vector<especimen>::iterator AG::Torneo(vector<especimen>::iterator p1, vector<especimen>::iterator p2){
  if((*p1).Perf >= (*p2).Perf)
    return p1;

  return p2;
}

/*******************************
*@brief Funcion de mutacion de los especimenes
*       muta los individuos de la poblacion
*       todo en funcion de la constante definida
*       como PMUTATION.
********************************/
void AG::Mutate(){//Tira un random y con este lo haces todo
  float        aleatorio      = Rand();
  unsigned int characToChange = Randint(0,numberOfCharac);
  float        alteration     = (aleatorio * 2) - 1; //Rango de valores entre [-1,1]
  unsigned int sizeToChange   = ceil(PMUTATION* (float)TAM_POPULATION)-1;
  unsigned int currentPoint     = ceil(aleatorio * (TAM_POPULATION-1));

  //cout << "Valor de size to change " << sizeToChange <<"  valor real "<< PMUTATION* (float)TAM_POPULATION <<endl;
  //cout << "Valor de Punto " << currentPoint <<"  valor real "<< aleatorio * (TAM_POPULATION-1) <<endl;
  if(sizeToChange < 1){
    //cout << "\nEl valor de size to change es pequeño para la poblacion " << sizeToChange;
    if(aleatorio < PMUTATION){
      sizeToChange = 1;
      //cout << "\nSe ha decidido mutar";
    }
  }

  //cout << "\nNumero de caracteristica:" <<numberOfCharac<< endl;
  while(sizeToChange > 0){
    //cout << "MIEMBRO ELEGIDO: " << currentPoint << endl;
    //cout << population[currentPoint];
    //cout << "\nMiembro a cambiar: " << currentPoint << "/" << population.size();
    //cout << "\nValor del gen: " << population[currentPoint].Genes[characToChange] << endl;
    population[currentPoint].Genes[characToChange] =
                              population[currentPoint].Genes[characToChange] +
                              (alteration * population[currentPoint].Genes[characToChange]);

    if(population[currentPoint].Genes[characToChange] > 1)
      population[currentPoint].Genes[characToChange] = 1.0;

    population[currentPoint].Perf = KNN(trainData,testData,dataMatrix,realLabels,population[currentPoint].Genes,0.2);
    //cout << "\nValor cambiado: " << population[currentPoint].Genes[characToChange] << endl;
    //cout<< "\nLa variable "<< characToChange<<" Cambiado a: \n" << population[currentPoint];
    sizeToChange--;
    //cout << "\nValor de characToChange: " << characToChange << "  characToChange++:"<<characToChange+1;
    characToChange = (characToChange+1) % numberOfCharac;
    //cout << " \nValor tras el cambio: " << population[currentPoint].Perf;
    currentPoint = (currentPoint+1) % TAM_POPULATION;
  }
}
/*******************************
*@brief Inicializador de la poblacion
********************************/
void AG::initialize(){
  //cout << "\nNumero de caracteristicas: " << numberOfCharac << endl;
  //cout << "\nTamano de la matrix: (" << dataMatrix[0].size() << "," << realLabels.size() << ")" << endl;

  for(unsigned int i= 0; i < TAM_POPULATION; i++){
    vector<float> Gen;
    for (unsigned int j = 0; j < numberOfCharac; j++){
      Gen.push_back(Rand());
    }
    especimen nuevo ;
    nuevo.Genes = Gen;
    nuevo.Perf  = KNN(trainData,testData,dataMatrix,realLabels,Gen,0.2);//Esta linea hay que cambiarla y añaidir el KNN
    nuevo.n_e   = 0;

    population.push_back(nuevo);
    //cout << "\n\tNUEVO ESPECIMEN\n" << nuevo;
  }

  //cout << "\nTamaño de la poblacion: " << population.size() << endl;
}
/*******************************
*@brief Operador de cruze para el problema con
*     variables reales usando el aritmetico con un
*     desplazamiento de 0.3 y 0.7
********************************/
pair<especimen,especimen> AG::Crossover (vector<especimen>::iterator padre, vector<especimen>::iterator madre){
  pair<especimen,especimen> result;
  especimen Hijo1,Hijo2;
  float max,min;
  float sigma = 0.3, inv_sig= 1 - sigma;
  float hijo_1_result, hijo_2_result;
  float dif;
  //Cruze BLX con sigma = 0.3

  for(unsigned int i = 0; i < numberOfCharac; i++){
      if((*padre).Genes[i]>=(*madre).Genes[i]){
        max = (*padre).Genes[i];
        min = (*madre).Genes[i];
      }else{
        max = (*madre).Genes[i];
        min = (*padre).Genes[i];
      }

      dif = max - min;

      hijo_1_result = min + (dif*sigma);
      hijo_2_result = min + (dif*inv_sig);

      Hijo1.Genes.push_back(hijo_1_result);
      Hijo2.Genes.push_back(hijo_2_result);
  }
  Hijo1.Perf = KNN(trainData,testData,dataMatrix,realLabels,Hijo1.Genes,0.2); //Linea a cambiar
  Hijo2.Perf = KNN(trainData,testData,dataMatrix,realLabels,Hijo2.Genes,0.2); //Linea a cambiar

  result = make_pair(Hijo1,Hijo2);
  return result;
}
/*********************************
* sigma con valor de 0.3
*********************************/
pair<especimen,especimen> AG::BLX (vector<especimen>::iterator padre, vector<especimen>::iterator madre){
  pair<especimen,especimen> result;
  especimen Hijo1,Hijo2;
  float max,min;
  float dif;
  float sig = 0.3;
  float random = Rand();
  float hijo_1_result,hijo_2_result;
  //Cruze BLX con sigma = 0.3

  for(unsigned int i = 0; i < numberOfCharac; i++){
      if((*padre).Genes[i]>=(*madre).Genes[i]){
        max = (*padre).Genes[i];
        min = (*madre).Genes[i];
      }else{
        max = (*madre).Genes[i];
        min = (*padre).Genes[i];
      }

      dif = max - min;
      dif = (max + sig*dif) - (min - sig*dif);

      hijo_1_result = min + (dif*random);
      hijo_2_result = min + (dif*1-random);

      Hijo1.Genes.push_back(hijo_1_result);
      Hijo2.Genes.push_back(hijo_2_result);
  }
  Hijo1.Perf = KNN(trainData,testData,dataMatrix,realLabels,Hijo1.Genes,0.2); //Linea a cambiar
  Hijo2.Perf = KNN(trainData,testData,dataMatrix,realLabels,Hijo2.Genes,0.2); //Linea a cambiar

  result = make_pair(Hijo1,Hijo2);
  return result;
}
/*******************************
*@brief Ordena los especimenes de la poblacion asignando en su variable n_e
*     el valor que tendrían ademas de indicar cual es el mejor.
********************************/
void AG::OrdenateValue(){
  int best;
  float perf;

  for (unsigned int i=0;i<TAM_POPULATION;i++)
    population[i].n_e=0;


  for(unsigned int i = 0; i < TAM_POPULATION; i++){
    best = -1;
    perf = 0.0;

    for(unsigned int j=0;j<TAM_POPULATION;j++)
    {
      if(population[j].n_e==0 && (best == -1 || (population[j].Perf > perf) )){
        perf = population[j].Perf;
        best = j;
      }
    }

    population[best].n_e = TAM_POPULATION - 1 - i;
    if(i == 0){
      the_best = population.begin() + best;
    }else if(i == (TAM_POPULATION - 1)){
      the_worst = population.begin() + best;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////

AGG::AGG(){//Default Constructor
}
AGG::AGG(
   const vector<int> &train,
   const vector<int> &test,
   const vector<vector<float>> &matrixData,
   const vector<int> &vectorLabel):AG(train,test,matrixData,vectorLabel){}

/*******************************
*@brief Método de seleccion estocastico de baker
*     usando la Ruleta , lo dividimos en 6 partes
*     cada parte sacamos un miembro y lo usamos
********************************/
vector<especimen> AGG::Selection(){
  vector<especimen> result;
  int Total = TAM_POPULATION - 1;
  int NumberOfSector = TAM_POPULATION*2;
  float Distance;
  float start = Rand() * Distance;
  float Pointer = 0.0;
  float sum;
  unsigned int j = 0;
  unsigned int i = 0;


  Distance = (float)Total/(float)NumberOfSector;
  //cout << "Valor de Total: " << Total << " Valor de Num: " << NumberOfSector << endl;
  //cout << "Valor de Distance: " << Distance << " Valor de start: " << start << endl;
  for (; i < NumberOfSector; i++){
    Pointer = start + i*Distance;
    sum = 0.0;
    //cout << "Valor de j: " << j << " ";
    //cout << "Valor de Pointer: " << Pointer << " ";
    for(; sum < Pointer; j++){
      sum += population[j].n_e;
      if(j > TAM_POPULATION-1)
        j = 0;
    }
    result.push_back(population[j]);
  }
  //cout << "Salida\n";

  return result;
}

void AGG::Reemplazar(){
  vector<especimen> result;
  predecesor = (*the_best);
  population = Selection();
  vector<especimen>::iterator it= population.begin();
  for(unsigned int i = 0; i < population.size()-3; i=i+4){
    vector<especimen>::iterator p1=it,p2=it+1,p3=it+2,p4=it+3;
    pair<especimen,especimen> hijos = Crossover(Torneo(p1,p2),Torneo(p3,p4));
    result.push_back(hijos.first);
    result.push_back(hijos.second);
    it = it + 4;
  }

  population = result;
  OrdenateValue();
  (*the_worst) = predecesor;
  OrdenateValue();//Podemos cambiarlo para ser mucho mas eficiente

}

vector<especimen>::iterator AGG::getBest(){
  return the_best;
}

////////////////////////////////////////////////////////////////////////////////////
AGE::AGE(){//Default Constructor
}
AGE::AGE(
   const vector<int> &train,
   const vector<int> &test,
   const vector<vector<float>> &matrixData,
   const vector<int> &vectorLabel):AG(train,test,matrixData,vectorLabel){}

vector<especimen>::iterator AGE::getBest(){
  return the_best;
}

vector<especimen> AGE::Selection(){
  vector<especimen> result;
  int Total = TAM_POPULATION - 1;
  int NumberOfSector = (1*2)*2;
  float Distance;
  float start = Rand() * Distance;
  float Pointer = 0.0;
  float sum;
  unsigned int j = 0;
  unsigned int i = 0;


  Distance = (float)Total/(float)NumberOfSector;
  //cout << "Valor de Total: " << Total << " Valor de Num: " << NumberOfSector << endl;
  //cout << "Valor de Distance: " << Distance << " Valor de start: " << start << endl;
  for (; i < NumberOfSector; i++){
    Pointer = start + i*Distance;
    sum = 0.0;
    //cout << "Valor de j: " << j << " ";
    //cout << "Valor de Pointer: " << Pointer << " ";
    for(; sum < Pointer; j++){
      sum += population[j].n_e;
      if(j > TAM_POPULATION-1)
        j = 0;
    }
    result.push_back(population[j]);
  }
  //cout << "Salida\n";

  return result;
}

void AGE::Find_Dirty(vector<especimen>::iterator &w1,
                        vector<especimen>::iterator &w2){


  for(unsigned int i = 0; i < TAM_POPULATION; i++){

    if(population[i].n_e == (TAM_POPULATION - 1)){
      the_best= population.begin() + i;
    }else if(population[i].n_e == 0){
      w1 = population.begin() + i;
    }else if(population[i].n_e == 1){
      w2 = population.begin() + i;
    }
  }
}

void AGE::Reemplazar(){
  Find_Dirty(the_worst,the_second_worst);
  vector<especimen> selected = Selection();
  vector<especimen>::iterator it= selected.begin();
  pair<especimen,especimen> hijos = Crossover(Torneo(it,it + 1),Torneo(it + 2,it + 4));

  // Nos apoyamos en el orden implicito de los operandos entonces solo hay
  // Tres casos posibles
  // -Los dos mayores
  // -Uno mayor
  // -Ninguno mayor
  if (hijos.first.Perf > (*the_second_worst).Perf){
    if(hijos.second.Perf > (*the_second_worst).Perf){
      (*the_worst) = hijos.first;
      (*the_second_worst) = hijos.second;
    }else {
      (*the_worst) = hijos.first;
    }
  }else if (hijos.second.Perf > (*the_second_worst).Perf){
    (*the_worst) = hijos.second;
  }else if (hijos.first.Perf > hijos.second.Perf){
    if (hijos.first.Perf > (*the_worst).Perf)
      (*the_worst) = hijos.first;
  }else{
    if (hijos.second.Perf > (*the_worst).Perf)
      (*the_worst) = hijos.second;
  }

  OrdenateValue();//Podemos cambiarlo para ser mucho mas eficiente

}
