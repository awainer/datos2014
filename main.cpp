/*
 * main.cpp
 *
 *  Created on: 08/04/2014
 *      Author: ari
 */

//#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <sys/stat.h>

using namespace std;


#include "contrib/gtest/gtest.h"
int main(int argc, char **argv) {
 ::testing::InitGoogleTest(&argc, argv);
 return RUN_ALL_TESTS();
	return 0;
}
