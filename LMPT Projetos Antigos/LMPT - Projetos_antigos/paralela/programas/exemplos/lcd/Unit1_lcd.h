//---------------------------------------------------------------------------

#ifndef Unit1_lcdH
#define Unit1_lcdH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TEdit *Campo_endereco_paralela;
        TEdit *Texto_inicial_LCD_1;
        TEdit *Texto_inicial_LCD_2;
        TLabel *Label1;
        TLabel *Label2;
        TEdit *Campo_tecla_digitada;
        TLabel *Label3;
        TLabel *Label4;
        TEdit *Campo_endereco_teclado;
        TButton *Botao_inicia_aquisicao;
        TButton *Botao_sair;
        TTimer *Timer1;
        TLabel *Label5;
        TEdit *Campo_endereco_LCD;
        void __fastcall Botao_sairClick(TObject *Sender);
        void __fastcall Botao_inicia_aquisicaoClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
