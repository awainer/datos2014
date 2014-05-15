/*
 * CompressedFileReader.h
 *
 *  Created on: 14/05/2014
 *      Author: ari
 */

#ifndef COMPRESSEDFILEREADER_H_
#define COMPRESSEDFILEREADER_H_
#include "DataBlock.h"
#include <fstream>
namespace std {

class CompressedFileReader {
public:
	//CompressedFileReader();
	CompressedFileReader(string path);
	DataBlock * getBlock();
	virtual ~CompressedFileReader();
private:
	uint32_t nextBlockSizeInBits;
	ifstream fileStream;
};

} /* namespace std */

#endif /* COMPRESSEDFILEREADER_H_ */
