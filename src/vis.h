struct visibility {
	double u_axis;
	double v_axis;
	double r_value;
	double i_value;
	double noise;
};

typedef struct visibility visibility;

void showVisibility(visibility visibility);
visibility stringToVisibility(char * vis);
double mediaReal(int qty_visibilities, visibility * visibilities);
double mediaImaginaria(int qty_visibilities, visibility * visibilities);
double ruidoTotal(int qty_visibilities, visibility * visibilities);
double potenciaVisibilidades(int qty_visibilities, visibility * visibilities);