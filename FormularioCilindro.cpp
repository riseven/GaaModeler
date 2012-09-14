//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "FormularioCilindro.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormParamCilindro *FormParamCilindro;
//---------------------------------------------------------------------------
__fastcall TFormParamCilindro::TFormParamCilindro(TComponent* Owner)
    : TForm(Owner)
{
        X = 0.0;
        Y = 0.0;
        Z = 0.0;
        Radio = 100.0;
        Paralelos = 32;
        Altura = 200.0 ;
        Color = clBlue;
        EditX->Text = "0,0";
        EditY->Text = "0,0";
        EditZ->Text = "0,0";
        EditRadio->Text = "100,0";
        EditParalelos->Text = "32";
        EditAltura->Text = "200,0";
        EditColor->Color = Color;
}
//---------------------------------------------------------------------------
void __fastcall TFormParamCilindro::BotonColorClick(TObject *Sender)
{
        ColorDialog1->Execute();
        Color = ColorDialog1->Color;
        EditColor->Color = ColorDialog1->Color;
}
//---------------------------------------------------------------------------
void __fastcall TFormParamCilindro::BotonCancelarClick(TObject *Sender)
{
        EsOK = false;
        ModalResult = mrCancel;
}
//---------------------------------------------------------------------------
void __fastcall TFormParamCilindro::BotonOKClick(TObject *Sender)
{
	X = StrToFloat(EditX->Text);
	Y = StrToFloat(EditY->Text);
	Z = StrToFloat(EditZ->Text);
	Radio = StrToFloat(EditRadio->Text);
    Paralelos = StrToInt(EditParalelos->Text);
    Altura = StrToFloat(EditAltura->Text);
    EsOK = true;
    ModalResult = mrOk;
}
//---------------------------------------------------------------------------

