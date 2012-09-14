//---------------------------------------------------------------------------
#ifndef FormularioEsferaH
#define FormularioEsferaH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\Dialogs.hpp>
//---------------------------------------------------------------------------
class TFormParamEsfera : public TForm
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
	TEdit *EditMeridianos;
	TColorDialog *ColorDialog1;
	void __fastcall BotonOKClick(TObject *Sender);
	void __fastcall BotonCancelarClick(TObject *Sender);
	void __fastcall BotonColorClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormParamEsfera(TComponent* Owner);
        bool EsOK;
        double X, Y, Z, Radio;
        int Paralelos, Meridianos;
        TColor Color;
};
//---------------------------------------------------------------------------
extern TFormParamEsfera *FormParamEsfera;
//---------------------------------------------------------------------------
#endif
