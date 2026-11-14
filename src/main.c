#include <stdio.h>
#include "artemis.h"
#include "validaciones.h"

int main(void)
{
    Orbita orbita;
    Pulso pulso = { 0 };
    Desafio desafio = { 0 };
    int opcion;
    inicializarOrbita(&orbita, ALTURA_INICIAL, MASA_ORION);

    do {
        printf("\n==================================================\n");
        printf("   ARTEMIS - Insercion y estabilidad en orbita LEO\n");
        printf("==================================================\n");
        printf(" 1. Ver / cambiar datos de la orbita\n");
        printf(" 2. (a) Gravedad como fuerza centripeta y velocidad\n");
        printf(" 3. (b) Periodo orbital\n");
        printf(" 4. (c) Aceleracion centripeta\n");
        printf(" 5. (d) Pulso del propulsor lateral\n");
        printf(" 6. Desafio: insercion orbital (juego)\n");
        printf(" 7. Simulacion grafica\n");
        printf(" 8. Reporte de mision\n");
        printf(" 0. Salir\n");

        opcion = leerEntero("Elegi una opcion: ", 0, 8);
        switch (opcion) {
            case 1: 
                configurarOrbita(&orbita);
                pulso.realizado = 0;
                break;
            case 2: mostrarVelocidad(&orbita);                  break;
            case 3: mostrarPeriodo(&orbita);                    break;
            case 4: mostrarAceleracion(&orbita);                break;
            case 5: mostrarPulso(&orbita, &pulso);              break;
            case 6: jugarDesafio(&orbita, &desafio);            break;
            case 8: mostrarReporte(&orbita, &pulso, &desafio);  break;
            case 0:
                printf("Fin de la simulacion. Hasta luego!\n");
                break;
        }

        if (opcion != 0) {
            pausar();
        }
    } while (opcion != 0);

    return 0;
}