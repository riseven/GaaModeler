//---------------------------------------------------------------------------
//      PRACTICA DE GRAFICOS AVANZADOS Y ANIMACION
//      Curso 04-05
//      Definici�n de las clases:
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

#ifndef EscenaH
#define EscenaH

#include <math.h>

#define INF 10000
#define EPSILON 0.001
#define PI 3.14159265

//----- Definici�n de los tipos de figuras

#define FIGURA_GENERICA 0
#define FIGURA_PRISMA   1
#define FIGURA_ESFERA   2
#define FIGURA_CILINDRO 3
#define FIGURA_CONO     4
#define FIGURA_TORO     5
#define FIGURA_HMAP     6

//----- Definici�n de los modelos de iluminaci�n

#define MODELO_ALAMBRE                  1
#define MODELO_ALAMBRE_OCULTACION       2
#define MODELO_PHONG                    3
#define MODELO_BLINN                    4
#define MODELO_COOK_TORRANCE            5
#define MODELO_CELL_SHADING             6
#define MODELO_RAY_TRACING              7


//---------------------------------------------------------------------------
//	CLASE T3DPunto: Punto geom�trico 3D. Se utiliza tambi�n para representar
//	otros elementos formados por 3 reales: vectores y color RGB
//---------------------------------------------------------------------------

class T3DPunto
{
    public:

        //----- Constructores

        T3DPunto ();
        T3DPunto (T3DPunto&);
        T3DPunto (double, double, double);

        //----- Atributos p�blicos

    	double X, Y, Z;

        //----- M�todos p�blicos

        double Modulo ();
        void Normalizar ();
        void Escalar(double k){X*=k;Y*=k;Z*=k;}
        T3DPunto operator + (const T3DPunto &p){
            T3DPunto np = *this;
            X += p.X ;
            Y += p.Y ;
            Z += p.Z ;
            return *this;
        }
};

//---------------------------------------------------------------------------
//	CLASE TV�rtice: V�rtice de un pol�gono. Incluye el punto y su normal
//---------------------------------------------------------------------------

class TVertice : public T3DPunto
{
    public:

        //----- Constructores

     	TVertice ();
        TVertice (T3DPunto);
        TVertice (T3DPunto, T3DPunto);
        TVertice (TVertice&);
        TVertice (double, double, double);
        TVertice (double, double, double, double, double, double);

        //----- Atributos p�blicos

        T3DPunto N;
};

//---------------------------------------------------------------------------
//	CLASE TTransformacion: Transformaciones geom�tricas
//---------------------------------------------------------------------------

class TTransformacion
{
    public:

        //----- Constructor

    	TTransformacion ();
    	TTransformacion (int, int);

        //----- M�todos p�blicos

        TVertice Aplicar (TVertice);
        T3DPunto Aplicar (T3DPunto);

        TVertice AlRaster (TVertice);
        TVertice InvAlRaster (TVertice);

        void Trasladar (T3DPunto Punto);
        void RotarX (double Angulo);
        void RotarY (double Angulo);
        void RotarZ (double Angulo);
        void Escalar (T3DPunto Punto);

        void Identidad ();
        void Invertir();

    protected:
        //----- Atributos protegidos

        double Matriz [4][4];   //----- Matriz de transformacion
        int TamX, TamY;         //----- Tama�o de la ventana del raster

        //----- M�todos protegidos

        void ProductoMatriz (TTransformacion M);
        T3DPunto ProductoVector (T3DPunto P);


};

//---------------------------------------------------------------------------
//	CLASE TPoligono: Poligono. Una lista de pol�gonos forma una figura
//---------------------------------------------------------------------------

class TPoligono
{
    public:

        //----- Constructor y destructor

    	TPoligono ();
        ~TPoligono ();

        //----- Atributos p�blicos: lista de v�rtices del pol�gono

        TList *ListaVertices;

        //----- M�todos p�blicos

        double PlanoCoeficienteA (TTransformacion *);	// Calcular coeficientes del plano
        double PlanoCoeficienteB (TTransformacion *);
        double PlanoCoeficienteC (TTransformacion *);
        double PlanoCoeficienteD (TTransformacion *);

        void AddVertice (TVertice *);           // A�adir v�rtice a la lista

        void ExtremosY (TTransformacion *, double &, double &);     // Extremos del pol�gono en X e Y. Necesario para el Z-Buffer
        void ExtremosX (TTransformacion *, double, double &, double &, T3DPunto &, T3DPunto &, double &);
};

//---------------------------------------------------------------------------
//	CLASE TFigura: Figura geom�trica. Clase padre de las dem�s figuras
//---------------------------------------------------------------------------

class TFigura
{
    public:

        //----- Constructores y destructor

        TFigura ();
    	TFigura (T3DPunto, T3DPunto, T3DPunto);
        ~TFigura ();

        //----- Atributos p�blicos: colores del material para cada tipo de luz
        //----- (coeficiente k del modelo de Phong) y lista de pol�gonos

        T3DPunto ColorAmbiental;
        T3DPunto ColorDifuso;
        T3DPunto ColorEspecular;
        TList *ListaPoligonos;

        //----- M�todos p�blicos: generar pol�gonos, tipo de figura y c�lculo
        //----- de la intersecci�n -son virtuales porque cada clase hija
        //----- generar� los pol�gonos de una manera dependiendo del tipo
        //----- de figura que sea, informar� de qui�n es, y calcular� su

        virtual void GenerarPoligonos(void) {};
        virtual inline int QuienSoy () {return FIGURA_GENERICA;};
        virtual double Interseccion(TVertice rayo);

        double minT;
        TVertice minVertice;
        void ResetMinT(){minT=2.0;}

        void AddT(double nt, TVertice v){
            if (nt < minT && nt > 0.0 ){ // Estrictamente mayor, para evitar
                                        // reflejarse continuamente en la misma figura
                minT = nt;
                minVertice = v;
            }
        }

        double GetMinT(){return minT<=1.0?minT:-1.0;}
        TVertice GetMinVertice(){return minVertice;}

        //-------------------------------------------------------------------
        // Radiosity
        //-------------------------------------------------------------------
        virtual void CalcularPatch(int face, double param1, double param2, TPoligono &polig);
        virtual double AreaPatch(int face, double param1, double param2);
};


//---------------------------------------------------------------------------
//	CLASE TEsfera: Figura tipo esfera. Deriva de TFigura
//---------------------------------------------------------------------------

class TEsfera : public TFigura
{
    public:

    	//----- Constructores y destructor

        TEsfera ();
        TEsfera (T3DPunto, double, int, int);
        ~TEsfera ();

        //----- Atributos p�blicos: centro, radio, paralelos y meridianos

        T3DPunto Centro;
        double Radio;
        int Paralelos;
        int Meridianos;

        //----- M�todos p�blicos: generar pol�gonos para formar una esfera,
        //----- informar de que es una esfera

        void GenerarPoligonos(void);
        inline int QuienSoy () {return FIGURA_ESFERA;};
        double Interseccion(TVertice rayo);

        virtual void CalcularPatch(int face, double param1, double param2, TPoligono &polig);
        virtual double AreaPatch(int face, double param1, double param2);
};

//---------------------------------------------------------------------------
//	CLASE TPrisma: Figura tipo prisma. Deriva de TFigura
//---------------------------------------------------------------------------

class TPrisma : public TFigura
{
    public:

    	//----- Constructores y destructor
        TPrisma ();
        TPrisma (T3DPunto, double, double, double);
        ~TPrisma ();

        //----- Atributos p�blicos: centro, ancho, alto y profundidad

        T3DPunto Centro;
        double Ancho;
        double Alto ;
        double Profundidad ;

        //----- M�todos p�blicos: generar pol�gonos para formar un prisma,
        //----- informar de que es un prisma

        void GenerarPoligonos(void);
        inline int QuienSoy () {return FIGURA_PRISMA;};
        double Interseccion(TVertice rayo);
};


//---------------------------------------------------------------------------
//	CLASE TCilindro: Figura tipo cilindro. Deriva de TFigura
//---------------------------------------------------------------------------

class TCilindro : public TFigura
{
    public:

    	//----- Constructores y destructor
        TCilindro ();
        TCilindro (T3DPunto, double, double, int);
        ~TCilindro ();

        //----- Atributos p�blicos: centro, radio, aristas y altura

        T3DPunto Centro;
        double Radio;
        double Altura;
        int Aristas;

        //----- M�todos p�blicos: generar pol�gonos para formar un cilindro,
        //----- informar de que es un cilindro

        void GenerarPoligonos(void);
        inline int QuienSoy () {return FIGURA_CILINDRO;};
        double Interseccion (TVertice rayo);
};

//---------------------------------------------------------------------------
//	CLASE TCono: Figura tipo cono. Deriva de TFigura
//---------------------------------------------------------------------------

class TCono : public TFigura
{
    public:

    	//----- Constructores y destructor

        TCono ();
        TCono (T3DPunto, double, double, int);
        ~TCono ();

        //----- Atributos p�blicos: centro, radio, paralelos y altura

        T3DPunto Centro;
        double Radio;
        double Altura;
        int Paralelos;
        double Epsilon ;

        //----- M�todos p�blicos: generar pol�gonos para formar un cono,
        //----- informar de que es una cono

        void GenerarPoligonos(void);
        inline int QuienSoy () {return FIGURA_CONO;};
        double Interseccion (TVertice rayo);
};

//---------------------------------------------------------------------------
//	CLASE TToro: Figura tipo cono. Deriva de TFigura
//---------------------------------------------------------------------------

class TToro : public TFigura
{
    public:

    	//----- Constructores y destructor

        TToro ();
        TToro (T3DPunto, double, double, int, int );
        ~TToro ();

        //----- Atributos p�blicos: centro, radio, radio del anillo, paralelos
        //----- y numero de anillos que se conectan para formar el toro

        T3DPunto Centro;
        double Radio;
        double RadioAnillo;
        int Paralelos;
        int Anillos;

        //----- M�todos p�blicos: generar pol�gonos para formar un toro,
        //----- informar de que es una toro

        void GenerarPoligonos(void);
        inline int QuienSoy () {return FIGURA_TORO;};
};

//---------------------------------------------------------------------------
//	CLASE TCono: Figura tipo cono. Deriva de TFigura
//---------------------------------------------------------------------------

class THMap : public TFigura
{
    public:

    	//----- Constructores y destructor

        THMap ();
        THMap (T3DPunto, double, double, AnsiString);
        ~THMap ();

        //----- Atributos p�blicos: centro, escala, altura global y nombre
        //----- del fichero del que leer las alturas

        T3DPunto Centro;
        double Escala ;
        double Altura ;
        AnsiString Fichero;

        //----- M�todos p�blicos: generar pol�gonos para formar un HMap,
        //----- informar de que es una HMap

        void GenerarPoligonos(void);
        inline int QuienSoy () {return FIGURA_HMAP;};
};

//---------------------------------------------------------------------------
//	CLASE TLuz: Clase que contiene todos los par�metros de cada foco de luz
//---------------------------------------------------------------------------

class TLuz
{
    public:

    	//----- Constructores y destructor

    	TLuz ();
        ~TLuz ();

        //----- Atributos p�blicos: posici�n de la luz y componentes

        T3DPunto Posicion;
        T3DPunto ColorAmbiental;
        T3DPunto ColorDifuso;
        T3DPunto ColorEspecular;
};

//---------------------------------------------------------------------------
//	CLASE TEscena: Clase que contiene todos los elementos de la escena
//---------------------------------------------------------------------------

class TEscena
{
    public:

    	//----- Constructores y destructor

    	TEscena (int, int, TCanvas *);
        ~TEscena ();

        double ProporcionAmbiental, ProporcionDifusa, ProporcionEspecular;
        double ProporcionLocal, ProporcionReflexiva, ProporcionRefractiva;
        double Rugosidad;
        double Mate;
        T3DPunto Refraccion;
        double UmbralRayTracing;

        //----- M�todos p�blicos

        //----- Cambiar el tipo de visualizaci�n: Alambre, Phong ...

        void CambiarModeloIluminacion (int Modelo);
        void CambiarEjesVisibles (bool visibles) {EjesVisibles = visibles;};

        //----- A�adir una figura a la escena

        void AddEsfera (T3DPunto, double, int, int, T3DPunto);
        void AddPrisma (T3DPunto, double, double, double, T3DPunto);
        void AddCilindro (T3DPunto, double , double, int, T3DPunto);
        void AddCono (T3DPunto, double, double, int, T3DPunto);
        void AddToro (T3DPunto, double, double, int, int, T3DPunto);
        void AddHMap (T3DPunto, double, double, AnsiString, T3DPunto);

        //----- Dibujar escena

        void Dibujar ();

        //----- Maneja los eventos de teclado y rat�n

        void RatonPinchar (int, int);
        void RatonMover (int, int);
        void RatonSoltar (int, int);

    protected:

        //----- Atributos protegidos

        int TamX, TamY;                  // Tama�o del �rea de dibujo
        int ModeloIluminacion;           // Modelo de iluminacion: Alambre, Ocultaci�n, Phong, Blinn o Cook-Torrance

        bool Pinchando;                  // Necesarios para el manejo del evento de rat�n
        int XPrevio, YPrevio;
        int ModeloActivo;

        bool EjesVisibles;               // Ejes visibles
        TList *ListaFiguras;             // Lista de figuras de la escena

        TTransformacion *Transformacion; // Matriz de transformaci�n
        TLuz Luz;                        // Luz de la escena
        TCanvas *MiCanvas;               // Ventana de dibujo
        Graphics::TBitmap *IBuffer;      // Buffer de intensidades
        double **ZBuffer;

        //----- M�todos protegidos

        //----- Dibujar la escena con alambres, con el m�todo del Z-Buffer (para Phong)

        void DibujarAlambre ();
        void DibujarAlambreOcultacion();
        void DibujarZBuffer ();
        void DibujarRayTracing ();

        //----- Dibujar los ejes

        void DibujarEjes ();

        //----- Iluminaci�n de Phong: dada una figura y un punto de esta devuelve
        //----- el color del punto seg�n la iluminaci�n de Phong

        T3DPunto IluminacionPhong (TFigura *, TVertice);

        // Iluminacion de Blinn
        T3DPunto IluminacionBlinn (TFigura *, TVertice);

        // Iluminacion de Cook-Torrance
        T3DPunto IluminacionCookTorrance (TFigura *, TVertice);

        // Iluminacion de Cell Shading
        T3DPunto IluminacionCellShading (TFigura *, TVertice);


        // Para Ray-Tracing:
        T3DPunto TrazarRayo(TVertice rayo, float peso, int ignorar);
        bool TrazarSombra(TVertice rayo, int ignorar);
        TVertice ProlongarRayoLimite(TVertice rayo);

        T3DPunto IluminacionPhongRayTracing (TFigura *, TVertice, TVertice);

};

//---------------------------------------------------------------------------
//	FUNCIONES AUXILIARES para la conversi�n entre formatos de color
//---------------------------------------------------------------------------

T3DPunto ConvertirTColorEnRGB (TColor);
TColor ConvertirRGBEnTColor (T3DPunto);

#endif

