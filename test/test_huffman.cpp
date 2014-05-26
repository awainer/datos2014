
#include "gtest/gtest.h"
#include "../HUFFMAN.h"
#include "../util/bitsetaux.cpp"

namespace std{


TEST(AAAHUFFMANTest,TestGenerarPrimerosCodigos){
	HUFFMAN * huffman = new HUFFMAN();
	int frecuencias[256];
	DataBlock sarasa;
	DataBlock * result;
	for(int i = 0 ; i < 256 ; i++)
				frecuencias[i] = 0;
	frecuencias['A'] = 4;
	frecuencias['B'] = 2;
	frecuencias['C'] = 1;
	result = huffman->Compress(&sarasa,frecuencias);

	vector<bool> expectedA;
	vector<bool> expectedB;
	vector<bool> expectedC;

	vector<bool> codes[3];
	codes[0] = huffman->getCodigo('A');
	codes[1] = huffman->getCodigo('B');
	codes[2] = huffman->getCodigo('C');

	for(int i=0;i<3;i++){
		cerr << "Code: size" << codes[i].size() << " ";
		for(int j=0;j<codes[i].size();j++)
			cerr << codes[i][j];
		cerr << endl;
	}

	expectedA.push_back(0);
	expectedB.push_back(1);
	expectedB.push_back(0);
	expectedC.push_back(1);
	expectedC.push_back(1);

	ASSERT_EQ(huffman->getCodigo('A'),expectedA);   // 0
	ASSERT_EQ(huffman->getCodigo('B'),expectedB);   // 10
	ASSERT_EQ(huffman->getCodigo('C'),expectedC);   // 11

	delete result;
	delete huffman;
}

string vector_bool_to_string(vector<bool> b){
	string  result;

	for (unsigned int i=0; i<b.size(); i++)
		if (b[i])
		     result.push_back('1');
		else
			result.push_back('0');
	return result;
}
/*
TEST(AAAHUFFMANTest,TestEncodeTable){
//	cerr << "GAROLA" << vector_bool_to_string(vector<bool>(1010)) << endl;
	HUFFMAN * huffman1 = new HUFFMAN();
	HUFFMAN * huffman2 = new HUFFMAN();
	int frecuencias[256];
	DataBlock sarasa;
	DataBlock * compressed, * decompressed;
	for(int i = 0 ; i < 65 ; i++)
				frecuencias[i] = 0;
	for(int i = 65 ; i < 95 ; i++){
				frecuencias[i] = 3*i;
	for(int i = 95 ; i < 256 ; i++)
				frecuencias[i] = 0;
	}

    compressed = huffman1->Compress(&sarasa,frecuencias);
*/
    /*auto it = compressed->getIterator();
    for(int i=0;i<256;i++){
    	cerr << "Bloque comprimido, byte " << i << " " << (int) *it << endl;
    	it++;
    }*/

	// Un nuevo huffman
/*	huffman2 = new HUFFMAN();
	decompressed = huffman2->decompress(compressed);

	for(int i = 65 ; i < 95 ; i++){
		//cerr <<  vector_bool_to_string(huffman1->getCodigo(i)) << "|||||||||" << vector_bool_to_string(huffman2->getCodigo(i)) << endl;
		//cerr << "tes " << (int)i << endl;
		ASSERT_EQ(huffman1->getCodigo(i),huffman2->getCodigo(i));
	}
	delete compressed;
	delete decompressed;
	delete huffman1;
	delete huffman2;
}*/


/*TEST(AAAHUFFMANTest,TestCompressAndDecompressRandomData){

	HUFFMAN * huffman1 = new HUFFMAN();
	DataBlock * orig, * compressed, *decompressed;
	orig = new DataBlock();

	unsigned char c;
	int	frecs[256];
	for(int i=0;i<256;i++)
		frecs[i]=0;
	for(int i=0;i<20;i++){
		c = rand() % 100;
		frecs[c]+=1;
		orig->addByte(c);
	}

	compressed = huffman1->Compress(orig,frecs);
	decompressed = huffman1->decompress(compressed);

	ASSERT_EQ(orig->getSizeInBytes(),decompressed->getSizeInBytes());
	auto it1 = orig->getIterator();
	auto it2 = decompressed->getIterator();

	for(unsigned int i=0; i< orig->getSizeInBytes(); i++){
		ASSERT_EQ(it1[i],it2[i]);
	}
	delete orig;
	delete huffman1;
	delete compressed;
	delete decompressed;
}*/
}
