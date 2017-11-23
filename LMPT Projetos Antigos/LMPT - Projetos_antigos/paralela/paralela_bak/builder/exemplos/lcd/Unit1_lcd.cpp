//---------------------------------------------------------------------------

bool inicia_aquisicao = false;  // Variável global

#include <vcl.h>
#pragma hdrstop

#include "Unit1_lcd.h"
#include "lcd_40.h"
#include "teclado.h"

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

  Botao_inicia_aquisicao->Enabled = false;

  Endereco_paralela = StrToInt(Campo_endereco_paralela->Text);
  Endereco_LCD = StrToInt(Campo_endereco_LCD->Text);

  Inicializa_LCD(Endereco_paralela, Endereco_LCD);

  // Posiciona o cursor na primeira linha e escreve a mensagem inicial
  linha = 1;
  executou = Linha_LCD(Endereco_paralela, Endereco_LCD, linha);
  while (linha <= Texto_inicial_LCD_1->Text.Length())
  {
    caracter = Texto_inicial_LCD_1->Text[linha];
    Escreve_caracter_LCD(Endereco_paralela,Endereco_LCD, caracter);
    linha ++;
  }

  // Posiciona o cursor na segunda linha e escreve a mensagem inicial
  linha = 2;
  executou = Linha_LCD(Endereco_paralela, Endereco_LCD, linha);
  linha = 1;
  while (linha <= Texto_inicial_LCD_2->Text.Length())
  {
    caracter = Texto_inicial_LCD_2->Text[linha];
    Escreve_caracter_LCD(Endereco_paralela, Endereco_LCD, caracter);
    linha ++;
  }
     
  Timer1->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  unsigned short int Endereco_paralela, Endereco_teclado, Endereco_LCD;
  int tecla;
  char caracter;

  Endereco_paralela = StrToInt(Campo_endereco_paralela->Text);
  Endereco_teclado = StrToInt(Campo_endereco_teclado->Text);
  Endereco_LCD = StrToInt(Campo_endereco_LCD->Text);

  tecla = le_teclado(Endereco_paralela, Endereco_teclado);

  if (inicia_aquisicao == false)
  {
    if (tecla == 10)
    {
      inicia_aquisicao = true;
      Limpa_LCD(Endereco_paralela, Endereco_LCD);
    }
  }
  else
  {
    if ((tecla >= 0) & (tecla <= 9))
    {
      tecla = tecla + 0x30;
      caracter = tecla;
      Escreve_caracter_LCD(Endereco_paralela, Endereco_LCD, caracter);
      Campo_tecla_digitada->Text = caracter;
    }
    else
    {
      if (tecla == 10)
      {
        caracter = '*';
        Escreve_caracter_LCD(Endereco_paralela, Endereco_LCD, caracter);
        Campo_tecla_digitada->Text = caracter;
      }
      else
      {
        if (tecla == 11)
        {
          caracter = '#';
          Escreve_caracter_LCD(Endereco_paralela, Endereco_LCD, caracter);
          Campo_tecla_digitada->Text = caracter;
        }
      }
    }
  }  
}
//---------------------------------------------------------------------------

