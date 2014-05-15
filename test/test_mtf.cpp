/*
 * test_mtf.cpp
 *
 *  Created on: 18/04/2014
 *      Author: ari
 */

#include "gtest/gtest.h"
#include "../MTF.h"
#include "../DataBlock.h"

namespace std{

TEST(MTFTest, caaaaxcha) {
	MTF * miTrans = new MTF();
	vector<unsigned char>::iterator it;
	unsigned char  miBloqueInit[] = {'C','A','A','A','X','C','H','A'};
	//unsigned char  bloqueMovido[] = {59,61,1,0,38,3,55,0};
	unsigned char  bloqueMovido[] = {59,61,1,0,38,3,55,0};
	DataBlock * miBloque = new DataBlock();
	for(unsigned int i=0; i<sizeof(miBloqueInit); i++)
		miBloque->addByte(miBloqueInit[i]);
	DataBlock * r = miTrans->encode(miBloque);
	it = r->getIterator();
	for(unsigned int i=0;i<sizeof(r);i++)
	{
		ASSERT_EQ(it[i],bloqueMovido[i]);
	}
	delete r;
	delete miTrans;
	delete miBloque;
}

TEST(MTFTest, caaaaxcha_decode) {
	MTF * miTrans = new MTF();
	vector<unsigned char>::iterator it;
	unsigned char  bloqueMovido[] = {'C','A','A','A','X','C','H','A'};
	unsigned char  miBloqueInit[] = {59,61,1,0,38,3,55,0};

	DataBlock * miBloque = new DataBlock();
		for(unsigned int i=0; i<sizeof(miBloqueInit); i++)
			miBloque->addByte(miBloqueInit[i]);
	DataBlock * r = miTrans->decode(miBloque);
	it=r->getIterator();
	for(unsigned int i=0;i<sizeof(r);i++)
	{
		ASSERT_EQ(it[i],bloqueMovido[i]);
	}
	delete miBloque;
	delete miTrans;
	delete r;
}

TEST(MTFTest, unchar) {
	MTF * miTrans = new MTF();
	DataBlock *  miBloque = new DataBlock();
	miBloque->addByte('a');
	DataBlock * r = miTrans->encode(miBloque);
	vector<unsigned char>::iterator it=r->getIterator();
	ASSERT_EQ(*it,6);
	delete miTrans;
	delete miBloque;
	delete r;
}

TEST(MTFTest, fullcycle) {
	MTF * miTrans = new MTF();
	unsigned char  originit[] = {87, 71, 192, 112, 177, 122, 215, 125, 148, 202, 95, 42, 2, 83, 24, 57, 217, 165, 164,
			127, 175, 105, 18, 189, 181, 95, 150, 39, 54, 212, 67, 101, 53, 161, 159, 162, 68, 166,
			226, 122, 52, 31, 169, 141, 136, 150, 253, 143, 251, 152, 35, 167, 4, 117, 204, 45, 234,
			59, 230, 233, 125, 108, 53, 180, 149, 151, 185, 31, 60, 242, 161, 161, 236, 208, 119, 84,
			2, 218, 203, 157, 118, 20, 171, 246, 160, 0, 224, 12, 105, 61, 30, 75, 38, 251, 98, 210,
			244, 42, 155, 153, 201, 132, 30, 223, 67, 116, 226, 131, 48, 242, 62, 180, 95, 103, 162,
			187, 246, 212, 47, 222, 57, 11, 195, 79, 17, 107, 210, 94, 4, 69, 166, 139, 114, 223, 103,
			190, 94, 24, 225, 250, 65, 69, 121, 14, 159, 98, 246, 34, 103, 91, 99, 216, 195, 109, 51};
	DataBlock * r;
	DataBlock * s;
	DataBlock * orig = new DataBlock();
	vector<unsigned char>::iterator it1,it2;

	for(unsigned int i=0;i<sizeof(originit);i++)
		orig->addByte(originit[i]);
	r = miTrans->encode(orig);
	s = miTrans->decode(r);
	it1 = orig->getIterator();
	it2 = s->getIterator();
	for(unsigned int i=0;i<sizeof(orig);i++)
		ASSERT_EQ(it1[i],it2[i]);
	delete miTrans;
	delete r;
	delete s;
	delete orig;
}

TEST(MTFTest, vacio) {
	MTF * miTrans = new MTF();
	DataBlock * miBloque= new DataBlock();

	DataBlock* r = miTrans->encode(miBloque);
	ASSERT_FALSE(r->getSizeInBytes());
	ASSERT_FALSE(r->getSizeInBits());
	delete miTrans;
	delete r;
	delete miBloque;

}




}
