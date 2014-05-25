
#include "gtest/gtest.h"
#include "../HUFFMAN.h"
#include "../util/bitsetaux.cpp"

namespace std{
/*TEST(HUFFMANtest, generarCodigos) {
	list<NodoArbol*> hojas;
		Arbol * huff = new Arbol();
		Caracter chars[256];

		for (int i = 0 ; i < 256 ; i++){
			chars[i].longitud = 0;
		}

		for(int i = 65 ; i < 95 ; i++){
			NodoArbol * nuevoNodo = new NodoArbol(i*3,i);

			hojas.push_back(nuevoNodo);
		}

		 for (std::list<NodoArbol*>::iterator it=hojas.begin(); it != hojas.end(); ++it)
		    std::cout << ' ' << (*it)->getPeso();

		 huff->ArmarArbol(hojas);

		 huff->generarCodigos(chars);

		 cout << endl;
		 for (int i = 0 ; i < 256 ; i++){
			 if(chars[i].longitud != 0 ){
				cout << (char)i << " Codigo: ";
		 		for (int j = 0 ; j < chars[i].longitud ; j++)
		 			cout << chars[i].cod[j];
		 		cout << endl;
			 }
		 }
}*/

TEST(AAAHUFFMANTest,TestGenerarCodigos){
	HUFFMAN * huffman = new HUFFMAN();
	int frecuencias[256];
	DataBlock sarasa;
	DataBlock * result;
	for(int i = 0 ; i < 65 ; i++)
				frecuencias[i] = 0;
	for(int i = 65 ; i < 95 ; i++){
				frecuencias[i] = 3*i;
	for(int i = 95 ; i < 256 ; i++)
				frecuencias[i] = 0;
	}

	result = huffman->Compress(&sarasa,frecuencias);

	vector<bool> aux;
	/*for(unsigned char i = 65 ; i < 95 ; i++){
		aux =  huffman->getCodigo(i);
		cerr << i << " ";
		for (unsigned int j=0; j<aux.size();j++)
			cerr << aux[j];
		cerr << endl;
	}*/
	ASSERT_EQ(huffman->getCodigo(65).size(),5);
	ASSERT_EQ(huffman->getCodigo(94).size(),4);
	delete result;
	delete huffman;
}
/*
TEST(AAAHUFFMANTest,TestGenerarPrimerosCodigos){
	HUFFMAN * huffman = new HUFFMAN();
	int frecuencias[256];
	DataBlock sarasa;
	DataBlock * result;
	for(int i = 0 ; i < 256 ; i++)
				frecuencias[i] = 0;
	frecuencias['A'] = 1;
	frecuencias['B'] = 3;
	frecuencias['C'] = 5;
	result = huffman->Compress(&sarasa,frecuencias);

	vector<bool> aux;
	for(unsigned char i = 'A' ; i < 'D' ; i++){
		aux =  huffman->getCodigo(i);
		cerr << i << " ";
		for (unsigned int j=0; j<aux.size();j++)
			cerr << aux[j];
		cerr << endl;
	}
	delete result;
	delete huffman;
}
*/
string vector_bool_to_string(vector<bool> b){
	string  result;

	for (unsigned int i=0; i<b.size(); i++)
		if (b[i])
		     result.push_back('1');
		else
			result.push_back('0');
	return result;
}

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

    /*auto it = compressed->getIterator();
    for(int i=0;i<256;i++){
    	cerr << "Bloque comprimido, byte " << i << " " << (int) *it << endl;
    	it++;
    }*/

	// Un nuevo huffman
	huffman2 = new HUFFMAN();
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
}


TEST(AAAHUFFMANTest,TestCompressAndDecompressRandomData){
//	cerr << "GAROLA" << vector_bool_to_string(vector<bool>(1010)) << endl;
	HUFFMAN * huffman1 = new HUFFMAN();
	DataBlock * orig, * compressed, *decompressed;
	orig = new DataBlock();

	unsigned char c;
	int	frecs[256];
	for(int i=0;i<256;i++)
		frecs[i]=0;
	for(int i=0;i<2000;i++){
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
}
}
