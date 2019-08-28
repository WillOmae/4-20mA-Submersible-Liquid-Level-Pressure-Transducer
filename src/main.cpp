/*
 * Pressure Water Level Sensor
 * main.cpp
 *
 * Created: 8/28/2019 2:00:00 PM
 * Author: WILLOMAE
 */
#include <Arduino.h>
int readAnalogInput (void);
double calcVoltage (int);
double calcCurrent (double);
double calcDistance (double);
void setup()
{
    Serial.begin (115200);
}

void loop()
{
    int adc = readAnalogInput();
    double volt = calcVoltage (adc);
    double amp = calcCurrent (volt);
    double cm = calcDistance (amp);
    Serial.print ("V:\t");
    Serial.print (volt, 3);
    Serial.print ("V");
    Serial.print ("\tI:");
    Serial.print (amp, 3);
    Serial.print ("mA");
    Serial.print ("\tH:");
    Serial.print (cm, 3);
    Serial.print ("cm");
    Serial.println();
    delay (1000);
}
int readAnalogInput()
{
    int buf[10], temp;

    for (int i = 0; i < 10; i++)
    {
        buf[i] = analogRead (A0);
        delay (10);
    }

    for (int i = 0; i < 9; i++)
    {
        for (int j = i + 1; j < 10; j++)
        {
            if (buf[i] > buf[j])
            {
                temp = buf[i];
                buf[i] = buf[j];
                buf[j] = temp;
            }
        }
    }

    int avgValue = 0;

    for (int i = 2; i < 8; i++)
    {
        avgValue += buf[i];
    }

    avgValue /= 6;
    return avgValue;
}
double calcVoltage (int adc)
{
    double volt = (double)adc * (5 - 0) / (1023 - 0);
    int temp = volt * 100;
    volt = (double)temp / 100;
    return volt;
}
double calcCurrent (double volt)
{
    double amp = (volt / 250) * 1000;
    return amp;
}
double calcDistance (double amp)
{
    return (amp - 4) * 1000 / 16;
}