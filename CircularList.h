/*
 * CircularList.h
 *
 *  Created on: 14/05/2014
 *      Author: tavo
 */

#ifndef CircularList_H
#define CircularList_H

#include "CircularListNode.h"
#include "DataBlock.h"
#include <list>
#include <string>


namespace std {

class CircularList {
private:
	list <CircularListNode *> list_circular_nodes;
	unsigned long int quantity_nodes;
	CircularListNode * first_node;
	CircularListNode * last_node;

public:
	CircularList();
	CircularListNode * getFirstNode();
	CircularListNode * getLastNode();
	unsigned long int getQuantityNodes();
	void addNode(unsigned char val);
	DataBlock * getStringStartingAt(unsigned long int initial_node);
	DataBlock * getStringStartingAtNode(CircularListNode * initial_node);
	CircularListNode * getNodeAt(unsigned long int node_number);
	list<CircularListNode *>::iterator getIterator();
	list<CircularListNode *>::iterator getIteratorAt(unsigned long int initial_node);
	unsigned long int getPosNode(CircularListNode * node);
	~CircularList();
};

}

#endif // CircularList_H
