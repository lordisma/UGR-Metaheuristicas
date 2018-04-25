BIN = bin
INC = include
OBJ = obj
SOL = sol
SRC = src

CXX = g++
CPPFLAGS = -O3 -g -c -std=c++11 -I$(INC)

# ************ Compilacion de los Programas ************

all: $(BIN)/ClasificadorKNN $(BIN)/Genetico

$(BIN)/ClasificadorKNN: $(OBJ)/clasificadorknn.o $(OBJ)/clasificador.o $(OBJ)/datos.o $(OBJ)/generador.o $(OBJ)/localsearch.o $(OBJ)/relief.o $(OBJ)/temporizador.o
	$(CXX) $(OBJ)/clasificadorknn.o $(OBJ)/clasificador.o $(OBJ)/datos.o $(OBJ)/generador.o $(OBJ)/localsearch.o $(OBJ)/relief.o $(OBJ)/temporizador.o -o $(BIN)/ClasificadorKNN

$(BIN)/Genetico: $(OBJ)/Genetico.o $(OBJ)/generador.o $(OBJ)/temporizador.o $(OBJ)/datos.o $(OBJ)/main.o
	$(CXX)  $(OBJ)/main.o $(OBJ)/clasificador.o $(OBJ)/Genetico.o $(OBJ)/generador.o $(OBJ)/datos.o $(OBJ)/temporizador.o -o $(BIN)/Genetico

# ************ Creacion de Objetos ************

$(OBJ)/main.o: $(SRC)/main_AG.cpp $(INC)/temporizador.h $(INC)/generador.h $(INC)/datos.h $(INC)/AGG.h
	$(CXX) $(CPPFLAGS) $(SRC)/main_AG.cpp -o $(OBJ)/main.o

$(OBJ)/clasificador.o: $(SRC)/clasificador.cpp $(INC)/clasificador.h
	$(CXX) $(CPPFLAGS) $(SRC)/clasificador.cpp -o $(OBJ)/clasificador.o

$(OBJ)/clasificadorknn.o: $(SRC)/clasificadorknn.cpp $(INC)/clasificador.h $(INC)/datos.h $(INC)/generador.h $(INC)/localsearch.h $(INC)/relief.h $(INC)/temporizador.h
	$(CXX) $(CPPFLAGS) $(SRC)/clasificadorknn.cpp -o $(OBJ)/clasificadorknn.o

$(OBJ)/datos.o: $(SRC)/datos.cpp $(INC)/datos.h
	$(CXX) $(CPPFLAGS) $(SRC)/datos.cpp -o $(OBJ)/datos.o

$(OBJ)/generador.o: $(SRC)/generador.cpp $(INC)/generador.h
	$(CXX) $(CPPFLAGS) $(SRC)/generador.cpp -o $(OBJ)/generador.o

$(OBJ)/localsearch.o: $(SRC)/localsearch.cpp $(INC)/localsearch.h
	$(CXX) $(CPPFLAGS) $(SRC)/localsearch.cpp -o $(OBJ)/localsearch.o

$(OBJ)/relief.o: $(SRC)/relief.cpp $(INC)/relief.h
	$(CXX) $(CPPFLAGS) $(SRC)/relief.cpp -o $(OBJ)/relief.o

$(OBJ)/temporizador.o: $(SRC)/temporizador.cpp $(INC)/temporizador.h
	$(CXX) $(CPPFLAGS) $(SRC)/temporizador.cpp -o $(OBJ)/temporizador.o

$(OBJ)/Genetico.o: $(SRC)/AGG.cpp $(INC)/AGG.h
	$(CXX) $(CPPFLAGS) $(SRC)/AGG.cpp -o $(OBJ)/Genetico.o

# ************ Limpieza ************

clean:
	$(info "Limpiando...")
	rm -f $(OBJ)/* $(BIN)/* $(SOL)/*
