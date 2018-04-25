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
