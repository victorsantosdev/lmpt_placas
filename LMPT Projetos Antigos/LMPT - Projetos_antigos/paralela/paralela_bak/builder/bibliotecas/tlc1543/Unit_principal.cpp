//---------------------------------------------------------------------------

#include <windows.h>
#include "..\dlportio\Dlportio.h"
//---------------------------------------------------------------------------
//   Important note about DLL memory management when your DLL uses the
//   static version of the RunTime Library:
//
//   If your DLL exports any functions that pass String objects (or structs/
//   classes containing nested Strings) as parameter or function results,
//   you will need to add the library MEMMGR.LIB to both the DLL project and
//   any other projects that use the DLL.  You will also need to use MEMMGR.LIB
//   if any other projects which use the DLL will be performing new or delete
//   operations on any non-TObject-derived classes which are exported from the
//   DLL. Adding MEMMGR.LIB to your project will change the DLL and its calling
//   EXE's to use the BORLNDMM.DLL as their memory manager.  In these cases,
//   the file BORLNDMM.DLL should be deployed along with your DLL.
//
//   To avoid using BORLNDMM.DLL, pass string information using "char *" or
//   ShortString parameters.
//
//   If your DLL uses the dynamic version of the RTL, you do not need to
//   explicitly add MEMMGR.LIB as this will be done implicitly for you
//---------------------------------------------------------------------------

#pragma argsused

// Protótipos das funções

extern "C" __declspec(dllexport) unsigned short int le_canal(unsigned short int, unsigned short int, unsigned short int);


int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
  return 1;
}
//---------------------------------------------------------------------------

unsigned short int le_canal(unsigned short int end_paralela, unsigned short int end_canal, unsigned short int end_conv)
{
  unsigned int conv, canal, contador, EOC;
  unsigned short int valor_lido = 0;

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
      DlPortWritePortUchar(end_paralela + 2, 0x0F); // Nenhum CI selecionado (CS's altos)
//      OutPortB(Endereco_Paralela + 2, 0x0F); // Nenhum CI selecionado (CS's altos)

      conv = (0xFF - end_conv) & 0x04; // Separa o terceiro bit (saídas sào complementares)
      conv = conv << 1; // Desloca o terceiro bit para o quarto bit
      conv = conv | (0xFF - end_conv); // Compõe o endereço a ser transmitido para o CI
      conv = conv & 0x0B; // Zera o terceiro bit

      DlPortWritePortUchar(end_paralela + 2, conv); // Seleciona o conversor
//      OutPortB(Endereco_Paralela + 2 , conv); // Seleciona o conversor

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
        DlPortWritePortUchar(end_paralela, canal); // Fornece DIN para o conversor
//        OutPortB(Endereco_Paralela, canal); // Fornece DIN para o conversor

        canal = canal + 1; // Ativa I/OClock
        DlPortWritePortUchar(end_paralela, canal); // Fornece I/OClock para o conversor
//        OutPortB(Endereco_Paralela, canal); // Fornece I/OClock para o conversor

        canal = canal & 0xFE; // Desativa I/OClock
        DlPortWritePortUchar(end_paralela, canal);
//        OutPortB(Endereco_Paralela, canal);

        contador = contador / 2;
      }

      // Manda os seis pulsos restantes de I/OClock
      for (contador = 5; contador <= 10; contador++)
      {
        DlPortWritePortUchar(end_paralela, 0x01); // Ativa I/OClock
        DlPortWritePortUchar(end_paralela, 0x00); // Desativa I/OClock
//        OutPortB(Endereco_Paralela, 0x01); // Ativa I/OClock
//        OutPortB(Endereco_Paralela, 0x00); // Desativa I/OClock
      }

      // Espera o fim da conversão ou o envio dos 16 bits

      DlPortWritePortUchar(end_paralela, 0x01); // Ativa I/OClock
//      OutPortB(Endereco_Paralela, 0x01); // Ativa I/OClock

      for (unsigned int delay = 0; delay <= 10000; delay++)
      {
        if ((DlPortReadPortUchar(end_paralela + 1)) & 0x08)
//        if ((InPortB(Endereco_Paralela + 1)) & 0x08)
        {
          break;
        }
      }

      for (contador = 11; contador <= 16; contador++)
      {
        DlPortWritePortUchar(end_paralela, 0x00); // Desativa I/OClock
//        OutPortB(Endereco_Paralela, 0x00); // Desativa I/OClock
        if (contador != 16)
        {
          DlPortWritePortUchar(end_paralela, 0x01); // Ativa I/OClock
//          OutPortB(Endereco_Paralela, 0x01); // Ativa I/OClock
        }
      }

      DlPortWritePortUchar(end_paralela + 2, 0x0F); // Nenhum CI selecionado (CS's altos)
//      OutPortB(Endereco_Paralela + 2, 0x0F); // Nenhum CI selecionado (CS's altos)

      DlPortWritePortUchar(end_paralela + 2, conv); // Seleciona o conversor
//      OutPortB(Endereco_Paralela + 2 , conv); // Seleciona o conversor

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
        DlPortWritePortUchar(end_paralela, canal); // Fornece DIN para o conversor
//        OutPortB(Endereco_Paralela, canal); // Fornece DIN para o conversor

        EOC = DlPortReadPortUchar(end_paralela + 1); // Aqui EOC é utilizado apenas como uma variável temporária
//        EOC = InPortB(Endereco_Paralela + 1); // Aqui EOC é utilizado apenas como uma variável temporária
        EOC = EOC & 0x10; //Separa o bit DOUT
        EOC = EOC >> 4; // Coloca o bit DOUT como MSB
        valor_lido = valor_lido | EOC; // Compõe o valor lido
        valor_lido = valor_lido << 1; // Coloca os bits nas posições corretas

        canal = canal + 1; // Ativa I/OClock
        DlPortWritePortUchar(end_paralela, canal); // Fornece I/OClock para o conversor
//        OutPortB(Endereco_Paralela, canal); // Fornece I/OClock para o conversor

        canal = canal & 0xFE; // Desativa I/OClock
        DlPortWritePortUchar(end_paralela, canal);
//        OutPortB(Endereco_Paralela, canal);

        contador = contador / 2;
      }

      // Manda os seis pulsos restantes de I/OClock
      for (contador = 5; contador <= 10; contador++)
      {
        EOC = DlPortReadPortUchar(end_paralela + 1); // Aqui EOC é utilizado apenas como uma variável temporária
//        EOC = InPortB(Endereco_Paralela + 1); // Aqui EOC é utilizado apenas como uma variável temporária
        EOC = EOC & 0x10; //Separa o bit DOUT
        EOC = EOC >> 4; // Coloca o bit DOUT como MSB
        valor_lido = valor_lido | EOC; // Compõe o valor lido

        if (contador < 10)
        {
          valor_lido = valor_lido << 1; // Coloca os bits nas posições corretas
        }

        DlPortWritePortUchar(end_paralela, 0x01); // Ativa I/OClock
//        OutPortB(Endereco_Paralela, 0x01); // Ativa I/OClock

        DlPortWritePortUchar(end_paralela, 0x00); // Desativa I/OClock
//        OutPortB(Endereco_Paralela, 0x00); // Desativa I/OClock
      }

      // Espera o fim da conversão ou o envio dos 16 bits

      DlPortWritePortUchar(end_paralela, 0x01); // Ativa I/OClock
//      OutPortB(Endereco_Paralela, 0x01); // Ativa I/OClock

      for (unsigned int delay = 0; delay <= 10000; delay++)
      {
        if ((DlPortReadPortUchar(end_paralela + 1)) & 0x08)
//        if ((InPortB(Endereco_Paralela + 1)) & 0x08)
        {
          break;
        }
      }

      for (contador = 11; contador <= 16; contador++)
      {
        DlPortWritePortUchar(end_paralela, 0x00); // Desativa I/OClock
//        OutPortB(Endereco_Paralela, 0x00); // Desativa I/OClock
        if (contador != 16)
        {
          DlPortWritePortUchar(end_paralela, 0x01); // Ativa I/OClock
//          OutPortB(Endereco_Paralela, 0x01); // Ativa I/OClock
        }
      }

      DlPortWritePortUchar(end_paralela + 2, 0x0F); // Nenhum CI selecionado (CS's altos)
//      OutPortB(Endereco_Paralela + 2, 0x0F); // Nenhum CI selecionado (CS's altos)
    }
  }

  return valor_lido;
}