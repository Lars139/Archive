/*
Block Comment
Anything I put within this block is ignored by the compiler
It has no effect on the program
*/

// Line Comment - All text following the double slash on this line is ignored

/*
 * This document uses Doxygen style comments
 * Doxygen is a documentation generator that automatically generates documentation for your code in many formats
 * Adhering to the Doxygen comment style conventions separates the content of your comments their formatting.
 * This makes it easy to generate documentation on the fly in a variety of formats
 *
 */

// The /** designates the start of the doxygen comment
// Each @ statement designates a special doxygen item

//This doxygen comment descirbes the entire file:
/** 
 * @file
 * @author Joey Tomlinson
 * @version 1.0
 *
 * @section LICENSE
 * 
 * Here you can specify a licence which governs the use of the software in this file.
 * 
 * @section DESCRIPTION
 * 
 * Write a short description of your file here.
 * In this case, this program serves as a simple example of an embedded microcontroller
 * application which measures the height of salt water in a tank, calculates the mass
 * of the tank, and activates an alarm if the mass excededs a certine threshold.
 * 
 */

#include <util/delay.h>
 
#define DENSITY_OF_SALT_WATER 1027.2f

float massOfTank (int length, int width, int height, float fluid_density);
void alarm();
 
 
//This doxygen comment descirbes the main function
/**
 * Put a short description of the function here.  In this case the main function
 * is where your program starts execution.
 * 
 * @return Describe the return value of the function here.  In this case, the main function
 * returns an int variable type.  This is a convention in the C language.  When a C program
 * is run under an opperating system, the return value is returned to the opperating system
 * and is often used to report sucess or failure of the program.  In embedded software such
 * as that written for the ATTINY26 which you use in lab, the return value of main is usually
 * ignored
 * 
 */
  
int main (void) {
	
	/*
	 * First we define the data direction for digital IO ports PORTA and PORTB
	 * Each digital IO pin on the microcontroller can be an input or an output
	 * Input pins recieve data from an input device such as a switch
	 * Output pins control an output device like an LED
	 * The 0x in the definition specifies that the number is in hexadecimal format
	*/
	
	DDRA = 0x00; // Sets all pins in PORTA to INPUTS (specified by a 0)
	DDRB = 0xFF; // Sets all pins in PORTB to OUTPUTS (specified by a 1)
	
	/*
	 * Next we declare variables to use to temporarily store data while we do
	 * computations on it.  In C, variables are always declared with a data type.
	 * The data types we use here are defined as follows:
	 * 
	 * int		stores integers between -2147483648 and 2147483647
	 * float	stores real numbers with a decimal place (approximately 7 digits of precision)
	 * double	like a float but more precise (approximately 15 digits of precision)
	 * 
	 */
	
	int length; // Declares a variable named length with an int data type
	length = TANK_LENGTH; // Sets length equal to TANK_LENGTH which is defined in example.h
	int width = TANK_WIDTH; // Declares another int and sets it equal to TANK_WIDTH in one line
	int height;
	float mass; //declares a float variable named mass
	
	/* Now we use a while loop to repeatedly compute the mass of the water in the tank and trigger
	 * an alarm if it is too high.
	 * 
	 * The while loop checks the logical expression inside the ().  If it is true, the code between the {}
	 * is executed.  When that code finishes, the condition is checked again, and if it is true, the code
	 * inside the {} runs again.  This continues until the expression becomes false.  When it becomes
	 * false, program execution resumes after the closing {
	 */
	
	while (TRUE) {
		
		height = PORTA; // Sets the height variable equal to the binary electrical signal present on PORTA
		// In this case PORTA would be connected to a device which measured the height of the water in the tank
		
		// Next, we call a function called massOfTank (defined below) to calculate the mass of the water in the tank
		// Variables are passed to the function in the order they are defined in the function definition
		mass = massOfTank(length, width, height, DENSITY_OF_SALT_WATER);
		
		// The if statement checks the logical expression inside the () and executes the code inside the {}
		// only if it is true
		
		// The greater than operator (>) evaluates to true if mass is greater than MASS_ALARM_THRESHOLD
		if (mass > MASS_ALARM_THRESHOLD) { 
			alarm(); // function call to alarm() which is defined below
		} else { // the statment inside the else {} executes if the logical expression is false
			PORTB = 0x00; // in this case we are setting all of the pins on PORTB to 0, which turns off the alarm
		}
	}
}

//This doxygen comment descirbes the massOfTank function
/**
 * Calculates the mass of the tank of saltwater
 * 
 * @param length length of the tank in meters
 * @param width width of the tank in meters
 * @param height height of the water in the tank in meters
 * @param fluid_density density of the water in the tank
 * @return mass of the tank
 * 
 */
float massOfTank (int length, int width, int height, float fluidDensity) {
	int volume;
	float mass;
	volume = length*width*height; // Calculates volume ('*' is the multiplication opperator)
	mass = volume*fluidDensity; // Calculates mass
	return mass;
}

// This doxygen comment descirbes the alarm function
/**
 * Blinks Lights Connected to PORTB 10 times, signaling an alarm
 * 
 */
void alarm() { // the keyword void specifies that the alarm function doesn't return anything
	int i;
	
	/*
	 * We will use a for loop to blink the lights attached to PORTB 10 times.
	 * The syntax is for (initialization;condition;action) {}
	 * 
	 * The initialization statement runs once and sets i=0
	 * The statements inside the {} runs
	 * The action statment runs
	 * The condition statement is then checked. If the condition is true,
	 *      the statements in the {} runs again.
	 * This repeats untill the condition becomes false
	 * 
	 */
	for (i=0;i<10;i++) { 
		PORTB = 0b11111111; //turn all lights on port b on
		// The _delay_ms function pauses program execution for a specific number of
		// microseconds.  It is defined in delay.h, which is included in example.h
		_delay_ms(100); 
		PORTB = 0b00000000; //turn all lights on port b off
		_delay_ms(100);
	}
}
