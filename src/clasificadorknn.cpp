#include <clasificador.h>
#include <datos.h>
#include <generador.h>
#include <iostream>
#include <localsearch.h>
#include <relief.h>
#include <temporizador.h>

#include <fstream> // Generacion de los archivos csv

using namespace std;

void FillCsv(ofstream &file_csv, vector<float> data, unsigned int length_line){
		for(unsigned int i = 0; i < data.size()-1; i++){
			if((i % length_line) == 0)
				file_csv << "\n";

			file_csv << data[i] << ",";
		}

		file_csv << data[data.size()-1];

}

int getFromFile(string path, int &optionFile, int &optionAlgorithm, unsigned long &chosenSeed){
	ifstream file(path);
	string row;
	getline(file, row, ' ');
	optionFile = stoi(row);
	if(optionFile != 1 && optionFile != 2 && optionFile != 3){
		file.close();
		cout << "Error al escoger el archivo" << endl;
		cout << "1 -> Ozone" << endl;
		cout << "2 -> Parkinsons" << endl;
		cout << "3 -> Spectf-Heart" << endl;
		return 0;
	}
	getline(file, row, ' ');
	optionAlgorithm = stoi(row);
	if(optionAlgorithm != 1 && optionAlgorithm != 2 && optionAlgorithm != 3){
		file.close();
		cout << "Error al escoger el algoritmo" << endl << "1 -> 1-NN" << endl;
		cout << "2 -> Busqueda Local" << endl << "3 -> Greedy Relief" << endl;
		return -1;
	}
	getline(file, row);
	unsigned long auxSeed = stoul(row);
	if(auxSeed != 0){
		chosenSeed = auxSeed;
	}
	file.close();
	switch(optionFile){
		case 1:{
			cout << "----------------------------------------------" << endl;
			cout << "Archivo de Datos: Ozone" << endl;
			break;
		}
		case 2:{
			cout << "----------------------------------------------" << endl;
			cout << "Archivo de Datos: Parkisons" << endl;
			break;
		}
		case 3:{
			cout << "----------------------------------------------" << endl;
			cout << "Archivo de Datos: Spectf-Heart" << endl;
			break;
		}
	}
	switch(optionAlgorithm){
		case 1:{
			cout << "----------------------------------------------" << endl;
			cout << "Algoritmo: 1-NN" << endl;
			break;
		}
		case 2:{
			cout << "----------------------------------------------" << endl;
			cout << "Algoritmo: Busqueda Local" << endl;
			break;
		}
		case 3:{
			cout << "----------------------------------------------" << endl;
			cout << "Algoritmo: Greedy Relief" << endl;
			break;
		}
	}
	cout << "----------------------------------------------" << endl;
	cout << "Semilla Escogida: " << chosenSeed << endl;
	return 1;
}

int getFromParameter(string pathOptionFile, string pathOptionAlgorithm, string pathChosenSeed, int &optionFile, int &optionAlgorithm, unsigned long &chosenSeed){
	string readOptionFile(pathOptionFile);
	string readOptionAlgorithm(pathOptionAlgorithm);
	string readChosenSeed(pathChosenSeed);
	optionFile = stoi(readOptionFile);
	if(optionFile != 1 && optionFile != 2 && optionFile != 3){
		cout << "Error al escoger el archivo" << endl;
		cout << "1 -> Ozone" << endl;
		cout << "2 -> Parkinsons" << endl;
		cout << "3 -> Spectf-Heart" << endl;
		return 0;
	}
	optionAlgorithm = stoi(readOptionAlgorithm);
	if(optionAlgorithm != 1 && optionAlgorithm != 2 && optionAlgorithm != 3){
		cout << "Error al escoger el algoritmo" << endl;
		cout << "1 -> 1-NN" << endl;
		cout << "2 -> Busqueda Local" << endl;
		cout << "3 -> Greedy Relief" << endl;
		return -1;
	}
	unsigned long auxSeed = stoul(readChosenSeed);
	if(auxSeed != 0){
		chosenSeed = auxSeed;
	}
	switch(optionFile){
		case 1:{
			cout << "----------------------------------------------" << endl;
			cout << "Archivo de Datos: Ozone" << endl;
			break;
		}
		case 2:{
			cout << "----------------------------------------------" << endl;
			cout << "Archivo de Datos: Parkisons" << endl;
			break;
		}
		case 3:{
			cout << "----------------------------------------------" << endl;
			cout << "Archivo de Datos: Spectf-Heart" << endl;
			break;
		}
	}
	switch(optionAlgorithm){
		case 1:{
			cout << "----------------------------------------------" << endl;
			cout << "Algoritmo: 1-NN" << endl;
			break;
		}
		case 2:{
			cout << "----------------------------------------------" << endl;
			cout << "Algoritmo: Busqueda Local" << endl;
			break;
		}
		case 3:{
			cout << "----------------------------------------------" << endl;
			cout << "Algoritmo: Greedy Relief" << endl;
			break;
		}
	}
	cout << "----------------------------------------------" << endl;
	cout << "Semilla Escogida: " << chosenSeed << endl;
	return 1;
}

void getFromTerminal(int &optionFile, int &optionAlgorithm, unsigned long &chosenSeed){
	while(optionFile != 1 && optionFile != 2 && optionFile != 3){
		cout << "----------------------------------------------" << endl;
		cout << "Elija el Archivo de Datos:" << endl;
		cout << "\tOpcion 1 -> Ozone" << endl;
		cout << "\tOpcion 2 -> Parkinsons" << endl;
		cout << "\tOpcion 3 -> Spectf-Heart" << endl;
		cin >> optionFile;
	}
	while(optionAlgorithm != 1 && optionAlgorithm != 2 && optionAlgorithm != 3){
		cout << "----------------------------------------------" << endl;
		cout << "Elija el Algoritmo:" << endl;
		cout << "\tOpcion 1 -> 1-NN" << endl;
		cout << "\tOpcion 2 -> Busqueda Local" << endl;
		cout << "\tOpcion 3 -> Greedy Relief" << endl;
		cin >> optionAlgorithm;
	}
	cout << "----------------------------------------------" << endl;
	cout << "Elija la Semilla:" << endl;
	cout << "\t0 -> Semilla por Defecto (20000913)" << endl;
	unsigned long auxSeed;
	cin >> auxSeed;
	if(auxSeed != 0){
		chosenSeed = auxSeed;
	}
}

int main(int argc, char* argv[]){
	unsigned long semilla = 20000913;
	int opcionArchivo = 0, opcionAlgoritmo = 0;
	float tMedio = 0.0, tasaMedia = 0.0;
	string file_name = "";
	string format    = ".csv";
	vector<float> results;

	if(argc == 2){
		int valor = getFromFile(argv[1], opcionArchivo, opcionAlgoritmo, semilla);
		if(valor == -1){
			return -1;
		}
	}else if(argc == 5){
		int valor = getFromParameter(argv[1], argv[2], argv[3], opcionArchivo, opcionAlgoritmo, semilla);
		if(valor == -1){
			return -1;
		}
	}else{
		getFromTerminal(opcionArchivo, opcionAlgoritmo, semilla);
	}
	Set_random(semilla);
	Datos conjuntoDatos;
	switch(opcionArchivo){
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
	}
	switch(opcionAlgoritmo){
		case 1:{
			vector<float> pesos(conjuntoDatos.getTamAtributos(), 1.0);
			float tasa;
			string aux = "_1NN";
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

				results.push_back(tasa);
				results.push_back(temp.getTime());
				results.push_back(0.0);
				results.push_back((float)0.5 * (float)tasa);
			}
			file_name = file_name + aux;
			break;
		}
		case 2:{
			vector<float> pesos, pesosAux;
			float tasa;
			string aux = "_BL";
			for(int i = 0; i < conjuntoDatos.getTamAtributos(); ++i){
				pesos.push_back(Randfloat(0.0, 1.0));
			}
			for(int i = 0; i < 5; ++i){
				Temporizador temp;
				pesosAux = pesos;
				int vecinosGenerados = 20 * (conjuntoDatos.getTamAtributos());
				cout << "----------------------------------------------" << endl;
				cout << "Comienzo del procesamiento de la" << endl << "particion " << i+1 << ":" << endl;
				temp.start();
				LocalSearch(conjuntoDatos.getParticionTrain(i+1), conjuntoDatos.getDatos(), conjuntoDatos.getEtiquetas(), vecinosGenerados, pesosAux);
				temp.stop();
				tasa = KNN(conjuntoDatos.getParticionTrain(i+1), conjuntoDatos.getParticionTest(i+1), conjuntoDatos.getDatos(), conjuntoDatos.getEtiquetas(), pesosAux, 0.2);
				tMedio += temp.getTime();
				tasaMedia += tasa;
				int pesosDescartados = 0;
				for(int j = 0; j < pesosAux.size(); ++j){
					if(pesosAux[j] < 0.2){
						pesosDescartados++;
					}
				}
				double tasaReduccion = (float)100.0 * ((float)pesosDescartados/(float)pesosAux.size());
				cout << "\tPorcentaje Acierto: " << tasa << "%" << endl;
				cout << "\tTiempo Ejecucion: " << temp.getTime() << " seg." << endl;
				cout << "\tTasa Reduccion: " << tasaReduccion << "%" << endl;
				cout << "\tAgregacion: " << (float)0.5 * (float)tasa + (float)0.5 * (float)tasaReduccion << " % " << endl;
				results.push_back(tasa);
				results.push_back(temp.getTime());
				results.push_back(tasaReduccion);
				results.push_back((float)0.5 * (float)tasa + (float)0.5 * (float)tasaReduccion);
			}
			file_name = file_name + aux;
			break;
		}
		case 3:{
			vector<float> pesos(conjuntoDatos.getTamAtributos(), 0.0), pesosAux;
			float tasa;
			string aux = "_RELIEF";
			for(int i = 0; i < 5; ++i){
				Temporizador temp;
				pesosAux = pesos;
				cout << "----------------------------------------------" << endl;
				cout << "Comienzo del procesamiento de la" << endl << "particion " << i+1 << ":" << endl;
				temp.start();
				Relief(conjuntoDatos.getParticionTrain(i+1), conjuntoDatos.getDatos(), conjuntoDatos.getEtiquetas(), pesosAux);
				temp.stop();
				tasa = KNN(conjuntoDatos.getParticionTrain(i+1), conjuntoDatos.getParticionTest(i+1), conjuntoDatos.getDatos(), conjuntoDatos.getEtiquetas(), pesosAux);
				tMedio += temp.getTime();
				tasaMedia += tasa;
				cout << "\tPorcentaje Acierto: " << tasa << "%" << endl;
				cout << "\tTiempo Ejecucion: " << temp.getTime() << " seg." << endl;
				cout << "\tTasa Reduccion: 0% " << endl;
				cout << "\tAgregacion: " << (float)0.5 * (float)tasa << " %" << endl;

				results.push_back(tasa);
				results.push_back(temp.getTime());
				results.push_back(0.0);
				results.push_back((float)0.5 * (float)tasa);

			}

			file_name = file_name + aux;
			break;
		}
	}
	cout << "----------------------------------------------" << endl;
	cout << "----------------------------------------------" << endl;
	cout<<"Porcentaje Medio de Acierto: " << tasaMedia/5 << endl;
	cout<<"Tiempo Medio de Ejecucion: " << tMedio/5 << endl;

	results.push_back(tasaMedia/5);
	results.push_back(tMedio/5);

	ofstream file ;
	file_name = file_name + format;
	file.open(file_name);
	FillCsv(file,results,4);
	file.close();
	return 0;
}
