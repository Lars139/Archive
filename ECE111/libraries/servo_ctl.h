/** 
 * @file
 * @author Robert L. Phillips III
 * @author Scott Rosenbalm
 * @author Joey Tomlinson
 * @author Dan Albert
 * @date Last updated 8/24/12
 * @version 1.2
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * @section DESCRIPTION
 * 
 * Includes functions for sending and receiving data to and from the computer
 * and moving the motor accordingly
 * 
 * @section HARDWARE
 * Target Device: ATTINY261
 */
 

/**
 * Calculates the absolute value of the given number
 */
#define ABS(x) ((x < 0) ? -x : x)

/**
 * Lower bound for the motor position when the Tiny looks for the
 * position where the solar panel receives the most light
 */
#define LOWER_BOUND 0

/**
 * Upper bound for the motor position when the Tiny looks for the
 * position where the solar panel receives the most light
 */
#define UPPER_BOUND 255

/** 
 * The motor forward direction
 */
#define FORWARD 1

/** 
 * The motor reverse direction
 */
#define REVERSE 0

/** 
 * The motor stop moving command
 */
#define STOP 0

/** 
 * The motor counter-clockwise motion command
 */
#define CCW 1

/** 
 * The motor clockwise motion command
 */
#define CW 2

/** 
 * The default duty cycle for the PWM on PB5, which determines the motor
 * speed
 */
#define SERVO_SPEED 50

/** 
 * The max error for the motor position that is considered acceptable
 */
#define DEADBAND 15

/** 
 * The time the motor is allowed to correct its position before it stops
 */
#define SERVO_POSITION_TIMEOUT 1000

/** 
 * The potentiometer ADC channel
 */
#define POT_ADC 5


/**
 * Changes the direction of the servo motor.
 * 
 * @param dir Direction of motor motion.
 */
void SetMotorDirection(int dir);

/**
 * Checks the current position of the servo and calculates the error from its destination.
 * @param destination The destination of the servo.
 * @return The error between the servo's current position and its destination.
 */
int ServoError(uint8_t destination);


/**
 * Updates the servo to turn clockwise or
 * counter-clockwise to reach its destination.
 */
void UpdateServo(uint8_t destination);


/**
 * Moves the servo to the desired position.
 * 
 * @param destination The position that the servo should move to.
 * @param seekTime The time that the servo spends locking on to its destination in milliseconds (roughly).
 */
void setServoPosition(uint8_t destination, uint16_t seekTime);
