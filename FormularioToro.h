//---------------------------------------------------------------------------
#ifndef FormularioToroH
#define FormularioToroH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TFormParamToro : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TBitBtn *BotonOK;
    TBitBtn *BotonCancelar;
    TEdit *EditX;
    TEdit *EditY;
    TEdit *EditZ;
    TEdit *EditRadio;
    TButton *BotonColor;
    TEdit *EditColor;
    TEdit *EditParalelos;
    TEdit *EditAnillos;
    TColorDialog *ColorDialog1;
    TLabel *Label8;
    TEdit *EditRadioAnillos;
    void __fastcall BotonColorClick(TObject *Sender);
    void __fastcall BotonCancelarClick(TObject *Sender);
    void __fastcall BotonOKClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFormParamToro(TComponent* Owner);
        bool EsOK;
        double X, Y, Z, Radio, RadioAnillos;
        int Paralelos, Anillos;
        TColor Color;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormParamToro *FormParamToro;
//---------------------------------------------------------------------------
#endif
