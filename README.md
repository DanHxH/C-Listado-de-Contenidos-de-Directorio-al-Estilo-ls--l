Listado de Contenidos de Directorio al Estilo ls -l

Este proyecto es una implementación en C que lista el contenido de un directorio y muestra sus atributos, similar al comando ls -l en Unix/Linux. El programa no utiliza ninguna función de la familia exec ni system.

Requisitos
Sistema operativo Unix/Linux
Compilador de C (como gcc)
Descripción del Proyecto
El programa realiza las siguientes funciones principales:

Apertura del Directorio: Utiliza la función opendir para abrir el directorio especificado por el usuario.
Lectura de Entradas del Directorio: Usa readdir para leer las entradas del directorio.
Obtención de Información de Archivos: Utiliza stat para obtener información detallada sobre cada archivo, como tipo, permisos, número de enlaces, propietario, grupo, tamaño y fecha de modificación.
Formato de Salida: Imprime la información de cada archivo en un formato similar al comando ls -l.
Archivos Principales
main.c: Contiene el código fuente del programa.

Uso
Compilación
Para compilar el programa, utiliza el siguiente comando:
gcc -o ls_sim main.c

Ejecución
Para ejecutar el programa, proporciona el nombre del directorio como argumento:
./ls_sim [directorio]

Por ejemplo, para listar el contenido del directorio actual, usa:
./ls_sim .