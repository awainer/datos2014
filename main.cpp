/*
 * main.cpp
 *
 *  Created on: 08/04/2014
 *      Author: ari
 */

using namespace std;

#include <fstream>
#include "Compressor.h"
#include "Decompressor.h"
#include "gtest/gtest.h"
#include "contrib/gtest/gtest.h"

int main(int argc, char **argv) {
	//::testing::InitGoogleTest(&argc, argv);
	//return RUN_ALL_TESTS();
	 if(argc != 3){
					cout << "Uso: " << endl;
					cout << argv[0] << " -c archivoAComprimir"<< endl;
					cout << argv[0] << " -d archivoADescomprimir"<< endl;
					exit(1);
			}

			string path=argv[2];

			if(!strcmp(argv[1],"-c")){
					Compressor * comp = new Compressor();
					comp->compress(path);
					//remove(path.c_str());
					delete comp;
			}

			if(!strcmp(argv[1],"-d")){
					Decompressor * decomp = new Decompressor();
					decomp->decompress(path);
					delete decomp;
			}
	return 0;
}


