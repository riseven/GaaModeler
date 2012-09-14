//---------------------------------------------------------------------------
//      PRACTICA DE GRAFICOS AVANZADOS Y ANIMACION
//      Curso 04-05
//      Definición de las clases:
//              - TCanvasForm
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#ifndef FormularioCanvasH
#define FormularioCanvasH
//---------------------------------------------------------------------------

#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Menus.hpp>
#include <vcl\ComCtrls.hpp>

//---------------------------------------------------------------------------
#include "Escena.h"
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//      CLASE TCanvasForm: Formulario principal de la aplicación
//---------------------------------------------------------------------------

class TCanvasForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *PanelFondo;

	TMainMenu *MainMenu1;
	TMenuItem *Archivos;
	TMenuItem *Cerrar;
	TMenuItem *Figuras;
	TMenuItem *Esfera;
	TMenuItem *Modelosiluminacion;
	TMenuItem *Alambre;
	TMenuItem *Phong;
	TGroupBox *GroupBoxIluminacion;
	TLabel *LabelIluminacionAmbiental;
	TTrackBar *TrackBarAmbiental;
	TLabel *LabelPorcentajeAmbiental;
	TLabel *LabelIluminacionDifusa;
	TTrackBar *TrackBarDifusa;
	TLabel *LabelPorcentajeDifusa;
	TLabel *LabelIluminacionEspecular;
	TTrackBar *TrackBarEspecular;
	TLabel *LabelPorcentajeEspecular;

	TImage *MiCanvas;
    TMenuItem *Cilindro1;
    TMenuItem *Cono1;
    TMenuItem *Toro1;
        TMenuItem *Prisma1;
        TMenuItem *M1;
    TMenuItem *AlambreConOcultacion;
    TMenuItem *N1;
    TMenuItem *Blinn;
    TMenuItem *CookTorrance;
    TGroupBox *GroupBoxBlinn;
    TLabel *Label7;
    TLabel *LabelMate;
    TTrackBar *TrackBarMate;
    TGroupBox *GroupBoxPhong;
    TLabel *Label15;
    TLabel *LabelRugosidad;
    TTrackBar *TrackBarRugosidad;
    TMenuItem *Redibujar1;
    TLabel *Label1;
    TTrackBar *TrackBarRefraccion;
    TLabel *Label2;
    TLabel *LabelRefraccion;
    TGroupBox *GroupBoxCookTorrance;
    TLabel *Label3;
    TLabel *LabelMateCook;
    TLabel *Label5;
    TTrackBar *TrackBarMateCook;
    TLabel *Label9;
    TTrackBar *TrackBarRefraccionG;
    TLabel *LabelRefraccionG;
    TLabel *Label11;
    TTrackBar *TrackBarRefraccionR;
    TLabel *LabelRefraccionR;
    TLabel *Label6;
    TTrackBar *TrackBarRefraccionB;
    TLabel *LabelRefraccionB;
    TMenuItem *CellShading1;
    TGroupBox *GroupBoxRayTracing;
    TLabel *Label4;
    TLabel *LabelProporcionLocal;
    TLabel *Label12;
    TLabel *LabelProporcionRefractiva;
    TLabel *Label14;
    TLabel *LabelProporcionReflexiva;
    TLabel *Label17;
    TLabel *LabelUmbral;
    TTrackBar *TrackBarProporcionLocal;
    TTrackBar *TrackBarProporcionRefractiva;
    TTrackBar *TrackBarProporcionReflexiva;
    TTrackBar *TrackBarUmbral;
    TMenuItem *N2;
    TMenuItem *RayTracing1;
	void __fastcall CerrarClick(TObject *Sender);
	void __fastcall EsferaClick(TObject *Sender);
	void __fastcall AlambreClick(TObject *Sender);
	void __fastcall PhongClick(TObject *Sender);

	void __fastcall TrackBarAmbientalChange(TObject *Sender);
	void __fastcall TrackBarDifusaChange(TObject *Sender);
	void __fastcall TrackBarEspecularChange(TObject *Sender);

	void __fastcall MiCanvasMouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);
	void __fastcall MiCanvasMouseMove(TObject *Sender, TShiftState Shift, int X,
	int Y);
	void __fastcall MiCanvasMouseUp(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);

    void __fastcall Cilindro1Click(TObject *Sender);
    void __fastcall Cono1Click(TObject *Sender);
    void __fastcall Toro1Click(TObject *Sender);
        void __fastcall Prisma1Click(TObject *Sender);
        void __fastcall M1Click(TObject *Sender);
        void __fastcall BotonAceptarIluminacionClick(TObject *Sender);
    void __fastcall AlambreConOcultacionClick(TObject *Sender);
    void __fastcall TrackBarRugsidadChange(TObject *Sender);
    void __fastcall BotonDibujarClick(TObject *Sender);
    void __fastcall BlinnClick(TObject *Sender);
    void __fastcall Redibujar1Click(TObject *Sender);
    void __fastcall TrackBarMateChange(TObject *Sender);
    void __fastcall TrackBarRefraccionChange(TObject *Sender);
    void __fastcall CookTorranceClick(TObject *Sender);
    void __fastcall TrackBarRefraccionRChange(TObject *Sender);
    void __fastcall TrackBarRefraccionGChange(TObject *Sender);
    void __fastcall TrackBarRefraccionBChange(TObject *Sender);
    void __fastcall TrackBarMateCookChange(TObject *Sender);
    void __fastcall CellShading1Click(TObject *Sender);
    void __fastcall RayTracing1Click(TObject *Sender);
    void __fastcall TrackBarProporcionLocalChange(TObject *Sender);
    void __fastcall TrackBarProporcionReflexivaChange(TObject *Sender);
    void __fastcall TrackBarProporcionRefractivaChange(TObject *Sender);
    void __fastcall TrackBarUmbralChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TCanvasForm(TComponent* Owner);

            TEscena *Escena;
    void UncheckModelosIluminacion();
    void UnshowAll();

};
//---------------------------------------------------------------------------
extern TCanvasForm *CanvasForm;
//---------------------------------------------------------------------------
#endif
