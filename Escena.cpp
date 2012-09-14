//---------------------------------------------------------------------------
//      PRACTICA DE GRAFICOS AVANZADOS Y ANIMACION
//      Curso 04-05
//      Definición de las clases:
//          - T3DPunto
//          - TVertice
// 		- TTransformacion
// 		- TPoligono
// 		- TFigura
//              - TPrisma
// 		- TEsfera
//              - TCilindro
//              - TCono
//              - TToro
//              - THMap
//          - TLuz
//          - TEscena
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include <stdlib.h>
#include <vcl\vcl.h>
#pragma hdrstop

#include "Escena.h"
//---------------------------------------------------------------------------

//===========================================================================
//	CLASE T3DPunto: Punto geométrico 3D. Se utiliza también para representar
//	otros elementos formados por 3 reales: vectores u color RGB
//===========================================================================

//---------------------------------------------------------------------------
//	Constructor vacío
//---------------------------------------------------------------------------

T3DPunto :: T3DPunto ()
{
        X = 0.0;
        Y = 0.0;
        Z = 0.0;
}

//---------------------------------------------------------------------------
//	Constructor de copia
//---------------------------------------------------------------------------

T3DPunto :: T3DPunto (T3DPunto& P)
{
        X = P.X;
        Y = P.Y;
        Z = P.Z;
}

//---------------------------------------------------------------------------
//	Constructor a partir de tres reales
//---------------------------------------------------------------------------

T3DPunto :: T3DPunto (double x, double y, double z)
{
        X = x;
        Y = y;
        Z = z;
}

//---------------------------------------------------------------------------
//	FUNCION Modulo: tiene sentido cuando representa un vector. Calcula
//	el módulo del vector
//---------------------------------------------------------------------------

double
T3DPunto :: Modulo ()
{
        return (sqrt (X*X + Y*Y + Z*Z));
}

//---------------------------------------------------------------------------
//	FUNCION Normalizar: tiene sentido cuando representa un vector. Divide por
//	el módulo para normalizar
//---------------------------------------------------------------------------

void
T3DPunto :: Normalizar ()
{
        double modulo = Modulo ();

        //----- Divide sólo si el módulo es distinto de 0

        if (modulo != 0.0)
        {
                X = X/modulo;
                Y = Y/modulo;
                Z = Z/modulo;
        }
}

//===========================================================================
//	CLASE TVertice: Vértice de un polígono. Incluye el punto y su normal
//===========================================================================

//---------------------------------------------------------------------------
//	Constructor vacío
//---------------------------------------------------------------------------

TVertice :: TVertice () : T3DPunto()
{
        N.X = 0.0;
        N.Y = 0.0;
        N.Z = 0.0;
}

//---------------------------------------------------------------------------
//	Constructor a partir de un punto
//---------------------------------------------------------------------------

TVertice :: TVertice (T3DPunto P) : T3DPunto(P)
{
        N.X = 0.0;
        N.Y = 0.0;
        N.Z = 0.0;
}

//---------------------------------------------------------------------------
//	Constructor a partir de dos puntos: el punto y su normal
//---------------------------------------------------------------------------

TVertice :: TVertice (T3DPunto P, T3DPunto n) : T3DPunto(P)
{
        N.X = n.X;
        N.Y = n.Y;
        N.Z = n.Z;
}

//---------------------------------------------------------------------------
//	Constructor de copia
//---------------------------------------------------------------------------

TVertice :: TVertice (TVertice& V) : T3DPunto()
{
        X = V.X;
        Y = V.Y;
        Z = V.Z;

        N.X = V.N.X;
        N.Y = V.N.Y;
        N.Z = V.N.Z;
}

//---------------------------------------------------------------------------
//	Constructor a partir de tres reales
//---------------------------------------------------------------------------

TVertice :: TVertice (double x, double y, double z) : T3DPunto (x, y, z)
{
        N.X = 0.0;
        N.Y = 0.0;
        N.Z = 0.0;
}

//---------------------------------------------------------------------------
//	Constructor a partir de seis reales
//---------------------------------------------------------------------------

TVertice :: TVertice (double x, double y, double z, double nx, double ny, double nz) : T3DPunto (x, y, z)
{
        N.X = nx;
        N.Y = ny;
        N.Z = nz;
}

//===========================================================================
//	CLASE TTransformacion: Transformación geométrica
//===========================================================================

//---------------------------------------------------------------------------
//	Constructor vacío
//---------------------------------------------------------------------------

TTransformacion :: TTransformacion ()
{
	//----- La matriz por defecto es la identidad

	Identidad();
        TamX = 0;
        TamY = 0;
}

//---------------------------------------------------------------------------
//	Constructor a partir del tamaño de la ventana
//---------------------------------------------------------------------------

TTransformacion :: TTransformacion (int tamX, int tamY)
{
	//----- La matriz por defecto es la identidad

	Identidad();
        TamX = tamX;
        TamY = tamY;
}

//---------------------------------------------------------------------------
//	FUNCION Aplicar: Aplicar la matriz a un vértice. Devuelve el vértice
//      transformado (el punto y su normal)
//---------------------------------------------------------------------------

TVertice
TTransformacion :: Aplicar (TVertice P)
{
        //----- Al ser la normal un vector, hay que transformar origen y
        //----- destino del vector

        T3DPunto Orig = ProductoVector(T3DPunto(0.0, 0.0, 0.0));
        T3DPunto Norm = ProductoVector(P.N);

        //----- El punto transformado es el resultado de multiplicar el punto
        //----- por la matriz y transformar adecuadamente su normal

        return (TVertice(ProductoVector(P), T3DPunto (Norm.X-Orig.X, Norm.Y-Orig.Y, Norm.Z-Orig.Z)));
}

//---------------------------------------------------------------------------
//	FUNCION Aplicar: Aplicar la matriz a un punto. Igual que antes, pero
//      no es necesario transformar la normal
//---------------------------------------------------------------------------

T3DPunto
TTransformacion :: Aplicar (T3DPunto P)
{
        return (ProductoVector(P));
}

//---------------------------------------------------------------------------
//	FUNCION AlRaster: Lleva un punto al raster, aplicando la transformación
//      y transformando además en coordenadas discretas del raster
//---------------------------------------------------------------------------

TVertice
TTransformacion :: AlRaster (TVertice P)
{
        //----- Transformar el vértice

        TVertice PTransf = Aplicar (P);

        //----- Aplicar las transformaciones adecuadas para que el origen
        //----- se encuentre en el centro del canvas y el eje Y apunte hacia arriba

        PTransf.X += TamX/2;
        PTransf.Y += TamY/2;
        PTransf.Y *= -1;
        PTransf.Y += TamY;

        return (PTransf);
}


TVertice
TTransformacion :: InvAlRaster (TVertice P)
{
        //----- Transformar el vértice
        P.X -= TamX/2;
        P.Y -= TamY;
        P.Y *= -1 ;
        P.Y -= TamY/2;


        TVertice PTransf = Aplicar (P);

        return (PTransf);
}

//---------------------------------------------------------------------------
//	FUNCION Trasladar: Multiplica por una matriz de traslación
//---------------------------------------------------------------------------

void
TTransformacion :: Trasladar (T3DPunto Punto)
{
	Matriz[0][0] += Matriz [3][0] * Punto.X;
	Matriz[0][1] += Matriz [3][1] * Punto.X;
	Matriz[0][2] += Matriz [3][2] * Punto.X;
	Matriz[0][3] += Matriz [3][3] * Punto.X;
	Matriz[1][0] += Matriz [3][0] * Punto.Y;
	Matriz[1][1] += Matriz [3][1] * Punto.Y;
	Matriz[1][2] += Matriz [3][2] * Punto.Y;
	Matriz[1][3] += Matriz [3][3] * Punto.Y;
   	Matriz[2][0] += Matriz [3][0] * Punto.Z;
	Matriz[2][1] += Matriz [3][1] * Punto.Z;
	Matriz[2][2] += Matriz [3][2] * Punto.Z;
	Matriz[2][3] += Matriz [3][3] * Punto.Z;
}

//---------------------------------------------------------------------------
//	FUNCION RotarX: Multiplica por una matriz de rotación alrededor del eje X
//---------------------------------------------------------------------------

void
TTransformacion :: RotarX (double Angulo)
{
        double M10 = Matriz[1][0];
        double M11 = Matriz[1][1];
        double M12 = Matriz[1][2];
        double M13 = Matriz[1][3];
        double M20 = Matriz[2][0];
        double M21 = Matriz[2][1];
        double M22 = Matriz[2][2];
        double M23 = Matriz[2][3];
	Matriz[1][0] = M10 * cos (Angulo) - M20 * sin (Angulo);
	Matriz[1][1] = M11 * cos (Angulo) - M21 * sin (Angulo);
	Matriz[1][2] = M12 * cos (Angulo) - M22 * sin (Angulo);
	Matriz[1][3] = M13 * cos (Angulo) - M23 * sin (Angulo);
   	Matriz[2][0] = M10 * sin (Angulo) + M20 * cos (Angulo);
	Matriz[2][1] = M11 * sin (Angulo) + M21 * cos (Angulo);
	Matriz[2][2] = M12 * sin (Angulo) + M22 * cos (Angulo);
	Matriz[2][3] = M13 * sin (Angulo) + M23 * cos (Angulo);
}

//---------------------------------------------------------------------------
//	FUNCION RotarY: Multiplica por una matriz de rotación alrededor del eje Y
//---------------------------------------------------------------------------

void
TTransformacion :: RotarY (double Angulo)
{
        double M00 = Matriz[0][0];
        double M01 = Matriz[0][1];
        double M02 = Matriz[0][2];
        double M03 = Matriz[0][3];
        double M20 = Matriz[2][0];
        double M21 = Matriz[2][1];
        double M22 = Matriz[2][2];
        double M23 = Matriz[2][3];
	Matriz[0][0] = M00 * cos (Angulo) + M20 * sin (Angulo);
	Matriz[0][1] = M01 * cos (Angulo) + M21 * sin (Angulo);
	Matriz[0][2] = M02 * cos (Angulo) + M22 * sin (Angulo);
	Matriz[0][3] = M03 * cos (Angulo) + M23 * sin (Angulo);
   	Matriz[2][0] = - M00 * sin (Angulo) + M20 * cos (Angulo);
	Matriz[2][1] = - M01 * sin (Angulo) + M21 * cos (Angulo);
	Matriz[2][2] = - M02 * sin (Angulo) + M22 * cos (Angulo);
	Matriz[2][3] = - M03 * sin (Angulo) + M23 * cos (Angulo);
}

//---------------------------------------------------------------------------
//	FUNCION RotarZ: Multiplica por una matriz de rotación alrededor del eje Z
//---------------------------------------------------------------------------

void
TTransformacion :: RotarZ (double Angulo)
{
        double M00 = Matriz[0][0];
        double M01 = Matriz[0][1];
        double M02 = Matriz[0][2];
        double M03 = Matriz[0][3];
        double M10 = Matriz[1][0];
        double M11 = Matriz[1][1];
        double M12 = Matriz[1][2];
        double M13 = Matriz[1][3];
	Matriz[0][0] = M00 * cos (Angulo) - M10 * sin (Angulo);
	Matriz[0][1] = M01 * cos (Angulo) - M11 * sin (Angulo);
	Matriz[0][2] = M02 * cos (Angulo) - M12 * sin (Angulo);
	Matriz[0][3] = M03 * cos (Angulo) - M13 * sin (Angulo);
   	Matriz[1][0] = M00 * sin (Angulo) + M10 * cos (Angulo);
	Matriz[1][1] = M01 * sin (Angulo) + M11 * cos (Angulo);
	Matriz[1][2] = M02 * sin (Angulo) + M12 * cos (Angulo);
	Matriz[1][3] = M03 * sin (Angulo) + M13 * cos (Angulo);
}

//---------------------------------------------------------------------------
//	FUNCION Escalar: Multiplica por una matriz de escalado
//---------------------------------------------------------------------------

void
TTransformacion :: Escalar (T3DPunto Punto)
{
	Matriz[0][0] *= Punto.X;
	Matriz[0][1] *= Punto.X;
	Matriz[0][2] *= Punto.X;
	Matriz[0][3] *= Punto.X;
	Matriz[1][0] *= Punto.Y;
	Matriz[1][1] *= Punto.Y;
	Matriz[1][2] *= Punto.Y;
	Matriz[1][3] *= Punto.Y;
   	Matriz[2][0] *= Punto.Z;
	Matriz[2][1] *= Punto.Z;
	Matriz[2][2] *= Punto.Z;
	Matriz[2][3] *= Punto.Z;
}

//---------------------------------------------------------------------------
//	FUNCION Identidad: pone en la matriz la identidad
//---------------------------------------------------------------------------

void
TTransformacion :: Identidad ()
{
	Matriz[0][0] = 1.0;
	Matriz[0][1] = 0.0;
	Matriz[0][2] = 0.0;
	Matriz[0][3] = 0.0;
	Matriz[1][0] = 0.0;
	Matriz[1][1] = 1.0;
	Matriz[1][2] = 0.0;
	Matriz[1][3] = 0.0;
   	Matriz[2][0] = 0.0;
	Matriz[2][1] = 0.0;
	Matriz[2][2] = 1.0;
	Matriz[2][3] = 0.0;
	Matriz[3][0] = 0.0;
	Matriz[3][1] = 0.0;
	Matriz[3][2] = 0.0;
	Matriz[3][3] = 1.0;
}

//---------------------------------------------------------------------------
//	FUNCION ProductoMatriz: Premultiplica la matriz por otra (Matriz*M)
//---------------------------------------------------------------------------

void
TTransformacion :: ProductoMatriz (TTransformacion M)
{
        double MAux[4][4];

        for (int f=0; f<4; f++)
                for (int c=0; c<4; c++)
                        MAux[f][c] = Matriz[f][c];

        for (int f=0; f<4; f++)
                for (int c=0; c<4; c++)
                {
                        Matriz[f][c] = 0.0;
                        for (int i=0; i<4; i++)
                                Matriz[f][c] += M.Matriz[f][i]*MAux[i][c];
                }
}

//---------------------------------------------------------------------------
//	FUNCION ProductoVector: Premultiplica la matriz por un vector (punto) (Matriz*P)
//---------------------------------------------------------------------------

T3DPunto
TTransformacion :: ProductoVector (T3DPunto P)
{
       //----- Transforma el punto en coordenadas homogéneas

        double p[4];
        double q[4];

        p[0] = P.X;
        p[1] = P.Y;
        p[2] = P.Z;
        p[3] = 1;

        //----- Multiplica la matriz por el punto

        for (int f=0; f<4; f++)
        {
                q[f]=0;
                for (int c=0; c<4; c++)
                        q[f] += p[c]*Matriz[f][c];
        }

        //----- Divide por la última coordenada porque está en coordenadas
        //----- homogéneas (esta última coordenada será 1 generalmente

        return (T3DPunto(q[0]/q[3], q[1]/q[3], q[2]/q[3]));
}

void
TTransformacion :: Invertir()
{
    double m00 = Matriz[0][0];
    double m01 = Matriz[0][1];
    double m02 = Matriz[0][2];
    double m03 = Matriz[0][3];
    double m10 = Matriz[1][0];
    double m11 = Matriz[1][1];
    double m12 = Matriz[1][2];
    double m13 = Matriz[1][3];
    double m20 = Matriz[2][0];
    double m21 = Matriz[2][1];
    double m22 = Matriz[2][2];
    double m23 = Matriz[2][3];
    double m30 = Matriz[3][0];
    double m31 = Matriz[3][1];
    double m32 = Matriz[3][2];
    double m33 = Matriz[3][3];
    float det;

    // Asumiendo que se la ultima fila es [0 0 0 1]
    det = m00*m11*m22 + m01*m12*m20 + m02*m10*m21 -
          m02*m11*m20 - m01*m10*m22 - m00*m12*m21 ;

    Matriz[0][0] =  (m11*m22-m12*m21)/det;
    Matriz[1][0] = -(m10*m22-m12*m20)/det;
    Matriz[2][0] =  (m10*m21-m11*m20)/det;
    Matriz[3][0] = 0 ;

    Matriz[0][1] = -(m01*m22-m02*m21)/det;
    Matriz[1][1] =  (m00*m22-m02*m20)/det;
    Matriz[2][1] = -(m00*m21-m01*m20)/det;
    Matriz[3][1] = 0 ;

    Matriz[0][2] =  (m01*m12-m02*m11)/det;
    Matriz[1][2] = -(m00*m12-m02*m10)/det;
    Matriz[2][2] =  (m00*m11-m01*m10)/det;
    Matriz[3][2] = 0 ;

    Matriz[0][3] = -(m01*m12*m23 + m02*m13*m21 + m03*m11*m22 -
                     m03*m12*m21 + m02*m11*m23 + m01*m13*m22)/det;
    Matriz[1][3] = -(m00*m12*m23 + m02*m13*m20 + m03*m10*m22 -
                     m03*m12*m20 + m02*m10*m23 + m00*m13*m22)/det;
    Matriz[2][3] = -(m00*m11*m23 + m01*m13*m20 + m03*m10*m21 -
                     m03*m11*m20 + m01*m10*m23 + m00*m13*m21)/det;
    Matriz[3][3] = 1 ;
}

//===========================================================================
//	CLASE TPoligono: Clase de los Poligonos. Una lista de polígonos forma una figura
//===========================================================================

//---------------------------------------------------------------------------
//	Constructor vacío
//---------------------------------------------------------------------------

TPoligono :: TPoligono ()
{
        ListaVertices = new TList();
}

//---------------------------------------------------------------------------
//	Destructor
//---------------------------------------------------------------------------

TPoligono :: ~TPoligono ()
{
        if (ListaVertices)
        {
                ListaVertices->Clear();
                delete ListaVertices;
        }
        ListaVertices = NULL;
}

//---------------------------------------------------------------------------
//	FUNCION AddVertice: Añadir un vértice al polígono
//---------------------------------------------------------------------------

void
TPoligono :: AddVertice (TVertice *V)
{
        if (ListaVertices)
                ListaVertices->Add (V);
}


//---------------------------------------------------------------------------
//	FUNCION ExtremosY: A partir del polígono, calcula cuáles son los valores
//	mínimo y máximo de Y de todos sus vértices según la transformación actual.
//	Así, a la hora de aplicar el ZBuffer sabemos cuales son las líneas de
//	rastreo que debemos recorrer
//---------------------------------------------------------------------------

void
TPoligono :: ExtremosY (TTransformacion *Transf, double &minY, double &maxY)
{
	//----- Inicializar a infinito y -infinito

        minY = INF;
        maxY = -INF;

        //----- Recorrer todos sus vértices

        TVertice *Vertice, P;
        for (int v=0; v<ListaVertices->Count; v++)
        {
                //----- Aplicar la transformación al punto y actualizar máximo y mínimo

                Vertice = (TVertice *) ListaVertices->Items[v];
                P = Transf->AlRaster (*Vertice);

                if (P.Y < minY)
                        minY = P.Y;
                if (P.Y > maxY)
                        maxY = P.Y;
        }
}

//---------------------------------------------------------------------------
//	FUNCION ExtremosX: A partir del polígono y una línea de rastreo (un valor
//	de la coordenada Y), calcula cuáles son los valores mínimo y máximo de X
//	según la transformación actual. Así, a la hora de aplicar el ZBuffer sabemos
//	dentro de la línea de rastreo Y, qué valores de X debemos recorrer.
//	Aprovecha esta misma función para calcular los valores de la normal en los
//	extremos de la línea de rastreo (necesarios para el sombreado de Phong)
//	y la profundidad Z en el extremo inferior de la línea de rastreo (necesario
//	para el algoritmo del ZBuffer)
//---------------------------------------------------------------------------

void
TPoligono :: ExtremosX (TTransformacion *Transf, double Y, double &minX, double &maxX, T3DPunto &NormalMin, T3DPunto &NormalMax, double &ProfMin)
{
        double minY, maxY;
        double inters, aux1, aux2;
        TVertice *Vertice1, *Vertice2, P1, P2;

        //----- Inicializar a infinito y -infinito

        minX = INF;
        maxX = -INF;

        //----- Recorrer toda la lista de vertices

        for (int v=0; v<ListaVertices->Count; v++)
        {
                //----- Tomar los vértices 2 a 2 para formar las aristas. Obsérvese que
                //----- el polígono es cerrado por eso se supone que es cíclico

                Vertice1 = (TVertice *) ListaVertices->Items[v];
                Vertice2 = (TVertice *) ListaVertices->Items[(v+1)%ListaVertices->Count]; // Se aplica el módulo (%) para hacerlo cíclico

                //----- Transformar los vértices según la transformación actual y calcular su menor y mayor valor de Y

                P1 = Transf->AlRaster (*Vertice1);
                P2 = Transf->AlRaster (*Vertice2);
                minY = P1.Y < P2.Y ? P1.Y : P2.Y;
                maxY = P1.Y > P2.Y ? P1.Y : P2.Y;

                //----- Calcular la intersección entre la línea de rastreo Y y cada arista.
                //----- Sólo existe la intersección si la Y cae entre los valores mayor y menor
                //----- de y de la arista. La variable inters sólo guarda la x de la intersección
                //----- ya que su coordenada y es la variable Y

                if (Y>=minY && Y<=maxY)
                {
                        //----- Si la línea de rastreo coincide con un de los extremos, la intersección está allí
                        if (Y==minY || Y==maxY)
                        {
                                if (Y==P1.Y)
                                        inters = P1.X;
                                else
                                        inters = P2.X;
                        }
                        else
            	                //----- Si no coindice con los extremos, calcular la intersección.
                                //----- Basta con sustituir el valor de Y en la ecuación de la arista

                                inters = ((Y-P1.Y)*(P2.X-P1.X)+P1.X*(P2.Y-P1.Y))/(P2.Y-P1.Y);

                        //----- Utilizar el valor de la intersección para actualizar los valores
                        //----- mínimo y máximo de X. Actualizar también la normal en los extremos.
                        //----- La normal se calcula interpolando la normal en los vértices de la arista,
                        //----- tal y como indica el sombreado de Phong

                        if (inters<minX && P1.Y != P2.Y)
                        {
                                minX = inters;
                                aux1 = (Y-P2.Y)/(P1.Y-P2.Y);
                                aux2 = (P1.Y-Y)/(P1.Y-P2.Y);
                                NormalMin.X = aux1*P1.N.X + aux2*P2.N.X;
                                NormalMin.Y = aux1*P1.N.Y + aux2*P2.N.Y;
                                NormalMin.Z = aux1*P1.N.Z + aux2*P2.N.Z;
                                NormalMin.Normalizar();
                        }
                        if (inters>maxX && P1.Y != P2.Y)
                        {
                                maxX = inters;
                                aux1 = (Y-P2.Y)/(P1.Y-P2.Y);
                                aux2 = (P1.Y-Y)/(P1.Y-P2.Y);
                                NormalMax.X = aux1*P1.N.X + aux2*P2.N.X;
                                NormalMax.Y = aux1*P1.N.Y + aux2*P2.N.Y;
                                NormalMax.Z = aux1*P1.N.Z + aux2*P2.N.Z;
                                NormalMax.Normalizar();
                        }
                }
        }

        //----- Calcular por último la profundidad en el extremo inferior de la línea
        //----- de rastreo. Simplemente hay que sustituir este punto -que es (minX, Y)-
        //----- en la ecuación de la recta y despejar la z. También hay que evitar
        //----- divisiones por 0

        double C = PlanoCoeficienteC (Transf);
        if ( C!= 0.0)
        {
                double A = PlanoCoeficienteA (Transf);
                double B = PlanoCoeficienteB (Transf);
                double D = PlanoCoeficienteD (Transf);

                ProfMin = (-A*minX - B*Y - D)/C;
        }
        else
                ProfMin = 0;
}


//---------------------------------------------------------------------------
//	FUNCION PlanoCoeficienteA: Calcula el coeficiente A de la ecuación
//	del plano (Ax+By+Cz+D=0) a partir de tres puntos contenidos en él y
//      según la transformación
//---------------------------------------------------------------------------

double
TPoligono :: PlanoCoeficienteA (TTransformacion *Transf)
{
        TVertice *V1, *V2, *V3;
        TVertice P1, P2, P3;
        double A = 0.0;

        //----- Sólo puede realizarse si el polígono tiene al menos 3 puntos

        if (ListaVertices->Count >= 3)
        {
                V1 = (TVertice *) ListaVertices->Items[0];
                V2 = (TVertice *) ListaVertices->Items[1];
                V3 = (TVertice *) ListaVertices->Items[2];
                P1 = Transf->AlRaster(*V1);
                P2 = Transf->AlRaster(*V2);
                P3 = Transf->AlRaster(*V3);

                A = (P2.Y - P1.Y)*(P3.Z - P1.Z) - (P2.Z - P1.Z)*(P3.Y - P1.Y);
        }
        return A;
}

//---------------------------------------------------------------------------
//	FUNCION PlanoCoeficienteB: Calcula el coeficiente B de la ecuación
//	del plano (Ax+By+Cz+D=0) a partir de tres puntos contenidos en él y
//      según la transformación
//---------------------------------------------------------------------------

double
TPoligono :: PlanoCoeficienteB (TTransformacion *Transf)
{
        TVertice *V1, *V2, *V3;
        TVertice P1, P2, P3;
        double B = 0.0;

        //----- Sólo puede realizarse si el polígono tiene al menos 3 puntos

        if (ListaVertices->Count >= 3)
        {
                V1 = (TVertice *) ListaVertices->Items[0];
                V2 = (TVertice *) ListaVertices->Items[1];
                V3 = (TVertice *) ListaVertices->Items[2];
                P1 = Transf->AlRaster(*V1);
                P2 = Transf->AlRaster(*V2);
                P3 = Transf->AlRaster(*V3);

                B = (P2.Z - P1.Z)*(P3.X - P1.X) - (P2.X - P1.X)*(P3.Z - P1.Z);
        }
        return B;
}

//---------------------------------------------------------------------------
//	FUNCION PlanoCoeficienteC: Calcula el coeficiente C de la ecuación
//	del plano (Ax+By+Cz+D=0) a partir de tres puntos contenidos en él y
//      según la transformación
//---------------------------------------------------------------------------

double
TPoligono :: PlanoCoeficienteC (TTransformacion *Transf)
{
        TVertice *V1, *V2, *V3;
        TVertice P1, P2, P3;
        double C = 0.0;

        //----- Sólo puede realizarse si el polígono tiene al menos 3 puntos

        if (ListaVertices->Count >= 3)
        {
                V1 = (TVertice *) ListaVertices->Items[0];
                V2 = (TVertice *) ListaVertices->Items[1];
                V3 = (TVertice *) ListaVertices->Items[2];
                P1 = Transf->AlRaster(*V1);
                P2 = Transf->AlRaster(*V2);
                P3 = Transf->AlRaster(*V3);

                C = (P2.X - P1.X)*(P3.Y - P1.Y) - (P2.Y - P1.Y)*(P3.X - P1.X);
        }
        return C;
}

//---------------------------------------------------------------------------
//	FUNCION PlanoCoeficienteD: Calcula el coeficiente D de la ecuación
//	del plano (Ax+By+Cz+D=0) a partir de tres puntos contenidos en él y
//      según la transformación
//---------------------------------------------------------------------------

double
TPoligono :: PlanoCoeficienteD (TTransformacion *Transf)
{
        TVertice *V1, *V2, *V3;
        TVertice P1, P2, P3;
        double A, B, C, D = 0.0;

        //----- Sólo puede realizarse si el polígono tiene al menos 3 puntos

        if (ListaVertices->Count >= 3)
        {
                V1 = (TVertice *) ListaVertices->Items[0];
                V2 = (TVertice *) ListaVertices->Items[1];
                V3 = (TVertice *) ListaVertices->Items[2];
                P1 = Transf->AlRaster(*V1);
                P2 = Transf->AlRaster(*V2);
                P3 = Transf->AlRaster(*V3);

                A = PlanoCoeficienteA(Transf);
                B = PlanoCoeficienteB(Transf);
                C = PlanoCoeficienteC(Transf);
                D = -A*P1.X - B*P1.Y - C*P1.Z;
        }
        return D;
}

//===========================================================================
//	CLASE TFigura: Figura geométrica. Clase padre de las demás figuras. Es una
//	clase virtual.
//===========================================================================

//---------------------------------------------------------------------------
//	Constructor vacío
//---------------------------------------------------------------------------

TFigura :: TFigura ()
{
        ListaPoligonos = new TList();
        ColorAmbiental = T3DPunto (0.5, 0.1, 0.1);
        ColorDifuso = T3DPunto (0.5, 0.1, 0.1);
        ColorEspecular = T3DPunto (0.5, 0.1, 0.1);
}

//---------------------------------------------------------------------------
//	Constructor a partir de las tres componentes del color
//---------------------------------------------------------------------------

TFigura :: TFigura (T3DPunto ca, T3DPunto cd, T3DPunto ce)
{
        ListaPoligonos = new TList();
        ColorAmbiental = ca;
        ColorDifuso = cd;
        ColorEspecular = ce;
}

//---------------------------------------------------------------------------
//	Destructor
//---------------------------------------------------------------------------

TFigura :: ~TFigura ()
{
        if (ListaPoligonos)
        {
    	        ListaPoligonos->Clear();
                delete ListaPoligonos;
        }
        ListaPoligonos = NULL;
}

double
TFigura :: Interseccion(TVertice rayo)
{
    return -1.0;
}

//===========================================================================
//	CLASE TEsfera: Clase de la figura Esfera. Deriva de TFigura
//===========================================================================

//---------------------------------------------------------------------------
//	Constructor vacío
//---------------------------------------------------------------------------

TEsfera :: TEsfera () : TFigura ()
{
        Centro = T3DPunto (0.0, 0.0, 0.0);
        Radio = 100.0;
        Paralelos = 10;
        Meridianos = 10;

        //----- Genera los polígonos asociados a la esfera

        GenerarPoligonos ();
}

//---------------------------------------------------------------------------
//	Constructor a partir del centro, el radio y el número de paralelos y
//	meridianos.
//---------------------------------------------------------------------------

TEsfera :: TEsfera (T3DPunto centro, double radio, int paralelos, int meridianos) : TFigura ()
{
        Centro = centro;
        Radio = radio;
        Paralelos = paralelos;
        Meridianos = meridianos;

        //----- Genera los polígonos asociados a la esfera

        GenerarPoligonos ();
}

//---------------------------------------------------------------------------
//	Destructor
//---------------------------------------------------------------------------

TEsfera :: ~TEsfera ()
{
}

//---------------------------------------------------------------------------
//	FUNCION GenerarPoligonos: genera los poligonos correspondientes a la
//	esfera en función del número de paralelos y de meridianos
//---------------------------------------------------------------------------

void
TEsfera :: GenerarPoligonos (void)
{
        //----- Cada polígono de la esfera está formado por 4 puntos

	TVertice *P1, *P2, *P3, *P4;
        TPoligono *Polig;

        //----- El ángulo Phi recorre los paralelos y el Theta los meridianos.
        //----- Para calcular en cuanto debe incrementarse cada ángulo debemos
        //----- dividir 180º (la mitad de la esfera) entre el número de paralelos
        //----- y 360º (toda la esfera) entre el número de meridianos. Obsérvese
        //----- que los meridianos pasan todos por los polos, mientras que los
        //----- paralelos son parelelos al ecuador

        double incrPhi = M_PI/((double) Paralelos);
        double incrTheta = 2.0*M_PI/((double) Meridianos);

        //----- Recorrer los dos ángulos Phi y Theta

        for (double phi = -M_PI_2; phi<M_PI_2; phi+=incrPhi)
                for (double theta = -M_PI; theta<M_PI; theta+=incrTheta)
                {
                        //----- Calcular los 4 vértices aplicando la ecuación paramétrica de la esfera.
                        //----- Para cada vértice calcular también su normal como el vector que va desde
                        //----- el centro al vértice y normalizarla

                        P1 = new TVertice (Radio*cos(phi)*cos(theta)+Centro.X, Radio*sin(phi)+Centro.Y, Radio*cos(phi)*sin(theta)+Centro.Z);
                        P1->N.X = P1->X - Centro.X;
                        P1->N.Y = P1->Y - Centro.Y;
                        P1->N.Z = P1->Z - Centro.Z;
                        P1->N.Normalizar();

                        P2 = new TVertice (Radio*cos(phi+incrPhi)*cos(theta)+Centro.X, Radio*sin(phi+incrPhi)+Centro.Y, Radio*cos(phi+incrPhi)*sin(theta)+Centro.Z);
                        P2->N.X = P2->X - Centro.X;
                        P2->N.Y = P2->Y - Centro.Y;
                        P2->N.Z = P2->Z - Centro.Z;
                        P2->N.Normalizar();

                        P3 = new TVertice (Radio*cos(phi+incrPhi)*cos(theta+incrTheta)+Centro.X, Radio*sin(phi+incrPhi)+Centro.Y, Radio*cos(phi+incrPhi)*sin(theta+incrTheta)+Centro.Z);
                        P3->N.X = P3->X - Centro.X;
                        P3->N.Y = P3->Y - Centro.Y;
                        P3->N.Z = P3->Z - Centro.Z;
                        P3->N.Normalizar();

                        P4 = new TVertice (Radio*cos(phi)*cos(theta+incrTheta)+Centro.X, Radio*sin(phi)+Centro.Y, Radio*cos(phi)*sin(theta+incrTheta)+Centro.Z);
                        P4->N.X = P4->X - Centro.X;
                        P4->N.Y = P4->Y - Centro.Y;
                        P4->N.Z = P4->Z - Centro.Z;
                        P4->N.Normalizar();

                        //----- Crear el polígono y añadirle los vértices. Obsérvese que los
                        //----- polígonos de los polos solo tienen 3 vértices, por eso si estamos
                        //----- en un polo (Phi es 90º o -90º) hay un vértice que no se añade.

                        Polig = new TPoligono();
                        Polig->AddVertice (P1);
                        Polig->AddVertice (P2);

                        if (phi != M_PI_2)
                                Polig->AddVertice (P3);
                        if (phi != -M_PI_2)
                                Polig->AddVertice (P4);

                        //----- Guardar en la lista de polígonos

                        ListaPoligonos->Add (Polig);
                }
}

double
TEsfera :: Interseccion (TVertice rayo)
{
    double t;
    ResetMinT();

    double x0, y0, z0, dx, dy, dz, r2, A, B, C, disc, cx, cy, cz;
    x0 = rayo.X ;
    y0 = rayo.Y ;
    z0 = rayo.Z ;
    dx = rayo.N.X ;
    dy = rayo.N.Y ;
    dz = rayo.N.Z ;
    r2 = Radio*Radio ;
    cx = Centro.X ;
    cy = Centro.Y ;
    cz = Centro.Z ;

    A = dx*dx + dy*dy + dz*dz ;
    B = 2*x0*dx -2*dx*cx + 2*y0*dy -2*dy*cy +2*z0*dz -2*dz*cz ;
    C = x0*x0 + y0*y0 + z0*z0 -2*x0*cx -2*y0*cy -2*z0*cz + cx*cx + cy*cy + cz*cz - r2;
    disc = B*B -4*A*C ;

    if ( disc < 0.0 )
    {
        // El rayo es externo
        return -1 ;
    }

    // El rayo es secante o tangente. Lo tratamos como si fuera
    // secante, nos da igual calcular 2 veces el mismo punto ya que
    // esto va a suceder muy pocas veces.
    t = ( -B + sqrt(disc) ) / (2*A) ;
    if ( t >= 0.0 && t <= 1.0 )
    {
        TVertice punto(x0+dx*t,y0+dy*t,z0+dz*t);
        punto.N.X = punto.X-cx ;
        punto.N.Y = punto.Y-cy ;
        punto.N.Z = punto.Z-cz ;
        punto.N.Normalizar();
        if (fabs(punto.X-rayo.X) + fabs(punto.Y-rayo.Y) + fabs(punto.Z-rayo.Z) > EPSILON)
        {
            AddT(t, punto);
        }
    }

    t = ( -B - sqrt(disc) ) / (2*A) ;
    if ( t >= 0.0 && t <= 1.0 )
    {
        TVertice punto(x0+dx*t,y0+dy*t,z0+dz*t);
        punto.N.X = punto.X-cx ;
        punto.N.Y = punto.Y-cy ;
        punto.N.Z = punto.Z-cz ;
        punto.N.Normalizar();
        if (fabs(punto.X-rayo.X) + fabs(punto.Y-rayo.Y) + fabs(punto.Z-rayo.Z) > EPSILON)
        {
            AddT(t, punto);
        }
    }

    return GetMinT();
}

void CalcularPatch(int face, double param1, double param2, TPoligono &polig)
{
    if ( face != 1 )
        return;

    TVertice *v;

    v = new TVertice(
        Centro.X + Radio * sin(param2) * cos(param1),
        Centro.Y + Radio * cos(param2),
        Centro.Z + Radio * sin(param2) * sin(param1);

    
}




        virtual double AreaPatch(int face, double param1, double param2);

//===========================================================================
//	CLASE TPrisma: Clase de la figura Prisma. Deriva de TFigura
//===========================================================================

//---------------------------------------------------------------------------
//	Constructor vacío
//---------------------------------------------------------------------------

TPrisma :: TPrisma () : TFigura ()
{
        Centro = T3DPunto (0.0, 0.0, 0.0);
        Ancho = 100.0 ;
        Alto = 100.0 ;
        Profundidad = 100.0 ;

        //----- Genera los polígonos asociados a la prisma

        GenerarPoligonos ();
}

//---------------------------------------------------------------------------
//	Constructor a partir del ancho, alto y profundidad
//---------------------------------------------------------------------------

TPrisma :: TPrisma (T3DPunto centro, double ancho, double alto, double profundidad) : TFigura ()
{
        Centro = centro;
        Ancho = ancho ;
        Alto = alto ;
        Profundidad = profundidad ;

        //----- Genera los polígonos asociados a la esfera

        GenerarPoligonos ();
}

//---------------------------------------------------------------------------
//	Destructor
//---------------------------------------------------------------------------

TPrisma :: ~TPrisma ()
{
}

//---------------------------------------------------------------------------
//	FUNCION GenerarPoligonos: genera los poligonos correspondientes a la
//	prisma
//---------------------------------------------------------------------------

void
TPrisma :: GenerarPoligonos (void)
{
        TVertice *P1, *P2, *P3, *P4 ;
        TPoligono *Polig ;

        // Precalculamos algunos valores recurrentes
        double MAncho = Ancho/2.0 ;
        double MAlto = Alto/2.0 ;
        double MProf = Profundidad/2.0 ;

        // Generamos cada cara por separado, asignando a sus vertices la
        // normal de forma manual.

        // Cara frontal
        P1 = new TVertice(Centro.X-MAncho, Centro.Y-MAlto, Centro.Z-MProf);
        P2 = new TVertice(Centro.X-MAncho, Centro.Y+MAlto, Centro.Z-MProf);
        P3 = new TVertice(Centro.X+MAncho, Centro.Y+MAlto, Centro.Z-MProf);
        P4 = new TVertice(Centro.X+MAncho, Centro.Y-MAlto, Centro.Z-MProf);
        P1->N.X = 0 ; P1->N.Y = 0 ; P1->N.Z = -1 ;
        P2->N = P3->N = P4->N = P1->N ;
        Polig = new TPoligono();
        Polig->AddVertice(P1);
        Polig->AddVertice(P2);
        Polig->AddVertice(P3);
        Polig->AddVertice(P4);
        ListaPoligonos->Add(Polig);

        // Cara posterior
        P1 = new TVertice(Centro.X-MAncho, Centro.Y-MAlto, Centro.Z+MProf);
        P2 = new TVertice(Centro.X-MAncho, Centro.Y+MAlto, Centro.Z+MProf);
        P3 = new TVertice(Centro.X+MAncho, Centro.Y+MAlto, Centro.Z+MProf);
        P4 = new TVertice(Centro.X+MAncho, Centro.Y-MAlto, Centro.Z+MProf);
        P1->N.X = 0 ; P1->N.Y = 0 ; P1->N.Z = 1 ;
        P2->N = P3->N = P4->N = P1->N ;
        Polig = new TPoligono();
        Polig->AddVertice(P1);
        Polig->AddVertice(P2);
        Polig->AddVertice(P3);
        Polig->AddVertice(P4);
        ListaPoligonos->Add(Polig);

        // Cara izquierda
        P1 = new TVertice(Centro.X-MAncho, Centro.Y-MAlto, Centro.Z-MProf);
        P2 = new TVertice(Centro.X-MAncho, Centro.Y+MAlto, Centro.Z-MProf);
        P3 = new TVertice(Centro.X-MAncho, Centro.Y+MAlto, Centro.Z+MProf);
        P4 = new TVertice(Centro.X-MAncho, Centro.Y-MAlto, Centro.Z+MProf);
        P1->N.X = -1 ; P1->N.Y = 0 ; P1->N.Z = 0 ;
        P2->N = P3->N = P4->N = P1->N ;
        Polig = new TPoligono();
        Polig->AddVertice(P1);
        Polig->AddVertice(P2);
        Polig->AddVertice(P3);
        Polig->AddVertice(P4);
        ListaPoligonos->Add(Polig);

        // Cara derecha
        P1 = new TVertice(Centro.X+MAncho, Centro.Y-MAlto, Centro.Z-MProf);
        P2 = new TVertice(Centro.X+MAncho, Centro.Y+MAlto, Centro.Z-MProf);
        P3 = new TVertice(Centro.X+MAncho, Centro.Y+MAlto, Centro.Z+MProf);
        P4 = new TVertice(Centro.X+MAncho, Centro.Y-MAlto, Centro.Z+MProf);
        P1->N.X = 1 ; P1->N.Y = 0 ; P1->N.Z = 0 ;
        P2->N = P3->N = P4->N = P1->N ;
        Polig = new TPoligono();
        Polig->AddVertice(P1);
        Polig->AddVertice(P2);
        Polig->AddVertice(P3);
        Polig->AddVertice(P4);
        ListaPoligonos->Add(Polig);

        // Cara inferior
        P1 = new TVertice(Centro.X-MAncho, Centro.Y-MAlto, Centro.Z-MProf);
        P2 = new TVertice(Centro.X-MAncho, Centro.Y-MAlto, Centro.Z+MProf);
        P3 = new TVertice(Centro.X+MAncho, Centro.Y-MAlto, Centro.Z+MProf);
        P4 = new TVertice(Centro.X+MAncho, Centro.Y-MAlto, Centro.Z-MProf);
        P1->N.X = 0 ; P1->N.Y = -1 ; P1->N.Z = 0 ;
        P2->N = P3->N = P4->N = P1->N ;
        Polig = new TPoligono();
        Polig->AddVertice(P1);
        Polig->AddVertice(P2);
        Polig->AddVertice(P3);
        Polig->AddVertice(P4);
        ListaPoligonos->Add(Polig);

        // Cara superior
        P1 = new TVertice(Centro.X-MAncho, Centro.Y+MAlto, Centro.Z-MProf);
        P2 = new TVertice(Centro.X-MAncho, Centro.Y+MAlto, Centro.Z+MProf);
        P3 = new TVertice(Centro.X+MAncho, Centro.Y+MAlto, Centro.Z+MProf);
        P4 = new TVertice(Centro.X+MAncho, Centro.Y+MAlto, Centro.Z-MProf);
        P1->N.X = 0 ; P1->N.Y = 1 ; P1->N.Z = 0 ;
        P2->N = P3->N = P4->N = P1->N ;
        Polig = new TPoligono();
        Polig->AddVertice(P1);
        Polig->AddVertice(P2);
        Polig->AddVertice(P3);
        Polig->AddVertice(P4);
        ListaPoligonos->Add(Polig);
}

double
TPrisma :: Interseccion (TVertice rayo)
{
    float t;
    float c1, c2;
    ResetMinT();

    if ( rayo.N.X != 0.0 )
    {
        // Cara izquierda
        t = (Centro.X-Ancho/2-rayo.X)/rayo.N.X;
        if ( t >= 0.0 && t <= 1.0 )
        {
            c1 = rayo.Z + rayo.N.Z*t;
            if ( c1 >= Centro.Z-Profundidad/2 && c1 <= Centro.Z+Profundidad/2 )
            {
                c2 = rayo.Y + rayo.N.Y*t;
                if ( c2 >= Centro.Y-Alto/2 && c2 <= Centro.Y+Alto/2 )
                {
                    AddT(t, TVertice(Centro.X-Ancho/2, c2, c1, -1, 0, 0) );
                }
            }
        }

        // Cara derecha
        t = (Centro.X+Ancho/2-rayo.X)/rayo.N.X;
        if ( t >= 0.0 && t <= 1.0 )
        {
            c1 = rayo.Z + rayo.N.Z*t;
            if ( c1 >= Centro.Z-Profundidad/2 && c1 <= Centro.Z+Profundidad/2 )
            {
                c2 = rayo.Y + rayo.N.Y*t;
                if ( c2 >= Centro.Y-Alto/2 && c2 <= Centro.Y+Alto/2 )
                {
                    AddT(t, TVertice(Centro.X+Ancho/2, c2, c1, 1, 0, 0) );
                }
            }
        }
    }

    if (rayo.N.Y != 0.0)
    {
        // Cara inferior
        t = (Centro.Y-Alto/2-rayo.Y)/rayo.N.Y;
        if ( t >= 0.0 && t <= 1.0 )
        {
            c1 = rayo.X + rayo.N.X*t;
            if ( c1 >= Centro.X-Ancho/2 && c1 <= Centro.X+Ancho/2 )
            {
                c2 = rayo.Z + rayo.N.Z*t;
                if ( c2 >= Centro.Z-Profundidad/2 && c2 <= Centro.Z+Profundidad/2 )
                {
                    AddT(t, TVertice(c1, Centro.Y-Alto/2, c2, 0, -1, 0) );
                }
            }
        }

        // Cara superior
        t = (Centro.Y+Alto/2-rayo.Y)/rayo.N.Y;
        if ( t >= 0.0 && t <= 1.0 )
        {
            c1 = rayo.X + rayo.N.X*t;
            if ( c1 >= Centro.X-Ancho/2 && c1 <= Centro.X+Ancho/2 )
            {
                c2 = rayo.Z + rayo.N.Z*t;
                if ( c2 >= Centro.Z-Profundidad/2 && c2 <= Centro.Z+Profundidad/2 )
                {
                    AddT(t, TVertice(c1, Centro.Y+Alto/2, c2, 0, 1, 0) );
                }
            }
        }
    }

    if (rayo.N.Z != 0.0)
    {
        // Cara frontal
        t = (Centro.Z-Profundidad/2-rayo.Z)/rayo.N.Z;
        if ( t >= 0.0 && t <= 1.0 )
        {
            c1 = rayo.X + rayo.N.X*t;
            if ( c1 >= Centro.X-Ancho/2 && c1 <= Centro.X+Ancho/2 )
            {
                c2 = rayo.Y + rayo.N.Y*t;
                if ( c2 >= Centro.Y-Alto/2 && c2 <= Centro.Y+Alto/2 )
                {
                    AddT(t, TVertice(c1, c2, Centro.Z-Profundidad/2, 0, 0, -1) );
                }
            }
        }

        // Cara trasera
        t = (Centro.Z+Profundidad/2-rayo.Z)/rayo.N.Z;
        if ( t >= 0.0 && t <= 1.0 )
        {
            c1 = rayo.X + rayo.N.X*t;
            if ( c1 >= Centro.X-Ancho/2 && c1 <= Centro.X+Ancho/2 )
            {
                c2 = rayo.Y + rayo.N.Y*t;
                if ( c2 >= Centro.Y-Alto/2 && c2 <= Centro.Y+Alto/2 )
                {
                    AddT(t, TVertice(c1, c2, Centro.Z+Profundidad/2, 0, 0, 1) );
                }
            }
        }
    }




    return GetMinT();
}



//===========================================================================
//	CLASE TCilindro: Clase de la figura Cilindro. Deriva de TFigura
//===========================================================================

//---------------------------------------------------------------------------
//	Constructor vacío
//---------------------------------------------------------------------------

TCilindro :: TCilindro () : TFigura ()
{
        Centro = T3DPunto (0.0, 0.0, 0.0);
        Radio = 100.0;
        Altura = 200.0 ;
        Aristas = 10;

        //----- Genera los polígonos asociados al cilindro

        GenerarPoligonos ();
}

//---------------------------------------------------------------------------
//	Constructor a partir del centro, el radio, la altura y el número de aristas.
//---------------------------------------------------------------------------

TCilindro :: TCilindro (T3DPunto centro, double radio, double altura, int aristas) : TFigura ()
{
        Centro = centro;
        Radio = radio;
        Altura = altura;
        Aristas = aristas;

        //----- Genera los polígonos asociados al cilindro

        GenerarPoligonos ();
}

//---------------------------------------------------------------------------
//	Destructor
//---------------------------------------------------------------------------

TCilindro :: ~TCilindro ()
{
}

//---------------------------------------------------------------------------
//	FUNCION GenerarPoligonos: genera los poligonos correspondientes al
//	cilindro en función del número de paralelos y de meridianos
//---------------------------------------------------------------------------

void
TCilindro :: GenerarPoligonos (void)
{
    //----- Cada poligono del lateral del cilindro esta formado por 4 puntos

    TVertice *P1, *P2, *P3, *P4;
    TPoligono *Polig ;

    double incPhi = 2*M_PI/((double) Aristas);

    // La cara curva se genera recorriendo con phi el rango 0..2pi, que nos
    // indica el angulo. Se genera un quad para cada intervalor phi..phi+incphi
    // que va desde una tapa a la otra del cilindro

    // Recorrer Phi
    for (double phi = -M_PI ; phi < M_PI ; phi+=incPhi )
    {
        P1 = new TVertice (Radio*cos(phi)+Centro.X, Centro.Y - Altura/2.0, Radio*sin(phi)+Centro.Z);
        P1->N.X = P1->X - Centro.X;
        P1->N.Y = 0 ;
        P1->N.Z = P1->Z - Centro.Z;
        P1->N.Normalizar();

        P2 = new TVertice (Radio*cos(phi)+Centro.X, Centro.Y + Altura/2.0, Radio*sin(phi)+Centro.Z);
        P2->N.X = P2->X - Centro.X;
        P2->N.Y = 0 ;
        P2->N.Z = P2->Z - Centro.Z;
        P2->N.Normalizar();

        P3 = new TVertice (Radio*cos(phi+incPhi)+Centro.X, Centro.Y + Altura/2.0, Radio*sin(phi+incPhi)+Centro.Z);
        P3->N.X = P3->X - Centro.X;
        P3->N.Y = 0 ;
        P3->N.Z = P3->Z - Centro.Z;
        P3->N.Normalizar();

        P4 = new TVertice (Radio*cos(phi+incPhi)+Centro.X, Centro.Y - Altura/2.0, Radio*sin(phi+incPhi)+Centro.Z);
        P4->N.X = P4->X - Centro.X;
        P4->N.Y = 0 ;
        P4->N.Z = P4->Z - Centro.Z;
        P4->N.Normalizar();

        Polig = new TPoligono();
        Polig->AddVertice (P1);
        Polig->AddVertice (P2);
        Polig->AddVertice (P3);
        Polig->AddVertice (P4);

        //----- Guardar en la lista de poligonos
        ListaPoligonos->Add (Polig);

    }

    // Ahora generamos las tapas
    // Se vuelve a recorrer el ranto 0..2pi pero ahora para generar un unico poligono

    TPoligono *Polig1, *Polig2;
    Polig1 = new TPoligono() ;
    Polig2 = new TPoligono() ;

    for (double phi = -M_PI ; phi < M_PI ; phi+=incPhi )
    {
        P1 = new TVertice (Radio*cos(phi)+Centro.X, Centro.Y - Altura/2.0, Radio*sin(phi)+Centro.Z);
        P1->N.X = 0 ;
        P1->N.Y = -1 ;
        P1->N.Z = 0 ;
        Polig1->AddVertice(P1);

        P2 = new TVertice (Radio*cos(phi)+Centro.X, Centro.Y + Altura/2.0, Radio*sin(phi)+Centro.Z);
        P2->N.X = 0 ;
        P2->N.Y = 1 ;
        P2->N.Z = 0 ;
        Polig2->AddVertice(P2);
    }

    ListaPoligonos->Add(Polig1);
    ListaPoligonos->Add(Polig2);
}


double
TCilindro :: Interseccion (TVertice rayo)
{
    double t;
    double x, y, z;
    ResetMinT();

    double x0, y0, z0, dx, dy, dz, r2, A, B, C, disc, cx, cy, cz;
    x0 = rayo.X ;
    y0 = rayo.Y ;
    z0 = rayo.Z ;
    dx = rayo.N.X ;
    dy = rayo.N.Y ;
    dz = rayo.N.Z ;
    r2 = Radio*Radio ;
    cx = Centro.X ;
    cy = Centro.Y ;
    cz = Centro.Z ;


    if ( rayo.N.Y != 0 )
    {
        t = (Centro.Y-Altura/2-rayo.Y)/rayo.N.Y ;
        x = rayo.X + rayo.N.X*t ;
        y = rayo.Y + rayo.N.Y*t ;
        z = rayo.Z + rayo.N.Z*t ;
        if ( pow(x-Centro.X,2) + pow(z-Centro.Z,2) <= pow(Radio,2) )
        {
            TVertice punto(x,y,z,0,-1,0);
            if (fabs(punto.X-rayo.X) + fabs(punto.Y-rayo.Y) + fabs(punto.Z-rayo.Z) > EPSILON)
            {
                AddT(t, punto);
            }
        }

        t = (Centro.Y+Altura/2-rayo.Y)/rayo.N.Y ;
        x = rayo.X + rayo.N.X*t ;
        y = rayo.Y + rayo.N.Y*t ;
        z = rayo.Z + rayo.N.Z*t ;
        if ( pow(x-Centro.X,2) + pow(z-Centro.Z,2) <= pow(Radio,2) )
        {
            TVertice punto(x,y,z,0,1,0);
            if (fabs(punto.X-rayo.X) + fabs(punto.Y-rayo.Y) + fabs(punto.Z-rayo.Z) > EPSILON)
            {
                AddT(t, punto);
            }
        }
    }

    A = dx*dx + dz*dz ;
    B = 2*dx*(x0-cx) + 2*dz*(z0-cz) ;
    C = x0*x0 + cx*cx - 2*cx*x0 +
        z0*z0 + cz*cz - 2*cz*z0 - r2 ;

    disc = B*B - 4*A*C;
    if ( disc >= 0 )
    {
        t = (-B+sqrt(disc))/(2*A) ;
        x = rayo.X + rayo.N.X*t ;
        y = rayo.Y + rayo.N.Y*t ;
        z = rayo.Z + rayo.N.Z*t ;
        if ( y <= cy+Altura/2 && y >= cy-Altura/2 )
        {
            TVertice punto(x,y,z,x-cx,0,z-cz);
            punto.N.Normalizar();
            if (fabs(punto.X-rayo.X) + fabs(punto.Y-rayo.Y) + fabs(punto.Z-rayo.Z) > EPSILON)
            {
                AddT(t, punto);
            }
        }

        t = (-B-sqrt(disc))/(2*A) ;
        x = rayo.X + rayo.N.X*t ;
        y = rayo.Y + rayo.N.Y*t ;
        z = rayo.Z + rayo.N.Z*t ;
        if ( y <= cy+Altura/2 && y >= cy-Altura/2 )
        {
            TVertice punto(x,y,z,x-cx,0,z-cz);
            punto.N.Normalizar();
            if (fabs(punto.X-rayo.X) + fabs(punto.Y-rayo.Y) + fabs(punto.Z-rayo.Z) > EPSILON)
            {
                AddT(t, punto);
            }
        }
    }

    return GetMinT();
}

//===========================================================================
//	CLASE TCono: Clase de la figura Cono. Deriva de TFigura
//===========================================================================

//---------------------------------------------------------------------------
//	Constructor vacío
//---------------------------------------------------------------------------

TCono :: TCono () : TFigura ()
{
        Centro = T3DPunto (0.0, 0.0, 0.0);
        Radio = 100.0;
        Altura = 200.0 ;
        Paralelos = 10;
        Epsilon = 0.0001 ;

        //----- Genera los polígonos asociados al cilindro

        GenerarPoligonos ();
}

//---------------------------------------------------------------------------
//	Constructor a partir del centro, el radio la altura y el número de paralelos.
//---------------------------------------------------------------------------

TCono :: TCono (T3DPunto centro, double radio, double altura, int paralelos) : TFigura ()
{
        Centro = centro;
        Radio = radio;
        Altura = altura;
        Paralelos = paralelos;
        Epsilon = 0.0001 ;

        //----- Genera los polígonos asociados a la esfera

        GenerarPoligonos ();
}

//---------------------------------------------------------------------------
//	Destructor
//---------------------------------------------------------------------------

TCono :: ~TCono ()
{
}

//---------------------------------------------------------------------------
//	FUNCION GenerarPoligonos: genera los poligonos correspondientes a la
//	cono en función del número de paralelos y de la altura
//---------------------------------------------------------------------------

void
TCono :: GenerarPoligonos (void)
{
    //----- Cada poligono del lateral del cilindro esta formado por 4 puntos

    TVertice *P1, *P2, *P3, *P4;
    TPoligono *Polig ;

    double incPhi = 2*M_PI/((double) Paralelos);

    // La cara curva se genera recorriendo con phi el rango 0..2pi, que nos
    // indica el angulo. Se genera un quad para cada intervalor phi..phi+incphi
    // en la base, y del mismo modo para el extremo superior, solo que formando
    // un circulo de radio infinitesimal (epsilon)

    // Recorrer Phi
    for (double phi = -M_PI ; phi < M_PI ; phi+=incPhi )
    {
        P1 = new TVertice (Radio*cos(phi)+Centro.X, Centro.Y - Altura/2.0, Radio*sin(phi)+Centro.Z);
        P1->N.X = P1->X - Centro.X;
        P1->N.Z = P1->Z - Centro.Z;
        P1->N.Normalizar();
        P1->N.Y = (Radio/Altura) ;
        P1->N.Normalizar();

        P2 = new TVertice (Radio*Epsilon*cos(phi)+Centro.X, Centro.Y + Altura/2.0 - Altura*Epsilon, Radio*Epsilon*sin(phi)+Centro.Z);
        P2->N = P1->N ;


        P4 = new TVertice (Radio*cos(phi+incPhi)+Centro.X, Centro.Y - Altura/2.0, Radio*sin(phi+incPhi)+Centro.Z);
        P4->N.X = P4->X - Centro.X;
        P4->N.Z = P4->Z - Centro.Z;
        P4->N.Normalizar();
        P4->N.Y = (Radio/Altura) ;
        P4->N.Normalizar();

        P3 = new TVertice (Radio*Epsilon*cos(phi+incPhi)+Centro.X, Centro.Y + Altura/2.0 - Altura*Epsilon, Radio*Epsilon*sin(phi+incPhi)+Centro.Z);
        P3->N = P4->N ;



        Polig = new TPoligono();
        Polig->AddVertice (P1);
        Polig->AddVertice (P2);
        Polig->AddVertice (P3);
        Polig->AddVertice (P4);

        //----- Guardar en la lista de poligonos
        ListaPoligonos->Add (Polig);
    }

    // Ahora generamos las tapas

    TPoligono *Polig1 ;
    Polig1 = new TPoligono() ;

    for (double phi = -M_PI ; phi < M_PI ; phi+=incPhi )
    {
        P1 = new TVertice (Radio*cos(phi)+Centro.X, Centro.Y - Altura/2.0, Radio*sin(phi)+Centro.Z);
        P1->N.X = 0 ;
        P1->N.Y = -1 ;
        P1->N.Z = 0 ;
        Polig1->AddVertice(P1);
    }

    ListaPoligonos->Add(Polig1);
}

double
TCono :: Interseccion (TVertice rayo)
{

    double t;
    double x, y, z;
    ResetMinT();

    double x0, y0, z0, dx, dy, dz, r2, A, B, C, disc, cx, cy, cz, D, I;
    x0 = rayo.X ;
    y0 = rayo.Y ;
    z0 = rayo.Z ;
    dx = rayo.N.X ;
    dy = rayo.N.Y ;
    dz = rayo.N.Z ;
    r2 = Radio*Radio ;
    cx = Centro.X ;
    cy = Centro.Y ;
    cz = Centro.Z ;


    if ( rayo.N.Y != 0 )
    {
        t = (Centro.Y-Altura/2-rayo.Y)/rayo.N.Y ;
        x = rayo.X + rayo.N.X*t ;
        y = rayo.Y + rayo.N.Y*t ;
        z = rayo.Z + rayo.N.Z*t ;
        if ( pow(x-Centro.X,2) + pow(z-Centro.Z,2) <= pow(Radio,2) )
        {
            TVertice punto(x,y,z,0,-1,0);
            if (fabs(punto.X-rayo.X) + fabs(punto.Y-rayo.Y) + fabs(punto.Z-rayo.Z) > EPSILON)
            {
                AddT(t, punto);
            }
        }
    }

    I = (Radio*(cy+Altura/2-y0))/Altura ;
    D = - (Radio / Altura) * dy ;

    A = dx*dx + dz*dz - D*D ;
    B = 2*dx*(x0-cx) + 2*dz*(z0-cz) - 2*I*D ;
    C = x0*x0 + cx*cx - 2*cx*x0 +
        z0*z0 + cz*cz - 2*cz*z0 - I*I ;

    disc = B*B - 4*A*C;
    if ( disc >= 0 )
    {
        t = (-B+sqrt(disc))/(2*A) ;
        x = rayo.X + rayo.N.X*t ;
        y = rayo.Y + rayo.N.Y*t ;
        z = rayo.Z + rayo.N.Z*t ;
        if ( y <= cy+Altura/2 && y >= cy-Altura/2 )
        {
            TVertice punto(x,y,z,x-cx,0,z-cz);
            punto.N.Normalizar();
            punto.N.Y = Radio/Altura ;
            punto.N.Normalizar();
            if (fabs(punto.X-rayo.X) + fabs(punto.Y-rayo.Y) + fabs(punto.Z-rayo.Z) > EPSILON)
            {
                AddT(t, punto);
            }
        }

        t = (-B-sqrt(disc))/(2*A) ;
        x = rayo.X + rayo.N.X*t ;
        y = rayo.Y + rayo.N.Y*t ;
        z = rayo.Z + rayo.N.Z*t ;
        if ( y <= cy+Altura/2 && y >= cy-Altura/2 )
        {
            TVertice punto(x,y,z,x-cx,0,z-cz);
            punto.N.Normalizar();
            punto.N.Y = Radio/Altura ;
            punto.N.Normalizar();
            if (fabs(punto.X-rayo.X) + fabs(punto.Y-rayo.Y) + fabs(punto.Z-rayo.Z) > EPSILON)
            {
                AddT(t, punto);
            }
        }
    }

    return GetMinT();
}

//===========================================================================
//	CLASE TToro: Clase de la figura Toro. Deriva de TFigura
//===========================================================================

//---------------------------------------------------------------------------
//	Constructor vacío
//---------------------------------------------------------------------------

TToro :: TToro () : TFigura ()
{
        Centro = T3DPunto (0.0, 0.0, 0.0);
        Radio = 100.0;
        RadioAnillo = 10.0 ;
        Paralelos = 10;
        Anillos = 10 ;

        //----- Genera los polígonos asociados al toro

        GenerarPoligonos ();
}

//---------------------------------------------------------------------------
//	Constructor a partir del centro, el radio, el radio de los anillos,
//      el numero de paralelos y el numero de anillos
//---------------------------------------------------------------------------

TToro :: TToro (T3DPunto centro, double radio, double radioAnillos, int paralelos, int anillos) : TFigura ()
{
        Centro = centro;
        Radio = radio;
        RadioAnillo = radioAnillos ;
        Paralelos = paralelos;
        Anillos = anillos ;

        //----- Genera los polígonos asociados a la toro

        GenerarPoligonos ();
}

//---------------------------------------------------------------------------
//	Destructor
//---------------------------------------------------------------------------

TToro :: ~TToro ()
{
}

//---------------------------------------------------------------------------
//	FUNCION GenerarPoligonos: genera los poligonos correspondientes a la
//	toro
//---------------------------------------------------------------------------

void
TToro :: GenerarPoligonos (void)
{
    TVertice *CentroAnillo1, *CentroAnillo2 ;
    TVertice *P1, *P2, *P3, *P4 ;
    TPoligono *Polig ;

    double incPhi = 2*M_PI/((double) Anillos) ;
    double incTheta = 2*M_PI/((double) Paralelos) ;

    // En primer lugar recorremos el rango 0..2pi para el radio exterior
    // para cada valor se calcula un punto central con phi (CentroAnillo1) y
    // otro (CentroAnillo2) con phi+incPhi.
    // Estos puntos centrales se toman como centro del circulo en el siguiente
    // bucle.

    for ( double phi = 0 ; phi < 2*M_PI ; phi += incPhi )
    {
        // Calculamos en primer lugar el centro del anillo segun phi
        CentroAnillo1 = new TVertice(Radio*cos(phi)+Centro.X, Centro.Y, Radio*sin(phi)+Centro.Y);
        CentroAnillo1->N.X = CentroAnillo1->X - Centro.X ;
        CentroAnillo1->N.Y = CentroAnillo1->Y - Centro.Y ;
        CentroAnillo1->N.Z = CentroAnillo1->Z - Centro.Z ;
        CentroAnillo1->N.Normalizar();

        CentroAnillo2 = new TVertice(Radio*cos(phi+incPhi)+Centro.X, Centro.Y, Radio*sin(phi+incPhi)+Centro.Y);
        CentroAnillo2->N.X = CentroAnillo2->X - Centro.X ;
        CentroAnillo2->N.Y = CentroAnillo2->Y - Centro.Y ;
        CentroAnillo2->N.Z = CentroAnillo2->Z - Centro.Z ;
        CentroAnillo2->N.Normalizar();

        // Se recorre de nuevo el rango 0..2pi pero ahora para los circulos
        // que parten de CentroAnillo1 y 2. De esta forma se obtiene un conjunto
        // de quadas que se ajustan a la forma del toro.

        for ( double theta = 0 ; theta < 2*M_PI ; theta += incTheta )
        {
            // Y ahora calculamos los 4 vertices del quad
            P1 = new TVertice(CentroAnillo1->X + CentroAnillo1->N.X*cos(theta)*RadioAnillo, CentroAnillo1->Y + sin(theta)*RadioAnillo, CentroAnillo1->Z + CentroAnillo1->N.Z*cos(theta)*RadioAnillo);
            P1->N.X = P1->X - CentroAnillo1->X ;
            P1->N.Y = P1->Y - CentroAnillo1->Y ;
            P1->N.Z = P1->Z - CentroAnillo1->Z ;
            P1->N.Normalizar();

            P2 = new TVertice(CentroAnillo1->X + CentroAnillo1->N.X*cos(theta+incTheta)*RadioAnillo, CentroAnillo1->Y + sin(theta+incTheta)*RadioAnillo, CentroAnillo1->Z + CentroAnillo1->N.Z*cos(theta+incTheta)*RadioAnillo);
            P2->N.X = P2->X - CentroAnillo1->X ;
            P2->N.Y = P2->Y - CentroAnillo1->Y ;
            P2->N.Z = P2->Z - CentroAnillo1->Z ;
            P2->N.Normalizar();

            P3 = new TVertice(CentroAnillo2->X + CentroAnillo2->N.X*cos(theta+incTheta)*RadioAnillo, CentroAnillo2->Y + sin(theta+incTheta)*RadioAnillo, CentroAnillo2->Z + CentroAnillo2->N.Z*cos(theta+incTheta)*RadioAnillo);
            P3->N.X = P3->X - CentroAnillo2->X ;
            P3->N.Y = P3->Y - CentroAnillo2->Y ;
            P3->N.Z = P3->Z - CentroAnillo2->Z ;
            P3->N.Normalizar();

            P4 = new TVertice(CentroAnillo2->X + CentroAnillo2->N.X*cos(theta)*RadioAnillo, CentroAnillo2->Y + sin(theta)*RadioAnillo, CentroAnillo2->Z + CentroAnillo2->N.Z*cos(theta)*RadioAnillo);
            P4->N.X = P4->X - CentroAnillo2->X ;
            P4->N.Y = P4->Y - CentroAnillo2->Y ;
            P4->N.Z = P4->Z - CentroAnillo2->Z ;
            P4->N.Normalizar();

            Polig = new TPoligono() ;
            Polig->AddVertice(P1);
            Polig->AddVertice(P2);
            Polig->AddVertice(P3);
            Polig->AddVertice(P4);

            ListaPoligonos->Add(Polig);
        }
    }
}

//===========================================================================
//	CLASE THMap: Clase de la figura HMap. Deriva de TFigura
//===========================================================================

//---------------------------------------------------------------------------
//	Constructor vacío
//---------------------------------------------------------------------------

THMap :: THMap () : TFigura ()
{
        Centro = T3DPunto (0.0, 0.0, 0.0);
        Escala = 1.0 ;
        Altura = 100.0 ;
        Fichero = "";

        //----- Genera los polígonos asociados al HMap

        GenerarPoligonos ();
}

//---------------------------------------------------------------------------
//	Constructor a partir de la escala, altura y nombre dle fichero
//---------------------------------------------------------------------------

THMap :: THMap (T3DPunto centro, double escala, double altura, AnsiString fichero) : TFigura ()
{
        Centro = centro;
        Escala = escala;
        Altura = altura;
        Fichero = fichero;

        //----- Genera los polígonos asociados a la HMap

        GenerarPoligonos ();
}

//---------------------------------------------------------------------------
//	Destructor
//---------------------------------------------------------------------------

THMap :: ~THMap ()
{
}

//---------------------------------------------------------------------------
//	FUNCION GenerarPoligonos: genera los poligonos correspondientes a la
//	HMap
//---------------------------------------------------------------------------
void
THMap :: GenerarPoligonos (void)
{
        Graphics::TBitmap *Bitmap = new Graphics::TBitmap();
        Bitmap->LoadFromFile(Fichero);

        TVertice *P1, *P2, *P3, *P4;
        TPoligono *Polig;

        double MAncho = Bitmap->Width*Escala/2.0 ;
        double MProf = Bitmap->Height*Escala/2.0 ;
        double MAlto = Altura/128 ;

        T3DPunto *normales = new TVertice[Bitmap->Width*Bitmap->Height*2];
        // Primero calculamos las normales de los triangulos
        // Se calculan haciendo el producto vectorial de dos laterales del mismo.
        // Se alamcenan en el array normales
        for ( int x = 0 ; x < Bitmap->Width-1 ; x++ )
        {
                for ( int y = 0 ; y < Bitmap->Height-1 ; y++ )
                {
                        int Gris = (Bitmap->Canvas->Pixels[x][y])&0xFF ;
                        P1 = new TVertice(x*Escala-MAncho, Gris*Altura/256 - MAlto, y*Escala-MProf);

                        Gris = (Bitmap->Canvas->Pixels[x+1][y])&0xFF ;
                        P2 = new TVertice((x+1)*Escala-MAncho, Gris*Altura/256 - MAlto, y*Escala-MProf);

                        Gris = (Bitmap->Canvas->Pixels[x+1][y+1])&0xFF ;
                        P3 = new TVertice((x+1)*Escala-MAncho, Gris*Altura/256 - MAlto, (y+1)*Escala-MProf);

                        Gris = (Bitmap->Canvas->Pixels[x][y+1])&0xFF ;
                        P4 = new TVertice(x*Escala-MAncho, Gris*Altura/256 - MAlto, (y+1)*Escala-MProf);


                        T3DPunto N1;
                        T3DPunto N2;
                        T3DPunto N3;
                        // P3-P1 x P2-P1
                        N1.X = P3->X - P1->X ;
                        N1.Y = P3->Y - P1->Y ;
                        N1.Z = P3->Z - P1->Z ;
                        N2.X = P2->X - P1->X ;
                        N2.Y = P2->Y - P1->Y ;
                        N2.Z = P2->Z - P1->Z ;

                        N3.X = N1.Y*N2.Z - N1.Z*N2.Y ;
                        N3.Y = N1.Z*N2.X - N1.X*N2.Z ;
                        N3.Z = N1.X*N2.Y - N1.Y*N2.X ;
                        N3.Normalizar() ;

                        normales[(x*Bitmap->Width+y)*2+0] = N3 ;

                        // P4-P1 x P3-P1
                        N1.X = P4->X - P1->X ;
                        N1.Y = P4->Y - P1->Y ;
                        N1.Z = P4->Z - P1->Z ;
                        N2.X = P3->X - P1->X ;
                        N2.Y = P3->Y - P1->Y ;
                        N2.Z = P3->Z - P1->Z ;

                        N3.X = N1.Y*N2.Z - N1.Z*N2.Y ;
                        N3.Y = N1.Z*N2.X - N1.X*N2.Z ;
                        N3.Z = N1.X*N2.Y - N1.Y*N2.X ;
                        N3.Normalizar() ;

                        normales[(x*Bitmap->Width+y)*2+1] = N3 ;
                }
        }





        for ( int x = 0 ; x < Bitmap->Width-1 ; x++ )
        {
                for ( int y = 0 ; y < Bitmap->Height-1 ; y++ )
                {
                        // Calculamos las coordenadas de los vertices

                        // Primer triangulo
                        int Gris = (Bitmap->Canvas->Pixels[x][y])&0xFF ;
                        P1 = new TVertice(x*Escala-MAncho, Gris*Altura/256 - MAlto, y*Escala-MProf);

                        Gris = (Bitmap->Canvas->Pixels[x+1][y])&0xFF ;
                        P2 = new TVertice((x+1)*Escala-MAncho, Gris*Altura/256 - MAlto, y*Escala-MProf);

                        Gris = (Bitmap->Canvas->Pixels[x+1][y+1])&0xFF ;
                        P3 = new TVertice((x+1)*Escala-MAncho, Gris*Altura/256 - MAlto, (y+1)*Escala-MProf);

                        Gris = (Bitmap->Canvas->Pixels[x][y+1])&0xFF ;
                        P4 = new TVertice(x*Escala-MAncho, Gris*Altura/256 - MAlto, (y+1)*Escala-MProf);

                        // Calculamos las normales de cada vertice haciendo
                        // un promedio de las normales almacenadas de los triangulos
                        // que son adyacentes a dicho vertice.
                        // Esto está más detallado en la documentación externa.

                        // Calculamos la normal del vertice 1
                        {
                                int tx = x ;
                                int ty = y ;
                                TVertice *TP = P1 ;
                                if (tx>0)
                                {
                                        if ( ty>0 )
                                        {
                                                TP->N.X = normales[((tx-1)*Bitmap->Width+ty-1)*2+0].X ;
                                                TP->N.Y = normales[((tx-1)*Bitmap->Width+ty-1)*2+0].Y ;
                                                TP->N.Z = normales[((tx-1)*Bitmap->Width+ty-1)*2+0].Z ;
                                                TP->N.X += normales[((tx-1)*Bitmap->Width+ty-1)*2+1].X ;
                                                TP->N.Y += normales[((tx-1)*Bitmap->Width+ty-1)*2+1].Y ;
                                                TP->N.Z += normales[((tx-1)*Bitmap->Width+ty-1)*2+1].Z ;
                                        }
                                        if ( ty<Bitmap->Height )
                                        {
                                                TP->N.X += normales[((tx-1)*Bitmap->Width+ty)*2+0].X;
                                                TP->N.Y += normales[((tx-1)*Bitmap->Width+ty)*2+0].Y;
                                                TP->N.Z += normales[((tx-1)*Bitmap->Width+ty)*2+0].Z;
                                                TP->N.X += normales[((tx-1)*Bitmap->Width+ty)*2+0].X;
                                                TP->N.Y += normales[((tx-1)*Bitmap->Width+ty)*2+0].Y;
                                                TP->N.Z += normales[((tx-1)*Bitmap->Width+ty)*2+0].Z;
                                        }
                                }
                                if (tx<Bitmap->Width)
                                {
                                        if (ty>0)
                                        {
                                                TP->N.X += normales[((tx)*Bitmap->Width+ty-1)*2+1].X;
                                                TP->N.Y += normales[((tx)*Bitmap->Width+ty-1)*2+1].Y;
                                                TP->N.Z += normales[((tx)*Bitmap->Width+ty-1)*2+1].Z;
                                                TP->N.X += normales[((tx)*Bitmap->Width+ty-1)*2+1].X;
                                                TP->N.Y += normales[((tx)*Bitmap->Width+ty-1)*2+1].Y;
                                                TP->N.Z += normales[((tx)*Bitmap->Width+ty-1)*2+1].Z;
                                        }
                                        if ( ty<Bitmap->Height )
                                        {
                                                TP->N.X += normales[((tx)*Bitmap->Width+ty)*2+0].X;
                                                TP->N.Y += normales[((tx)*Bitmap->Width+ty)*2+0].Y;
                                                TP->N.Z += normales[((tx)*Bitmap->Width+ty)*2+0].Z;
                                                TP->N.X += normales[((tx)*Bitmap->Width+ty)*2+1].X;
                                                TP->N.Y += normales[((tx)*Bitmap->Width+ty)*2+1].Y;
                                                TP->N.Z += normales[((tx)*Bitmap->Width+ty)*2+1].Z;
                                        }
                                }
                        }

                        // Calculamos la normal del vertice 2
                        {
                                int tx = x+1 ;
                                int ty = y ;
                                TVertice *TP = P2 ;
                                if (tx>0)
                                {
                                        if ( ty>0 )
                                        {
                                                TP->N.X = normales[((tx-1)*Bitmap->Width+ty-1)*2+0].X ;
                                                TP->N.Y = normales[((tx-1)*Bitmap->Width+ty-1)*2+0].Y ;
                                                TP->N.Z = normales[((tx-1)*Bitmap->Width+ty-1)*2+0].Z ;
                                                TP->N.X += normales[((tx-1)*Bitmap->Width+ty-1)*2+1].X ;
                                                TP->N.Y += normales[((tx-1)*Bitmap->Width+ty-1)*2+1].Y ;
                                                TP->N.Z += normales[((tx-1)*Bitmap->Width+ty-1)*2+1].Z ;
                                        }
                                        if ( ty<Bitmap->Height )
                                        {
                                                TP->N.X += normales[((tx-1)*Bitmap->Width+ty)*2+0].X;
                                                TP->N.Y += normales[((tx-1)*Bitmap->Width+ty)*2+0].Y;
                                                TP->N.Z += normales[((tx-1)*Bitmap->Width+ty)*2+0].Z;
                                                TP->N.X += normales[((tx-1)*Bitmap->Width+ty)*2+0].X;
                                                TP->N.Y += normales[((tx-1)*Bitmap->Width+ty)*2+0].Y;
                                                TP->N.Z += normales[((tx-1)*Bitmap->Width+ty)*2+0].Z;
                                        }
                                }
                                if (tx<Bitmap->Width)
                                {
                                        if (ty>0)
                                        {
                                                TP->N.X += normales[((tx)*Bitmap->Width+ty-1)*2+1].X;
                                                TP->N.Y += normales[((tx)*Bitmap->Width+ty-1)*2+1].Y;
                                                TP->N.Z += normales[((tx)*Bitmap->Width+ty-1)*2+1].Z;
                                                TP->N.X += normales[((tx)*Bitmap->Width+ty-1)*2+1].X;
                                                TP->N.Y += normales[((tx)*Bitmap->Width+ty-1)*2+1].Y;
                                                TP->N.Z += normales[((tx)*Bitmap->Width+ty-1)*2+1].Z;
                                        }
                                        if ( ty<Bitmap->Height )
                                        {
                                                TP->N.X += normales[((tx)*Bitmap->Width+ty)*2+0].X;
                                                TP->N.Y += normales[((tx)*Bitmap->Width+ty)*2+0].Y;
                                                TP->N.Z += normales[((tx)*Bitmap->Width+ty)*2+0].Z;
                                                TP->N.X += normales[((tx)*Bitmap->Width+ty)*2+1].X;
                                                TP->N.Y += normales[((tx)*Bitmap->Width+ty)*2+1].Y;
                                                TP->N.Z += normales[((tx)*Bitmap->Width+ty)*2+1].Z;
                                        }
                                }
                        }

                        // Calculamos la normal del vertice 3
                        {
                                int tx = x+1 ;
                                int ty = y+1 ;
                                TVertice *TP = P3 ;
                                if (tx>0)
                                {
                                        if ( ty>0 )
                                        {
                                                TP->N.X = normales[((tx-1)*Bitmap->Width+ty-1)*2+0].X ;
                                                TP->N.Y = normales[((tx-1)*Bitmap->Width+ty-1)*2+0].Y ;
                                                TP->N.Z = normales[((tx-1)*Bitmap->Width+ty-1)*2+0].Z ;
                                                TP->N.X += normales[((tx-1)*Bitmap->Width+ty-1)*2+1].X ;
                                                TP->N.Y += normales[((tx-1)*Bitmap->Width+ty-1)*2+1].Y ;
                                                TP->N.Z += normales[((tx-1)*Bitmap->Width+ty-1)*2+1].Z ;
                                        }
                                        if ( ty<Bitmap->Height )
                                        {
                                                TP->N.X += normales[((tx-1)*Bitmap->Width+ty)*2+0].X;
                                                TP->N.Y += normales[((tx-1)*Bitmap->Width+ty)*2+0].Y;
                                                TP->N.Z += normales[((tx-1)*Bitmap->Width+ty)*2+0].Z;
                                                TP->N.X += normales[((tx-1)*Bitmap->Width+ty)*2+0].X;
                                                TP->N.Y += normales[((tx-1)*Bitmap->Width+ty)*2+0].Y;
                                                TP->N.Z += normales[((tx-1)*Bitmap->Width+ty)*2+0].Z;
                                        }
                                }
                                if (tx<Bitmap->Width)
                                {
                                        if (ty>0)
                                        {
                                                TP->N.X += normales[((tx)*Bitmap->Width+ty-1)*2+1].X;
                                                TP->N.Y += normales[((tx)*Bitmap->Width+ty-1)*2+1].Y;
                                                TP->N.Z += normales[((tx)*Bitmap->Width+ty-1)*2+1].Z;
                                                TP->N.X += normales[((tx)*Bitmap->Width+ty-1)*2+1].X;
                                                TP->N.Y += normales[((tx)*Bitmap->Width+ty-1)*2+1].Y;
                                                TP->N.Z += normales[((tx)*Bitmap->Width+ty-1)*2+1].Z;
                                        }
                                        if ( ty<Bitmap->Height )
                                        {
                                                TP->N.X += normales[((tx)*Bitmap->Width+ty)*2+0].X;
                                                TP->N.Y += normales[((tx)*Bitmap->Width+ty)*2+0].Y;
                                                TP->N.Z += normales[((tx)*Bitmap->Width+ty)*2+0].Z;
                                                TP->N.X += normales[((tx)*Bitmap->Width+ty)*2+1].X;
                                                TP->N.Y += normales[((tx)*Bitmap->Width+ty)*2+1].Y;
                                                TP->N.Z += normales[((tx)*Bitmap->Width+ty)*2+1].Z;
                                        }
                                }
                        }

                        // Calculamos la normal del vertice 4
                        {
                                int tx = x ;
                                int ty = y+1 ;
                                TVertice *TP = P4 ;
                                if (tx>0)
                                {
                                        if ( ty>0 )
                                        {
                                                TP->N.X = normales[((tx-1)*Bitmap->Width+ty-1)*2+0].X ;
                                                TP->N.Y = normales[((tx-1)*Bitmap->Width+ty-1)*2+0].Y ;
                                                TP->N.Z = normales[((tx-1)*Bitmap->Width+ty-1)*2+0].Z ;
                                                TP->N.X += normales[((tx-1)*Bitmap->Width+ty-1)*2+1].X ;
                                                TP->N.Y += normales[((tx-1)*Bitmap->Width+ty-1)*2+1].Y ;
                                                TP->N.Z += normales[((tx-1)*Bitmap->Width+ty-1)*2+1].Z ;
                                        }
                                        if ( ty<Bitmap->Height )
                                        {
                                                TP->N.X += normales[((tx-1)*Bitmap->Width+ty)*2+0].X;
                                                TP->N.Y += normales[((tx-1)*Bitmap->Width+ty)*2+0].Y;
                                                TP->N.Z += normales[((tx-1)*Bitmap->Width+ty)*2+0].Z;
                                                TP->N.X += normales[((tx-1)*Bitmap->Width+ty)*2+0].X;
                                                TP->N.Y += normales[((tx-1)*Bitmap->Width+ty)*2+0].Y;
                                                TP->N.Z += normales[((tx-1)*Bitmap->Width+ty)*2+0].Z;
                                        }
                                }
                                if (tx<Bitmap->Width)
                                {
                                        if (ty>0)
                                        {
                                                TP->N.X += normales[((tx)*Bitmap->Width+ty-1)*2+1].X;
                                                TP->N.Y += normales[((tx)*Bitmap->Width+ty-1)*2+1].Y;
                                                TP->N.Z += normales[((tx)*Bitmap->Width+ty-1)*2+1].Z;
                                                TP->N.X += normales[((tx)*Bitmap->Width+ty-1)*2+1].X;
                                                TP->N.Y += normales[((tx)*Bitmap->Width+ty-1)*2+1].Y;
                                                TP->N.Z += normales[((tx)*Bitmap->Width+ty-1)*2+1].Z;
                                        }
                                        if ( ty<Bitmap->Height )
                                        {
                                                TP->N.X += normales[((tx)*Bitmap->Width+ty)*2+0].X;
                                                TP->N.Y += normales[((tx)*Bitmap->Width+ty)*2+0].Y;
                                                TP->N.Z += normales[((tx)*Bitmap->Width+ty)*2+0].Z;
                                                TP->N.X += normales[((tx)*Bitmap->Width+ty)*2+1].X;
                                                TP->N.Y += normales[((tx)*Bitmap->Width+ty)*2+1].Y;
                                                TP->N.Z += normales[((tx)*Bitmap->Width+ty)*2+1].Z;
                                        }
                                }
                        }

                        Polig = new TPoligono();
                        Polig->AddVertice(P1);
                        Polig->AddVertice(P2);
                        Polig->AddVertice(P3);

                        ListaPoligonos->Add(Polig);

                        Polig = new TPoligono();
                        Polig->AddVertice(P1);
                        Polig->AddVertice(P3);
                        Polig->AddVertice(P4);

                        ListaPoligonos->Add(Polig);
                }
        }

        delete Bitmap ;
}


//===========================================================================
//	CLASE TLuz: Clase que engloba los parámetros de la luz
//===========================================================================

//---------------------------------------------------------------------------
//	Constructor
//---------------------------------------------------------------------------

TLuz :: TLuz ()
{
        //----- La luz por defecto está en la posición (1000, 1000, -1000) y todas
        //----- sus componentes son blancas

        Posicion = T3DPunto (1000, 1000, -1000);
        ColorAmbiental = T3DPunto (1, 1, 1);
        ColorDifuso = T3DPunto (1, 1, 1);
        ColorEspecular = T3DPunto (1, 1, 1);
}

//---------------------------------------------------------------------------
//	Destructor
//---------------------------------------------------------------------------

TLuz :: ~TLuz ()
{
}

//===========================================================================
//	CLASE TEscena: Clase que contiene todos los elementos de la escena
//===========================================================================

//---------------------------------------------------------------------------
//	Constructor
//---------------------------------------------------------------------------

TEscena :: TEscena (int tamX, int tamY, TCanvas *miCanvas)
{
        //----- Crear una lista de figuras vacía

        ListaFiguras = new TList();
        ListaFiguras->Clear();

        //----- El modelo de iluminación por defecto es el de alambre y lo ejes son visibles

        ModeloIluminacion = MODELO_ALAMBRE;
        EjesVisibles = true;

        //----- Asignar el tamaño de la ventana y el canvas

        TamX = tamX;
        TamY = tamY;
        MiCanvas = miCanvas;

        //----- Crear una transformación (inicialmente es la identidad)

        Transformacion = new TTransformacion (TamX, TamY);

        //----- Inicializar los atributos para el manejo del ratón

        Pinchando = false;
        XPrevio = 0;
        YPrevio = 0;

        //----- Crear el buffer de intensidades como un bitmap y asignarle tamaño y color

        IBuffer = new Graphics::TBitmap();
        IBuffer->Width = TamX;
        IBuffer->Height = TamY;
        IBuffer->Canvas->Brush->Color = clDkGray;

        //----- Reserva de memoria para el Zbuffer que es una matriz de dobles
        //----- en la que guardar la profundidad de cada pixel.

        ZBuffer = (double **) malloc (sizeof(double *) * TamX);
                for (int x=0; x<TamX; x++)
                        ZBuffer[x] = (double *) malloc (sizeof(double) * TamY);

        //----- Dibujar la escena (que por el momento estará vacía)

        Dibujar();

        Mate = 1.0 ;
        Refraccion.X = 10.0;
}

//---------------------------------------------------------------------------
//	Destructor
//---------------------------------------------------------------------------

TEscena :: ~TEscena ()
{
        //----- Vaciar la lista de figuras y liberar su memoria

        if (ListaFiguras)
        {
    	        ListaFiguras->Clear();
                delete ListaFiguras;
        }
        ListaFiguras = NULL;

        //------ Liberar la memoria de la transformación

        delete Transformacion;

        //----- Liberar la memoria del IBuffer y del ZBuffer

        delete IBuffer;

        for (int x=0; x<TamX; x++)
                delete ZBuffer[x];

        delete ZBuffer;

}

//---------------------------------------------------------------------------
//      FUNCION CambiarModeloIluminacion: Cambiar el modelo de iluminación
//      de la escena
//---------------------------------------------------------------------------

void
TEscena :: CambiarModeloIluminacion (int Modelo)
{
        ModeloIluminacion = Modelo;
        Dibujar();
}

//---------------------------------------------------------------------------
//      FUNCION AddEsfera: Añadir una esfera a la escena
//---------------------------------------------------------------------------

void
TEscena :: AddEsfera (T3DPunto Centro, double Radio, int Paralelos, int Meridianos, T3DPunto Color)
{
        TEsfera *Esfera = new TEsfera (Centro, Radio, Paralelos, Meridianos);

        Esfera->ColorAmbiental = Color;
        Esfera->ColorDifuso = Color;
        Esfera->ColorEspecular = Color;

        //----- Añadir la esfera creada a la lista de figuras y dibujar la escena

        ListaFiguras->Add (Esfera);
        Dibujar();
}

//---------------------------------------------------------------------------
//      FUNCION AddPrisma: Añadir una prisma a la escena
//---------------------------------------------------------------------------

void
TEscena :: AddPrisma (T3DPunto Centro, double Ancho, double Alto, double Profundidad, T3DPunto Color)
{
        TPrisma *Prisma = new TPrisma (Centro, Ancho, Alto, Profundidad);

        Prisma->ColorAmbiental = Color;
        Prisma->ColorDifuso = Color;
        Prisma->ColorEspecular = Color;

        //----- Añadir la prisma creada a la lista de figuras y dibujar la escena

        ListaFiguras->Add (Prisma);
        Dibujar();
}


//---------------------------------------------------------------------------
//      FUNCION AddCilindro: Añadir un cilindro a la escena
//---------------------------------------------------------------------------

void
TEscena :: AddCilindro (T3DPunto Centro, double Radio, double Altura, int Paralelos, T3DPunto Color)
{
    TCilindro *Cilindro = new TCilindro (Centro, Radio, Altura, Paralelos);

    Cilindro->ColorAmbiental = Color ;
    Cilindro->ColorDifuso = Color ;
    Cilindro->ColorEspecular = Color ;

    // Añadir el cilindro a la lista de figuras y dibujar
    ListaFiguras->Add (Cilindro);
    Dibujar();
}

//---------------------------------------------------------------------------
//      FUNCION AddCono: Añadir un cono a la escena
//---------------------------------------------------------------------------

void
TEscena :: AddCono (T3DPunto Centro, double Radio, double Altura, int Paralelos, T3DPunto Color)
{
    TCono *Cono = new TCono (Centro, Radio, Altura, Paralelos);

    Cono->ColorAmbiental = Color ;
    Cono->ColorDifuso = Color ;
    Cono->ColorEspecular = Color ;

    // Añadir el cono a la lista de figuras y dibujar
    ListaFiguras->Add (Cono);
    Dibujar();
}

//---------------------------------------------------------------------------
//      FUNCION AddToro: Añadir un toro a la escena
//---------------------------------------------------------------------------

void
TEscena :: AddToro (T3DPunto Centro, double Radio, double RadioAnillo, int Paralelos, int Anillos, T3DPunto Color)
{
    TToro *Toro = new TToro (Centro, Radio, RadioAnillo, Paralelos, Anillos);

    Toro->ColorAmbiental = Color ;
    Toro->ColorDifuso = Color ;
    Toro->ColorEspecular = Color ;

    // Añadir el toro a la lista de figuras y dibujar
    ListaFiguras->Add (Toro);
    Dibujar();
}

//---------------------------------------------------------------------------
//      FUNCION AddHMap: Añadir un mapa de alturas a la escena
//---------------------------------------------------------------------------

void
TEscena :: AddHMap (T3DPunto Centro, double Escala, double Altura, AnsiString Fichero, T3DPunto Color)
{
        THMap *HMap = new THMap (Centro, Escala, Altura, Fichero);

        HMap->ColorAmbiental = Color ;
        HMap->ColorDifuso = Color ;
        HMap->ColorEspecular = Color ;

        // Añadir el mapa de alturas a la lista de figuras y dibujar
        ListaFiguras->Add (HMap);
        Dibujar();
}

//---------------------------------------------------------------------------
//      FUNCION Dibujar: Dibujar la escena
//---------------------------------------------------------------------------

void
TEscena :: Dibujar()
{
        //----- Borrar lo que haya en el canvas
        IBuffer->Canvas->FillRect(IBuffer->Canvas->ClipRect);

        //----- Si los ejes están visibles dibujarlos

        if (EjesVisibles)
                DibujarEjes();

        //----- Dependiendo del tipo de visualización dibujamos con alambres,
        //----- o con el ZBuffer (cualquiera de estos métodos
        //----- rellena el Buffer de Intensidades -que es un bitmap-)

        switch (ModeloIluminacion)
        {
        case MODELO_ALAMBRE:
                DibujarAlambre();
                break;
        case MODELO_ALAMBRE_OCULTACION:
                DibujarAlambreOcultacion();
                break;
        case MODELO_PHONG:
        case MODELO_BLINN:
        case MODELO_COOK_TORRANCE:
        case MODELO_CELL_SHADING:
                DibujarZBuffer();
                break;
        case MODELO_RAY_TRACING:
                DibujarRayTracing();
        }
        //----- Volcar el Buffer de Intensidades en el Canvas. No se dibuja
        //----- directamente en el Canvas porque es más lento y produce parpadeos

        MiCanvas->Draw( 0, 0, IBuffer);
}

//---------------------------------------------------------------------------
//      FUNCION RatonPinchar: Maneja el evento "Pinchar"
//---------------------------------------------------------------------------

void
TEscena :: RatonPinchar (int X, int Y)
{
        //----- Guarda la posición del ratón en el momento de pinchar y pone
        //----- el flag Pinchando a verdadero

        XPrevio = X;
        YPrevio = Y;
        Pinchando = true;

        //----- Guardamos el modelo de iluminación actual para recuperarlo después
        //----- y lo ponemos a modo alambre (de esta manera el movimiento es
        //----- más rápido

        ModeloActivo = ModeloIluminacion;
        ModeloIluminacion = MODELO_ALAMBRE;
}

//---------------------------------------------------------------------------
//      FUNCION RatonMover: Maneja el evento "Mover arrastrando"
//---------------------------------------------------------------------------

void
TEscena :: RatonMover (int X, int Y)
{
        //----- Sólo se maneja este evento si se entá pinchando (el el flag es verdadero)

        if (Pinchando)
        {

                //----- Transformamos los movimientos del ratón en X e Y en giros alrededor de
                //----- los ejes Y y X. Multiplicamos por un factor para que el movimiento
                //----- no sea excesivo

                Transformacion->RotarY((X-XPrevio)*-0.01);
                Transformacion->RotarX((Y-YPrevio)*-0.01);

                //----- Actualizar la posición del ratón y  dibujar

                XPrevio = X;
                YPrevio = Y;

                Dibujar();
        }
}

//---------------------------------------------------------------------------
//      FUNCION RatonSoltar: Maneja el evento "Soltar"
//---------------------------------------------------------------------------

void
TEscena :: RatonSoltar (int X, int Y)
{
        //----- Actualizar el flag, recuperar el modelo de iluminación y dibujar

        Pinchando = false;
        ModeloIluminacion = ModeloActivo;
        Dibujar();
}

//---------------------------------------------------------------------------
//      FUNCION DibujarEjes: Dibujar los ejes en color Rojo (eje X), Verde
//      (eje Y) y Azul (eje Z)
//---------------------------------------------------------------------------

void
TEscena :: DibujarEjes()
{
        //----- Transformar el origen y los extremos al raster y dibujar las líneas

        TVertice Origen = Transformacion->AlRaster(T3DPunto(0, 0, 0));
        TVertice ExtremoX = Transformacion->AlRaster(T3DPunto(1000, 0, 0));
        TVertice ExtremoY = Transformacion->AlRaster(T3DPunto(0, 1000, 0));
        TVertice ExtremoZ = Transformacion->AlRaster(T3DPunto(0, 0, 1000));

        IBuffer->Canvas->Pen->Color = clRed;
        IBuffer->Canvas->MoveTo(Origen.X, Origen.Y);
        IBuffer->Canvas->LineTo(ExtremoX.X, ExtremoX.Y);

        IBuffer->Canvas->Pen->Color = clGreen;
        IBuffer->Canvas->MoveTo(Origen.X, Origen.Y);
        IBuffer->Canvas->LineTo(ExtremoY.X, ExtremoY.Y);

        IBuffer->Canvas->Pen->Color = clBlue;
        IBuffer->Canvas->MoveTo(Origen.X, Origen.Y);
        IBuffer->Canvas->LineTo(ExtremoZ.X, ExtremoZ.Y);
}

//---------------------------------------------------------------------------
//      FUNCION DibujarAlambre: Dibujar con alambres. Se llama sólo cuando el
//      modo de visualización es VISUAL_ALAMBRE
//---------------------------------------------------------------------------

void
TEscena :: DibujarAlambre()
{
        //----- Sólo se crean las figuras si la lista contiene alguna


        if (ListaFiguras)
        {
                //----- Recorrer la lista de figuras

                for (int i=0; i<ListaFiguras->Count; i++)
                {
                        //----- Obtener la figura y poner el lápiz a su color (para los alambres
                        //----- utilizamos el color difuso)

                        TFigura *MiFigura = (TFigura *) ListaFiguras->Items[i];
                        IBuffer->Canvas->Pen->Color = ConvertirRGBEnTColor(MiFigura->ColorDifuso);

                        //----- Recorrer la lista de polígonos de la figura

                        for (int j=0; j<MiFigura->ListaPoligonos->Count; j++)
                        {
                                //----- Obtener el polígono y su primer punto, transformarlo y moverse a ese punto

                                TPoligono *MiPoligono = (TPoligono *) MiFigura->ListaPoligonos->Items[j];
                                TVertice *MiVertice = (TVertice *) MiPoligono->ListaVertices->Items[0];
                                TVertice PuntoTransf = Transformacion->AlRaster(*MiVertice);

                                IBuffer->Canvas->MoveTo(PuntoTransf.X, PuntoTransf.Y);

                                //----- Recorrer el resto de puntos, transformalos y dibujar líneas entre ellos

                                for (int k=1; true; k = (k+1)%MiPoligono->ListaVertices->Count)
                                {
                                        MiVertice = (TVertice *) MiPoligono->ListaVertices->Items[k];
                                        PuntoTransf = Transformacion->AlRaster(*MiVertice);

                                        IBuffer->Canvas->LineTo(PuntoTransf.X, PuntoTransf.Y);

                                        if ( k==0 ) break;
                                }
                        }

                }
        }
}

//---------------------------------------------------------------------------
//      FUNCION DibujarZBuffer: Dibujar con el método del Z-Buffer. Se llama
//      cuando el modo de visualización es Ocultación, Phong, Blinn o Cook-Torrance
//---------------------------------------------------------------------------

void
TEscena :: DibujarAlambreOcultacion()
{
    TFigura *MiFigura;
    TPoligono *MiPoligono;
    TVertice Vertice;
    T3DPunto NormalMin, NormalMax;
    T3DPunto ColorPixel;
    double minX = INF, maxX = -INF, minY = INF, maxY = -INF;
    double ProfZ, Constante;
    int lxmin, lxmax, rxmin, rxmax;
    int newlxmin, newlxmax, newrxmin, newrxmax ;
    double sigminX, sigmaxX;
    bool diblx;
    int antminX, antmaxX;
    int actminX, actmaxX;

    if (ListaFiguras)
    {
        for (int x=0; x<TamX; x++)
            for (int y=0; y<TamY; y++)
                ZBuffer[x][y] = INF;

        for (int f=0; f<ListaFiguras->Count; f++)
        {
            MiFigura = (TFigura *) ListaFiguras->Items[f];

            for (int p=0; p<MiFigura->ListaPoligonos->Count; p++)
            {
                MiPoligono = (TPoligono *) MiFigura->ListaPoligonos->Items[p];

                MiPoligono->ExtremosY(Transformacion, minY, maxY);
                double C = MiPoligono->PlanoCoeficienteC(Transformacion);
                if (C != 0.0)
                    Constante = (MiPoligono->PlanoCoeficienteA(Transformacion))/C;
                else
                    Constante = 0 ;

                if (minY < 0)
                    minY = 0;
                if (maxY >= TamY)
                    maxY = TamY-1;

                for (int y=minY; y<=((int)(maxY+1)); y++)
                {
                    //MiPoligono->ExtremosX(Transformacion, y+1, sigminX, sigmaxX, NormalMin, NormalMax, ProfZ);
                    MiPoligono->ExtremosX(Transformacion, y, minX, maxX, NormalMin, NormalMax, ProfZ);

                    /*
                    if (minX < 0)
                    {
                        ProfZ = ProfZ+minX*Constante;
                        minX = 0 ;
                    }

                    if (maxX >= TamX)
                        maxX = TamX-1;
                    */

                    if ( y == ((int)minY))
                    {
                        antminX = minX ;
                        antmaxX = maxX ;

                        lxmin = minX ;
                        lxmax = maxX ;
                        rxmin = minX ;
                        rxmax = maxX ;

                        actminX = minX ;
                        actmaxX = maxX ;
                    }
                    else if ( y > ((int)maxY) )
                    {
                        rxmin = lxmin = antminX+1 ;
                        rxmax = lxmax = antmaxX-1 ;

                        actminX = lxmin ;
                        actmaxX = lxmax ;
                    }
                    else
                    {
                        actminX = minX ;
                        actmaxX = maxX ;

                        if (antminX == actminX)
                        {
                            lxmin = actminX ;
                            lxmax = actminX ;
                        }
                        else
                        {
                            if (antminX < actminX)
                            {
                                lxmin = antminX+1;
                                lxmax = actminX;
                            }
                            else
                            {
                                lxmin = actminX;
                                lxmax = antminX-1;
                            }
                        }

                        if (antmaxX == actmaxX)
                        {
                            rxmin = actmaxX;
                            rxmax = actmaxX;
                        }
                        else
                        {
                            if(antmaxX < actmaxX)
                            {
                                rxmin = antmaxX+1;
                                rxmax = actmaxX;
                            }
                            else
                            {
                                rxmin = actmaxX;
                                rxmax = antmaxX-1;
                            }
                        }

                        antminX = actminX ;
                        antmaxX = actmaxX ;
                    }

                    actminX = minX ;
                    actmaxX = maxX ;

                    if (lxmin < minX)
                        actminX = lxmin ;
                    if (rxmax > maxX)
                        actmaxX = rxmax ;

                    if (actminX < 0 )
                        actminX = 0 ;
                    if (actmaxX >= TamX)
                        actmaxX = TamX-1 ;

                    ProfZ = ProfZ - Constante*(actminX-minX) ;
                    minX = actminX ;
                    maxX = actmaxX ;


                    for (int x=minX; x<=maxX; x++)
                    {
                        if (ProfZ < ZBuffer[x][y] )
                        {
                            ZBuffer[x][y] = ProfZ;

                            if ( (x>=lxmin && x<=lxmax) || (x>=rxmin && x<=rxmax) )//||
//                                y == ((int)maxY) || y == ((int)minY) )
                            {
                                ColorPixel.X = MiFigura->ColorDifuso.X;
                                ColorPixel.Y = MiFigura->ColorDifuso.Y;
                                ColorPixel.Z = MiFigura->ColorDifuso.Z;
                            }
                            else
                            {
                                ColorPixel = ConvertirTColorEnRGB(IBuffer->Canvas->Brush->Color);
                            }
                            IBuffer->Canvas->Pixels[x][y] = ConvertirRGBEnTColor(ColorPixel);
                        }
                        ProfZ -= Constante ;
                    }


                }
            }
        }
    }
}



//---------------------------------------------------------------------------
//      FUNCION DibujarZBuffer: Dibujar con el método del Z-Buffer. Se llama
//      cuando el modo de visualización es Ocultación, Phong, Blinn o Cook-Torrance
//---------------------------------------------------------------------------

void
TEscena :: DibujarZBuffer()
{
   //----- Realizar las acciones sólo si hay figuras en la lista

   if (ListaFiguras)
   {
      TFigura *MiFigura;
      TPoligono *MiPoligono;
      TVertice Vertice;
      T3DPunto NormalMin, NormalMax;
      T3DPunto ColorPixel;
      double minX = INF, maxX = -INF, minY = INF, maxY = -INF;
      double ProfZ, Constante;

      //----- Inicializar el ZBuffer
      for (int x=0; x<TamX; x++)
         for (int y=0; y<TamY; y++)
            ZBuffer[x][y] = INF;

      //----- Recorrer toda la lista de figuras
      for (int f=0; f<ListaFiguras->Count; f++)
	  {
         MiFigura = (TFigura *) ListaFiguras->Items[f];

         //----- Recorrer cada polígono de cada figura. Este bucle implementa
         //----- el método del Z-Buffer y el modelo de iluminación de Phong
	     for (int p=0; p<MiFigura->ListaPoligonos->Count; p++)
         {
            MiPoligono = (TPoligono *) MiFigura->ListaPoligonos->Items[p];

            //----- Calcular entre qué dos valores de y se encuentra el polígono,
            //----- es decir, los valores mínimo y máximo de las lineas de rastreo
            MiPoligono->ExtremosY (Transformacion, minY, maxY);

            //----- Obtener el valor constante que debe sumarse a la profundidad
            //----- para calcularla de forma incremental, según el método del
            //----- Z-Buffer. Este valor depende de los coeficientes A y C de la
            //----- ecuación del plano. También evitamos divisiones por 0.

            double C = MiPoligono->PlanoCoeficienteC(Transformacion);
            if (C != 0.0)
               Constante = (MiPoligono->PlanoCoeficienteA(Transformacion))/C;
            else
               Constante = 0;

            //----- Comprobar que no se accede fuera del rango de la matriz
            if (minY < 0)
               minY = 0;
            if (maxY >= TamY)
               maxY = TamY-1;

            //----- Recorrer cada línea de rastreo
            for (int y=minY; y<=maxY; y++)
            {
               //----- Para cada línea de rastreo, calcular su intersección con
               //----- el poligono (extremos minimo y maximo de esa línea de rastreo).
               //----- Se aprovecha también la función para obtener las normales
               //----- al polígono en los extremos y la profundidad en el extremo mínimo

               MiPoligono->ExtremosX (Transformacion, y, minX, maxX, NormalMin, NormalMax, ProfZ);

               //----- Comprobar que no se accede fuera del rango de la matriz
               if (minX < 0)
               {
                  ProfZ = ProfZ+minX*Constante;
                  minX = 0;
               }
               if (maxX >= TamX)
                  maxX = TamX-1;

               //----- Recorrer cada pixel de la línea de rastreo
               for (int x=minX; x<maxX; x++)
               {
                  //----- Si su profundidad es menor, sustituir el valor en el ZBuffer
                  //----- y actualizar el IBuffer
                  if (ProfZ < ZBuffer[x][y])
                  {
                     ZBuffer[x][y] = ProfZ;

                     //----- Calcula también la normal en ese vértice (que es x, y, ProfZ)
                     //----- según el método incremental del sombreado de Phong. La
                     //----- variable aux se utiliza para evitar divisiones por 0

                     Vertice = TVertice ((double) x, (double) y, ProfZ);
                     double aux = maxX-minX;
                     aux = aux == 0 ? 0.01 : aux;

                     Vertice.N.X = ((maxX-x)/aux)*NormalMin.X + ((x-minX)/aux)*NormalMax.X;
                     Vertice.N.Y = ((maxX-x)/aux)*NormalMin.Y + ((x-minX)/aux)*NormalMax.Y;
                     Vertice.N.Z = ((maxX-x)/aux)*NormalMin.Z + ((x-minX)/aux)*NormalMax.Z;
                     Vertice.N.Normalizar();

                     //----- Calcular el color del pixel según el modelo de Phong
                     switch (ModeloIluminacion)
                     {
                     case MODELO_PHONG:
                        ColorPixel = IluminacionPhong (MiFigura, Vertice);
                        break;
                     case MODELO_BLINN:
                        ColorPixel = IluminacionBlinn (MiFigura, Vertice);
                        break;
                     case MODELO_COOK_TORRANCE:
                        ColorPixel = IluminacionCookTorrance (MiFigura, Vertice);
                        break;
                     case MODELO_CELL_SHADING:
                        ColorPixel = IluminacionCellShading (MiFigura, Vertice);
                        break;
                     }



                     //----- Actualizar el IBuffer, asignándole el color obtenido
                     //----- al pixel. El color RGB hay que convertirlo a la clase TColor
                     IBuffer->Canvas->Pixels[x][y] = ConvertirRGBEnTColor(ColorPixel);
                  }

                  //----- Actualiza la profundidad según el algoritmo del ZBuffer
                  ProfZ = ProfZ-Constante;
               }
            }
         }
      }
   }
}

//---------------------------------------------------------------------------
//      FUNCION DibujarRayTracing: Dibujar con el método de ray-tracing
//          inverso.
//---------------------------------------------------------------------------
void
TEscena :: DibujarRayTracing ()
{
    if (ListaFiguras)
    {
        T3DPunto color;
        TTransformacion inv = *Transformacion;
        inv.Invertir();

        for (int x=0; x<TamX; x++)
        {
            for (int y=0; y<TamY; y++)
            {
                TVertice v;
                v.X = x;
                v.Y = y;
                v.Z = -INF;
                v.N.X = 0;
                v.N.Y = 0;
                v.N.Z = 2*INF;

                v = inv.InvAlRaster(v);
                color = TrazarRayo(v, 1.0,-1);

                if ( color.X < 0.0 )
                {
                    IBuffer->Canvas->Pixels[x][y] = IBuffer->Canvas->Brush->Color ;
                }
                else
                {
                    IBuffer->Canvas->Pixels[x][y] = ConvertirRGBEnTColor(color);
                }
            }
        }
    }
}

T3DPunto
TEscena :: TrazarRayo(TVertice rayo, float peso, int ignorar)
{
    double N1Ref=1.0;
    double N2Ref=1.55;

    if (peso < UmbralRayTracing)
    {
        return T3DPunto(-1,-1,-1);
    }

    float min = 2.0 ;
    int minIndex = -1;
    TVertice minVertice;
    for (int i=0; i < ListaFiguras->Count ; i++ )
    {
        if ( i == ignorar )
            continue;
        float temp = ((TFigura *)ListaFiguras->Items[i])->Interseccion(rayo);
        if ( temp < 0.0 )
            continue;
        if ( temp < min )
        {
            min = temp ;
            minIndex = i ;
            //minVertice = Transformacion->AlRaster(((TFigura *)ListaFiguras->Items[i])->GetMinVertice());
            minVertice = ((TFigura *)ListaFiguras->Items[i])->GetMinVertice();
        }
    }
    if (minIndex != -1)
    {
        T3DPunto colorLocal, colorReflexion, colorRefraccion;
        minVertice.N.Normalizar();

        // Trazamos el rayo de sombra
        T3DPunto PosLuz = Luz.Posicion ;
        TTransformacion InvTrans = *Transformacion;
        InvTrans.Invertir();
        PosLuz = InvTrans.Aplicar(PosLuz);

        TVertice sombra(minVertice.X, minVertice.Y, minVertice.Z,
            PosLuz.X-minVertice.X, PosLuz.Y-minVertice.Y, PosLuz.Z-minVertice.Z);


        bool llegaLuz = TrazarSombra(sombra, minIndex);
        float tempDifusa, tempEspecular;

        if (!llegaLuz)
        {
            tempDifusa = ProporcionDifusa;
            tempEspecular = ProporcionEspecular;
            ProporcionDifusa = ProporcionEspecular = 0.0 ;
        }

        //return T3DPunto(0,1,0);
        colorLocal = IluminacionPhongRayTracing( ((TFigura *)ListaFiguras->Items[minIndex]), minVertice, rayo );

        if (!llegaLuz)
        {
            ProporcionDifusa = tempDifusa ;
            ProporcionEspecular = tempEspecular ;
        }

        // Ahora la reflexion
        TVertice rayoReflexion;
        rayoReflexion = minVertice ;
        rayoReflexion.N.Normalizar();
        rayo.N.Normalizar();

        float cosTheta = rayo.N.X*rayoReflexion.N.X + rayo.N.Y*rayoReflexion.N.Y + rayo.N.Z*rayoReflexion.N.Z ;
        cosTheta = -cosTheta ;
        rayoReflexion.N.X = rayo.N.X + 2*cosTheta*rayoReflexion.N.X ;
        rayoReflexion.N.Y = rayo.N.Y + 2*cosTheta*rayoReflexion.N.Y ;
        rayoReflexion.N.Z = rayo.N.Z + 2*cosTheta*rayoReflexion.N.Z ;
        rayoReflexion = ProlongarRayoLimite(rayoReflexion);

        colorReflexion = TrazarRayo(rayoReflexion, peso*ProporcionReflexiva, minIndex);
        if ( colorReflexion.X < 0.0 )
        {
            colorReflexion = colorLocal ;
        }
        else
        {

            if ( ConvertirRGBEnTColor(colorReflexion) != ConvertirRGBEnTColor(ConvertirTColorEnRGB(IBuffer->Canvas->Brush->Color)))
            {
                TColor temp = ConvertirRGBEnTColor(colorReflexion);
            }
        }

        TVertice rayoRefraccion;
        rayoRefraccion = minVertice ;
        rayoRefraccion.N.Normalizar();

        float N1OverN2 = N1Ref / N2Ref ;
        if ( cosTheta < 0 ) // Cara interna
        {
            N1OverN2 = 1 / N1OverN2 ;
            cosTheta = -cosTheta ;
            rayoRefraccion.N.Escalar(-1);
        }

        float argumento = 1 - pow(N1OverN2,2)*(1-pow(cosTheta,2));
        float cosTheta2 ;
        if (argumento < 0.0)
        {
            // Se produce reflexion total
            colorRefraccion = colorReflexion ;
        }
        else
        {
            float cosTheta2 = sqrt(argumento ) ;
            rayoRefraccion.N.X = N1OverN2*rayo.N.X - (cosTheta2-N1OverN2*cosTheta)*rayoRefraccion.N.X;
            rayoRefraccion.N.Y = N1OverN2*rayo.N.Y - (cosTheta2-N1OverN2*cosTheta)*rayoRefraccion.N.Y;
            rayoRefraccion.N.Z = N1OverN2*rayo.N.Z - (cosTheta2-N1OverN2*cosTheta)*rayoRefraccion.N.Z;
            rayoRefraccion.N.Normalizar();
            rayoRefraccion = ProlongarRayoLimite(rayoRefraccion);

            colorRefraccion = TrazarRayo(rayoRefraccion, peso*ProporcionRefractiva, minIndex);
        }
        if ( colorRefraccion.X < 0.0 )
        {
            colorRefraccion = colorLocal ;
        }

        colorLocal.Escalar(ProporcionLocal);
        colorReflexion.Escalar(ProporcionReflexiva) ;
        colorRefraccion.Escalar(ProporcionRefractiva);
        T3DPunto colorFinal = colorLocal + colorReflexion + colorRefraccion;
        if ( colorFinal.X < 0 ) colorFinal.X = 0 ;
        else if ( colorFinal.X > 1 ) colorFinal.X = 1;
        if ( colorFinal.Y < 0 ) colorFinal.Y = 0 ;
        else if ( colorFinal.Y > 1 ) colorFinal.Y = 1;
        if ( colorFinal.Z < 0 ) colorFinal.Z = 0 ;
        else if ( colorFinal.Z > 1 ) colorFinal.Z = 1;

        return colorFinal ;
    }

    return ConvertirTColorEnRGB(IBuffer->Canvas->Brush->Color);

}

TVertice
TEscena :: ProlongarRayoLimite(TVertice rayo)
{
    float minK = 10*INF ;
    float tempK ;

    if (rayo.N.X != 0.0 )
    {
        tempK = (INF-rayo.X) / rayo.N.X ;
        minK = (tempK > 0.0 && tempK < minK) ? tempK : minK ;

        tempK = (-INF-rayo.X) / rayo.N.X ;
        minK = (tempK > 0.0 && tempK < minK) ? tempK : minK ;
    }

    if (rayo.N.Y != 0.0 )
    {
        tempK = (INF-rayo.Y) / rayo.N.Y ;
        minK = (tempK > 0.0 && tempK < minK) ? tempK : minK ;

        tempK = (-INF-rayo.Y) / rayo.N.Y ;
        minK = (tempK > 0.0 && tempK < minK) ? tempK : minK ;
    }

    if (rayo.N.Z != 0.0 )
    {
        tempK = (INF-rayo.Z) / rayo.N.Z ;
        minK = (tempK > 0.0 && tempK < minK) ? tempK : minK ;

        tempK = (-INF-rayo.Z) / rayo.N.Z ;
        minK = (tempK > 0.0 && tempK < minK) ? tempK : minK ;
    }

    rayo.N.X *= minK ;
    rayo.N.Y *= minK ;
    rayo.N.Z *= minK ;

    return rayo ;
}

bool
TEscena :: TrazarSombra (TVertice rayo, int ignorar)
{
    for (int i=0; i < ListaFiguras->Count ; i++ )
    {
        //if ( i == ignorar )
        //    continue ;
        float temp = ((TFigura *)ListaFiguras->Items[i])->Interseccion(rayo);
        if ( temp < 0.0 )
            continue;
        return false;
    }
    return true;
}

//---------------------------------------------------------------------------
//      FUNCION IluminacionPhongRayTracing: Calcular la iluminación de Phong
//	de un punto dado por el vértice y por el punto de vista
//---------------------------------------------------------------------------

T3DPunto
TEscena :: IluminacionPhongRayTracing (TFigura *Figura, TVertice Vertice, TVertice OrigenVista)
{
        T3DPunto ColorPixel;

        //----- Calcula los vectores L (vector de iluminación), V (vector de vista)
        //----- y H (vector bisector de L-V), a partir de la posición de la luz
        //----- y del punto de vista

        T3DPunto L, V, H;

        T3DPunto PosLuz = Luz.Posicion;
        TTransformacion InvTrans = *Transformacion;
        InvTrans.Invertir();
        PosLuz = InvTrans.Aplicar(PosLuz);
        //T3DPunto PVista = T3DPunto (TamX/2, TamY/2, -1000);

        L.X = PosLuz.X - Vertice.X;
        L.Y = PosLuz.Y - Vertice.Y;
        L.Z = PosLuz.Z - Vertice.Z;
        L.Normalizar();

        V.X = OrigenVista.X - Vertice.X;
        V.Y = OrigenVista.Y - Vertice.Y;
        V.Z = OrigenVista.Z - Vertice.Z;
        V.Normalizar();

        H.X = (L.X + V.X)/2.0;
        H.Y = (L.Y + V.Y)/2.0;
        H.Z = (L.Z + V.Z)/2.0;
        H.Normalizar();

        //----- Productos escalares de L·N y de H·N

        double LporN = L.X*Vertice.N.X + L.Y*Vertice.N.Y + L.Z*Vertice.N.Z;
        double HporN = H.X*Vertice.N.X + H.Y*Vertice.N.Y + H.Z*Vertice.N.Z;

        //----- Iluminación de Phong, con las tres componentes: ambiental, difusa y especular
        //----- Observar que el color de la luz es la iluminación I y el color de la figura
        //----- es el coeficiente k del material. Añadimos además, tres valores para controlar
        //----- la proporción de cada tipo de iluminación

        ColorPixel.X = ProporcionAmbiental * Figura->ColorAmbiental.X * Luz.ColorAmbiental.X + ProporcionDifusa * Figura->ColorDifuso.X * Luz.ColorDifuso.X * LporN + ProporcionEspecular * Figura->ColorEspecular.X * Luz.ColorEspecular.X * pow(HporN, Rugosidad);
        ColorPixel.Y = ProporcionAmbiental * Figura->ColorAmbiental.Y * Luz.ColorAmbiental.Y + ProporcionDifusa * Figura->ColorDifuso.Y * Luz.ColorDifuso.Y * LporN + ProporcionEspecular * Figura->ColorEspecular.Y * Luz.ColorEspecular.Y * pow(HporN, Rugosidad);
        ColorPixel.Z = ProporcionAmbiental * Figura->ColorAmbiental.Z * Luz.ColorAmbiental.Z + ProporcionDifusa * Figura->ColorDifuso.Z * Luz.ColorDifuso.Z * LporN + ProporcionEspecular * Figura->ColorEspecular.Z * Luz.ColorEspecular.Z * pow(HporN, Rugosidad);

        //----- Controlamos que ningún valor de color se salga del rango [0,1]

        T3DPunto MiColor;
        MiColor.X = ColorPixel.X > 1 ? 1 : (ColorPixel.X < 0 ? 0 : ColorPixel.X);
        MiColor.Y = ColorPixel.Y > 1 ? 1 : (ColorPixel.Y < 0 ? 0 : ColorPixel.Y);
        MiColor.Z = ColorPixel.Z > 1 ? 1 : (ColorPixel.Z < 0 ? 0 : ColorPixel.Z);

        return MiColor;
}


//---------------------------------------------------------------------------
//      FUNCION IluminacionPhong: Calcular la iluminación de Phong de un punto
//	dado por el vértice.
//---------------------------------------------------------------------------

T3DPunto
TEscena :: IluminacionPhong (TFigura *Figura, TVertice Vertice)
{
        T3DPunto ColorPixel;

        //----- Calcula los vectores L (vector de iluminación), V (vector de vista)
        //----- y H (vector bisector de L-V), a partir de la posición de la luz
        //----- y del punto de vista

        T3DPunto L, V, H;

        T3DPunto PosLuz = Luz.Posicion;
        T3DPunto PVista = T3DPunto (TamX/2, TamY/2, -1000);

        L.X = PosLuz.X - Vertice.X;
        L.Y = PosLuz.Y - Vertice.Y;
        L.Z = PosLuz.Z - Vertice.Z;
        L.Normalizar();

        V.X = PVista.X - Vertice.X;
        V.Y = PVista.Y - Vertice.Y;
        V.Z = PVista.Z - Vertice.Z;
        V.Normalizar();

        H.X = (L.X + V.X)/2.0;
        H.Y = (L.Y + V.Y)/2.0;
        H.Z = (L.Z + V.Z)/2.0;
        H.Normalizar();

        //----- Productos escalares de L·N y de H·N

        double LporN = L.X*Vertice.N.X + L.Y*Vertice.N.Y + L.Z*Vertice.N.Z;
        double HporN = H.X*Vertice.N.X + H.Y*Vertice.N.Y + H.Z*Vertice.N.Z;

        //----- Iluminación de Phong, con las tres componentes: ambiental, difusa y especular
        //----- Observar que el color de la luz es la iluminación I y el color de la figura
        //----- es el coeficiente k del material. Añadimos además, tres valores para controlar
        //----- la proporción de cada tipo de iluminación

        ColorPixel.X = ProporcionAmbiental * Figura->ColorAmbiental.X * Luz.ColorAmbiental.X + ProporcionDifusa * Figura->ColorDifuso.X * Luz.ColorDifuso.X * LporN + ProporcionEspecular * Figura->ColorEspecular.X * Luz.ColorEspecular.X * pow(HporN, Rugosidad);
        ColorPixel.Y = ProporcionAmbiental * Figura->ColorAmbiental.Y * Luz.ColorAmbiental.Y + ProporcionDifusa * Figura->ColorDifuso.Y * Luz.ColorDifuso.Y * LporN + ProporcionEspecular * Figura->ColorEspecular.Y * Luz.ColorEspecular.Y * pow(HporN, Rugosidad);
        ColorPixel.Z = ProporcionAmbiental * Figura->ColorAmbiental.Z * Luz.ColorAmbiental.Z + ProporcionDifusa * Figura->ColorDifuso.Z * Luz.ColorDifuso.Z * LporN + ProporcionEspecular * Figura->ColorEspecular.Z * Luz.ColorEspecular.Z * pow(HporN, Rugosidad);

        //----- Controlamos que ningún valor de color se salga del rango [0,1]

        T3DPunto MiColor;
        MiColor.X = ColorPixel.X > 1 ? 1 : (ColorPixel.X < 0 ? 0 : ColorPixel.X);
        MiColor.Y = ColorPixel.Y > 1 ? 1 : (ColorPixel.Y < 0 ? 0 : ColorPixel.Y);
        MiColor.Z = ColorPixel.Z > 1 ? 1 : (ColorPixel.Z < 0 ? 0 : ColorPixel.Z);

        return MiColor;
}

//---------------------------------------------------------------------------
//      FUNCION IluminacionCellShading: Calcular la iluminación de Cell Shading de un punto
//	dado por el vértice.
//---------------------------------------------------------------------------

T3DPunto
TEscena :: IluminacionCellShading (TFigura *Figura, TVertice Vertice)
{
        T3DPunto ColorPixel;

        //----- Calcula los vectores L (vector de iluminación), V (vector de vista)
        //----- y H (vector bisector de L-V), a partir de la posición de la luz
        //----- y del punto de vista

        T3DPunto L, V, H, N;

        T3DPunto PosLuz = Luz.Posicion;
        T3DPunto PVista = T3DPunto (TamX/2, TamY/2, -1000);

        N.X = Vertice.N.X;
        N.Y = Vertice.N.Y;
        N.Z = Vertice.N.Z;

        L.X = PosLuz.X - Vertice.X;
        L.Y = PosLuz.Y - Vertice.Y;
        L.Z = PosLuz.Z - Vertice.Z;
        L.Normalizar();

        V.X = PVista.X - Vertice.X;
        V.Y = PVista.Y - Vertice.Y;
        V.Z = PVista.Z - Vertice.Z;
        V.Normalizar();

        V.X = 0 ;
        V.Y = 0 ;
        V.Z = -1 ;

        H.X = (L.X + V.X)/2.0;
        H.Y = (L.Y + V.Y)/2.0;
        H.Z = (L.Z + V.Z)/2.0;
        H.Normalizar();

        //----- Productos escalares de L·N y de H·N

        double LporN = L.X*N.X + L.Y*N.Y + L.Z*N.Z;
        double HporN = H.X*N.X + H.Y*N.Y + H.Z*N.Z;
        double VporN = V.X*N.X + V.Y*N.Y + V.Z*N.Z;

        LporN = ((int)((LporN*5.0)-EPSILON))/4.0;
        if ( LporN == 0.0 ) LporN = 0.25 ;
        if ( VporN < 0.1 ) LporN = 0.00 ;


        //HporN = ((int)((HporN*5.0)+0.499))/5.0;

        //----- Iluminación de Phong, con las tres componentes: ambiental, difusa y especular
        //----- Observar que el color de la luz es la iluminación I y el color de la figura
        //----- es el coeficiente k del material. Añadimos además, tres valores para controlar
        //----- la proporción de cada tipo de iluminación

        double tempRugosidad = Rugosidad != 0.0 ? Rugosidad : 1.0 ;

        ColorPixel.X = ProporcionAmbiental * Figura->ColorAmbiental.X * Luz.ColorAmbiental.X + ProporcionDifusa * Figura->ColorDifuso.X * Luz.ColorDifuso.X * LporN + ProporcionEspecular * Figura->ColorEspecular.X * Luz.ColorEspecular.X * pow(HporN, tempRugosidad);
        ColorPixel.Y = ProporcionAmbiental * Figura->ColorAmbiental.Y * Luz.ColorAmbiental.Y + ProporcionDifusa * Figura->ColorDifuso.Y * Luz.ColorDifuso.Y * LporN + ProporcionEspecular * Figura->ColorEspecular.Y * Luz.ColorEspecular.Y * pow(HporN, tempRugosidad);
        ColorPixel.Z = ProporcionAmbiental * Figura->ColorAmbiental.Z * Luz.ColorAmbiental.Z + ProporcionDifusa * Figura->ColorDifuso.Z * Luz.ColorDifuso.Z * LporN + ProporcionEspecular * Figura->ColorEspecular.Z * Luz.ColorEspecular.Z * pow(HporN, tempRugosidad);

        //----- Controlamos que ningún valor de color se salga del rango [0,1]

        T3DPunto MiColor;
        MiColor.X = ColorPixel.X > 1 ? 1 : (ColorPixel.X < 0 ? 0 : ColorPixel.X);
        MiColor.Y = ColorPixel.Y > 1 ? 1 : (ColorPixel.Y < 0 ? 0 : ColorPixel.Y);
        MiColor.Z = ColorPixel.Z > 1 ? 1 : (ColorPixel.Z < 0 ? 0 : ColorPixel.Z);

        return MiColor;
}


//---------------------------------------------------------------------------
//      FUNCION IluminacionBlinn: Calcular la iluminación de Blinn de un punto
//	dado por el vértice.
//---------------------------------------------------------------------------

T3DPunto
TEscena :: IluminacionBlinn (TFigura *Figura, TVertice Vertice)
{
        T3DPunto ColorPixel;

        //----- Calcula los vectores L (vector de iluminación), V (vector de vista)
        //----- y H (vector bisector de L-V), a partir de la posición de la luz
        //----- y del punto de vista

        T3DPunto L, V, H;
        T3DPunto R, N;
        double d, g, gc , DGdiv;

        T3DPunto PosLuz = Luz.Posicion;
        T3DPunto PVista = T3DPunto (TamX/2, TamY/2, -1000);

        L.X = PosLuz.X - Vertice.X;
        L.Y = PosLuz.Y - Vertice.Y;
        L.Z = PosLuz.Z - Vertice.Z;
        L.Normalizar();

        N.X = Vertice.N.X;
        N.Y = Vertice.N.Y;
        N.Z = Vertice.N.Z;

        R.X = N.X + N.X - L.X ;
        R.Y = N.Y + N.Y - L.Y ;
        R.Z = N.Z + N.Z - L.Z ;
        R.Normalizar();

        V.X = PVista.X - Vertice.X;
        V.Y = PVista.Y - Vertice.Y;
        V.Z = PVista.Z - Vertice.Z;
        V.Normalizar();

        H.X = (L.X + V.X)/2.0;
        H.Y = (L.Y + V.Y)/2.0;
        H.Z = (L.Z + V.Z)/2.0;
        H.Normalizar();

        //----- Productos escalares de L·N y de H·N y de N·V

        double NporL = L.X*N.X + L.Y*N.Y + L.Z*N.Z;
        double NporH = H.X*N.X + H.Y*N.Y + H.Z*N.Z;
        double NporV = N.X*V.X + N.Y*V.Y + N.Z*V.Z;
        double VporH = V.X*H.X + V.Y*H.Y + V.Z*H.Z;
        double LporH = L.X*H.X + L.Y*H.Y + L.Z*H.Z;

        //----- Iluminación de Phong, con las tres componentes: ambiental, difusa y especular
        //----- Observar que el color de la luz es la iluminación I y el color de la figura
        //----- es el coeficiente k del material. Añadimos además, tres valores para controlar
        //----- la proporción de cada tipo de iluminación

        // Componente ambiental
        ColorPixel.X = ProporcionAmbiental * Figura->ColorAmbiental.X * Luz.ColorAmbiental.X ;
        ColorPixel.Y = ProporcionAmbiental * Figura->ColorAmbiental.Y * Luz.ColorAmbiental.Y ;
        ColorPixel.Z = ProporcionAmbiental * Figura->ColorAmbiental.Z * Luz.ColorAmbiental.Z ;

        // Componente difusa
        ColorPixel.X += ProporcionDifusa * Figura->ColorDifuso.X * Luz.ColorDifuso.X * NporL;
        ColorPixel.Y += ProporcionDifusa * Figura->ColorDifuso.Y * Luz.ColorDifuso.Y * NporL;
        ColorPixel.Z += ProporcionDifusa * Figura->ColorDifuso.Z * Luz.ColorDifuso.Z * NporL;

        // Componente especular

        d = pow( (Mate*Mate)/ ( (Mate*Mate -1)*NporH*NporH +1 ) , 2.0) ;

        g = 2*NporH*NporV / VporH ;
        gc = 2*NporH*NporL / VporH ;
        g = g < gc ? g : gc ;
        g = g < 1.0 ? g : 1.0 ;

        DGdiv = d*g/NporV ;

        double Fc = LporH;
        double arg = pow(1.0/Refraccion.X,2.0) + Fc*Fc - 1 ;

        double Fg = arg > 0.0 ? sqrt(arg) : 0.0 ;
        double F = (0.5*pow(Fg-Fc,2)/pow(Fg+Fc,2))*(1+pow(Fc*(Fg+Fc)-1,2)/pow(Fc*(Fg-Fc)+1,2));

        double Blinn = DGdiv*F ;

        ColorPixel.X += ProporcionEspecular * Blinn * Luz.ColorEspecular.X ;
        ColorPixel.Y += ProporcionEspecular * Blinn * Luz.ColorEspecular.Y ;
        ColorPixel.Z += ProporcionEspecular * Blinn * Luz.ColorEspecular.Z ;

        //----- Controlamos que ningún valor de color se salga del rango [0,1]

        T3DPunto MiColor;
        MiColor.X = ColorPixel.X > 1 ? 1 : (ColorPixel.X < 0 ? 0 : ColorPixel.X);
        MiColor.Y = ColorPixel.Y > 1 ? 1 : (ColorPixel.Y < 0 ? 0 : ColorPixel.Y);
        MiColor.Z = ColorPixel.Z > 1 ? 1 : (ColorPixel.Z < 0 ? 0 : ColorPixel.Z);

        return MiColor;
}

//---------------------------------------------------------------------------
//      FUNCION IluminacionCookTorrance: Calcular la iluminación de Cook-Torrance de un punto
//	dado por el vértice.
//---------------------------------------------------------------------------

T3DPunto
TEscena :: IluminacionCookTorrance (TFigura *Figura, TVertice Vertice)
{
        T3DPunto ColorPixel;

        //----- Calcula los vectores L (vector de iluminación), V (vector de vista)
        //----- y H (vector bisector de L-V), a partir de la posición de la luz
        //----- y del punto de vista

        T3DPunto L, V, H;
        T3DPunto R, N;
        double d, g, gc , DGdiv;

        T3DPunto PosLuz = Luz.Posicion;
        T3DPunto PVista = T3DPunto (TamX/2, TamY/2, -1000);

        L.X = PosLuz.X - Vertice.X;
        L.Y = PosLuz.Y - Vertice.Y;
        L.Z = PosLuz.Z - Vertice.Z;
        L.Normalizar();

        N.X = Vertice.N.X;
        N.Y = Vertice.N.Y;
        N.Z = Vertice.N.Z;

        R.X = N.X + N.X - L.X ;
        R.Y = N.Y + N.Y - L.Y ;
        R.Z = N.Z + N.Z - L.Z ;
        R.Normalizar();

        V.X = PVista.X - Vertice.X;
        V.Y = PVista.Y - Vertice.Y;
        V.Z = PVista.Z - Vertice.Z;
        V.Normalizar();

        H.X = (L.X + V.X)/2.0;
        H.Y = (L.Y + V.Y)/2.0;
        H.Z = (L.Z + V.Z)/2.0;
        H.Normalizar();

        //----- Productos escalares de L·N y de H·N y de N·V

        double NporL = L.X*N.X + L.Y*N.Y + L.Z*N.Z;
        double NporH = H.X*N.X + H.Y*N.Y + H.Z*N.Z;
        double NporV = N.X*V.X + N.Y*V.Y + N.Z*V.Z;
        double VporH = V.X*H.X + V.Y*H.Y + V.Z*H.Z;
        double LporH = L.X*H.X + L.Y*H.Y + L.Z*H.Z;

        //----- Iluminación de Phong, con las tres componentes: ambiental, difusa y especular
        //----- Observar que el color de la luz es la iluminación I y el color de la figura
        //----- es el coeficiente k del material. Añadimos además, tres valores para controlar
        //----- la proporción de cada tipo de iluminación

        // Componente ambiental
        ColorPixel.X = ProporcionAmbiental * Figura->ColorAmbiental.X * Luz.ColorAmbiental.X ;
        ColorPixel.Y = ProporcionAmbiental * Figura->ColorAmbiental.Y * Luz.ColorAmbiental.Y ;
        ColorPixel.Z = ProporcionAmbiental * Figura->ColorAmbiental.Z * Luz.ColorAmbiental.Z ;

        // Componente difusa
        ColorPixel.X += ProporcionDifusa * Figura->ColorDifuso.X * Luz.ColorDifuso.X * NporL;
        ColorPixel.Y += ProporcionDifusa * Figura->ColorDifuso.Y * Luz.ColorDifuso.Y * NporL;
        ColorPixel.Z += ProporcionDifusa * Figura->ColorDifuso.Z * Luz.ColorDifuso.Z * NporL;

        // Componente especular

        //d = pow( (Mate*Mate)/ ( (Mate*Mate -1)*NporH*NporH +1 ) , 2.0) ;
        d = exp( -pow((tan(acos(NporH)))/Mate ,2) ) / ( 4*Mate*Mate*pow(NporH,4) );

        g = 2*NporH*NporV / VporH ;
        gc = 2*NporH*NporL / VporH ;
        g = g < gc ? g : gc ;
        g = g < 1.0 ? g : 1.0 ;

        DGdiv = d*g/NporV ;

        double Fc = LporH;
        double argR = pow(1.0/Refraccion.X,2.0) + Fc*Fc - 1 ;
        double argG = pow(1.0/Refraccion.Y,2.0) + Fc*Fc - 1 ;
        double argB = pow(1.0/Refraccion.Z,2.0) + Fc*Fc - 1 ;

        double FgR = argR > 0.0 ? sqrt(argR) : 0.0 ;
        double FgG = argG > 0.0 ? sqrt(argG) : 0.0 ;
        double FgB = argB > 0.0 ? sqrt(argB) : 0.0 ;

        double FR = (0.5*pow(FgR-Fc,2)/pow(FgR+Fc,2))*(1+pow(Fc*(FgR+Fc)-1,2)/pow(Fc*(FgR-Fc)+1,2));
        double FG = (0.5*pow(FgG-Fc,2)/pow(FgG+Fc,2))*(1+pow(Fc*(FgG+Fc)-1,2)/pow(Fc*(FgG-Fc)+1,2));
        double FB = (0.5*pow(FgB-Fc,2)/pow(FgB+Fc,2))*(1+pow(Fc*(FgB+Fc)-1,2)/pow(Fc*(FgB-Fc)+1,2));

        double BlinnR = DGdiv*FR ;
        double BlinnG = DGdiv*FG ;
        double BlinnB = DGdiv*FB ;

        ColorPixel.X += ProporcionEspecular * BlinnR * Luz.ColorEspecular.X ;
        ColorPixel.Y += ProporcionEspecular * BlinnG * Luz.ColorEspecular.Y ;
        ColorPixel.Z += ProporcionEspecular * BlinnB * Luz.ColorEspecular.Z ;

        //----- Controlamos que ningún valor de color se salga del rango [0,1]

        T3DPunto MiColor;
        MiColor.X = ColorPixel.X > 1 ? 1 : (ColorPixel.X < 0 ? 0 : ColorPixel.X);
        MiColor.Y = ColorPixel.Y > 1 ? 1 : (ColorPixel.Y < 0 ? 0 : ColorPixel.Y);
        MiColor.Z = ColorPixel.Z > 1 ? 1 : (ColorPixel.Z < 0 ? 0 : ColorPixel.Z);

        return MiColor;
}




//---------------------------------------------------------------------------
//      FUNCION ConvertirTColorEnRGB: Función auxiliar que convierte en RGB (entre 0 y 1)
//      colores en formato TColor (están en hexadecimal)
//---------------------------------------------------------------------------

T3DPunto ConvertirTColorEnRGB (TColor color)
{
        int colorEntero, colorR, colorG, colorB;

        //----- Transforma en enteros los hexadecimales mediante divisiones
        //----- enteras 16^4 (=65536) y 16^2 (=256)

        colorEntero = (int) color;
        colorB = colorEntero/65536;
        colorEntero = colorEntero-colorB*65536;
        colorG = colorEntero/256;
        colorR = colorEntero-colorG*256;

        //----- Normaliza para que estén entre 0 y 1

        return (T3DPunto (colorR/256.0, colorG/256.0, colorB/256.0));
}

//---------------------------------------------------------------------------
//      FUNCION ConvertirRGBEnTColor: Función auxiliar que convierte en formato TColor
//      (están en hexadecimal) colores en RGB (entre 0 y 1)
//---------------------------------------------------------------------------

TColor ConvertirRGBEnTColor (T3DPunto RGB)
{
        int colorEntero, colorR0, colorR1, colorG0, colorG1, colorB0, colorB1;

        //----- Transforma en enteros los hexadecimales mediante divisiones
        //----- enteras 16^4 (=65536) y 16^2 (=256)

        colorR1 = (RGB.X*255)/16;
        colorR0 = (RGB.X*255)-colorR1*16;
        colorG1 = (RGB.Y*255)/16;
        colorG0 = (RGB.Y*255)-colorG1*16;
        colorB1 = (RGB.Z*255)/16;
        colorB0 = (RGB.Z*255)-colorB1*16;
        colorEntero = colorR0 + colorR1*16 + colorG0*256 + colorG1*4096 + colorB0*65536 + colorB1*1048576;

        //----- Normaliza para que estén entre 0 y 1

        return ((TColor) colorEntero);
}



