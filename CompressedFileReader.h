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
	bool hasBlocksLeft();
	DataBlock * getBlock();
	virtual ~CompressedFileReader();
	void close();
private:
	uint32_t nextBlockSizeInBits;
	ifstream fileStream;
};

} /* namespace std */

#endif /* COMPRESSEDFILEREADER_H_ */
