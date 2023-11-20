#include <avr/io.h>
#include <util/delay.h>
#include <Servo.h>

Servo myservo;
int ldr1_pin = 14;
int ldr2_pin = 15;
int val1;
int val2;
int pos = 90;

void setup()
{
    myservo.attach(5);
    DDRD |= (1 << PD6);
    TCCR0A = 0b10000011;
    OCR0A = 20;
}

int main(void)
{
    setup();

    while (1)
    {
        val1 = analogRead(ldr1_pin);
        val2 = analogRead(ldr2_pin);

        if (val1 > (val2 + 200))
        {
            if (pos < 180)
                pos = pos + 1;
            myservo.write(pos);
            PORTD |= (1 << PD6);
            _delay_ms(200);
        }
        else if (val2 > (val1 + 200))
        {
            if (pos > 0)
                pos = pos - 1;
            myservo.write(pos);
            PORTD &= ~(1 << PD6);
            _delay_ms(200);
        }
    }

    return 0;
}
