/*
 * test_datablock.cpp
 *
 *  Created on: 20/04/2014
 *      Author: ari
 */

#include "../contrib/gtest/gtest.h"
#include "../DataBlock.h"
namespace std{
TEST(DataBlockTest,addbyte){
	DataBlock * block = new DataBlock();
	block->addByte(7);
	ASSERT_EQ(block->getSizeInBytes(),1);
}

}


