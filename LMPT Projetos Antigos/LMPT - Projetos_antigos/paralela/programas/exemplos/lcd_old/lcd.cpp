//---------------------------------------------------------------------------

#include <windows.h>
#include <time.h>

#pragma argsused
#include "..\..\bibliotecas\dlportio\dlportio.h"
#include "lcd2x40.h"

//---------------------------------------------------------------------------

void Escreve_texto_LCD(string Texto_LCD, unsigned int Endereco_LCD, unsigned int Endereco_Paralela)
{
  for (unsigned int contador = 0; contador <= Texto_LCD.length() - 1; contador++)
  {
    if (Texto_LCD[contador] == NULL)
    {
      break;
    }
    else
    {
      Escreve_caracter_LCD(Texto_LCD[contador], Endereco_LCD, Endereco_Paralela);
    }
  }
}
//---------------------------------------------------------------------------

void Escreve_caracter_LCD(char caracter_LCD, unsigned int Endereco_LCD, unsigned int Endereco_paralela)
{
  unsigned int LCD, milisseconds;

  DlPortWritePortUchar(Endereco_paralela + 2, 0x05); // Nenhum CI selecionado (CS's altos), RS em 1 e R/W em zero

//  _delay(1);

  LCD = (0xFF - Endereco_LCD) & 0x04; // Separa o terceiro bit (saídas são complementares)
  LCD = LCD << 1; // Desloca o terceiro bit para o quarto bit
  LCD = LCD | (0xFF - Endereco_LCD); // Compõe o endereço a ser transmitido para o CI
  LCD = LCD & 0x0B; // Coloca /C3 e C2 em zero

  DlPortWritePortUchar(Endereco_paralela + 2, 0x01); // Armazerna os valores de RS e R/W no latch

//  _delay(1);

  DlPortWritePortUchar(Endereco_paralela, caracter_LCD);

//  _delay(1);

  DlPortWritePortUchar(Endereco_paralela + 2 , LCD); // Habilita o LCD

//  _delay(1);

  LCD = LCD & 0xF7; // Desabilita o LCD
  DlPortWritePortUchar(Endereco_paralela + 2, LCD); // Nenhum CI selecionado (CS's altos)

  _delay(1);
}
//---------------------------------------------------------------------------

bool Linha_LCD(unsigned int linha, unsigned int Endereco_LCD, unsigned int Endereco_paralela)
{
  bool Executou;

  if (linha == 1)
  {
    Escreve_instrucao_LCD(0x80, Endereco_LCD, Endereco_paralela); // Coloca o cursor no início da primeira linha
    Executou = true;
    return(Executou);
  }
  else
  {
    if (linha == 2)
    {
      Escreve_instrucao_LCD(0xC0, Endereco_LCD, Endereco_paralela); // Coloca o cursor no início da segunda linha
      Executou = true;
      return(Executou);
    }
    else
    {
      Executou = false;  // Se não foi indicada a linha 1 ou 2, indica um erro
      return(Executou);
    }
  }
}
//---------------------------------------------------------------------------

void Limpa_LCD(unsigned int Endereco_LCD, unsigned int Endereco_paralela)
{
  Escreve_instrucao_LCD(0x01, Endereco_LCD, Endereco_paralela); // Limpa Display
//  _delay(2);
}
//---------------------------------------------------------------------------

void Inicializa_LCD(unsigned int Endereco_LCD, unsigned int Endereco_paralela)
{
  Escreve_instrucao_LCD(0x3F, Endereco_LCD, Endereco_paralela); // 2 linhas, 5x10 pontos
  _delay(1);
  Escreve_instrucao_LCD(0x0F, Endereco_LCD, Endereco_paralela); // Display on, cursor on, blinking on
  _delay(1);
  Escreve_instrucao_LCD(0x01, Endereco_LCD, Endereco_paralela); // Limpa Display
  _delay(2);
  Escreve_instrucao_LCD(0x06, Endereco_LCD, Endereco_paralela); // Increase cursor, display is shifted
  _delay(1);
}
//---------------------------------------------------------------------------

void ProcuraLCD()
{
  for (Endereco_LCD = 0; Endereco_LCD <= 3; Endereco_LCD++)
  {
    Inicializa_LCD(Endereco_LCD, 0x378);
    Escreve_dados_LCD(0xA5, dadoEndereco_LCD, 0x378); // Escreve Z (1010 0101)

  }
}
//---------------------------------------------------------------------------

void Escreve_dados_LCD(unsigned int dado, unsigned int Endereco_LCD, unsigned int Endereco_paralela)
{
  unsigned int LCD;

  LCD = LCD & 0xF7; // Desabilita o LCD
  DlPortWritePortUchar(Endereco_paralela + 2, 0x07); // Nenhum CI selecionado (CS's altos), RS e R/W em zero

//  _delay(1);

  LCD = (0xFF - Endereco_LCD) & 0x04; // Separa o terceiro bit (saídas são complementares)
  LCD = LCD << 1; // Desloca o terceiro bit para o quarto bit
  LCD = LCD | (0xFF - Endereco_LCD); // Compõe o endereço a ser transmitido para o CI
  LCD = LCD & 0x0B; // Coloca /C3 e C2 em zero

  DlPortWritePortUchar(Endereco_paralela + 2, 0x03); // Armazerna os valores de RS e R/W no latch

//  _delay(1);

  DlPortWritePortUchar(Endereco_paralela, 0x40); // Coloca a instrução nas linhas de dados
                                                 // Set CG RAM Address
//  _delay(1);

  DlPortWritePortUchar(Endereco_paralela + 2, 0x01); // Armazerna os valores de RS e R/W no latch

//  _delay(1);

  DlPortWritePortUchar(Endereco_paralela, dado);

//  _delay(1);
}
//---------------------------------------------------------------------------

void Escreve_instrucao_LCD(unsigned int instrucao, unsigned int Endereco_LCD, unsigned int Endereco_paralela)
{
  unsigned int LCD;

  LCD = LCD & 0xF7; // Desabilita o LCD
  DlPortWritePortUchar(Endereco_paralela + 2, 0x07); // Nenhum CI selecionado (CS's altos), RS e R/W em zero

//  _delay(1);

  LCD = (0xFF - Endereco_LCD) & 0x04; // Separa o terceiro bit (saídas são complementares)
  LCD = LCD << 1; // Desloca o terceiro bit para o quarto bit
  LCD = LCD | (0xFF - Endereco_LCD); // Compõe o endereço a ser transmitido para o CI
  LCD = LCD & 0x0B; // Coloca /C3 e C2 em zero

  DlPortWritePortUchar(Endereco_paralela + 2, 0x03); // Armazerna os valores de RS e R/W no latch

//  _delay(1);

  DlPortWritePortUchar(Endereco_paralela, instrucao); // Coloca a instrução nas linhas de dados

//  _delay(1);

  DlPortWritePortUchar(Endereco_paralela + 2 , LCD); // Habilita o LCD

//  _delay(1);

  LCD = LCD & 0xF7; // Desabilita o LCD
  DlPortWritePortUchar(Endereco_paralela + 2, LCD); // Nenhum CI selecionado (CS's altos)

//  _delay(1);
}

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