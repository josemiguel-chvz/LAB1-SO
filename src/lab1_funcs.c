#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "lab1.h"


//Entradas: Struct visibilidad
//Salidas: Distancia en double desde el centro del plano de fourier a la visibilidad indicada
//Descripción: usando la formula de distancia, se toma el eje u y v en el plano de fourier para calcular su distancia al centro (0,0)
double getDistance(visibility visibility)
{
	double distance = ((visibility.u_axis)*(visibility.u_axis))+((visibility.v_axis)*(visibility.v_axis));
	return sqrt(distance);
}

//Entradas:El valor de la distancia, cantidad de radios, ancho de disco
//Salidas: Disco con el rango correspondiente al valor de la distancia
//Descripción: dada una distancia, se indica a que disco corresponde según los rangos de los radios
//Siendo en el caso de encontrarse en el último radio, se indica el último disco
//En los otros casos se verifica si la distancia se encuentra dentro de los rangos de un disco (parte desde 0)
// 2 discos -> Disco 0; Disco 1
int getDisk(double value, int qty_radius, int disk_width)
{
	int i;
	int disk;
	for(i = 0; i <= qty_radius; i++)
	{
		double radius = (double) i*disk_width;
		double next_radius = (double) (i+1)*disk_width;

		if (i == qty_radius){
			if(value >= radius)
				disk = i;
		}
		else if (value >= radius && value < next_radius)
			disk = i;
	}
	return disk;
}

//Entradas: nombre de archivo, buffer mensaje_salida, disco
//Salidas: ninguna
//Descripción: a partir de un nombre de archivo dado se escribe/sobrescribe un buffer de mensaje en el archivo así como el disco correspondiente
void writeResult(char *filename, char buffer[1000], char disk[10])
{
	FILE *file_result;
    file_result = fopen(filename, "a");
    if (file_result == NULL)
    {
        perror("No es posible abrir el archivo");
        exit(1);
    }
    fprintf(file_result, "%s\n", disk);
    fprintf(file_result, "%s\n", buffer);
    fclose(file_result);
    return;
}

//Entradas: argc (cantidad de argumentos), argv (arreglo de argumentos)
//Salidas: command setting que contiene nombre de archivo, archivo de salida, cantidad de discos, ancho disco, flag
//Descripción: Usando los argumentos recibidos en la linea de comandos,
//Estos son procesados por la función getopt() según lo indicando en la linea de comando
//Al encontrar un caso valido en el getopt, el argumento se almacena en el struct command setting setting
command_setting getSetting(int argc, char **argv)
{
	/* Opciones de linea de comando */
	int opt;
	command_setting setting;
	setting.b_flag = 1;

	while ((opt = getopt(argc, argv, ":i:o:d:n:b")) != -1)
	{
		switch(opt)
		{
			case 'i':
				setting.filename = optarg;
				printf("Archivo: %s\n", optarg);
				break;
			case 'o':
				setting.result_filename = optarg;
				printf("Archivo de salida: %s\n", optarg);
				break;
			case 'n':
				setting.qty_disks = atoi(optarg);
				printf("Cantidad discos: %d\n", atoi(optarg));
				break;
			case 'd':
				setting.disk_width = atoi(optarg);
				printf("Ancho disco: %d\n", atoi(optarg));
				break;
			case 'b':
				printf("Mostrar por consola: Activado\n");
				setting.b_flag = 0; // True
				break;
			case '?':
				if (optopt == 'i')
					fprintf (stderr, "Opcion -%c requiere el nombre de archivo de entrada.\n", optopt);
				else if(optopt == 'o')
					fprintf (stderr, "Opcion -%c requiere el nombre de archivo de salida.\n", optopt);
				else if(optopt == 'n')
					fprintf (stderr, "Opcion -%c requiere indicar cantidad de discos\n", optopt);
				else if(optopt == 'd')
					fprintf (stderr, "Opcion -%c requiere indicar el ancho de disco\n", optopt);
				else if (isprint (optopt))
					fprintf (stderr, "Opción desconocida `-%c'.\n", optopt);
				else
					fprintf (stderr,"Caracter de opción desconocida `\\x%x'.\n",optopt);
			default:
				abort();
		}
	}

	return setting;
}