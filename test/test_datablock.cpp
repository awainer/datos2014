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
	unsigned char uno = 1;
	unsigned char cero = 0;
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
	ASSERT_EQ(*it,0xF0);
}

TEST(DataBlockTest,addbits2){
	DataBlock * block = new DataBlock();
	unsigned short int unos = 0xFF;
	unsigned short int uno = 0x18;
	block->addBits(unos,4);
	block->addBits(uno,4);
	//block->addByte(1);
	vector<unsigned char>::iterator it = block->getIterator();
	ASSERT_EQ(block->getSizeInBytes(),1);
	ASSERT_EQ(*it,0xF8);
}

TEST(DataBlockTest,addBitsBytepico){
	DataBlock * block = new DataBlock();
	unsigned short int unos = 0xFF;
	block->addBits(unos,7);
	block->addBits((unsigned char)0x07,4);
	vector<unsigned char>::iterator it = block->getIterator();
	ASSERT_EQ(block->getSizeInBytes(),2);
	ASSERT_EQ(*it,0xFE);
	it++;
	ASSERT_EQ(*it,0xE0);
}

TEST(DataBlockTest,bitsAndBytes){
	DataBlock * block = new DataBlock();
	block->addBits((unsigned char)0xCC,6);
	block->addByte((unsigned char)0x07);
	vector<unsigned char>::iterator it = block->getIterator();
	ASSERT_EQ(block->getSizeInBytes(),2);
	ASSERT_EQ(*it,0x30);
	it++;
	ASSERT_EQ(*it,0x1C);
}
}


