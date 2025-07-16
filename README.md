# SE_TPFinal_1c2025

## Título: Sistema de monitoreo Eléctrico

### Alumno: Nicolás Orfanudis

### Padrón: 102410

### Objetivo: Desarrollar un sistema que mida y comunique por display y por aplicación celular el consumo eléctrico y la hora actual


## Descripción:


El sistema se encontrará conectado a la red eléctrica domiciliaria con la intención de monitorear el consumo eléctrico de uno o mas electrodomesticos y aparatos electrónicos.

En este se incluirán dispositivos que permitan realizar una medición aislada de las variables de interes, tanto la corriente, tensión y frecuencia, como tambien el coseno $\phi$, importante a la hora de medir el consumo activo, reactivo y total de potencia.

Las mediciones se realizan y procesan en tiempo real, las cuales se muestran en un display LCD de 16x2 junto con la hora actual, configurada inicialmente via consola. Adicionalmente, las variables medidas y calculadas se enviarán via Bluetooth a una aplicación celular desarrollada en el entorno [MIT App Inventor](https://appinventor.mit.edu/). El programa sigue un flujo bastante simple, observado en la Maquina de estados que se encuentra a continuación:

Maquina de Estados Finitos 

<img width="1152" height="622" alt="imagen" src="https://github.com/user-attachments/assets/53363d63-a576-4936-8adc-d2400d35f35a" />



La tensión de entrada se rectificará y reducirá a un nivel admisible para luego ser medida por un optoacoplador, la cual se enciará al microcontrolador. Por otro lado, la medición de corriente se realizará mediante el dispositivo [ASC712](https://www.allegromicro.com/-/media/files/datasheets/acs712-datasheet.ashx) que, utilizando el [Efecto Hall](https://es.wikipedia.org/wiki/Efecto_Hall) permite realizar una medición (También aislada de la red) de la corriente.

La frecuencia y el coseno $\phi$ se medirán a traves de pulsos que comiencen en el cruce por cero, permitiendo calcular el tiempo entre el comienzo de una onda y la otra, y de dos pulsos consecutivos de una de las ondas. 

Plataforma de desarrollo: NUCLEO-F429ZI

Perifericos a utilizar:

- ANALOG IN 1 Y 2: Para las mediciones de tensión y corriente
- D7, D0, D2, D6, D9, D8 como interfaz de comunicación con el display LCD16x2
- D14, D15 Como los detectores de cruce por cero
- PC10, PC11, PC12, PA4: Interfaz SPI para el módulo SD
- PD5, PD6 (UART2): Interfaz de comunicación con módulo HC06

[Video de demostración](https://drive.google.com/file/d/1sq7Mj2O91dZLGVSDQ7my_pVvpUdaSsIS/view?usp=sharing)

Diagrama en Bloques:

<img width="1055" height="391" alt="imagen" src="https://github.com/user-attachments/assets/cff5d478-5585-4b47-9231-c4836b922de8" />
