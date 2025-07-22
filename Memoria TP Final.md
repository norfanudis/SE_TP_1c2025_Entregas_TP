<img src="https://github.com/user-attachments/assets/15600b18-f73b-4ba3-a959-47f0048a1ab6" alt="image2" width="30%">

**UNIVERSIDAD DE BUENOS AIRES**  
**Facultad de Ingeniería**  
**86.65 Sistemas Embebidos**

Memoria del Trabajo Final:

***MainsControl* - Monitoreo de Linea en tiempo real**

**Autor: Nicolás Orfanudis**

Legajo: 102.410

*Este trabajo fue realizado en las Ciudad Autónoma de Buenos Aires,*   
*entre Marzo y Julio de 2025\.*

  
**RESUMEN**

En la siguiente memoría se describe el diseño e implementación de un sistema de monitoreo de linea para el entorno tanto domiciliario como industrial. El proyecto permite relevar datos de tensión, corriente, frecuencia, factor de potencia y potencia, tanto real como activa y reactiva.

Estos datos son mostrados al usuario tanto por un display LCD de 16x2 caracteres, como por una aplicación conectada al dispositivo via Bluetooth, permitiendole obtener los datos en tiempo real a distancia. Adicionalmente, el sistema almacena los datos medidos y calculados en una memoria SD, regstrando la fecha, hora y todos los valores mencionados previamente.

Estre proyecto le permite al usuario tener mejor control sobre los consumos eléctricos de un hogar, una máquina, o incluso un pequeño recinto industrial, evitando así grandes facturas de luz o posibles penalizaciones por factores de potencia elevados.


# Índice General

- [**Registro de versiones**](#registro-de-versiones)
- [**Introducción general**](#introducción-general)
  - [1.1 Análisis de necesidad y objetivos](#11-análisis-de-necesidad-y-objetivos)
  - [1.2 Módulos e Interfaces](#12-módulos-e-interfaces-de-smartlock)
- [**Introducción específica**](#introducción-específica)
  - [2.1 Requisitos](#21-requisitos)
  - [2.2 Casos de uso](#22-casos-de-uso)
  - [2.3 Descripción de los Módulos del sistema](#23-descripción-de-los-módulos-del-sistema)
    - [2.3.1 Alimentación](#231-alimentación)
    - [2.3.2 Microcontrolador](#232-microcontrolador)
    - [2.3.3 Sensor de Corriente](#233-sensor-de-corriente)
    - [2.3.4 Sensor de Tensión](#234-sensor-de-tension)
    - [2.3.5 Sensor de frecuencia y fase](#235-sensor-de-frecuencia-y-fase)
    - [2.3.6 Módulo SD](#236-modulo-sd)
    - [2.3.7 RTC](#237-modulo-sd)
    - [2.3.8 Módulo LCD 16x2](#238-modulo-LCD-16x2)
    - [2.3.9 Módulo Bluetooth](#239-modulo-bluetooth)
- [**Diseño e Implementación**](#diseño-e-implementación)
  - [3.1 Diseño del Hardware](#31-diseño-del-hardware)
    - [3.1.1 Diseño del sensor de corriente](#312-diseño-del-sensor-de-corriente)
    - [3.1.2 Diseño del sensor de tensión](#313-diseño-del-sensor-de-corriente)
    - [3.1.3 Diseño del sensor de frecuencia y fase](#315-diseño-del-sensor-de-frecuencia-y-fase)
    - [3.1.4 Diseño del modulo SD](#316-diseño-del-modulo-sd)
    - [3.1.5 Diseño del modulo LCD 16x2](#316-diseño-del-modulo-LCD-16x2)
    - [3.1.6 Diseño del modulo Bluetooth](#317-diseño-del-módulo-wi-fi)
    - [3.1.7 Diseño del hardware con la placa NUCLEO-F429ZI](#318-diseño-del-hardware-con-la-placa-nucleo-f429zi)
  - [3.2 Diseño del Firmware](#32-firmware)
    - [3.2.1 Módulo Tensión y Corriente](#321-modulo-tension-corriente)
    - [3.2.2 Módulo frecuencia y fase](#322-modulo-frecuencia-fase)
    - [3.2.3 Módulo RTC](#323-mdulo-sd)
    - [3.2.4 Módulo SD](#324-modulo-16x2)
    - [3.2.5 Módulo LCD 16x2](#325-modulo-16x2)
    - [3.2.6 Módulo Bluetooth](#326-módulo-bluetooth)
    - [3.2.7 Firmware Adicional](#327-firmware-adicional)
  - [3.3 Diseño de la aplicación y comunicación Bluetooth](#35-diseño-de-la-aplicación)
- [**Ensayos y Resultados**](#ensayos-y-resultados)
  - [4.1 Pruebas funcionales](#41-pruebas-funcionales-de-funcionamiento)
  - [4.2 Cumplimiento de requisitos](#42-cumplimiento-de-requisitos)
  - [4.3 Comparación con otros sistemas similares](#43-comparación-con-otros-sistemas-similares)
  - [4.4 Documentación del desarrollo realizado](#44-documentación-del-desarrollo-realizado)
- [**Conclusiones**](#conclusiones)
  - [5.1 Resultados obtenidos](#51-resultados-obtenidos)
  - [5.2 Próximos pasos](#52-próximos-pasos)
- [**Bibliografía**](#bibliografía)





# Registro de versiones 

| Revisión | Cambios realizados | Fecha |
| :---: | ----- | ----- |
| 1.0 | Creación del documento | 04/07/2025 |
| 1.1 | Redacción de la primera parte | 09/07/2025 |
| 1.2 | Entrega parcial del informe  | 11/07/2025 |


### 

# **CAPÍTULO 1** 

# **Introducción general** 

## **1.1 Análisis de necesidad y objetivos** 

Con el constante crecimiento de la tecnolgía, y el aumento continuo de consumo energético por persona en la sociedad moderna, las empresas que proveen esta energía se encuentran obligadas a realizar una discretización mas fina de los distintos tipos de consumidores, incluso imponiendo impuestos o tarifas elevadas si se supera un cierto consumo preestablecido o si se supera cierto tipo de energía consumida. Debido a eso, uno como usuario le gustaría (o en ciertos casos se encuentra obligado) a verificar periodicamente estos consumos y variables eléctricas.

Esta recolección de datos no resulta tan simple como parece, debido a las distintas formas de medición que se requieren, junto con la periodicidad de estas mediciones. Para ello, se requiere un dispositivo diseñado especialmente para obtener, analizar y comunicar estas mediciones, permitiendo así que el usuario pueda tomar una decisión informada de las acciones a realizar para decrementar el consumo o corregir consumos excesivos.

Adicionalmente se desea que este relevamiento de datos se pueda realizar de forma práctica y cómoda para el usuario, y por supuesto, de forma continua. También resulta de utilidad almacenar esta información de forma no volatil para su utilización en informes o análisis en un tiempo mas extendido.

Este tipo de productos no son una novedad, se encuentran comercialmente en distintos rangos de funcionamiento, para distintos entornos de consumo eléctrico y con diferencias sustanciales entre ellos. El primer ejemplo es un producto como el [MM2D-65](https://mail.bawelectric.com/imagenes/contenidos/2023-08/283-mm2d-65-manual.pdf) que realiza la medición de las variables mencionadas, pero no admite comunicación a internet o almacenamiento de datos en memorias externas, solo muestra los datos en una pantalla integrada. Estos se encuentran en el rango de los AR$ 45.000 y AR$ 65.000

Otro producto mas complejo, ahora si con comunicación via Wi-Fi, LAN o bluetooth es el [EM-50](https://www.digitalbaytech.com/es/products/shelly-pro-em-50-smart-din-rail-2-channel-single-phase-energy-meter-wi-fi-lan-and-bluetooth-connection?utm_content=&utm_term=&gad_source=1&gad_campaignid=20122675672&gbraid=0AAAAApF22wW701be59viJB4lXsergzUJo&gclid=EAIaIQobChMIh5LrgordjQMVip5aBR2niQFREAQYASABEgJ2bfD_BwE) de Shelly, con un costo de US$ 81,49 permite el monitoreo remoto de la red eléctrica monofásica. A diferencia del proyecto, o del ejemplo de BAW, este no cuenta con pantalla para leer los datos en tiempo real, pero si cuenta con memoria interna de hasta 60 días para guardar las mediciones.

En este proyecto se realizará una combinación de estos dos últimos, donde se tendrán las mediciones de tesión, corriente, frecuencia y fase, y en base a esas se realizará el calculo de las potencias real, activa y reactiva. Seguido de un display donde se mostrarán estos datos, y un módulo SD donde serán almacenados, y finalizando con un módul bluetooth que permita relevar estos datos a distancia.

## **1.2 Módulos e Interfaces de *MainControl*** 

El proyecto se puede subdividir en los siguientes bloques:

<img width="1031" height="395" alt="imagen" src="https://github.com/user-attachments/assets/d7f42d0a-7301-483c-9b2d-d76928e06ad0" />

Cada uno de ellos cuenta con una función particular, las cuales serán descriptas más en profundidad en la sección 2.3, pero principalmente, el sistema consiste en conversiones de las variables de la red, como tensión, corriente, frecuencia y fase, y las transforma en señales adecuadas para el microcontrolador, el cual mediante cuentas y factores de conversión, determina los valores de estas variables originales, junto con otras variables calculadas como la potencia total, activa y reactiva.

Una vez obtenidas, estas son mostradas en un display de 16x2 caracteres de forma cíclica, o en una aplicación conectada vía Bluetooth al proyecto. Esto le permite al usuario conocer estos valores de estas variables y tener un mejor control sobre los consumos de su hogar, maquina o cualquier entorno que desee.

# **CAPÍTULO 2** 

# **Introducción específica** 

## **2.1 Requisitos**

Realizada la mención de las caracteristicas básicas del proyecto, se definieron los requisitos principales que debe cumplir el proyecto. Las mismas se pueden observar en la siguiente tabla:

<table><thead>
  <tr>
    <th>Grupo de Req.</th>
    <th>ID del Req.</th>
    <th>Descripción</th>
  </tr></thead>
<tbody>
  <tr>
    <td>1. Entradas</td>
    <td>1.1</td>
    <td>El sistema contiene entradas para la tensión, la corriente y para las señales de cruce por cero</td>
  </tr>
  <tr>
    <td></td>
    <td>1.2</td>
    <td>El sistema realiza las mediciones de las entradas analógicas y digitales</td>
  </tr>
  <tr>
    <td>2. Modos</td>
    <td>2.1</td>
    <td>El sistema tendrá un modo de medición continuo</td>
  </tr>
  <tr>
    <td></td>
    <td>2.1.1</td>
    <td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;El sistema medirá el valor de tensión por la entrada analógica A1</td>
  </tr>
  <tr>
    <td></td>
    <td>2.1.2</td>
    <td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;El sistema medirá el valor de corriente por la entrada analógica A2</td>
  </tr>
  <tr>
    <td></td>
    <td>2.1.3</td>
    <td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;El sistema medirá el defasaje entre las señales de cruce por cero de las entradas digitales (D14 y D15)</td>
  </tr>
  <tr>
    <td></td>
    <td>2.1.4</td>
    <td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;El sistema medirá la frecuencia con el periodo de la señal de cruce por cero de tensión D15</td>
  </tr>
  <tr>
    <td></td>
    <td>2.1.5</td>
    <td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;El sistema calculará el consumo de potencia multiplicando la corriente con la tensión</td>
  </tr>
  <tr>
    <td></td>
    <td>2.2</td>
    <td>El sistema iniciará en modo configuración</td>
  </tr>
  <tr>
    <td></td>
    <td>2.2.1</td>
    <td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;El sistema solicitará por consola el seteo de fecha y hora</td>
  </tr>
  <tr>
    <td></td>
    <td>2.2.2</td>
    <td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;El sistema solicitará por consola el tipo de archivo deseado</td>
  </tr>
  <tr>
    <td>3. Display</td>
    <td>3.1</td>
    <td>El display mostrará el mensaje inicial que notificará al usuario que requiere configurar el sistema por consola</td>
  </tr>
  <tr>
    <td></td>
    <td>3.2</td>
    <td>El display mostrará los valores actuales de tensión, corriente, frecuencia y defasaje por 6 segundos</td>
  </tr>
  <tr>
    <td></td>
    <td>3.3</td>
    <td>El display mostrará la fecha y hora por 2 segundo</td>
  </tr>
  <tr>
    <td></td>
    <td>3.4</td>
    <td>El display mostrará los valores actuales de potencia total, activa y reactiva por 6 segundos</td>
  </tr>
  <tr>
    <td>4. SD</td>
    <td>4.1</td>
    <td>El sistema almacenará el estado actual de las entradas en la tarjeta SD cada 10 segundos</td>
  </tr>
  <tr>
    <td></td>
    <td>4.2</td>
    <td>El sistema permitirá via comando de consola leer las ultimas 10 mediciones guardadas</td>
  </tr>

  <tr>
    <td>5. Modulo Bluetooth</td>
    <td>5.1</td>
    <td>El sistema le comunicará al módulo Bluetooth el estado de las entradas cada 14 segundos</td>
  </tr>
  <tr>
    <td></td>
    <td>5.2</td>
    <td>El modulo Bluetooth establecerá conexión con una aplicación de celular para mostrar los datos enviados</td>
  </tr>
  <tr>
    <td>6. Alimentación</td>
    <td>6.1</td>
    <td>El sistema puede estar alimentado por USB y realizar la comunicación serie</td>
  </tr>
  <tr>
    <td></td>
    <td>6.2</td>
    <td>El sistema puede estar alimentado externamente</td>
  </tr>
  <tr>
    <td>7. Fecha de Entrega</td>
    <td>7.1</td>
    <td>El sistema se desarrollará en el lapso de un mes</td>
  </tr>
  <tr>
    <td>8. Costo</td>
    <td>8.1</td>
    <td>El sistema no costará mas de AR$200.000 (Placa NUCLEO Incluida)</td>
  </tr>
  <tr>
    <td>9. Documentación</td>
    <td>9.1</td>
    <td>El prototipo está acompañado de su lista de componentes, esquemáticos, diagramas de conexión y un repositorio con el código de implementación</td>
  </tr>
</tbody></table>

## **2.2 Casos de uso**
A continuación se listan tres casos de uso que ejempliifican la utilización del sistema.

<table><thead>
  <tr>
    <th>Caso de Uso</th>
    <th>Definición</th>
  </tr></thead>
<tbody>
  <tr>
    <td>Trigger</td>
    <td>El usuario desea comenzar las mediciones de la red de alimentación</td>
  </tr>
  <tr>
    <td>Precondición</td>
    <td>El sistema debe estar energizado<br>El sistema debe estar conectado a la PC via USB</td>
  </tr>
  <tr>
    <td>Flujo Básico</td>
    <td>El usuario ingresa fecha y hora por consola y el sistema comienza a medir las variables de entrada</td>
  </tr>
  <tr>
    <td>Flujo Alternativo</td>
    <td>El sistema informa que los datos ingresados son incorrectos y comienza nuevamente</td>
  </tr>
</tbody>
</table>

<table><thead>
  <tr>
    <th>Caso de Uso</th>
    <th>Definición</th>
  </tr></thead>
<tbody>
  <tr>
    <td>Trigger</td>
    <td>El usuario desea configurar la extensión del archivo de la SD que almacena las mediciones</td>
  </tr>
  <tr>
    <td>Precondición</td>
    <td>El sistema debe estar energizado<br>El sistema debe estar conectado a la PC via USB<br>Debe haber una tarjeta SD conectada correctamente al sistema</td>
  </tr>
  <tr>
    <td>Flujo Básico</td>
    <td>El usuario, luego de configurar la fecha y hora, selecciona la extensión del archivo de guardado</td>
  </tr>
  <tr>
    <td>Flujo Alternativo</td>
    <td>La tarjeta SD no pudo ser leida correctamente, se le avisa al usuario que debe reiniciar el sistema</td>
  </tr>
</tbody>
</table>

<table><thead>
  <tr>
    <th>Caso de Uso</th>
    <th>Definición</th>
  </tr></thead>
<tbody>
  <tr>
    <td>Trigger</td>
    <td>El usuario desea leer los datos de entrada mediante aplicación celular</td>
  </tr>
  <tr>
    <td>Precondición</td>
    <td>El sistema debe estar energizado<br>El modulo Bluetooth debe estar energizado, conectado al sistema y  con enlace activo a un dispositivo<br>El sistema debe estar midiendo actualmente<br>El usuario debe tener la aplicación instalada en su dispositivo</td>
  </tr>
  <tr>
    <td>Flujo Básico</td>
    <td>El usuario releva los datos de entrada y de potencia desde la aplicación instalada en el dispositivo</td>
  </tr>
  <tr>
    <td>Flujo Alternativo</td>
    <td>La aplicación no se encuentra conectada al módulo</td>
  </tr>
</tbody>
</table>

## **2.3 Descripción de los Módulos del sistema**
A continuación se mencionará una breve descripción de los módulos utilizados, tanto comerciales como hechos a medida para el proyecto, donde se hará enfasís en estos últimos para lograr que el lector comprenda su utilización y criterios de diseño.

## **2.3.1 Alimentación**

El sistema se alimenta mediante los bornes de alimentación de la placa de desarrollo Nucleo-F429ZI la cual se alimenta del USB utilizado para la comunicación por consola. Se utilizan los rieles de 3,3 V para los módulos de tensión y corriente, el de frecuencia y fase y el de tarjeta SD. Por otro lado, se utiliza el riel de alimentación de 5 V para el módulo LCD y el módulo Bluetooth.

Se tomó especial cuidado para verificar que la suma de los consumos de los distintos módulos no supere la salida máxima admisible por la placa de desarrollo. 

## **2.3.2 Microcontrolador** 

El microcontrolador seleccionado es el STM32F429ZI, contenido en la placa de desarrollo Nucleo-F429ZI. Se eligió la opción en placa de desarrollo debido a la facilidad y rapidez de prototipado, y a la gran disponibilidad de interfaces de comunicación, necesarias para la cantidad de módulos impelementados.

Otra razon para la elección de la placa de desarrollo es la interfaz UART para mayor faciliadad de comunicación USB con el software en el que se realizó la implementación, y la habilidad de debug que esta contiene.

## **2.3.3 Sensor de Corriente** 

El sensor de corriente elegído para el proyecto es el [ASC712](https://www.allegromicro.com/-/media/files/datasheets/acs712-datasheet.ashx), el cual utiliza el [Efecto Hall](https://es.wikipedia.org/wiki/Efecto_Hall) para realizar las mediciones de corriente. El dispositivo es conectado en serie con la carga a la cual se le quiere medir el consumo de corriente, y a la salida se mide una tensión que puede variar desde la alimentación negativa a la positiva.

El integrado cuenta con variantes para corrientes alternas o continuas positivas, asi como distintos rangos de corriente máxima. Adicionalmente, la salida del integrado se encuentra aislada de la conexión con la carga, evitando así la destrucción de lo conectado si ocurre un error en la linea. Se pueden encontrar módulos disponibles comercialmente, como el que se muestra a continuación:


## **2.3.4 Sensor de Tensión** 

Para el sensor de tensión se utilizó una técnica similar al de corriente, donde la salida de tensión proporcional a la tensión en la entrada se encuentra aislada de esta. En este caso se realizó con un optoacoplador, donde la tensión de entrada es rectificada y ajustada a valores apropiados para el optoacoplador elegíd. En este caso el (PC817)[https://www.farnell.com/datasheets/73758.pdf]. 


## **2.3.5 Sensor de frecuencia y fase** 

Para la detección de frecuencia y fase se utilizan las señales previamente obtenidas para las mediciones de tensión y corriente, las cuales son introducidas a dos amplificadores operacionales en modo comparador que permite obtener señales cuadradas que coinciden con los cruces por cero de las señales. 

Como se explorará mas a fondo en la sección de Firmware, si uno mide los tiempos entre los cruces por cero, sin importar las tensiones o corrientes pico, se pueden obtener valores para la frecucuencia comparando los flancos de una señal, y valroes de defasaje midiendo el tiempo entre los flancos de las dos señales.

## **2.3.6 RTC**

Prinicpalmente utilizada para anotar junto a las mediciones realizadas la fecha y hora, el modulo de reloj de tiempo real, _Real Time Clock (RTC)_, es aquel que permite contar con una presición aceptable los segundos transcurridos a partir de cierta fecha establecida.

Este se encuentra ya integrado dentro del microcontrolador, y se utilizan ciertas funciones descriptas en la sección de firmware para interactuar con él.

## **2.3.7 Módulo SD** 

Para el módulo SD se consideró uno disponible comercialmente que hace uso del protocolo SPI para almacenar los datos en una memoria no volatil. Dentro del módulo se encuentra un 'Level -shifter' que permite ser utilizado  con microcontroladores que funcionan a 5 V.

<img width="484" height="367" alt="imagen" src="https://github.com/user-attachments/assets/1b17e924-01ed-47af-956a-63283ad3710c" />

## **2.3.8 Módulo LCD 16x2** 

Otro módulo que tambien resulta disponible comercialmente es el display LCD de 16x2 caracteres. Es un módulo ampliamente utilizado y documentado en infinidad de proyectos, ya que resulta muy facul de utilizar y extremadamente versatil, permitiendo observar datos actuales de un programa en tiempo real.

<img width="492" height="380" alt="imagen" src="https://github.com/user-attachments/assets/49188155-235b-4bae-b4c7-e0957fe90444" />

Una de sus limitaciones resulta la escasa cantidad de caracteres disponibles, algo de mucha importancia en este proyecto debido a la cantidad de información a mostrar. Para ello se utilizaron 'pantallas', en las cuales muestran una cantidad de datos por unos segundos, luego en otra pantalla otros datos, y así sucesivamente. Esta técnica será explorada mas en profundidad en la sección de Firmware del módulo. 

## **2.3.9 Módulo Bluetooth** 

Por último, la adición de un módulo que admite la comunicación via bluetooth mediante dos dispositivos, en este caso el proyecto y una aplicación celular. El módulo en cuestión es el HC06:

<img width="450" height="448" alt="imagen" src="https://github.com/user-attachments/assets/07f8a7d8-b1f5-45a8-8ebe-ca0601658d5a" />

Este módulo se puede dividir en una placa portadora, con componentes auxiliares como reguladores de corriente, botones de reinicio e indicadores LED, y el microcontrolador en sí con el que uno se comunica. La comunicación con este módulo se realiza a travez del protocolo UART, con simples comandos que permiten evaluar el estado del dispositivo y su configuración mediante comandso "AT", como enviar y recibir datos vía Bluetooth a otros dispositivos.  

# **CAPÍTULO 3** 

# **Diseño e implementación** 

## **3.1 Diseño del Hardware** 

En esta sección se mostrarán los esquematicos de los distintos módulos mencionados y explicados en la sección anterior, entrando más en detalle de los criterios utilizados para el diseño. Se explciará cada módulo en su resectiva sección de manera aislada, y finalizando con un diseño integral que incluye el microcontrolador.

## **3.1.1 Diseño del sensor de Corriente** 

El diseño del sensor de corriente se muestra a continuación:

<img width="802" height="512" alt="imagen" src="https://github.com/user-attachments/assets/be0b1ba1-7ded-4df0-bd37-4407fd15bacf" />

Donde se observa la conexión a la carga a monitorear a la izquierda, junto con la salida analógica y alimentación por la derecha. El microcontrolador elegido automaticamente convierte la señal senoidal de la entrada a una señal analogica proporcional al valor de corriente, centrada en 3,3 V/2.

## **3.1.2 Diseño del sensor de Tensión** 

En el caso del módulo de tensión:

<img width="678" height="336" alt="imagen" src="https://github.com/user-attachments/assets/37be91e9-d381-4557-8469-d0e9efd5b467" />

Se puede observar el rectificador en la entrada del optoacoplador, permitiendo el correcto funcionamiento del mismo, juto con la salida nalógica aisalda. En este caso, la señal entregada es un hemiciclo de la señal senoidal utilizada para alimentar la carga, y con valor "medio" de la señal original en 0.

## **3.1.3 Diseño del sensor de frecuencia y fase** 

Debido a las distintas implementaciones de los sensores de tensión y corriente, se requieren leves diferencias en los circuitos de comparación para otener señales apropiadas a los cruces por cero:

<img width="501" height="476" alt="imagen" src="https://github.com/user-attachments/assets/1f5d7519-3b58-4dc5-9afa-e80cd82838a0" />

En el caso del comparador de corriente, se compara con la mitad del valor de alimentación, teniendo un valor positivo a la salida en el hemiciclo positivo de la corriente y 0 en el hemiciclo negativo. En el caso de la tensión, simplemente se compara con un valor levemente superior a 0. 

El comparador elegido es el [MCP6002](https://ww1.microchip.com/downloads/aemDocuments/documents/MSLD/ProductDocuments/DataSheets/MCP6001-1R-1U-2-4-1-MHz-Low-Power-Op-Amp-DS20001733L.pdf), que admite salidas 'rail to rail', es decir que la salida puede variar desde la alimentación positiva ala alimentación negativa, con una caida imperceptible en este caso. Se tomó este comparador para obtener valores de tensión apropiados para las entradas digitales del microcontrolador y evitar errores de niveles que puedan provocar falsos disparos o ningun disparo en absoluto.

## **3.1.4 Diseño del módulo SD**

Para los módulos comericales como el de la tarjeta SD, el display y el módulo bluetooth, simplemente alcanza con realizar las conexiones adecuadas a los puertos correspondientes del microcontrolador. En el caso del móludo SD, la interfaz SPI:

<img width="409" height="309" alt="imagen" src="https://github.com/user-attachments/assets/040a3fdb-a171-49ae-9444-9b8819d43ffb" />

## **3.1.5 Diseño del módulo LCD 16x2** 

Para el LCD, es necesario realizar las conexiones de los 4 bits de datos (D7 a D4) los pines RW, E y las alimentaciones, junto con un potenciometro para modificar el brillo del display.

<img width="634" height="533" alt="imagen" src="https://github.com/user-attachments/assets/75a3de41-6567-4e09-9ee4-f96bfb301d37" />

## **3.1.6 Diseño del módulo Bluetooth** 

De forma similar a los anteriores, se realizan las conexiones correspondientes a los pines del microcontrolador, ene ste caso con protocolo UART.

<img width="452" height="245" alt="imagen" src="https://github.com/user-attachments/assets/29930976-ef54-41af-be78-4699cadee40d" />


## **3.1.7 Diseño del hardware con la placa NUCLEO-F429ZI** 

Uniendo todos estos módulos, se realiza el esquematico completo, integrando el microcontrolador, que tambien es el que provee la alimentación al circuito.

<img width="483" height="897" alt="imagen" src="https://github.com/user-attachments/assets/4bca810f-f257-48d9-8191-4d57b464bdb8" />

En base al esquematico, podemos realizar una especie de "shield" para el microcontrolador:

<img width="759" height="539" alt="imagen" src="https://github.com/user-attachments/assets/d6e62dbf-cf5e-4406-8fb8-5366465629db" />

## **3.2 Diseño del Firmware** 

A continuación se describen las distintas secciones del software, separado en sus respectivos módulos:

## **3.2.1 Módulo Corriente y Tensión** 

Comenzando por los módulos de corriente y tensión, el archivo *meassurements.cpp* consiste en dos declaraciones de entradas analógicas, una para cada señal, y dos funciones para obtener dichos valores.

<img width="596" height="499" alt="imagen" src="https://github.com/user-attachments/assets/05c90af3-65a5-4d0d-b994-2dfa738644aa" />

En las funciones privadas, se puede observar como se realizan las mediciones:

<img width="886" height="648" alt="imagen" src="https://github.com/user-attachments/assets/a8a37fb8-d9b1-4414-a1e3-ec4ea2c6f017" />

En estas se muestrea la entrada por 40ms para garantizar que se obtiene al menos 1 máximo de la señal. Obtenido el máximo, se lo multiplica por un factor de conversión definido por las conversiones realizadas.

## **3.2.2 Módulo frecuencia y fase** 

En el módulo *timing.cpp* se tienen las entradas digitales de los cruces por cero de la tensión y de la corriente, a las cuales se las declara como interrupciones por flanco ascendente en la inicialización, como tambien un _timer_ que servirá para medir las distancias de tiempo entre pulsos.

<img width="574" height="838" alt="imagen" src="https://github.com/user-attachments/assets/2781d5e5-5305-41f5-919c-649d019ac565" />

Para calcular los valores de frecuencia, utilizamos una función privada que, comienza almacenando el tiempo transcurrido entre pulsos, seguido de evaluar si ya ocurrió una interrupción. Esto último sirve para diferenciar entre una medición entre dos pulsos de una misma señal, o de una señal con la otra. Esta implementación asume que ambas señales tiene misma frecuencia, en caso de que esto no sea cierto, la medición será erronea edbido a un efecto de barrido.

<img width="755" height="200" alt="imagen" src="https://github.com/user-attachments/assets/afc7e57b-11fa-484f-9d46-9977e2b57cbd" />

Con el valor de la duración entre pulsos, se calcula la frecuencia a partir del perido, o el coseno del angulo entre las fases.

## **3.2.3 RTC**

Esta sección de código contiene tres funciones, una que setea la fecha y hora ingresada previamente por el usuario, una que devuelve la hora actual y la última que devuelve la fecha actual, ambas formateadas apropiadamente.

<img width="974" height="766" alt="imagen" src="https://github.com/user-attachments/assets/32057246-163c-47a4-9cdd-97314388fcc8" />

## **3.2.4 Módulo SD** 

La implementación del código para el módulo SD consiste en principio en la declaración del puerto SPI para la comunicación, el tipo de archivo. Luego, en la funcion de incialización, se intenta montar la tarjeta SD y crear un directorio, si esto resulta exitoso, se elimina el directorio y retorna _true_. En caso que ocurra un error, sele da aviso al usuario y retorna _false_.

<img width="795" height="657" alt="imagen" src="https://github.com/user-attachments/assets/a6b70d9d-ae0b-4d8b-8c3e-2c8593896342" />
<img width="598" height="404" alt="imagen" src="https://github.com/user-attachments/assets/f4219575-8f59-41d4-a4aa-77500c91ece9" />

Las funciones de lectura y escritura y borrado consisten en abrir el archivo deseado, verificar que no ocurrió un error, y leerlo, modificarlo o eliminarlo según correspona, en algunos casos mediante un buffer.

<img width="561" height="835" alt="imagen" src="https://github.com/user-attachments/assets/1ad19180-8c3c-48a2-9b6c-a2d7ea859540" />
<img width="535" height="533" alt="imagen" src="https://github.com/user-attachments/assets/7e2b9ec3-0ca2-434c-820d-adfaa779fa21" />
<img width="825" height="458" alt="imagen" src="https://github.com/user-attachments/assets/63db107b-d3ac-47e1-adfe-709b1311fd12" />

## **3.2.5 Módulo LCD 16x2** 

Para el módulo LCD, se utilizó la librería [TextLCD](https://os.mbed.com/users/simon/code/TextLCD/) publicada por SimonFord, utilizando las funciones que se describirán más adelante.

## **3.2.6 Módulo Bluetooth** 

El módulo bluetooth se comporta como una comunicación serial, donde se envían los mensajes que serán recibidos por la aplicación de celular. Cada uno de estos valores se envía con un prefijo que indica el tipo de valor que es, en caso de que se pierda un mensaje.

<img width="740" height="897" alt="imagen" src="https://github.com/user-attachments/assets/4ce46673-7d2f-4176-927a-f667177a095b" />


Adicionalmente se implementa una función tipo _ping_ que envia el comando "AT" y se espera recibir la respuesta "OK". En caso de no recibirla, se considera fallido y retorna falso.

<img width="725" height="245" alt="imagen" src="https://github.com/user-attachments/assets/8a14e6e8-0965-4628-bb21-e5a97acbc354" />

## **3.2.7 Firmware Adicional** 

Se tienen dos archivos adicionales, uno que se encarga de la comunicación por consola con el usuario y otra que se encarga del fujo básico del programa.

Comenzando por la interfaz con el usuario, se plantea una máquina de estados finitos que muestra cíclicamente los valores de tensión, corriente, frecuencia y fase por 6 segundos, o 3 refrescos de pantalla, luego muestra la fecha y hora por 2 segundos, y finaliza con mostrar en pantalla los valores de potencia total, activa y reactiva nuevamente por 6 segundos. En este último pasó, adicionalmente, se transmiten los valores actuales de linea por Bluetooth. 

<img width="686" height="784" alt="imagen" src="https://github.com/user-attachments/assets/d756b184-79dd-4ba7-a0a3-b0a4ab44995a" />
<img width="808" height="624" alt="imagen" src="https://github.com/user-attachments/assets/590ff1c4-a7a6-497d-8998-eb619194af0c" />


El resto de las funciones se encargan de mostrar los distintos valores en pantalla, utilizando las distintas funciones del módulo LCD. Finalmente, se utiliza un timer de 10s para realizar el almacenamiento de valores en la tarjeta SD.

<img width="700" height="840" alt="imagen" src="https://github.com/user-attachments/assets/d7facf90-349a-4b96-81a2-b0ec756bb947" />

Finalizando con el módulo de comunicación USB, aqui se implementan las funciones de impresión por consola para interactuar con el usuario. Comenzando por la de seteo de fecha y hora, junto con la carga de estos datos al reloj interno

<img width="998" height="650" alt="imagen" src="https://github.com/user-attachments/assets/e926b095-ac1d-4867-937b-af99ae68ac9f" />

Como la de conversión de dato tipo _float_ a _string_, correctamente formateado

<img width="789" height="335" alt="imagen" src="https://github.com/user-attachments/assets/e85c0bfd-758f-4270-a3a4-7bfa4822c949" />

Y por último, la de escritura y lectura en consola mediante un buffer de salida

<img width="878" height="258" alt="imagen" src="https://github.com/user-attachments/assets/822f2708-8c60-4774-bdee-9f0a5d78c6ce" />

## **3.3 Diseño de la aplicación y comunicación Bluetooth** 

Finalizando con la implementación de software, ahora por fuera de la plataforma, se diseñó la aplicación bluetooth en un entorno brindado por el Instituto de Tecnología de Massachusetts que permite mediante una interfaz gráfica y bloques, crear la funcionalidad completa de una aplicación. 

El entorno del [MIT App Inventor](https://appinventor.mit.edu/) consta de una interfaz que nos permite colocar los objetos con los que interactua el usario en la pantalla del dispositivo movil, como botones, etiquetas, etc, a los que luego se le agrega funcionalidad y lógica a traves de la segunda intefaz, donde se importan los distintos atributos de los bloques mencionados previamente.

En el caso de este proyecto, los objetos que se utilizarán son la conexión bluetooth que recibirá los mensajes enviados por el módulo, y etiquetas para mostrar los distintos valores recibidos.

<img width="358" height="609" alt="imagen" src="https://github.com/user-attachments/assets/344debff-757c-4842-8788-81a0beefe180" />

En la sección de "código", primero se le permite al usuario seleccionar el dispositivo con el que se quiere conectar y una vez seleccionado establece la conexión. Por otro lado se utiliza un reloj que cada 3,5s verifica si se encuentra conectado a un dispositivo, y si existen datos para recibir. En caso de que si, se recibe el dato y se evalua el prefijo para validar el tipo de variable recibida.

<img width="594" height="750" alt="imagen" src="https://github.com/user-attachments/assets/61f3b96f-b68f-40dd-8d15-457e42dead5b" />

<img width="364" height="775" alt="imagen" src="https://github.com/user-attachments/assets/2621daa0-8a90-4d8d-9a59-f6fd9046e399" />


# **CAPÍTULO 4** 

# **Ensayos y resultados** 

## **4.1 Pruebas funcionales**  

El desarrollo del trabajo se realizó durante el transcurso de 4 meses, donde se tomó la idea principal y subdividió en 4 partes, donde se continuaban agregando los módulos previemanete mencionados. A continucación se listan los distintos readme donde se indican los módulos implementados junto con un link al README donde se encuentra el link al vdeo mostrando el funcionamiento.

- [README_TP2.md](https://github.com/norfanudis/SE_TP_1c2025_Entregas_TP/blob/SE_TP_1c2025_TP2/README.md) : Sensor de corriente y  tensión, Módulo Display 16x2 y RTC
- [README_TP3.md](https://github.com/norfanudis/SE_TP_1c2025_Entregas_TP/blob/Entregas-TP-Final/README.md) : Sensor de frecuncia y fase, Módulo SD
- [README_TP_FINAL.md](https://github.com/norfanudis/SE_TP_1c2025_Entregas_TP/blob/Entrega-TP-Final-Rev1/README.md) : Módulo Bluetooth, aplicación celular

## **4.2 Cumplimiento de requisitos**  

Finalizado el trabajo, se verificaron los requisitos mencionados en la sección 2.1 y se evaluó el estado de los mismos:

<table><thead>
  <tr>
    <th>Grupo de Req.</th>
    <th>ID del Req.</th>
    <th>Descripción</th>
    <th>Estado</th>
  </tr></thead>
<tbody>
  <tr>
    <td>1. Entradas</td>
    <td>1.1</td>
    <td>El sistema contiene entradas para la tensión, la corriente y para las señales de cruce por cero</td>
    <td>CUMPLIDO</td>
  </tr>
  <tr>
    <td></td>
    <td>1.2</td>
    <td>El sistema realiza las mediciones de las entradas analógicas y digitales</td>
    <td>CUMPLIDO</td>
  </tr>
  <tr>
    <td>2. Modos</td>
    <td>2.1</td>
    <td>El sistema tendrá un modo de medición continuo</td>
    <td>CUMPLIDO</td>
  </tr>
  <tr>
    <td></td>
    <td>2.1.1</td>
    <td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;El sistema medirá el valor de tensión por la entrada analógica A1</td>
    <td>CUMPLIDO</td>
  </tr>
  <tr>
    <td></td>
    <td>2.1.2</td>
    <td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;El sistema medirá el valor de corriente por la entrada analógica A2</td>
    <td>CUMPLIDO</td>
  </tr>
  <tr>
    <td></td>
    <td>2.1.3</td>
    <td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;El sistema medirá el defasaje entre las señales de cruce por cero de las entradas digitales (D14 y D15)</td>
    <td>CUMPLIDO</td>
  </tr>
  <tr>
    <td></td>
    <td>2.1.4</td>
    <td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;El sistema medirá la frecuencia con el periodo de la señal de cruce por cero de tensión D15</td>
    <td>CUMPLIDO</td>
  </tr>
  <tr>
    <td></td>
    <td>2.1.5</td>
    <td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;El sistema calculará el consumo de potencia multiplicando la corriente con la tensión</td>
    <td>CUMPLIDO</td>
  </tr>
  <tr>
    <td></td>
    <td>2.2</td>
    <td>El sistema iniciará en modo configuración</td>
    <td>CUMPLIDO</td>
  </tr>
  <tr>
    <td></td>
    <td>2.2.1</td>
    <td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;El sistema solicitará por consola el seteo de fecha y hora</td>
    <td>CUMPLIDO</td>
  </tr>
  <tr>
    <td></td>
    <td>2.2.2</td>
    <td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;El sistema solicitará por consola el tipo de archivo deseado</td>
    <td>CUMPLIDO</td>
  </tr>
  <tr>
    <td>3. Display</td>
    <td>3.1</td>
    <td>El display mostrará el mensaje inicial que notificará al usuario que requiere configurar el sistema por consola</td>
    <td>CUMPLIDO</td>
  </tr>
  <tr>
    <td></td>
    <td>3.2</td>
    <td>El display mostrará los valores actuales de tensión, corriente, frecuencia y defasaje por 6 segundos</td>
    <td>CUMPLIDO</td>
  </tr>
  <tr>
    <td></td>
    <td>3.3</td>
    <td>El display mostrará la fecha y hora por 2 segundo</td>
    <td>CUMPLIDO</td>
  </tr>
  <tr>
    <td></td>
    <td>3.4</td>
    <td>El display mostrará los valores actuales de potencia total, activa y reactiva por 6 segundos</td>
    <td>CUMPLIDO</td>
  </tr>
  <tr>
    <td>4. SD</td>
    <td>4.1</td>
    <td>El sistema almacenará el estado actual de las entradas en la tarjeta SD cada 10 segundos</td>
    <td>CUMPLIDO</td>
  </tr>
  <tr>
    <td></td>
    <td>4.2</td>
    <td>El sistema permitirá via comando de consola leer las ultimas 10 mediciones guardadas</td>
    <td>INCOMPLETO</td>
  </tr>

  <tr>
    <td>5. Modulo Bluetooth</td>
    <td>5.1</td>
    <td>El sistema le comunicará al módulo Bluetooth el estado de las entradas cada 14 segundos</td>
    <td>CUMPLIDO</td>
  </tr>
  <tr>
    <td></td>
    <td>5.2</td>
    <td>El modulo Bluetooth establecerá conexión con una aplicación de celular para mostrar los datos enviados</td>
    <td>CUMPLIDO</td>
  </tr>
  <tr>
    <td>6. Alimentación</td>
    <td>6.1</td>
    <td>El sistema puede estar alimentado por USB y realizar la comunicación serie</td>
    <td>CUMPLIDO</td>
  </tr>
  <tr>
    <td></td>
    <td>6.2</td>
    <td>El sistema puede estar alimentado externamente</td>
    <td>CUMPLIDO</td>
  </tr>
  <tr>
    <td>7. Fecha de Entrega</td>
    <td>7.1</td>
    <td>El sistema se desarrollará en el lapso de un mes</td>
    <td>CUMPLIDO</td>
  </tr>
  <tr>
    <td>8. Costo</td>
    <td>8.1</td>
    <td>El sistema no costará mas de AR$200.000 (Placa NUCLEO Incluida)</td>
    <td>CUMPLIDO</td>
  </tr>
  <tr>
    <td>9. Documentación</td>
    <td>9.1</td>
    <td>El prototipo está acompañado de su lista de componentes, esquemáticos, diagramas de conexión y un repositorio con el código de implementación</td>
    <td>CUMPLIDO</td>
  </tr>
</tbody></table>

Se observa que en su mayoría, estos se encuentran completos, salvo la impresión de los datos guardados en la tarjeta SD.


## **4.3 Comparación con otros sistemas similares**   

Como se hace mención en la sección de análisis de necesidad, la idea del proyeto realizado se encuentra actualmente en el mercado, principalmente en el entorno industrial. Una diferencia que se encontró respecto a estos es la utilización de una tarjeta SD para el almacenamiento de datos y eventualmente relevar esos datos desde la aplicación o desde la consola.

## **4.4 Documentación del desarrollo realizado**

La siguiente tabla incluye la documentación realizada en las distintas etapas del proyecto

| Nombre                 | Fecha de Finalización     | Referencia         |
|------------------------|---------------------------|--------------------|
| Trabajo Práctico 1    | 5 de Abril del 2025    | README_TP1.md      |
| Trabajo Práctico 2    | 16 de Mayo del 2025    | README_TP2.md      |
| Trabajo Práctico 3    | 6 de Junio del 2025  | README_TP3.md      |
| Requisitos y casos   | 21 de Junio del 2025  | Readme_requisitos_y_casos.md      |
| Informe de Avance   | 21 de Junio del 2025  | Informe de Avance del Trabajo Final.md      |
| Trabajo Práctico Final | 16 de Julio del 2025   | README_TP_FINAL.md |
| Memoria del trabajo | 16 de Julio del 2025   | Memoria del trabajo final.md |

# **CAPÍTULO 5** 

# **Conclusiones** 

## **5.1 Resultados obtenidos**
 
Duante el transcurso del trabajo, se logró implementar la mayoría de los objetivos pretendidos con posibles expansiones o modificaciones a futuro, permitiendo así obtener un excelente proyecto para comenzar desarrolloes en plataformas mas avanzadas que las convencionales con todo lo que eso conlleva. La incorporación de modulos disponibles comercialmente, asi como circuitos diseñados particularmente para este, también permite interactuar tanto con el software como el hardware, lo que lo hace un sistema integramente embebido.

Adicionalmente, debido al diseño modular, el código y las implementaciones utilizadas pueden ser migradas facilmente a otros proyectos nuevos, o para expansiones en otros.

La plataforma utilizada resulta en igual partes práctica y facil de realizar implementaciones de baja escala, como compleja con infinidad de posibiliadades de interacción con la misma debido a la cantidad de puertos e interfaces que contiene.

## **5.2 Próximos pasos**    

Este trabajo puede resultar una buena base para una expansión, agragando distintas caracteristicas y funcionalidades. A continuación algunas posibles alternativas:

- Adcicionar salidas de monitoreo, replicando los circuitos de sensado de variables para evaluar multiples consumos y realizar el monitoreo de los mismos.
- Adicion de funciones en la aplicación bluetooth. Actualmente solo permite relevar los datos obtenidos, pero se podría implementar un boton para realizar el guardado en la SD de una lectura en particular. También se podrían agregar gráficos que le permitan al usuario obtener mas información a lo largo del tiempo.
- No necesariamente una adición, pero se podría implementar un portal web que permita obtener los datos de forma similar que la aplicación bluetooth, pero disponible para cualquier usuario con credenciales aropiadas.
- Modificación del display LCD de 16x2 a uno mas pequeño para facilitar la integración a un panel eléctrico o máquina
- Agregar mayor funcionalidad a la interacción con el usuario por consola, permitiendo tanto realizar modificaciones en la configuración, como establecer alarmas de consumo.

Cada modificación se centra en uno o mas módulos particulares, pudiendo realizar estos cambios de forma progresiva, y obteniendo un proyecto mucho mas maduro.

# **Bibliografía** 

\[1\] A Beginner’s Guide to Designing Embedded System Applications on Arm Cortex-M Microcontrollers, por Ariel Lutenberg, Pablo Gomez y Eric Pernia. [Online]. Available: https://www.arm.com/resources/education/books/designing-embedded-systems

\[2\] HM-10: Use An Arduino To Talk To A HM-10 [Online]. Available: https://www.martyncurrey.com/hm-10-use-an-arduino-to-talk-to-the-hm-10/

\[3\] The Complete Guide To The HC-06 [Online]. Available: https://www.martyncurrey.com/the-complete-guide-to-the-hc-06/

\[4\] Manual de usuario NUCLEO-f429ZI [Online]. Available: https://www.st.com/en/evaluation-tools/nucleo-f429zi.html

\[5\] The MIT App Inventor Library: Documentation & Support [Online]. Available: https://appinventor.mit.edu/explore/library

\[6\] STM32 Nucleo-144 development board with STM32F429ZI MCU, supports Arduino, ST Zio and morpho connectivity https://www.st.com/en/evaluation-tools/nucleo-f429zi.html#documentation
