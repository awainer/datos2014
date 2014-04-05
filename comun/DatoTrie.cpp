#include "DatoTrie.h"

DatoTrie::DatoTrie(const char caracter, NodoTrie * ptrNodoHijo) {
	this->caracter = caracter;
	this->ptrNodoHijo = ptrNodoHijo;
}

char DatoTrie::getCaracter() {
	return caracter;
}

NodoTrie * DatoTrie::getPtrNodoHijo() {
	return ptrNodoHijo;
}

DatoTrie::~DatoTrie() {
}


