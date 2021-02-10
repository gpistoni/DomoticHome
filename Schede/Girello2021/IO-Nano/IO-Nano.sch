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
P 9800 4600
F 0 "#PWR0101" H 9800 4350 50  0001 C CNN
F 1 "GND" H 9805 4427 50  0000 C CNN
F 2 "" H 9800 4600 50  0001 C CNN
F 3 "" H 9800 4600 50  0001 C CNN
	1    9800 4600
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
$Comp
L Transistor_FET:IRF540N Q1
U 1 1 601F8931
P 8950 3750
F 0 "Q1" H 9154 3796 50  0000 L CNN
F 1 "IRF540N" H 9154 3705 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 9200 3675 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irf540n.pdf" H 8950 3750 50  0001 L CNN
	1    8950 3750
	1    0    0    -1  
$EndComp
Connection ~ 8350 3750
Wire Wire Line
	8350 3750 8750 3750
$Comp
L Device:LED D1
U 1 1 60203687
P 8350 3900
F 0 "D1" V 8389 3782 50  0000 R CNN
F 1 "LED" V 8298 3782 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm" H 8350 3900 50  0001 C CNN
F 3 "~" H 8350 3900 50  0001 C CNN
	1    8350 3900
	0    -1   -1   0   
$EndComp
$Comp
L Device:R Ro1
U 1 1 6020708C
P 8350 4450
F 0 "Ro1" H 8420 4496 50  0000 L CNN
F 1 "R220" H 8420 4405 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 8280 4450 50  0001 C CNN
F 3 "~" H 8350 4450 50  0001 C CNN
	1    8350 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	8350 4050 8350 4300
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
Wire Wire Line
	8350 4600 8350 5150
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
P 9650 3950
F 0 "OUT1" V 9568 3762 50  0000 R CNN
F 1 "Screw_Terminal_01x02" V 9523 3762 50  0001 R CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-2-5.08_1x02_P5.08mm_Horizontal" V 9523 3762 50  0001 R CNN
F 3 "~" H 9650 3950 50  0001 C CNN
	1    9650 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:R Rgnd1
U 1 1 6022579D
P 9400 4850
F 0 "Rgnd1" H 9470 4896 50  0000 L CNN
F 1 "R47" H 9470 4805 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 9330 4850 50  0001 C CNN
F 3 "~" H 9400 4850 50  0001 C CNN
	1    9400 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 4400 6950 4400
Wire Wire Line
	6950 5150 7300 5150
Connection ~ 8350 5150
Wire Wire Line
	8350 5150 8350 5200
Wire Wire Line
	9050 3950 9450 3950
Wire Wire Line
	9450 4050 9400 4050
$Comp
L Connector:Screw_Terminal_01x02 OUT2
U 1 1 6023E095
P 9650 3350
F 0 "OUT2" V 9568 3162 50  0000 R CNN
F 1 "Screw_Terminal_01x02" V 9523 3162 50  0001 R CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-2-5.08_1x02_P5.08mm_Horizontal" V 9523 3162 50  0001 R CNN
F 3 "~" H 9650 3350 50  0001 C CNN
	1    9650 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 3550 9300 2950
Wire Wire Line
	9300 1350 7700 1350
Connection ~ 7700 1350
Wire Wire Line
	9050 3550 9300 3550
Wire Wire Line
	9450 3450 9400 3450
Wire Wire Line
	9400 3450 9400 4050
Connection ~ 9400 4050
$Comp
L Transistor_FET:IRF540N Q2
U 1 1 60244AEA
P 8950 3150
F 0 "Q2" H 9154 3196 50  0000 L CNN
F 1 "IRF540N" H 9154 3105 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 9200 3075 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irf540n.pdf" H 8950 3150 50  0001 L CNN
	1    8950 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9050 3350 9450 3350
Wire Wire Line
	9050 2950 9300 2950
Connection ~ 9300 2950
Wire Wire Line
	9300 2950 9300 1350
$Comp
L Device:LED D2
U 1 1 60249C24
P 8000 3900
F 0 "D2" V 8039 3782 50  0000 R CNN
F 1 "LED" V 7948 3782 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm" H 8000 3900 50  0001 C CNN
F 3 "~" H 8000 3900 50  0001 C CNN
	1    8000 3900
	0    -1   -1   0   
$EndComp
$Comp
L Device:R Ro2
U 1 1 6024A0F1
P 8000 4450
F 0 "Ro2" H 8070 4496 50  0000 L CNN
F 1 "R220" H 8070 4405 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 7930 4450 50  0001 C CNN
F 3 "~" H 8000 4450 50  0001 C CNN
	1    8000 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 3750 8000 3300
Wire Wire Line
	8000 3150 8750 3150
Wire Wire Line
	8000 4050 8000 4300
Wire Wire Line
	8000 4600 8000 5150
Connection ~ 8000 5150
Wire Wire Line
	8000 5150 8350 5150
$Comp
L Isolator:PC817 Uo4
U 1 1 602536DC
P 8800 2000
F 0 "Uo4" H 8800 2325 50  0000 C CNN
F 1 "PS2501" H 8800 2234 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 8600 1800 50  0001 L CIN
F 3 "http://www.soselectronic.cz/a_info/resource/d/pc817.pdf" H 8800 2000 50  0001 L CNN
	1    8800 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:R Ruo4
U 1 1 60255FD4
P 8100 1900
F 0 "Ruo4" H 8170 1946 50  0000 L CNN
F 1 "R220" H 8170 1855 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 8030 1900 50  0001 C CNN
F 3 "~" H 8100 1900 50  0001 C CNN
	1    8100 1900
	0    1    1    0   
$EndComp
Wire Wire Line
	8250 1900 8500 1900
Wire Wire Line
	5950 3700 6300 3700
Wire Wire Line
	6300 3700 6300 3000
Wire Wire Line
	6300 3000 7350 3000
$Comp
L Device:R Ruo3
U 1 1 6026ED6D
P 8100 2450
F 0 "Ruo3" H 8170 2496 50  0000 L CNN
F 1 "R220" H 8170 2405 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 8030 2450 50  0001 C CNN
F 3 "~" H 8100 2450 50  0001 C CNN
	1    8100 2450
	0    1    1    0   
$EndComp
$Comp
L Isolator:PC817 Uo3
U 1 1 6027A2D2
P 8800 2550
F 0 "Uo3" H 8800 2875 50  0000 C CNN
F 1 "PS2501" H 8800 2784 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 8600 2350 50  0001 L CIN
F 3 "http://www.soselectronic.cz/a_info/resource/d/pc817.pdf" H 8800 2550 50  0001 L CNN
	1    8800 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 2450 8500 2450
Wire Wire Line
	7400 3050 6350 3050
Wire Wire Line
	6350 3050 6350 3800
Wire Wire Line
	6350 3800 5950 3800
Wire Wire Line
	7950 2450 7800 2450
Wire Wire Line
	7350 2450 7350 3000
Wire Wire Line
	7400 3050 7400 1900
Wire Wire Line
	7400 1900 7750 1900
Wire Wire Line
	5950 3400 6450 3400
Wire Wire Line
	6450 3400 6450 3250
Wire Wire Line
	6450 3250 8350 3250
Wire Wire Line
	8350 3250 8350 3750
Wire Wire Line
	5950 3500 6500 3500
Wire Wire Line
	6500 3500 6500 3300
Wire Wire Line
	6500 3300 8000 3300
Connection ~ 8000 3300
Wire Wire Line
	8000 3300 8000 3150
$Comp
L Connector:Screw_Terminal_01x02 OUT4
U 1 1 60290D2D
P 9650 2000
F 0 "OUT4" V 9568 1812 50  0000 R CNN
F 1 "Screw_Terminal_01x02" V 9523 1812 50  0001 R CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-2-5.08_1x02_P5.08mm_Horizontal" V 9523 1812 50  0001 R CNN
F 3 "~" H 9650 2000 50  0001 C CNN
	1    9650 2000
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 OUT3
U 1 1 6029157C
P 9650 2550
F 0 "OUT3" V 9568 2362 50  0000 R CNN
F 1 "Screw_Terminal_01x02" V 9523 2362 50  0001 R CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" V 9523 2362 50  0001 R CNN
F 3 "~" H 9650 2550 50  0001 C CNN
	1    9650 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 2450 9450 2550
Wire Wire Line
	9100 2650 9450 2650
Wire Wire Line
	9100 1900 9450 2000
Wire Wire Line
	9100 2100 9450 2100
Wire Wire Line
	9400 5150 8350 5150
Wire Wire Line
	9400 5000 9400 5150
$Comp
L Device:LED D3
U 1 1 602B3D83
P 7650 3900
F 0 "D3" V 7689 3782 50  0000 R CNN
F 1 "LED" V 7598 3782 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm" H 7650 3900 50  0001 C CNN
F 3 "~" H 7650 3900 50  0001 C CNN
	1    7650 3900
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D4
U 1 1 602B42E0
P 7300 3900
F 0 "D4" V 7339 3782 50  0000 R CNN
F 1 "LED" V 7248 3782 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm" H 7300 3900 50  0001 C CNN
F 3 "~" H 7300 3900 50  0001 C CNN
	1    7300 3900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6950 4400 6950 5150
$Comp
L Device:R Ro3
U 1 1 602B68D0
P 7650 4450
F 0 "Ro3" H 7720 4496 50  0000 L CNN
F 1 "R220" H 7720 4405 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 7580 4450 50  0001 C CNN
F 3 "~" H 7650 4450 50  0001 C CNN
	1    7650 4450
	1    0    0    -1  
$EndComp
$Comp
L Device:R Ro4
U 1 1 602B6C60
P 7300 4450
F 0 "Ro4" H 7370 4496 50  0000 L CNN
F 1 "R220" H 7370 4405 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 7230 4450 50  0001 C CNN
F 3 "~" H 7300 4450 50  0001 C CNN
	1    7300 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 4050 7300 4300
Wire Wire Line
	7650 4050 7650 4300
Wire Wire Line
	7650 3750 7650 3150
Wire Wire Line
	7650 3150 7800 3150
Wire Wire Line
	7800 3150 7800 2450
Connection ~ 7800 2450
Wire Wire Line
	7800 2450 7350 2450
Wire Wire Line
	7300 3750 7300 3100
Wire Wire Line
	7300 3100 7750 3100
Wire Wire Line
	7750 3100 7750 1900
Connection ~ 7750 1900
Wire Wire Line
	7750 1900 7950 1900
Wire Wire Line
	7650 4600 7650 5150
Connection ~ 7650 5150
Wire Wire Line
	7650 5150 8000 5150
Wire Wire Line
	7300 4600 7300 5150
Connection ~ 7300 5150
Wire Wire Line
	7300 5150 7650 5150
Wire Wire Line
	9400 3450 9400 1800
Wire Wire Line
	9400 1800 7700 1800
Connection ~ 9400 3450
Connection ~ 7700 1800
Wire Wire Line
	9800 4550 9800 4600
Wire Wire Line
	9400 4050 9400 4550
Wire Wire Line
	9800 4550 9400 4550
Connection ~ 9400 4550
Wire Wire Line
	9400 4550 9400 4700
$EndSCHEMATC
