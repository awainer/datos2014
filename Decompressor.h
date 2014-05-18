/*
 * Decompressor.h
 *
 *  Created on: 17/05/2014
 *      Author: ari
 */

#ifndef DECOMPRESSOR_H_
#define DECOMPRESSOR_H_
#include <string>
namespace std {

class Decompressor {
public:
	Decompressor();
	void decompress(string file);
	virtual ~Decompressor();
private:
	string removeExtension(string path);
	string extension;
};

} /* namespace std */

#endif /* DECOMPRESSOR_H_ */
