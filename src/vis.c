#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>
#include <math.h>
#include "vis.h"

int main(int argc, char **argv) {
    
    int qty_visibilities = argc-1;
    visibility * list = (visibility*)malloc(sizeof(visibility)*qty_visibilities);

    int i;
    for (i = 1; i <= qty_visibilities; i++)
    {
        list[i-1] = stringToVisibility(argv[i]);
    }

    double media_real = mediaReal(qty_visibilities, list);
    double media_imaginaria = mediaImaginaria(qty_visibilities, list);
    double ruido_total = ruidoTotal(qty_visibilities, list);
    double potencia = potenciaVisibilidades(qty_visibilities, list);
    
    char buffer_media_real[10];
    char buffer_media_imaginaria[10];
    char buffer_ruido_total[20];
    char buffer_potencia[10];

    sprintf(buffer_media_real, "%.4f", media_real);
    sprintf(buffer_media_imaginaria, "%.4f", media_imaginaria);
    sprintf(buffer_ruido_total, "%.4f", ruido_total);
    sprintf(buffer_potencia, "%.4f", potencia);
    
    char buffer[1000];
    char media_r[] = "Media real: ";
    char media_i[] = "Media imaginaria: ";
    char potencia_t[] = "Potencia: ";
    char ruido_t[] = "Ruido total: ";

    strcat(buffer, media_r);
    strcat(buffer, buffer_media_real);
    strcat(buffer, "\n");
    strcat(buffer, media_i);
    strcat(buffer, buffer_media_imaginaria);
    strcat(buffer, "\n");
    strcat(buffer, potencia_t);
    strcat(buffer, buffer_potencia);
    strcat(buffer, "\n");
    strcat(buffer, ruido_t);
    strcat(buffer, buffer_ruido_total);

    write(STDOUT_FILENO, buffer, 1000);
    
    free(list); 
    
    return EXIT_SUCCESS;
}