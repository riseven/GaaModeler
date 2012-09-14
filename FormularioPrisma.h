//---------------------------------------------------------------------------

#ifndef FormularioPrismaH
#define FormularioPrismaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TFormParamPrisma : public TForm
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
        TEdit *EditAncho;
        TButton *BotonColor;
        TEdit *EditColor;
        TEdit *EditAlto;
        TEdit *EditProfundidad;
        TColorDialog *ColorDialog1;
        void __fastcall BotonColorClick(TObject *Sender);
        void __fastcall BotonCancelarClick(TObject *Sender);
        void __fastcall BotonOKClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormParamPrisma(TComponent* Owner);
        bool EsOK;
        double X, Y, Z, Radio;
        double Ancho, Alto, Profundidad;
        TColor Color;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormParamPrisma *FormParamPrisma;
//---------------------------------------------------------------------------
#endif
