//---------------------------------------------------------------------------
#pragma hdrstop
#include <stdio.h>
#include <iostream.h>
#include <fstream.h>

//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[])
{
  ofstream ArqDecimal;
  ifstream Le;
  unsigned int ano, mes, dia, hora, minutos, segundos, milissegundos;
  unsigned int contador_bytes = 0;
  unsigned int contador_bytes_bin = 0;
  double valor_lido[30], resolucao;
  char buffer[30];
  char* pbuffer;
  pbuffer = &buffer[0];

  resolucao = 5.0/1023.0;

  if (argc == 2) //Testa se o número de parâmetros está correto
  {
    //Verifica qual é experimento desejado

    if (!strcmp(argv[1],"cbemg"))
    {
      ArqDecimal.open("cbemg.txt",ios::out); // Gera um novo arquivo e destrói o antigo, caso houver
      ArqDecimal.close();

      Le.open("cbemg.dat",ios::binary); // Abre o arquivo binário

      if (Le.fail()) // Se não consegue abrir o arquivo, encerra o programa
      {
        exit(0);
      }

      ArqDecimal.open("cbemg.txt",ios::out);
    }
    else
    {
      if (!strcmp(argv[1],"fluxrad"))
      {
        ArqDecimal.open("fluxrad.txt",ios::out); // Gera um novo arquivo e destrói o antigo, caso houver
        ArqDecimal.close();

        Le.open("fluxrad.dat",ios::binary); // Abre o arquivo binário

        if (Le.fail()) // Se não consegue abrir o arquivo, encerra o programa
        {
          exit(0);
        }

        ArqDecimal.open("fluxrad.txt",ios::out);
      }
      else
      {
        if (!strcmp(argv[1],"cpl"))
        {
          ArqDecimal.open("cpl.txt",ios::out); // Gera um novo arquivo e destrói o antigo, caso houver
          ArqDecimal.close();

          Le.open("cpl.dat",ios::binary); // Abre o arquivo binário

          if (Le.fail()) // Se não consegue abrir o arquivo, encerra o programa
          {
            exit(0);
          }

          ArqDecimal.open("cpl.txt",ios::out);
        }
        else  // Sai se não acha um nome de experimento correto
        {
          exit(0);
        }
      }
    }

    while(1)
    {
      if(Le.read(pbuffer,6)) // Descarta os 6 primeiros bytes
      {
        if(Le.read(pbuffer,11)) // Lê os bytes de temporização e subtipo
        {
          ano = ((buffer[0] & 0xF0) << 8) + ((buffer[0] & 0x0F) << 8); // Devido a problemas com
          ano = ano + (buffer[1] & 0xF0) + (buffer[1] & 0x0F); // o compilador, a composição dos dados
                                                              // é feita nibble a nibble

          mes = (buffer[2] & 0xF0) + (buffer[2] & 0x0F); // Devido a problemas com o compilador, a composição dos dados é feita nibble a nibble

          dia = (buffer[3] & 0xF0) + (buffer[3] & 0x0F); // Devido a problemas com o compilador, a composição dos dados é feita nibble a nibble

          hora = (buffer[4] & 0xF0) + (buffer[4] & 0x0F); // Devido a problemas com o compilador, a composição dos dados é feita nibble a nibble

          minutos = (buffer[5] & 0xF0) + (buffer[5] & 0x0F); // Devido a problemas com o compilador, a composição dos dados é feita nibble a nibble

          segundos = (buffer[6] & 0xF0) + (buffer[6] & 0x0F); // Devido a problemas com o compilador, a composição dos dados é feita nibble a nibble

          milissegundos = ((buffer[7] & 0xF0) << 12) + ((buffer[7] & 0x0F) << 12); // Devido a problemas com
          milissegundos = milissegundos + ((buffer[8] & 0xF0) << 4) + ((buffer[8] & 0x0F) << 4); // com o compilador, a composição dos
          milissegundos = milissegundos + ((buffer[9] & 0xF0) >> 4); // dados é feita nibble a nibble
         /*
          ArqDecimal << "Ano  Mês Dia Hora Minutos Segundos Milissegundos" << endl;
          ArqDecimal << ano << " " << mes << "  " << dia << "  " << hora << "   ";
          ArqDecimal << minutos << "      " << segundos << "       " << milissegundos << endl << endl;
          ArqDecimal << "hora;minutos;segundos;milissegundos;";
          ArqDecimal << "CBEMGAN1;CBEMGAN2;CBEMGAN3;CBEMGAN4;";
          ArqDecimal << "CBEMGAN5;CBEMGAN6;CBEMGAN7;CBEMGAN8;";
          ArqDecimal << "FLUX9;VR1;VR2;VR3;VR4;TR;PIN15;PIN16;" << endl; */


          if((!strcmp(argv[1],"cbemg"))|(!strcmp(argv[1],"fluxrad")))
          {
            for(unsigned int tm_data = 0; tm_data <= 39; tm_data++)  // Lê os 1000 bytes de dados
            {
              if(Le.read(pbuffer,25)) // Lê os dados da aquisição
              {
                hora = (buffer[0] & 0xF0) + (buffer[0] & 0x0F); // Devido a problemas com o compilador, a composição dos dados é feita nibble a nibble

                minutos = (buffer[1] & 0xF0) + (buffer[1] & 0x0F); // Devido a problemas com o compilador, a composição dos dados é feita nibble a nibble

                segundos = (buffer[2] & 0xF0) + (buffer[2] & 0x0F); // Devido a problemas com o compilador, a composição dos dados é feita nibble a nibble

                milissegundos = ((buffer[3] & 0xF0) << 8) + ((buffer[3] & 0x0F) << 8); // Devido a problemas com o compilador, a composição
                milissegundos = milissegundos + (buffer[4] & 0xF0) + (buffer[4] & 0x0F); // dos dados é feita nibble a nibble

                while (contador_bytes <= 15)  // Decodifica os dados lidos
                {
                  for(unsigned short int contador_valor_lido = 0; contador_valor_lido <= 3; contador_valor_lido++)
                  {
                    switch (contador_valor_lido)
                    {
                      case 0:
                      valor_lido[contador_bytes] = ((buffer[contador_bytes_bin + 5] & 0xC0) << 2) + ((buffer[contador_bytes_bin + 5] & 0x3F) << 2) + ((buffer[contador_bytes_bin + 6] & 0xC0) >> 06);
                      valor_lido[contador_bytes] = valor_lido[contador_bytes]*(resolucao);
                      break;

                      case 1:
                      valor_lido[contador_bytes] = ((buffer[contador_bytes_bin + 5] & 0x30) << 4) + ((buffer[contador_bytes_bin + 5] & 0x0F) << 4) + ((buffer[contador_bytes_bin + 6] & 0xF0) >> 4);
                      valor_lido[contador_bytes] = valor_lido[contador_bytes]*(resolucao);
                      break;

                      case 2:
                      valor_lido[contador_bytes] = ((buffer[contador_bytes_bin + 5] & 0x0F) << 6) + ((buffer[contador_bytes_bin + 6] & 0xFC) >> 2);
                      valor_lido[contador_bytes] = valor_lido[contador_bytes]*(resolucao);
                      break;

                      default:
                      valor_lido[contador_bytes] = ((buffer[contador_bytes_bin + 5] & 0x03) << 8) + (buffer[contador_bytes_bin + 6] & 0xFF);
                      valor_lido[contador_bytes] = valor_lido[contador_bytes]*(resolucao);
                      break;
                    }

                    contador_bytes++;
                    contador_bytes_bin++;
                  }
                  contador_bytes_bin++;
                }

                // Grava os dados decodificados
                ArqDecimal << hora << ';' << minutos << ';' << segundos << ';' << milissegundos << ';';

                for (contador_bytes = 0; contador_bytes <= 15; contador_bytes++)
                {
                  ArqDecimal << valor_lido[contador_bytes] << ';';
                }

                ArqDecimal << endl;

                contador_bytes = 0;
                contador_bytes_bin = 0;
              }
            }
          }
          else // Se for o CPL
          {
            for(unsigned int tm_data = 0; tm_data <= 32; tm_data++)  // Lê os 990 bytes de dados
            {
              if(Le.read(pbuffer,30)) // Lê os dados da aquisição
              {
                hora = (buffer[0] & 0xF0) + (buffer[0] & 0x0F); // Devido a problemas com o compilador, a composição dos dados é feita nibble a nibble

                minutos = (buffer[1] & 0xF0) + (buffer[1] & 0x0F); // Devido a problemas com o compilador, a composição dos dados é feita nibble a nibble

                segundos = (buffer[2] & 0xF0) + (buffer[2] & 0x0F); // Devido a problemas com o compilador, a composição dos dados é feita nibble a nibble

                milissegundos = ((buffer[3] & 0xF0) << 8) + ((buffer[3] & 0x0F) << 8); // Devido a problemas com o compilador, a composição
                milissegundos = milissegundos + (buffer[4] & 0xF0) + (buffer[4] & 0x0F); // dos dados é feita nibble a nibble

                while (contador_bytes <= 19)  // Decodifica os dados lidos
                {
                  for(unsigned short int contador_valor_lido = 0; contador_valor_lido <= 3; contador_valor_lido++)
                  {
                    switch (contador_valor_lido)
                    {
                      case 0:
                      valor_lido[contador_bytes] = ((buffer[contador_bytes_bin + 5] & 0xC0) << 2) + ((buffer[contador_bytes_bin + 5] & 0x3F) << 2) + ((buffer[contador_bytes_bin + 6] & 0xC0) >> 06);
                      valor_lido[contador_bytes] = valor_lido[contador_bytes]*(resolucao);
                      break;

                      case 1:
                      valor_lido[contador_bytes] = ((buffer[contador_bytes_bin + 5] & 0x30) << 4) + ((buffer[contador_bytes_bin + 5] & 0x0F) << 4) + ((buffer[contador_bytes_bin + 6] & 0xF0) >> 4);
                      valor_lido[contador_bytes] = valor_lido[contador_bytes]*(resolucao);
                      break;

                      case 2:
                      valor_lido[contador_bytes] = ((buffer[contador_bytes_bin + 5] & 0x0F) << 6) + ((buffer[contador_bytes_bin + 6] & 0xFC) >> 2);
                      valor_lido[contador_bytes] = valor_lido[contador_bytes]*(resolucao);
                      break;

                      default:
                      valor_lido[contador_bytes] = ((buffer[contador_bytes_bin + 5] & 0x03) << 8) + (buffer[contador_bytes_bin + 6] & 0xFF);
                      valor_lido[contador_bytes] = valor_lido[contador_bytes]*(resolucao);
                      break;
                    }

                    contador_bytes++;
                    contador_bytes_bin++;
                  }
                  contador_bytes_bin++;
                }

                // Grava os dados decodificados
                ArqDecimal << hora << ';' << minutos << ';' << segundos << ';' << milissegundos << ';';

                for (contador_bytes = 0; contador_bytes <= 15; contador_bytes++)
                {
                  ArqDecimal << valor_lido[contador_bytes] << ';';
                }

                ArqDecimal << endl;

                contador_bytes = 0;
                contador_bytes_bin = 0;
              }
            }

            if(Le.read(pbuffer,6)) // No momento descarta os 6 últimos bytes
            {
            }

          }
          //ArqDecimal << endl;
        }
        else  // Sai caso tenha chegado ao fim do arquivo
        {
          ArqDecimal.close();
          Le.close();
          exit(0);
        }
      }

      else  // Sai caso tenha chegado ao fim do arquivo
      {
        ArqDecimal.close();
        Le.close();
        exit(0);
      }
    }
  return 0;
  }
}
//---------------------------------------------------------------------------
