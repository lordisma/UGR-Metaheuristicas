# include <iostream>
# include "Memetico.h"
# include <vector>
# include "generador.h"
# include "datos.h"
# include "temporizador.h"
# include "clasificador.h"


int main(int argc, char* argv[]){
  float tMedio = 0.0, tasaMedia = 0.0;
  string file_name = "";
  unsigned long semilla = 20000913;
  Set_random(semilla);
  Datos conjuntoDatos;
  vector<especimen> Selected_especimen;
  bool End = false;

  unsigned int data_number;

  if(argc != 2){
    return 1;
  }else{
    data_number = stoi(argv[1]);
    cout << data_number<< endl;
  }

  switch(data_number){
    case 1:{
      cout << "----------------------------------------------" << endl;
      cout << "Leyendo, normalizando y particionando datos Ozone..." << endl;
      conjuntoDatos.leerDatos("../data/ozone-320.arff");
      file_name = "Ozone";
      break;
    }
    case 2:{
      cout << "----------------------------------------------" << endl;
      cout << "Leyendo, normalizando y particionando datos Parkinsons..." << endl;
      conjuntoDatos.leerDatos("../data/parkinsons.arff");
      file_name = "Parkinsons";
      break;
    }
    case 3:{
      cout << "----------------------------------------------" << endl;
      cout << "Leyendo, normalizando y particionando datos Spectf-Heart..." << endl;
      conjuntoDatos.leerDatos("../data/spectf-heart.arff");
      file_name = "Spect_Heart";
      break;
    }

    default:{
      return 1;
    }
  }

  float  tasa = 0.0;
  int pesosDescartados = 0;

  for(unsigned int j = 0; j < 5; j++){
  Temporizador temp;
  cout << "------------------------------------------------" << endl;
  cout << "                   INICIO                       " << endl;
  Memetico genetic(conjuntoDatos.getParticionTrain(j),conjuntoDatos.getParticionTest(j),conjuntoDatos.getDatos(),conjuntoDatos.getEtiquetas());
  genetic.initialize();
  genetic.OrdenateValue();
  cout << "------------------------------------------------" << endl;
  cout << "               GEN GENERACIONAL                 " << endl;

  temp.start();
  //cout << "Miembros de las seleccionados" << endl;
  for(unsigned int i = 0; i < 10000 && !End; i++){
    //cout << "\nNUEVO REEMPLAZAMIENTO nº"<< i << endl;
    genetic.Reemplazar();
    genetic.Mutate();
    if(KNN( conjuntoDatos.getParticionTrain(j),
            conjuntoDatos.getParticionTest(j),
            conjuntoDatos.getDatos(),
            conjuntoDatos.getEtiquetas(),
            (*genetic.getBest()).Genes,   0.2) > 90){
      End = true;
    }

    if((i%10) == 0){
      genetic.BL_to_best();
    }

  }

  temp.stop();
  tasa = (*genetic.getBest()).Perf;
  tasaMedia += tasa;
  tMedio += temp.getTime();
  pesosDescartados = 0;

  for(unsigned int t = 0; t < (*genetic.getBest()).Genes.size(); t++){
    if ((*genetic.getBest()).Genes[t] < 0.2)
      pesosDescartados ++;
  }

  double tasaReduccion = (float)100.0 * ((float)pesosDescartados/(float)(*genetic.getBest()).Genes.size());
  cout << "\tPorcentaje Acierto: " << tasa << "%" << endl;
  cout << "\tTiempo Ejecucion: " << temp.getTime() << " seg." << endl;
  cout << "\tTasa Reduccion: " << tasaReduccion << "%" << endl;
  cout << "\tAgregacion: " << (float)0.5 * (float)tasa + (float)0.5 * (float)tasaReduccion << " % " << endl;

  }

  cout << endl << "ACIERTO MEDIO: " << tasaMedia/5 << endl;
  cout << "TIEMPO MEDIO: " << tMedio/5 << endl;
}
