/*
 * Compressor.cpp
 *
 *  Created on: 17/05/2014
 *      Author: ari
 */

#include "Compressor.h"
#include "DataBlock.h"
#include "FileReader.h"
#include "BWT.h"
#include "MTF.h"
#include "RunLenght.h"
#include "CompressedFileWriter.h"
#include <iostream>
#include "HUFFMAN.h"
namespace std {

Compressor::Compressor() {
	this->extension = ".cmp";

}

Compressor::~Compressor() {
	// TODO Auto-generated destructor stub
}

void Compressor::compress(string file) {

	DataBlock *dbIn,*dbOut;
	FileReader * fr = new FileReader(file);
	BWT * bwt = new BWT();
	RunLenght * rle = new RunLenght();
	MTF * mtf = new MTF();
	CompressedFileWriter * fw = new CompressedFileWriter(file.append(this->extension));
	HUFFMAN * huffman = new HUFFMAN();
	while(fr->hasBlocksLeft()){
		dbIn = fr->getBlock();
		//BWT
		dbOut = bwt->transform(dbIn);
		delete dbIn;
		dbIn = dbOut;
		//MTF
		dbOut = mtf->encode(dbIn);
		delete dbIn;
		dbIn = dbOut;
		//RLE
		dbOut = rle->encode(dbOut);
		delete dbIn;
		dbIn = dbOut;
		//Huffman
		unsigned int * stats;
		stats = rle->getStats();
		dbOut = huffman->Compress(dbIn,stats);


		fw->writeBlock(dbOut);
		delete dbOut;
		delete dbIn;
	}
	fr->close();
	fw->close();
	delete fr;
	delete bwt;
	delete mtf;
	delete rle;
	delete fw;
	delete huffman;
}

} /* namespace std */
