# SE_TP_1c2025
 


 

## Título: Sistema de monitoreo Eléctrico
 


 

### Alumno: Nicolás Orfanudis
 

### Padrón: 102410
 

### Objetivo: Desarrollar un sistema que mida y comunique por UART el consumo eléctrico
 


 

## Descripción:
 


 

El sistema se encontrará conectado a la red eléctrica domiciliaria con la intención de monitorear el consumo eléctrico de uno o mas electrodomesticos y aparatos electrónicos.
 


 

En este se incluirán dispositivos que permitan realizar una medición aislada de las variables de interes, tanto la corriente y tensión, como tambien el coseno $\phi$, importante a la hora de medir el consumo activo, reactivo y total de potencia.
 


 

Las mediciones se realizan y procesan en tiempo real permitiendo calcular el consumo total, el cual se transmite por UART al computador que se encuentre conectado.
 


 

La tensión de entrada se rectificará y reducirá a un nivel admisible para luego ser medida por un optoacoplador, la cual se enciará al microcontrolador. Por otro lado, la medición de corriente se realizará mediante el dispositivo [ASC712](https://www.allegromicro.com/-/media/files/datasheets/acs712-datasheet.ashx) que, utilizando el [Efecto Hall](https://es.wikipedia.org/wiki/Efecto_Hall) permite realizar una medición (También aislada de la red) de la corriente.
 


 

Por último, estas dos señales adicionalmente pasan por comparadores para así obtener pulsos sincronizados con los cruces por cero, permitiendo calcular mediante timers el defasaje de estos, obteniendo así el coseno $\phi$.
 


 

Plataforma de desarrollo: Bluepill (STM32F103C8)
 


 

Perifericos a utilizar:
 

- ANALOG IN 1 Y 2: Para las mediciones de tensión y corriente
 

- T1C1 y T1C2: Para las mediciones de los cruces por cero y cálculo de coseno $phi$
 

- PC13 (Built in LED): Para indicar que se está realizando la comunicación por UART
 


 

Diagrama en Bloques:
 


 


 

![Diagrama en Bloques](https://github.com/user-attachments/assets/b75f6c81-f9ea-49db-8967-70c928032676)