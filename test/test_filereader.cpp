/*
 * test_filereader.cpp
 *
 *  Created on: 12/05/2014
 *      Author: ari
 */
#include "gtest/gtest.h"
#include "../FileReader.h"

namespace std{
TEST(TestFileReader,readSmallFile){
	string path = "/tmp/small.txt";
	ofstream outfile (path.c_str(),std::ofstream::binary);
	FileReader * fr;
	char data[]="0123456789";
	// Creo un archivo de pruebas
	for(int i=0; i<10000;i++)
		outfile.write((char*)&data,sizeof(data));
	outfile.close();

	fr = new FileReader(path);
	ASSERT_TRUE(fr->hasBlocksLeft());


	delete fr;
}

}



