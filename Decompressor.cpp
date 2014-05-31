/*
 * Decompressor.cpp
 *
 *  Created on: 17/05/2014
 *      Author: ari
 */

#include "Decompressor.h"
#include "DataBlock.h"
#include "BWT.h"
#include "MTF.h"
#include <iostream>
#include "RunLenght.h"
#include "FileWriter.h"
#include "CompressedFileReader.h"
#include "HUFFMAN.h"
namespace std {

Decompressor::Decompressor() {
	this->extension=".cmp";

}

void Decompressor::decompress(string file) {
	DataBlock *dbIn,*dbOut;
	HUFFMAN * huffman = new HUFFMAN();
	CompressedFileReader * fr = new CompressedFileReader(file);
	BWT * bwt = new BWT();
	RunLenght * rle = new RunLenght();
	MTF * mtf = new MTF();
	FileWriter * fw = new FileWriter(this->removeExtension(file));
	while(fr->hasBlocksLeft()){
		cerr << "Leo un bloque" << endl;
		dbIn = fr->getBlock();
		// Aca va huffman
		cerr << "HUff" << endl;
		dbOut = huffman->decompress(dbIn);
		delete dbIn;
		dbIn=dbOut;
		cerr << "RLE" << endl;
		dbOut = rle->decode(dbIn);
		delete dbIn;
		dbIn = dbOut;
		cerr << "MTF" << endl;
		dbOut = mtf->decode(dbIn);
		delete dbIn;
		// Aca va BWT
		dbIn=dbOut;
		cerr << "BWT" << endl;
		dbOut=bwt->untransform(dbIn);
		fw->writeBlock(dbOut);
		delete dbOut;
		delete dbIn;
	}
	fr->close();
	fw->close();
	delete huffman;
	delete rle;
	delete bwt;
	delete mtf;
	delete fw;
	delete fr;


}

Decompressor::~Decompressor() {
	// TODO Auto-generated destructor stub
}

string Decompressor::removeExtension(string path) {
	if(path.compare(path.size()-this->extension.size(), this->extension.size(), this->extension, 0,this->extension.size())){
		path.resize(path.size()-2);
		return path;
	}else
		throw "Extensión equivocada";
	return NULL;
}

} /* namespace std */
