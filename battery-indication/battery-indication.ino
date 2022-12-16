#include <avr/io.h> 
#include <SoftwareSerial.h>
#include <util/delay.h>

// Specify the pins to use for the software serial connection to the Arduino Nano
const int RX_PIN = 2;
const int TX_PIN = 3;

int main()
{
  // Create a software serial object and specify the pins to use for the TX and RX lines
  SoftwareSerial serial(RX_PIN, TX_PIN);

  // Set the baud rate for the serial connection (9600 baud is a common baud rate for serial communication)
  serial.begin(9600);

  while (true)
  {
    // Set the reference voltage of the ADC to AVcc (the supply voltage of the ATtiny204)
    ADMUX |= (1 << REFS0);

    // Set the ADC prescaler to 128, to set the ADC clock frequency to 125 kHz (which is within the recommended range for the ATtiny204)
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    // Enable the ADC module
    ADCSRA |= (1 << ADEN);

    // Start the first conversion
    ADCSRA |= (1 << ADSC);

    // Wait for the conversion to complete
    while (ADCSRA & (1 << ADSC)) {}

    // Read the digital value from the ADC data register
    uint16_t adc_value = ADC;

    // Calculate the supply voltage of the ATtiny204 using the ADC value and the reference voltage
    float supply_voltage = (adc_value / 1024.0) * 5.0;

    // Print the supply voltage by serial
    serial.println(supply_voltage);

    // Wait for 1 second before starting the next conversion
    _delay_ms(1000);
  }
}
