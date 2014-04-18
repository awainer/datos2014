/*
 * test_mtf.cpp
 *
 *  Created on: 18/04/2014
 *      Author: ari
 */

#include "gtest/gtest.h"
#include "../MTF.h"

#include <iostream>
namespace std{
TEST(MTFTest, unTest) {
	MTF * miTrans = new MTF();
	char * miBloque = "CADORCHA";
	cout << "test cadorcha" << endl;
	int tamanio =  8;
	unsigned char * r = miTrans->b(tamanio,miBloque);
	for (int i=0; i<tamanio; i++)
		cout << (int)r[i] << endl;
}
}
