/*
 * FileWriter.cpp
 *
 *  Created on: 17/05/2014
 *      Author: ari
 */

#include "FileWriter.h"

namespace std {

FileWriter::FileWriter(string path) {
	this->fileStream.open(path.c_str(), ios::out | ios::binary);
}

void FileWriter::writeBlock(DataBlock* db) {
	vector<unsigned char>::iterator it = db->getIterator();
	this->fileStream.write((char*)&(it[0]),db->getSizeInBytes());
}

void FileWriter::close() {
}

FileWriter::~FileWriter() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
