/*
 * CircularListNode.h
 *
 *  Created on: 15/05/2014
 *      Author: tavo
 */

#ifndef CircularListNode_H
#define CircularListNode_H


class CircularListNode {
private:
	unsigned char value;
	CircularListNode * pointer_next;
	CircularListNode * pointer_previous;

public:
	CircularListNode();
	CircularListNode(unsigned char val);
	CircularListNode(unsigned char val, CircularListNode * next_node);
	CircularListNode(unsigned char val, CircularListNode * next_node, CircularListNode * previous_node);
	unsigned char getVal();
	void setVal(unsigned char val);
	CircularListNode * getNext();
	void setNext(CircularListNode * next_node);
	CircularListNode * getPrevious();
	void setPrevious(CircularListNode * previous_node);
	~CircularListNode();
};

#endif // CircularListNode_H
