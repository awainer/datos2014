
#include "gtest/gtest.h"
#include "../HUFFMAN.h"


namespace std{
TEST(HUFFMANtest, OrdenamientoHojasArbol) {
	DataBlock * data = NULL;
	HUFFMAN * huf = new HUFFMAN();
	int chars[256];

	for (int i = 0 ; i < 256 ; i++)
		chars[i] = 0;

	chars[10] = 20;
	chars[40] = 50;
	chars[100] = 15;
	chars[200] = 5;
	chars[29] = 2043;
	chars[23] = 200;
	chars[45] = 15;
	chars[250] = 5;

	huf->Compress(data,chars);
	huf->recorrerHojas();
}

}
