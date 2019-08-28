# 4-20mA-Submersible-Liquid-Level-Pressure-Transducer
Arduino control of a 4-20mA submersible liquid level pressure transducer for level measurement
## Summary
Use an Arduino Mega to measure the level of a liquid by means of a 4-20mA submersible pressure transducer. By connecting a resistor in series with the transducer, the voltage across the resistor can be measured by the Arduino via an analog pin. From this voltage, the current can be calculated using Ohm's law and thereafter mapped to the liquid level. The ranges of the sensor are: 4-20mA, 0-10m, 12-36VDC.
## 4-20mA
This is an industry standard that outputs current in response to a change in a physical condition. The lowest possible value (4mA) corresponds to 0% of the measured value and is called <b>live zero</b>, whereas 20mA corresponds to 100% of the measured value.

It has the following advantages over voltage:
* Self-diagnosing: a break in the loop is detected as 0A, different from 0% as 4mA.
* Current does not drop while travelling in a low impedance loop. Voltage is dropped along the wire and hence suffers over a long distance.

It has the following advantages over wireless transmission:
* Self-diagnosis (discussed above).
* Inherent noise resistance (discussed above).
* Inexpensive.
* Handles long distances.

Since most MCUs read voltage inputs, the current signal is converted to a voltage by introducing a resistor of known value in series with the 4-20mA transducer. Since the same current from the transducer flows through the resistor, the voltage across the resistor (which is a measure of the current from the transducer) is determined via Ohms's law `V = I x R`.

Since the Arduino Mega is limited to 5V inputs, the required resistor value is determined from Ohm's law to be: `R = V / I = 5V / 20mA = 250Ω`. However, unless resistors are combined, a `220Ω` resistor is the closest one can get. This translates to `4.4V` for 100% and `0.88V` for 0%.
## Analog reading
The Arduino Mega has dedicated analog pins. The circuit simply requires the positive side of the `220Ω` resistor to be wired to one of the analog pins (e.g. A0) and the negative side to the Arduino ground.

The `analogRead(analog pin)` method was used to return an integer corresponding to the value of the voltage through the ADC.

In practice, it was found that the ADC value varies from reading to reading even though the transducer is at the same level. A more accurate value was determined by getting the average of ten successive readings. In order to eliminate outliers in the readings, the values were sorted using the `bubble sort algorithm` and the middle values used to calculate the average. The sensitivity was decreased by reducing the number of decimal points after calculating the average.
## Calculating voltage
The voltage was calculated from the ADC value using the formula `adc reading x voltage range / ADC range`. The sensitivity was reduced by reducing the number of decimal points.
## Calculating current
The current was calculated from the voltage using Ohm's law `I = V / R`.
## Calculating distance
The distance was calculated by mapping the current to the distance range using the formula `(calculated current - minimum current) * distance range / current range`.