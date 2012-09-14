//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("FormularioCanvas.cpp", CanvasForm);
USERES("Canvas.res");
USEUNIT("Escena.cpp");
USEFORM("FormularioEsfera.cpp", FormParamEsfera);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TCanvasForm), &CanvasForm);
		Application->CreateForm(__classid(TFormParamEsfera), &FormParamEsfera);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------
