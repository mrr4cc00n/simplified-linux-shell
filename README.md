
A simplified version of linux shell implemented in C (2018)
========================

The objective of the project is to make a shell that simulates the linux operating system shells.

The functionalities are the following:

1. When executing the program, it should print a prompt (example "$")
2. Run commands and print their output
3. Be able to execute the command `cd` (and change directory)
4. Redirect standard command input and output to / from files with `>`, `<`, `>>`
5. Redirect the standard output of one command to the input of another with a pipe `|`
6. Once the previous command is finished, the prompt should be shown again.
7. There will only be one space between each of the * tokens * of the entry
  * commands
  * parameters
  * redirect operators (`>`, `|`, etc.)

and up to here they have 3 points in the project

8. Implement more than one pipeline (additional 1pt)
9. Implement the `&` operator and have background processes (additional 1pt)
  * jobs => list all processes that are running in the background
  * fg <pid> => send process <pid> to the foreground
  * NOTE: something like `command1 <file1 | command2> file2 & `
9. Allow any number of spaces or not between commands and parameters (additional 0.5pt)
10. Implement a command history (a `history` command) that allows printing the last 50 commands executed in the console (0.5pt additional)
  * NOTE: if the command begins with a space, then it does not go to the history.

El objetivo del proyecto es hacer un shell que simule los shells del sistema operativo linux.

Las funcionalidades son las siguiente:

1. Al ejecutar el programa este debe imprimir un prompt (ejemplo "$ ")
2. Ejecutar comandos e imprimir su salida
3. Poder ejecutar el comando `cd` (y que cambie de directorio)
4. Redirigir entrada y salida estandar de comandos hacia/desde ficheros con `>`, `<`, `>>` 
5. Redirigir la salida estandar de un comando hacia la entrada de otro con un pipe `|`
6. Una vez terminado el comando previo, se debe mostrar el prompt nuevamente.
7. Solamente habrá un espacio entre cada uno de los *tokens* de la entrada
  * comandos
  * parámetros
  * operadores de redirección (`>`, `|`, etc.)

y hasta aqui tienen 3 puntos en el proyecto

8. Implementar mas de una tubería (1pt adicional)
9. Implementar el operador `&` y tener procesos en el background (1pt adicional)
  * jobs => listar todos los procesos que estan correiendo en el background
  * fg <pid> => envia el proceso <pid> hacia el foreground
  * NOTA: aqui tiene que funcionar algo como `command1 < file1 | command2 > file2 &`
9. Permitir cualquier cantidad de espacios o no entre los comandos y parametros (0.5pt adicional)
10. Implementar un historial de comandos (un commando `history`) que permita imprimir los últimos 50 comandos ejecutados en la consola (0.5pt adicional)
  * NOTA: si el comando empieza con espacio, entonces no va a parar al historial.
