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
	vector<unsigned char>::iterator it = block->getIterator();
	ASSERT_EQ(block->getSizeInBytes(),1);
	ASSERT_EQ(*it,7);
}

TEST(DataBlockTest,buildbyte){
	DataBlock * block = new DataBlock();
	unsigned short int uno = 1;
	unsigned short int cero = 0;
	block->addBits(uno,1);
	block->addBits(uno,1);
	block->addBits(uno,1);
	block->addBits(uno,1);
	block->addBits(cero,1);
	block->addBits(cero,1);
	block->addBits(cero,1);
	block->addBits(uno,1);
	vector<unsigned char>::iterator it = block->getIterator();
	ASSERT_EQ(block->getSizeInBytes(),1);
	ASSERT_EQ(*it,241);
}

TEST(DataBlockTest,addbits){
	DataBlock * block = new DataBlock();
	unsigned short int unos = 0xFF;
	block->addBits(unos,4);
	//block->addByte(1);
	vector<unsigned char>::iterator it = block->getIterator();
	ASSERT_EQ(block->getSizeInBytes(),1);
	ASSERT_EQ(*it,0x0F);
}


}


