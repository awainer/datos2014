/*
 * test_filereader.cpp
 *
 *  Created on: 12/05/2014
 *      Author: ari
 */
#include "gtest/gtest.h"
#include "../FileReader.h"
#include  "../DataBlock.h"
namespace std{
TEST(TestFileReader,readSmallFile){
	string path = "/tmp/small.txt";
	ofstream outfile (path.c_str(),std::ofstream::binary);
	FileReader * fr;
	DataBlock * block;
	char data[]="0123456789";
	// Creo un archivo de pruebas: 10 bytes * 10k = 100k
	for(int i=0; i<10000;i++)
		outfile.write((char*)&data,10);
	outfile.close();

	fr = new FileReader(path);
	ASSERT_TRUE(fr->hasBlocksLeft());
	block = fr->getBlock();
	//blockSize = 16k  (7 bloques)
	ASSERT_EQ(block->getSizeInBytes(),16384);
	vector<unsigned char>::iterator it = block->getIterator();
	unsigned char c = '0';
	for(int i=0; i<10;i++){
		ASSERT_EQ(c,*it);
		c+=1;
		it++;
	}
	for(int i=0;i<6;i++){
		ASSERT_TRUE(fr->hasBlocksLeft());
		delete block;
		block = fr->getBlock();
	}
	ASSERT_FALSE(fr->hasBlocksLeft());
	ASSERT_EQ(block->getSizeInBytes(),1696);
	delete block;
	delete fr;
}

}



