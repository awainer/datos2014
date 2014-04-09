#ifndef ARBOLTRIE_H
#define ARBOLTRIE_H

#include "NodoTrie.h"

class ArbolTrie {
private:
	NodoTrie * primero;	
	NodoTrie * getNodoFinal(std::string palabra);
	
public:
	ArbolTrie();
	void agregarPalabra(std::string palabra, Elemento * elemento);
	Elemento * getElementoDe(std::string palabra, bool & esValido);
	~ArbolTrie();

};

#endif // ARBOLTRIE_H
