/* Usage: WriteTextInLCD(TextLCD, AddressLCD, AddressLPT);
          LineLCD(line, AddressLCD, AddressLPT);
          ClearLCD(AddressLCD, AddressLPT);
          InitializeLCD(AddressLCD, AddressLPT);
*/

#ifdef __BUILDING_THE_DLL
#define __EXPORT_TYPE __export
#else
#define __EXPORT_TYPE __import
#endif

#include <windows.h>
#include <cstring.h>
#include <sstream.h>
#include <time.h>
#include "dlportio.h"

//void __EXPORT_TYPE WriteTextInLCD(string, unsigned int, unsigned int);
void __EXPORT_TYPE WriteTextInLCD(char *, unsigned int, unsigned int);

void WriteCharLCD(char, unsigned int, unsigned int);
bool __EXPORT_TYPE LineLCD(unsigned int, unsigned int, unsigned int);
void __EXPORT_TYPE ClearLCD(unsigned int, unsigned int);
void __EXPORT_TYPE InitializeLCD(unsigned int, unsigned int);
void WriteInstructionLCD(unsigned int, unsigned int, unsigned int);
void _delay(unsigned int);
