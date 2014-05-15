/*
 * test_write_and_read_compressed.cpp
 *
 *  Created on: May 15, 2014
 *      Author: awainer
 */

#include "../contrib/gtest/gtest.h"
#include "../DataBlock.h"
#include "../CompressedFileWriter.h"
#include "../CompressedFileReader.h"
#include <fstream>
#include <sys/stat.h>

namespace std{

TEST(testIntegracionCompressedWriter,testOneBlock){
	string path = "/tmp/prueba.cmp";
	CompressedFileWriter * writer = new CompressedFileWriter(path);
	CompressedFileReader * reader;

	unsigned char aux = 0xFF;
	DataBlock * block = new DataBlock();
	DataBlock * readBlock;


	for(int i=0; i< 25; i++){
		//cerr << "sizeInBits: "<< block->getSizeInBits() << endl;
		block->addBits(aux,5); //125 bits
	}
	ASSERT_EQ(block->getSizeInBits(),125);
	writer->writeBlock(block);
	writer->close();

	reader = new CompressedFileReader(path);
	readBlock = reader->getBlock();
	ASSERT_EQ(readBlock->getSizeInBits(),125);
	delete readBlock;
	delete reader;
	delete writer;
	delete block;
}
TEST(testIntegracionCompressedWriter,testThreeBlocks){
	string path = "/tmp/prueba.cmp";
	CompressedFileWriter * writer = new CompressedFileWriter(path);
	CompressedFileReader * reader;

	unsigned char aux = 0xFF;
	DataBlock * readBlock;
	DataBlock * block1= new DataBlock();
	DataBlock * block2= new DataBlock();
	DataBlock * block3= new DataBlock();

	for(int i=0; i< 25; i++){
		//cerr << "sizeInBits: "<< block->getSizeInBits() << endl;
		block1->addBits(aux,5); //125 bits
	}
	for(int i=0; i< 32; i++){
		//cerr << "sizeInBits: "<< block->getSizeInBits() << endl;
		block2->addBits(aux,1); //32 bits
	}
	for(int i=0; i< 33; i++){
		//cerr << "sizeInBits: "<< block->getSizeInBits() << endl;
		block3->addBits(aux,2); //66 bits
	}
	ASSERT_EQ(block1->getSizeInBits(),125);
	ASSERT_EQ(block2->getSizeInBits(),32);
	ASSERT_EQ(block3->getSizeInBits(),66);

	writer->writeBlock(block1);
	writer->writeBlock(block2);
	writer->writeBlock(block3);
	writer->close();

	reader = new CompressedFileReader(path);
	readBlock = reader->getBlock();
	ASSERT_EQ(readBlock->getSizeInBits(),125);
	delete readBlock;
	readBlock = reader->getBlock();
	ASSERT_EQ(readBlock->getSizeInBits(),32);
	delete readBlock;
	readBlock = reader->getBlock();
	ASSERT_EQ(readBlock->getSizeInBits(),66);
	delete readBlock;

	delete reader;
	delete writer;
	delete block1;
	delete block2;
	delete block3;

}

TEST(testIntegracionCompressedWriter,testThreeBlocksWithRandomData){
	string path = "/tmp/prueba.cmp";
	CompressedFileWriter * writer = new CompressedFileWriter(path);
	CompressedFileReader * reader;
	vector<unsigned char>::iterator it,it2;

	DataBlock * readBlock;
	DataBlock * block1= new DataBlock();
	DataBlock * block2= new DataBlock();
	DataBlock * block3= new DataBlock();

	for(int i=0; i< 25; i++){
		//cerr << "sizeInBits: "<< block->getSizeInBits() << endl;
		block1->addBits(rand()%256,5); //125 bits
	}
	for(int i=0; i< 32; i++){
		//cerr << "sizeInBits: "<< block->getSizeInBits() << endl;
		block2->addBits(rand()%256,1); //32 bits
	}
	for(int i=0; i< 33; i++){
		//cerr << "sizeInBits: "<< block->getSizeInBits() << endl;
		block3->addBits(rand()%256,2); //66 bits
	}
	ASSERT_EQ(block1->getSizeInBits(),125);
	ASSERT_EQ(block2->getSizeInBits(),32);
	ASSERT_EQ(block3->getSizeInBits(),66);

	writer->writeBlock(block1);
	writer->writeBlock(block2);
	writer->writeBlock(block3);
	writer->close();

	reader = new CompressedFileReader(path);

	readBlock = reader->getBlock();
	ASSERT_EQ(readBlock->getSizeInBits(),125);
		it = readBlock->getIterator();
	it2 = block1->getIterator();
	for(unsigned int i=0;i<readBlock->getSizeInBytes();i++)
		ASSERT_EQ(it[i],it2[i]);
	delete readBlock;

	readBlock = reader->getBlock();
	ASSERT_EQ(readBlock->getSizeInBits(),32);
	it = readBlock->getIterator();
	it2 = block2->getIterator();
	for(unsigned int i=0;i<readBlock->getSizeInBytes();i++)
		ASSERT_EQ(it[i],it2[i]);
	delete readBlock;


	readBlock = reader->getBlock();
	ASSERT_EQ(readBlock->getSizeInBits(),66);
	it = readBlock->getIterator();
	it2 = block3->getIterator();
	for(unsigned int i=0;i<readBlock->getSizeInBytes();i++)
		ASSERT_EQ(it[i],it2[i]);
	delete readBlock;

	delete reader;
	delete writer;
	delete block1;
	delete block2;
	delete block3;

}



}
