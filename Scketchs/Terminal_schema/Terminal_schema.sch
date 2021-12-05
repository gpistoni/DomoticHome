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
L ESP32:PinHeader_4x2Relay TERMINAL_22
U 1 1 60573687
P 1300 1550
F 0 "TERMINAL_22" H 1308 725 50  0000 C CNN
F 1 "Luci Esterne" H 1308 816 50  0000 C CNN
F 2 "ESP32:PinHeader_4x2Relay" H 1300 1550 50  0001 C CNN
F 3 "~" H 1300 1550 50  0001 C CNN
	1    1300 1550
	-1   0    0    1   
$EndComp
Text Label 1500 1350 0    50   ~ 0
L1=lampAgoli
Text Label 1500 1250 0    50   ~ 0
L2=lampLati
Text Label 1500 1150 0    50   ~ 0
L3=lampPalo
Text Label 1500 1050 0    50   ~ 0
L4=lampExtra
Text Label 1500 1650 0    50   ~ 0
L5
Text Label 1500 1750 0    50   ~ 0
L6
Text Label 1500 1850 0    50   ~ 0
L7
Text Label 1500 1950 0    50   ~ 0
L8
Wire Notes Line
	650  600  2300 600 
Wire Notes Line
	2300 600  2300 2300
Wire Notes Line
	650  2300 650  600 
Wire Notes Line
	650  2300 2300 2300
Text Notes 700  2250 0    50   ~ 0
Terminal relay Esp32
$Comp
L ESP32:PinHeader_4x2Relay TERMINAL_23
U 1 1 605790CA
P 3150 1550
F 0 "TERMINAL_23" H 3158 725 50  0000 C CNN
F 1 "Relay Caldaia" H 3158 816 50  0000 C CNN
F 2 "ESP32:PinHeader_4x2Relay" H 3150 1550 50  0001 C CNN
F 3 "~" H 3150 1550 50  0001 C CNN
	1    3150 1550
	-1   0    0    1   
$EndComp
Text Label 3350 1250 0    50   ~ 0
L2=rPdcHeat
Text Label 3350 1150 0    50   ~ 0
L3=rPdcPompa
Text Label 3350 1050 0    50   ~ 0
L4=rPdcFullPower
Text Label 3350 1650 0    50   ~ 0
L5=rPompaPianoPrimo
Text Label 3350 1750 0    50   ~ 0
L6=rPompaPianoTerra
Text Label 3350 1850 0    50   ~ 0
L7=rBoilerAcs
Text Label 3350 1950 0    50   ~ 0
L8=rPompaCamino
Wire Notes Line
	2500 2300 2500 600 
Text Notes 2550 2250 0    50   ~ 0
Terminal relay Esp32
Text Label 3350 1350 0    50   ~ 0
L1=rPdc
$Comp
L Connector:Screw_Terminal_01x08 TERMINAL_23
U 1 1 605A2FA3
P 4650 1350
F 0 "TERMINAL_23" H 4568 725 50  0000 C CNN
F 1 "Temp Caldaia (IN)" H 4568 816 50  0000 C CNN
F 2 "" H 4650 1350 50  0001 C CNN
F 3 "~" H 4650 1350 50  0001 C CNN
	1    4650 1350
	-1   0    0    1   
$EndComp
Text Label 4850 1650 0    50   ~ 0
T1=tPufferHi
Text Label 4850 1550 0    50   ~ 0
T2=tPufferLow
Text Label 4850 1450 0    50   ~ 0
T3=tInputMixer
Text Label 4850 1350 0    50   ~ 0
T4=tReturnFireplace
Text Label 4850 1250 0    50   ~ 0
T5=tReturnFloor
Text Label 4850 1150 0    50   ~ 0
T6=tInletFloor
Text Label 4850 1050 0    50   ~ 0
T7=tExternal
Wire Notes Line
	6500 600  6500 2300
$Comp
L ESP32:PinHeader_3x2 J1
U 1 1 6072A0BF
P 5950 1950
F 0 "J1" H 6000 2381 50  0000 C CNN
F 1 "PinHeader_3x2" H 6000 2290 50  0000 C CNN
F 2 "ESP32:PinHeader_3in2" H 5950 1950 50  0001 C CNN
F 3 "~" H 5950 1950 50  0001 C CNN
	1    5950 1950
	1    0    0    -1  
$EndComp
Text Notes 5200 2200 0    50   ~ 0
6-5 Res 2.5K\n3-1 Link
$Comp
L Device:R R1
U 1 1 6072BE50
P 5550 1850
F 0 "R1" H 5620 1896 50  0000 L CNN
F 1 "2k5" H 5620 1805 50  0000 L CNN
F 2 "" V 5480 1850 50  0001 C CNN
F 3 "~" H 5550 1850 50  0001 C CNN
	1    5550 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 1700 5550 1700
Wire Wire Line
	5750 1950 5750 2000
Wire Wire Line
	5750 2000 5550 2000
Wire Wire Line
	6000 2000 6000 2250
Wire Wire Line
	6000 2250 6250 2250
Wire Wire Line
	6250 2250 6250 2000
Wire Notes Line
	2500 600  6500 600 
Text Notes 5850 1200 0    50   ~ 0
Dallas Probe\nRed 3v3\nGray GNd\nYellow Signal\n
Wire Notes Line
	2500 2300 6500 2300
$EndSCHEMATC
