/*
 * Compressor.h
 *
 *  Created on: 17/05/2014
 *      Author: ari
 */

#ifndef COMPRESSOR_H_
#define COMPRESSOR_H_
#include <string>
namespace std {

class Compressor {
public:
	Compressor();
	virtual ~Compressor();
	void compress(string file);
private:
	string extension;
};

} /* namespace std */

#endif /* COMPRESSOR_H_ */
