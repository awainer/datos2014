/*
 * MTF.h
 *
 *  Created on: 18/04/2014
 *      Author: ari
 */

#ifndef MTF_H_
#define MTF_H_

#include <list>

namespace std {

class MTF {
public:
	MTF();
	virtual ~MTF();
	unsigned char * encode(unsigned long int blockLenght,unsigned char * blockData);
	unsigned char * decode(unsigned long int blockLenght,unsigned char * blockData);
private:
	void resetStatus();
	void updateStatus(unsigned char);
	unsigned char getCurrentPosition(unsigned char);
	unsigned char getElementAt(unsigned short int postition);

	unsigned short int initial_vector[256];

	  list<unsigned short int> symbol_status;

};

} /* namespace std */

#endif /* MTF_H_ */
