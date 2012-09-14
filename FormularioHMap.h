//---------------------------------------------------------------------------

#ifndef FormularioHMapH
#define FormularioHMapH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TFormParamHMap : public TForm
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
        TEdit *EditEscala;
        TButton *BotonColor;
        TEdit *EditColor;
        TEdit *EditAltura;
        TEdit *EditFichero;
        TColorDialog *ColorDialog1;
        TButton *BotonFichero;
        TOpenDialog *OpenDialog1;
        void __fastcall BotonFicheroClick(TObject *Sender);
        void __fastcall BotonColorClick(TObject *Sender);
        void __fastcall BotonCancelarClick(TObject *Sender);
        void __fastcall BotonOKClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormParamHMap(TComponent* Owner);
        bool EsOK;
        double X, Y, Z, Radio;
        double Escala, Altura;
        AnsiString Fichero ;
        TColor Color;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormParamHMap *FormParamHMap;
//---------------------------------------------------------------------------
#endif
