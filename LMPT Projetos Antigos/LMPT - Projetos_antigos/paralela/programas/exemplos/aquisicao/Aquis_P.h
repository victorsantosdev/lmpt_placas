//---------------------------------------------------------------------------

#ifndef Aquis_PH
#define Aquis_PH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <time.h>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TEdit *Edit1;
        TEdit *Edit2;
        TLabel *Label1;
        TLabel *Label2;
        TEdit *Edit3;
        TLabel *Label3;
        TEdit *Edit4;
        TLabel *Label4;
        TButton *Botao_Parar_aquisicao;
        TEdit *Edit5;
        TLabel *Label5;
        TTimer *Timer1;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Botao_Parar_aquisicaoClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
