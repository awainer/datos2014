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
#include <bitset>

typedef unsigned char BYTE;


namespace std{

struct Caracter{
	unsigned char c;
	//vector<bool> code;
	unsigned int code_lenght;
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
	void setNodoIzquierda(NodoArbol * node);
	void setNodoDerecha(NodoArbol * node);
	bool esHoja(){if (peso == -1) return 0;return 1;};
};

class Arbol{
private:
	NodoArbol * raiz;
//	void codear(NodoArbol * node, vector<bool> code);
public:
	Arbol(){raiz = NULL;};
	~Arbol();
	void ArmarArbol(list<NodoArbol*> hojas);
	void deleteRecursivo(NodoArbol* node);
	NodoArbol * root(){return raiz;};
	void setRoot(NodoArbol * root){raiz = root;};
	void insertarHoja(int c, vector<bool> code);
	NodoArbol * nodoIzqDe(NodoArbol * nodo){return nodo->izquierda();};
	NodoArbol * nodoDerDe(NodoArbol * nodo){return nodo->derecha();};
};
class HUFFMAN {
private:
	 Arbol * arbolHuff;
	 vector<bool> codigos[256];
	 void encodeTable(DataBlock * dest);
	 void canonical(vector<Caracter> vec);
	 void insertarHoja(int c, vector<bool> code);
public:
	HUFFMAN();
	virtual ~HUFFMAN();
	DataBlock* Compress(DataBlock * data, int chars[256]);
	DataBlock* decompress(DataBlock * data);
	void generarCodigos();
	vector<bool> getCodigo(unsigned char c);
	void recorrerArbol(NodoArbol * node, vector<bool> code);
	void reconstruirArbol();
	bool decompress();
};

}

#endif /* HUFFMAN_H_ */
