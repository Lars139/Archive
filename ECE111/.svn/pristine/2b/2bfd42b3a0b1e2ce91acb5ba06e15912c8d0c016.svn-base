'''
The classes necessary to interface with the Tiny261 and OSUisp2

Created on Aug 17, 2012

@author: Robert L. Phillips III
@version: 1.0

@section DEPENDENCIES  
    -  tiny26usb.dll
         Contains the following methods that communicate commands to the Tiny26 microcontroller via
         the OSUisp2 programmer (See usb.c, usb.h and the OSUisp2 firmware in order to understand more
         about how the programmer acts as a middleman between the computer and Tiny26):
         
                int UsbOpenDevice(usbDevice_t **device, int vendor, char *vendorName, int product, char *productName)
                int UsbEstablishConnection(usbDevice_t *dev)
                int UsbUpdateServoPosition(usbDevice_t *dev, int speed)
                void UsbCloseDevice(usbDevice_t * dev)
                
    -  wxPython
          In order to show error messages, this module relies on wxPython to generate and show message
          boxes to the user
          
    -  ctypes
          Because the usb interface is written in C, ctypes is used to open up the tiny26usb DLL and
          use the methods that have been exported to it in a Python module.  Therefore, the previously
          written Tiny26 interface did not need to be ported to Python, but the C code needed to be
          modified to be exported as a DLL and called from Python code.
          
'''

import ctypes
import wx

from threading import Thread
from time import sleep

## Vendor ID of the OSUisp2 programmer.
vid = 0x16c0

## Product ID of the OSUisp2 programmer
pid = 0x05df

## The usb interface for the OSUisp2 and the Tiny261 is contained in this class.  It contains
# all the methods for establishing connections, closing connections, and sending request to the
# Tiny261 to move the servo and to get the ADC measurements from the solar panel.
class USB_Interface:
    
    ## Constructor for the usb interface
    def __init__(self, window):
        
        ## The frame that is associated with the USB interface
        self.window = window
        
        ## tiny26usb.dll library
        self.lib = None
        
        ## usbDevice_t * needed to establish a connection with OSUisp2 and
        # the Tiny
        self.device = None
        
        ## Holds the connection status
        self.connected = False
        
        # try to open the tiny26usb library and show an error box on failure
        try:
            self.lib = ctypes.cdll.LoadLibrary("./tiny26usb.dll")
        except:
            self.ShowErrorMsg("Failed to open tiny26usb.dll.  Is it located in the Motor Controller\nroot directory?", "Fatal Error")
            return
           
        # make sure the library is not empty and show an error message if it is
        if self.lib is not None:
            
            # give the device variable a void pointer value
            self.device = ctypes.c_void_p()
            
            # open up a connection to the OSUisp2 and show an error message on failure
            if (self.lib.UsbOpenDevice(ctypes.pointer(self.device), vid, "beaversource.oregonstate.edu/projects/osuisp2", pid, "OSUisp2") == 0):
                
                # establish a connection with the Tiny26 and show an error message on failure
                if(self.lib.UsbEstablishConnection(self.device) != 0):
                    self.ShowErrorMsg("Couldn't connect to the Tiny26!  Is the correct firmware\ninstalled?", "Connection Error")
                else:
                    
                    # indicate that the connection was succcessfully established
                    self.connected = True
            else:
                self.ShowErrorMsg("Couldn't find the programmer!  Is it plugged in and powered?", "Connection Error")
                    
        else:
            self.ShowErrorMsg("Something went wrong while opening tiny26usb.dll", "Fatal Error")
            
    ## Returns the connection status
    #
    # @param self: The object pointer
    def IsConnected(self):
        return self.connected
          
    ## Reads the output of the solar panel
    #
    # Sends a request to the Tiny to keep the motor in the current position
    # respond with the light measurements
    #
    # @param self: The object pointer
    def MeasureSolarPanel(self):
        
        # get the light measurements from the Tiny
        response = self.lib.UpdateServoPosition(self.device, 0)
        
        # show an error message if the response indicates an error
        if (response == -1):    
            self.ShowErrorMsg("Connection to the Tiny26 has been interrupted!", "Connection Lost")
            self.connected = False
            
        # return the response code
        return response
              
        
    ## Moves the solar panel to its optimal position
    #
    # Sends a request to the Tiny to search for the position that gives the solar
    # panel the most light.  The Tiny does not respond to any movement requests while
    # it is searching for the solar panel's optimal position
    #
    # @param self: The object pointer
    def FindMostSun(self):
        
        # causes the Tiny to initiate the sequence that searches for the position
        # of the solar panel with the most light
        response = self.lib.UpdateServoPosition(self.device, 255)
        
        # show an error message if the response indicates an error
        if (response == -1):    
            self.ShowErrorMsg("Connection to the Tiny26 has been interrupted!", "Connection Lost")
            self.connected = False
            
        # return the response code
        return response
    
    ## Moves the solar panel to the specified position
    #
    # Sends a request to the Tiny to move the servo to the specified position.  The
    # Tiny will not respond to any requests while it is moving the servo.  If the given
    # position is out of the valid range, the servo moves to 254 or 1 depending on
    # which extrema was violated
    #
    # @param self: The object pointer
    # @param position: The desired position (0 < position < 255)
    def SetSolarPosition(self, position):
        
        # cause the Tiny to move the servo to the supplied position
        response = self.lib.UpdateServoPosition(self.device, position)
        
        # show an error message if the response indicates an error
        if (response == -1):    
            self.ShowErrorMsg("Connection to the Tiny26 has been interrupted!", "Connection Lost")
            self.connected = False
             
        # return the response code
        return response
    
    ## Displays an error message box with the supplied message and title
    #
    # @param self: The object pointer
    # @param message: The desired message for the Message Box
    # @param title: The desired title for the Message Box
    def ShowErrorMsg(self, message, title):
        
        # defines a new message box
        msg = wx.MessageDialog(self.window, message, title, wx.OK | wx.ICON_ERROR)
        
        # shows the message box and destroys it when 'OK' is clicked
        msg.ShowModal()
        msg.Destroy()
        
    ## Cleans up the connection to the Tiny26
    #
    # Sends a request to the OSUisp2 Universal Programmer to disconnect from the Tiny
    #
    # @param self: The object pointer
    def CloseConnection(self):
    
        # checks to make sure that a connection has been established
        if((self.device is not None) and (self.lib is not None)):
            
            # closes the connection
            self.lib.UsbCloseDevice(self.device)
            
            
## Contains the definition for the background thread that polls the ADC input from
# the solar panel and sends that value to the GUI to be displayed to the user
class SolarTrackingThread(Thread):
    
    ## Constructor for the solar tracking thread
    def __init__(self, parent, usb, evt):
        
        Thread.__init__(self)
        
        ## The usb interface associated with the thread
        self.usb = usb
        
        ## The event that needs to be fired when the GUI needs to
        # be updated
        self.event = evt
        
        ## The parent frame that should be updated when a new solar
        # measurement is received
        self.parent = parent
        
        ## The stop flag for the thread
        self.stop = False
        
    ## Called when the thread is started
    #
    # As long as the stop flag is not set, the thread sends a request to the
    # Tiny for solar measurements.  When the computer receives a response from
    # the Tiny, it fires a SolarEvent, which tells the GUI to update itself
    # with the latest solar measurements.
    #
    # @param self: The object pointer
    def run(self):  
        
        # polls the Tiny for solar panel measurements as long as the
        # stop flag has not been set      
        while self.stop is False:
            
            # make sure the connection has been established
            if(self.usb is not None):
                
                # get the solar panel measurement
                voltage = self.usb.MeasureSolarPanel()
            
                # trigger a new event to tell the GUI to update itself with
                # the latest measurement
                evt = SolarEvent(self.event, -1, voltage)
                wx.PostEvent(self.parent, evt)
                
            # wait for 100ms
            sleep(.1)
        
    ## Sets the stop flag to stop the thread
    #
    # Sets the stop flag, which causes the loop in the thread to stop if
    # it was running
    #
    # @param self: The object pointer
    def QuitThread(self):
        self.stop = True
        
## Event class that allows a background thread to send messages to GUI
# to tell it to update itself
class SolarEvent(wx.PyCommandEvent):
    
    ## Constructor for the solar event
    def __init__(self, etype, eid, value = None):
        
        # call the event and set the value equal to the supplied value
        wx.PyCommandEvent.__init__(self, etype, eid)
        
        ## The value contained in the event
        self._value = value

    ## Returns the value of the event that is set in the constructor
    #
    # @param self: The object pointer
    def GetValue(self):
        return self._value
        