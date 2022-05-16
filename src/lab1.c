#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "lab1.h"

int main(int argc, char **argv)
{
    // Configuración segun comandos de entrada
    command_setting setting = getSetting(argc, argv);
    // Mensaje Termino
    char end_visibility[200] = "FIN";

    // Configuración
    char* filename = setting.filename;
    char* result_filename = setting.result_filename;
    int qty_disks = setting.qty_disks;
    int disk_width = setting.disk_width;
    int b_flag = setting.b_flag;
    int qty_radius = qty_disks - 1;

    // 2 pipes por proceso: 
    // Padre -> Hijo
    // Hijo -> Padre
    // Pipes ocupan dos espacios por proceso en lista de pipes
    int p = 0;
    int pipes[qty_disks*2][2]; // 2 pipes por proceso: Padre -> Hijo
    
    int i;
    for(i = 0; i < qty_disks; i++)
    {
        if(pipe(pipes[p]) == -1)
        {
            printf("No se pudo crear el pipe h -> p\n");
            exit(EXIT_FAILURE);
        }

        if (pipe(pipes[p+1]) == -1)
        {
            printf("No se pudo crear el pipe p-> h\n");
            exit(EXIT_FAILURE);
        }
        
        int pid;    
        if((pid = fork()) == -1)
        {
            printf("no se pudo crear un hijo\n");
            exit(EXIT_FAILURE); 
        }
        if(pid == 0)
        {
            // Proceso Hijo
            printf("Child process => PPID=%d, PID=%d\n", getppid(), getpid());

            close(pipes[p][READ]);
            close(pipes[p+1][WRITE]);
            fflush(stdout);

            int qty_visibilities = 0;
            char *visibilities[MAX_VISIBILITIES];
            
            char *child_program = "./vis";
            visibilities[0] = (char*)malloc(strlen(child_program)*sizeof(char));
            strcpy(visibilities[0], child_program);

            char new_vis[200];

            while (read(pipes[p+1][READ], &new_vis, sizeof(char) * 200) > 0) {
                if (strcmp(new_vis, "FIN") == 0) {
                    if (b_flag == 0)
                        printf("Fin del proceso hijo %d -> procesé %d visibilidades\n", getpid(), qty_visibilities);
                    
                    if (dup2(pipes[p][WRITE],STDOUT_FILENO) == -1){
                        printf("Error in dup2()\n");
                        exit(-1);
                    }
                    
                    visibilities[qty_visibilities+1] = NULL;
                    execve("./vis", visibilities, NULL);
                    exit(EXIT_FAILURE);
                }
                else {
                    visibilities[qty_visibilities+1] = (char*)malloc(strlen(new_vis)*sizeof(char));
                    strcpy(visibilities[qty_visibilities+1], new_vis);
                    qty_visibilities++;
                }
            }
            close(pipes[p+1][READ]);
            close(pipes[p][WRITE]); 
        }
        p = p+2;
    }
            
    // Proceso Padre
    printf("Parent process => PID=%d\n", getpid());

    // Procesamiento archivo entrada
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("No es posible abrir el archivo");
        exit(1);
    }

    char vis[200];
    char line[200];
    visibility new_visibility;
    while(fgets(line, sizeof(line),file))
    {
        // Copiar linea string obtenida desde archivo de visibilidad a string vis.
        strcpy(vis, strtok(line,"\n"));

        // Split string según ','
        // Identificar atributos de cada visibilidad para generar una nueva y calcular propiedades
        char* token;
        token = strtok(line, ",");
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

        /* Propiedades Visibilidades */
        double distance = getDistance(new_visibility);
        int disk = getDisk(distance, qty_radius, disk_width);

        /* Enviar visibilidad a proceso hijo por pipe según disco */
        int pipe = disk + (disk+1);
        close(pipes[pipe-1][WRITE]);
        close(pipes[pipe][READ]);
        if (write(pipes[pipe][WRITE], &vis, sizeof(char) * 200) == -1)
        {
             printf("no es posible escribir al hijo\n");
             exit(1);
        }
    }
    
    /* FIN */
    fclose(file);

    p = 0;
    for(i = 0; i < qty_disks; i++)
    {   
        // Enviar mensaje FIN a hijos
        if (write(pipes[p+1][WRITE], &end_visibility, sizeof(char) * 200) == -1)
        {
            printf("no es posible escribir al hijo\n");
            exit(1);
        }

        // Obtener disco (proceso hijo)
        char disk[10];
        sprintf(disk, "Disco %d", i+1);

        // Obtener buffer desde salida de programa proceso hijo (./vis)
        char buffer[1000];
        read(pipes[p][READ], buffer, 1000);
        printf("buffer %s\n", buffer);

        // Escribir resultado en archivo de salida
        writeResult(result_filename, buffer, disk);

        // Cerrar pipe escriture hijo -> padre
        // Cerar pipe lectura padre -> hijo
        close(pipes[p][WRITE]);
        close(pipes[p+1][READ]);
        p = p+2;
    }

    return EXIT_SUCCESS;
}