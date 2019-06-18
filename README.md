# Whatsapp Message Communication Arduino
Trabajo Final de la asignatura Periféricos para la realización del sistema de mensajería Whatsapp y visualización de mensajes y comunicación haciendo uso de la herramienta Arduino. 

## Autores
```
- Luis Blázquez Miñambres
- Miguel Cabezas Puerto
- Alberto Hernández Pintor
```

## Funcionamiento del código
Para la realización de este proyecto hemos utilizado una placa Arduino Mega cuyo funcionamiento esta basado en la utilización de los siguientes lenguajes de programación realizado el programa utilizando los lenguajes de programación: **Arduino**, para modificar el comportamiento de las diferentes piezas y herramientas hardware que hemos conectado a la placa. Y , por otro lado, el lenguaje de programación **Python**, para el tratamiento de la comunicación de mensajes y persistencia y almacenamiento de datos en los chats que ofrece el servicio WhatsApp.

## Objetivo
El objetivo a alcanzar se trataba de conseguir enviar un mensaje a un número de teléfono y posteriormente no solo esta funcionalidad, si no también poder recibir mensajes de otros números, es decir, se trataba de una comunicación unidireccional puesto que los equipos que intervienen en la comunicación no pueden mandar mensajes a la vez, esto lo solucionamos posteriormente convirtiendo la comunicación en bidireccional de tal forma que se puede tener una conversación fluida normal al estilo WhatsApp.

A partir de este momento optamos por empezar a introducir más periféricos tanto de entrada (Keypad) como de salida (LEDs y Buzzer) con el fin de conseguir un mayor número de funcionalidades, cuyo propósito se explica en puntos posteriores.

Por último, con el fin de poder tener una agenda de contactos y guardar las conversaciones (para que, aunque te salgas de una conversación cuando te vuelvas a meter en la misma, continúe por donde se quedó) decidimos añadir persistencia de datos, lo cual nos obligó a utilizar Python. Finalmente decidimos añadir una interfaz gráfica en la terminal del ordenador para una mejor visualización de la interacción, una pantalla LCD donde poder visualizar menús y notificaciones y un joystick para movernos por los menús en el LCD.

## Ensamblaje 
El ensamblaje y conexión de las piezas de nuestro circuito a la placa Arduino se puede ver representados en la siguiente imágen

![Alt text](https://github.com/luisblazquezm/usal-gii-3-whatsapp-message-communication-arduino/raw/master/Arduino.png "Optional Title")
