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
	DataBlock(vector<unsigned char> *v);
	DataBlock(vector<unsigned char> *v, unsigned char remaining_bits);
	//iterator begin();
	// iterator end();
	//void addBytes(unsigned char * data, unsigned long int count);
	void addByte(unsigned char data);
	void addBits(unsigned char data, unsigned char count);
	void addDataBlock(DataBlock * db);
	unsigned long int getSizeInBytes();
	unsigned long int getSizeInBits();
	char getRemainingBits();
	vector<unsigned char>::iterator getIterator();
	virtual ~DataBlock();
private:
	vector<unsigned char> * data;
	unsigned char remaining_bits_count;
	//vector<unsigned char>::iterator last;
	char masks[8];
	void initialize();
	//unsigned char masks[8];
};

} /* namespace std */

#endif /* DATABLOCK_H_ */
