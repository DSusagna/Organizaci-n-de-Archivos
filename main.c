#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void create_folder(char *folder_name) {
    mkdir(folder_name, 0755);
}

int main() {
    // Abre el directorio actual
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Error al abrir el directorio");
        return 1;
    }

    struct dirent *entry;

    // Contadores para el número de carpetas y archivos en cada carpeta
    int folder_count = 0;
    int file_count = 0;

    // Itera sobre los archivos en el directorio
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) { // Solo procesa archivos regulares
            // Verifica si el número actual de archivos alcanzó 50
            if (file_count % 50 == 0) {
                // Si es así, crea una nueva carpeta
                folder_count++;
                char folder_name[10];
                sprintf(folder_name, "cp%02d", folder_count);
                create_folder(folder_name);
            }

            // Mueve el archivo a la carpeta actual
            char new_path[50];
            sprintf(new_path, "cp%02d/%s", folder_count, entry->d_name);
            if (rename(entry->d_name, new_path) != 0) {
                perror("Error al mover el archivo");
                return 1;
            }

            file_count++;
        }
    }

    closedir(dir);

    printf("Proceso completado con éxito.\n");

    return 0;
}
