/*
 * test_mtf.cpp
 *
 *  Created on: 18/04/2014
 *      Author: ari
 */

#include "gtest/gtest.h"
#include "../MTF.h"


namespace std{
TEST(MTFTest, caaaaxcha) {
	MTF * miTrans = new MTF();
	unsigned char  miBloque[] = {'C','A','A','A','X','C','H','A'};
	unsigned char  bloqueMovido[] = {59,61,1,0,38,3,55,0};
	int tamanio =  sizeof(miBloque);
	unsigned char * r = miTrans->b(tamanio,miBloque);

	for(unsigned int i=0;i<sizeof(r);i++)
	{
		cerr << (int)r[i] << endl;
		ASSERT_EQ(r[i],bloqueMovido[i]);
	}

}

TEST(MTFTest, unchar) {
	MTF * miTrans = new MTF();
	unsigned char  miBloque[] = {'a'};
	int tamanio =  sizeof(miBloque);
	unsigned char * r = miTrans->b(tamanio,miBloque);
	ASSERT_EQ(*r,6);

}

TEST(MTFTest, vacio) {
	MTF * miTrans = new MTF();
	unsigned char  miBloque[] = {};
	int tamanio =  sizeof(miBloque);
	unsigned char * r = miTrans->b(tamanio,miBloque);
	ASSERT_EQ(*r,*miBloque);

}

}



