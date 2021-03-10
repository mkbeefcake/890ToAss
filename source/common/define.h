#pragma once
#include <string>
#include <vector>
#include <limits>

#ifdef WIN32
#include <io.h>
#include <mbctype.h>
#else
#include "../linux_lib/findfirst.h"
#endif 

#include <locale.h>
#include <unordered_map>
#include <cmath>
#include <cctype>

#include "exceptionhelper.h"
#include "stringhelper.h"
#include "stringbuilder.h"
#include "vectorhelper.h"
#include "bankersrounding.h"

class Paragraph;
using namespace std;

typedef unsigned char uchar;
typedef unsigned int uint;
typedef vector<unsigned char> u8Vector;
typedef vector<Paragraph*> ParagraphVector;
//typedef std::string myString;

#define UNUSED(expr) do { (void)(expr); } while(0)
