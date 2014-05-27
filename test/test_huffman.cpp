
#include "gtest/gtest.h"
#include "../HUFFMAN.h"
#include "../util/bitsetaux.cpp"

namespace std{


TEST(AAAHUFFMANTest,TestGenerarPrimerosCodigos){
	HUFFMAN * huffman = new HUFFMAN();
	unsigned int frecuencias[256];
	DataBlock * sarasa = new DataBlock();
	DataBlock * result;
	for(int i = 0 ; i < 256 ; i++)
				frecuencias[i] = 0;
	frecuencias['A'] = 4;
	frecuencias['B'] = 2;
	frecuencias['C'] = 1;
	for(int i=0;i<4;i++)
		sarasa->addByte('A');
	for(int i=0;i<2;i++)
		sarasa->addByte('B');
	sarasa->addByte('C');

	ASSERT_EQ(sarasa->getSizeInBytes(),7);

	result = huffman->Compress(sarasa,frecuencias);

	vector<bool> expectedA;
	vector<bool> expectedB;
	vector<bool> expectedC;

	vector<bool> codes[3];
	codes[0] = huffman->getCodigo('A');
	codes[1] = huffman->getCodigo('B');
	codes[2] = huffman->getCodigo('C');

	for(int i=0;i<3;i++){
		cerr << "Code: size" << codes[i].size() << " ";
		for(unsigned int j=0;j<codes[i].size();j++)
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
	// 00001010 11000000
	auto it = result->getIterator();
	//encoding de la tabla
	ASSERT_EQ(it['A'],1);
	ASSERT_EQ(it['B'],2);
	ASSERT_EQ(it['C'],2);
	ASSERT_EQ(it[256],10);
	ASSERT_EQ(it[257],192);

	ASSERT_EQ(result->getSizeInBytes(),256+2);

	delete result;
	delete huffman;
	delete sarasa;
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

TEST(AAAHUFFMANTest,TestCompressAndDecompress){
	HUFFMAN * huffman = new HUFFMAN();
	HUFFMAN * decompressor = new HUFFMAN();
	unsigned int frecuencias[256];
	DataBlock * sarasa = new DataBlock();
	DataBlock * result;
	DataBlock * decompressed;
	for(int i = 0 ; i < 256 ; i++)
				frecuencias[i] = 0;
	frecuencias['A'] = 4;
	frecuencias['B'] = 2;
	frecuencias['C'] = 1;
	for(int i=0;i<4;i++)
		sarasa->addByte('A');
	for(int i=0;i<2;i++)
		sarasa->addByte('B');
	sarasa->addByte('C');

	ASSERT_EQ(sarasa->getSizeInBytes(),7);

	result = huffman->Compress(sarasa,frecuencias);

	vector<bool> expectedA;
	vector<bool> expectedB;
	vector<bool> expectedC;

	vector<bool> codes[3];
	codes[0] = huffman->getCodigo('A');
	codes[1] = huffman->getCodigo('B');
	codes[2] = huffman->getCodigo('C');

	for(int i=0;i<3;i++){
		cerr << "Code: size" << codes[i].size() << " ";
		for(unsigned int j=0;j<codes[i].size();j++)
			cerr << codes[i][j];
		cerr << endl;
	}

	decompressed = decompressor->decompress(result);
	ASSERT_EQ(decompressed->getSizeInBytes(),sarasa->getSizeInBytes());
	//auto it = result->getIterator();

	delete result;
	delete huffman;
	delete sarasa;
	delete decompressor;
	delete decompressed;
}


TEST(AAAHUFFMANTest,TestCompressAndDecompressRandomData){

	HUFFMAN * huffman1 = new HUFFMAN();
	HUFFMAN * huffman2 = new HUFFMAN();
	DataBlock * orig, * compressed, *decompressed;
	orig = new DataBlock();

	unsigned char c;
	unsigned int	frecs[256];
	for(int i=0;i<256;i++)
		frecs[i]=0;
	for(int i=0;i<1000;i++){
		c = rand() % 100;
		frecs[c]+=1;
		orig->addByte(c);
	}

	compressed = huffman1->Compress(orig,frecs);
	decompressed = huffman2->decompress(compressed);

	ASSERT_EQ(orig->getSizeInBytes(),decompressed->getSizeInBytes());
	auto it1 = orig->getIterator();
	auto it2 = decompressed->getIterator();

	for(unsigned int i=0; i< orig->getSizeInBytes(); i++){
		ASSERT_EQ(it1[i],it2[i]);
	}
	delete orig;
	delete huffman1;
	delete huffman2;
	delete compressed;
	delete decompressed;
}
}
