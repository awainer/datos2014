/*
 * test_CircularListNode.cpp
 *
 *  Created on: 15/05/2014
 *      Author: tavo
 */

#include "../contrib/gtest/gtest.h"
#include "../CircularListNode.h"
#include <vector>

namespace std{

TEST(CircularListNodeTest,addA){
	CircularListNode * circular_list_node = new CircularListNode('a');

	ASSERT_EQ(circular_list_node->getVal(),'a');

	delete circular_list_node;

}


TEST(CircularListNodeTest,addABandComparePointers){
	CircularListNode * circular_list_node = new CircularListNode('a');
	CircularListNode * circular_list_node2 = new CircularListNode('b',circular_list_node);

	circular_list_node->setNext(circular_list_node2);
	circular_list_node2->setNext(circular_list_node);
	circular_list_node->setPrevious(circular_list_node2);
	circular_list_node2->setPrevious(circular_list_node);


	ASSERT_EQ(circular_list_node->getVal(),'a');
	ASSERT_EQ(circular_list_node2->getVal(),'b');
	ASSERT_EQ(circular_list_node->getNext(),circular_list_node2);
	ASSERT_EQ(circular_list_node2->getNext(),circular_list_node);
	ASSERT_EQ((circular_list_node2->getNext())->getVal(),'a');
	ASSERT_EQ((circular_list_node->getNext())->getVal(),'b');
	ASSERT_EQ((circular_list_node2->getPrevious())->getVal(),'a');
	ASSERT_EQ((circular_list_node->getPrevious())->getVal(),'b');


	delete circular_list_node;
	delete circular_list_node2;

}


}


