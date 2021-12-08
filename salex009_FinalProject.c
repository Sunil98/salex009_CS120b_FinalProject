//'* Author:  Sunil Alexander
//* Lab Section: 021
// * Assignment: Lab Final Project
// * Exercise Description: [optional - include for your own benefit]
// *
// * I acknowledge all content contained herein, excluding template or example
// * code, is my own original work.// *
// *  Complexity 1 demo: https://drive.google.com/file/d/1u_rLmP5nUXY-HwEEr2AvZb6z6dsKXMWZ/view?usp=sharing
//    https://drive.google.com/file/d/1Niaap2sKQjGRSW3e9IFZhQNANrRmxlKP/view?usp=sharing
//
//    Complexity 2 demo: https://drive.google.com/file/d/1ZlpfcudxScRiedtSmgaA8Bs-b-qnyizu/view?usp=sharing
//   
//    Full Demo: 
// *

#include <avr/io.h>
#include <util/delay.h>

int16_t x1;
int16_t y1;
int16_t x2;
int16_t y2;

static inline void timer1Servo(void)
{
  TCCR1A |= 1<<WGM11 | 1<<COM1A1 | 1<<COM1B1;   //SERVO 1
  TCCR1B |= 1<<WGM12 |1<<WGM13 |1<<CS10;
  ICR1=19999;
  DDRB |= (1 << PB1);                           //PWM1

  TCCR1A |= 1<<WGM11 | 1<<COM1A1 | 1<<COM1B1;   //SERVO 2
  TCCR1B |= 1<<WGM12 |1<<WGM13 |1<<CS10;
  ICR1=19999;
  DDRB |= (1 << PB2);                           //PWM2

  TCCR1A |= 1<<WGM11 | 1<<COM1A1 | 1<<COM1B1;   //SERVO 3
  TCCR1B |= 1<<WGM12 |1<<WGM13 |1<<CS10;
  ICR1=19999;
  DDRB |= (1 << PB3);                           //PWM3

  TCCR1A |= 1<<WGM11 | 1<<COM1A1 | 1<<COM1B1;   //SERVO 4
  TCCR1B |= 1<<WGM12 |1<<WGM13 |1<<CS10;
  ICR1=19999;
  DDRD |= (1 << PD5);                           //PWM4
}





static inline void startADC()
{
  ADMUX |= (1 << REFS0);
  ADCSRA |= (1 << ADPS1) | (1 << ADPS0);            //JOYSTICK 
  ADCSRA |= (1 << ADEN);
}




uint16_t readADC(uint8_t channel)
{
  ADMUX = (0x0F & ADMUX) | channel;
  ADCSRA |= (1 << ADSC);
  loop_until_bit_is_clear(ADCSRA, ADSC);
  return(ADC);
}

//Concurrency
enum Inputs{Start,In}Input;

 void Joystick()
 {
  switch(Input)
  {
    case Start:
        Input = In; break;
    case In:
    Input = In;
    x1 = readADC(0);
    y1 = readADC(1);
    x2 = readADC(2);
    y2 =readADC(3);
    break;
    default:
    break;
  }
 }


 enum Outputs{Begin,Out}Output;

 void Servos()
 {
  switch(Output)
  {
    case Begin:
        Output = Out; break;
    case Out:
    Output = Out;
   OCR1A = x1 * 3.5;
   OCR1B = y1 * 3.5;
   OCR2A = x1 * 3.5;
   OCR0B = y1 * 3.5;
    break;
    default:
    break;
  }
 }

 

int main(void)
{
  timer1Servo();
  startADC();

  while (1)
  {
    
    void Joystick();
    void Servos();


  

  
  _delay_ms(10);
    
  }

   return 0;


    
}
