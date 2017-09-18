EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:switches
LIBS:isp_burner-cache
EELAYER 25 0
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
L ATMEGA16-16PU main_controller1
U 1 1 59B6580C
P 5450 3450
F 0 "main_controller1" H 4600 5330 50  0000 L BNN
F 1 "ATMEGA16-16PU" H 5900 1500 50  0000 L BNN
F 2 "Housings_DIP:DIP-40_W15.24mm" H 5450 3450 50  0001 C CIN
F 3 "" H 5450 3450 50  0001 C CNN
	1    5450 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 1450 5600 1450
$Comp
L GND #PWR01
U 1 1 59B66ADB
P 5400 5850
F 0 "#PWR01" H 5400 5600 50  0001 C CNN
F 1 "GND" H 5400 5700 50  0000 C CNN
F 2 "" H 5400 5850 50  0001 C CNN
F 3 "" H 5400 5850 50  0001 C CNN
	1    5400 5850
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR02
U 1 1 59B66B77
P 5300 1200
F 0 "#PWR02" H 5300 1050 50  0001 C CNN
F 1 "VCC" H 5300 1350 50  0000 C CNN
F 2 "" H 5300 1200 50  0001 C CNN
F 3 "" H 5300 1200 50  0001 C CNN
	1    5300 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 1200 5300 1450
Wire Wire Line
	5400 5450 5400 5850
$Comp
L BARREL_JACK power_in1
U 1 1 59B676F7
P 1900 3400
F 0 "power_in1" H 1900 3595 50  0000 C CNN
F 1 "BARREL_JACK" H 1900 3245 50  0000 C CNN
F 2 "Connectors:BARREL_JACK" H 1900 3400 50  0001 C CNN
F 3 "" H 1900 3400 50  0001 C CNN
	1    1900 3400
	1    0    0    -1  
$EndComp
Connection ~ 5300 1450
Wire Wire Line
	2200 3400 2200 5450
Connection ~ 2200 3500
$Comp
L Crystal crystal_1
U 1 1 59B68215
P 3100 4850
F 0 "crystal_1" H 3100 5000 50  0000 C CNN
F 1 "16MHz" H 3100 4700 50  0000 C CNN
F 2 "Crystals:Crystal_HC49-U_Vertical" H 3100 4850 50  0001 C CNN
F 3 "" H 3100 4850 50  0001 C CNN
	1    3100 4850
	-1   0    0    1   
$EndComp
Wire Wire Line
	4450 2150 2950 2150
Wire Wire Line
	2950 2150 2950 5050
Wire Wire Line
	4450 2550 3250 2550
Wire Wire Line
	3250 2550 3250 5050
$Comp
L C crystal_cap_1
U 1 1 59B6854A
P 2950 5200
F 0 "crystal_cap_1" H 2975 5300 50  0000 L CNN
F 1 "22pF" H 2975 5100 50  0000 L CNN
F 2 "Capacitors_THT:C_Axial_L5.1mm_D3.1mm_P7.50mm_Horizontal" H 2988 5050 50  0001 C CNN
F 3 "" H 2950 5200 50  0001 C CNN
	1    2950 5200
	1    0    0    -1  
$EndComp
$Comp
L C crystal_cap_2
U 1 1 59B685D0
P 3250 5200
F 0 "crystal_cap_2" H 3275 5300 50  0000 L CNN
F 1 "22pF" H 3275 5100 50  0000 L CNN
F 2 "Capacitors_THT:C_Axial_L5.1mm_D3.1mm_P7.50mm_Horizontal" H 3288 5050 50  0001 C CNN
F 3 "" H 3250 5200 50  0001 C CNN
	1    3250 5200
	1    0    0    -1  
$EndComp
Connection ~ 2950 4850
Connection ~ 3250 4850
Wire Wire Line
	2950 5350 2950 5450
Connection ~ 2950 5450
Wire Wire Line
	3250 5450 3250 5350
Connection ~ 3250 5450
$Comp
L LM7805 voltage_regulator1
U 1 1 59B6879A
P 3400 1500
F 0 "voltage_regulator1" H 3550 1304 50  0000 C CNN
F 1 "LM7805" H 3400 1700 50  0000 C CNN
F 2 "Transistors_OldSowjetAera:OldSowjetaera_Transistor_Type-I_BigPads" H 3400 1500 50  0001 C CNN
F 3 "" H 3400 1500 50  0001 C CNN
	1    3400 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 3300 2200 1450
Wire Wire Line
	2200 1450 3000 1450
Wire Wire Line
	2200 5450 5400 5450
Wire Wire Line
	3400 1750 3400 5450
Connection ~ 3400 5450
$Comp
L C power_cap_in1
U 1 1 59B6914E
P 2850 1700
F 0 "power_cap_in1" H 2875 1800 50  0000 L CNN
F 1 "0.33uF" H 2875 1600 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D5.0mm_W2.5mm_P2.50mm" H 2888 1550 50  0001 C CNN
F 3 "" H 2850 1700 50  0001 C CNN
	1    2850 1700
	1    0    0    -1  
$EndComp
$Comp
L C power_cap_out1
U 1 1 59B691BB
P 4000 1700
F 0 "power_cap_out1" H 4025 1800 50  0000 L CNN
F 1 "0.1uF" H 4025 1600 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D5.0mm_W2.5mm_P2.50mm" H 4038 1550 50  0001 C CNN
F 3 "" H 4000 1700 50  0001 C CNN
	1    4000 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 1550 2850 1450
Connection ~ 2850 1450
Wire Wire Line
	2850 1850 2850 1900
Wire Wire Line
	2850 1900 4000 1900
Connection ~ 3400 1900
Wire Wire Line
	4000 1900 4000 1850
Wire Wire Line
	4000 1550 4000 1450
Connection ~ 4000 1450
$EndSCHEMATC
