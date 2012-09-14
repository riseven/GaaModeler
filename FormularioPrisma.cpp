//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormularioPrisma.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormParamPrisma *FormParamPrisma;
//---------------------------------------------------------------------------
__fastcall TFormParamPrisma::TFormParamPrisma(TComponent* Owner)
        : TForm(Owner)
{
        X = 0.0;
        Y = 0.0;
        Z = 0.0;
        Ancho = 100.0;
        Alto = 100.0 ;
        Profundidad = 100.0 ;
        Color = clBlue;
        EditX->Text = "0,0";
        EditY->Text = "0,0";
        EditZ->Text = "0,0";
        EditAncho->Text = "100,0";
        EditAlto->Text = "100,0";
        EditProfundidad->Text = "100,0";
        EditColor->Color = Color;
}
//---------------------------------------------------------------------------
void __fastcall TFormParamPrisma::BotonColorClick(TObject *Sender)
{
        ColorDialog1->Execute();
        Color = ColorDialog1->Color;
        EditColor->Color = ColorDialog1->Color;        
}
//---------------------------------------------------------------------------
void __fastcall TFormParamPrisma::BotonCancelarClick(TObject *Sender)
{
        EsOK = false;
        ModalResult = mrCancel;
}
//---------------------------------------------------------------------------
void __fastcall TFormParamPrisma::BotonOKClick(TObject *Sender)
{
        X = StrToFloat(EditX->Text);
	    Y = StrToFloat(EditY->Text);
	    Z = StrToFloat(EditZ->Text);
        Ancho = StrToFloat(EditAncho->Text);
        Alto = StrToFloat(EditAlto->Text);
        Profundidad = StrToFloat(EditProfundidad->Text);
        EsOK = true;
        ModalResult = mrOk;
}
//---------------------------------------------------------------------------
