/*
 * CompressedFileWriter.h
 *
 *  Created on: 14/05/2014
 *      Author: ari
 */

#ifndef COMPRESSEDFILEWRITER_H_
#define COMPRESSEDFILEWRITER_H_

#include <fstream>
#include <string>
#include "DataBlock.h"

namespace std {

class CompressedFileWriter {
public:
	CompressedFileWriter();
	CompressedFileWriter(string path);
	void writeBlock(DataBlock * block);
	void close();
	virtual ~CompressedFileWriter();
private:
	ofstream fileStream;
	void writeBlockHeader(uint32_t size);
};

} /* namespace std */

#endif /* COMPRESSEDFILEWRITER_H_ */
