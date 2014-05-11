/*
 * test_rl.cpp
 *
 *  Created on: 10/05/2014
 *      Author: ari
 */
#include "gtest/gtest.h"
#include  "../DataBlock.h"
#include  "../RunLenght.h"
#include <cstdlib>

namespace std{

TEST(TestRLE, TestEncode){
	//unsigned char data[] = { 23,23,23,22,23,23,12,76,25,25,25,25,255,25,34,255,255,16 };
	unsigned char data[] = "ABBBCAAAADEFDFKJ";
	unsigned char expected_result[] = {'A','B','B','B','C','$','A',0,'D','E','F','D','F','K','J'};
	vector<unsigned char>::iterator it;
	DataBlock * db = new DataBlock();
	DataBlock * result;
	RunLenght * encoder = new RunLenght();
	for (unsigned int i=0; i < sizeof(data) -1 ; i++)
		db->addByte(data[i]);
	result=encoder->encode(db);
	it = result->getIterator();
	for(unsigned long int i=0;i<result->getSizeInBytes()-1;i++){
		ASSERT_EQ(it[i],expected_result[i]);
	}

	delete db;
	delete result;
	delete encoder;
}

TEST(TestRLE, UnMatchStats){
	unsigned char data[] = "ZZZZ";
	unsigned int *  stats;
	DataBlock * db = new DataBlock();
	DataBlock * result;
	RunLenght * encoder = new RunLenght();
	for (unsigned int i=0; i < sizeof(data) -1 ; i++)
		db->addByte(data[i]);
	result=encoder->encode(db);
	stats = encoder->getStats();
//	for(int i=0;i<256;i++)
//		cerr << i << " " << stats[i] << endl;
	ASSERT_EQ(3,result->getSizeInBytes());
	ASSERT_EQ(1,stats['Z']);
	ASSERT_EQ(1,stats[0]); //count en offset 4!
	ASSERT_EQ(1,stats[encoder->getEscapeChar()]);
	delete db;
	delete result;
	delete encoder;
}
TEST(TestRLE, UnMatchStatsYotroNoMatch){
	unsigned char data[] = "AZBCZZZZZQ";
	unsigned int *  stats;
	DataBlock * db = new DataBlock();
	DataBlock * result;
	RunLenght * encoder = new RunLenght();
	for (unsigned int i=0; i < sizeof(data) -1 ; i++)
		db->addByte(data[i]);
	result = encoder->encode(db);
	stats = encoder->getStats();
//	for(int i=0;i<256;i++)
//		cerr << i << " " << stats[i] << endl;
	ASSERT_EQ(8,result->getSizeInBytes());
	ASSERT_EQ(2,stats['Z']);
	ASSERT_EQ(1,stats[1]);
	ASSERT_EQ(1,stats['A']);
	ASSERT_EQ(1,stats['B']);
	ASSERT_EQ(1,stats['C']);
	ASSERT_EQ(1,stats['Q']);
	ASSERT_EQ(1,stats[encoder->getEscapeChar()]);
	delete db;
	delete result;
	delete encoder;
}

TEST(TestRLE, MatchDemasiadoLargo){

	unsigned int *  stats;
	DataBlock * db = new DataBlock();
	DataBlock * result;
	RunLenght * encoder = new RunLenght();
	for (unsigned int i=0; i<900 ; i++)
		db->addByte('X');

	// Un match demasiado largo se debe representar como
	// varios matches.
	// 900 = 260 + 260 + 260 + 120 (offset -4)
	result = encoder->encode(db);
	stats = encoder->getStats();

	vector<unsigned char>::iterator it = result->getIterator();
//	for(int i=0;i<result->getSizeInBytes(); i++)
//		cerr << it[i] << " " << (int) it[i] << endl;
	ASSERT_EQ(12,result->getSizeInBytes());
	ASSERT_EQ(4,stats['X']);
	ASSERT_EQ(4,stats[encoder->getEscapeChar()]);
	//ASSERT_EQ(1,stats[116]);
	ASSERT_EQ(3,stats[255]); //full
	delete db;
	delete result;
	delete encoder;
}

TEST(TestRLE, encodeAndDecode){

	DataBlock * orig = new DataBlock();
	DataBlock * encoded,*decoded;
	RunLenght * encoder = new RunLenght();
	vector<unsigned char>::iterator it1,it2;
	unsigned char r;
	for(int i=0;i<5000;i++){
		r = rand() % 5 + 'a'; //una letra random entre a y e, como para que hay algun run
		orig->addByte(r);
	}
	encoded = encoder->encode(orig);
	encoder->decode(encoded);
	ASSERT_LT(encoded->getSizeInBytes(),orig->getSizeInBytes());
	decoded = encoder->decode(encoded);
	delete encoded;

	it1 = orig->getIterator();
	it2 = decoded->getIterator();
	ASSERT_EQ(decoded->getSizeInBytes(),orig->getSizeInBytes());
}


}
