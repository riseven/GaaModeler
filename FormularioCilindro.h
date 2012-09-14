//---------------------------------------------------------------------------
#ifndef FormularioCilindroH
#define FormularioCilindroH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TFormParamCilindro : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TBitBtn *BotonOK;
    TBitBtn *BotonCancelar;
    TEdit *EditX;
    TEdit *EditY;
    TEdit *EditZ;
    TEdit *EditRadio;
    TButton *BotonColor;
    TEdit *EditColor;
    TEdit *EditParalelos;
    TColorDialog *ColorDialog1;
    TLabel *Label7;
    TEdit *EditAltura;
    void __fastcall BotonColorClick(TObject *Sender);
    void __fastcall BotonCancelarClick(TObject *Sender);
    void __fastcall BotonOKClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
    __fastcall TFormParamCilindro(TComponent* Owner);
        bool EsOK;
        double X, Y, Z, Radio;
        int Paralelos;
        double Altura;
        TColor Color;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormParamCilindro *FormParamCilindro;
//---------------------------------------------------------------------------
#endif
