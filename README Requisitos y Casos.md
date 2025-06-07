Imagen FIUBA

# **Sisitema de Monitoreo Eléctrico**

 

**Autor: Nicolás Orfanudis**

**Padrón: 102410**

**Fecha: 2do cuatrimestre 2024**

 
### **1\. Selección del proyecto a implementar**

#### **1.1 Análisis de proyectos**

En esta sección se establece qué aspectos serán considerados a la hora de decidir el proyecto a realizar. A su vez se establece un sistema de puntos y pesos que servirán para ponderar cada aspecto y facilitar el proceso de decisión. Se considera que los pesos relativos pueden variar entre 1 (el más bajo) y 10 (el más alto). A continuación, se detalla la elección de cada peso por parámetro.

 Los parámetros considerados son: 
1. Disponibilidad del hardware (peso : 10) : Se considera con el peso relativo más alto por un motivo simple, de no poder contar con la parte física de la implementación es imposible la realización del proyecto.     
2. Utilidad del proyecto (peso : 5) : Se pondera este parámetro con un peso apenas superior a lo intermedio, se determina como el nivel de practicidad y satisfacción que le puede otorgar al usuario final del producto o la solución. 
3. Tiempo de implementación (peso : 8) Se considera también como un aspecto importante dado a que se pretende que el proyecto pueda ser realizado en el periodo de tiempo con el que se cuenta desde el desarrollo de este informe hasta la fecha de cierre de notas del actual cuatrimestre (un mes aproximadamente). 

Los proyectos a analizar son los siguientes:
1. Sistema de Monitoreo Eléctrico
2. Estación Meteorológica 

El sistema de monitoreo eléctrico consiste en la medición de tensión de linea, junto con la corriente consumida, y un módulo que permite medir la frecuencia de la linea, junto con el defasaje o coseno $phi$. Con los datos sensados, realiza las conversiones apropiadas y los cálculos de potencia total, activa y reactiva consumida. Toda esa información, junto con la hora y el día actual, son presentadas en distintas formas al usuario. Una de las formas consiste en mostrarla a travez de una pantalla LCD de 16 caracteres y 2 filas que alterna entre pantallas con distinta información. Otra forma de relevar la información es mediante una tarjeta SD conectada al dispositivo que almacena las mediciones realizadas junto con la fecha y hora de la medición. Por último, la información tambien se comunica en tiempo real via wifi a una página que muestra el estado actual del sistema junto con las variables.

Realizada esta breve introducción, resta asignarle valores a los parámetros planteados en la sección anterior. Respecto a la disponibilidad de hardware, el sistema utiliza un módulo disponible comercialmente para la medición de corriente y requiere un circuito relativamente básico para la medición de tensión, utilizando componentes disponibles en el mercado. Junto con el resto de los perifericos, como el display o el módulo SD, no resulta dificil la implementación del proyecto en cuanto al hardware, por lo que se le asignó un puntaje de 8. Respecto a la utilidad del proyecto resulta bastante versatil ya que permite el monitoreo de un consumo domiciliario hasta el de uno industrial ya que los módulos son facilmente reemplazables por otros de mayor consumo y en el software solo requiere cambiar constantes de conversión. Adicional a esto, un mayor control sobre el consumo permite un eventual análisis del mismo y una posibilidad de ahorro de energía y dinero. Por todo lo mencionado, se le dió un pntaje de Utilidad de 9. 
Por último, el tiempo de implementación resulta rápido debido a que los módulos para realizar las mediciones o almacenar y mostrar los datos son de uso común y se pueden utilizar documentación e implementaciones ya realizadas, agilizando el proceso de desarrollo. Basado en ese análisis, se le asigna un puntaje de 7.

El siguiente proyecto propuesto consiste en una estación meteorológica que permite levantar datos ambientales, como la calidad de aire, velocidad de viento, temperatura, humedad, entre otros. De la misma manera que el proyecto anterior, este tambien permite el logeo de datos en memoria SD y la comunicación via Wifi de la información, permitiendo relevarla de forma remota. 

Si bien los proyectos resultan similares en la cuestión de relevo de datos, la utilización de módulos mas complejos para sensar variables abientales complejiza el desarrollo del proyecto. Para mediciones de viento se requieren sensores específicos de viento que necesitan ser calibrados. Por otro lado, si se quisieran agregar sensores inalambricos para medir humedad o temperatura en lugares mas remotos, dificulta la implementación del proyecto. Por esta razon se decidió asignarle un puntaje de disponibilidad de hardware de 5. Respecto a la utilidad, una estación meteorológica encuentra su uso en ambientes agropecuarios o incluso aeropuertos de baja escala, pero no tiene un uso tan domiciliario como el proyecto anterior, reduciendo levemente su puntaje a un 6. 
Finalmente, el tiempo de implementación es similar al mencionado para el otro proyecto, ya que también consiste de módulos y interfaces parecidas, con la complejidad adicional de implementación y calibración de los sensores de variables ambientales, resultando en un puntaje de 6.

Recopilando lo mencionado en la siguiente tabla:

<table><thead>
  <tr>
    <th>Proyecto</th>
    <th></th>
    <th>Disponibilidad de Hardware<br>(peso: 10)</th>
    <th>Utilidad del poyecto <br>(peso: 5)</th>
    <th>Tiempo de Implementación <br>(peso: 8)</th>
    <th>Puntaje total</th>
  </tr></thead>
<tbody>
  <tr>
    <td rowspan="2">Sistema de monitoreo eléctrico</td>
    <td>Puntaje individual</td>
    <td>8</td>
    <td>9</td>
    <td>7</td>
    <td></td>
  </tr>
  <tr>
    <td>Puntaje Ponderado</td>
    <td>80</td>
    <td>45</td>
    <td>56</td>
    <td>181</td>
  </tr>
  <tr>
    <td rowspan="2">Estación Meteorológica</td>
    <td>Puntaje individual</td>
    <td>5</td>
    <td>6</td>
    <td>6</td>
    <td></td>
  </tr>
  <tr>
    <td>Puntaje Ponderado</td>
    <td>50</td>
    <td>30</td>
    <td>48</td>
    <td>128</td>
  </tr>
</tbody>
</table>

<p align="center"><em>Comparación de proyectos</em></p>

#### **1.2 Selección de proyecto**

En base al análisis realizado y a los puntajes obtenidos, se decidió avanzar con el proyecto del sistema de monitoreo de consumo eléctrico. Continuando la breve introducción mencionada en la sección anterior, se procede a detallar mas en profundidad el funcionamiento y desarrollo del proyecto. Comenzando por el diagrama en bloques del proyecto:

%%DIAGRAMA EN BLOQUES

Como se mencionó, el sistema consiste en una placa de desarrollo NUCLEO-F429ZI, junto a tres módulos para el sensado de las variables eléctricas. El módulo de tensión permite obtener una señal analógica proporcional a la tensión de linea, con valores dentro del rango tolerable de la entrada del microcontrolador. Esta conversión se realiza mediante un rectificador de onda completo, junto con un optoacoplador para aisalar ambos sistemas, resultado en una mayor seguridad eléctrica. 
De manera similar, la corriente es medida mediante un módulo basado en el [ASC712](https://www.allegromicro.com/-/media/files/datasheets/acs712-datasheet.ashx), que permite medición de corriente aislada mediante el [Efecto Hall](https://es.wikipedia.org/wiki/Efecto_Hall), también asegurando mayor seguridad para el usuario. Tanto la señal de tensión como de corriente ingresan por puerto analógico del microcontrolador, obteniendo asi los valores RMS de tensión y corriente
Para las mediciones de frecuencia y defasaje, o coseno $\phi$, se toman las mismas señales analógicas de los senores de corriente y tensión y se las compara mediante un amplificador operacional [MCP6002](https://ww1.microchip.com/downloads/aemDocuments/documents/MSLD/ProductDocuments/DataSheets/MCP6001-1R-1U-2-4-1-MHz-Low-Power-Op-Amp-DS20001733L.pdf) para así obtener una señal cuadrada, cuyo flanco ascendente coincide con los cruces por cero de las señales de tensión y corriente. Mediante la utilización de interrupciones por flanco del microcontrolador y un timer, se puede medir el tiempo entre el flanco de tensión y el de corriente para obtener el defasaje, y el tiempo entre dos flancos de tensión para obtener la corriente. Para el correcto funcionamiento del sistema ambas señales deben tener la misma frecuencia, algo que en una red eléctrica es esperable.

Realizadas estas mediciones y, junto a la utilziación del RTC (Real Time Clock) interno, son procesadas por el microcontrolador para obtener las variables de la red como la tensión, corriente, potencia total, activa y reactiva, frecuencia y defasaje o coseno $\phi$. 

Para el relevamiento de estos datos se utiliza un display LCD de 16x2 caracteres en donde la información se muestra de forma cíclica en distintas pantallas. Adicional al LCD, los datos son almacenados en un archivo en una tarjeta SD para luego ser exportado al software de análisis de elección y son enviados por Wifi con la ayuda del módulo ESP32, los cuales son enviados a un servidor Web y mostrados en un portal que se puede acceder desde cualquier navegador.  

Además de la interfaz del display, se hace uso de los LEDs ya integrados en la placa de desarrollo Nucleo para comunicar el estado actual del sistema. Ya que estos LEDs se encuentran conectados a los puertos de salida, estos se pueden colocar externamente en el caso de diseñar una envolvente para el proyecto.

Por último, el sistema utiliza comunicación por puerto serie UART para la configuración inicial de fecha y hora y la elección de formato de archivo de salida, permitiendo elegir entre datos legibles y valores separados por com (.csv), admitiendo también una modificación de la configuración una vez ya iniciado el sistema, tambien mediante la consola.


 
### **2\. Elicitación de requisitos y casos de uso**

#### **2.1 Productos en el mercado**

El concepto de medir consumo y variables eléctricas no es innovador y existe bastante competencia para este tipo de productos. Lo que destaca este desarrollo de la competencia es, por un lado, la habilidad de guardar los datos en una memoria SD para luego relevarlos, y también las configuraciones posibles para distintos consumos de tensión o corriente.

El primer ejemplo es un producto como el [MM2D-65](https://mail.bawelectric.com/imagenes/contenidos/2023-08/283-mm2d-65-manual.pdf) que realiza la medición de las variables mencionadas, pero no admite comunicación a internet o almacenamiento de datos en memorias externas, solo muestra los datos en una pantalla integrada. Estos se encuentran en el rango de los AR$45.000 y AR$65.000

Otro producto mas complejo, ahora si con comunicación via wifi, LAN o bluetooth es el [EM-50](https://www.digitalbaytech.com/es/products/shelly-pro-em-50-smart-din-rail-2-channel-single-phase-energy-meter-wi-fi-lan-and-bluetooth-connection?utm_content=&utm_term=&gad_source=1&gad_campaignid=20122675672&gbraid=0AAAAApF22wW701be59viJB4lXsergzUJo&gclid=EAIaIQobChMIh5LrgordjQMVip5aBR2niQFREAQYASABEgJ2bfD_BwE) de Shelly, con un costo de US$81.49 permite el monitoreo remoto de la red eléctrica monofásica. A diferencia del proyecto, o del ejemplo de BAW, este no cuenta con pantalla para leer los datos en tiempo real, pero si cuenta con memoria interna de hasta 60 días para guardar las mediciones.

Como los ejemplos mostrados, existen bastantes alternativas con distintas prestaciones cada uno, demostrando que es una idea que se encuentra ya implementada, pero no todas cuentan con las mismas prestaciones, incluso las prestaciones ofrecidas por el proyecto a desarrollar.

<table><thead>
  <tr>
    <th>Caracteristicas</th>
    <th>BAW MM2D-25</th>
    <th>Shelly Pro EM-50</th>
  </tr></thead>
<tbody>
  <tr>
    <td>Conexionado</td>
    <td>Bornera</td>
    <td>Bornera</td>
  </tr>
  <tr>
    <td>Valores medidos</td>
    <td>Corriente, tensión, energía, potencia, frecuencia, Factor de potencia</td>
    <td>Corriente, tensión, energía, potencia, Factor de potencia</td>
  </tr>
  <tr>
    <td>Valores Máximos</td>
    <td>276V, 65A</td>
    <td>260V, 50A</td>
  </tr>
  <tr>
    <td>Conectividad</td>
    <td>Ninguna</td>
    <td>Ethernet, Wifi, Bluetooth</td>
  </tr>
  <tr>
    <td>Memoria</td>
    <td>Ninguna</td>
    <td>60 días (mediciones cada 1 minuto)</td>
  </tr>
  <tr>
    <td>Interfaz de usuario (propia)</td>
    <td>Pantalla LCD para los datos</td>
    <td>Indicadores de conexión</td>
  </tr>
  <tr>
    <td>Configuración</td>
    <td>Tara de energía</td>
    <td>Configuración de conexión y protocolos</td>
  </tr>
  <tr>
    <td>Montaje</td>
    <td>Riel DIN</td>
    <td>Riel DIN</td>
  </tr>
  <tr>
    <td>Precio</td>
    <td>AR$ 45.000 - 65.000</td>
    <td>US$ 81.49</td>
  </tr>
</tbody></table>

#### **2.2 Requisitos iniciales**

A continuación, la tabla de requisitos iniciales, junto con su ID y descripción

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
    <td></td>
    <td>2.2.3</td>
    <td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;El sistema solicitará por consola las credenciales de la red para informar al modulo Wifi</td>
  </tr>
  <tr>
    <td></td>
    <td>2.2.4</td>
    <td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;El sistema le comunicará al usuario la IP del servidor con la información de las entradas</td>
  </tr>
  <tr>
    <td>3. Display</td>
    <td>3.1</td>
    <td>El display mostrará el mensaje inicial que notificará al usuario que requiere configurar el sistema por consola</td>
  </tr>
  <tr>
    <td></td>
    <td>3.2</td>
    <td>El display mostrará los valores actuales de tensión, corriente, frecuencia y defasaje por 3 segundos</td>
  </tr>
  <tr>
    <td></td>
    <td>3.3</td>
    <td>El display mostrará la fecha y hora por 1 segundo</td>
  </tr>
  <tr>
    <td></td>
    <td>3.4</td>
    <td>El display mostrará los valores actuales de potencia total, activa y reactiva por 3 segundos</td>
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
    <td>5. Modulo Wifi</td>
    <td>5.1</td>
    <td>El sistema le comunicará al módulo Wifi el estado de las entradas cada 1 segundo</td>
  </tr>
  <tr>
    <td></td>
    <td>5.2</td>
    <td>El modulo wifi establecerá un servidor web que permita ver el ultimo estado de las entradas</td>
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


#### **1.2 Selección de proyecto**

Por último, se listan 3 posibles casos de uso para este proyecto

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
    <td>El usuario desea leer los datos de la tarjeta SD por consola</td>
  </tr>
  <tr>
    <td>Precondición</td>
    <td>El sistema debe estar energizado<br>El sistema debe estar conectado a la PC via USB<br>Debe haber una tarjeta SD conectada correctamente al sistema<br>Debe existir un archivo con mediciones guardadas en la tarjeta SD</td>
  </tr>
  <tr>
    <td>Flujo Básico</td>
    <td>El usuario ingresa el comando para leer el archivo y las lineas se imprimen por consola</td>
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
    <td>El usuario desea leer los datos de entrada mediante portal web</td>
  </tr>
  <tr>
    <td>Precondición</td>
    <td>El sistema debe estar energizado<br>El modulo Wifi debe estar energizado, conectado al sistema y conectado a una red<br>El sistema debe estar midiendo actualmente<br>El sistema debe estar conectado a la PC vía USB</td>
  </tr>
  <tr>
    <td>Flujo Básico</td>
    <td>El usuario ingresa mediante navegador al servidor creado por el módulo Wifi y releva los datos de entrada</td>
  </tr>
  <tr>
    <td>Flujo Alternativo</td>
    <td>El modulo Wifi no se encuentra energizado o conectado y da aviso por consola al usuario</td>
  </tr>
</tbody>
</table>
