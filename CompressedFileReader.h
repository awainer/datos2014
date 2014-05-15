/*
 * CompressedFileReader.h
 *
 *  Created on: 14/05/2014
 *      Author: ari
 */

#ifndef COMPRESSEDFILEREADER_H_
#define COMPRESSEDFILEREADER_H_
#include "DataBlock.h"
namespace std {

class CompressedFileReader {
public:
	CompressedFileReader();
	CompressedFileReader(string path);
	DataBlock * getBlock();
	virtual ~CompressedFileReader();
private:
	long int nextBlockSizeInBits;
};

} /* namespace std */

#endif /* COMPRESSEDFILEREADER_H_ */
