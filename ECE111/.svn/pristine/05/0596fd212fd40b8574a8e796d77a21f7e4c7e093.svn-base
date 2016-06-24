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

#include "usb.h"
#include <string.h>
#include <stdlib.h>

DllExport int UsbSendData(usbDevice_t *dev, uchar command, uchar * dataToSend, int length, uchar * outBuffer, int outBufferLength)
{

    if (dev==NULL)
        return DEVICE_NOT_OPEN;

    ReportOut_t reportOut;
    ReportIn_t reportIn;

    reportOut.reportSize = length;
    reportOut.command = command;

    if (reportOut.reportSize <= 6)
        reportOut.reportID = 1;
    else if (reportOut.reportSize <= 14)
        reportOut.reportID = 2;
    else if (reportOut.reportSize <=248)
        reportOut.reportID = 3;
    else
        return MULTIPLE_TRANSMISSION_REQUIRED;

    if (outBufferLength > 250)
        return OUTBUF_EXCEEDS_MAX;


    /* copy the data to the transmit buffer */
    int i;
    for (i=0; i<reportOut.reportSize; i++)
            reportOut.data[i] = dataToSend[i];

    /* send out the data */
    if (!HidD_SetFeature(dev, (void*)&reportOut, sizeof(ReportOut_t)))
        return TRANSMISSION_FAILED;

    /* Receive the data */
    if (outBufferLength <= 7)
        reportIn.reportID = 1; // Up to 7 bytes of data to receive, plus 1 size byte
    else if (outBufferLength <= 15)
        reportIn.reportID = 2;
    else if (outBufferLength <=249)
        reportIn.reportID = 3;

    if (!HidD_GetFeature(dev, (void*)&reportIn, sizeof(ReportIn_t)))
        return RECEIVE_FAILED;

    if (outBuffer!=NULL)
        for (i=0; i<reportIn.reportSize; i++)
            outBuffer[i] = reportIn.data[i];

    /* The return code should be held in this value */
    return reportIn.reportSize;
}

/** Helper function for UsbOpenDevice **/
static void convertUniToAscii(char *buffer)
{
    unsigned short  *uni = (unsigned short*)buffer;
    char            *ascii = buffer;
    while(*uni != 0){
        if(*uni >= 256){
            *ascii++ = '?';
        }else{
            *ascii++ = *uni++;
        }
    }
    *ascii++ = 0;
}

DllExport int UsbOpenDevice(usbDevice_t **device, int vendor, char *vendorName, int product, char *productName)
{
    GUID                                hidGuid;        // GUID for HID driver
    HDEVINFO                            deviceInfoList;
    SP_DEVICE_INTERFACE_DATA            deviceInfo;
    SP_DEVICE_INTERFACE_DETAIL_DATA     *deviceDetails = NULL;
    DWORD                               size;
    int                                 i, openFlag = 0;  // may be FILE_FLAG_OVERLAPPED
    int                                 errorCode = USBOPEN_ERR_NOTFOUND;
    HANDLE                              handle = INVALID_HANDLE_VALUE;
    HIDD_ATTRIBUTES                     deviceAttributes;

    HidD_GetHidGuid(&hidGuid);
    deviceInfoList = SetupDiGetClassDevs(&hidGuid, NULL, NULL, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);
    deviceInfo.cbSize = sizeof(deviceInfo);
    for(i=0;;i++){
        if(handle != INVALID_HANDLE_VALUE){
            CloseHandle(handle);
            handle = INVALID_HANDLE_VALUE;
        }
        if(!SetupDiEnumDeviceInterfaces(deviceInfoList, 0, &hidGuid, i, &deviceInfo))
            break;  // no more entries
        // first do a dummy call just to determine the actual size required
        SetupDiGetDeviceInterfaceDetail(deviceInfoList, &deviceInfo, NULL, 0, &size, NULL);
        if(deviceDetails != NULL)
            free(deviceDetails);
        deviceDetails = (SP_DEVICE_INTERFACE_DETAIL_DATA*)malloc(size);
        deviceDetails->cbSize = sizeof(*deviceDetails);
        // this call is for real:
        SetupDiGetDeviceInterfaceDetail(deviceInfoList, &deviceInfo, deviceDetails, size, &size, NULL);
#if 0
        // If we want to access a mouse our keyboard, we can only use feature
        // requests as the device is locked by Windows. It must be opened
        // with ACCESS_TYPE_NONE.
        //
        handle = CreateFile(deviceDetails->DevicePath, ACCESS_TYPE_NONE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, openFlag, NULL);
#endif
        // attempt opening for R/W -- we don't care about devices which can't be accessed
        handle = CreateFile(deviceDetails->DevicePath, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, openFlag, NULL);
        if(handle == INVALID_HANDLE_VALUE){
            // errorCode = USBOPEN_ERR_ACCESS; opening will always fail for mouse -- ignore
            continue;
        }
        deviceAttributes.Size = sizeof(deviceAttributes);
        HidD_GetAttributes(handle, &deviceAttributes);
        if(deviceAttributes.VendorID != vendor || deviceAttributes.ProductID != product)
            continue;   //ignore this device
        errorCode = USBOPEN_ERR_NOTFOUND;
        if(vendorName != NULL && productName != NULL){
            char    buffer[512];
            if(!HidD_GetManufacturerString(handle, buffer, sizeof(buffer))){
                errorCode = USBOPEN_ERR_IO;
                continue;
            }
            convertUniToAscii(buffer);
            if(strcmp(vendorName, buffer) != 0)
                continue;
            if(!HidD_GetProductString(handle, buffer, sizeof(buffer))){
                errorCode = USBOPEN_ERR_IO;
                continue;
            }
            convertUniToAscii(buffer);
            if(strcmp(productName, buffer) != 0)
                continue;
        }
        break;  // we have found the device we are looking for!
    }
    SetupDiDestroyDeviceInfoList(deviceInfoList);
    if(deviceDetails != NULL)
        free(deviceDetails);
    if(handle != INVALID_HANDLE_VALUE){
        *device = (usbDevice_t *)handle;
        errorCode = 0;
    }
    return errorCode;
}

DllExport int UpdateServoPosition(usbDevice_t *dev, int position)
{
    uchar delay = 1;

    if(position < 0)
        position = 0;
    else if(position > 255)
        position = 255;

    uchar data_out[7] = {delay, position, position, position, position, position, position};
    uchar response[6];

    UsbSendData(dev, TRANSMIT, data_out, 7, response, 6);
    if(response[0] != 0xA9)
        return -1;
    else
        return response[1];
}

DllExport int UsbEstablishConnection(usbDevice_t *dev)
{
    uchar dataToSend[2] = {8, 0};
    if (UsbSendData(dev, CONNECT, dataToSend, 2, NULL, 0) != 1)
        return CONNECT_MODE_FAILED;

    Sleep(100);

    uchar testData [7] = {1, 0, 0, 0, 0, 0, 0};
    uchar reply[6];
    if (UsbSendData(dev, TRANSMIT, testData, 7, reply, 6) != 6)
    {
        UsbCloseDevice(dev);
        return TINY_CONNECT_FAILED;
    }

    if (reply[0] !=0xA9)
    {
        UsbCloseDevice(dev);
        return reply[0];
    }

    return 0;
}

DllExport void UsbCloseDevice(usbDevice_t * dev)
{
    if (dev!=NULL)
    {
        UsbSendData(dev, DISCONNECT, NULL, 0, NULL, 0);

        CloseHandle(dev);
        dev = NULL;
    }
}



