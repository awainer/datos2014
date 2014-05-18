/*
 * test_BWT.cpp
 *
 *  Created on: 27/04/2014
 *      Author: tavo
 */

#include "gtest/gtest.h"
#include "../BWT.h"
#include "../DataBlock.h"

namespace std{

TEST(BWTTEST,testSortShortBlock){
	unsigned char  initVector[] = {'C','A','A','A','X','C','H','A'};

	//unsigned char  expectedResultVector[] = {'C','A','H','A','A','X','C','A'};
	/**
	 * Las rotaciones, ordenadas alfabeticamente:
	 *  AAAXCHAC <--Esta deberia ser la mas chica
	 *  AAXCHACA
	 *  ACAAAXCH
	 *  AXCHACAA
	 *  CAAAXCHA
	 *  CHACAAAX
	 *  HACAAAXC
	 *  XCHACAAA
	 *
	 *  El reusltado (ultima columna): CAHAAXCA
	 */

	DataBlock * orig = new DataBlock();
	DataBlock * result;
	BWT * bwt = new BWT();
	for (unsigned int i=0; i<sizeof(initVector);i++)
		orig->addByte(initVector[i]);

	result = bwt->transform(orig);
	/*ASSERT_EQ(result->getSizeInBytes()+4,orig->getSizeInBytes());
	auto it = result->getIterator();
	for (unsigned int i=0; i<sizeof(initVector);i++)
		ASSERT_EQ(it[i+4],expectedResultVector[i]);
*/
	delete bwt;
	delete orig;
	delete result;

}






}

/*TEST(BWTTest, caaaaxcha) {
	MTF * miTrans = new MTF();
	unsigned char  miBloque[] = {'C','A','A','A','X','C','H','A'};
	unsigned char  bloqueMovido[] = {59,61,1,0,38,3,55,0};
	int tamanio =  sizeof(miBloque);
	unsigned char * r = miTrans->encode(tamanio,miBloque);

	for(unsigned int i=0;i<sizeof(r);i++)
	{
		ASSERT_EQ(r[i],bloqueMovido[i]);
	}

}

TEST(BWTTest, caaaaxcha_decode) {
	MTF * miTrans = new MTF();
	unsigned char  bloqueMovido[] = {'C','A','A','A','X','C','H','A'};
	unsigned char  miBloque[] = {59,61,1,0,38,3,55,0};
	int tamanio =  sizeof(miBloque);
	unsigned char * r = miTrans->decode(tamanio,miBloque);

	for(unsigned int i=0;i<sizeof(r);i++)
	{
		ASSERT_EQ(r[i],bloqueMovido[i]);
	}

}

TEST(BWTTest, unchar) {
	MTF * miTrans = new MTF();
	unsigned char  miBloque[] = {'a'};
	int tamanio =  sizeof(miBloque);
	unsigned char * r = miTrans->encode(tamanio,miBloque);
	ASSERT_EQ(*r,6);

}
TEST(BWTTest, fullcycle) {
	MTF * miTrans = new MTF();
	unsigned char  orig[] = {87, 71, 192, 112, 177, 122, 215, 125, 148, 202, 95, 42, 2, 83, 24, 57, 217, 165, 164,
			127, 175, 105, 18, 189, 181, 95, 150, 39, 54, 212, 67, 101, 53, 161, 159, 162, 68, 166,
			226, 122, 52, 31, 169, 141, 136, 150, 253, 143, 251, 152, 35, 167, 4, 117, 204, 45, 234,
			59, 230, 233, 125, 108, 53, 180, 149, 151, 185, 31, 60, 242, 161, 161, 236, 208, 119, 84,
			2, 218, 203, 157, 118, 20, 171, 246, 160, 0, 224, 12, 105, 61, 30, 75, 38, 251, 98, 210,
			244, 42, 155, 153, 201, 132, 30, 223, 67, 116, 226, 131, 48, 242, 62, 180, 95, 103, 162,
			187, 246, 212, 47, 222, 57, 11, 195, 79, 17, 107, 210, 94, 4, 69, 166, 139, 114, 223, 103,
			190, 94, 24, 225, 250, 65, 69, 121, 14, 159, 98, 246, 34, 103, 91, 99, 216, 195, 109, 51};
	unsigned char * r;
	unsigned char * s;
	r = miTrans->encode(sizeof(orig),orig);
	s = miTrans->decode(sizeof(orig),r);
	free(r);
	for(unsigned int i=0;i<sizeof(orig);i++)
		ASSERT_EQ(orig[i],s[i]);
}

TEST(BWTTest, vacio) {
	MTF * miTrans = new MTF();
	unsigned char  miBloque[] = {};
	int tamanio =  sizeof(miBloque);
	unsigned char * r = miTrans->encode(tamanio,miBloque);
	ASSERT_EQ(*r,*miBloque);

}


}
*/
