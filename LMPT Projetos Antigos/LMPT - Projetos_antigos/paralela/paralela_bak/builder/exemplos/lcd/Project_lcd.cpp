//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("Project_lcd.res");
USEFORM("Unit1_lcd.cpp", Form1);
USEUNIT("lcd_40.cpp");
USEUNIT("paralela.cpp");
USEUNIT("teclado.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TForm1), &Form1);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
