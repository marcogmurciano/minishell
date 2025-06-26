# Lista Unificada de Tareas para Minishell

## 1. Tokenización, Análisis Léxico y Sintáctico
- Definir y clasificar los tokens: palabras, operadores, EOF.
- Implementar reconocimiento de operadores (`|`, `>`, `>>`,`<<`, `<`).
- Separar la entrada en palabras usando metacaracteres y espacios.
- Implementar reconocimiento y manejo de comillas (simples y dobles).
- Identificar el tipo de palabra.
- Clasificar tokens según su contexto gramatical
- Generar estructuras de comandos a partir de listas de palabras.

## 2. Lectura y Procesamiento de Entrada
- Leer caracteres desde la entrada.
- Pasar línea al analizador.

## 3. Expansión y Manejo de Variables
- Implementar la expansión de variables (`$VAR`, `$?`, `$_`, etc.) y sustitución de parámetros.
- Diferenciar el comportamiento de expansiones según el tipo de comillas.
- Revisar el orden de expansión/tokenización: expandir antes de tokenizar argumentos con espacios (excepto entre comillas).
- Volver a tokenizar argumentos tras la expansión de variables.
- Asegurarse que la variable `PWD` siempre se expanda correctamente.
- Implementar correctamente la expansión de variables en el contexto de here_doc y delimitadores.
- Asegurarse de que la expansión `$""` retorna NULL y `$"USER"` retorna USER.
- Validar comportamiento cuando se reciben solo símbolos especiales como `$` como argumento.

## 4. Manejo de Comandos, Pipes y Redirecciones
- Implementar una estructura para describir palabras (cadena y banderas).
- Permitir la conexión de comandos mediante pipes, redirigiendo la salida de uno como entrada de otro.
- Permitir la redirección de flujos estándar (entrada, salida y error) a archivos o procesos.
- Crear objetos de redirección y asignar descriptores de archivo (fd) a variables.
- Implementar la reversión de redirecciones al finalizar el comando (ej. usando dup2).
- Gestionar listas de objetos de redirección y restaurar el estado previo.

## 5. Ejecución de Expansiones y Comandos
- Implementar una tubería interna para transformar palabras a través de varias etapas de expansión.
- Aplicar expansiones antes de la ejecución del comando.
- Separar nombre de comando y argumentos tras las expansiones.
- Implementar asignaciones de variables previas o independientes al comando.
- Modificar el entorno de ejecución según el contexto de la asignación.
- Buscar comandos en el PATH y ejecutar funciones internas si no se encuentran ejecutables externos.
- Gestionar la ejecución directa si se proporciona una ruta de comando.

## 6. Comandos Integrados (Built-ins)
- Implementar comandos internos que no crean procesos nuevos (ej. `cd`, `exit`, `unset`, `export`, `env`, `echo`).
- Permitir la modificación del entorno del intérprete mediante built-ins.
- Gestionar argumentos expandidos y reglas especiales para declaraciones de asignación.
- Validar el comportamiento de `exit` con argumentos numéricos y no numéricos, incluyendo el trim de argumentos.
- Revisar la gestión de la variable especial `$_` (último parámetro).
- Validar el comportamiento de `unset`, incluyendo el manejo de variables vacías y la prohibición de unsetear `$_`.
- Comprobar funcionamiento de `export`, especialmente:
  - Exportar correctamente variables con y sin valor.
  - No modificar variables ya existentes si se exportan sin valor.
  - Imprimir correctamente variables especiales como `_=/usr/bin/env`.
  - Gestionar correctamente la actualización y visibilidad de variables exportadas con valores complejos.
- Validar que `env` no imprima variables vacías y que imprima correctamente las necesarias.
- Validar el funcionamiento del comando `echo` (incluyendo múltiples flags `-n`).

## 7. Manejo Avanzado de Here_doc
- Permitir cierre de here_doc con Ctrl+D y gestión correcta de delimitadores (sin expandir si está entre comillas).
- Manejar advertencias de herramientas como Valgrind al cerrar here_doc con señales.
- Asegurar funcionamiento de señales dentro de here_doc (`Ctrl+C` debe cerrar ejecución y devolver control).

## 8. Control de Trabajos, Procesos y Señales
- Implementar la ejecución de comandos en primer y segundo plano.
- Gestionar grupos de procesos, suspendiendo y reanudando según sea necesario.
- Mantener estructuras de datos para el seguimiento de procesos y trabajos.
- Asociar procesos con trabajos y gestionar sus estados (ejecución, suspensión, finalización).
- Prevenir reacciones indeseadas ante señales como SIGQUIT (debe ser ignorada).
- Garantizar que las señales funcionen como se espera durante la ejecución y en el contexto de here_doc.

## 9. Manejo de Códigos de Salida y Operadores Lógicos
- Implementar el almacenamiento y consulta del código de salida del último comando (`$?`).
- Implementar operadores lógicos de ejecución condicional (`&&`, `||`) y su comportamiento de cortocircuito.
- Implementar comandos `true` y `false` para pruebas lógicas.
- Filtrar y asignar correctamente los códigos de retorno en errores de ejecución (ej. 126, 127).
- Capturar el valor de retorno si un proceso termina por señal (usar variable global para diferenciar).

## 10. Validación, Errores y Estilo
- Manejar correctamente los pipes, incluyendo casos con pipes en posiciones atípicas o vacías.
- Impedir ejecución de comandos con argumentos vacíos (ej. `ls "" -l "" -a`).
- Ignorar variables no válidas en argumentos de comandos.
- Revisar y corregir posibles double free al manejar argumentos como `$`.
- Cumplir con las normas de estilo (Norminette u otra estándar).
- Revisar mensajes de debug y eliminar los innecesarios.
- Confirmar que se liberen correctamente los recursos en todas las salidas (`exit`, errores, señales).

## 11. Pruebas y Comprobaciones Adicionales
- Revisar el comportamiento con comillas dobles y simples durante la expansión.
- Validar funcionamiento cuando se reciben solo símbolos especiales como `$` como argumento.
- Revisar que unset funcione correctamente con o sin argumentos.
