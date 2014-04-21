/*
 * test_datablock.cpp
 *
 *  Created on: 20/04/2014
 *      Author: ari
 */

#include "../contrib/gtest/gtest.h"
#include "../DataBlock.h"
namespace std{
TEST(DataBlockTest,addbyte){
	DataBlock * block = new DataBlock((unsigned char*)NULL, 0,0,0);
	unsigned char  bytesToAdd[]="garompa";//{'g','a','r','o','m','p','a'};
	unsigned char * ptr = bytesToAdd;
	block->addBytes(ptr,7); // Deliberadamente omito el '\0'
	ASSERT_EQ(block->getSizeInBytes(),7);
}

}


