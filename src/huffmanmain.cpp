/*
 * CS 106X Huffman Encoding
 * This file contains the main program and user interface for running your
 * Huffman Encoder.  It contains a text menu to allow you to test all of the
 * various functions of your program for encoding and decoding data.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * Author : Marty Stepp
 * Version: Thu 2013/11/21
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "HuffmanNode.h"
#include "encoding.h"
#include <vector>
#include "huffmanutil.h"
using namespace std;


int main() {
//    compress(R"(C:\Users\fateh\Documents\CS\huffman-coding\res\short.txt)",
//            R"(C:\Users\fateh\Documents\CS\huffman-coding\res\short.huff)");
//    decompress(R"(C:\Users\fateh\Documents\CS\huffman-coding\res\short.huff)",
//             R"(C:\Users\fateh\Documents\CS\huffman-coding\res\dshort.txt)");
    compress("res/ababcab.txt", "res/out.huff");
//    decompress("res/out.huff", "res/decomp.txt");
//    compress("res/fibonacci.txt", "res/fibonacci.huff");
//    decompress("res/fibonacci.huff", "res/fibonacci_d.txt");
//    compress("res/dictionary.txt", "res/dictionary.huff");
//    decompress("res/dictionary.huff", "res/d_dictionary.txt");
//    compress("res/hellokitty.bmp", "res/hello.huff");
//    decompress("res/hello.huff", "res/d_hellokitty.bmp");
   // compress("res/dictionary.txt", "res/dictionary.huff");
   // compress("res/bender.jpg", "res/bender.huff");

//   1 byte indicating number of encodings to come
// for each encoding, 1 byte indicating the character we're encoding
// 1 byte containing the number of bits (n) of the character encoding
// n bits containing the character encoding
}