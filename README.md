# greenhouse_project

### Členové týmu

* [Martin Kousal](https://github.com/mkousal)
* [Jiří Navrátil](https://github.com/georgenavratil)
* [Tomáš Kříčka](https://github.com/tomaskricka)


Odkaz na GitHub repozitář:

[https://github.com/mkousal/greenhouse_project](https://github.com/mkousal/greenhouse_project)

### Table of contents

* [Cíle projektu](#objectives)
* [Popis hadware](#hardware)
* [Popis knihoven](#libs)
* [Hlavní aplikace](#main)
* [Video](#video)
* [Reference](#references)

<a name="objectives"></a>

## Cíle projektu

Cílem projektu je navrhnout chytrý skleník, který bude za měnících podmínek uchovávat ve skleníku co nejlepší podmínky pro pěstování zeleniny.


<a name="hardware"></a>

## Popis hardaware

V projektu používáme:
* Arduinu UNO - mikrocontroler s AVR procesorem [Atmega283P](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)
* senzor teploty a vlhkosti - [DHT12](https://robototehnika.ru/file/DHT12.pdf) komunikuje s Arduinem přes I2C sběrnici
* senzor vlhkosti půdy -  [capacitive soil moisture sensor v1.2](https://www.sigmaelectronica.net/wp-content/uploads/2018/04/sen0193-humedad-de-suelos.pdf) změnou kapacity měří vlhkost půdy
* intenzita světla - [GL5539 photoresistor](https://www.kth.se/social/files/54ef17dbf27654753f437c56/GL5537.pdf) změnou odporu měří intentitu světla
* znakový display 2*16 - [LCD keypad shield]() využívá I2C sběrnici
* relé modul - [4 relay shield, Calatex](https://www.distrelec.cz/Web/Downloads/_t/ds/103030009_eng_tds.pdf) spínáním relé jsou ovládáno zavlažování, světlo, ventilace
 

<a name="libs"></a>

## Popis knihoven

Write your text here.

<a name="main"></a>

## Hlavní aplikace

![Flow_1](images/flow_1.svg)
![Flow_2](images/flow_2.svg)

<a name="video"></a>

## Video

Write your text here

<a name="references"></a>

## Reference

1. Write your text here.