/*
 * RunLenght.h
 *
 *  Created on: 09/05/2014
 *      Author: ari
 */

#ifndef RUNLENGHT_H_
#define RUNLENGHT_H_

#include "DataBlock.h"

namespace std {
class Run{
public:
	Run();
	virtual ~Run();
	unsigned char symbol;
	unsigned short int count; //Runs màximos de 256 + 4?
};

class RunLenght {
public:
	RunLenght();
	virtual ~RunLenght();
	DataBlock * encode(DataBlock * src);
	DataBlock * decode(DataBlock * src);
	unsigned int * getStats();
	unsigned char getEscapeChar();
private:
	char escape;
	unsigned int stats[256];
	Run getRun(vector<unsigned char >::iterator, unsigned long int);
	void encodeRun(DataBlock * dst, Run r);
	void decodeRun(DataBlock * dst, Run r);
	void resetStats();
};




} /* namespace std */

#endif /* RUNLENGHT_H_ */
