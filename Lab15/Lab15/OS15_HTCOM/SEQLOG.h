#pragma once
#include <fstream>
extern std::fstream LogCOM;
extern long Seq;
#define SEQ LONG __XXCSeq = InterlockedIncrement(&Seq)
#define LOG(x,y) LogCOM << __XXCSeq << ":" << (x) << (y) << std::endl