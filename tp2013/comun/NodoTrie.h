#ifndef NODOTRIE_H
#define NODOTRIE_H
#include <iostream>
#include <set>
#include "DatoTrie.h"
#include "Elemento.h"

class CompDatoTrie {
public:
	bool operator()(DatoTrie * d1, DatoTrie * d2) { 
		return d1->getCaracter() < d2->getCaracter(); 
	}
};

class NodoTrie {
private:
	std::set<DatoTrie*, CompDatoTrie> datos;
	Elemento * elemento;
	bool esValido;
	
public:
	NodoTrie();
	NodoTrie * getPtrNodoHijo(char clave);
	void insertarClave(char clave);
	void eliminarClave(char clave);
	Elemento * getElemento();
	void setElemento(Elemento * elemento);
	bool getValidez();
    void setValido();
	~NodoTrie();

};

#endif // NODOTRIE_H
