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
		if(n1->getVal() < n2->getVal())
			return true;
		if(n1->getVal() > n2->getVal())
			return false;
		//son iguales, me fijo en el siguiente
		node1 = node1->getNext();
		node2 = node2->getNext();
		n--;
	}while(n>0);
	return false; //o true, es lo mismo, son iguales
}

DataBlock * BWT::transform(DataBlock * original_block) {
	//DataBlock * result_block;
	unsigned char un_char;

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
	sort (vec.begin(), vec.end()-1,
			[this] (CircularListNode *n1,CircularListNode *n2)
				  {return this->nodeCompare(n1,n2);});

	//this->circular_list->getIteratorAt(i);


	//std::sort (myvector.begin()+4, myvector.end(), myfunction);

	return this->circular_list->getStringStartingAtNode(vec.at(0));

//	for(int i=0 ; i < cadena_orig.size;i++)
//		this->vector_punteros[i] = &cadena_orig[i];

}

BWT::~BWT() {
}

}
