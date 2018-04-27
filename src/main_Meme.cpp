# include <iostream>
# include "Memetico.h"
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
  Memetico genetic(conjuntoDatos.getParticionTrain(1),conjuntoDatos.getParticionTest(1),conjuntoDatos.getDatos(),conjuntoDatos.getEtiquetas());
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

    if((i%10) == 0){
      genetic.BL_to_Best();
    }

  }

  cout << "\n\nEl valor devuelto es " << (*genetic.getBest()) << endl;


}
