# include <iostream>
# include "AGG.h"
# include <vector>
# include "generador.h"
# include "datos.h"
# include "temporizador.h"


int main(int argc, char* argv[]){
  float tMedio = 0.0, tasaMedia = 0.0;
  string file_name = "";
  unsigned long semilla = 50627728;
  Set_random(semilla);
  Datos conjuntoDatos;
  vector<especimen> Selected_especimen;
  bool End = false;
  unsigned int data_number, kind_genetic;

  if(argc != 3){
    return 1;
  }else{
    data_number = stoi(argv[1]);
    kind_genetic= stoi(argv[2]);
  }

  cout << "----------------------------------------------" << endl;
  cout << "Semilla Escogida: " << semilla << endl;

  switch(data_number){
    case 1:{
      cout << "----------------------------------------------" << endl;
      cout << "Archivo de Datos: Ozone" << endl;
      cout << "----------------------------------------------" << endl;
      cout << "Leyendo, normalizando y particionando datos Ozone..." << endl;
      conjuntoDatos.leerDatos("../data/ozone-320.arff");
      file_name = "Ozone";
      break;
    }
    case 2:{
      cout << "----------------------------------------------" << endl;
      cout << "Archivo de Datos: Parkisons" << endl;
      cout << "----------------------------------------------" << endl;
      cout << "Leyendo, normalizando y particionando datos Parkinsons..." << endl;
      conjuntoDatos.leerDatos("../data/parkinsons.arff");
      file_name = "Parkinsons";
      break;
    }
    case 3:{
      cout << "----------------------------------------------" << endl;
      cout << "Archivo de Datos: Spectf-Heart" << endl;
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

if (kind_genetic == 1){
  cout << "----------------------------------------------" << endl;
  cout << "Algoritmo: Genetico Generacional" << endl;

  for(unsigned int j = 0; j < 5; j++){
    End = false;
    Temporizador temp;
    cout << "----------------------------------------------" << endl;
    cout << "Comienzo del procesamiento de la" << endl;
    cout << "particion " << j+1 << ":" << endl;
    AGG genetic(conjuntoDatos.getParticionTrain(j),conjuntoDatos.getParticionTest(j),conjuntoDatos.getDatos(),conjuntoDatos.getEtiquetas());
    genetic.initialize();
    genetic.OrdenateValue();

    temp.start();
    //cout << "Miembros de las seleccionados" << endl;
    for(unsigned int i = 0; i < 15000 && !End; i++){
      //cout << "\nNUEVO REEMPLAZAMIENTO nº"<< i << endl;
      //cout << endl << "El valor en la iteracion " << i << " es " << (genetic.getBest()).Perf;
      genetic.Reemplazar();
      //cout << "\nIntento de mutacion";
      genetic.Mutate();
      //genetic.OrdenateValue();
      if( (genetic.getBest()).Perf > 90){
        End = true;
      }
      //cout << "\nFin iteracion";

    }

    temp.stop();
    //tasa = (*genetic.getBest()).Perf;
    tasa = KNN( conjuntoDatos.getParticionTrain(j),
            conjuntoDatos.getParticionTest(j),
            conjuntoDatos.getDatos(),
            conjuntoDatos.getEtiquetas(),
            (genetic.getBest()).Genes,   0.2);
    tasaMedia += tasa;
    tMedio += temp.getTime();
    pesosDescartados = 0;

    for(unsigned int t = 0; t < (genetic.getBest()).Genes.size(); t++){
      if ((genetic.getBest()).Genes[t] < 0.2)
        pesosDescartados ++;
    }

    double tasaReduccion = (float)100.0 * ((float)pesosDescartados/(float)(genetic.getBest()).Genes.size());
    cout << "\tPorcentaje Acierto: " << tasa << "%" << endl;
    cout << "\tTiempo Ejecucion: " << temp.getTime() << " seg." << endl;
    cout << "\tTasa Reduccion: " << tasaReduccion << "%" << endl;
    cout << "\tAgregacion: " << (float)0.5 * (float)tasa + (float)0.5 * (float)tasaReduccion << " % " << endl;

  }
}else{
  cout << "----------------------------------------------" << endl;
  cout << "Algoritmo: Genetico Estacional" << endl;

  for(unsigned int j = 0; j < 5; j++){
    End = false;
    Temporizador temp;
    cout << "----------------------------------------------" << endl;
    cout << "Comienzo del procesamiento de la" << endl;
    cout << "particion " << j + 1 << ":" << endl;
    AGE genetic(conjuntoDatos.getParticionTrain(j),conjuntoDatos.getParticionTest(j),conjuntoDatos.getDatos(),conjuntoDatos.getEtiquetas());
    genetic.initialize();
    genetic.OrdenateValue();

    temp.start();
    //cout << "Miembros de las seleccionados" << endl;
    for(unsigned int i = 0; i < 15000 && !End; i++){
      //cout << "\nNUEVO REEMPLAZAMIENTO nº"<< i << endl;
      genetic.Reemplazar();
      genetic.Mutate();
    //  cout << endl << (genetic.getBest()).Perf << endl;
      if( (genetic.getBest()).Perf > 90){
        End = true;
      }

    }
    temp.stop();
    //tasa = (*genetic.getBest()).Perf;
    tasa = KNN( conjuntoDatos.getParticionTrain(j),
            conjuntoDatos.getParticionTest(j),
            conjuntoDatos.getDatos(),
            conjuntoDatos.getEtiquetas(),
            (genetic.getBest()).Genes,   0.2);
    tasaMedia += tasa;
    tMedio += temp.getTime();
    pesosDescartados = 0;

    for(unsigned int t = 0; t < (genetic.getBest()).Genes.size(); t++){
      if ((genetic.getBest()).Genes[t] < 0.2)
        pesosDescartados ++;
    }

    double tasaReduccion = (float)100.0 * ((float)pesosDescartados/(float)(genetic.getBest()).Genes.size());
    cout << "\tPorcentaje Acierto: " << tasa << "%" << endl;
    cout << "\tTiempo Ejecucion: " << temp.getTime() << " seg." << endl;
    cout << "\tTasa Reduccion: " << tasaReduccion << "%" << endl;
    cout << "\tAgregacion: " << (float)0.5 * (float)tasa + (float)0.5 * (float)tasaReduccion << " % " << endl;

  }
}
cout << "----------------------------------------------" << endl;
cout << "----------------------------------------------" << endl;
cout << "Porcentaje Medio de Acierto: " << tasaMedia/5 << endl;
cout << "Tiempo Medio de Ejecucion: " << tMedio/5 << endl;

}
