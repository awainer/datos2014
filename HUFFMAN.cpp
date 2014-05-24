/*
 * HUFFMAN.cpp
 *
 *  Created on: May 12, 2014
 *      Author: freakazoid
 */

#include <iostream>
#include "HUFFMAN.h"
#include <stdio.h>
#include <string.h>
#include "DataBlock.h"
#include <algorithm>
#include <list>
//#include "util/bitsetaux.cpp"
namespace std {

NodoArbol::~NodoArbol() {
}
void NodoArbol::setNodoIzquierda(NodoArbol* node) {
	hijoIzq = node;
}

void NodoArbol::setNodoDerecha(NodoArbol* node) {
	hijoDer = node;
}

int compareNodos(NodoArbol * nodo1, NodoArbol * nodo2) {
	if (nodo1->getPeso() > nodo2->getPeso())
		return 1;
	return 0;
}

void Arbol::ArmarArbol(list<NodoArbol*> hojas) {
	NodoArbol * der;
	NodoArbol * izq;

	if (hojas.size() == 0)
		return; //error no puede entrar sin elementos

	if (hojas.size() == 1)
		raiz = hojas.back();

	while (hojas.size() > 1) {
		hojas.sort(compareNodos);

		der = hojas.back();
		hojas.pop_back();

		izq = hojas.back();
		hojas.pop_back();

		NodoArbol * nuevoNodo = new NodoArbol(izq->getPeso() + der->getPeso(),
				izq, der);

		if (hojas.empty())
			raiz = nuevoNodo;
		else
			hojas.push_back(nuevoNodo);
	}
	hojas.~list();
}

void Arbol::deleteRecursivo(NodoArbol* node) {
//http://stackoverflow.com/questions/8062080/deleting-the-entire-binary-search-tree-at-once
	if (node != NULL) {

		this->deleteRecursivo(node->derecha());
		this->deleteRecursivo(node->izquierda());

		if (node->derecha() != NULL) {
			node->setNodoDerecha(NULL);
		}
		if (node->izquierda() != NULL) {
			node->setNodoIzquierda(NULL);
		}
		delete node;
	}

}

Arbol::~Arbol() {
	deleteRecursivo(raiz);
}

DataBlock* HUFFMAN::Compress(DataBlock * data, int chars[256]) {
	list<NodoArbol*> hojas;
	DataBlock * output = new DataBlock();

	for (int i = 0; i < 256; i++) {
		if (chars[i] != 0) {
			NodoArbol * nuevoNodo = new NodoArbol(chars[i], i);

			hojas.push_back(nuevoNodo);
		}
	}
	arbolHuff->ArmarArbol(hojas);
	//arbolHuff->generarCodigos(&this->codigos);
	this->generarCodigos();

	//encode table
	this->encodeTable(data);

	//encode data
	vector<bool> code;
	auto it = data->getIterator();
	for (unsigned int i = 0; i < data->getSizeInBytes(); i++) {
		code = this->codigos[*it];
		for (unsigned short int j = 0; j < code.size(); j++)
			output->addBoolean(code[j]);
		it++;
	}
	return output;
}

HUFFMAN::HUFFMAN() {
	arbolHuff = new Arbol();
}

HUFFMAN::~HUFFMAN() {
	delete this->arbolHuff;
}


bool carComp(Caracter c1, Caracter c2){
										if (c1.code.size() < c2.code.size())
											return true;
										if (c1.code.size() > c2.code.size())
											return false;
										if (c1.c < c2.c)
											return true;
										//if (c1.c > c2.c)
											return false;
										}
// Me parece que es mas correcto que quien genere los códigos sea Huffman.
void HUFFMAN::generarCodigos() {
	vector<bool> code;
	this->recorrerArbol(this->arbolHuff->root(), code);
	// Lo hago canónico, para poder almacenar solo las longitudes.
	// Ver: http://en.wikipedia.org/wiki/Canonical_Huffman_code
	//Caracter aux_sort[256];
	vector<Caracter> aux_sort = vector<Caracter>(256);
	for(unsigned short int i=0;i<256;i++){
		aux_sort[i].c=i;
		aux_sort[i].code=this->codigos[i];
	}
	sort(aux_sort.begin(),aux_sort.end(), carComp);
	this->canonical(aux_sort);
}

void HUFFMAN::canonical(vector<Caracter> characters) {
	unsigned int lenght=characters[0].code.size();
	bitset<32> last_code=0;
	vector<bool> aux_code;

	// Asigno el primer código, todos ceros.
	for(unsigned int i=0;i<lenght;i++)
		aux_code.push_back(0);
	this->codigos[characters[0].c]=aux_code;

	for(unsigned short int i=1; i<255; i++){
		aux_code.clear();
		if(characters[i].code.size()>0){
			//increment(last_code);
			if(characters[i].code.size() != lenght){
				unsigned short int zeros_to_append=characters[i].code.size() - lenght;
				last_code = last_code << zeros_to_append;
				lenght = characters[i].code.size();
			}

			for(unsigned short int j=0;j<lenght;j++)
				aux_code.push_back(last_code[j]);
			this->codigos[characters[0].c]=aux_code;
		}
	}
}

void HUFFMAN::encodeTable(DataBlock* dest) {
	char aux;
	for (unsigned int i=0; i<255; i++){
		aux = this->codigos[i].size();
		dest->addByte(aux);
	}
}

void HUFFMAN::recorrerArbol(NodoArbol* node, vector<bool> code) {
	// Estamos en una hoja
	if (node->derecha() == NULL && node->izquierda() == NULL) {
		this->codigos[node->getCode()] = code;
	}
	//Proceso izquierda
	if (node->izquierda()) {
		vector<bool> cizq = code;
		cizq.push_back(1);
		recorrerArbol(node->izquierda(), cizq);
	}

	if (node->derecha()) {
		//Proceso derecha
		vector<bool> cder = code;
		cder.push_back(0);
		recorrerArbol(node->derecha(), cder);
	}
}

vector<bool> HUFFMAN::getCodigo(unsigned char c) {
	return this->codigos[c];
}

}
