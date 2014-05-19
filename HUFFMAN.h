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
#include <vector>
#include <algorithm>

typedef unsigned char BYTE;


namespace std{

struct Caracter{
	BYTE cod;
	int frec;
};

class NodoArbol{
private:
	BYTE caracter;
	int peso;
	class NodoArbol * derecha;
	class NodoArbol * izquierda;
	class NodoArbol * hijoDerecho;
	class NodoArbol * hijoIzquierdo;

public:
	NodoArbol(BYTE caract, int frecuencia){caracter = caract; peso = frecuencia;derecha=NULL;
	izquierda=NULL;hijoDerecho=NULL;hijoIzquierdo=NULL;};
	NodoArbol(NodoArbol* nodoIzq, NodoArbol* nodoDer){peso = nodoIzq->getPeso()+nodoDer->getPeso();
	caracter = '*';derecha=NULL;izquierda=NULL;hijoDerecho=NULL;hijoIzquierdo=NULL;};
	virtual ~NodoArbol();
	int getPeso(){return peso;};
	void setHojaDer(NodoArbol*hoja){derecha = hoja;};
	class NodoArbol *getHojaDer(){return derecha;};
	void setHojaIzq(NodoArbol*hoja){izquierda = hoja;};
	class NodoArbol *getHojaIzq(){return izquierda;};

};

class Arbol{
private:
	NodoArbol * raiz;
	NodoArbol * ultimaHoja;

public:
	Arbol(){raiz = NULL; ultimaHoja = NULL;};
	virtual ~Arbol();
	void armarArbol();
	void agregarNodo(NodoArbol * nodoIzq, NodoArbol * nodoDer);
	NodoArbol* buscarNodoMin();
	void setearUltimaHoja(NodoArbol * hojaUltima){ultimaHoja = hojaUltima;};
	NodoArbol* getUltimaHoja(){return ultimaHoja;};
	void recorrerHojas();

};

class HUFFMAN {
private:
	vector<Caracter> frecuencias;
	Arbol * arbolHuff;
	//bool CodeComparator(Caracter char1, Caracter char2);
	void conectarHojas();
	void armarArbol();

public:
	HUFFMAN();
	virtual ~HUFFMAN();
	bool Compress(DataBlock * data, int chars[256]);
	bool decompress();
	void recorrerHojas();

};

}

#endif /* HUFFMAN_H_ */
