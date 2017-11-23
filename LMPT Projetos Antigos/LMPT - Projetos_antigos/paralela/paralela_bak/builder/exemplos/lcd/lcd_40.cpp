#include "paralela.h"
#include "lcd_40.h"
#include <vcl.h>

void Escreve_caracter_LCD(unsigned int Endereco_paralela, unsigned int Endereco_LCD, char caracter_LCD)
{
  unsigned int LCD;

  OutPortB(Endereco_paralela + 2, 0x05); // Nenhum CI selecionado (CS's altos), RS em 1 e R/W em zero
  Sleep(1);

  LCD = (0xFF - Endereco_LCD) & 0x04; // Separa o terceiro bit (saídas são complementares)
  LCD = LCD << 1; // Desloca o terceiro bit para o quarto bit
  LCD = LCD | (0xFF - Endereco_LCD); // Compõe o endereço a ser transmitido para o CI
  LCD = LCD & 0x0B; // Coloca /C3 e C2 em zero

  OutPortB(Endereco_paralela + 2, 0x01); // Armazerna os valores de RS e R/W no latch
  Sleep(1);

//  OutPortB(Endereco_paralela + 2, 0x01); // Desabilita o LCD, coloca RS em 1 e R/W em zero
//  Sleep(1);

  OutPortB(Endereco_paralela, caracter_LCD);
  Sleep(1);

  OutPortB(Endereco_paralela + 2 , LCD); // Habilita o LCD
  Sleep(1);

  LCD = LCD & 0xF7; // Desabilita o LCD
  OutPortB(Endereco_paralela + 2, LCD); // Nenhum CI selecionado (CS's altos)
  Sleep(1);
}

bool Linha_LCD(unsigned int Endereco_paralela, unsigned int Endereco_LCD, unsigned int linha)
{
  bool Executou;

  if (linha == 1)
  {
    Escreve_instrucao_LCD(Endereco_paralela, Endereco_LCD, 0x80); // Coloca o cursor no início da primeira linha
    Executou = true;
    return(Executou);
  }
  else
  {
    if (linha == 2)
    {
      Escreve_instrucao_LCD(Endereco_paralela, Endereco_LCD, 0xC0); // Coloca o cursor no início da segunda linha
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

void Limpa_LCD(unsigned int Endereco_paralela, unsigned int Endereco_LCD)
{
  Escreve_instrucao_LCD(Endereco_paralela, Endereco_LCD, 0x01); // Limpa Display
  Sleep(2);
}

void Inicializa_LCD(unsigned int Endereco_paralela, unsigned int Endereco_LCD)
{
  Sleep(20);
  Escreve_instrucao_LCD(Endereco_paralela, Endereco_LCD, 0x3F); // 2 linhas, 5x10 pontos
  Sleep(1);
  Escreve_instrucao_LCD(Endereco_paralela, Endereco_LCD, 0x0F); // Display on, cursor on, blinking on
  Sleep(1);
  Escreve_instrucao_LCD(Endereco_paralela, Endereco_LCD, 0x01); // Limpa Display
  Sleep(2);
  Escreve_instrucao_LCD(Endereco_paralela, Endereco_LCD, 0x06); // Increase cursor, display is shifted
  Sleep(1);
}

void Escreve_instrucao_LCD(unsigned int Endereco_paralela, unsigned int Endereco_LCD, unsigned int instrucao)
{
  unsigned int LCD;

  OutPortB(Endereco_paralela + 2, 0x07); // Nenhum CI selecionado (CS's altos), RS e R/W em zero
  Sleep(1);

  LCD = (0xFF - Endereco_LCD) & 0x04; // Separa o terceiro bit (saídas são complementares)
  LCD = LCD << 1; // Desloca o terceiro bit para o quarto bit
  LCD = LCD | (0xFF - Endereco_LCD); // Compõe o endereço a ser transmitido para o CI
  LCD = LCD & 0x0B; // Coloca /C3 e C2 em zero

  OutPortB(Endereco_paralela + 2, 0x03); // Armazerna os valores de RS e R/W no latch
  Sleep(1);

  OutPortB(Endereco_paralela, instrucao); // Coloca a instrução nas linhas de dados
  Sleep(1);

  OutPortB(Endereco_paralela + 2 , LCD); // Habilita o LCD
  Sleep(1);

  LCD = LCD & 0xF7; // Desabilita o LCD
  OutPortB(Endereco_paralela + 2, LCD); // Nenhum CI selecionado (CS's altos)
  Sleep(1);
}
