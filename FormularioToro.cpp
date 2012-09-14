//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "FormularioToro.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormParamToro *FormParamToro;
//---------------------------------------------------------------------------
__fastcall TFormParamToro::TFormParamToro(TComponent* Owner)
    : TForm(Owner)
{
        X = 0.0;
        Y = 0.0;
        Z = 0.0;
        Radio = 100.0;
        RadioAnillos = 10.0 ;
        Paralelos = 32;
        Anillos = 32 ;
        Color = clBlue;
        EditX->Text = "0,0";
        EditY->Text = "0,0";
        EditZ->Text = "0,0";
        EditRadio->Text = "100,0";
        EditRadioAnillos->Text = "10,0";
        EditParalelos->Text = "32";
        EditAnillos->Text = "32";
        EditColor->Color = Color;
}
//---------------------------------------------------------------------------
void __fastcall TFormParamToro::BotonColorClick(TObject *Sender)
{
        ColorDialog1->Execute();
        Color = ColorDialog1->Color;
        EditColor->Color = ColorDialog1->Color;      
}
//---------------------------------------------------------------------------
void __fastcall TFormParamToro::BotonCancelarClick(TObject *Sender)
{
        EsOK = false;
        ModalResult = mrCancel;     
}
//---------------------------------------------------------------------------
void __fastcall TFormParamToro::BotonOKClick(TObject *Sender)
{
	X = StrToFloat(EditX->Text);
	Y = StrToFloat(EditY->Text);
	Z = StrToFloat(EditZ->Text);
	Radio = StrToFloat(EditRadio->Text);
    RadioAnillos = StrToFloat(EditRadioAnillos->Text);
    Paralelos = StrToInt(EditParalelos->Text);
    Anillos = StrToInt(EditAnillos->Text);
    EsOK = true;
    ModalResult = mrOk;
}
//---------------------------------------------------------------------------
