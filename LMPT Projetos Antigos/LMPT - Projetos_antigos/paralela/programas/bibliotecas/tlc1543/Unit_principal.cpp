//---------------------------------------------------------------------------
#include "../include/tlc1543.h"
#pragma argsused

int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
  return 1;
}
//---------------------------------------------------------------------------

int le_canal(unsigned int end_canal, unsigned int end_conv, unsigned int end_paralela)
{
  unsigned int conv, canal, contador, EOC;
  int valor_lido = 0;

  if (end_canal < 0)
  {
    valor_lido = -1;  // Erro, canal inv�lido
  }
  else
  {
    if (end_canal > 13)
    {
      valor_lido = -1;  // Erro, canal inv�lido
    }
    else
    {
      if ((end_conv < 0) | (end_conv > 3))
      {
        valor_lido = -2;  // Erro, endere�o do conversor inv�lido
      }
      else
      {
        DlPortWritePortUchar(end_paralela + 2, 0x0F); // Nenhum CI selecionado (CS's altos)

        conv = (0xFF - end_conv) & 0x04; // Separa o terceiro bit (sa�das s�o complementares)
        conv = conv << 1; // Desloca o terceiro bit para o quarto bit
        conv = conv | (0xFF - end_conv); // Comp�e o endere�o a ser transmitido para o CI
        conv = conv & 0x0B; // Zera o terceiro bit

        DlPortWritePortUchar(end_paralela + 2, conv); // Seleciona o conversor

        contador = 8;
        while (contador >= 1)
        {
          canal = end_canal & contador; // Separa os bits de sele��o do canal para serem enviados serialmente

          if (contador >=4)
          {
            canal = canal >> contador/4 ; // DIN est� ligado em D1
          }
          else
          {
            if (contador == 1)
            {
              canal = canal << 1;  // DIN est� ligado em D1
            }
          }
          DlPortWritePortUchar(end_paralela, canal); // Fornece DIN para o conversor

          canal = canal + 1; // Ativa I/OClock
          DlPortWritePortUchar(end_paralela, canal); // Fornece I/OClock para o conversor

          canal = canal & 0xFE; // Desativa I/OClock
          DlPortWritePortUchar(end_paralela, canal);

          contador = contador / 2;
        }

      // Manda os seis pulsos restantes de I/OClock
        for (contador = 5; contador <= 10; contador++)
        {
          DlPortWritePortUchar(end_paralela, 0x01); // Ativa I/OClock
          DlPortWritePortUchar(end_paralela, 0x00); // Desativa I/OClock
        }

      // Espera o fim da convers�o ou o envio dos 16 bits

        DlPortWritePortUchar(end_paralela, 0x01); // Ativa I/OClock

        for (unsigned int delay = 0; delay <= 10000; delay++)
        {
          if ((DlPortReadPortUchar(end_paralela + 1)) & 0x08)
          {
            break;
          }
        }

        for (contador = 11; contador <= 16; contador++)
        {
          DlPortWritePortUchar(end_paralela, 0x00); // Desativa I/OClock
          if (contador != 16)
          {
            DlPortWritePortUchar(end_paralela, 0x01); // Ativa I/OClock
          }
        }

        DlPortWritePortUchar(end_paralela + 2, 0x0F); // Nenhum CI selecionado (CS's altos)
        DlPortWritePortUchar(end_paralela + 2, conv); // Seleciona o conversor

        contador = 8;
        while (contador >= 1)
        {
          canal = end_canal & contador; // Separa os bits de sele��o do canal para serem enviados serialmente
          if (contador >=4)
          {
            canal = canal >> contador/4 ; // DIN est� ligado em D1
          }
          else
          {
            if (contador == 1)
            {
              canal = canal << 1;  // DIN est� ligado em D1
            }
          }
          DlPortWritePortUchar(end_paralela, canal); // Fornece DIN para o conversor

          EOC = DlPortReadPortUchar(end_paralela + 1); // Aqui EOC � utilizado apenas como uma vari�vel tempor�ria
          EOC = EOC & 0x10; //Separa o bit DOUT
          EOC = EOC >> 4; // Coloca o bit DOUT como MSB
          valor_lido = valor_lido | EOC; // Comp�e o valor lido
          valor_lido = valor_lido << 1; // Coloca os bits nas posi��es corretas

          canal = canal + 1; // Ativa I/OClock
          DlPortWritePortUchar(end_paralela, canal); // Fornece I/OClock para o conversor

          canal = canal & 0xFE; // Desativa I/OClock
          DlPortWritePortUchar(end_paralela, canal);

          contador = contador / 2;
        }

        // Manda os seis pulsos restantes de I/OClock
        for (contador = 5; contador <= 10; contador++)
        {
          EOC = DlPortReadPortUchar(end_paralela + 1); // Aqui EOC � utilizado apenas como uma vari�vel tempor�ria
          EOC = EOC & 0x10; //Separa o bit DOUT
          EOC = EOC >> 4; // Coloca o bit DOUT como MSB
          valor_lido = valor_lido | EOC; // Comp�e o valor lido

          if (contador < 10)
          {
            valor_lido = valor_lido << 1; // Coloca os bits nas posi��es corretas
          }

          DlPortWritePortUchar(end_paralela, 0x01); // Ativa I/OClock

          DlPortWritePortUchar(end_paralela, 0x00); // Desativa I/OClock
        }

      // Espera o fim da convers�o ou o envio dos 16 bits

        DlPortWritePortUchar(end_paralela, 0x01); // Ativa I/OClock

        for (unsigned int delay = 0; delay <= 10000; delay++)
        {
          if ((DlPortReadPortUchar(end_paralela + 1)) & 0x08)
          {
            break;
          }
        }

        for (contador = 11; contador <= 16; contador++)
        {
          DlPortWritePortUchar(end_paralela, 0x00); // Desativa I/OClock
          if (contador != 16)
          {
            DlPortWritePortUchar(end_paralela, 0x01); // Ativa I/OClock
          }
        }

        DlPortWritePortUchar(end_paralela + 2, 0x0F); // Nenhum CI selecionado (CS's altos)
      }
    }
  }

  return valor_lido;
}
