/*
 * FileWriter.h
 *
 *  Created on: 17/05/2014
 *      Author: ari
 */

#ifndef FILEWRITER_H_
#define FILEWRITER_H_
#include <string>
#include <fstream>
#include "DataBlock.h"
namespace std {

class FileWriter {
public:
	FileWriter(string path);
	void writeBlock(DataBlock * db);
	void close();
	virtual ~FileWriter();
private:
	ofstream fileStream;
};

} /* namespace std */

#endif /* FILEWRITER_H_ */
