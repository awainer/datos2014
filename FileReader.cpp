/*
 * FileReader.cpp
 *
 *  Created on: 12/05/2014
 *      Author: ari
 */

#include "FileReader.h"
#include <iostream>
#include <sys/stat.h>
namespace std {


FileReader::FileReader(string path) {

	struct stat filestatus;
	if(stat(path.c_str(), &filestatus) != 0)
		throw( "no se puede abrir el archivo, fijate que exista y tenga permisos.");
	this->blockSize = this->determineBlockSize(filestatus.st_size);
	this->fileStream.open(path.c_str(), ios::out | ios::binary);
	this->lastBlockRead = 0;
}

DataBlock* FileReader::getBlock() {
	vector<unsigned char> * vec;

    return NULL;
}

bool FileReader::hasBlocksLeft() {
	//stub
	return false;
}



FileReader::~FileReader() {
	// TODO Auto-generated destructor stub
}

unsigned long long int FileReader::determineBlockSize(unsigned long long int fileSize) {
	/**
	 * Posibles tamanios de bloque:
	 *  bloque |archivo
	 *  16K     < 128K
	 *  128K    < 512K
	 *  4M      < 16M
	 *  64M     < 256M
	 *  512M    < 1G
	 *
	 *  Atencion! el codigo que viene a continuacion es muy feo. Yo avise.
	 */
	unsigned long int sizes[] = {
			1024*1024*1024,  1024*1024*512,
			1024*1024*256,   1024*1024*64,
			1024*1024*16,    1024*1024*4,
			1024*512,        1024*128,
			1024*128,        1024*16
			};
	unsigned long long int result;
	//Ineficente? Si! Son 4 iteraciones por archivo....
	for(unsigned int i=0;i<sizeof(sizes)-1; i+=2){
		if (fileSize < sizes[i])
			result = sizes[i+1];
	}
	return result;

}

} /* namespace std */
