//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("Aquis.res");
USEFORM("Aquis_P.cpp", Form1);
USEUNIT("paralela.cpp");
USEUNIT("tlc1543.cpp");
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
