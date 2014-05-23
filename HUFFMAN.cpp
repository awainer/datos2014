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

void Arbol::codear(NodoArbol * node, int * cont, int code[20], Caracter chars[256]){
	if(node->derecha() == NULL && node->izquierda() == NULL){
		for(int i = 0; i < *cont ; i++)
			chars[node->getCode()].cod[i] = code[i];
		chars[node->getCode()].longitud = (*cont);
		(*cont)--;
	}
	else if ( node == NULL) return;
	else{
		code[(*cont)] = 0;
		(*cont)++;
		codear(node->izquierda(),cont,code,chars);
		code[(*cont)] = 1;
		(*cont)++;
		codear(node->derecha(),cont,code,chars);
		(*cont)--;

	}

}

void Arbol::generarCodigos(Caracter codigos[256]){
	int cont = 0;
	int code[20];

	for (int i = 0 ; i < 20 ; i++){
		code[i] = 0;
	}

	codear(raiz,&cont,code,codigos);
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
	arbolHuff->generarCodigos(codigos);
	return output;
}

HUFFMAN::HUFFMAN() {

	for (int i = 0; i < 256 ; i++){
		for(int j = 0 ; j < 20 ; j++)
			codigos[i].cod[j] = 0;
		codigos[i].longitud = 0;
	}

	arbolHuff = new Arbol();

}

HUFFMAN::~HUFFMAN() {
	// TODO Auto-generated destructor stub
}

}
