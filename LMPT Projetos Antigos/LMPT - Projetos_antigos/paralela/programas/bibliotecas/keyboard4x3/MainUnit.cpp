//---------------------------------------------------------------------------
#include "../include/keyboard4x3.h"
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
        return 1;
}
//---------------------------------------------------------------------------

int ReadKeyboard(unsigned int AddressKeyboard, unsigned int AddressLPT)
{
  int key, keyboard, TestBit;

  DlPortWritePortUchar(AddressLPT + 2, 0x07); // Unselect CIs (CS's high), RS high and R/W low

  keyboard = (0xFF - AddressKeyboard) & 0x04;     // Separate the third bit (complementary outputs)
  keyboard = keyboard << 1;                       // Allocate the third bit in the fourth bit
  keyboard = keyboard | (0x0F - AddressKeyboard); // Compose the address to be transmited to CI
  DlPortWritePortUchar(AddressLPT + 2, keyboard); // Select keyboard
  keyboard = keyboard & 0x0B;                     // Set /C3 and C2 low
  DlPortWritePortUchar(AddressLPT + 2, keyboard); // Enable keyboard

  // Verifica o teclado

   TestBit = 0x01;   // Seleciona a primeira coluna
   while (TestBit <= 0x08)
   {
     DlPortWritePortUchar(AddressLPT, ~TestBit);   // Allocate the TestBit in the first column
     key = DlPortReadPortUchar(AddressLPT + 1);    // Read lines
     key = key >> 3;                               // Move S5, S4, S3 for S2, S1, S0
     if (key != 0x0F)                              // Stop if a key was pushed
     {
       // Verify if the key is in the first column
       if (TestBit == 0x01)
       {
         if ((key & 0x01) == 0)
         {
           key = 1;
           break;
         }
         else
         {
           if ((key & 0x02) == 0)
           {
             key = 2;
             break;
           }
           else
           {
             key = 3;
             break;
           }
         }
       }
       else
       {
         // Verify if the key is in the second column
         if (TestBit == 0x02)
         {
           if ((key & 0x01) == 0)
           {
             key = 4;
             break;
           }
           else
           {
             if ((key & 0x02) == 0)
             {
               key = 5;
               break;
             }
             else
             {
               key = 6;
               break;
             }
           }
         }
         else
         {
           // Verify if the key is in the third column
           if (TestBit == 0x04)
           {
             if ((key & 0x01) == 0)
             {
               key = 7;
               break;
             }
             else
             {
               if ((key & 0x02) == 0)
               {
                 key = 8;
                 break;
               }
               else
               {
                 key = 9;
                 break;
               }
             }
           }
           // The key is in the forth column
           else
           {
             if ((key & 0x01) == 0)
             {
               key = 10;
               break;
             }
             else
             {
               if ((key & 0x02) == 0)
               {
                 key = 0;
                 break;
               }
               else
               {
                 key = 11;
                 break;
               }
             }
           }
         }
       }
     }
     TestBit = TestBit << 1; // Select the next column
   }

   // If a key not pressed, return -1
  if ((TestBit == 0x10) & (key == 0x0F))
  {
    key = -1;
  }

  keyboard = keyboard | 0x04;                      // Set /C3 and C2 high
  DlPortWritePortUchar(AddressLPT + 2 , keyboard); // Unselect CIs (CS's high), RS high and R/W low
  return(key);
} 
