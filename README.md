# Basic circuits

A collection of simple and basic circuits.

###### Available circuits

- [Resistors Circuit](#resistors)
- [LED Circuit](#led)
- [Capacitors Circuit](#capacitors)
- [Button Circuit](#button)
- [LED Indicator Circuit](#led_indicator)
- [Power Circuit](#power)
- [Diode Bridge Circuit](#diode_bridge)
- [Pull-up/pull-down Resistor Circuit](#pull-up-down)
- [RS232 to Serial Circuit](#rs232_to_serial)
- [USB to Serial Circuit](#usb_to_serial)
- [Basic Stamp 2](#bs2)
- [Arduino](#arduino)


##<t id="resistors"/>Resistors Circuit



#### TODO

 - parallel and series

### Color Code

The colored bands over the resistors indicate their resistance, using this table you can find the value:

![Color Code Table](http://www.digikey.com/-/media/Images/Marketing/Resources/Calculators/resistor-color-chart.jpg?la=en-US&ts=72364a89-2139-476a-8a54-8d78dacd29ff)

##<t id="led"/>LED Circuit

Is the smallest circut used to power a LED (Light Emitting Diode)

![LED Circuit](led/schematic.png)

The *R1* resistor depends on the V<sub>cc</sub> voltage and on the LED type. For e 3mm LED at 5 VDC, for example, this are the rounded values:

Size | Color  | Forward current | Foward voltage | Resistor 
---- | ------ | --------------- | -------------- | --------
3mm  | Red    | 20mA            | 1.8 VDC        | 160 ohm
3mm  | Green  | 20mA            | 2.2 VDC        | 140 ohm
3mm  | Yellow | 20mA            | 2.1 VDC        | 145 ohm
3mm  | Blue   | 20mA            | 2.8 VDC        | 110 ohm


In general, the formul is:

 **R = (V<sub>cc</sub> - V<sub>L</sub>) / I<sub>L</sub>**

### Links
 - [Eagle project](led/)
 - [LED Resistor Calculator](http://www.ohmslawcalculator.com/led-resistor-calculator)


##<t id="capacitors"/>Capacitors Circuit

### Code

The code over the capacitors indicate their capacitance, using this table you can find the value:

 1st 2nd number | 3rd number | Multiply with 
----------------|-----------|---------------
 xx  | 0 | 1
 xx  | 1 | 10
 xx  | 2 | 100
 xx  | 3 | 1,000
 xx  | 4 | 10,000
 xx  | 5 | 100,000
 xx  | 6 | 1,000,000
 xx  | 7 | Not used
 xx  | 8 | 0.01
 xx  | 9 | 0.1
 xRx | / | 0.1

In general, the first two digit are the value, the 3rd is the multiplier and the letter is for tollerance. The very small capacitors can have an **R** between the first and second digits, this means that there is a point (ex. *2R2 = 2.2pF*).

In the most case, on a capacitor, there are also the max supported voltage (ex. *500V*)

Normally, on the electrolytic capacitors, there are the capacitance and the max voltage wrote in the clear form.

If there is a letter after the code, it represents the tollerance:

 Letter | Tolerance
--------|----------
 D | 0.5pF
 F | 1%
 G | 2%
 H | 3%
 J | 5%
 K | 10%
 M | 20%
 P | +100% / -0%
 Z | +80% / -20%


#### TODO

 - parallel and series
 - charge
 - discarge
 - oscilloscope
 

##<t id="button"/>Button Circuit

#### TODO

 - oscilloscope


##<t id="led_indicator"/>LED Indicator Circuit

This is a example that allow you to indicate the locical value in a line.

![LED Indicator Circuit](led_indicator/schematic.png)

*LED1* indicate the **1** logic state, *LED2* indicate the **0** logic state.

This is possible because a LED is a diode, so it allow the current flow only from positive to negative. When the line is at V<sub>cc</sub>, *LED1* allow current flow so it's on and *LED2* is off. Vice versa, when the line is at GND, *LED2* don't allow current flow so it's off and *LED2* is on.

### Links
 - [Eagle project](led_indicator/)


##<t id="power"/>Power Circuit

The standard **voltage regulator** is a component that allow us to get a normalized current and voltage. Every voltage regulator have a specific max Vin level and in order to get clean power, the datasheets recommends to using a **capacitor**.

![Power Circuit](power/schematic.png)

In this circuit I added a **12V diode** in order to perform a simple reverse polarity and overvoltage protection.

### Links
 - [Diode Bridge Circuit](power/)

##<t id="diode_bridge"/>Diode Bridge Circuit

A **Diode Bridge** is a circuit that provides the same polarity of output for either polarity of input and it's made by **4 diode**.

![Diode Bridge Circuit](diode_bridge/schematic_no_capacitor.png)

If the *V1* supply is positive, current flows through *D3* to V<sub>cc</sub> and flows to *V2* through *D2*. Vice versa, if the *V1* supply is negative, current flows through *D4* to V<sub>cc</sub> and flows to *V1* through *D1*.

The Diode Bridge is good to correct **Power Circuit** inverted polarity, but it allow us to convert an **AC** input into a **DC** output, for this porpuse, the addition of a capacitor is recomanded in order to prevent an output of pulsed DC.

![Diode Bridge Circuit](diode_bridge/schematic.png)

### Links
 - [Diode Bridge Circuit](diode_bridge/)


##<t id="pull-up-down"/>Pull-up/pull-down Resistor Circuit

#### TODO


##<t id="oscillator"/>Oscillator Circuit

###TODO

### Links
 - [Shift Oscillator](http://www.circuitstoday.com/transistor-phase-shift-oscillator)

##<t id="rs232_to_serial"/>RS232 to Serial Circuit

#### TODO

##<t id="usb_to_serial"/>USB to Serial Circuit

#### TODO

##<t id="bs2"/>Basic Stamp 2

#### TODO

##<t id="arduino"/> Arduino

#### TODO
