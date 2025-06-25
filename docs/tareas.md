# Lista de tareas agnóstica

## 1. Manejo de errores y códigos de retorno
- Filtrar y asignar correctamente los códigos de retorno en errores de ejecución (ej. 126, 127).
- Capturar el valor de retorno si un proceso termina por señal (usar variable global para diferenciar).
- Revisar y corregir posibles double free al manejar argumentos como `$`.

## 2. Validación de comandos y argumentos
- Manejar correctamente los pipes, incluyendo casos con pipes en posiciones atípicas o vacías.
- Impedir ejecución de comandos con argumentos vacíos (ej. `ls "" -l "" -a`).
- Ignorar variables no válidas en argumentos de comandos.

## 3. Expansión y tokenización de variables
- Revisar el orden de expansión/tokenización: expandir antes de tokenizar argumentos con espacios (excepto entre comillas).
- Volver a tokenizar argumentos tras la expansión de variables.
- Asegurarse que la variable `PWD` siempre se expanda correctamente.
- Implementar correctamente la expansión de variables en el contexto de here_doc y delimitadores.

## 4. Funcionalidad de comandos internos
- Validar el comportamiento de `exit` con argumentos numéricos y no numéricos, incluyendo el trim de argumentos.
- Revisar la gestión de la variable especial `$_` (último parámetro).
- Validar el comportamiento de `unset`, incluyendo el manejo de variables vacías y la prohibición de unsetear `$_`.
- Comprobar funcionamiento de `export`, especialmente:
  - Exportar correctamente variables con y sin valor.
  - No modificar variables ya existentes si se exportan sin valor.
  - Imprimir correctamente variables especiales como `_=/usr/bin/env`.
  - Gestionar correctamente la actualización y visibilidad de variables exportadas con valores complejos (ej. `export cmd="ls -la"`).
- Validar que `env` no imprima variables vacías y que imprima correctamente las necesarias.

## 5. Manejo avanzado de here_doc
- Permitir cierre de here_doc con Ctrl+D y gestión correcta de delimitadores (sin expandir si está entre comillas).
- Manejar advertencias de herramientas como Valgrind al cerrar here_doc con señales.
- Asegurar funcionamiento de señales dentro de here_doc (`Ctrl+C` debe cerrar ejecución y devolver control).

## 6. Señales y comportamiento interactivo
- Prevenir reacciones indeseadas ante señales como SIGQUIT (debe ser ignorada).
- Garantizar que las señales funcionen como se espera durante la ejecución y en el contexto de here_doc.

## 7. Revisión y estilo de código
- Cumplir con las normas de estilo (Norminette u otra estándar).
- Revisar mensajes de debug y eliminar los innecesarios (ej. `printf("exit\n");`).

## 8. Pruebas y comprobaciones adicionales
- Validar el funcionamiento del comando `echo` (incluyendo múltiples flags `-n`).
- Revisar el comportamiento con comillas dobles y simples durante la expansión.
- Asegurarse de que la expansión `$""` retorna NULL y `$"USER"` retorna USER.
- Validar comportamiento cuando se reciben solo símbolos especiales como `$` como argumento.

## 9. Otros detalles
- Revisar que unset funcione correctamente con o sin argumentos.
- Confirmar que se liberen correctamente los recursos en todas las salidas (`exit`, errores, señales).