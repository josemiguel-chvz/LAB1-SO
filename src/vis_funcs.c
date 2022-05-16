#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>
#include <math.h>
#include "vis.h"

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