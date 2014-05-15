/*
 * MTF.h
 *
 *  Created on: 18/04/2014
 *      Author: ari
 */

#ifndef MTF_H_
#define MTF_H_

#include <list>
#include "DataBlock.h"
namespace std {

class MTF {
public:
	MTF();
	virtual ~MTF();
	DataBlock * encode(DataBlock * blockData);
	DataBlock * decode(DataBlock * blockData);
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
