/*
 * CircularList.cpp
 *
 *  Created on: 14/05/2014
 *      Author: tavo
 */

#include "CircularList.h"
#include "DataBlock.h"
#include <list>
#include <iostream>

namespace std{


CircularList::CircularList() {
	this->quantity_nodes = 0;
}


unsigned long int CircularList::getQuantityNodes(){
	return quantity_nodes;
}


CircularListNode * CircularList::getFirstNode(){
	return this->first_node;
}


CircularListNode * CircularList::getLastNode(){
	return this->last_node;
}


void CircularList::addNode(unsigned char val){
	CircularListNode * new_node;
	if (this->quantity_nodes == 0) {
		new_node = new CircularListNode(val);
		this->first_node = new_node;
		this->last_node = new_node;

	}
	else{
		new_node = new CircularListNode(val,this->first_node);
	}
	(this->last_node)->setNext(new_node);
	this->last_node = new_node;
	this->quantity_nodes++;
	list_circular_nodes.push_back(new_node);
}


DataBlock * CircularList::getStringStartingAt(unsigned long int initial_node){
	list<CircularListNode *>::iterator itNodes = this->list_circular_nodes.begin();
	DataBlock * block = new DataBlock();
	CircularListNode * actual_node;

	for (unsigned long int i = 1; i < initial_node; i++){
		itNodes++;
	}

	actual_node = (*itNodes);

	for (unsigned long int i = 1; i <= this->quantity_nodes; i++){
		block->addByte(actual_node->getVal());
		actual_node= (actual_node->getNext());
	}

	return block;
}


CircularListNode * CircularList::getNodeAt(unsigned long int node_number){
	list<CircularListNode *>::iterator itNodes = this->list_circular_nodes.begin();

	for (unsigned long int i = 1; i < node_number; i++){
		itNodes++;
	}

	return (*itNodes);
}


unsigned long int CircularList::getPosNode(CircularListNode * node){
	list<CircularListNode *>::iterator itNodes = this->list_circular_nodes.begin();

	for (unsigned long int i = 1; i <= quantity_nodes; i++){
		if ((*itNodes)== node){
			return i;
		}
		itNodes++;
	}
	return 0;
}


list<CircularListNode *>::iterator CircularList::getIterator(){
	list<CircularListNode *>::iterator itNodes = this->list_circular_nodes.begin();

	return itNodes;
}


list<CircularListNode *>::iterator CircularList::getIteratorAt(unsigned long int initial_node){
	list<CircularListNode *>::iterator itNodes = this->list_circular_nodes.begin();

	for (unsigned long int i = 1; i < initial_node; i++){
		itNodes++;
	}

	return itNodes;
}



CircularList::~CircularList() {
	list<CircularListNode *>::iterator itNodes = this->list_circular_nodes.begin();
	for (; itNodes != this->list_circular_nodes.end(); itNodes++)
		delete (*itNodes);
}

}
