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
L power:GND #PWR0101
U 1 1 601EDCB1
P 10400 4600
F 0 "#PWR0101" H 10400 4350 50  0001 C CNN
F 1 "GND" H 10405 4427 50  0000 C CNN
F 2 "" H 10400 4600 50  0001 C CNN
F 3 "" H 10400 4600 50  0001 C CNN
	1    10400 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 1300 6500 1350
Wire Wire Line
	6500 1500 6550 1500
Wire Wire Line
	6350 2400 6350 2150
Wire Wire Line
	6350 2150 7150 2150
$Comp
L Device:C c1
U 1 1 6020A2CA
P 7700 1650
F 0 "c1" H 7815 1696 50  0000 L CNN
F 1 "100nF" H 7815 1605 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.0mm_W2.5mm_P2.50mm" H 7738 1500 50  0001 C CNN
F 3 "~" H 7700 1650 50  0001 C CNN
	1    7700 1650
	-1   0    0    1   
$EndComp
Connection ~ 6500 1500
Connection ~ 6000 1800
Wire Wire Line
	6000 1800 5500 1800
$Comp
L Regulator_Linear:L7805 U1
U 1 1 601FB59C
P 6850 1500
F 0 "U1" H 6850 1742 50  0000 C CNN
F 1 "L7805" H 6850 1651 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 6875 1350 50  0001 L CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 6850 1450 50  0001 C CNN
	1    6850 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 1500 6000 1800
Wire Wire Line
	6300 1500 6500 1500
$Comp
L Device:CP C2
U 1 1 6020AEB1
P 6150 1500
F 0 "C2" V 5895 1500 50  0000 C CNN
F 1 "10uf" V 5986 1500 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D7.5mm_P2.50mm" H 6188 1350 50  0001 C CNN
F 3 "~" H 6150 1500 50  0001 C CNN
	1    6150 1500
	0    1    1    0   
$EndComp
Wire Wire Line
	6000 1800 6850 1800
$Comp
L Connector:Screw_Terminal_01x02 5v-GND1
U 1 1 601EF503
P 7250 550
F 0 "5v-GND1" V 7168 362 50  0000 R CNN
F 1 "Screw_Terminal_01x02" V 7123 362 50  0001 R CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-2-5.08_1x02_P5.08mm_Horizontal" V 7123 362 50  0001 R CNN
F 3 "~" H 7250 550 50  0001 C CNN
	1    7250 550 
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 24v-GND1
U 1 1 601F03B1
P 6600 550
F 0 "24v-GND1" V 6518 362 50  0000 R CNN
F 1 "Screw_Terminal_01x02" V 6473 362 50  0001 R CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-2-5.08_1x02_P5.08mm_Horizontal" V 6473 362 50  0001 R CNN
F 3 "~" H 6600 550 50  0001 C CNN
	1    6600 550 
	0    -1   -1   0   
$EndComp
$Comp
L pspice:DIODE DP1
U 1 1 601ED81C
P 6500 1100
F 0 "DP1" V 6454 1228 50  0000 L CNN
F 1 "DIODE" V 6545 1228 50  0000 L CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 6500 1100 50  0001 C CNN
F 3 "~" H 6500 1100 50  0001 C CNN
	1    6500 1100
	0    1    1    0   
$EndComp
Wire Wire Line
	6600 750  6500 750 
Wire Wire Line
	6500 750  6500 900 
Wire Wire Line
	6700 750  6700 850 
Wire Wire Line
	6700 850  5500 850 
Wire Wire Line
	5500 850  5500 1800
Wire Wire Line
	7350 750  7350 850 
Wire Wire Line
	7350 850  6700 850 
Connection ~ 6700 850 
$Comp
L Transistor_FET:IRF540N Q1
U 1 1 601F8931
P 9550 3750
F 0 "Q1" H 9754 3796 50  0000 L CNN
F 1 "IRF540N" H 9754 3705 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 9800 3675 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irf540n.pdf" H 9550 3750 50  0001 L CNN
	1    9550 3750
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D1
U 1 1 60203687
P 9050 3900
F 0 "D1" V 9150 3950 50  0000 R CNN
F 1 "LED" V 8998 3782 50  0001 R CNN
F 2 "LED_THT:LED_D3.0mm" H 9050 3900 50  0001 C CNN
F 3 "~" H 9050 3900 50  0001 C CNN
	1    9050 3900
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 60208474
P 8350 5200
F 0 "#PWR0102" H 8350 4950 50  0001 C CNN
F 1 "GND" H 8355 5027 50  0000 C CNN
F 2 "" H 8350 5200 50  0001 C CNN
F 3 "" H 8350 5200 50  0001 C CNN
	1    8350 5200
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0103
U 1 1 60208A7F
P 7150 2150
F 0 "#PWR0103" H 7150 2000 50  0001 C CNN
F 1 "+5V" H 7165 2323 50  0000 C CNN
F 2 "" H 7150 2150 50  0001 C CNN
F 3 "" H 7150 2150 50  0001 C CNN
	1    7150 2150
	1    0    0    -1  
$EndComp
$Comp
L power:+24V #PWR0104
U 1 1 602160C5
P 7700 1350
F 0 "#PWR0104" H 7700 1200 50  0001 C CNN
F 1 "+24V" H 7715 1523 50  0000 C CNN
F 2 "" H 7700 1350 50  0001 C CNN
F 3 "" H 7700 1350 50  0001 C CNN
	1    7700 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 1350 7700 1350
Connection ~ 6500 1350
Wire Wire Line
	6500 1350 6500 1500
Wire Wire Line
	7250 750  7250 1500
Wire Wire Line
	7150 1500 7250 1500
Wire Wire Line
	7700 1800 6850 1800
Connection ~ 6850 1800
Connection ~ 7250 1500
Wire Wire Line
	7250 1500 7700 1500
Wire Wire Line
	7250 2150 7150 2150
Wire Wire Line
	7250 1500 7250 2150
Connection ~ 7150 2150
$Comp
L Connector:Screw_Terminal_01x02 OUT1
U 1 1 6022382A
P 10250 3850
F 0 "OUT1" V 10350 3900 50  0000 R CNN
F 1 "Screw_Terminal_01x02" V 10123 3662 50  0001 R CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-2-5.08_1x02_P5.08mm_Horizontal" V 10123 3662 50  0001 R CNN
F 3 "~" H 10250 3850 50  0001 C CNN
	1    10250 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:R Rgnd1
U 1 1 6022579D
P 10000 4850
F 0 "Rgnd1" H 10070 4896 50  0000 L CNN
F 1 "R47" H 10070 4805 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 9930 4850 50  0001 C CNN
F 3 "~" H 10000 4850 50  0001 C CNN
	1    10000 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 4400 6950 4400
Connection ~ 8350 5150
Wire Wire Line
	8350 5150 8350 5200
Wire Wire Line
	9650 3950 10050 3950
Wire Wire Line
	10050 4050 10000 4050
$Comp
L Connector:Screw_Terminal_01x02 OUT2
U 1 1 6023E095
P 10250 3250
F 0 "OUT2" V 10350 3300 50  0000 R CNN
F 1 "Screw_Terminal_01x02" V 10123 3062 50  0001 R CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-2-5.08_1x02_P5.08mm_Horizontal" V 10123 3062 50  0001 R CNN
F 3 "~" H 10250 3250 50  0001 C CNN
	1    10250 3250
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:IRF540N Q2
U 1 1 60244AEA
P 9550 3150
F 0 "Q2" H 9754 3196 50  0000 L CNN
F 1 "IRF540N" H 9754 3105 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 9800 3075 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irf540n.pdf" H 9550 3150 50  0001 L CNN
	1    9550 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9650 3350 10050 3350
$Comp
L Isolator:PC817 Uo4
U 1 1 602536DC
P 9400 2200
F 0 "Uo4" H 9700 2200 50  0000 C CNN
F 1 "PS2501" H 9000 2200 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 9200 2000 50  0001 L CIN
F 3 "http://www.soselectronic.cz/a_info/resource/d/pc817.pdf" H 9400 2200 50  0001 L CNN
	1    9400 2200
	1    0    0    -1  
$EndComp
$Comp
L Isolator:PC817 Uo3
U 1 1 6027A2D2
P 9400 2550
F 0 "Uo3" H 9700 2550 50  0000 C CNN
F 1 "PS2501" H 9000 2550 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 9200 2350 50  0001 L CIN
F 3 "http://www.soselectronic.cz/a_info/resource/d/pc817.pdf" H 9400 2550 50  0001 L CNN
	1    9400 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 3400 6450 3400
Wire Wire Line
	6450 3400 6450 3250
Wire Wire Line
	5950 3500 6500 3500
Wire Wire Line
	6500 3500 6500 3300
$Comp
L Connector:Screw_Terminal_01x02 OUT4
U 1 1 60290D2D
P 10250 2200
F 0 "OUT4" V 10350 2250 50  0000 R CNN
F 1 "Screw_Terminal_01x02" V 10123 2012 50  0001 R CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-2-5.08_1x02_P5.08mm_Horizontal" V 10123 2012 50  0001 R CNN
F 3 "~" H 10250 2200 50  0001 C CNN
	1    10250 2200
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 OUT3
U 1 1 6029157C
P 10250 2550
F 0 "OUT3" V 10350 2600 50  0000 R CNN
F 1 "Screw_Terminal_01x02" V 10123 2362 50  0001 R CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" V 10123 2362 50  0001 R CNN
F 3 "~" H 10250 2550 50  0001 C CNN
	1    10250 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9700 2450 10050 2550
Wire Wire Line
	9700 2650 10050 2650
Wire Wire Line
	9700 2100 10050 2200
Wire Wire Line
	9700 2300 10050 2300
Wire Wire Line
	10000 5000 10000 5150
Wire Wire Line
	6950 4400 6950 5150
Wire Wire Line
	10400 4550 10400 4600
Wire Wire Line
	10400 4550 10000 4550
Wire Wire Line
	10000 4550 10000 4700
Text Label 6300 4150 1    50   ~ 0
10-13_Eth
$Comp
L MCU_Module:Arduino_Nano_v2.x A1
U 1 1 601EC25F
P 6450 3400
F 0 "A1" H 6450 2311 50  0000 C CNN
F 1 "Arduino_Nano_v2.x" H 6450 2220 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 6450 3400 50  0001 C CIN
F 3 "https://www.arduino.cc/en/uploads/Main/ArduinoNanoManual23.pdf" H 6450 3400 50  0001 C CNN
	1    6450 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	10050 2950 10050 3250
Wire Wire Line
	9650 2950 10050 2950
Wire Wire Line
	10050 3550 10050 3850
Wire Wire Line
	9650 3550 10050 3550
Wire Wire Line
	9350 3750 9050 3750
$Comp
L Isolator:PC817 Uo6
U 1 1 602C1EA9
P 9400 1500
F 0 "Uo6" H 9700 1500 50  0000 C CNN
F 1 "PS2501" H 9000 1500 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 9200 1300 50  0001 L CIN
F 3 "http://www.soselectronic.cz/a_info/resource/d/pc817.pdf" H 9400 1500 50  0001 L CNN
	1    9400 1500
	1    0    0    -1  
$EndComp
$Comp
L Isolator:PC817 Uo5
U 1 1 602C1EAF
P 9400 1850
F 0 "Uo5" H 9700 1850 50  0000 C CNN
F 1 "PS2501" H 9000 1850 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 9200 1650 50  0001 L CIN
F 3 "http://www.soselectronic.cz/a_info/resource/d/pc817.pdf" H 9400 1850 50  0001 L CNN
	1    9400 1850
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 OUT6
U 1 1 602C1EB5
P 10250 1500
F 0 "OUT6" V 10350 1550 50  0000 R CNN
F 1 "Screw_Terminal_01x02" V 10123 1312 50  0001 R CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-2-5.08_1x02_P5.08mm_Horizontal" V 10123 1312 50  0001 R CNN
F 3 "~" H 10250 1500 50  0001 C CNN
	1    10250 1500
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 OUT5
U 1 1 602C1EBB
P 10250 1850
F 0 "OUT5" V 10350 1900 50  0000 R CNN
F 1 "Screw_Terminal_01x02" V 10123 1662 50  0001 R CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" V 10123 1662 50  0001 R CNN
F 3 "~" H 10250 1850 50  0001 C CNN
	1    10250 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	9700 1750 10050 1850
Wire Wire Line
	9700 1950 10050 1950
Wire Wire Line
	9700 1400 10050 1500
Wire Wire Line
	9700 1600 10050 1600
Wire Wire Line
	8800 1400 9100 1400
Wire Wire Line
	5950 3100 6250 3100
Wire Wire Line
	6250 3100 6250 3050
Wire Wire Line
	5950 3200 6300 3200
Wire Wire Line
	6300 3200 6300 3100
Wire Wire Line
	5950 3300 6350 3300
Wire Wire Line
	6350 3300 6350 3150
Wire Wire Line
	6950 5150 8350 5150
Wire Wire Line
	8350 5150 10000 5150
$Comp
L Device:LED D2
U 1 1 6034F1CE
P 8800 3900
F 0 "D2" V 8900 3950 50  0000 R CNN
F 1 "LED" V 8748 3782 50  0001 R CNN
F 2 "LED_THT:LED_D3.0mm" H 8800 3900 50  0001 C CNN
F 3 "~" H 8800 3900 50  0001 C CNN
	1    8800 3900
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D3
U 1 1 6034F6E7
P 8550 3900
F 0 "D3" V 8650 3950 50  0000 R CNN
F 1 "LED" V 8498 3782 50  0001 R CNN
F 2 "LED_THT:LED_D3.0mm" H 8550 3900 50  0001 C CNN
F 3 "~" H 8550 3900 50  0001 C CNN
	1    8550 3900
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D4
U 1 1 60350BB9
P 8300 3900
F 0 "D4" V 8400 3950 50  0000 R CNN
F 1 "LED" V 8248 3782 50  0001 R CNN
F 2 "LED_THT:LED_D3.0mm" H 8300 3900 50  0001 C CNN
F 3 "~" H 8300 3900 50  0001 C CNN
	1    8300 3900
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D5
U 1 1 603510AD
P 8050 3900
F 0 "D5" V 8150 3950 50  0000 R CNN
F 1 "LED" V 7998 3782 50  0001 R CNN
F 2 "LED_THT:LED_D3.0mm" H 8050 3900 50  0001 C CNN
F 3 "~" H 8050 3900 50  0001 C CNN
	1    8050 3900
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D6
U 1 1 60352DDD
P 7800 3900
F 0 "D6" V 7900 3950 50  0000 R CNN
F 1 "LED" V 7748 3782 50  0001 R CNN
F 2 "LED_THT:LED_D3.0mm" H 7800 3900 50  0001 C CNN
F 3 "~" H 7800 3900 50  0001 C CNN
	1    7800 3900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8850 4900 8750 4900
Wire Wire Line
	8350 4900 8350 5150
Wire Wire Line
	8550 4050 8550 4300
Wire Wire Line
	8550 4300 8350 4300
Wire Wire Line
	8350 4300 8350 4500
Wire Wire Line
	8300 4050 8300 4250
Wire Wire Line
	8300 4250 8250 4250
Wire Wire Line
	8250 4250 8250 4500
Wire Wire Line
	8050 4050 8050 4300
Wire Wire Line
	8050 4300 8150 4300
Wire Wire Line
	8150 4300 8150 4500
Wire Wire Line
	7800 4050 7800 4350
Wire Wire Line
	7800 4350 8050 4350
Wire Wire Line
	8050 4350 8050 4500
Wire Wire Line
	8650 4900 8550 4900
$Comp
L Device:R_Network04 RN?
U 1 1 603B8874
P 8150 4700
F 0 "RN?" H 7870 4654 50  0000 R CNN
F 1 "R_220" H 7870 4745 50  0000 R CNN
F 2 "Resistor_THT:R_Array_SIP5" V 8425 4700 50  0001 C CNN
F 3 "http://www.vishay.com/docs/31509/csc.pdf" H 8150 4700 50  0001 C CNN
	1    8150 4700
	-1   0    0    1   
$EndComp
$EndSCHEMATC
