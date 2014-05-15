/*
 * CircularListNode.cpp
 *
 *  Created on: 14/05/2014
 *      Author: tavo
 */

#include "CircularListNode.h"

CircularListNode::CircularListNode(){
}


CircularListNode::CircularListNode(unsigned char val){
	this->setVal(val);
}

CircularListNode::CircularListNode(unsigned char val, CircularListNode * next_node){
	this->setVal(val);
	this->setNext(next_node);
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


CircularListNode::~CircularListNode() {
}

