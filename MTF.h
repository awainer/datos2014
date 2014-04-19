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
	unsigned char * b(unsigned long int blockLenght,char * blockData);
private:
	void resetStatus();
	void updateStatus(unsigned char);
	unsigned char get_current_position(unsigned char);

	unsigned short int initial_vector[256];

	  list<unsigned short int> symbol_status;

};

} /* namespace std */

#endif /* MTF_H_ */
