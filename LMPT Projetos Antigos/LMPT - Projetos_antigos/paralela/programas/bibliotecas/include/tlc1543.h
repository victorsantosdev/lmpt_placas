// Uso : valor_lido = le_canal(end_canal, end_conv, end_paralela);
#include <windows.h>
#include "Dlportio.h"

#ifdef __BUILDING_THE_DLL
#define __EXPORT_TYPE __export
#else
#define __EXPORT_TYPE __import
#endif

int __EXPORT_TYPE le_canal(unsigned int, unsigned int, unsigned int);
