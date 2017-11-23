//---------------------------------------------------------------------------

bool inicia_aquisicao = false;  // Variável global

#include <vcl.h>
#pragma hdrstop

#include "Unit1_lcd.h"
#include "..\..\bibliotecas\include\teclado4x3.h"
#include "..\..\bibliotecas\include\lcd2x40.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Botao_sairClick(TObject *Sender)
{
  Close();        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Botao_inicia_aquisicaoClick(TObject *Sender)
{
  unsigned short int Endereco_paralela, Endereco_teclado, linha, Endereco_LCD;
  bool executou;
  char caracter;
  string texto;

  Botao_inicia_aquisicao->Enabled = false;

  Endereco_paralela = StrToInt(Campo_endereco_paralela->Text);
  Endereco_LCD = StrToInt(Campo_endereco_LCD->Text);

  Inicializa_LCD(Endereco_LCD, Endereco_paralela);

  // Posiciona o cursor na primeira linha e escreve a mensagem inicial
  linha = 1;
  while (linha <= Texto_inicial_LCD_1->Text.Length())
  {
    texto = texto + Texto_inicial_LCD_1->Text[linha];
    linha ++;
  }

  Escreve_texto_LCD(texto, Endereco_LCD, Endereco_paralela);

  // Posiciona o cursor na segunda linha e escreve a mensagem inicial
  texto.clear();
  linha = 2;
  executou = Linha_LCD(linha, Endereco_LCD, Endereco_paralela);
  linha = 1;
  while (linha <= Texto_inicial_LCD_2->Text.Length())
  {
    texto = texto + Texto_inicial_LCD_2->Text[linha];
    linha ++;
  }

  Escreve_texto_LCD(texto, Endereco_LCD, Endereco_paralela);

  Timer1->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  unsigned short int Endereco_paralela, Endereco_teclado, Endereco_LCD;
  int tecla;
  string texto;

  Endereco_paralela = StrToInt(Campo_endereco_paralela->Text);
  Endereco_teclado = StrToInt(Campo_endereco_teclado->Text);
  Endereco_LCD = StrToInt(Campo_endereco_LCD->Text);

  tecla = le_teclado(Endereco_teclado, Endereco_paralela);

  if (inicia_aquisicao == false)
  {
    if (tecla == 10)
    {
      inicia_aquisicao = true;
      Limpa_LCD(Endereco_LCD, Endereco_paralela);
    }
  }
  else
  {
    if ((tecla >= 0) & (tecla <= 9))
    {
      tecla = tecla + 0x30;
      texto = tecla;
      Escreve_texto_LCD(texto, Endereco_LCD, Endereco_paralela);
      Campo_tecla_digitada->Text = texto[0];
    }
    else
    {
      if (tecla == 10)
      {
        texto = '*';
        Escreve_texto_LCD(texto, Endereco_LCD, Endereco_paralela);
        Campo_tecla_digitada->Text = texto[0];
      }
      else
      {
        if (tecla == 11)
        {
          texto = '#';
          Escreve_texto_LCD(texto, Endereco_LCD, Endereco_paralela);
          Campo_tecla_digitada->Text = texto[0];
        }
      }
    }
  }
}
//---------------------------------------------------------------------------

