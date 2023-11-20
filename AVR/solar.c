#include <avr/io.h>
#include <util/delay.h>

#define SERVO_PIN PB3 // Pin connected to the servo

void servoWrite(uint8_t angle)
{
    uint16_t pulseWidth = (angle * 10) + 600; // Calculate pulse width in microseconds

    // Set the pulse width in Timer/Counter2 registers
    OCR2A = (pulseWidth / 8) - 1; // Adjust for prescaler

    _delay_ms(500); // Wait for the servo to move to the desired angle
}

void setup()
{
    // Configure Timer/Counter2 for Fast PWM mode with non-inverted output
    TCCR2A = (1 << COM2A1) | (1 << WGM21) | (1 << WGM20);
    TCCR2B = (1 << CS22); // Prescaler of 64

    // Set the servo pin as an output
    DDRB |= (1 << SERVO_PIN);

    // Initialize the servo to the initial position
    servoWrite(90);

    // Configure ADC for LDR1 (Analog pin 0)
    ADMUX = (1 << REFS0);

    // Enable ADC and set ADC prescaler to 64
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
}

int main(void)
{
    setup();

    uint16_t val1;
    uint16_t val2;
    uint8_t pos = 90;

    while (1)
    {
        // Read the value from LDR1 (Analog pin 0)
        ADMUX &= ~(1 << MUX0);
        ADCSRA |= (1 << ADSC); // Start conversion
        while (ADCSRA & (1 << ADSC))
        {
        } // Wait for conversion to complete
        val1 = ADC;

        // Read the value from LDR2 (Analog pin 1)
        ADMUX |= (1 << MUX0);
        ADCSRA |= (1 << ADSC); // Start conversion
        while (ADCSRA & (1 << ADSC))
        {
        } // Wait for conversion to complete
        val2 = ADC;

        if (val1 > (val2 + 200))
        {
            if (pos < 180)
                pos = pos + 1;
            servoWrite(pos);
            _delay_ms(200);
        }
        else if (val2 > (val1 + 200))
        {
            if (pos > 0)
                pos = pos - 1;
            servoWrite(pos);
            _delay_ms(200);
        }
    }

    return 0;
}

// #include <avr/io.h>
// #include <stdlib.h>
// #include <util/delay.h>

// #define SERVO_PIN PB3 // Pin connected to the servo

// void servoWrite(uint8_t angle)
// {
//     uint16_t pulseWidth = (angle * 10) + 600; // Calculate pulse width in microseconds

//     // Set the pulse width in Timer/Counter2 registers
//     OCR2A = (pulseWidth / 8) - 1; // Adjust for prescaler

//     _delay_ms(500); // Wait for the servo to move to the desired angle
// }

// void setup()
// {
//     // Configure Timer/Counter2 for Fast PWM mode with non-inverted output
//     TCCR2A = (1 << COM2A1) | (1 << WGM21) | (1 << WGM20);
//     TCCR2B = (1 << CS22); // Prescaler of 64

//     // Set the servo pin as an output
//     DDRB |= (1 << SERVO_PIN);

//     // Initialize the servo to the initial position
//     servoWrite(90);

//     // Configure ADC for LDR1 (Analog pin 0)
//     ADMUX = (1 << REFS0);

//     // Enable ADC and set ADC prescaler to 64
//     ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
// }

// int main(void)
// {
//     setup();

//     uint16_t val1;
//     uint16_t val2;
//     uint8_t pos = 90;
//     uint8_t prevPos = 90;

//     while (1)
//     {
//         // Read the value from LDR1 (Analog pin 0)
//         ADMUX &= ~(1 << MUX0);
//         ADCSRA |= (1 << ADSC); // Start conversion
//         while (ADCSRA & (1 << ADSC))
//         {
//         } // Wait for conversion to complete
//         val1 = ADC;

//         // Read the value from LDR2 (Analog pin 1)
//         ADMUX |= (1 << MUX0);
//         ADCSRA |= (1 << ADSC); // Start conversion
//         while (ADCSRA & (1 << ADSC))
//         {
//         } // Wait for conversion to complete
//         val2 = ADC;

//         if (val1 > (val2 + 200))
//         {
//             if (pos < 180)
//                 pos = pos + 1;
//         }
//         else if (val2 > (val1 + 200))
//         {
//             if (pos > 0)
//                 pos = pos - 1;
//         }

//         // Check if there's a significant change in position
//         if (abs(pos - prevPos) >= 3)
//         {
//             servoWrite(pos);
//             _delay_ms(200);
//             prevPos = pos;
//         }
//     }

//     return 0;
// }
