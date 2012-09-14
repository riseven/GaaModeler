//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormularioHMap.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormParamHMap *FormParamHMap;
//---------------------------------------------------------------------------
__fastcall TFormParamHMap::TFormParamHMap(TComponent* Owner)
        : TForm(Owner)
{
        X = 0.0;
        Y = 0.0;
        Z = 0.0;
        Escala = 1.0 ;
        Altura = 100.0 ;
        Fichero = "";
        Color = clBlue;
        EditX->Text = "0,0";
        EditY->Text = "0,0";
        EditZ->Text = "0,0";
        EditEscala->Text = "1,0";
        EditAltura->Text = "100,0";
        EditFichero->Text = "";
        EditColor->Color = Color;
}
//---------------------------------------------------------------------------
void __fastcall TFormParamHMap::BotonFicheroClick(TObject *Sender)
{
        OpenDialog1->Execute();
        Fichero = OpenDialog1->FileName ;
        EditFichero->Text = Fichero ;
}
//---------------------------------------------------------------------------
void __fastcall TFormParamHMap::BotonColorClick(TObject *Sender)
{
        ColorDialog1->Execute();
        Color = ColorDialog1->Color;
        EditColor->Color = ColorDialog1->Color;          
}
//---------------------------------------------------------------------------
void __fastcall TFormParamHMap::BotonCancelarClick(TObject *Sender)
{
        EsOK = false;
        ModalResult = mrCancel;        
}
//---------------------------------------------------------------------------
void __fastcall TFormParamHMap::BotonOKClick(TObject *Sender)
{
        X = StrToFloat(EditX->Text);
	Y = StrToFloat(EditY->Text);
	Z = StrToFloat(EditZ->Text);
        Escala = StrToFloat(EditEscala->Text);
        Altura = StrToFloat(EditAltura->Text);
        Fichero = EditFichero->Text ;
        EsOK = true;
        ModalResult = mrOk;
}
//---------------------------------------------------------------------------
