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
	this->circular_list = new CircularList();
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
	DataBlock * result_block =new DataBlock();
	unsigned char un_char;
	uint32_t row=0; //TODO

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
/*
	// ARI DESCOMENTA ESTO
	bool end_of_cycle = false;
	for (unsigned long int i = 0; ((i < original_block->getSizeInBytes()) || (end_of_cycle)) ; i++){
		CircularListNode * current = vec[i];
		CircularListNode * orig_string = this->circular_list->getFirstNode();

		if (this->checkStringsEquals(orig_string, current)){
			row = i;
			end_of_cycle = true;
		}
	}
*/
	// TODO: encontrar la posicion del bloque original
	//puaj!
	for(int i=0;i<4;i++)
		result_block->addByte( *((char *) (i +&row)) );

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

	// Paso el resultado al Data Block de salida
	for (unsigned long int i = 0; i < original_block->getSizeInBytes(); i++){

		CircularListNode * current = vec[i];
		CircularListNode * prev = current->getPrevious();
		unsigned char val = prev->getVal();
		result_block->addByte(val);
	}

	return result_block;

}

BWT::~BWT() {
	delete this->circular_list;
}

}
