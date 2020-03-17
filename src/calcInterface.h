#pragma once
#include <Windows.h>
#include "Intersect.h"
#include <fstream>
#include <string>
#include <vector>
#include <utility>


#ifdef IMPORT_DLL
#else
#define IMPORT_DLL extern "C" _declspec(dllimport) //指的是允许将其给外部调用
#endif

IMPORT_DLL int guiProcess(std::vector<std::pair<double,double>> *points, std::string msg);

IMPORT_DLL void cmdProcess(int argc, char *argv[]);