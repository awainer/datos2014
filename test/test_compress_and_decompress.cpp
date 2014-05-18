/*
 * test_compress_and_decompress.cpp
 *
 *  Created on: 17/05/2014
 *      Author: ari
 */

#include "../contrib/gtest/gtest.h"
#include <fstream>
#include <cstdio>
#include "../Compressor.h"
#include "../Decompressor.h"
namespace std{

TEST(testIntegracionCompressor,CompressAndDecompress){
	ofstream fs;
	string path="/tmp/lagarola.txt";
	string path_cmp="/tmp/lagarola.txt.cmp";
	int buffsize=500000;
	fs.open(path.c_str(), ios::out | ios::binary);
	string  buffer;

	char aux;

	for(int i=0;i<buffsize;i++){
		aux = (rand() % 10) + 'a';
		buffer.push_back(aux);
	}
	//cerr << "Buffer.Size " << buffer.size() << endl;
	//string buffer;// = "GARRRRRRRRRRRRRROOOLA";

	fs.write(&(buffer.c_str()[0]), buffer.size());
	fs.close();

	Compressor * comp = new Compressor();

	comp->compress(path);
	remove(path.c_str());
	delete comp;

	Decompressor * decomp = new Decompressor();
	decomp->decompress(path_cmp);
	ifstream is;
	//char * buffer2 = (char*) malloc(buffsize);
	string buffer2;
	buffer2.reserve(buffer.size());
	is.open(path.c_str(), ios::in | ios::binary);
	is.read((char*)&(buffer2.c_str()[0]),buffer.size());

	for (unsigned int i=0; i<buffer.size(); i++){
	//	cerr << (int)buffer->c_str()[i] << " " <<  (int)buffer2.c_str()[i] << endl;
	//	cerr << "cmp " << i << endl;
		ASSERT_EQ(buffer.c_str()[i],buffer2.c_str()[i]);
	}

	delete decomp;
	//delete buffer;

}

}


