/*
 * common.h
 *
 *  Created on: May 20, 2014
 *      Author: nicola
 */

#pragma once

#include <vector>

enum formula_type {CONJUNCTION,ATOMIC,NEGATION,ALL_TOMORROW,EXISTS_TOMORROW,ALL_UNTIL,EXISTS_UNTIL};

typedef int formula;
typedef unsigned int formula_index;

typedef unsigned int uint;
typedef unsigned long int ulint;

typedef unsigned char uchar;

typedef std::vector<bool> state;

//parser errors
#define ERROR 256
#define ATOM 0
