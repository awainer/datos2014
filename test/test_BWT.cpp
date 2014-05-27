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

	unsigned char  expectedResultVector[] = {'C','A','H','A','A','X','C','A'};
	/**
	 * Las rotaciones, ordenadas alfabeticamente:
	 * 0 AAAXCHAC <--Esta deberia ser la mas chica
	 * 1 AAXCHACA
	 * 2 ACAAAXCH
	 * 3 AXCHACAA
	 * 4 CAAAXCHA
	 * 5 CHACAAAX
	 * 6 HACAAAXC
	 * 7 XCHACAAA
	 *
	 *  El resultado (ultima columna): CAHAAXCA nro string original
	 *  Nro de stirng original: 4
	 */

	DataBlock * orig = new DataBlock();
	DataBlock * result;
	BWT * bwt = new BWT();

	// Agrego la columna original
	for (unsigned int i=0; i<sizeof(initVector);i++)
		orig->addByte(initVector[i]);

	result = bwt->transform(orig);
	ASSERT_EQ(result->getSizeInBytes()-4,orig->getSizeInBytes());
	auto it = result->getIterator();
	for (unsigned int i=0; i<sizeof(initVector);i++)
		ASSERT_EQ(it[i+4],expectedResultVector[i]);

	ASSERT_EQ(*((uint32_t*)&it[0]),4);
//	for (unsigned int i=0; i<4;i++)
//			cerr << "LALA" << (int)it[i] << endl;

	it = result->getIterator();
	// Verifico el número de columna original
/*	for(int i=0;i<4;i++)
		ASSERT_EQ(it[i],*((char *) (i +&row)));*/
//		orig->addByte( *((char *) (i +&row)) );

	delete bwt;
	delete orig;
	delete result;

}


TEST(BWTTEST,testSortUnsortShortBlock){
	unsigned char  initVector[] = {'C','A','A','A','X','C','H','A'};

	//unsigned char  expectedResultVector[] = {'C','A','H','A','A','X','C','A'};

	unsigned char  expectedResultVector[] = {'C','A','H','A','A','X','C','A'};
	/**
	 * Las rotaciones, ordenadas alfabeticamente:
	 * 0 AAAXCHAC <--Esta deberia ser la mas chica
	 * 1 AAXCHACA
	 * 2 ACAAAXCH
	 * 3 AXCHACAA
	 * 4 CAAAXCHA
	 * 5 CHACAAAX
	 * 6 HACAAAXC
	 * 7 XCHACAAA
	 *
	 *  El resultado (ultima columna): CAHAAXCA nro string original
	 *  Nro de stirng original: 4
	 */

	DataBlock * orig = new DataBlock();
	DataBlock * result;
	BWT * bwt = new BWT();

	// Agrego la columna original
	for (unsigned int i=0; i<sizeof(initVector);i++)
		orig->addByte(initVector[i]);

	result = bwt->transform(orig);
	ASSERT_EQ(result->getSizeInBytes()-4,orig->getSizeInBytes());
	auto it = result->getIterator();
	for (unsigned int i=0; i<sizeof(initVector);i++)
		ASSERT_EQ(it[i+4],expectedResultVector[i]);

	ASSERT_EQ(*((uint32_t*)&it[0]),4);

	// Unsort
	DataBlock * result_orig;
	result_orig = bwt->untransform(result);
	ASSERT_EQ(result_orig->getSizeInBytes(),orig->getSizeInBytes());

	auto it_orig = orig->getIterator();
	auto it_result = result_orig->getIterator();

	for (unsigned int i=0; i<orig->getSizeInBytes();i++){
			ASSERT_EQ(*it_orig,*it_result);
			it_orig++;
			it_result++;
	}
	delete bwt;
	delete orig;
	delete result_orig;
	delete result;

}


TEST(BWTTEST,testRandom100){
	DataBlock * orig = new DataBlock();
	DataBlock * result;
	BWT * bwt = new BWT();

	unsigned char r;
	for(int i=0;i<100;i++){
		r = rand() % 5 + 'a'; //una letra random entre a y e, como para que hay algun run
		orig->addByte(r);
	}
/*
	// SACAR: solo muestro la cadena original
	auto itaux = orig->getIterator();
	cerr << "cadena original: ";
	for (unsigned int i=0; i<orig->getSizeInBytes();i++){
		cerr << (*itaux);
		itaux++;
	}
	cerr << endl;
*/
	result = bwt->transform(orig);
	ASSERT_EQ(result->getSizeInBytes()-4,orig->getSizeInBytes());
	//auto it = result->getIterator();

	// Unsort
	DataBlock * result_orig;
	result_orig = bwt->untransform(result);
	ASSERT_EQ(result_orig->getSizeInBytes(),orig->getSizeInBytes());

/*	auto it_orig = orig->getIterator();
	auto it_result = result_orig->getIterator();

	cerr << "voy descomprimiendo esta cosa: ";
	for (unsigned int i=0; i<orig->getSizeInBytes();i++){
		ASSERT_EQ(*it_orig,*it_result);
		cerr << (*it_result);
		it_orig++;
		it_result++;
	}
	cerr << endl;
*/

	delete bwt;
	delete orig;
	delete result_orig;
	delete result;

}


TEST(BWTTEST,testRandomBiGGG){
	DataBlock * orig = new DataBlock();
	DataBlock * result;
	BWT * bwt = new BWT();

	unsigned char r;
	for(int i=0;i<10000;i++){
		r = rand() % 5 + 'a'; //una letra random entre a y e, como para que hay algun run
		orig->addByte(r);
	}
/*
	// SACAR: solo muestro la cadena original
	auto itaux = orig->getIterator();
	cerr << "cadena original: ";
	for (unsigned int i=0; i<orig->getSizeInBytes();i++){
		cerr << (*itaux);
		itaux++;
	}
	cerr << endl;
*/
	result = bwt->transform(orig);
	ASSERT_EQ(result->getSizeInBytes()-4,orig->getSizeInBytes());
//	auto it = result->getIterator();

	// Unsort
	DataBlock * result_orig;
	result_orig = bwt->untransform(result);
	ASSERT_EQ(result_orig->getSizeInBytes(),orig->getSizeInBytes());

//	auto it_orig = orig->getIterator();
//	auto it_result = result_orig->getIterator();
/*
	cerr << "voy descomprimiendo esta cosa: ";
	for (unsigned int i=0; i<orig->getSizeInBytes();i++){
		ASSERT_EQ(*it_orig,*it_result);
		cerr << (*it_result);
		it_orig++;
		it_result++;
	}
	cerr << endl;
*/

	delete bwt;
	delete orig;
	delete result_orig;
	delete result;

}


}
