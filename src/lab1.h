#define READ    0
#define WRITE   1
#define MAX_VISIBILITIES 100000

struct visibility {
	double u_axis;
	double v_axis;
	double r_value;
	double i_value;
	double noise;
};

struct command_setting {
	char *filename;
	char *result_filename;
	int qty_disks;
	int disk_width;
	int b_flag; // 0 TRUE ; 1 FALSE
};

typedef struct visibility visibility;
typedef struct command_setting command_setting;

double getDistance(visibility visibility);
int getDisk(double value, int qty_radius, int disk_width);
void writeResult(char *filename, char buffer[1000], char disk[10]);
command_setting getSetting(int argc, char **argv);