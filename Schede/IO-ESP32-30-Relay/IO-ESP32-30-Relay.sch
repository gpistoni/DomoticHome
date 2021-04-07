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
L pspice:DIODE DP1
U 1 1 6038761C
P 2800 6350
F 0 "DP1" H 2800 6615 50  0000 C CNN
F 1 "DIODE" H 2800 6524 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 2800 6350 50  0001 C CNN
F 3 "~" H 2800 6350 50  0001 C CNN
	1    2800 6350
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 5V1
U 1 1 6038763E
P 1600 6350
F 0 "5V1" V 1700 6300 50  0000 C CNN
F 1 "Screw_Terminal_01x02" V 1473 6162 50  0001 R CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-2-5.08_1x02_P5.08mm_Horizontal" V 1473 6162 50  0001 R CNN
F 3 "~" H 1600 6350 50  0001 C CNN
	1    1600 6350
	-1   0    0    1   
$EndComp
Wire Wire Line
	1800 6350 2200 6350
$Comp
L power:VCC #PWR0101
U 1 1 60387667
P 2200 6350
F 0 "#PWR0101" H 2200 6200 50  0001 C CNN
F 1 "VCC" H 2215 6523 50  0000 C CNN
F 2 "" H 2200 6350 50  0001 C CNN
F 3 "" H 2200 6350 50  0001 C CNN
	1    2200 6350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 5400 6900 4650
Wire Wire Line
	6900 3550 7450 3550
Wire Wire Line
	5700 4650 6050 4650
Wire Wire Line
	6600 4650 6600 4150
Wire Wire Line
	6600 4050 7450 4050
Wire Wire Line
	6600 4150 7450 4150
Connection ~ 6600 4150
Wire Wire Line
	6600 4150 6600 4050
$Comp
L ESP32:DOIT-ESP32-30PIN U1
U 1 1 603942E7
P 5100 3450
F 0 "U1" H 5075 4015 50  0000 C CNN
F 1 "DOIT-ESP32-30PIN" H 5075 3924 50  0000 C CNN
F 2 "ESP32:ESP32-DOIT-DEVKIT" H 5050 3900 50  0001 C CNN
F 3 "" H 5050 3900 50  0001 C CNN
	1    5100 3450
	1    0    0    -1  
$EndComp
$Comp
L ESP32:PinHeader_4x2Relay J1
U 1 1 60395457
P 7650 4050
F 0 "J1" H 7909 4042 50  0000 L CNN
F 1 "PinHeader_4x2Relay" H 7909 3951 50  0000 L CNN
F 2 "ESP32:PinHeader_4x2Relay" H 7650 4050 50  0001 C CNN
F 3 "~" H 7650 4050 50  0001 C CNN
	1    7650 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 3250 6250 3250
Wire Wire Line
	6250 3250 6250 3650
Wire Wire Line
	6250 3650 7450 3650
Wire Wire Line
	5700 3350 6200 3350
Wire Wire Line
	6200 3350 6200 3750
Wire Wire Line
	6200 3750 7450 3750
Wire Wire Line
	5700 3650 6150 3650
Wire Wire Line
	6150 3850 7450 3850
Wire Wire Line
	6150 3650 6150 3850
Wire Wire Line
	5700 3750 6100 3750
Wire Wire Line
	6100 3750 6100 3950
Wire Wire Line
	6100 3950 7450 3950
Wire Wire Line
	5700 3850 6050 3850
Wire Wire Line
	6050 3850 6050 4250
Wire Wire Line
	6050 4250 7450 4250
Wire Wire Line
	5700 4050 6000 4050
Wire Wire Line
	6000 4050 6000 4350
Wire Wire Line
	6000 4350 7450 4350
Wire Wire Line
	5700 4150 5950 4150
Wire Wire Line
	5950 4150 5950 4450
Wire Wire Line
	5950 4450 7450 4450
Wire Wire Line
	5700 4250 5900 4250
Wire Wire Line
	5900 4250 5900 4550
Wire Wire Line
	5900 4550 7450 4550
$Comp
L Device:LED D1
U 1 1 60334896
P 4150 4600
F 0 "D1" V 4250 4650 50  0000 R CNN
F 1 "LED" V 4098 4482 50  0001 R CNN
F 2 "LED_THT:LED_D3.0mm" H 4150 4600 50  0001 C CNN
F 3 "~" H 4150 4600 50  0001 C CNN
	1    4150 4600
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R1
U 1 1 6033E0DA
P 4150 5000
F 0 "R1" V 4050 5000 50  0000 C CNN
F 1 "220" V 4150 5000 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 4080 5000 50  0001 C CNN
F 3 "~" H 4150 5000 50  0001 C CNN
	1    4150 5000
	-1   0    0    1   
$EndComp
$Comp
L Connector:Screw_Terminal_01x08 J2
U 1 1 603718E5
P 1200 3600
F 0 "J2" H 1118 2975 50  0000 C CNN
F 1 "Screw_Terminal_01x08" H 1118 3066 50  0000 C CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-8-5.08_1x08_P5.08mm_Horizontal" H 1200 3600 50  0001 C CNN
F 3 "~" H 1200 3600 50  0001 C CNN
	1    1200 3600
	-1   0    0    1   
$EndComp
Wire Wire Line
	6250 2400 6250 3250
Connection ~ 6250 3250
Wire Wire Line
	6200 3350 6200 2450
Connection ~ 6200 3350
Wire Wire Line
	6150 3650 6150 2500
Connection ~ 6150 3650
Wire Wire Line
	6100 3750 6100 2550
Connection ~ 6100 3750
Wire Wire Line
	6050 3850 6050 2600
Connection ~ 6050 3850
Wire Wire Line
	6000 4050 6000 2650
Connection ~ 6000 4050
Wire Wire Line
	5950 4150 5950 2700
Connection ~ 5950 4150
Wire Wire Line
	5900 4250 5900 2750
Connection ~ 5900 4250
Wire Wire Line
	1400 3900 1600 3900
Wire Wire Line
	1650 3800 1400 3800
Wire Wire Line
	4350 4650 4450 4650
$Comp
L ESP32:PinHeader_3x2 JP4
U 1 1 6046CAD0
P 3000 4150
F 0 "JP4" H 3100 4100 50  0000 R CNN
F 1 "PinHeader_3x2" H 2756 4105 50  0001 R CNN
F 2 "ESP32:PinHeader_3in2" H 3000 4150 50  0001 C CNN
F 3 "~" H 3000 4150 50  0001 C CNN
	1    3000 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 3900 1600 5200
Wire Wire Line
	1650 3800 1650 4850
Wire Wire Line
	1700 3700 1400 3700
Wire Wire Line
	1750 3600 1400 3600
Wire Wire Line
	2400 3150 1750 3150
Wire Wire Line
	1750 3400 1400 3400
Wire Wire Line
	1700 2800 1700 3300
Wire Wire Line
	1700 3300 1400 3300
Wire Wire Line
	1400 3200 1650 3200
Wire Wire Line
	1650 3200 1650 2450
Wire Wire Line
	1650 2450 2900 2450
Wire Wire Line
	3400 2400 6250 2400
Wire Wire Line
	3450 2450 3450 2750
Wire Wire Line
	3450 2450 6200 2450
Wire Wire Line
	3500 2500 3500 3100
Wire Wire Line
	3500 3100 2900 3100
Wire Wire Line
	3500 2500 6150 2500
Wire Wire Line
	3550 2550 3550 3450
Wire Wire Line
	3550 2550 6100 2550
Wire Wire Line
	3600 2600 3600 4100
Wire Wire Line
	3600 4100 3300 4100
Wire Wire Line
	3600 2600 6050 2600
Wire Wire Line
	3650 2650 3650 4450
Wire Wire Line
	3650 2650 6000 2650
Wire Wire Line
	3700 2700 3700 4800
Wire Wire Line
	3700 2700 5950 2700
Wire Wire Line
	3750 2750 5900 2750
Wire Wire Line
	4000 5250 4000 4250
Wire Wire Line
	4000 4250 4450 4250
Wire Wire Line
	4450 4150 3950 4150
Wire Wire Line
	3950 4150 3950 4900
Wire Wire Line
	3900 4550 3900 4050
Wire Wire Line
	3900 4050 4450 4050
Wire Wire Line
	3850 4200 3850 3950
Wire Wire Line
	3850 3950 4450 3950
Wire Wire Line
	2650 3550 4150 3550
Wire Wire Line
	2900 3200 4200 3200
Wire Wire Line
	4200 3200 4200 3550
Wire Wire Line
	4300 3350 4450 3350
Wire Wire Line
	3400 2500 3400 2850
Wire Wire Line
	3400 2850 4300 2850
Wire Wire Line
	4300 2850 4300 3350
$Comp
L ESP32:PinHeader_3x2 JP6
U 1 1 6046DA09
P 2600 3150
F 0 "JP6" H 2750 3100 50  0000 R CNN
F 1 "PinHeader_3x2" H 2356 3105 50  0001 R CNN
F 2 "ESP32:PinHeader_3in2" H 2600 3150 50  0001 C CNN
F 3 "~" H 2600 3150 50  0001 C CNN
	1    2600 3150
	1    0    0    -1  
$EndComp
$Comp
L ESP32:PinHeader_3x2 JP8
U 1 1 6046E56E
P 3100 2450
F 0 "JP8" H 3150 2400 50  0000 C CNN
F 1 "PinHeader_3x2" H 2856 2405 50  0001 R CNN
F 2 "ESP32:PinHeader_3in2" H 3100 2450 50  0001 C CNN
F 3 "~" H 3100 2450 50  0001 C CNN
	1    3100 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 5200 1600 5200
Wire Wire Line
	3750 5150 2500 5150
Wire Wire Line
	4000 5250 2500 5250
$Comp
L ESP32:PinHeader_3x2 JP3
U 1 1 6046C1D0
P 2700 4500
F 0 "JP3" H 2850 4450 50  0000 R CNN
F 1 "PinHeader_3x2" H 2456 4455 50  0001 R CNN
F 2 "ESP32:PinHeader_3in2" H 2700 4500 50  0001 C CNN
F 3 "~" H 2700 4500 50  0001 C CNN
	1    2700 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 4550 3900 4550
Wire Wire Line
	3650 4450 3000 4450
Wire Wire Line
	2500 4500 1700 4500
Wire Wire Line
	4450 3450 4250 3450
Wire Wire Line
	4250 3450 4250 3000
Wire Wire Line
	4450 3550 4200 3550
Wire Wire Line
	4450 3650 4150 3650
Wire Wire Line
	4150 3650 4150 3550
$Comp
L Connector:Screw_Terminal_01x02 3v3
U 1 1 60633DF4
P 1600 5950
F 0 "3v3" V 1700 5900 50  0000 C CNN
F 1 "Screw_Terminal_01x02" V 1473 5762 50  0001 R CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-2-5.08_1x02_P5.08mm_Horizontal" V 1473 5762 50  0001 R CNN
F 3 "~" H 1600 5950 50  0001 C CNN
	1    1600 5950
	-1   0    0    1   
$EndComp
Wire Wire Line
	1800 5850 2100 5850
Wire Wire Line
	2100 6250 2100 5850
Wire Wire Line
	1800 6250 2100 6250
Connection ~ 2100 5850
Wire Wire Line
	2100 5850 2950 5850
Wire Wire Line
	2200 6350 2600 6350
Connection ~ 2200 6350
Wire Wire Line
	5050 6350 5050 5400
Connection ~ 5050 5400
Wire Wire Line
	3000 6350 3550 6350
$Comp
L power:+3V3 #PWR0102
U 1 1 606AACF3
P 4750 5800
F 0 "#PWR0102" H 4750 5650 50  0001 C CNN
F 1 "+3V3" H 4765 5973 50  0000 C CNN
F 2 "" H 4750 5800 50  0001 C CNN
F 3 "" H 4750 5800 50  0001 C CNN
	1    4750 5800
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0103
U 1 1 606AB502
P 3550 6350
F 0 "#PWR0103" H 3550 6200 50  0001 C CNN
F 1 "+5V" H 3565 6523 50  0000 C CNN
F 2 "" H 3550 6350 50  0001 C CNN
F 3 "" H 3550 6350 50  0001 C CNN
	1    3550 6350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 6350 5050 6350
Wire Wire Line
	2650 2800 1700 2800
Wire Wire Line
	3450 2750 3150 2750
$Comp
L ESP32:PinHeader_3x2 JP7
U 1 1 6046DF8F
P 2850 2800
F 0 "JP7" H 3000 2750 50  0000 R CNN
F 1 "PinHeader_3x2" H 2606 2755 50  0001 R CNN
F 2 "ESP32:PinHeader_3in2" H 2850 2800 50  0001 C CNN
F 3 "~" H 2850 2800 50  0001 C CNN
	1    2850 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 4850 1650 4850
Wire Wire Line
	3700 4800 2750 4800
$Comp
L Device:R_Network04 RN1
U 1 1 603540B2
P 2750 5650
F 0 "RN1" H 2470 5604 50  0000 R CNN
F 1 "R_1k" H 2470 5695 50  0000 R CNN
F 2 "Resistor_THT:R_Array_SIP5" V 3025 5650 50  0001 C CNN
F 3 "http://www.vishay.com/docs/31509/csc.pdf" H 2750 5650 50  0001 C CNN
	1    2750 5650
	-1   0    0    1   
$EndComp
Connection ~ 3550 6350
Wire Wire Line
	4750 5800 4750 5950
Connection ~ 4750 5800
Connection ~ 2950 5850
Wire Wire Line
	4350 4650 4350 5300
$Comp
L ESP32:PinHeader_3x2 JP1
U 1 1 603F47B2
P 2200 5200
F 0 "JP1" H 2350 5150 50  0000 R CNN
F 1 "PinHeader_3x2" H 1956 5155 50  0001 R CNN
F 2 "ESP32:PinHeader_3in2" H 2200 5200 50  0001 C CNN
F 3 "~" H 2200 5200 50  0001 C CNN
	1    2200 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 4400 2950 5450
Wire Wire Line
	2850 4750 2850 5450
Wire Wire Line
	2600 5100 2750 5400
Wire Wire Line
	2750 5400 2750 5450
Wire Wire Line
	2350 5450 2650 5450
Wire Wire Line
	1700 3700 1700 4500
Wire Wire Line
	1750 3600 1750 4150
Wire Wire Line
	1750 4150 2800 4150
Wire Wire Line
	2650 3450 3550 3450
Wire Wire Line
	4250 3000 3150 3000
Wire Wire Line
	3150 3000 3150 2850
$Comp
L Device:R_Network04 RN2
U 1 1 608F85E2
P 3350 5650
F 0 "RN2" H 3070 5604 50  0000 R CNN
F 1 "R_1k" H 3070 5695 50  0000 R CNN
F 2 "Resistor_THT:R_Array_SIP5" V 3625 5650 50  0001 C CNN
F 3 "http://www.vishay.com/docs/31509/csc.pdf" H 3350 5650 50  0001 C CNN
	1    3350 5650
	-1   0    0    1   
$EndComp
Wire Wire Line
	3250 2700 3250 3250
Wire Wire Line
	3250 3250 3500 3250
Wire Wire Line
	3500 3250 3550 5450
Wire Wire Line
	3000 3050 3000 3300
Wire Wire Line
	3000 3300 3450 3300
Wire Wire Line
	3450 3300 3450 5450
Wire Wire Line
	3400 3350 2750 3350
Wire Wire Line
	2750 3350 2750 3400
Connection ~ 3550 5850
Wire Wire Line
	3550 5850 4350 5850
Wire Wire Line
	2950 5850 3550 5850
Wire Wire Line
	3350 5450 3400 3350
Wire Wire Line
	2500 3750 3350 3750
Wire Wire Line
	3250 5450 3350 3750
Wire Wire Line
	1750 3150 1750 3400
Wire Wire Line
	1950 4600 2400 4600
Wire Wire Line
	5050 5400 6900 5400
Wire Wire Line
	7450 4650 6900 4650
Connection ~ 6900 4650
Wire Wire Line
	6900 4650 6900 3550
Wire Wire Line
	5850 5800 5850 4750
Wire Wire Line
	5850 4750 5700 4750
Wire Wire Line
	4750 5800 5850 5800
$Comp
L power:GND #PWR0104
U 1 1 6056639E
P 6600 4750
F 0 "#PWR0104" H 6600 4500 50  0001 C CNN
F 1 "GND" H 6605 4577 50  0000 C CNN
F 2 "" H 6600 4750 50  0001 C CNN
F 3 "" H 6600 4750 50  0001 C CNN
	1    6600 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 4750 6600 4650
Connection ~ 6600 4650
Wire Wire Line
	6050 5300 6050 4650
Connection ~ 4350 5300
Wire Wire Line
	4350 5300 4350 5850
Connection ~ 6050 4650
Wire Wire Line
	6050 4650 6600 4650
Text Label 10750 7650 0    50   ~ 0
2.0
Wire Wire Line
	4450 5400 4450 4750
Wire Wire Line
	4450 5400 5050 5400
Wire Wire Line
	4150 4750 4150 4850
Wire Wire Line
	4350 5300 4150 5300
Wire Wire Line
	4150 5150 4150 5300
Wire Wire Line
	4350 5300 6050 5300
Wire Wire Line
	4150 4350 4450 4350
Wire Wire Line
	4150 4350 4150 4450
Text Label 3900 5250 0    50   ~ 0
14
Wire Wire Line
	3950 4900 2750 4900
Text Label 3850 4900 0    50   ~ 0
27
Text Label 3800 4550 0    50   ~ 0
26
Text Label 4050 3550 0    50   ~ 0
35
Text Label 4050 3200 0    50   ~ 0
34
Text Label 4050 3000 0    50   ~ 0
39
Text Label 4050 2850 0    50   ~ 0
36
Wire Wire Line
	3750 2750 3750 5150
Wire Wire Line
	3300 4200 3850 4200
Text Label 3800 4200 0    50   ~ 0
25
$Comp
L ESP32:PinHeader_3x2 JP2
U 1 1 6046BDBF
P 2450 4850
F 0 "JP2" H 2600 4800 50  0000 R CNN
F 1 "PinHeader_3x2" H 2206 4805 50  0001 R CNN
F 2 "ESP32:PinHeader_3in2" H 2450 4850 50  0001 C CNN
F 3 "~" H 2450 4850 50  0001 C CNN
	1    2450 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 4250 1950 4250
Wire Wire Line
	2950 3900 1950 3900
Wire Wire Line
	1950 2900 2550 2900
Wire Wire Line
	2800 2550 1950 2550
Wire Wire Line
	1950 2550 1950 2900
Wire Wire Line
	1950 5950 4750 5950
Wire Wire Line
	1950 5950 1800 5950
Connection ~ 1950 5950
Wire Wire Line
	2150 4950 1950 4950
Wire Wire Line
	1950 4950 1950 5950
$Comp
L ESP32:PinHeader_3x2 JP5
U 1 1 6046CF51
P 2350 3500
F 0 "JP5" H 2500 3450 50  0000 R CNN
F 1 "PinHeader_3x2" H 2106 3455 50  0001 R CNN
F 2 "ESP32:PinHeader_3in2" H 2350 3500 50  0001 C CNN
F 3 "~" H 2350 3500 50  0001 C CNN
	1    2350 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 2900 1950 3250
Connection ~ 1950 2900
Connection ~ 1950 4950
Connection ~ 1950 3900
Wire Wire Line
	1950 3900 1950 4250
Connection ~ 1950 4250
Wire Wire Line
	1950 4250 1950 4600
Connection ~ 1950 4600
Wire Wire Line
	1950 4600 1950 4950
Wire Wire Line
	2300 3250 1950 3250
Connection ~ 1950 3250
Wire Wire Line
	1950 3250 1950 3900
Wire Wire Line
	1950 2200 1950 2550
Wire Wire Line
	1950 2200 3050 2200
Connection ~ 1950 2550
Wire Wire Line
	1400 3500 2150 3500
$EndSCHEMATC
