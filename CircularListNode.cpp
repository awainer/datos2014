/*
 * CircularListNode.cpp
 *
 *  Created on: 14/05/2014
 *      Author: tavo
 */

#include "CircularListNode.h"
#include <iostream>


CircularListNode::CircularListNode(){
	this->value = 0;
	this->pointer_next = NULL;
	this->pointer_previous = NULL;
}


CircularListNode::CircularListNode(unsigned char val){
	this->value = val;
	this->pointer_next = NULL;
	this->pointer_previous = NULL;
}

CircularListNode::CircularListNode(unsigned char val, CircularListNode * next_node){
	this->value = val;
	this->pointer_next = next_node;
	this->pointer_previous = NULL;
}


CircularListNode::CircularListNode(unsigned char val, CircularListNode * next_node, CircularListNode * previous_node){
	this->value = val;
	this->pointer_next = next_node;
	this->pointer_previous = previous_node;
}



unsigned char CircularListNode::getVal(){
	return this->value;
}


void CircularListNode::setVal(unsigned char val){
	this->value = val;
}


CircularListNode * CircularListNode::getNext(){
	return this->pointer_next;
}


void CircularListNode::setNext(CircularListNode * next_node){
	this->pointer_next = next_node;
}


CircularListNode * CircularListNode::getPrevious(){
	return this->pointer_previous;
}


void CircularListNode::setPrevious(CircularListNode * previous_node){
	this->pointer_previous = previous_node;
}


CircularListNode::~CircularListNode() {
}

