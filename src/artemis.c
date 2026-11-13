// artemis.c
#include <stdio.h>
#include "artemis.h"
#include "validaciones.h"

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
void configurarOrbita(Orbita *o)
{
    double alturaKm;

    printf("\n--- DATOS ACTUALES ---\n");
    printf("Altura de la orbita: %.1f km\n", o->altura / 1000.0);
    printf("Masa de Orion:       %.1f kg\n", o->masa);
    printf("Radio orbital:       %.1f km\n", o->radio / 1000.0);

    if (leerSiNo("\nQueres cambiar los datos?") == 's') {
        alturaKm = leerFlotante("Altura en km (160 a 2000): ", ALTURA_MIN_KM, ALTURA_MAX_KM);
        o->masa = leerFlotante("Masa de la nave en kg (1000 a 100000): ", MASA_MIN, MASA_MAX);
        o->altura = alturaKm * 1000.0;
        calcularOrbita(o);
        printf("Datos actualizados. Nuevo radio orbital: %.1f km\n", o->radio / 1000.0);
    }
}