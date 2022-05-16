#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>
#include <math.h>
#include "vis.h"

//Entradas: Struct visibilidad
//Salidas: ninguna
//Descripción: A partir de una visibilidad indicada, se muestran sus atributos
void showVisibility(visibility visibility)
{
	puts("******************************");
	printf("Eje u: %f\n",visibility.u_axis);
	printf("Eje v: %f\n",visibility.v_axis);
	printf("Parte Real: %f\n",visibility.r_value);
	printf("Parte Imaginaria: %f\n",visibility.i_value);
	printf("Ruido: %f\n",visibility.noise);
	puts("******************************");
	return;
}

//Entradas:String visibilidad
//Salidas: Struct visibilidad
//Descripción: a partir de un string que representa una visibilidad,
//se procesa para obtener los parametros y generar una visibilidad tipo struct visibility
visibility stringToVisibility(char * vis)
{
	visibility new_visibility;
	char* token;
	token = strtok(vis, ",");
	int attr_pos = 0;

	while(token != NULL)
	{
		if (attr_pos == 0){
			new_visibility.u_axis = strtod(token, NULL);
		}
		else if (attr_pos == 1){
			new_visibility.v_axis = strtod(token, NULL);
		}
		else if (attr_pos == 2){
			new_visibility.r_value = strtod(token, NULL);
		}
		else if (attr_pos == 3){
			new_visibility.i_value = strtod(token, NULL);
		}
		else if (attr_pos == 4){
			new_visibility.noise = strtod(token, NULL);
		}

		attr_pos++;
		token = strtok(NULL, ",");
	}
	return new_visibility;
}

//Entradas: cantidad de visibilidades, lista de visibilidades
//Salidas: valor double que indica la media real de las visibilidades del disco
//Descripción: dado una cantidad de visibilidades y una lista de visibilidades tipo struct visibility
//se calcula la media real usando el atributo r_value
double mediaReal(int qty_visibilities, visibility * visibilities)
{
	int i;
	double sum = 0.0;
	for(i = 0; i < qty_visibilities; i++)
	{
		sum = sum + visibilities[i].r_value;
	}

	return sum / qty_visibilities;
}

//Entradas: cantidad de visibilidades, lista de visibilidades
//Salidas: valor double que indica la media imaginaria de las visibilidades del disco
//Descripción: dado una cantidad de visibilidades y una lista de visibilidades tipo struct visibility
//se calcula la media imaginaria usando el atributo i_value
double mediaImaginaria(int qty_visibilities, visibility * visibilities)
{
	int i;
	double sum = 0.0;
	for(i = 0; i < qty_visibilities; i++)
	{
		sum = sum + visibilities[i].i_value;
	}

	return sum / qty_visibilities;
}

//Entradas: cantidad de visibilidades, lista de visibilidades
//Salidas: valor double que indica el ruido total del disco
//Descripción: dado una cantidad de visibilidades y una lista de visibilidades tipo struct visibility
//se calcula el ruido total usando el atributo noise
double ruidoTotal(int qty_visibilities, visibility * visibilities)
{
	int i;
	double sum = 0.0;
	for(i = 0; i < qty_visibilities; i++)
	{
		sum = sum + visibilities[i].noise;
	}

	return sum;
}

//Entradas: cantidad de visibilidades, lista de visibilidades
//Salidas: valor double que indica la potencia de las visibilidades del disco
//Descripción: dado una cantidad de visibilidades y una lista de visibilidades tipo struct visibility
//se calcula la potencia usando el atributo r_value e i_value
double potenciaVisibilidades(int qty_visibilities, visibility * visibilities)
{
	int i;
	double sum = 0.0;
	for(i = 0; i < qty_visibilities; i++)
	{
		double distancia = (visibilities[i].r_value * visibilities[i].r_value) + (visibilities[i].i_value * visibilities[i].i_value);
		sum = sum + sqrt(distancia);
	}

	return sum;
}