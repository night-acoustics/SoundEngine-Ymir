// *******************
// Interupt based Synth test code.
// *******************
#include <avr/io.h>
#include <avr/interrupt.h>

// song
int frequencies[3] = {22,17,15}; 

// Bit set, clear, check and toggle macros
// -----------------------------------------------------
// sets the bit at bit in y position in x registry.
#define SET(x,y) (x |=(1<<y))	
// clears the bit at bit in y position in x registry. 	        		 
#define CLR(x,y) (x &=(~(1<<y)))       		
// checs the bit at bit in y position in x registry. 	    
#define CHK(x,y) (x & (1<<y))    
// toggles the bit in y postion in x registry.       			
#define TOG(x,y) (x ^=(1<<y))            			
// -----------------------------------------------------

#define ERROR_LED_1 0

// local variables.
int counter = 0;
int interen = 0;
int noice = 0;
int pointer = 0;

int main(void)
{
    // run setup
    setup();
    // While loop much importantant. counter does not run with out.
    while (1)
    {
        // counter++;
        // // do nothing
        // if (counter == 200)
        // {
        //     PORTB ^= (1 << PORTB0);
        //     counter = 0;
        //     pointer++;
        //     pointer = pointer%3;
        //     noice = frequencies[pointer];            
        // }        
    }
}

void setup(){
    // sets all portB as output.
    SET(DDRB,ERROR_LED_1);
    // Set timer to 0;
    // TCNT0 = 0;
    SET(TCNT0,0);
    // Configure the timer
    TCCR0 = (1 << WGM01) // << Bit shift to the left.
                         // WGM01 = 3.
                         // 1 denotes the value for the given flag
                         // WGM01 is the flags index
                         // meaning we put 1 into the 4th bit in the register for WGM01.
                         // writing it this way makes our code more resistent to changes.
                         // because if the location for WGM01 changes the code remains the same.
                         // setting the WGM01 flag Sets the TCCR0 8 bit timer to use CTC,
                         // meaning Clear Timer on Compare Match (CTC) mode
            | (1 << CS02)  //
            | (1 << CS00); // setting these two register flags, set up timer with prescaler = 1024.
            //| (1 << CS01);

    // Number of ticks for the timer.
    OCR0 = 97;
    // enable compare interrupt.
    TIMSK = (1 << OCIE0);
    // Sets I bit. enable global interrupts.
    sei();
}

ISR(TIMER0_COMP_vect)
{
    counter ++;
    if(counter >=10)
    {
        if(CHK(PORTB,ERROR_LED_1))
        {
            CLR(PORTB,ERROR_LED_1);
        }
        else
        {
            SET(PORTB,ERROR_LED_1);
        }
        
        //PORTB ^= (1 << PORTB0);
        counter =0;
    }
    // interen++;
    // if (interen >= noice)
    // {
    //     PORTB ^= (1 << PORTB7);
    //     interen = 0;
    // }    
}
