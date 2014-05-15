/*
* test_compressedfilewriter.cpp
 *
 *  Created on: 14/05/2014
 *      Author: ari
 */

#include "../contrib/gtest/gtest.h"
#include "../DataBlock.h"
#include "../CompressedFileWriter.h"
#include <fstream>
#include <sys/stat.h>

namespace std{

TEST(testCompressedWriter,testOneBlock){
	string path = "/tmp/prueba.cmp";
	CompressedFileWriter * writer = new CompressedFileWriter(path);
	ifstream reader;
	unsigned char aux = 0xFF;
	struct stat filestatus;
	DataBlock * block = new DataBlock();
	char * readBuffer;
	for(int i=0; i< 25; i++){
		//cerr << "sizeInBits: "<< block->getSizeInBits() << endl;
		block->addBits(aux,5); //125 bits
	}
	ASSERT_EQ(block->getSizeInBits(),125);
	writer->writeBlock(block);
	writer->close();
	stat(path.c_str(), &filestatus);
	int filesize = block->getSizeInBytes() + 4;
	ASSERT_EQ(filesize,filestatus.st_size);
	readBuffer = (char*) malloc(filesize);
	reader.open(path.c_str(), ios::in | ios::binary);
	reader.read(readBuffer,filesize);

	//Primeros 32 bits contienen el size en bits
	ASSERT_EQ(*((uint32_t*)readBuffer),125);


	free(readBuffer);
	delete writer;
	delete block;
}


}
