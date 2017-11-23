#include "paralela.h"
#include "teclado.h"
#include <vcl.h>

int le_teclado(unsigned int end_porta, unsigned int end_teclado)
{
  unsigned int tecla, teclado, bit_teste;

  OutPortB(end_porta + 2, 0x07); // Nenhum CI selecionado (CS's altos)
  Sleep(1);

  teclado = (0xFF - end_teclado) & 0x04; // Separa o terceiro bit (saídas são complementares)
  teclado = teclado << 1; // Desloca o terceiro bit para o quarto bit
  teclado = teclado | (0x0F - end_teclado); // Compõe o endereço a ser transmitido para o CI
  OutPortB(end_porta + 2 , teclado); // Seleciona o teclado
  Sleep(1);
  teclado = teclado & 0x0B; // Coloca /C3 e C2 em zero
  OutPortB(end_porta + 2 , teclado); // Habilita o teclado
  Sleep(1);

  // Verifica o teclado

   bit_teste = 0x01;   // Seleciona a primeira coluna
   while (bit_teste <= 0x08)
   {
     OutPortB(end_porta, ~bit_teste);   // Coloca o bit de teste na primeira coluna

     tecla = InPortB(end_porta + 1);    // Leitura das linhas
     tecla = tecla >> 3;                // Move S5, S4, S3 para S2, S1, S0
     if (tecla != 0x0F) // Se alguma tecla foi pressionada, pára
     {
       // Verifica se pertence à primeira coluna
       if (bit_teste == 0x01)
       {
         if ((tecla & 0x01) == 0)
         {
           tecla = 0;
           break;
         }
         else
         {
           if ((tecla & 0x02) == 0)
           {
             tecla = 1;
             break;
           }
           else
           {
             tecla = 2;
             break;
           }
         }
       }
       else
       {
         // Verifica se pertence à segunda coluna
         if (bit_teste == 0x02)
         {
           if ((tecla & 0x01) == 0)
           {
             tecla = 3;
             break;
           }
           else
           {
             if ((tecla & 0x02) == 0)
             {
               tecla = 4;
               break;
             }
             else
             {
               tecla = 5;
               break;
             }
           }
         }
         else
         {
           // Verifica se pertence à terceira coluna
           if (bit_teste == 0x04)
           {
             if ((tecla & 0x01) == 0)
             {
               tecla = 6;
               break;
             }
             else
             {
               if ((tecla & 0x02) == 0)
               {
                 tecla = 7;
                 break;
               }
               else
               {
                 tecla = 8;
                 break;
               }
             }
           }
           // Se não pertence à nenhuma outra, pertence à quarta coluna
           else
           {
             if ((tecla & 0x01) == 0)
             {
               tecla = 9;
               break;
             }
             else
             {
               if ((tecla & 0x02) == 0)
               {
                 tecla = 10;
                 break;
               }
               else
               {
                 tecla = 11;
                 break;
               }
             }
           }
         }
       }
     }
     bit_teste = bit_teste << 1; // Seleciona a coluna seguinte
   }

   // Se nenhuma tecla foi pressionada, retorna -1
  if ((bit_teste == 0x10) & (tecla == 0x0F))
  {
    tecla = -1;
  }

  teclado = teclado | 0x04; // Coloca /C3 e C2 em 1
  OutPortB(end_porta + 2 , teclado); // Desabilita o teclado
  Sleep(1);
  return (tecla);
}
