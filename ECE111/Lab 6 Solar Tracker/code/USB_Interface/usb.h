/**
  * @file
  * @author Robert L. Phillips III
  * @note Code adapted from the Tiny26 test widget written by Ben Porter
  * @version 1.1
  *
  * @section SUMMARY
  * Project:            tiny26usb.dll
  *
  * Build Environment:  Code::Blocks 10.05
  *
  * Compiler:           GNU GCC Compiler
  *
  * Linked Libraries:
  * - libhid
  *
  * - libhidparse
  *
  * - libsetupapi
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
  * Library definition for the tiny26usb library.  This library allows the user
  * to forward commands to the Tiny26 microcontroller using the OSUisp2 universal
  * programmer.  In order for this library to work, the Tiny26 must have the correct
  * firmware installed because of the way the library checks to ensure that the
  * Tiny26 is connected and receiving the commands from the computer.
  *
  * This library is meant to abstract away the inner workings of the USB connection
  * to the OSUisp2 and the Tiny26 for the purpose of an ECE111 demo.
  *
  * Example Usage (for example Python usage, see the ECE111 Python GUI demo):
  *
  *         usbDevice_t * dev;
  *
  *         UsbOpenDevice(&dev, 0x16c0, "beaversource.oregonstate.edu/projects/osuisp2", 0x05df, "OSUisp2");
  *
  *         UsbEstablishConnection(dev);
  *
  *         UsbUpdateServoPosition(dev, 150);
  *
  *         UsbCloseDevice(dev);
  *
  * @section HARDWARE
  * Target Device: OSUisp2 Universal Programmer
  */


#ifndef _USB_H
#define _USB_H


#include <windows.h>
#include <setupapi.h>
#include <ddk/hidsdi.h>
#include <ddk/hidpi.h>
#include <ddk/hidusage.h>

/**
 * Causes the method to be exported to the DLL
 */
#define DllExport   __declspec( dllexport )

/**
 * USB connection was opened successfully
 */
#define USBOPEN_SUCCESS                 0

/**
 * There were insufficient permissions to open a USB connection
 */
#define USBOPEN_ERR_ACCESS              1

/**
 * An I/O error caused the USB connection to fail
 */
#define USBOPEN_ERR_IO                  2

/**
 * The USB device was not found
 */
#define USBOPEN_ERR_NOTFOUND            3

/**
 * The USB device handle has not been opened
 */
#define DEVICE_NOT_OPEN                 -1

/**
 * The size of the output buffer exceeds the max
 */
#define OUTBUF_EXCEEDS_MAX              -2

/**
 * The size of the send buffer is too large
 */
#define MULTIPLE_TRANSMISSION_REQUIRED  -3

/**
 * USB transmission to the HID failed
 */
#define TRANSMISSION_FAILED              -4

/**
 * USB HID failed to receive a response
 */
#define RECEIVE_FAILED                  -5

/**
 * The OSUisp2 Universal Programmer could not be put into connect mode
 */
#define CONNECT_MODE_FAILED             -1

/**
 * A connection to the Tiny261 could not be established
 */
#define TINY_CONNECT_FAILED             -2

/**
 * OSUisp2 connect mode command
 */
#define CONNECT                         1

/**
 * OSUisp2 disconnect mode command
 */
#define DISCONNECT                      2

/**
 * OSUisp2 transmit mode command
 */
#define TRANSMIT                        3

/**
 * Windows USB device type
 */
typedef struct usbDevice usbDevice_t;


#ifndef uchar
/**
 * uchar assignemnt unsigned char
 */
typedef unsigned char uchar;
#endif



/**
 * Output Report Structure
 */
typedef struct ReportOut
{
    /**
     * The ID of the report
     */
    unsigned char reportID;

    /**
     * The size of the report
     */
    unsigned char reportSize;

    /**
     * The command to be sent
     */
    unsigned char command;

    /**
     * The data out buffer
     */
    unsigned char data [248];
} ReportOut_t;


/**
 * Input Report Structure
 */
typedef struct ReportIn
{
    /**
     * The ID of the report
     */
    unsigned char reportID;

    /**
     * The size of the report
     */
    unsigned char reportSize;

    /**
     * The data in buffer
     */
    unsigned char data [249];
} ReportIn_t;


/**
 * Send and receive data over USB (Windows)
 *
 * @param dev
 * @param command to send to the device
 * @param dataToSend The data buffer to be sent
 * @param length The length of the data to send
 * @param outBuffer The buffer to hold response (8 characters)
 * @param outBufferLength The expected length of the response data
 *
 * @return length The length of the data received
 *
 * @see CONNECT
 * @see DISCONNECT
 * @see TRANSMIT
 * @see DEVICE_NOT_OPEN
 * @see OUTBUF_EXCEEDS_MAX
 * @see MULTIPLE_TRANSMISSION_REQUIRED
 * @see TRANSMISSION_FAILED
 * @see RECEIVE_FAILED
 */
int UsbSendData(usbDevice_t *dev, uchar command, uchar * dataToSend, int length, uchar * outBuffer, int outBufferLength);


/**
 * Open a connection to the specified USB device
 *
 * @param device A pointer to the device pointer that is to hold the device instance
 * @param vendor The vendor ID of the desired USB device
 * @param vendorName The name of the vendor corresponding to the desired USB device
 * @param product The product ID of the desired USB device
 * @param productName The name of the USB device
 *
 * @return The return code that indicates whether or not an error occurred
 *
 * @see USBOPEN_SUCCESS
 * @see USBOPEN_ERR_ACCESS
 * @see USBOPEN_ERR_IO
 * @see USBOPEN_ERR_NOTFOUND
 */
int UsbOpenDevice(usbDevice_t **device, int vendor, char *vendorName, int product, char *productName);


/**
 * Closes the connection to the Tiny261 and OSUisp2 Universal Programmer
 *
 * @param dev The handle to the USB device that corresponds to the connection between
 * the computer and the OSUisp2
 */
void UsbCloseDevice (usbDevice_t * dev);


/**
 * Establishes a connection to the Tiny261
 *
 * @param dev The handle to the USB device that corresponds to the connection between
 * the computer and the OSUisp2
 *
 * @see CONNECT_MODE_FAILED
 * @see TINY_CONNECT_FAILED
 *
 * @return The return code that indicates whether a connection to the Tiny261 was successfully
 * established
 */
int UsbEstablishConnection(usbDevice_t *dev);


/**
 * Sends a request to the Tiny261 to update the motor position
 *
 * Moves the motor unless 0 or 255 is given as the position parameter.  If 0 is given as the
 * position, the motor will not move and the Tiny will only respond with the solar measurements.
 * If 255 is given as the position, it will cause the Tiny to search for the position with
 * the highest solar measurements.  If the given position is out of range (position range =
 * 0 <= position <= 255), 1 or 254 will be sent instead depending on which extrema was violated.
 *
 * @param dev The handle to the USB device that corresponds to the connection between the
 * computer, OSUisp2, and Tiny261
 * @param position The position that the motor is to be moved to
 *
 * @return The return code that indicates whether the transmission was successful
 */
int UpdateServoPosition(usbDevice_t *dev, int position);





#endif


