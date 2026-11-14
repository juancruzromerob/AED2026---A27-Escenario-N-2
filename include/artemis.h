#ifndef ARTEMIS_H
#define ARTEMIS_H

#define G_CONST        6.674e-11      
#define MASA_TIERRA    5.972e24       
#define RADIO_TIERRA   6371000.0      
#define ALTURA_INICIAL 192000.0       
#define MASA_ORION     33000.0       
#define PULSO_ACEL     0.50           
#define PULSO_TIEMPO   10.0           
#define NUM_PI         3.14159265358979


#define ALTURA_MIN_KM  160.0          
#define ALTURA_MAX_KM  2000.0         
#define MASA_MIN       1000.0
#define MASA_MAX       100000.0
#define MAX_INTENTOS   3              
#define TOLERANCIA     0.01          

#define RUTA_TIERRA    "assets/tierra.png"
#define RUTA_COHETE    "assets/cohete.png"
typedef struct {
    double altura;
    double masa;
    double radio;
    double fuerzaGrav;
    double velocidad;
    double periodo;
    double acelCentripeta;
} Orbita;


typedef struct {
    double aceleracion;
    double tiempo;
    double desvio;
    double velLateral;
    double velResultante;
    double angulo;
    int    realizado;
} Pulso;

typedef struct {
    double intentos[MAX_INTENTOS];
    int    cantidad;
    int    gano;
    int    partidas;
    int    victorias;
} Desafio;


void inicializarOrbita(Orbita *o, double altura, double masa);
void calcularOrbita(Orbita *o);
void configurarOrbita(Orbita *o);

void mostrarVelocidad(const Orbita *o);
void mostrarPeriodo(const Orbita *o);
void mostrarAceleracion(const Orbita *o);
 
void calcularPulso(const Orbita *o, Pulso *p);
void mostrarPulso(const Orbita *o, Pulso *p);

void jugarDesafio(const Orbita *o, Desafio *d);
void mostrarReporte(const Orbita *o, const Pulso *p, const Desafio *d);
#endif
