/*
 * DataBlock.h
 *
 *  Created on: 20/04/2014
 *      Author: ari
 */

#ifndef DATABLOCK_H_
#define DATABLOCK_H_

#include <cstdint>
namespace std {

class DataBlock {
public:
	DataBlock(unsigned char * data, unsigned long int size_in_bytes, char remaining_bits, char remaining_bits_count);
	void addBytes(unsigned char * data, unsigned long int count);
	void addBits(unsigned char data, unsigned char count);
	unsigned long int getSizeInBytes();
	unsigned long int getSizeInBits();
	char getRemainingBits();
	unsigned char * getalignedData();
	virtual ~DataBlock();
private:
	unsigned char * data;
	unsigned char * next_byte;
	unsigned long int size_in_bytes;
	char	remaining_bits;
	/**
	 * Este union tiene el objetivo de poder adicionar bits al último byte.
	 * La idea es
	 */
	union {
		struct{
		uint8_t last_byte;
		uint8_t first_byte;
		}parts;
		uint16_t all;
	} incomplete_byte;
};

} /* namespace std */

#endif /* DATABLOCK_H_ */
