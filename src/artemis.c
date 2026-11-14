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

void mostrarVelocidad(const Orbita *o)
{
    double fuerzaCentripeta = o->masa * o->velocidad * o->velocidad / o->radio;

    printf("\n--- (a) GRAVEDAD COMO FUERZA CENTRIPETA ---\n");
    printf("En orbita la unica fuerza sobre Orion es la gravedad,\n");
    printf("y apunta siempre al centro de la Tierra. Por eso hace de fuerza centripeta:\n\n");
    printf("   Fg = Fc\n");
    printf("   G*MT*m / r^2 = m*v^2 / r\n");
    printf("   v = raiz(G*MT / r)      (la masa de la nave se cancela)\n\n");
    printf("Fuerza gravitatoria  Fg = %.2f N\n", o->fuerzaGrav);
    printf("Fuerza centripeta    Fc = %.2f N  (son iguales)\n", fuerzaCentripeta);
    printf("Velocidad orbital    v  = %.2f m/s  (%.2f km/h)\n", o->velocidad, o->velocidad * 3.6);
}


void mostrarPeriodo(const Orbita *o)
{
    printf("\n--- (b) PERIODO ORBITAL ---\n");
    printf("T = 2*pi*r / v\n");
    printf("T = %.2f s = %.2f minutos\n", o->periodo, o->periodo / 60.0);
    printf("Vueltas por dia: %.2f\n", 86400.0 / o->periodo);
}


void mostrarAceleracion(const Orbita *o)
{
    printf("\n--- (c) ACELERACION CENTRIPETA ---\n");
    printf("ac = v^2 / r  (tambien es igual a G*MT / r^2)\n");
    printf("ac = %.2f m/s^2  (%.1f %% de la gravedad en la superficie)\n",
           o->acelCentripeta, o->acelCentripeta / 9.80 * 100.0);
    printf("Los astronautas flotan porque caen junto con la nave, no porque no haya gravedad.\n");
}
void calcularPulso(const Orbita *o, Pulso *p)
{
    p->desvio = 0.5 * p->aceleracion * p->tiempo * p->tiempo;
    p->velLateral = p->aceleracion * p->tiempo;
    p->velResultante = sqrt(o->velocidad * o->velocidad + p->velLateral * p->velLateral);
    p->angulo = atan(p->velLateral / o->velocidad) * 180.0 / NUM_PI;
    p->realizado = 1;
}
void mostrarPulso(const Orbita *o, Pulso *p)
{
    printf("\n--- (d) PULSO DEL PROPULSOR LATERAL ---\n");
    printf("Valores del enunciado: a = %.2f m/s^2 durante %.1f s\n", PULSO_ACEL, PULSO_TIEMPO);

    if (leerSiNo("Usar esos valores?") == 's') {
        p->aceleracion = PULSO_ACEL;
        p->tiempo = PULSO_TIEMPO;
    } else {
        p->aceleracion = leerFlotante("Aceleracion del pulso en m/s^2 (0.01 a 10): ", 0.01, 10.0);
        p->tiempo = leerFlotante("Duracion del pulso en s (0.1 a 120): ", 0.1, 120.0);
    }

    calcularPulso(o, p);

    printf("\nTrayectoria: durante el pulso la nave sigue avanzando a %.2f m/s (MRU)\n", o->velocidad);
    printf("y a la vez acelera hacia el costado (MRUV). La suma de los dos\n");
    printf("movimientos da una curva parabolica, como un tiro horizontal.\n\n");
    printf("Desviacion lateral   d  = 1/2 * a * t^2 = %.2f m\n", p->desvio);
    printf("Velocidad lateral    vl = a * t         = %.2f m/s\n", p->velLateral);
    printf("Velocidad resultante v' = %.4f m/s\n", p->velResultante);
    printf("Angulo de desvio respecto de la orbita = %.4f grados\n", p->angulo);
    printf("\nComo ahora la velocidad tiene una componente lateral, la nave deja la orbita\n");
    printf("original y pasa a una orbita apenas inclinada (y algo eliptica).\n");
}
