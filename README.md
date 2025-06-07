# SE_TP3_1c2025

## Título: Sistema de monitoreo Eléctrico

### Alumno: Nicolás Orfanudis

### Padrón: 102410

### Objetivo: Desarrollar un sistema que mida y comunique por display el consumo eléctrico y la hora actual


## Descripción:


El sistema se encontrará conectado a la red eléctrica domiciliaria con la intención de monitorear el consumo eléctrico de uno o mas electrodomesticos y aparatos electrónicos.

En este se incluirán dispositivos que permitan realizar una medición aislada de las variables de interes, tanto la corriente, tensión y frecuencia, como tambien el coseno $\phi$, importante a la hora de medir el consumo activo, reactivo y total de potencia.

Las mediciones se realizan y procesan en tiempo real, las cuales se muestran en un display LCD de 16x2 junto con la hora actual, configurada inicialmente via consola. El programa sigue un flujo bastante simple, observado en la Maquina de estados que se encuentra a continuación:

Maquina de Estados Finitos 

![Maquina de estados Finitos](https://github.com/user-attachments/assets/8ddaffff-9a58-4a25-ae2f-aa091b65a6a5)


La tensión de entrada se rectificará y reducirá a un nivel admisible para luego ser medida por un optoacoplador, la cual se enciará al microcontrolador. Por otro lado, la medición de corriente se realizará mediante el dispositivo [ASC712](https://www.allegromicro.com/-/media/files/datasheets/acs712-datasheet.ashx) que, utilizando el [Efecto Hall](https://es.wikipedia.org/wiki/Efecto_Hall) permite realizar una medición (También aislada de la red) de la corriente.

La frecuencia y el coseno $\phi$ se medirán a traves de pulsos que comiencen en el cruce por cero, permitiendo calcular el tiempo entre el comienzo de una onda y la otra, y de dos pulsos consecutivos de una de las ondas. 

Plataforma de desarrollo: NUCLEO-F429ZI

Perifericos a utilizar:

- ANALOG IN 1 Y 2: Para las mediciones de tensión y corriente
- D7, D0, D2, D6, D9, D8 como interfaz de comunicación con el display LCD16x2
- D14, D15 Como los detectores de cruce por cero
- PC10, PC11, PC12, PA4: Interfaz SPI para el módulo SD
- LED1 (Built in LED): Para indicar que se está realizando la comunicación por UART
- LED2 (Built in LED): Para indicar el grabado de la tarjeta SD
- USER_BUTTON(Built in): Como Pulsador ara realizar el grabado de la medición actual

![Video de demostración](https://drive.google.com/file/d/1tdw8074xq97-fDzAJOZByrxbPwTC79gV/view?usp=drive_link )

Diagrama en Bloques:

![Diagrama en bloques](https://github.com/user-attachments/assets/d889034b-d62c-4e3e-9be8-2a3a255e05f6)
