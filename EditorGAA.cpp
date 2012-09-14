//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USEFORM("FormularioCanvas.cpp", CanvasForm);
USEFORM("FormularioEsfera.cpp", FormParamEsfera);
USEFORM("FormularioCilindro.cpp", FormParamCilindro);
USEFORM("FormularioCono.cpp", FormParamCono);
USEFORM("FormularioToro.cpp", FormParamToro);
USEFORM("FormularioPrisma.cpp", FormParamPrisma);
USEFORM("FormularioHMap.cpp", FormParamHMap);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TCanvasForm), &CanvasForm);
                 Application->CreateForm(__classid(TFormParamEsfera), &FormParamEsfera);
                 Application->CreateForm(__classid(TFormParamCilindro), &FormParamCilindro);
                 Application->CreateForm(__classid(TFormParamCono), &FormParamCono);
                 Application->CreateForm(__classid(TFormParamToro), &FormParamToro);
                 Application->CreateForm(__classid(TFormParamPrisma), &FormParamPrisma);
                 Application->CreateForm(__classid(TFormParamHMap), &FormParamHMap);
                 Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
