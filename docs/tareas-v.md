# Lista de Tareas - Implementación de un Intérprete de Comandos

## 1. Tokenización y Tipos de Palabras
- Definir y clasificar los tokens: palabras reservadas, palabras comunes y operadores.
- Implementar el reconocimiento de operadores (por ejemplo, `|` y `>`).
- Implementar el manejo de variables (expansión de cadenas que empiezan con `$`).

## 2. Manejo de Comandos y Pipes
- Implementar una estructura para describir palabras (ejemplo: estructura con cadena y banderas).
- Permitir la conexión lineal de comandos mediante pipes, redirigiendo la salida de uno como entrada de otro.
- Permitir la redirección de flujos estándar (entrada, salida y error) a archivos o procesos.

## 3. Lectura y Procesamiento de Entrada
- Leer caracteres desde la entrada, gestionar el buffer visible y el buffer real.
- Dividir caracteres en líneas y pasarlas al analizador.

## 4. Análisis Léxico
- Implementar el reconocimiento de comillas y evitar que los caracteres entre ellas sean interpretados como tokens especiales.
- Separar la entrada en palabras usando metacaracteres (espacios, tabulaciones, `;`, `&`).
- Identificar el tipo de palabra (reservada, identificador, declaración de asignación, etc.).

## 5. Análisis Sintáctico
- Clasificar tokens según su contexto gramatical.
- Analizar construcciones de varias líneas, declaraciones de casos, patrones extendidos o código.
- Generar estructuras de comandos a partir de listas de palabras, aplicando transformaciones según el contexto.

## 6. Expansiones de Palabras
- Implementar la expansión de variables y sustitución de parámetros.
- Procesar la expansión de llaves (ejemplo: `{uno,dos}` → `uno`, `dos`).
- Implementar la sustitución de comandos (`$(comando)` o `` `comando` ``).
- Implementar la sustitución de procesos y la expansión aritmética (`$((expresión))`).
- Diferenciar el comportamiento de expansiones según el tipo de comillas (simples/dobles).
- Realizar la expansión de nombres de archivos y rutas.

## 7. Implementación de la Ejecución de Expansiones
- Implementar una tubería interna para transformar palabras a través de varias etapas de expansión.
- Aplicar expansiones antes de la ejecución del comando.
- Separar nombre de comando y argumentos tras las expansiones.

## 8. Redirección de Flujos
- Crear objetos de redirección y asignar descriptores de archivo (fd) a variables.
- Implementar la reversión de redirecciones al finalizar el comando (por ejemplo, usando dup2).
- Gestionar listas de objetos de redirección para comandos y restaurar el estado previo.

## 9. Comandos Integrados (Built-ins)
- Implementar comandos internos que no crean procesos nuevos (ejemplo: `cd`).
- Permitir la modificación del entorno del intérprete mediante built-ins.
- Gestionar argumentos expandidos y reglas especiales para declaraciones de asignación.

## 10. Ejecución de Comandos Simples
- Implementar asignaciones de variables previas o independientes al comando.
- Modificar el entorno de ejecución según el contexto de la asignación.
- Buscar comandos en el PATH y ejecutar funciones internas si no se encuentran ejecutables externos.
- Gestionar la ejecución directa si se proporciona una ruta de comando.

## 11. Control de Trabajos y Procesos
- Implementar la ejecución de comandos en primer y segundo plano.
- Gestionar grupos de procesos, suspendiendo y reanudando según sea necesario.
- Mantener estructuras de datos simples para el seguimiento de procesos y trabajos.
- Asociar procesos con trabajos y gestionar sus estados (ejecución, suspensión, finalización).

## 12. Manejo de Códigos de Salida y Operadores Lógicos
- Implementar el almacenamiento y consulta del código de salida del último comando (`$?`).
- Implementar operadores lógicos de ejecución condicional (`&&`, `||`) y su comportamiento de cortocircuito.
- Implementar comandos `true` y `false` para pruebas lógicas.

---
Cada tarea puede implementarse de forma independiente a la plataforma o lenguaje, facilitando la adaptación a distintos entornos.