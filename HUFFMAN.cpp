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
#include "util/bitsetaux.cpp"
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
	//hojas.~list();
	//delete hojas;
}

void Arbol::insertarHoja(int c, vector<bool> code){
	NodoArbol * nodoAux = raiz ;
	NodoArbol * padre;

	unsigned int j = 0;
	for( ; j < code.size() -1 ; j++){
		padre = nodoAux;
		if (code[j] == 0){
			if(!nodoAux->izquierda())
				nodoAux->setNodoIzquierda(new NodoArbol(-1,0));
				nodoAux = nodoAux->izquierda();
			}
		else{
			if(!nodoAux->derecha())
				nodoAux->setNodoDerecha(new NodoArbol(-1,0));
			nodoAux = nodoAux->derecha();
			}

/*		if ( nodoAux == NULL && j != (code.size()-1))
			nodoAux = new NodoArbol(-1,-1);
		if ( nodoAux == NULL && j == (code.size()-1))
			nodoAux = new NodoArbol(j,c);*/

	}
	padre = nodoAux;
	nodoAux = new NodoArbol(1,c);
		if (code[j])
			padre->setNodoDerecha(nodoAux);
		else
			padre->setNodoIzquierda(nodoAux);
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

DataBlock* HUFFMAN::Compress(DataBlock * data,unsigned int chars[256]) {
	this->arbolHuff = new Arbol();
	list<NodoArbol*> hojas;
	DataBlock * output = new DataBlock();

	for (int i = 0; i < 256; i++) {
		if (chars[i] != 0) {
			NodoArbol * nuevoNodo = new NodoArbol(chars[i], i);

			hojas.push_back(nuevoNodo);
		}
	}
	arbolHuff->ArmarArbol(hojas);
	hojas.clear();

	//arbolHuff->generarCodigos(&this->codigos);
	this->generarCodigos();
	delete this->arbolHuff;
	//encode table
	this->encodeTable(output);

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
	this->arbolHuff = NULL;
}

HUFFMAN::~HUFFMAN() {
	//delete this->arbolHuff;
}


bool carComp(Caracter c1, Caracter c2){
										if (c1.code_lenght < c2.code_lenght)
											return true;
										if (c1.code_lenght > c2.code_lenght)
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
		aux_sort[i].code_lenght=this->codigos[i].size();
	}
	sort(aux_sort.begin(),aux_sort.end(), carComp);
	this->canonical(aux_sort);
}

void HUFFMAN::canonical(vector<Caracter> characters) {
	/*for(int i=0;i<256;i++)
		if (characters[i].code_lenght!=0)
	//		cerr << "Canonical: " << (int)characters[i].c << " long" << characters[i].code_lenght << endl;*/
	unsigned int lenght=characters[0].code_lenght;
	bitset<32> last_code=0;
	vector<bool> aux_code;

	int j=0;
	//Busco el primer no cero.
	while(lenght==0){
		lenght=characters[j].code_lenght;
		j++;
	}
	j--;
	for(unsigned int i=0;i<lenght;i++)
		aux_code.push_back(0);
	this->codigos[characters[j].c]=aux_code;
	//cerr << "Primer char con codigo " << (int)characters[j].c <<  " largo " << aux_code.size() <<  endl;
	j++;
//	cerr << last_code << endl;
	for(; j<256; j++){
		aux_code.clear();
		if(characters[j].code_lenght>0){

			last_code=increment(last_code);
			//cerr << 'j' << j << endl;
			if(characters[j].code_lenght != lenght){
				unsigned short int zeros_to_append=characters[j].code_lenght - lenght;
				last_code = last_code << zeros_to_append;
				lenght = characters[j].code_lenght;
			}
			/*cerr << "last code" << endl;
			cerr << last_code[1];
			cerr << last_code[0] << endl;
			cerr << "LENGHT"<< lenght << endl;
*/
			for(short int i=lenght-1;i>=0;i--){
				//cerr << i << endl;
				aux_code.push_back(last_code[i]);
			}


			this->codigos[characters[j].c]=aux_code;
			//cerr << "Canonical-code: " << (int)characters[j].c << " long" << characters[j].code_lenght << endl;
		}
	}
}

void HUFFMAN::encodeTable(DataBlock* dest) {
	char aux;
	for (unsigned int i=0; i<256; i++){
		aux = this->codigos[i].size();
		/*if(aux>0)
			cerr << "Encodeo tabla, caracter " << i << " long " << (int)aux << endl;*/
		dest->addByte(aux);
	}
}

DataBlock* HUFFMAN::decompress(DataBlock* data) {
	this->arbolHuff = new Arbol();
	DataBlock * result = new DataBlock();

	auto it = data->getIterator();
	vector<Caracter> aux;
	Caracter c;
	for(int i=0; i<256; i++){
		c.c = i;
		c.code_lenght=0;
		if(*it > 0){
		for(int j=0;j<*it;j++)
			c.code_lenght++;
		}
		//cerr << "Car " << (int)c.c << "long  " << (int)it[i] << endl;
		aux.push_back(c);
		it++;
	}
	sort(aux.begin(),aux.end(), carComp);
	this->canonical(aux);

	reconstruirArbol();
	//it++;
	unsigned char mask;
	NodoArbol * nodoAux = arbolHuff->root();
	long int bitcounter=data->getSizeInBits() - 8 * 256; // le resto la tabla
	//for( unsigned int i = 256; i < data->getSizeInBytes(); i++){
	//cerr << "bitcount inicial" << bitcounter << endl;
	while(bitcounter>0){
		//cerr << "bitcount " << bitcounter << endl;
		//cerr << "Compressed byte: " << (int) *it << endl;

		mask = 128; // 10000000 en binario
		for(unsigned short int j=0;j<8;j++){
			bitcounter-=1;
			if(bitcounter < 0)
				break;
			if( (*it & mask) > 0){
				nodoAux = arbolHuff->nodoDerDe(nodoAux); // era un 1
			}
			else{
				nodoAux = arbolHuff->nodoIzqDe(nodoAux); // era un 0
			}
			if (nodoAux->esHoja()){
				result->addByte((unsigned char)nodoAux->getCode());
			//	cerr << "pushout: " << (unsigned char)nodoAux->getCode() << endl;
				nodoAux = arbolHuff->root();
			}
			mask = mask >> 1;
		}
		it++;
	}

	delete this->arbolHuff;
	return result;
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


void HUFFMAN::reconstruirArbol(){
	arbolHuff->setRoot(new NodoArbol(0,NULL,NULL));
	for(int i = 0 ; i < 256 ; i++){
		 if (codigos[i].size() > 0){
			 arbolHuff->insertarHoja(i,codigos[i]);
		 }
	}
}

}
