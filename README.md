# SE_TP_1c2025

## Título: Sistema de monitoreo Eléctrico

### Alumno: Nicolás Orfanudis

### Padrón: 102410

### Objetivo: Desarrollar un sistema que mida y comunique por display el consumo eléctrico y la hora actual


## Descripción:


El sistema se encontrará conectado a la red eléctrica domiciliaria con la intención de monitorear el consumo eléctrico de uno o mas electrodomesticos y aparatos electrónicos.

En este se incluirán dispositivos que permitan realizar una medición aislada de las variables de interes, tanto la corriente y tensión, como tambien el coseno $\phi$, importante a la hora de medir el consumo activo, reactivo y total de potencia.

Las mediciones se realizan y procesan en tiempo real, las cuales se muestran en un display LCD de 16x2 junto con la hora actual, configurada inicialmente via consola. El programa sigue un flujo bastante simple, boservado en la Maquina de estados que se encuentra a continuación:

Maquina de Estados Finitos 

![Maquina de estados Finitos](https://github.com/user-attachments/assets/b0b19644-70bc-4a97-880d-bbe02e6440db)
 
La tensión de entrada se rectificará y reducirá a un nivel admisible para luego ser medida por un optoacoplador, la cual se enciará al microcontrolador. Por otro lado, la medición de corriente se realizará mediante el dispositivo [ASC712](https://www.allegromicro.com/-/media/files/datasheets/acs712-datasheet.ashx) que, utilizando el [Efecto Hall](https://es.wikipedia.org/wiki/Efecto_Hall) permite realizar una medición (También aislada de la red) de la corriente.

Plataforma de desarrollo: NUCLEO-F429ZI

Perifericos a utilizar:

- ANALOG IN 1 Y 2: Para las mediciones de tensión y corriente
- D8 a D13 como interfaz de comunicación con el display LCD16x2
- LED1 (Built in LED): Para indicar que se está realizando la comunicación por UART

[Video de demostración](https://drive.google.com/file/d/104cdx5k34bb13Tn5gw9p0ZyQc01t_1UM/view?usp=sharing)

Diagrama en Bloques:

![Diagrama en Bloques](https://github.com/user-attachments/assets/b75f6c81-f9ea-49db-8967-70c928032676)

