//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "FormularioEsfera.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TFormParamEsfera *FormParamEsfera;
//---------------------------------------------------------------------------
__fastcall TFormParamEsfera::TFormParamEsfera(TComponent* Owner)
	: TForm(Owner)
{
        X = 0.0;
        Y = 0.0;
        Z = 0.0;
        Radio = 100.0;
        Paralelos = 32;
        Meridianos = 32;
        Color = clBlue;
        EditX->Text = "0,0";
        EditY->Text = "0,0";
        EditZ->Text = "0,0";
        EditRadio->Text = "100,0";
        EditParalelos->Text = "32";
        EditMeridianos->Text = "32";
        EditColor->Color = Color;
}
//---------------------------------------------------------------------------
void __fastcall TFormParamEsfera::BotonOKClick(TObject *Sender)
{
	X = StrToFloat(EditX->Text);
	Y = StrToFloat(EditY->Text);
	Z = StrToFloat(EditZ->Text);
	Radio = StrToFloat(EditRadio->Text);
        Paralelos = StrToInt(EditParalelos->Text);
        Meridianos = StrToInt(EditMeridianos->Text);
        EsOK = true;
        ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TFormParamEsfera::BotonCancelarClick(TObject *Sender)
{
        EsOK = false;
        ModalResult = mrCancel;
}
//---------------------------------------------------------------------------
void __fastcall TFormParamEsfera::BotonColorClick(TObject *Sender)
{
        ColorDialog1->Execute();
        Color = ColorDialog1->Color;
        EditColor->Color = ColorDialog1->Color;
}
//---------------------------------------------------------------------------