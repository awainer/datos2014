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
	delete block;
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
	delete block;
}

TEST(DataBlockTest,addbits){
	DataBlock * block = new DataBlock();
	unsigned short int unos = 0xFF;
	block->addBits(unos,4);
	//block->addByte(1);
	vector<unsigned char>::iterator it = block->getIterator();
	ASSERT_EQ(block->getSizeInBytes(),1);
	ASSERT_EQ(*it,0xF0);
	delete block;
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
	delete block;
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
	delete block;
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
	delete block;
}

TEST(DataBlockTest,fromVector){
	DataBlock * block;
	vector<unsigned char> * v;
	v = new vector<unsigned char>;
	v->push_back('G');
	v->push_back('A');
	v->push_back('R');
	v->push_back('O');
	v->push_back('L');
	v->push_back('A');
	block = new DataBlock(v);
	ASSERT_EQ(block->getSizeInBytes(),6);
	delete block;
}

TEST(DataBlockTest,deACinco){
	DataBlock * block = new DataBlock();
	unsigned char aux= 0xFF;
	vector<unsigned char>::iterator it;
	ASSERT_EQ(block->getSizeInBits(),0);
	block->addBits(aux,5);
	ASSERT_EQ(block->getSizeInBits(),5);
	block->addBits(aux,5);
	it = block->getIterator();
	ASSERT_EQ(*it,255);
	it++;
	ASSERT_EQ(*it,192);
	ASSERT_EQ(block->getSizeInBits(),10);
	delete block;
}

}


