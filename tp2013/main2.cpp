#include <stdio.h>
//#include "../modeloClustering/Input.h"

<<<<<<< HEAD:tp2013/main.cpp
/*
int main(int argc, char **argv) {
	Input input(argc, argv);
=======

int main2(int argc, char **argv) {
/*	Input input(argc, argv);
>>>>>>> 4b4ea6d7af934e1b5cd950f930256e8ff4e2c734:tp2013/main2.cpp
	
	switch (input.getFuncion()) {
		case CLUSTERING: {
			//Parser
		case LISTADOC: {
			std::cout << "lista documentos y grupo al que pertenese\n";
			std::cout << "vacio: " << input.getParametro('l') << "\n";
			Listador * miListador = new Listador("./clusteringCorto.dat");
			miListador->imprimirRelacion(0);
			delete (miListador);
		} break;
		case LISTAGRUP: {
			std::cout << "lista los grupos y sus documentos\n";
			std::cout << "vacio: " << input.getParametro('g') << "\n";
			Listador * miListador = new Listador("./clusteringCorto.dat");
			miListador->imprimirRelacion(1);
			delete (miListador);
		} break;
		case AGREGADOC:
			std::cout << "agrega documento a la clasificacion\n";
			std::cout << "documento: " << input.getParametro('a') << "\n";
			break;
		case ERROR:
			std::cout << "parametros incorrectos\n";
			std::cout << "vacio: " << input.getParametro('t') << "\n";
			break;
	}
	
	return 0;
}
*/
