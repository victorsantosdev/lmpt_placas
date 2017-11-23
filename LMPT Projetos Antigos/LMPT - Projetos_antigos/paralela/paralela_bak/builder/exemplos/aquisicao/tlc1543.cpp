/*
Biblioteca para o acesso das placas baseadas no conversor TLC1543

Autor: Carlos Eduardo Paghi

Data: agosto, 2001
 */


#include "tlc1543.h"
//#include <vcl.h>

int le_canal(unsigned int end_canal, unsigned int end_conv, unsigned int end_porta)
{
  unsigned int conv, canal, contador;
  unsigned int EOC = 0;
  int valor_lido = 0;

  if ((end_canal < 0) | (end_canal > 13))
  {
    valor_lido = -1;  // Erro, canal inválido
  }
  else
  {
    if ((end_conv < 0) | (end_conv > 3))
    {
      valor_lido = -2;  // Erro, endereço do conversor inválido
    }
    else
    {
      OutPortB(end_porta + 2, 0x0F); // Nenhum CI selecionado (CS's altos)
      //Sleep(10);

      conv = (0xFF - end_conv) & 0x04; // Separa o terceiro bit (saídas sào complementares)
      conv = conv << 1; // Desloca o terceiro bit para o quarto bit
      conv = conv | (0xFF - end_conv); // Compõe o endereço a ser transmitido para o CI
      conv = conv & 0x0B; // Zera o terceiro bit
      OutPortB(end_porta + 2 , conv); // Seleciona o conversor
      //Sleep(10);

      contador = 8;
      while (contador >= 1)
      {
        canal = end_canal & contador; // Separa os bits de seleção do canal para serem enviados serialmente

        if (contador >=4)
        {
          canal = canal >> contador/4 ; // DIN está ligado em D1
        }
        else
        {
          if (contador == 1)
          {
            canal = canal << 1;  // DIN está ligado em D1
          }
        }
        OutPortB(end_porta, canal); // Fornece DIN para o conversor

        //Sleep(10);

        canal = canal + 1; // Ativa I/OClock
        OutPortB(end_porta, canal); // Fornece I/OClock para o conversor
        //Sleep(10);

        canal = canal & 0xFE; // Desativa I/OClock
        OutPortB(end_porta, canal);
        //Sleep(10);

        contador = contador / 2;
      }

      // Manda os seis pulsos restantes de I/OClock
      for (contador = 5; contador <= 10; contador++)
      {
        OutPortB(end_porta, 0x01); // Ativa I/OClock
        //Sleep(1);

        OutPortB(end_porta, 0x00); // Desativa I/OClock
        //Sleep(1);
      }

//==========================================================

      OutPortB(end_porta, 0x01); // Ativa I/OClock

      for (unsigned char delay = 0; delay <= 1000000L; delay++)
      {
        if ((InPortB(end_porta + 1)) & 0x08)
        {
          break;
        }
      }

      for (contador = 11; contador <= 16; contador++)
      {
        OutPortB(end_porta, 0x00); // Desativa I/OClock
        if (contador != 16)
        {
          OutPortB(end_porta, 0x01); // Ativa I/OClock
        }  
      }

      OutPortB(end_porta + 2, 0x0F); // Nenhum CI selecionado (CS's altos)
      //Sleep(1);

      OutPortB(end_porta + 2 , conv); // Seleciona o conversor
      //Sleep(10);

      contador = 8;
      while (contador >= 1)
      {
        canal = end_canal & contador; // Separa os bits de seleção do canal para serem enviados serialmente

        if (contador >=4)
        {
          canal = canal >> contador/4 ; // DIN está ligado em D1
        }
        else
        {
          if (contador == 1)
          {
            canal = canal << 1;  // DIN está ligado em D1
          }
        }
        OutPortB(end_porta, canal); // Fornece DIN para o conversor

        //Sleep(10);

        EOC = InPortB(end_porta + 1); // Aqui EOC é utilizado apenas como uma variável temporária
        EOC = EOC & 0x10; //Separa o bit DOUT
        EOC = EOC >> 4; // Coloca o bit DOUT como MSB
        valor_lido = valor_lido | EOC; // Compõe o valor lido
        valor_lido = valor_lido << 1; // Coloca os bits nas posições corretas

        canal = canal + 1; // Ativa I/OClock
        OutPortB(end_porta, canal); // Fornece I/OClock para o conversor
        //Sleep(10);

        canal = canal & 0xFE; // Desativa I/OClock
        OutPortB(end_porta, canal);
        //Sleep(10);

        contador = contador / 2;
      }

      // Manda os seis pulsos restantes de I/OClock
      for (contador = 5; contador <= 10; contador++)
      {

        EOC = InPortB(end_porta + 1); // Aqui EOC é utilizado apenas como uma variável temporária
        EOC = EOC & 0x10; //Separa o bit DOUT
        EOC = EOC >> 4; // Coloca o bit DOUT como MSB
        valor_lido = valor_lido | EOC; // Compõe o valor lido

        if (contador < 10)
        {
          valor_lido = valor_lido << 1; // Coloca os bits nas posições corretas
        }

        OutPortB(end_porta, 0x01); // Ativa I/OClock
        //Sleep(1);

        OutPortB(end_porta, 0x00); // Desativa I/OClock
        //Sleep(1);
      }

//==========================================================

      OutPortB(end_porta, 0x01); // Ativa I/OClock

      for (unsigned char delay = 0; delay <= 1000000L; delay++)
      {
        if ((InPortB(end_porta + 1)) & 0x08)
        {
          break;
        }
      }

      for (contador = 11; contador <= 16; contador++)
      {
        OutPortB(end_porta, 0x00); // Desativa I/OClock
        if (contador != 16)
        {
          OutPortB(end_porta, 0x01); // Ativa I/OClock
        }
      }

      OutPortB(end_porta + 2, 0x0F); // Nenhum CI selecionado (CS's altos)
      //Sleep(10);
    }
  }
  return valor_lido;
}
