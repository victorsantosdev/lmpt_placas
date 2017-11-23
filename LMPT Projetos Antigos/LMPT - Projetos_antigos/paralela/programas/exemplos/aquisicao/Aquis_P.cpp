//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Aquis_P.h"
#include "..\..\bibliotecas\tlc1543\tlc1543.h"

unsigned int end_porta, end_canal, end_ci, num_aquisicoes;
time_t tempo_inicial, tempo_final;
int valor_lido;
int buffer[20000]; // O vetor deve ter um comprimento suficiente
                   // para guardar todas as aquisições
double tensao, somador;

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
void __fastcall TForm1::Button1Click(TObject *Sender)
{
  Timer1->Enabled = true;
  Button1->Enabled = false;
  Botao_Parar_aquisicao->Enabled = true;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Botao_Parar_aquisicaoClick(TObject *Sender)
{
  Timer1->Enabled = false;
  Botao_Parar_aquisicao->Enabled = false;
  Button1->Enabled = true;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  end_porta = StrToInt(Edit1->Text);
  end_ci = StrToInt(Edit4->Text);
  end_canal = StrToInt(Edit3->Text);
  tempo_inicial = time(NULL);
  tempo_final = time(NULL);
  somador = 0;
  num_aquisicoes = 0;

  while ((difftime(tempo_final, tempo_inicial)) < 1)
  {
    valor_lido = le_canal(end_canal, end_ci, end_porta);
    buffer[num_aquisicoes] = valor_lido;

    if (valor_lido < 0)
    {
      Edit2->Text = "Canal inválido";
      Timer1->Enabled = false;
      Button1->Enabled = true;
      Botao_Parar_aquisicao->Enabled = false;
      break;
    }
    else
    {
      num_aquisicoes++;
      tempo_final = time(NULL);
    }
  }
  for (unsigned int contador = 0 ; contador <= num_aquisicoes ; contador++)
  {
    somador = somador + buffer[contador];
  }


  tensao = ((somador/num_aquisicoes)*5.031) / 1023.0;
  Edit2->Text = FloatToStrF(tensao,ffGeneral,4,5);
  Edit5->Text = IntToStr(num_aquisicoes);
  num_aquisicoes = 0;
}
//---------------------------------------------------------------------------

