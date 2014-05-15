/*
 * CompressedFileWriter.cpp
 *
 *  Created on: 14/05/2014
 *      Author: ari
 */

#include "CompressedFileWriter.h"
#include <stdint.h>

namespace std {

CompressedFileWriter::CompressedFileWriter() {
	// TODO Auto-generated constructor stub

}

CompressedFileWriter::CompressedFileWriter(string path) {
	this->fileStream.open(path.c_str(), ios::out | ios::binary);
}

void CompressedFileWriter::writeBlockHeader(uint32_t size){
	// Esto es una chanchada, pero no se me ocurre otra forma.
	// La idea es leer 32 bits de a 8, para poder escribirlos
	char * aux = (char *) &size;
	this->fileStream.write(aux,4);

}
void CompressedFileWriter::writeBlock(DataBlock* block) {
	uint32_t sizeInBits = block->getSizeInBits();
	vector<unsigned char>::iterator it = block->getIterator();

	this->writeBlockHeader(sizeInBits);
	this->fileStream.write((char*)&(it[0]),block->getSizeInBytes());
}

void CompressedFileWriter::close() {
	this->fileStream.close();
}

CompressedFileWriter::~CompressedFileWriter() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
