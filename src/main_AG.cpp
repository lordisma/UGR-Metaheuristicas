# include <iostream>
# include "AGG.h"
# include <vector>
# include "generador.h"
# include "datos.h"
# include "temporizador.h"


int main(){
  float tMedio = 0.0, tasaMedia = 0.0;
  string file_name = "";
  unsigned long semilla = 20000913;
  Set_random(semilla);
  Datos conjuntoDatos;
  vector<especimen> Selected_especimen;
  bool End = false;

  cout << "----------------------------------------------" << endl;
  cout << "Leyendo, normalizando y particionando datos Spectf-Heart..." << endl;
  conjuntoDatos.leerDatos("../data/spectf-heart.arff");
  file_name = "Spect_Heart";

  cout << "------------------------------------------------" << endl;
  cout << "                   INICIO                       " << endl;
  AGE genetic(conjuntoDatos.getParticionTrain(1),conjuntoDatos.getParticionTest(1),conjuntoDatos.getDatos(),conjuntoDatos.getEtiquetas());
  genetic.initialize();
  genetic.OrdenateValue();
  cout << "------------------------------------------------" << endl;
  cout << "               GEN GENERACIONAL                 " << endl;

  //cout << "Miembros de las seleccionados" << endl;
  for(unsigned int i = 0; i < 10000 && !End; i++){
    cout << "\nNUEVO REEMPLAZAMIENTO nº"<< i << endl;
    genetic.Reemplazar();
    genetic.Mutate();
    if(KNN( conjuntoDatos.getParticionTrain(1),
            conjuntoDatos.getParticionTest(1),
            conjuntoDatos.getDatos(),
            conjuntoDatos.getEtiquetas(),
            (*genetic.getBest()).Genes,   0.2) > 90){
      End = true;
    }

  }

  cout << "\n\nEl valor devuelto es " << (*genetic.getBest()) << endl;

  //for(vector<especimen>::iterator it = result.begin(); it != result.end(); it++){
  //  cout << endl << (*it);
  //}
/*
  vector<float> pesos(conjuntoDatos.getTamAtributos(), 1.0);
  float tasa;

  for(int i = 0; i < 5; ++i){
    Temporizador temp;
    cout << "----------------------------------------------" << endl;
    cout << "Comienzo del procesamiento de la" << endl << "particion " << i+1 << ":" << endl;
    temp.start();
    tasa = KNN(conjuntoDatos.getParticionTrain(i+1), conjuntoDatos.getParticionTest(i+1), conjuntoDatos.getDatos(), conjuntoDatos.getEtiquetas(), pesos);
    temp.stop();
    tMedio += temp.getTime();
    tasaMedia += tasa;
    cout << "\tPorcentaje Acierto: " << tasa << "%" << endl;
    cout << "\tTiempo Ejecucion: " << temp.getTime() << " seg." << endl;
    cout << "\tTasa Reduccion: 0%" << endl;
    cout << "\tAgregacion: " << (float)0.5 * (float)tasa << " % " << endl;

  }
*/

}