/*
 * DataBlock.h
 *
 *  Created on: 20/04/2014
 *      Author: ari
 */

#ifndef DATABLOCK_H_
#define DATABLOCK_H_

#include <cstdint>
#include <vector>
namespace std {

class DataBlock {
	//const unsigned char masks ={1,3,7,15,31,63,127.255};
public:
	DataBlock();
	//void addBytes(unsigned char * data, unsigned long int count);
	void addByte(unsigned char data);
	void addBits(unsigned char data, unsigned char count);
	unsigned long int getSizeInBytes();
	unsigned long int getSizeInBits();
	char getRemainingBits();
	unsigned char * getalignedData();
	virtual ~DataBlock();
private:
	vector<unsigned char> data;
	unsigned char remaining_bits,remaining_bits_count;
};

} /* namespace std */

#endif /* DATABLOCK_H_ */
