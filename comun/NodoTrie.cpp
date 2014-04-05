#include "NodoTrie.h"

NodoTrie::NodoTrie() {
    esValido = false;
	elemento = NULL;
}

NodoTrie * NodoTrie::getPtrNodoHijo(char clave) {
	DatoTrie * datoAux = new DatoTrie(clave, NULL);
	std::set<DatoTrie*, CompDatoTrie>::iterator itDat = datos.find(datoAux);
	delete (datoAux);
	if (itDat != datos.end())
		return (*itDat)->getPtrNodoHijo();
	return NULL;
}

bool NodoTrie::getValidez() {
    return esValido;
}

void NodoTrie::setValido() {
    esValido = true;
}

void NodoTrie::insertarClave(char clave) {
	NodoTrie * nuevoNodoHijo = new NodoTrie();
	DatoTrie * ptrDato = new DatoTrie(clave, nuevoNodoHijo);
	if (datos.find(ptrDato) == datos.end())
		datos.insert(ptrDato);
	else {
		delete (nuevoNodoHijo);
		delete (ptrDato);
	}
}

void NodoTrie::eliminarClave(char clave) {
	// si borrar un dato se eliminan todos sus decendientes
	DatoTrie * datoAux = new DatoTrie(clave, NULL);
	std::set<DatoTrie*, CompDatoTrie>::iterator itDat = datos.find(datoAux);
	delete (datoAux);
	if (itDat != datos.end()) {
		delete ((*itDat)->getPtrNodoHijo());
		delete (*itDat);
	}
}

Elemento * NodoTrie::getElemento() {
	return elemento;
}

void NodoTrie::setElemento(Elemento * elemento) {
	if (this->elemento != NULL) delete(this->elemento);
	this->elemento = elemento;
}

NodoTrie::~NodoTrie() { 
	// con esto posicionandome en el primero del arbol, 
	// borrar todos los decendientes
	std::set<DatoTrie*>::iterator itDat = datos.begin();
	for (;itDat != datos.end(); itDat++) {
		delete ((*itDat)->getPtrNodoHijo());
		delete ((*itDat));
	}
	delete(elemento);
	datos.clear();
}

