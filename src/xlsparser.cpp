#include <cstdlib>
#include <fstream>
#include <iostream>
#include <libxl.h>
#include <string>

using namespace libxl;
using namespace std;

int main(int argc, char* argv[]){
	if(argc != 5){
		cout << "Error, faltan datos" << endl;
		cout << "Modo de uso: <hoja> <fila> <columna> <fichero>" << endl;
		return -1;
	}
	Book* book = xlCreateBook();
	if(book){
		if(book->load("sol/Tablas.xls")){
			int hoja = atoi(argv[1]), fila = atoi(argv[2]), columna = atoi(argv[3]);
			ifstream file(argv[4]);
			string row, write;
			Sheet* sheet = book->getSheet(hoja);
			if(sheet){
					for(int i = 0; i < 12; ++i){
						getline(file, row);
					}
					for(int i = 0; i < 5; ++i){
						write = row.substr(row.find_last_of(":")+2, row.length());
						sheet->writeNum(fila+i, columna, stof(write.substr(0, write.length()-1)));
						getline(file, row);
						write = row.substr(row.find_last_of(":")+2, row.length());
						sheet->writeNum(fila+i, columna+3, stof(write.substr(0, write.length()-4)));
						getline(file, row);
						write = row.substr(row.find_last_of(":")+2, row.length());
						sheet->writeNum(fila+i, columna+1, stof(write.substr(0, write.length()-1)));
						getline(file, row);
						write = row.substr(row.find_last_of(":")+2, row.length());
						sheet->writeNum(fila+i, columna+2, stof(write.substr(0, write.length()-1)));
						for(int i = 0; i < 4; ++i){
							getline(file, row);
						}
					}
			}
		}
		book->save("sol/Tablas.xls");
	        book->release();
	}
	return 0;
}
