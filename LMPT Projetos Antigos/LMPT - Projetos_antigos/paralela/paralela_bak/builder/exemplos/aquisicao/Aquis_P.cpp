//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Aquis_P.h"
#include "paralela.h"
#include "tlc1543.h"
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
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  unsigned int end_porta, end_canal, end_ci;
  int valor_lido;
  double tensao;

  end_porta = StrToInt(Edit1->Text);
  end_ci = StrToInt(Edit4->Text);
  end_canal = StrToInt(Edit3->Text);

  valor_lido = le_canal(end_canal, end_ci, end_porta);
  if (valor_lido < 0)
  {
    Edit2->Text = "Canal inválido";
  }
  else
  {
    tensao = (valor_lido*5.031) / 1023.0;
    Edit2->Text = FloatToStrF(tensao,ffGeneral,4,5);
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Botao_Parar_aquisicaoClick(TObject *Sender)
{
  Timer1->Enabled = false;        
}
//---------------------------------------------------------------------------

