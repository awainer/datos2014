/*
 * HUFFMAN.cpp
 *
 *  Created on: May 12, 2014
 *      Author: freakazoid
 */

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

#include "HUFFMAN.h"
#include "DataBlock.h"


namespace std{

NodoArbol::~NodoArbol(){
	//lala
}

void HUFFMAN::recorrerHojas(){
	cout << "HOlaaaaaaaaaa" << endl;
	NodoArbol * nodoAux = arbolHuff->getUltimaHoja();
	cout << (nodoAux != NULL) << endl;
	while (nodoAux != NULL){
		cerr << nodoAux->getPeso() << endl;
		nodoAux = nodoAux->getHojaIzq();
	}
}

NodoArbol * Arbol::buscarNodoMin(){

	NodoArbol * nodoAux =  ultimaHoja;
	while(nodoAux->getHojaIzq() != NULL && nodoAux->getPeso() > nodoAux->getHojaIzq()->getPeso()){
			nodoAux = nodoAux->getHojaIzq();
	}
	return nodoAux;
}

void Arbol::agregarNodo(NodoArbol * nodoIzq, NodoArbol * nodoDer){
	NodoArbol * nuevoNodo = new NodoArbol(nodoIzq,nodoDer);

	if (nodoIzq->getHojaIzq() != NULL){
		nodoIzq->getHojaIzq()->setHojaDer(nuevoNodo);
	}
	if (nodoDer->getHojaDer() != NULL){
		nodoDer->getHojaDer()->setHojaIzq(nuevoNodo);
	}
	nuevoNodo->setHojaIzq(nodoIzq->getHojaIzq());
	nuevoNodo->setHojaDer(nodoDer->getHojaDer());
}

Arbol::~Arbol(){
	//lala
}

void HUFFMAN::armarArbol(){


}

void HUFFMAN::conectarHojas(){
	vector<Caracter>::iterator it;

	//seteo la primer hoja
	it = frecuencias.begin();
	NodoArbol * hojaAnterior = new NodoArbol(it->cod, it->frec);;

	for (it = (frecuencias.begin()+1); it != frecuencias.end(); it++){
		NodoArbol * nuevaHoja = new NodoArbol(it->cod, it->frec);

		nuevaHoja->setHojaIzq(hojaAnterior);
		hojaAnterior->setHojaDer(nuevaHoja);

		hojaAnterior = nuevaHoja;
	}
	arbolHuff->setearUltimaHoja(hojaAnterior);

}

bool codeComparator(Caracter char1, Caracter char2){
	if( char1.frec > char2.frec)
		return 1;
	return 0;
}

bool HUFFMAN::Compress(DataBlock * data, int chars[256]){

	vector<Caracter>::iterator it;
	it = frecuencias.begin();
	for (int i = 0; i < 256 ; i++){
		if (chars[i] != 0){
			Caracter caract;
			caract.cod = (BYTE)i;
			caract.frec = chars[i];
			it = frecuencias.insert(it,caract);
		}
	}
	std::sort (frecuencias.begin(), frecuencias.end(), codeComparator);
	conectarHojas();
	return true;
}

HUFFMAN::HUFFMAN() {

	arbolHuff = new Arbol();

}

HUFFMAN::~HUFFMAN() {
	// TODO Auto-generated destructor stub
}

}
