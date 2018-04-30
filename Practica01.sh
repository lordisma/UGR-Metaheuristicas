#!/bin/bash

#Uso: ./Practica01.sh

#Guardamos los directorios necesarios
bin=$(pwd)/bin
obj=$(pwd)/obj
soluciones=$(pwd)/sol

#Colores para los mensajes por terminal
nocolor='\033[0m'
color='\033[0;34m'

#Se crean los directorios "vacios" si no existen
if [ -d $bin ];
then
	echo -e "${color}Directorio 'bin' listo${nocolor}"
else
	mkdir $bin
	echo -e "${color}Directorio 'bin' creado${nocolor}"
fi
if [ -d $obj ];
then
	echo -e "${color}Directorio 'obj' listo${nocolor}"
else
	mkdir $obj
	echo -e "${color}Directorio 'obj' creado${nocolor}"
fi
if [ -d $soluciones ];
then
	echo -e "${color}Directorio 'sol' listo${nocolor}"
else
	mkdir $soluciones
	echo -e "${color}Directorio 'sol' creado${nocolor}"
fi

#Usa make clean para limpiar
echo -e "\n${color}Limpiando los Directorios...\n${nocolor}"
make clean

#Compila el codigo
echo -e "\n${color}Compilando en Codigo...\n${nocolor}"
make

#Se mueve a la carpeta bin
cd $bin

#Se lanzan las ejecuciones de la Practica 01
#Los resultados se almacenan en 'sol'
echo -e "\n${color}Guardando solucion en: ${soluciones}\n${nocolor}"

echo -e "\n${color}Ejecutando Ozone para 1NN...\n${nocolor}"
${bin}/ClasificadorKNN 1 1 0 Ozone_1NN > "${soluciones}/Ozone_1NN.txt"
echo -e "${color}Ejecutando Ozone para BL...\n${nocolor}"
$bin/ClasificadorKNN 1 2 0 Ozone_BL >  $soluciones/"Ozone_BL.txt"
echo -e "${color}Ejecutando Ozone para RELIEF...\n${nocolor}"
$bin/ClasificadorKNN 1 3 0 Ozone_RELIEF > $soluciones/"Ozone_RELIEF.txt"
echo -e "${color}Ejecutando Parkinsons para 1NN...\n${nocolor}"
$bin/ClasificadorKNN 2 1 0 Parkisons_1NN > $soluciones/"Parkinsons_1NN.txt"
echo -e "${color}Ejecutando Parkinsons para BL...\n${nocolor}"
$bin/ClasificadorKNN 2 2 0 "Parkinsons_BL" > $soluciones/"Parkinsons_BL.txt"
echo -e "${color}Ejecutando Parkinsons para RELIEF...\n${nocolor}"
$bin/ClasificadorKNN 2 3 0 "Parkinsons_RELIEF" > $soluciones/"Parkinsons_RELIEF.txt"
echo -e "${color}Ejecutando Spectf-Heart para 1NN...\n${nocolor}"
$bin/ClasificadorKNN 3 1 0 "Spectf-Heart_1NN" > $soluciones/"Spectf-Heart_1NN.txt"
echo -e "${color}Ejecutando Spectf-Heart para BL...\n${nocolor}"
$bin/ClasificadorKNN 3 2 0 "Spectf-Heart_BL" > $soluciones/"Spectf-Heart_BL.txt"
echo -e "${color}Ejecutando Spectf-Heart para RELIEF...\n${nocolor}"
$bin/ClasificadorKNN 3 3 0 "Spectf-Heart_RELIEF" > $soluciones/"Spectf-Heart_RELIEF.txt"
echo -e "${color}Ejecutando Spectf-Heart para Generacional...\n${nocolor}"
$bin/Genetico 3 1 > $soluciones/"Spectf-Heart_Generacional.txt"
echo -e "${color}Ejecutando Spectf-Heart para Estacionario...\n${nocolor}"
$bin/Genetico 3 2 > $soluciones/"Spectf-Heart_Estacionario.txt"
echo -e "${color}Ejecutando Parkinson para Generacional...\n${nocolor}"
$bin/Genetico 2 1 > $soluciones/"Parkinsons_Generacional.txt"
echo -e "${color}Ejecutando Parkinsons para Estacionario...\n${nocolor}"
$bin/Genetico 2 2 > $soluciones/"Parkinsons_Estacionario.txt"
echo -e "${color}Ejecutando Ozone para Generacional...\n${nocolor}"
$bin/Genetico 1 1 > $soluciones/"Ozone_Generacional.txt"
echo -e "${color}Ejecutando Ozone para Estacionario...\n${nocolor}"
$bin/Genetico 1 2 > $soluciones/"Ozone_Estacionario.txt"
echo -e "${color}Ejecutando Spectf-Heart para Memetico Random...\n${nocolor}"
$bin/Memetico 3 1 > $soluciones/"Spectf-Heart_MR.txt"
echo -e "${color}Ejecutando Spectf-Heart para Memetico All...\n${nocolor}"
$bin/Memetico 3 2 > $soluciones/"Spectf-Heart_MA.txt"
echo -e "${color}Ejecutando Spectf-Heart para Memetico Best...\n${nocolor}"
$bin/Memetico 3 3 > $soluciones/"Spectf-Heart_MB.txt"
echo -e "${color}Ejecutando Parkinsons para Memetico Random...\n${nocolor}"
$bin/Memetico 2 1 > $soluciones/"Parkisons_MR.txt"
echo -e "${color}Ejecutando Parkisons para Memetico All...\n${nocolor}"
$bin/Memetico 2 2 > $soluciones/"Parkisons_MA.txt"
echo -e "${color}Ejecutando Parkisons para Memetico Best...\n${nocolor}"
$bin/Memetico 2 3 > $soluciones/"Parkisons_MB.txt"
echo -e "${color}Ejecutando Ozone para Memetico Random...\n${nocolor}"
$bin/Memetico 1 1 > $soluciones/"Ozone_MR.txt"
echo -e "${color}Ejecutando Ozone para Memetico All...\n${nocolor}"
$bin/Memetico 1 2 > $soluciones/"Ozone_MA.txt"
echo -e "${color}Ejecutando Ozone para Memetico Best...\n${nocolor}"
$bin/Memetico 1 3 > $soluciones/"Ozone_MB.txt"

cd ..

echo -e "\n${color}Escribiendo resultados en XLS\n${nocolor}"

#Se lanzan las ejecuciones de XLSparser
#Los resultados se almacenan en 'sol', en un fichero .xls
echo -e "\n${color}Insertando datos en .xls para Ozone 1NN...\n${nocolor}"
$bin/XLSparser 0 4 1 $soluciones/"Ozone_1NN.txt"
echo -e "${color}Insertando datos en .xls para Ozone BL...\n${nocolor}"
$bin/XLSparser 0 14 1 $soluciones/"Ozone_BL.txt"
echo -e "${color}Insertando datos en .xls para Ozone RELIEF...\n${nocolor}"
$bin/XLSparser 0 24 1 $soluciones/"Ozone_RELIEF.txt"
echo -e "${color}Insertando datos en .xls para Parkinsons 1NN...\n${nocolor}"
$bin/XLSparser 0 4 5 $soluciones/"Parkinsons_1NN.txt"
echo -e "${color}Insertando datos en .xls para Parkinsons BL...\n${nocolor}"
$bin/XLSparser 0 14 5 $soluciones/"Parkinsons_BL.txt"
echo -e "${color}Insertando datos en .xls para Parkinsons RELIEF...\n${nocolor}"
$bin/XLSparser 0 24 5 $soluciones/"Parkinsons_RELIEF.txt"
echo -e "${color}Insertando datos en .xls para Spectf-Heart 1NN...\n${nocolor}"
$bin/XLSparser 0 4 9 $soluciones/"Spectf-Heart_1NN.txt"
echo -e "${color}Insertando datos en .xls para Spectf-Heart BL...\n${nocolor}"
$bin/XLSparser 0 14 9 $soluciones/"Spectf-Heart_BL.txt"
echo -e "${color}Insertando datos en .xls para Spectf-Heart RELIEF...\n${nocolor}"
$bin/XLSparser 0 24 9 $soluciones/"Spectf-Heart_RELIEF.txt"
echo -e "${color}Insertando datos en .xls para Spectf-Heart AGG...\n${nocolor}"
$bin/XLSparser 0 41 9 $soluciones/"Spectf-Heart_Generacional.txt"
echo -e "${color}Insertando datos en .xls para Spectf-Heart AGE...\n${nocolor}"
$bin/XLSparser 0 51 9 $soluciones/"Spectf-Heart_Estacionario.txt"
echo -e "${color}Insertando datos en .xls para Parkinsons AGG...\n${nocolor}"
$bin/XLSparser 0 41 5 $soluciones/"Parkinsons_Generacional.txt"
echo -e "${color}Insertando datos en .xls para Parkinsons AGE...\n${nocolor}"
$bin/XLSparser 0 51 5 $soluciones/"Parkinsons_Estacionario.txt"
echo -e "${color}Insertando datos en .xls para Ozone AGG...\n${nocolor}"
$bin/XLSparser 0 41 1 $soluciones/"Ozone_Generacional.txt"
echo -e "${color}Insertando datos en .xls para Ozone AGE...\n${nocolor}"
$bin/XLSparser 0 51 1 $soluciones/"Ozone_Estacionario.txt"
echo -e "${color}Insertando datos en .xls para Ozone MR...\n${nocolor}"
$bin/XLSparser 0 61 1 $soluciones/"Ozone_MR.txt"
echo -e "${color}Insertando datos en .xls para Ozone MA...\n${nocolor}"
$bin/XLSparser 0 71 1 $soluciones/"Ozone_MA.txt"
echo -e "${color}Insertando datos en .xls para Ozone MB...\n${nocolor}"
$bin/XLSparser 0 81 1 $soluciones/"Ozone_MB.txt"
echo -e "${color}Insertando datos en .xls para Parkisons MR...\n${nocolor}"
$bin/XLSparser 0 61 5 $soluciones/"Parkisons_MR.txt"
echo -e "${color}Insertando datos en .xls para Parkisons MA...\n${nocolor}"
$bin/XLSparser 0 71 5 $soluciones/"Parkisons_MA.txt"
echo -e "${color}Insertando datos en .xls para Parkisons MB...\n${nocolor}"
$bin/XLSparser 0 81 5 $soluciones/"Parkisons_MB.txt"
echo -e "${color}Insertando datos en .xls para Spectf-Heart MR...\n${nocolor}"
$bin/XLSparser 0 61 9 $soluciones/"Spectf-Heart_MR.txt"
echo -e "${color}Insertando datos en .xls para Spectf-Heart MA...\n${nocolor}"
$bin/XLSparser 0 71 9 $soluciones/"Spectf-Heart_MA.txt"
echo -e "${color}Insertando datos en .xls para Spectf-Heart MB...\n${nocolor}"
$bin/XLSparser 0 81 9 $soluciones/"Spectf-Heart_MB.txt"
