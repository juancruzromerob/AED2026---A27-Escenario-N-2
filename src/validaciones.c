#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "validaciones.h"

#define TAM_LINEA 100

static int leerLinea(char *linea) {
    int c;
    if (fgets(linea, TAM_LINEA, stdin) == NULL) {
        linea[0] = '\0';
        return 0;
    }
    if (strchr(linea, '\n') == NULL) {
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }
    linea[strcspn(linea, "\n")] = '\0';
    return linea[0] != '\0';
}

static int soloEspacios(const char *texto) {
    while (*texto != '0') {
        if (!isspace((unsigned char)*texto))
            return 0;
        ++texto;
    }
    return 1;
}

int leerEntero(const char *mensaje, int min, int max) {
    char linea[TAM_LINEA];
    char *fin;
    long valor;
    while (1) {
        printf("%s", mensaje);
        if (!leerLinea(linea)) {
            mostrarError("No escribiste nada.");
            continue;
        }
        valor = strtol(linea, &fin, 10);
        if (fin == linea || !soloEspacios(fin))
            mostrarError("Tenes que ingresar un numero entero.");
        else if (valor < min || valor > max)
            printf("  [!] El valor debe estar entre %d y %d.\n", min, max);
        else
            return (int)valor;
    }
}

double leerFlotante(const char *mensaje, double min, double max) {
    char linea[TAM_LINEA];
    char *fin, *coma;
    double valor;
    while (1) {
        printf("%s", mensaje);
        if (!leerLinea(linea)) {
            mostrarError("No escribiste nada.");
            continue;
        }
        coma = strchr(linea, ",");

        if (coma != NULL) *coma = '.';

        valor = strtod(linea, &fin);
        if (fin == linea || !soloEspacios(fin))
            mostrarError("Tenes que ingresar un numero (ej: 192 o 0.5).");
        else if (valor < min || valor > max)
            printf("  [!] El valor debe estar entre %.2f y %.2f.\n", min, max);
        else
            return valor;
    }
}

char leerSiNo(const char *mensaje) {
    char linea[TAM_LINEA];
    char c;
    while (1) {
        printf("%s (s/n): ", mensaje);
        if (leerLinea(linea) && strlen(linea) == 1) {
            c = (char)tolower((unsigned char)linea[0]);
            if (c == 's' || c == 'n')
                return c;
        }
        mostrarError("Responde solo con 's' o 'n'.");
    }
}


void mostrarError(const char *mensaje) {
    printf("  [!] %s\n", mensaje);
}

void pausar(void) {
    char linea[TAM_LINEA];
    printf("\nPresiona Enter para continuar...");
    leerLinea(linea);
}
