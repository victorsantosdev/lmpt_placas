//---------------------------------------------------------------------------
#include "../include/lcd2x40.h"

//---------------------------------------------------------------------------

void WriteTextInLCD(char *pTextLCD, unsigned int AddressLCD, unsigned int AddressLPT)
{
  unsigned int counter = 0;
  while (*(pTextLCD + counter) != NULL)
  {
    WriteCharLCD(*(pTextLCD + counter), AddressLCD, AddressLPT);
    counter++;
  }
}
//---------------------------------------------------------------------------

void WriteCharLCD(char charLCD, unsigned int AddressLCD, unsigned int AddressLPT)
{
  unsigned int LCD;

  DlPortWritePortUchar(AddressLPT + 2, 0x05); // Unselect CIs (CS's high), RS high and R/W low

//  _delay(1);

  LCD = (0xFF - AddressLCD) & 0x04; // Separate the third bit (complementary outputs)
  LCD = LCD << 1;                   // Allocate the third bit in the fourth bit
  LCD = LCD | (0xFF - AddressLCD);  // Compose the address to be transmited to CI
  LCD = LCD & 0x0B;                 // Set /C3 and C2 low

  DlPortWritePortUchar(AddressLPT + 2, 0x01); // Store the values of RS and R/W in the latch

//  _delay(1);

  DlPortWritePortUchar(AddressLPT, charLCD);

//  _delay(1);

  DlPortWritePortUchar(AddressLPT + 2 , LCD); // Enable LCD

//  _delay(1);

  LCD = LCD & 0xF7; // Desabilita o LCD
  DlPortWritePortUchar(AddressLPT + 2, LCD); // Unselect CIs (CS's high), RS high and R/W low

  _delay(1);
}
//---------------------------------------------------------------------------

bool LineLCD(unsigned int line, unsigned int AddressLCD, unsigned int AddressLPT)
{
  bool Executed;

  switch (line)
  {
    case 1:
      WriteInstructionLCD(0x80, AddressLCD, AddressLPT); // Put the cursor in the first line begin
      Executed = true;
    break;

    case 2:
      WriteInstructionLCD(0xC0, AddressLCD, AddressLPT); // Put the cursor in the second line begin
      Executed = true;
    break;

    default: // Return error if line not equal 1 or 2
      Executed = false;
  }

  _delay(1);
  return(Executed);
}
//---------------------------------------------------------------------------

void ClearLCD(unsigned int AddressLCD, unsigned int AddressLPT)
{
  WriteInstructionLCD(0x01, AddressLCD, AddressLPT); // Clear Display
//  _delay(2);
}
//---------------------------------------------------------------------------

void InitializeLCD(unsigned int AddressLCD, unsigned int AddressLPT)
{
  WriteInstructionLCD(0x3F, AddressLCD, AddressLPT); // 2 lines, 5x10 dots
  _delay(1);
  WriteInstructionLCD(0x0F, AddressLCD, AddressLPT); // Display on, cursor on, blinking on
  _delay(1);
  WriteInstructionLCD(0x01, AddressLCD, AddressLPT); // Clear Display
  _delay(2);
  WriteInstructionLCD(0x06, AddressLCD, AddressLPT); // Increase cursor, display is shifted
  _delay(1);
}
//---------------------------------------------------------------------------

void WriteInstructionLCD(unsigned int instruction, unsigned int AddressLCD, unsigned int AddressLPT)
{
  unsigned int LCD;

  LCD = LCD & 0xF7; // Desabilita o LCD
  DlPortWritePortUchar(AddressLPT + 2, 0x07); // Unselect CIs (CS's high), RS high and R/W low

//  _delay(1);

  LCD = (0xFF - AddressLCD) & 0x04; // Separate the third bit (complementary outputs)
  LCD = LCD << 1;                   // Allocate the third bit in the fourth bit
  LCD = LCD | (0xFF - AddressLCD);  // Compose the address to be transmited to CI
  LCD = LCD & 0x0B;                 // Set /C3 and C2 low

  DlPortWritePortUchar(AddressLPT + 2, 0x03); // Store the values of RS and R/W in the latch

//  _delay(1);

  DlPortWritePortUchar(AddressLPT, instruction); 

//  _delay(1);

  DlPortWritePortUchar(AddressLPT + 2 , LCD); // Enable LCD

//  _delay(1);

  LCD = LCD & 0xF7; // Desabilita o LCD
  DlPortWritePortUchar(AddressLPT + 2, LCD); // Unselect CIs (CS's high), RS high and R/W low

//  _delay(1);
}
//---------------------------------------------------------------------------

void _delay(unsigned int delay)
{
  clock_t start, end;

  start = clock();
  end = clock();

  while ((end - start) < delay)
  {
    end = clock();
  }
}