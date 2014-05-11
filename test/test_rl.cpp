/*
 * test_rl.cpp
 *
 *  Created on: 10/05/2014
 *      Author: ari
 */
#include "gtest/gtest.h"
#include  "../DataBlock.h"
#include  "../RunLenght.h"

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
	result=encoder->encode(db);
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

}
