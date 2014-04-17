/*
 * main.cpp
 *
 *  Created on: 08/04/2014
 *      Author: ari
 */

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <sys/stat.h>

using namespace std;

#define BLOCKSIZE 500000
#define MAX_BLOCK_COUNT 4

void reset_stats(int v[MAX_BLOCK_COUNT][256]) {
	for (int block_count = 0; block_count < MAX_BLOCK_COUNT; block_count++)
		for (int i = 0; i < 256; i++)
			v[block_count][i] = 0;
}

void print_stats(int v[MAX_BLOCK_COUNT][256]) {

	int i, block_count;
	int bytes_per_block[MAX_BLOCK_COUNT];

	for (block_count = 0; block_count < MAX_BLOCK_COUNT; block_count++)
		bytes_per_block[block_count] = 0;
	for (block_count = 0; block_count < MAX_BLOCK_COUNT; block_count++)
		for (i = 0; i < 256; i++)
			bytes_per_block[block_count] += v[block_count][i];

	for (i = 0; i < 256; i++) {
		cout << i << " ";
		for (block_count = 0; block_count < MAX_BLOCK_COUNT; block_count++) {
			cout
					<< 100 * v[block_count][i]
							/ float(bytes_per_block[block_count]) << " ";
		}
		cout << endl;
	}

	/*      int suma=0;
	 suma+=v[i];
	 for (i=0;i<256;i++){
	 if (v[i]>0)
	 cout << i << ";" << 100*v[i]/float(suma) << endl;
	 }
	 cout << "total bytes: " << suma;*/
}

int main() {

	string DATAPATH = "/home/freakazoid/Downloads/canterbury.tar";
	char buffer[BLOCKSIZE];
	int counts[MAX_BLOCK_COUNT][256];
	int i, block_count;
	ifstream myFile(DATAPATH.c_str(), ios::in | ios::binary);
	cout << "Inicio" << endl;
	reset_stats(counts);

	for (block_count = 0; block_count < MAX_BLOCK_COUNT; block_count++) {
		myFile.read(buffer, BLOCKSIZE);
		for (i = 0; i < BLOCKSIZE; i++)
			counts[block_count][(unsigned char) buffer[i]] += 1;
	}

	print_stats(counts);

	reset_stats(counts);
	int filesize;
	struct stat filestatus;
	stat(DATAPATH.c_str(), &filestatus);
	filesize = filestatus.st_size;
	// Archivo completo
	cout << "Archivo completo: " << filesize << " bytes" << endl;
	char * filebuffer = (char*) malloc(filesize);
	if (!filebuffer) {
		cout << "error de memoria" << endl;
		exit(1);
	}

	myFile.seekg(0);
	cout << "Leyendo" << endl;
	myFile.read(filebuffer, filesize);
	cout << "Fin lectura" << endl;
	for (i = 0; i < filesize; i++) {
		counts[0][(unsigned char) filebuffer[i]] += 1;
	}
	free(filebuffer);

	print_stats(counts);


	myFile.close();
	cout << "Fin" << endl;
	return 0;
}

