/*
 * BWT.cpp
 *
 *  Created on: 27/04/2014
 *      Author: tavo
 */

#include "BWT.h"
#include "CircularList.h"
#include "DataBlock.h"
#include <string>
#include <vector>
#include <algorithm>    // std::sort
#include <iostream>

namespace std{

BWT::BWT() {
	this->circular_list = NULL;
}


bool BWT::nodeCompare(CircularListNode * n1, CircularListNode * n2){
	// True si n1 precede a n2, segun la referencia.
	// Para no modificar los parametros
	CircularListNode * node1 = n1;
	CircularListNode * node2 = n2;
	unsigned long int n = this->circular_list->getQuantityNodes();
	do{
		if(node1->getVal() < node2->getVal())
			return true;
		if(node1->getVal() > node2->getVal())
			return false;
		//son iguales, me fijo en el siguiente
		node1 = node1->getNext();
		node2 = node2->getNext();
		n--;
	}while(n>0);
	return false; //o true, es lo mismo, son iguales
}


bool BWT::checkStringsEquals(CircularListNode * n1, CircularListNode * n2){
	CircularListNode * node1 = n1;
	CircularListNode * node2 = n2;
	unsigned long int n = this->circular_list->getQuantityNodes();
	do{
		if(node1->getVal() < node2->getVal())
			return false;
		if(node1->getVal() > node2->getVal())
			return false;
		//son iguales, me fijo en el siguiente
		node1 = node1->getNext();
		node2 = node2->getNext();
		n--;
	}while(n>0);

	return true; //o true, es lo mismo, son iguales
}


DataBlock * BWT::transform(DataBlock * original_block) {
	DataBlock * result_block = new DataBlock();
	this->circular_list = new CircularList();
	unsigned char un_char;
	uint32_t row=0;

	vector<unsigned char>::iterator it = original_block->getIterator();

	// Armo la lista circular
	for (unsigned long int i = 1; i <= original_block->getSizeInBytes(); i++){
		un_char = (*it);
		this->circular_list->addNode(un_char);
		it++;
	}

	// Armo el vector de iteradoes a ordenar
	//unsigned long int cant_chars = this->circular_list->getQuantityNodes();
	//vector<list<CircularListNode *>::iterator> un_vector();
	vector<CircularListNode *> vec;

	for (unsigned long int i = 1; i <= original_block->getSizeInBytes(); i++){
		vec.push_back(this->circular_list->getNodeAt(i));
	}

	// Lambda functions FTW!
	// http://stackoverflow.com/questions/18273997/passing-a-private-method-of-the-class-as-the-compare-operator-for-stdsort
	// http://es.cppreference.com/w/cpp/language/lambda
	sort (vec.begin(), vec.end(),
			[this] (CircularListNode *n1,CircularListNode *n2)
				  {return this->nodeCompare(n1,n2);});

	// Recupero el número de fila donde está el string original
	bool end_of_cycle = false;
	for (unsigned long int i = 0; (i < (vec.size() -1 ) && (!end_of_cycle)) ; i++){
		CircularListNode * current = vec[i];
		CircularListNode * orig_string = this->circular_list->getFirstNode();

		if (this->checkStringsEquals(orig_string, current)){
			row = i;
			end_of_cycle = true;
		}
	}

	// TODO: encontrar la posicion del bloque original
	//puaj!
	unsigned char * b = (unsigned char*) & row;
	for(int i=0;i<4;i++){
		result_block->addByte(*b);
		b+=1;
		//cerr << "ADD: " << (int)*b << endl;
	}
/*
	// Muestro el vector salida
	for (unsigned long int i = 0; i < original_block->getSizeInBytes(); i++){
		CircularListNode * current = vec[i];
		CircularListNode * current2 = current;
		for (unsigned long int j = 0; j < original_block->getSizeInBytes(); j++){
			cerr << current2->getVal();
			current2=current2->getNext();
		}
		cerr << endl;
	}
*/
	// Paso el resultado al Data Block de salida
	for (unsigned long int i = 0; i < original_block->getSizeInBytes(); i++){

		CircularListNode * current = vec[i];
		CircularListNode * prev = current->getPrevious();
		unsigned char val = prev->getVal();
		result_block->addByte(val);
	}

	delete this->circular_list;
	return result_block;

}


DataBlock * BWT::untransform(DataBlock * cadena_ant){
	DataBlock * cadena_orig = new DataBlock();
	this->circular_list = new CircularList();
	vector<unsigned long int> vec;
	uint32_t pos_vector=0;

	vector<unsigned char>::iterator it = cadena_ant->getIterator();

	// Recupero la posición original del string
	unsigned char * b = (unsigned char*) & pos_vector;

	for (unsigned long int i = 0; i < 4; i++){
		(*b) = (*it);
		b+=1;
		it++;
	}

	// armo el vector con las posiciones de los chars
	for (unsigned long int i = 0; i < (cadena_ant->getSizeInBytes()-4); i++){
		vec.push_back(i);
	}
/*
	// sacar: muestro el vector
	cerr << "vector original: ";
	for (unsigned long int i = 0; i < (cadena_ant->getSizeInBytes()-4); i++){
		cerr << (*(it + vec[i]));
	}
	cerr << endl;
*/
	//ordeno el vector de las posiciones de los chars
	stable_sort (vec.begin(), vec.end(),
			[this, it] (unsigned long int pos_char1, unsigned long int pos_char2)
			  {return this->charCompare(it, pos_char1,pos_char2);});
/*
	// sacar: muestro el vector
	cerr << "vector: ";
	for (unsigned long int i = 0; i < (cadena_ant->getSizeInBytes()-4); i++){
		cerr << (*(it + vec[i]));
	}
	cerr << endl;
*/
/*
		// sacar: muestro posiciones del vector
		cerr << "posiciones vector: ";
		for (unsigned long int i = 0; i < (cadena_ant->getSizeInBytes()-4); i++){
			cerr << ( vec[i])<< ' ';
		}
		cerr << endl;
*/

	// armo la salida
	unsigned long int indice = pos_vector;
	it = cadena_ant->getIterator();
	it = it+4;
/*
	cerr << "pos_vector: " << pos_vector << endl;
*/
	for (unsigned long int k = 0; k < (cadena_ant->getSizeInBytes()-4); k++){
//		cerr << "k: " << k << endl;
//		cerr << "indice: " << indice << endl;
//		cerr << "vec[indice]: " << vec[indice] << endl;
		pos_vector = vec[indice];
//		cerr << "pos_vector: " << pos_vector << endl;
//		cerr << "addByte: " << (*(it + pos_vector)) << endl;
		cadena_orig->addByte(*(it + pos_vector));
		indice = pos_vector;
	}

	delete this->circular_list;
	return cadena_orig;
}


bool BWT::charCompare(vector<unsigned char>::iterator it, unsigned long int pos_char1, unsigned long int pos_char2){
	if (it[pos_char1] >= it[pos_char2]){
		return false;
	}
	else {
		return true;
	}
}


BWT::~BWT() {
	//delete this->circular_list;
}

}
