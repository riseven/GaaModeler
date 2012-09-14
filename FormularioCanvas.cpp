//---------------------------------------------------------------------------
//      PRACTICA DE GRAFICOS AVANZADOS Y ANIMACION
//      Curso 04-05
//      Implementación de las clases:
//              - TCanvasForm
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "FormularioCanvas.h"
#include "Escena.h"
#include "FormularioEsfera.h"
#include "FormularioPrisma.h"
#include "FormularioCilindro.h"
#include "FormularioCono.h"
#include "FormularioToro.h"
#include "FormularioHMap.h"


//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TCanvasForm *CanvasForm;
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//      CONSTRUCTOR DE TCanvasForm
//---------------------------------------------------------------------------

__fastcall TCanvasForm::TCanvasForm(TComponent* Owner)
	: TForm(Owner)
{
        //----- Creamos la escena y le asignamos valor inicial a sus atributos públicos

        Escena = new TEscena (MiCanvas->ClientRect.Right-MiCanvas->ClientRect.Left,
                              MiCanvas->ClientRect.Bottom-MiCanvas->ClientRect.Top,
                              MiCanvas->Canvas);

        Escena->ProporcionAmbiental = 0.1;
        Escena->ProporcionDifusa = 0.7;
        Escena->ProporcionEspecular = 0.2;

        Escena->ProporcionLocal = 0.4;
        Escena->ProporcionReflexiva = 0.3;
        Escena->ProporcionRefractiva = 0.3;
        Escena->UmbralRayTracing = 0.01;

        Escena->Rugosidad = 1;
}

//---------------------------------------------------------------------------
//      FUNCION CerrarClick: Cerrar aplicación
//---------------------------------------------------------------------------

void __fastcall TCanvasForm::CerrarClick(TObject *Sender)
{
		Close();
    	delete Escena;
}

//---------------------------------------------------------------------------
//      FUNCIONES _________Click: Responder a las opciones del menú
//---------------------------------------------------------------------------

void __fastcall TCanvasForm::EsferaClick(TObject *Sender)
{
        //----- Mostrar el cuadro de diálogo para introducir los parámetros
        //----- de la esfera

        FormParamEsfera->ShowModal();
        if (FormParamEsfera->EsOK)
        {
    	        //----- Si hemos pulsado OK, convertir el color elegido en RGB,
                //----- y añadir una esfera a la escena

                T3DPunto Centro (FormParamEsfera->X, FormParamEsfera->Y, FormParamEsfera->Z);
                T3DPunto Color = ConvertirTColorEnRGB (FormParamEsfera->Color);

                Escena->AddEsfera(Centro, FormParamEsfera->Radio, FormParamEsfera->Paralelos, FormParamEsfera->Meridianos, Color);
        }
}

//---------------------------------------------------------------------------

void __fastcall TCanvasForm::AlambreClick(TObject *Sender)
{
        //----- Actualizar la marca de selección de las opciones de menú

        UncheckModelosIluminacion();
        Alambre->Checked = true;


        //----- Ocultar los controles de iluminación, porque en este modo
        //----- no son necesarios
        UnshowAll();

        //----- Actualizar el modelo de iluminación de la escena

        Escena->CambiarModeloIluminacion (MODELO_ALAMBRE);
        Escena->Dibujar();
}


//---------------------------------------------------------------------------

void __fastcall TCanvasForm::PhongClick(TObject *Sender)
{
	//----- Actualizar la marca de selección de las opciones de menú

        UncheckModelosIluminacion();
        Phong->Checked = true;

        //----- Mostrar los controles de iluminación, y ocultar los
        //----- que no son necesarios para este modo
        UnshowAll();
        GroupBoxIluminacion->Visible = true;
        GroupBoxIluminacion->Top = 0 ;
        GroupBoxPhong->Visible = true ;
        GroupBoxPhong->Top = 224 ;

         //----- Actualizar el modelo de iluminación de la escena

        Escena->CambiarModeloIluminacion (MODELO_PHONG);
        Escena->Dibujar();
}

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//      FUNCIONES TrackBar_______Change: Responder a los cambios en las
//      barras de deslizamiento
//---------------------------------------------------------------------------

void __fastcall TCanvasForm::TrackBarAmbientalChange(TObject *Sender)
{
        LabelPorcentajeAmbiental->Caption = IntToStr (TrackBarAmbiental->Position*10) + "%";
        Escena->ProporcionAmbiental = TrackBarAmbiental->Position / 10.0;
        //Escena->Dibujar();
}

//---------------------------------------------------------------------------

void __fastcall TCanvasForm::TrackBarDifusaChange(TObject *Sender)
{
        LabelPorcentajeDifusa->Caption = IntToStr (TrackBarDifusa->Position*10) + "%";
        Escena->ProporcionDifusa = TrackBarDifusa->Position / 10.0;
        //Escena->Dibujar();
}

//---------------------------------------------------------------------------

void __fastcall TCanvasForm::TrackBarEspecularChange(TObject *Sender)
{
        LabelPorcentajeEspecular->Caption = IntToStr (TrackBarEspecular->Position*10) + "%";
        Escena->ProporcionEspecular = TrackBarEspecular->Position / 10.0;
        //Escena->Dibujar();
}

//---------------------------------------------------------------------------
//      FUNCIONES de manejo de los eventos de ratón
//---------------------------------------------------------------------------

void __fastcall TCanvasForm::MiCanvasMouseDown(TObject *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y)
{
        Escena->RatonPinchar (X, Y);

}
//---------------------------------------------------------------------------
void __fastcall TCanvasForm::MiCanvasMouseMove(TObject *Sender,
	TShiftState Shift, int X, int Y)
{
          Escena->RatonMover (X, Y);

}
//---------------------------------------------------------------------------
void __fastcall TCanvasForm::MiCanvasMouseUp(TObject *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y)
{
          Escena->RatonSoltar (X, Y);

}
//------------------------------------------------------------------------------------------------------------------
void __fastcall TCanvasForm::Cilindro1Click(TObject *Sender)
{
        //----- Mostrar el cuadro de diálogo para introducir los parámetros
        //----- del cilindro

        FormParamCilindro->ShowModal();
        if (FormParamCilindro->EsOK)
        {
            // Si hemos pulsado OK, convertir el color elegido en RGB,
            // y añadir un cilindro a la escena

            T3DPunto Centro (FormParamCilindro->X, FormParamCilindro->Y, FormParamCilindro->Z);
            T3DPunto Color = ConvertirTColorEnRGB (FormParamCilindro->Color);

            Escena->AddCilindro(Centro, FormParamCilindro->Radio, FormParamCilindro->Altura, FormParamCilindro->Paralelos, Color);
        }
}
//---------------------------------------------------------------------------

void __fastcall TCanvasForm::Cono1Click(TObject *Sender)
{
        //----- Mostrar el cuadro de diálogo para introducir los parámetros
        //----- del cono

        FormParamCono->ShowModal();
        if (FormParamCono->EsOK)
        {
            // Si hemos pulsado OK, convertir el color elegido en RGB,
            // y añadir un cono a la escena

            T3DPunto Centro (FormParamCono->X, FormParamCono->Y, FormParamCono->Z);
            T3DPunto Color = ConvertirTColorEnRGB (FormParamCono->Color);

            Escena->AddCono(Centro, FormParamCono->Radio, FormParamCono->Altura, FormParamCono->Paralelos, Color);
        }
}
//---------------------------------------------------------------------------

void __fastcall TCanvasForm::Toro1Click(TObject *Sender)
{
        //----- Mostrar el cuadro de diálogo para introducir los parámetros
        //----- del toro

        FormParamToro->ShowModal();
        if (FormParamToro->EsOK)
        {
            // Si hemos pulsado OK, convertir el color elegido en RGB,
            // y añadir un toro a la escena

            T3DPunto Centro (FormParamToro->X, FormParamToro->Y, FormParamToro->Z);
            T3DPunto Color = ConvertirTColorEnRGB (FormParamToro->Color);

            Escena->AddToro(Centro, FormParamToro->Radio, FormParamToro->RadioAnillos, FormParamToro->Paralelos, FormParamToro->Anillos, Color);
        }
}
//---------------------------------------------------------------------------

void __fastcall TCanvasForm::Prisma1Click(TObject *Sender)
{
        //----- Mostrar el cuadro de dialogo para introducir los parametros
        //----- del prisma

        FormParamPrisma->ShowModal();
        if (FormParamPrisma->EsOK)
        {
                // Si hemos pulsado OK, convertir el color en RGB y añadir un
                // prisma a la escena

                T3DPunto Centro (FormParamPrisma->X, FormParamPrisma->Y, FormParamPrisma->Z);
                T3DPunto Color = ConvertirTColorEnRGB (FormParamPrisma->Color);

                Escena->AddPrisma(Centro, FormParamPrisma->Ancho, FormParamPrisma->Alto, FormParamPrisma->Profundidad, Color);
        }
}
//---------------------------------------------------------------------------

void __fastcall TCanvasForm::M1Click(TObject *Sender)
{
        //----- Mostrar el cuadro de dialogo para introducir los parametros
        //----- del mapa de alturas

        FormParamHMap->ShowModal();
        if (FormParamHMap->EsOK)
        {
                // Si hemos pulsado OK, convertir el color en RGB y añadir un
                // mapa de alturas a la escena

                T3DPunto Centro (FormParamHMap->X, FormParamHMap->Y, FormParamHMap->Z);
                T3DPunto Color = ConvertirTColorEnRGB (FormParamHMap->Color);

                Escena->AddHMap(Centro, FormParamHMap->Escala, FormParamHMap->Altura, FormParamHMap->Fichero, Color);
        }
}
//---------------------------------------------------------------------------

void __fastcall TCanvasForm::BotonAceptarIluminacionClick(TObject *Sender)
{
        //----- Al actualizar los cambios de parametros de phong
        //----- es cuando se redibuja la escena
        Escena->Dibujar();
}
//---------------------------------------------------------------------------

void __fastcall TCanvasForm::AlambreConOcultacionClick(TObject *Sender)
{
        //----- Actualizar la marca de selección de las opciones de menú

        UncheckModelosIluminacion();
        AlambreConOcultacion->Checked = true;


        //----- Ocultar los controles de iluminación, porque en este modo
        //----- no son necesarios
        UnshowAll();

        //----- Actualizar el modelo de iluminación de la escena

        Escena->CambiarModeloIluminacion (MODELO_ALAMBRE_OCULTACION);
        Escena->Dibujar();
}
//---------------------------------------------------------------------------
void TCanvasForm::UncheckModelosIluminacion()
{
    Alambre->Checked = false ;
    AlambreConOcultacion->Checked = false ;
    Phong->Checked = false ;
    Blinn->Checked = false ;
    CookTorrance->Checked = false ;
    CellShading1->Checked = false ;
    RayTracing1->Checked = false ;
}
void __fastcall TCanvasForm::TrackBarRugsidadChange(TObject *Sender)
{
    LabelRugosidad->Caption = IntToStr (TrackBarRugosidad->Position);
    Escena->Rugosidad = TrackBarRugosidad->Position ;
}
//---------------------------------------------------------------------------

void __fastcall TCanvasForm::BotonDibujarClick(TObject *Sender)
{
        Escena->Dibujar();
}
//---------------------------------------------------------------------------

void __fastcall TCanvasForm::BlinnClick(TObject *Sender)
{
	//----- Actualizar la marca de selección de las opciones de menú

        UncheckModelosIluminacion();
        Blinn->Checked = true;

        //----- Mostrar los controles de iluminación, y ocultar los
        //----- que no son necesarios para este modo

        UnshowAll();
        GroupBoxIluminacion->Visible = true;
        GroupBoxIluminacion->Top = 0 ;
        GroupBoxBlinn->Visible = true ;
        GroupBoxBlinn->Top = 224 ;

         //----- Actualizar el modelo de iluminación de la escena

        Escena->CambiarModeloIluminacion (MODELO_BLINN);
        Escena->Mate = TrackBarMate->Position/10.0;
        Escena->Refraccion.X = TrackBarRefraccion->Position+1;
        Escena->Dibujar();
}
//---------------------------------------------------------------------------

void __fastcall TCanvasForm::Redibujar1Click(TObject *Sender)
{
        Escena->Dibujar();    
}
//---------------------------------------------------------------------------


void __fastcall TCanvasForm::TrackBarMateChange(TObject *Sender)
{
    LabelMate->Caption = IntToStr (TrackBarMate->Position*10) + "%";
    Escena->Mate = TrackBarMate->Position / 10.0;
}
//---------------------------------------------------------------------------

void __fastcall TCanvasForm::TrackBarRefraccionChange(TObject *Sender)
{
    double value = (TrackBarRefraccion->Position+1)*3.0/11.0;
    LabelRefraccion->Caption = FloatToStr (value) ;
    Escena->Refraccion.X = value ;
}
//---------------------------------------------------------------------------
void TCanvasForm::UnshowAll()
{
    GroupBoxIluminacion->Visible = false ;
    GroupBoxPhong->Visible = false ;
    GroupBoxBlinn->Visible = false ;
    GroupBoxCookTorrance->Visible = false ;
    GroupBoxRayTracing->Visible = false ;
}

void __fastcall TCanvasForm::CookTorranceClick(TObject *Sender)
{
	//----- Actualizar la marca de selección de las opciones de menú

        UncheckModelosIluminacion();
        CookTorrance->Checked = true;

        //----- Mostrar los controles de iluminación, y ocultar los
        //----- que no son necesarios para este modo

        UnshowAll();
        GroupBoxIluminacion->Visible = true;
        GroupBoxIluminacion->Top = 0 ;
        GroupBoxCookTorrance->Visible = true ;
        GroupBoxCookTorrance->Top = 224 ;

         //----- Actualizar el modelo de iluminación de la escena
        Escena->Mate = TrackBarMateCook->Position/10.0;
        Escena->Refraccion.X = TrackBarRefraccionR->Position+1;
        Escena->Refraccion.Y = TrackBarRefraccionG->Position+1;
        Escena->Refraccion.Z = TrackBarRefraccionB->Position+1;
        Escena->CambiarModeloIluminacion (MODELO_COOK_TORRANCE);
        Escena->Dibujar();
}
//---------------------------------------------------------------------------

void __fastcall TCanvasForm::TrackBarRefraccionRChange(TObject *Sender)
{
    double value = (TrackBarRefraccionR->Position+1)*3.0/11.0;
    LabelRefraccionR->Caption = FloatToStr (value) ;
    Escena->Refraccion.X = value ;
}
//---------------------------------------------------------------------------

void __fastcall TCanvasForm::TrackBarRefraccionGChange(TObject *Sender)
{
    double value = (TrackBarRefraccionG->Position+1)*3.0/11.0;
    LabelRefraccionG->Caption = FloatToStr (value) ;
    Escena->Refraccion.Y = value ;
}
//---------------------------------------------------------------------------

void __fastcall TCanvasForm::TrackBarRefraccionBChange(TObject *Sender)
{
    double value = (TrackBarRefraccionB->Position+1)*3.0/11.0;
    LabelRefraccionB->Caption = FloatToStr (value) ;
    Escena->Refraccion.Z = value ;
}
//---------------------------------------------------------------------------

void __fastcall TCanvasForm::TrackBarMateCookChange(TObject *Sender)
{
    LabelMateCook->Caption = IntToStr (TrackBarMateCook->Position*10) + "%";
    Escena->Mate = TrackBarMateCook->Position / 10.0;
}
//---------------------------------------------------------------------------


void __fastcall TCanvasForm::CellShading1Click(TObject *Sender)
{
	//----- Actualizar la marca de selección de las opciones de menú

        UncheckModelosIluminacion();
        CellShading1->Checked = true;

        //----- Mostrar los controles de iluminación, y ocultar los
        //----- que no son necesarios para este modo

        UnshowAll();
        GroupBoxIluminacion->Visible = true;
        GroupBoxIluminacion->Top = 0 ;
        GroupBoxPhong->Visible = true ;
        GroupBoxPhong->Top = 224 ;

         //----- Actualizar el modelo de iluminación de la escena
        Escena->CambiarModeloIluminacion (MODELO_CELL_SHADING);
        Escena->Dibujar();
}
//---------------------------------------------------------------------------

void __fastcall TCanvasForm::RayTracing1Click(TObject *Sender)
{
	//----- Actualizar la marca de selección de las opciones de menú

        UncheckModelosIluminacion();
        RayTracing1->Checked = true;

        //----- Mostrar los controles de iluminación, y ocultar los
        //----- que no son necesarios para este modo

        UnshowAll();
        GroupBoxIluminacion->Visible = true;
        GroupBoxIluminacion->Top = 0 ;
        GroupBoxPhong->Visible = true ;
        GroupBoxPhong->Top = 224 ;
        GroupBoxRayTracing->Visible = true ;
        GroupBoxRayTracing->Top = 312 ;

         //----- Actualizar el modelo de iluminación de la escena
        Escena->CambiarModeloIluminacion (MODELO_RAY_TRACING);
        Escena->Dibujar();
}
//---------------------------------------------------------------------------

void __fastcall TCanvasForm::TrackBarProporcionLocalChange(TObject *Sender)
{
    double value = (TrackBarProporcionLocal->Position)/10.0;
    LabelProporcionLocal->Caption = FloatToStr (value*100.0) + "%";
    Escena->ProporcionLocal = value ;
}
//---------------------------------------------------------------------------

void __fastcall TCanvasForm::TrackBarProporcionReflexivaChange(
      TObject *Sender)
{
    double value = (TrackBarProporcionReflexiva->Position)/10.0;
    LabelProporcionReflexiva->Caption = FloatToStr (value*100.0) + "%";
    Escena->ProporcionReflexiva = value ;
}
//---------------------------------------------------------------------------

void __fastcall TCanvasForm::TrackBarProporcionRefractivaChange(
      TObject *Sender)
{
    double value = (TrackBarProporcionRefractiva->Position)/10.0;
    LabelProporcionRefractiva->Caption = FloatToStr (value*100.0) + "%";
    Escena->ProporcionRefractiva = value ;
}
//---------------------------------------------------------------------------

void __fastcall TCanvasForm::TrackBarUmbralChange(TObject *Sender)
{
    double value = (TrackBarUmbral->Position)+1;
    LabelUmbral->Caption = FloatToStr (value) ;
    Escena->UmbralRayTracing = 1 / pow(10,value);
}
//---------------------------------------------------------------------------

