/*
 * test_datablock.cpp
 *
 *  Created on: 20/04/2014
 *      Author: ari
 */

#include "../contrib/gtest/gtest.h"
#include "../DataBlock.h"
#include <vector>
namespace std{
TEST(DataBlockTest,addbyte){
	DataBlock * block = new DataBlock();
	block->addByte(7);
	//iterator it = block->getIterator();
	ASSERT_EQ(block->getSizeInBytes(),1);
	//ASSERT_EQ(*it,7);
}

}


