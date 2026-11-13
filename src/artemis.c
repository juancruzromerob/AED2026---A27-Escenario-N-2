// artemis.c
#include "artemis.h"

void inicializarOrbita(Orbita *o, double altura, double masa)
{
    o->altura = altura;
    o->masa = masa;
    calcularOrbita(o);
}

void calcularOrbita(Orbita *o)
{
    o->radio = RADIO_TIERRA + o->altura;
    o->fuerzaGrav = G_CONST * MASA_TIERRA * o->masa / (o->radio * o->radio);
    o->velocidad = sqrt(G_CONST * MASA_TIERRA / o->radio);
    o->periodo = 2.0 * NUM_PI * o->radio / o->velocidad;
    o->acelCentripeta = o->velocidad * o->velocidad / o->radio;
}
