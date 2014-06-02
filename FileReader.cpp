/*
 * FileReader.cpp
 *
 *  Created on: 12/05/2014
 *      Author: ari
 */

#include "FileReader.h"

#include <sys/stat.h>
namespace std {


FileReader::FileReader(string path) {

	struct stat filestatus;

	//if(stat(path.c_str(), &filestatus) != 0)
	//	throw( "no se puede abrir el archivo, fijate que exista y tenga permisos.");
	stat(path.c_str(), &filestatus);
	//cerr << "Filesize: " <<  filestatus.st_size << endl;
	this->blockSize = this->determineBlockSize(filestatus.st_size);
	this->fileStream.open(path.c_str(), ios::in | ios::binary);
	this->lastBlockRead = false;
}

DataBlock* FileReader::getBlock() {
	vector<unsigned char> * vec = new vector<unsigned char>(this->blockSize);
	vector<unsigned char>::iterator it = vec->begin();
	DataBlock * db=NULL;

	if(!this->lastBlockRead){
		this->fileStream.read((char*)&(it[0]),this->blockSize);
		this->lastBlockRead = this->fileStream.eof();
		//Ajusto el ultimo bloque
		if (this->lastBlockRead)
			vec->resize(this->fileStream.gcount());
		db = new DataBlock(vec);
		return db;
	}else{
		return NULL;
	}
}

bool FileReader::hasBlocksLeft() {
	return not this->lastBlockRead;

}



FileReader::~FileReader() {
	this->fileStream.close();
}

unsigned long long int FileReader::determineBlockSize(unsigned long long int fileSize) {
	/**
	 * Posibles tamanios de bloque:
	 *  bloque |archivo
	 *  16K     < 128K
	 *  128K    < 512K
	 *  4M      < 16M
	 *  8M     < 256M
	 *  32M    < 1G
	 *
	 *  Atencion! el codigo que viene a continuacion es muy feo. Yo avise.
	 */


	vector<unsigned long int> sizes = {
			1024*1024*1024,  1024*1024*32,
			1024*1024*256,   1024*1024*8,
			1024*1024*16,    1024*1024*4,
			1024*512,        1024*128,
			1024*128,        1024*16
			};
	unsigned long long int result=0;
	//Ineficente? Si! Son 4 iteraciones por archivo....
	for(unsigned int i=0;i<sizes.size(); i+=2){
		//cerr << " z " << sizeof(sizes) << "fs: " << fileSize << "  i: " << i << " sizes[i] " << sizes[i] << endl;
		if (fileSize < sizes[i])
			result = sizes[i+1];
	}
	//cerr << "DEBUG: determined block size: " << result << endl;
	return result;

}

void FileReader::close() {
	this->fileStream.close();
}

} /* namespace std */
