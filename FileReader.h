/*
 * FileReader.h
 *
 *  Created on: 12/05/2014
 *      Author: ari
 */

#ifndef FILEREADER_H_
#define FILEREADER_H_
#include "DataBlock.h"
#include <fstream>

namespace std {

class FileReader {
public:
	FileReader();
	FileReader(string path);
	DataBlock * getBlock();
	bool hasBlocksLeft();
	string getFilePath();
	virtual ~FileReader();
	void close();

private:
	unsigned long long int determineBlockSize(unsigned long long int fileSize);
	ifstream fileStream;
	unsigned long long int blockSize;
	bool lastBlockRead;
};

} /* namespace std */

#endif /* FILEREADER_H_ */
