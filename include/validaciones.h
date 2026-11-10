#ifndef VALIDACIONES_H
#define VALIDACIONES_H

int leerEntero(const char *mensaje, int min, int max);
double leerFlotante(const char *mensaje, double min, double max);
char leerSiNo(const char *mensaje);

void mostrarError(const char *mensaje);
void pausar(void);

#endif
