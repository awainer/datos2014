/*
 * HUFFMAN.h
 *
 *  Created on: May 12, 2014
 *      Author: freakazoid
 */

#ifndef HUFFMAN_H_
#define HUFFMAN_H_

#include <stdio.h>
#include <string.h>
#include "DataBlock.h"
#include <algorithm>
#include <list>

typedef unsigned char BYTE;


namespace std{

struct Caracter{
	DataBlock * cod;
	int longitud;
};

class NodoArbol{
private:
	int peso;
	int cod;
	NodoArbol*hijoDer;
	NodoArbol*hijoIzq;
public:
	NodoArbol(int weight,int code){peso = weight; cod = code;hijoDer=NULL;hijoIzq=NULL;};
	NodoArbol(int weight,NodoArbol*izq,NodoArbol*der){peso = weight; cod = 0;hijoIzq=izq;hijoDer=der;};
	~NodoArbol();
	int getPeso(){return peso;};
	int getCode(){return cod;};
	NodoArbol * derecha(){return hijoDer;};
	NodoArbol * izquierda(){return hijoIzq;};
};

class Arbol{
private:
	NodoArbol * raiz;
public:
	Arbol(){raiz = NULL;};
	~Arbol();
	void ArmarArbol(list<NodoArbol*> hojas);
	void generarCodigos(Caracter codigos[256]);
	void borrar(NodoArbol * node);
	NodoArbol * root(){return raiz;};
};

class HUFFMAN {
private:
	 Arbol * arbolHuff;
	 Caracter codigos[256];
public:
	HUFFMAN();
	virtual ~HUFFMAN();
	DataBlock* Compress(DataBlock * data, int chars[256]);
	bool decompress();
};

}

#endif /* HUFFMAN_H_ */
