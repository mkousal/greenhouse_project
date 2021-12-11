EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:+5V #PWR03
U 1 1 61578229
P 4050 4200
F 0 "#PWR03" H 4050 4050 50  0001 C CNN
F 1 "+5V" H 4065 4373 50  0000 C CNN
F 2 "" H 4050 4200 50  0001 C CNN
F 3 "" H 4050 4200 50  0001 C CNN
	1    4050 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 4400 4050 4200
Wire Wire Line
	3350 5100 3300 5100
Text GLabel 3300 5100 0    50   Input ~ 0
SER
Text GLabel 3300 5300 0    50   Input ~ 0
RCLK
Text GLabel 3300 5200 0    50   Input ~ 0
SRCLK
Wire Wire Line
	3350 5300 3300 5300
Wire Wire Line
	3350 5200 3300 5200
Connection ~ 5750 5700
Wire Wire Line
	5750 5500 5750 5700
Connection ~ 5750 5900
Wire Wire Line
	5750 5900 5750 5700
Wire Wire Line
	5350 5500 5750 5500
Wire Wire Line
	4350 5500 4950 5500
$Comp
L Switch:SW_Push SW2
U 1 1 61766926
P 5150 5500
F 0 "SW2" H 5250 5600 50  0000 C CNN
F 1 "SW_Push" H 4950 5600 50  0000 C CNN
F 2 "" H 5150 5700 50  0001 C CNN
F 3 "~" H 5150 5700 50  0001 C CNN
	1    5150 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 5700 5750 5700
Wire Wire Line
	4350 5700 4950 5700
$Comp
L Switch:SW_Push SW3
U 1 1 61766270
P 5150 5700
F 0 "SW3" H 5250 5800 50  0000 C CNN
F 1 "SW_Push" H 4950 5800 50  0000 C CNN
F 2 "" H 5150 5900 50  0001 C CNN
F 3 "~" H 5150 5900 50  0001 C CNN
	1    5150 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 5900 5750 5900
Wire Wire Line
	4350 5900 4950 5900
Wire Wire Line
	1700 6100 1700 6800
Wire Wire Line
	2800 6100 3350 6100
Wire Wire Line
	1950 6100 1700 6100
$Comp
L power:GND #PWR01
U 1 1 615748BB
P 1700 6800
F 0 "#PWR01" H 1700 6550 50  0001 C CNN
F 1 "GND" H 1705 6627 50  0000 C CNN
F 2 "" H 1700 6800 50  0001 C CNN
F 3 "" H 1700 6800 50  0001 C CNN
	1    1700 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 6100 2500 6100
$Comp
L Device:LED D4
U 1 1 6157240B
P 2100 6100
F 0 "D4" H 2050 6300 50  0000 L CNN
F 1 "LED_D1" H 2000 6200 50  0000 L CNN
F 2 "" H 2100 6100 50  0001 C CNN
F 3 "~" H 2100 6100 50  0001 C CNN
	1    2100 6100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 6156557A
P 2650 6100
F 0 "R4" V 2443 6100 50  0000 C CNN
F 1 "330" V 2534 6100 50  0000 C CNN
F 2 "" V 2580 6100 50  0001 C CNN
F 3 "~" H 2650 6100 50  0001 C CNN
	1    2650 6100
	0    1    1    0   
$EndComp
Wire Wire Line
	3850 6700 3850 6800
Wire Wire Line
	5750 6300 5750 5900
$Comp
L power:GND #PWR04
U 1 1 61552DD9
P 5750 6300
F 0 "#PWR04" H 5750 6050 50  0001 C CNN
F 1 "GND" H 5755 6127 50  0000 C CNN
F 2 "" H 5750 6300 50  0001 C CNN
F 3 "" H 5750 6300 50  0001 C CNN
	1    5750 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 6700 3750 6500
Wire Wire Line
	3850 6700 3750 6700
Wire Wire Line
	3850 6700 3850 6500
Connection ~ 3850 6700
Wire Wire Line
	3950 6700 3950 6500
Wire Wire Line
	3850 6700 3950 6700
$Comp
L power:GND #PWR02
U 1 1 6154E886
P 3850 6800
F 0 "#PWR02" H 3850 6550 50  0001 C CNN
F 1 "GND" H 3855 6627 50  0000 C CNN
F 2 "" H 3850 6800 50  0001 C CNN
F 3 "" H 3850 6800 50  0001 C CNN
	1    3850 6800
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 6154D65D
P 5150 5900
F 0 "SW1" H 5250 6000 50  0000 C CNN
F 1 "SW_Push" H 4950 6000 50  0000 C CNN
F 2 "" H 5150 6100 50  0001 C CNN
F 3 "~" H 5150 6100 50  0001 C CNN
	1    5150 5900
	1    0    0    -1  
$EndComp
$Comp
L MCU_Module:Arduino_UNO_R3 A1
U 1 1 6154C64C
P 3850 5400
F 0 "A1" H 3350 6500 50  0000 C CNN
F 1 "Arduino_UNO_R3" H 3350 6400 50  0000 C CNN
F 2 "Module:Arduino_UNO_R3" H 3850 5400 50  0001 C CIN
F 3 "https://www.arduino.cc/en/Main/arduinoBoardUno" H 3850 5400 50  0001 C CNN
	1    3850 5400
	1    0    0    -1  
$EndComp
$Comp
L Device:R_PHOTO R?
U 1 1 61B479A6
P 1900 3050
F 0 "R?" H 1970 3096 50  0000 L CNN
F 1 "R_PHOTO" H 1970 3005 50  0000 L CNN
F 2 "" V 1950 2800 50  0001 L CNN
F 3 "~" H 1900 3000 50  0001 C CNN
	1    1900 3050
	1    0    0    -1  
$EndComp
$Comp
L Sensor:DHT11 U?
U 1 1 61B4A96F
P 3350 3250
F 0 "U?" H 3106 3296 50  0000 R CNN
F 1 "DHT12" H 3106 3205 50  0000 R CNN
F 2 "Sensor:Aosong_DHT11_5.5x12.0_P2.54mm" H 3350 2850 50  0001 C CNN
F 3 "http://akizukidenshi.com/download/ds/aosong/DHT11.pdf" H 3500 3500 50  0001 C CNN
	1    3350 3250
	1    0    0    -1  
$EndComp
$Comp
L greenhouse:LDC_16x2 LCD?
U 1 1 61B4F192
P 4500 1600
F 0 "LCD?" H 5378 1588 50  0000 L CNN
F 1 "LDC_16x2" H 5378 1497 50  0000 L CNN
F 2 "" H 4300 1650 50  0001 C CNN
F 3 "" H 4300 1650 50  0001 C CNN
	1    4500 1600
	1    0    0    -1  
$EndComp
$EndSCHEMATC
