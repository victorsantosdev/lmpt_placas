// Usage : key = ReadKeyboard(AddressKeyboard, AddressLPT);

#include <windows.h>
#include "Dlportio.h"

#ifdef __BUILDING_THE_DLL
#define __EXPORT_TYPE __export
#else
#define __EXPORT_TYPE __import
#endif

int __EXPORT_TYPE ReadKeyboard(unsigned int, unsigned int);
