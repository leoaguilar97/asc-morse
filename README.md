# asc-morse

Practica 1

Sistema ASCmorse

# Objetivos
1. Desarrollar un dispositivo funcional capaz de comunicarse con internet
2. Desarrollar un circuito que incorpore los componentes físicos del dispositivo.
3. Implementar módulo WiFi al microcontrolador Arduino
4. Comunicar a través de una API REST los datos obtenidos.

# Descripción General
Se ha lanzado una propuesta de desarrollo de tecnología, en la cual se solicita a su equipo de trabajo desarrollar un proyecto donde se pueda traducir texto ingresado desde una 
página web a código Morse, el cual se reproducirá de forma auditiva y visual en un dispositivo utilizando el microcontrolador Arduino, 
así como la funcionalidad de traducir de código Morse a texto utilizando un botón.

# Detalles
Se deben tomar las siguientes consideraciones para la elaboración de esta práctica:

# Microcontrolador
Se debe utilizar Microcontroladores Arduino así como diferentes librerías y componentes compatibles con dicha tecnología.

# Acciones
El proyecto debe ser capaz de desarrollar las siguientes acciones:

- ASCII -> Morse:
1. Ingresar de forma web una cadena de texto.
2. Interpretar una cadena de texto en formato ASCII y traducirla a código Morse (ver Imagen I en la sección Anexo).
3. Con una bocina, reproducir el código Morse de forma entendible y que se pueda identificar y diferenciar la reproducción de un punto y la reproducción de un guión.
4. Utilizando una matriz de LEDs, reproducir el código Morse de forma gráfica (mostrando puntos y guiones). Esto debe estar sincronizado con la bocina.

- Morse -> ASCII:
1. Ingresar a través de un botón, el código morse a traducir.
2. Con una bocina, reproducir el código Morse que se está ingresando en tiempo real, esto como ayuda al usuario.
3. En la página web, se debe mostrar el texto ya traducido a ASCII.

- Modos:
El proyecto debe de tener los siguientes modos de funcionamiento:

1. Mensaje de bienvenida: En este modo se debe de mostrar en la matriz de luces LED el mensaje “HOLA GRUPO #”, donde # es el número de grupo asignado. Dicho mensaje debe de desplazarse de forma horizontal, sincronizándose de forma auditiva con el código Morse del mensaje.

2. Traducción ASCII -> Morse: Al ingresar un texto en la página web, se debe de reproducir la traducción de este de forma auditiva, a través de una bocina y visual, a través de la matriz, reproduciendo de forma sincrónica ambas. En la matriz debe de visualizarse cada punto y guion por separado, mostrando un carácter a la vez.

3. Traducción Morse -> ASCII: Al presionar una secuencia de puntos y barras (código morse) utilizando un botón, el sistema reproducirá de forma síncrona la representación auditiva en tiempo real. Cuando se complete el código, se mostrará el mensaje ahora en ASCII dentro de una página web.

4. Juego/Aprendizaje: Se debe ingresar un texto no mayor a 10 caracteres dentro de una página web (Si son menos de 10 caracteres, se deberá llenar los espacios que faltan con caracteres ASCII al azar). Se enviará la cadena al Arduino. El texto se mostrará en la matriz de LEDs, se mostrará carácter por carácter hasta terminar la cadena. Cada vez que se muestre un carácter, se espera que el usuario presione el equivalente del carácter en código morse. Se llevará un puntaje, el cual se mostrará al finalizar el juego. Por cada acierto, se sumará 1 punto y se debe escuchar el sonido de acierto dentro del dispositivo. Si el usuario se equivoca o no contesta dentro de un tiempo de 8 segundos (este tiempo puede variar dependiendo del tiempo del código
morse), no se sumará ningún punto y se escuchará el sonido de fallo.

# Almacenamiento
Para el almacenamiento de los textos a ingresar se recomienda utilizar una base de datos, pero queda libre la selección de esta al grupo de desarrollo.

# Comunicación
Deben utilizar un módulo WiFi para la comunicación entre Arduino y el servicio de Internet, se recomienda utilizar el módulo ESP32, pero no hay restricciones sobre este. Se recomienda el uso de una API REST para la comunicación entre la página web y el Arduino.

# Presentación
Se debe de desarrollar una página web que contenga un TextBox para mandar el texto a traducir a código Morse. Dicha página debe tener un historial del texto involucrado para cada modo, ya sea el texto ingresado (ASCII->Morse y el juego) o el texto recibido (Morse->ASCII).

# Recomendaciones
1. El tiempo del código morse no tiene restricciones, pero se sugiere que los puntos (.) tengan una duración de 1 segundo o menos; y que las barras (-) tengan una duración de 3 segundos. Se debe poder diferenciar entre puntos y barras, ya sea el audio de este, así como cuando se presiona el botón.
2. La presentación del dispositivo físico debe ser creativa y todos los circuitos deben estar encapsulados.
 No hay restricción para el tamaño de la matriz LED, pero debe ser entendible. Pueden utilizar drivers para facilitar su utilización.
3. Pueden utilizar un buzzer o cualquier dispositivo auditivo, solo se debe poder diferenciar entre los distintos sonidos del dispositivo (código morse, sonido de éxito, sonido de error).

# Documentación

La documentación deberá contener:

1. Introducción
2. Diagramas de la arquitectura del dispositivo (como funciona la comunicación con la web, almacenamiento, etc.)
3. Diagrama de partes del dispositivo realizados en Fritzing
4. Manual de Usuario
