/*
 * test_CircularList.cpp
 *
 *  Created on: 14/05/2014
 *      Author: tavo
 */

#include "../contrib/gtest/gtest.h"
#include "../DataBlock.h"
#include "../CircularList.h"
#include "../CircularListNode.h"
#include <vector>

namespace std{

TEST(CircularListTest,listVoid){
	CircularList * circular_list = new CircularList();
	ASSERT_EQ(circular_list->getQuantityNodes(),0);
	delete circular_list;

}


TEST(CircularListTest,addNode){
	CircularList * circular_list = new CircularList();
	circular_list->addNode('a');
	ASSERT_EQ(circular_list->getQuantityNodes(),1);
	ASSERT_EQ(circular_list->getFirstNode(),circular_list->getLastNode());
	delete circular_list;
}


TEST(CircularListTest,add2Nodes){
	CircularList * circular_list = new CircularList();
	circular_list->addNode('a');
	circular_list->addNode('b');
	ASSERT_EQ(circular_list->getQuantityNodes(),2);
	ASSERT_EQ(circular_list->getFirstNode(),(circular_list->getLastNode())->getNext());
	ASSERT_EQ(circular_list->getLastNode(),(circular_list->getFirstNode())->getNext());
	delete circular_list;
}

TEST(CircularListTest,add3Nodes){
	CircularList * circular_list = new CircularList();
	circular_list->addNode('a');
	circular_list->addNode('b');
	circular_list->addNode('c');
	ASSERT_EQ(circular_list->getQuantityNodes(),3);
	ASSERT_EQ(circular_list->getFirstNode(),(circular_list->getLastNode())->getNext());
	delete circular_list;
}


TEST(CircularListTest,addabc){
	DataBlock * block = new DataBlock();
	CircularList * circular_list = new CircularList();
	block->addByte('a');
	block->addByte('b');
	block->addByte('c');
	vector<unsigned char>::iterator it = block->getIterator();
	ASSERT_EQ(block->getSizeInBytes(),3);
	ASSERT_EQ(*it,'a');
	ASSERT_EQ(*it+1,'b');
	ASSERT_EQ(*it+2,'c');

	unsigned char un_char;

	for (int i = 1; i<=3; i++){
		un_char = (*it);
		circular_list->addNode(un_char);
		ASSERT_EQ(circular_list->getQuantityNodes(),i);
		it++;
	}

	DataBlock * cadena = circular_list->getStringStartingAt(1);
	vector<unsigned char>::iterator it2 = cadena->getIterator();
	ASSERT_EQ((*it2),'a');
	ASSERT_EQ((*it2+1),'b');
	ASSERT_EQ((*it2+2),'c');

	CircularListNode * auxnode = circular_list->getFirstNode();

	ASSERT_EQ('a',auxnode->getVal());
	auxnode=(auxnode->getNext());
	ASSERT_EQ('b',auxnode->getVal());
	auxnode=auxnode->getNext();
	ASSERT_EQ('c',auxnode->getVal());

	delete cadena;
	delete block;
	delete circular_list;

}


TEST(CircularListTest,addABCandObtainBCA){
	DataBlock * block = new DataBlock();
	CircularList * circular_list = new CircularList();
	block->addByte('a');
	block->addByte('b');
	block->addByte('c');
	vector<unsigned char>::iterator it = block->getIterator();
	unsigned char un_char;

	for (int i = 1; i<=3; i++){
		un_char = (*it);
		circular_list->addNode(un_char);
		it++;
	}

	ASSERT_EQ(circular_list->getQuantityNodes(),3);
	DataBlock * cadena = circular_list->getStringStartingAt(2);
	vector<unsigned char>::iterator it2 = cadena->getIterator();

	CircularListNode * auxnode = circular_list->getFirstNode();

	ASSERT_EQ('a',auxnode->getVal());
	auxnode=(auxnode->getNext());
	ASSERT_EQ('b',auxnode->getVal());


	it = cadena->getIterator();
	ASSERT_EQ(*it,auxnode->getVal());
	auxnode=(auxnode->getNext());
	it++;
	ASSERT_EQ(*it,auxnode->getVal());
	auxnode=auxnode->getNext();
	it++;
	ASSERT_EQ(*it,auxnode->getVal());

	delete cadena;
	delete block;
	delete circular_list;

}

}
