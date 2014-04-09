#include "ArbolTrie.h"

ArbolTrie::ArbolTrie() {
	this->primero = new NodoTrie();
}

void ArbolTrie::agregarPalabra(std::string palabra, Elemento * elemento) {
	// carga la referencia a la palabra y de no existir la palabra la agrega
	NodoTrie * nodoAux = getNodoFinal(palabra);
	if (nodoAux == NULL) {
		nodoAux = primero;
		unsigned index = 0;
		while (index < palabra.length()) {
			if(nodoAux->getPtrNodoHijo(palabra.at(index)) != NULL)
				nodoAux = nodoAux->getPtrNodoHijo(palabra.at(index));
			else {
				nodoAux->insertarClave(palabra.at(index));
				nodoAux = nodoAux->getPtrNodoHijo(palabra.at(index));
			}	
			index++;
		}
	}
	nodoAux->setValido();
	nodoAux->setElemento(elemento);
}

NodoTrie * ArbolTrie::getNodoFinal(std::string palabra) {
	// retorna null si el camino para palabra no existe
	NodoTrie * nodoAux = primero;
	unsigned index = 0;
	while (index < palabra.length()) {
		if (nodoAux->getPtrNodoHijo(palabra.at(index)) != NULL) {
			nodoAux = nodoAux->getPtrNodoHijo(palabra.at(index));
			index++;
		} else
			return NULL;
	}
	if (nodoAux->getValidez())
	    return nodoAux;
    return NULL;
}

Elemento * ArbolTrie::getElementoDe(std::string palabra, bool & esValido) {
	esValido = false;
	NodoTrie * nodoAux = getNodoFinal(palabra);
	if (nodoAux != NULL) {
		esValido = nodoAux->getValidez();
		return nodoAux->getElemento();
	}
	return NULL;
}

ArbolTrie::~ArbolTrie() {
	delete (primero);
}


