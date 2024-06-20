/*
Programa que lista el contenido de un cierto directorio 
y sus atributos como lo hace ls -l*/

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

// Función para imprimir los permisos de un archivo
void print_permissions(mode_t mode) {
    // Imprimir permisos de lectura, escritura y ejecución para el propietario
    putchar((mode & S_IRUSR) ? 'r' : '-');
    putchar((mode & S_IWUSR) ? 'w' : '-');
    putchar((mode & S_IXUSR) ? 'x' : '-');
    // Imprimir permisos de lectura, escritura y ejecución para el grupo
    putchar((mode & S_IRGRP) ? 'r' : '-');
    putchar((mode & S_IWGRP) ? 'w' : '-');
    putchar((mode & S_IXGRP) ? 'x' : '-');
    // Imprimir permisos de lectura, escritura y ejecución para otros
    putchar((mode & S_IROTH) ? 'r' : '-');
    putchar((mode & S_IWOTH) ? 'w' : '-');
    putchar((mode & S_IXOTH) ? 'x' : '-');
}

// Función para obtener el tipo de un archivo
char get_file_type(mode_t mode) {
    if (S_ISREG(mode))
        return '-';
    if (S_ISDIR(mode))
        return 'd';
    if (S_ISCHR(mode))
        return 'c';
    if (S_ISBLK(mode))
        return 'b';
    if (S_ISFIFO(mode))
        return 'p';
    if (S_ISLNK(mode))
        return 'l';
    if (S_ISSOCK(mode))
        return 's';
    return '?';
}

int main(int argc, char *argv[]) {
    DIR *dir; // Puntero al directorio
    struct dirent *entry; // Entrada del directorio
    struct stat fileStat; // Estructura para almacenar información sobre el archivo
    struct passwd *pwd; // Estructura para almacenar información sobre el propietario del archivo
    struct group *grp; // Estructura para almacenar información sobre el grupo del archivo
    char time[20]; // Buffer para almacenar la fecha de modificación del archivo

    // Verificar que se haya proporcionado el directorio como argumento
    if (argc < 2) {
        printf("Usage: %s [directory]\n", argv[0]);
        return 1;
    }

    // Abrir el directorio
    dir = opendir(argv[1]);
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    // Leer las entradas del directorio
    while ((entry = readdir(dir)) != NULL) {
        // Obtener información sobre el archivo
        if (stat(entry->d_name, &fileStat) == -1) {
            perror("stat");
            continue;
        }
        // Obtener la fecha de modificación del archivo en formato legible
        strftime(time, 20, "%b %d %H:%M", localtime(&fileStat.st_mtime));
        // Imprimir el tipo de archivo
        printf("%c", get_file_type(fileStat.st_mode));
        // Imprimir los permisos del archivo
        print_permissions(fileStat.st_mode);
        // Imprimir el número de enlaces duros al archivo
        printf(" %3ld", fileStat.st_nlink);

        // Imprimir el propietario del archivo
        pwd = getpwuid(fileStat.st_uid);
        if (pwd != NULL)
            printf(" %s", pwd->pw_name);
        else
            printf(" %d", fileStat.st_uid);

        // Imprimir el grupo del archivo
        grp = getgrgid(fileStat.st_gid);
        if (grp != NULL)
            printf(" %s", grp->gr_name);
        else
            printf(" %d", fileStat.st_gid);

        // Imprimir el tamaño, la fecha de modificación y el nombre del archivo
        printf(" %10lld %s %s\n", fileStat.st_size, time, entry->d_name);
    }

    // Cerrar el directorio
    closedir(dir);
    return 0;
}