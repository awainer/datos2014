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


namespace std{

NodoArbol::~NodoArbol(){
	delete hijoIzq;
	delete hijoDer;
}


int compareNodos(NodoArbol * nodo1, NodoArbol * nodo2){
	if (nodo1->getPeso() > nodo2->getPeso())
		return 1;
	return 0;
}

void Arbol::ArmarArbol(list<NodoArbol*> hojas){
	NodoArbol * der;
	NodoArbol * izq;

	if(hojas.size() == 0)
		return; //error no puede entrar sin elementos

	if(hojas.size() == 1)
		raiz = hojas.back();

	while(hojas.size() > 1){
		hojas.sort(compareNodos);

		der = hojas.back();
		hojas.pop_back();

		izq = hojas.back();
		hojas.pop_back();

		NodoArbol * nuevoNodo = new NodoArbol(izq->getPeso() + der->getPeso(),izq,der);

		if(hojas.empty())
			raiz = nuevoNodo;
		else
			hojas.push_back(nuevoNodo);
	}
	hojas.~list();
}


void Arbol::borrar(NodoArbol * node){
	if(node == NULL) return;
	borrar(node->izquierda());
	delete node;
	borrar(node->derecha());
}


Arbol::~Arbol(){
	borrar(raiz);
}

DataBlock* HUFFMAN::Compress(DataBlock * data, int chars[256]){
	list<NodoArbol*> hojas;
	DataBlock * output = new DataBlock();

	for (int i = 0; i < 256 ; i++){
		if (chars[i] != 0){
			NodoArbol * nuevoNodo = new NodoArbol(chars[i],i);

			hojas.push_back(nuevoNodo);
		}
	}
	arbolHuff->ArmarArbol(hojas);
	//arbolHuff->generarCodigos(&this->codigos);
	this->generarCodigos();

	vector<bool> code;
	auto it = data->getIterator();
	for(unsigned int i=0; i<data->getSizeInBytes();i++){
		code = this->codigos[*it];
		for (unsigned short int j=0; j<code.size();j++)
			output->addBoolean(code[j]);
		it++;
	}
	return output;
}

HUFFMAN::HUFFMAN() {
	arbolHuff = new Arbol();
}

HUFFMAN::~HUFFMAN() {
	// TODO Auto-generated destructor stub
}

// Me parece que es mas correcto que quien genere los códigos sea Huffman.
void HUFFMAN::generarCodigos() {
	vector<bool> code;
	this->recorrerArbol(this->arbolHuff->root(),code);
}


void HUFFMAN::recorrerArbol(NodoArbol* node, vector<bool> code) {
	// Estamos en una hoja
	if(node->derecha() == NULL && node->izquierda() == NULL){
		this->codigos[node->getCode()] = code;
	}
	//Proceso izquierda
	if(node->izquierda()){
		vector<bool> cizq = code;
		cizq.push_back(1);
		recorrerArbol(node->izquierda(),cizq);
	}

	if(node->derecha()){
		//Proceso derecha
		vector<bool> cder = code;
		cder.push_back(0);
		recorrerArbol(node->derecha(),cder);
	}
}

vector<bool> HUFFMAN::getCodigo(unsigned char c) {
	return this->codigos[c];
}

}
