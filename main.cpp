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
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
	return 0;
}


