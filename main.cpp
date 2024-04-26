#include "mbed.h"
#include "motor.h"
#include "tunes.h"
#include "pwm_tone.h"
#include "PROJ100_Encoder.h"
#include "PROJ100_Encoder_Tests.h"

#define TIME_PERIOD 10             //Constant compiler Values here 10 equates to 10ms or 100Hz base Frequency
#define ENCODER_PIN_LEFT            D8
#define ENCODER_PIN_RIGHT           D6 
#define PULSES_PER_ROTATION         20
#define DEBOUNCE_US                 30000

DigitalIn microswitch1(D4);         //Instance of the DigitalIn class called 'microswitch1'
DigitalIn microswitch2(D3);         //Instance of the DigitalIn class called 'microswitch2'
DigitalIn myButton(USER_BUTTON);    //Instance of the DigitalIn class called 'myButton'   
DigitalOut greenLED(LED1);          //Instance of the DigitalOut class called 'greenLED'

Motor Wheel(D13,D11,D9,D10);      //Instance of the Motor Class called 'Wheel' see motor.h and motor.cpp

PROJ100_Encoder right_encoder (ENCODER_PIN_RIGHT,PULSES_PER_ROTATION);  //Instance of the PROJ100Encoder class called 'right_encoder'
PROJ100_Encoder left_encoder(ENCODER_PIN_LEFT,PULSES_PER_ROTATION);     //Instance of the PROJ100Encoder class called 'left_encoder'

UnbufferedSerial ser(USBTX,USBRX,115200);   // Serial object for printing info

int main ()
{
    // Clear the terminal and print an intro
    printf("\033[2J\033[1;1H\r\n");
    printf("Plymouth University PROJ100 2023/24 Optical Encoder Demonstration\n\r");

    // Set the PWM frequency
    Wheel.Period_in_ms(TIME_PERIOD);                

    // Ensure our motors and encoders are stopped at the beginning
    right_encoder.stop();
    left_encoder.stop();
    Wheel.Stop();

    // The encoder pulses can be noisy and so are debounced within the class
    // You can experiment with changing the debouce time if you wish
    left_encoder.setDebounceTimeUs(DEBOUNCE_US);
    right_encoder.setDebounceTimeUs(DEBOUNCE_US);

    // Wait for the blue button to be pressed
    printf("Press Blue Button To Begin\n\r");
    while (myButton == 0){greenLED = !greenLED; ThisThread::sleep_for(100ms);}

    // Start the encoders
    left_encoder.start();
    right_encoder.start();

    /*********************ENCODER TESTS***************/
    // These contain while(1) loops so ensure that they are removed or commented out when running your own code
    // If these lines are left in the lines below will never run
    /*************************************************/

    // simple_test();
    //speed_test();

    while(true){

        // Write the parts of your code which should run in a loop between here..
        Wheel.Speed(1, 1);
        wait_us(8928*1000);// forward 1 m 
        
        Wheel.Stop();
        
        wait_us(2000*1000); // to allow for use in the 1m straight line task 
        
        Wheel.Speed(1, -1);
        wait_us(2000*1000); // turn 180 deg to the right 
        
        Wheel.Stop();
        wait_us(1000); // stopping the wheel for a small amount of time to allow for a smoother transition 
        
        Wheel.Speed(1, 1);
        wait_us(8928*1000); // going back 1m in a straight line 
        
        Wheel.Speed(-1, 1);
        wait_us(2000*1000); // turning 180 deg to the left 
        
        Wheel.Stop(); // stopping the wheels completely 
        starwars(5); // playing the starwars imperial march theme tune 
        wait_us(1000); // extra wait time for the code to finish 
        
        wait_us(5000*1000); // used to stop the code from running again before the chance to grab 
          
    /* Wheel.Speed(1, 1);
        wait_us(2000*1000);
        
        Wheel.Speed(-0.9,0.4); 
        wait_us(1000*1000); 
        Wheel.Speed(0.4,-0.9); 
        wait_us(1000*1000); 
        Wheel.Speed(-0.9,0.4); 
        wait_us(750*1000); 
        Wheel.Speed(0.4,-0.9); 
        wait_us(750*1000); 
        Wheel.Speed(-0.9,0.4); 
        wait_us(500*1000); 
        Wheel.Speed(0.4,-0.9); 
        wait_us(500*1000); 
        Wheel.Speed(-0.9,0.4); 
        wait_us(400*1000); 
        Wheel.Speed(0.4,-0.9); 
        wait_us(400*1000); 
        Wheel.Speed(-0.9,0.4); 
        wait_us(300*1000); 
        Wheel.Speed(0.4,-0.9); 
        wait_us(300*1000); 
        Wheel.Speed(-0.9,0.4); 
        wait_us(200*1000); 
        Wheel.Speed(0.4,-0.9); 
        wait_us(200*1000); 
        Wheel.Speed(-0.9,0.4); 
        wait_us(100*1000);
        Wheel.Speed(0.4,-0.9); 
        wait_us(100*1000); 
        Wheel.Speed(-0.9,0.4); 
        wait_us(200*1000); 
        Wheel.Speed(0.4,-0.9); 
        wait_us(200*1000); 
        Wheel.Speed(-0.9,0.4); 
        wait_us(100*1000); 
        Wheel.Speed(0.4,-0.9); 
        wait_us(100*1000); 
        Wheel.Speed(-0.9,0.4); 
        wait_us(200*1000); 
        Wheel.Speed(0.4,-0.9); 
        wait_us(200*1000); 
        Wheel.Speed(-0.9,0.4); 
        wait_us(100*1000); 
        Wheel.Speed(0.4,-0.9); 
        wait_us(100*1000); 
        Wheel.Speed(-0.9,0.4); 
        wait_us(200*1000); 
        Wheel.Speed(0.4,-0.9); 
        wait_us(200*1000); 
        Wheel.Speed(-0.9,0.4); 
        wait_us(100*1000); 
         Wheel.Speed(0.4,-0.9); 
        wait_us(100*1000); 
        Wheel.Speed(-0.9,0.4); 
        wait_us(200*1000); 
        Wheel.Speed(0.4,-0.9); 
        wait_us(200*1000); 
       Wheel.Speed(-0.9,0.4); 
       wait_us(100*1000); 
       Wheel.Speed(0.4,-0.9); 
        wait_us(100*1000); 
        starwars(5);
        wait_us(1000);  */

        // ..and here

    };
}