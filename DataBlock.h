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
#include <array>
namespace std {

class DataBlock {
public:
	DataBlock();
	//void addBytes(unsigned char * data, unsigned long int count);
	void addByte(unsigned char data);
	void addBits(unsigned char data, unsigned char count);
	unsigned long int getSizeInBytes();
	unsigned long int getSizeInBits();
	char getRemainingBits();
	vector<unsigned char>::iterator getIterator();
	virtual ~DataBlock();
private:
	vector<unsigned char> data;
	unsigned char remaining_bits,remaining_bits_count;
	char  masks[8];
	//unsigned char masks[8];
};

} /* namespace std */

#endif /* DATABLOCK_H_ */
