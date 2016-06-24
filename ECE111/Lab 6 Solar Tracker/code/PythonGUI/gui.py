'''
Defines the GUI that abstracts away the connection with the OSUisp2 and Tiny261
Created on Aug 13, 2012

@author: Robert L. Phillips III
@version: 1.0

@section DEPENDENCIES
    -  wxPython
          The GUI is generated using the third party library wxPython.  All documentation
          for the wxPython library can be found at wxpython.org.
          
    -  tiny26
          Contains the libraries necessary for the GUI to establish a connection to the
          Tiny26 and send commands to it.
          
    -  time
          Contains the sleep function, which is needed to block certain threads for a certain
          amount of time
'''

import wx
import tiny26

from time import sleep

## Defines the main frame for the GUI.  It provides a simple interface for the user to send
# commands to a Tiny261 microcontroller (that has the approriate firmware) via the OSUisp2 
# Universal Programmer.  The commands move a solar panel to certain positions and take measurements
# that correspond to the amount of light that is hitting the solar panel.  Those measurements
# are echoed back to the computer, which are displayed on the GUI.
class MotorGUI(wx.Frame):
    
    ## Constructor for a wxPython frame
    def __init__(self, parent, ident, title):
        
        # initialize the wxPython frame
        wx.Frame.__init__(self, parent, ident, title)
        
        ## Holds the event type definition for the event that is called
        # when the GUI needs to be updated with the latest solar panel
        # measurement
        self.solar_event = wx.NewEventType()
        
        # creates a new event type to handle events that signal the
        # GUI to update with the latest information from the solar
        # panel
        EVT_SOLAR = wx.PyEventBinder(self.solar_event, 1)
        
        ## Holds the usb connection variable that is used to interface
        # with the Tiny261
        self.usb = None
        
        # creates a new menu bar
        menu = wx.MenuBar()
        
        # creates two items to add to the menu bar
        file_menu = wx.Menu()
        help_menu = wx.Menu()
        
        # sets the menu of the gui to the one that was just created
        self.SetMenuBar(menu)
        
        # add the menu times to the menu bar
        menu.Append(file_menu, '&File')
        menu.Append(help_menu, '&Help')
        
        # add items to the menu items and set their event handlers
        file_exit = file_menu.Append(wx.ID_ANY, 'E&xit')
        self.Bind(wx.EVT_MENU, self.OnWindowClosed, file_exit)
        
        help_about = help_menu.Append(wx.ID_ANY, '&About')
        self.Bind(wx.EVT_MENU, self.OnAboutRequested, help_about)
        
        # define a sizer that will align its children vertically
        sizer = wx.BoxSizer(wx.VERTICAL)
        
        # define a new panel
        panel = wx.Panel(self, -1)
        
        ## The "Connect" button
        self.connect = wx.Button(panel, wx.ID_ANY, label = "Connect")
        
        ## The "Maximize Solar Efficiency" button
        self.find_sun = wx.Button(panel, wx.ID_ANY, label = "Maximize Solar Efficiency")
        self.find_sun.Disable()
        
        # create a new panel and its horizontal sizer
        motor_panel = wx.Panel(panel, -1)
        mtr_sizer = wx.BoxSizer(wx.HORIZONTAL)
        
        ## The "Position" text control (allows the user to specifiy a position to move the
        # servo).
        self.position = wx.TextCtrl(motor_panel, wx.ID_ANY)
        self.position.Disable()
        
        # create a new label
        label = wx.StaticText(motor_panel, wx.ID_ANY, label = "Motor Position (0 < position < 255):  ")
        
        # add the label and text control to the panel
        mtr_sizer.Add(label, proportion = 0, border = 1, flag = wx.EXPAND)
        mtr_sizer.Add(self.position, proportion = 1, border = 1, flag = wx.EXPAND)
        
        # set the panels sizer
        motor_panel.SetSizer(mtr_sizer)
        
        # create a new panel and its horizontal sizer
        info_panel = wx.Panel(panel, -1)
        info_sizer = wx.BoxSizer(wx.HORIZONTAL)

        # create a new label
        label2 = wx.StaticText(info_panel, wx.ID_ANY, label = "Solar Panel Reading:                          ")
        
        ## The "Display" text control (shows the solar panel measurements).
        self.display = wx.TextCtrl(info_panel, wx.ID_ANY)
        self.display.SetEditable(False)
        
        # add the text control and label to the panel
        info_sizer.Add(label2, proportion = 0, border = 1, flag = wx.EXPAND)
        info_sizer.Add(self.display, proportion = 1, border = 1, flag = wx.EXPAND)
        
        # set the sizer of the panel
        info_panel.SetSizer(info_sizer)
        
        ## The "Move Servo" button.
        self.move = wx.Button(panel, wx.ID_ANY, label = "Move Servo")
        self.move.Disable()
        
        # create a new image panel to hold the TekBots logo
        logo = wx.Panel(panel, style = wx.SUNKEN_BORDER)
        wx.StaticBitmap(logo, wx.ID_ANY, wx.Bitmap("TekBots.png"))
        
        ## The solar measurements Gauge (displays the measurements in gauge form).
        self.gauge = wx.Gauge(panel, wx.ID_ANY, 255)
        
        # add all the components to the sizer
        #
        # Add(component, proportion=p, border=b, flag=f)
        #        @component --> the component to add the sizer
        #        @p         --> determines whether or not to stretch the component to match the size
        #                            of the largets component
        #        @b         --> the border around the component
        #        @f         --> determines whether or not the component should resize based on the size
        #                            of the window
        sizer.Add(logo, proportion = 1, border = 0, flag = wx.EXPAND)
        sizer.Add(wx.StaticText(panel, wx.ID_ANY), proportion = 0, border = 1, flag = wx.EXPAND)
        sizer.Add(wx.StaticText(panel, wx.ID_ANY), proportion = 0, border = 1, flag = wx.EXPAND)
        sizer.Add(info_panel, proportion = 0, border = 1, flag = wx.EXPAND)
        sizer.Add(self.gauge, proportion = 0, border = 1, flag = wx.EXPAND)
        sizer.Add(wx.StaticText(panel, wx.ID_ANY), proportion = 0, border = 1, flag = wx.EXPAND)
        sizer.Add(wx.StaticText(panel, wx.ID_ANY), proportion = 0, border = 1, flag = wx.EXPAND)
        sizer.Add(motor_panel, proportion = 0, border = 1, flag = wx.EXPAND)
        sizer.Add(wx.StaticText(panel, wx.ID_ANY), proportion = 0, border = 1, flag = wx.EXPAND)
        sizer.Add(self.move, proportion = 0, border = 1, flag = wx.EXPAND)
        sizer.Add(self.find_sun, proportion = 0, border = 1, flag = wx.EXPAND)
        sizer.Add(self.connect, proportion = 0, border = 1, flag = wx.EXPAND)        
        
        # add the event listeners to the components
        #
        # component.Bind(event, method)
        #        @component --> the component to bind the listener to
        #        @event -->     the event to listen for
        #        @method -->    the method to handle the event
        self.Bind(wx.EVT_CLOSE, self.OnWindowClosed)
        self.Bind(EVT_SOLAR, self.OnSolarMeasureUpdate)
        self.connect.Bind(wx.EVT_BUTTON, self.OnButtonPressed)
        self.find_sun.Bind(wx.EVT_BUTTON, self.OnSolarMaxRequest)
        self.move.Bind(wx.EVT_BUTTON, self.OnMoveServoRequest)
        
        # centers the window on the screen
        self.CenterOnScreen()
        
        # adds the sizer to the panel
        panel.SetSizer(sizer)
        
        # resizes the window and panel so they fit around the component
        panel.Fit()
        self.Fit()
        
    ## Initiates the thread that polls the Tiny for the value of the solar
    #  panel ADC and then updates the GUI accordingly
    #
    # @param self: The object pointer
    def StartUpdateThread(self):
        
        ## Holds the object that corresponds to the solar panel measurements update thread
        self.updater = tiny26.SolarTrackingThread(self, self.usb, self.solar_event)
        
        #start the thread
        self.updater.start()
        
        
    ## Handles the event that is fired when the "Move Servo" button is pressed
    #
    # If a usb connection is currently active, a request is sent to the Tiny to
    # move the motor to the position that corresponds to value given by the user
    # in the position text control.  The solar measurement update thread is paused
    # until the Tiny26 is finished repositioning the motor
    #
    # @param self: The object pointer
    # @param event: The object that is associated with the event request
    def OnMoveServoRequest(self, event):
        
        # make sure a connection has been established
        if self.usb is not None and self.usb.IsConnected():
            
            # get the position that the user has put in the text control
            motor_pos = int(self.position.GetValue())
            
            # make sure that the position is in the valid range and put it
            # into the valid range if it isn't
            if(motor_pos < 1):
                motor_pos = 1
                
            if(motor_pos > 254):
                motor_pos = 254
            
            # quit the thread that updates the text control if it is active
            try:
                self.updater.QuitThread()
                
                # wait for 50ms to ensure the thread has stopped
                sleep(.05)
            except:
                self.updater = None
                
            # set the position of the solar panel
            self.usb.SetSolarPosition(motor_pos)
            
            # wait for 50ms ot ensure that the transmission has been completed
            sleep(.05)
            
            # restart the GUI update thread
            self.StartUpdateThread()
        else:
            self.usb = None
            
            
    ## Handles the event that is fired when the "Maximize Solar Efficiency" button is pressed
    #
    # If a usb connection is currently active, a request to find the position that produces
    # the highest voltage output from the solar panel is sent.  The solar panel measurement
    # update thread is paused until the Tiny had finished positioning the solar panel in the
    # position that receives the most light.
    #
    # @param self: The object pointer
    # @param event: The object that is associated with the event request
    def OnSolarMaxRequest(self, event):
        
        # make sure the connection has been established
        if self.usb is not None and self.usb.IsConnected():
            
            # quit the thread that updates the text control if it is active
            try:
                self.updater.QuitThread()
                
                # wait for 50ms to ensure that the thread has stopped
                sleep(.05)
            except:
                self.updater = None
                
            # tell the Tiny to find find the position with the most solar
            # panel production
            self.usb.FindMostSun()
            
            # wait for 50ms to ensure that the transmission was complete
            sleep(.05)
            
            # restart the thread that updates the GUI
            self.StartUpdateThread()
        else:
            self.usb = None
        
    ## Handles the event that is fired when the "Connect" button is pressed
    #
    # If a usb connection is not currently active, the GUI sends a request to
    # the OSUisp2 programmer to connect to the Tiny and verify that the correct
    # firmware is installed.
    #
    # @param self: The object pointer
    # @param event: The object that is associated with the event request
    def OnButtonPressed(self, event):
        
        # create a new USB_Interface instance
        self.usb = tiny26.USB_Interface(self)
        
        # if the connection was made successfully, disable the connect button, enable
        # the slider and set the usb variable back to 'None' if the connection failed
        if self.usb.IsConnected():
            
            # disable the connect button
            self.connect.Disable()
            
            # enable the servo movement GUI components
            self.position.Enable()
            self.find_sun.Enable()
            self.move.Enable()
            
            # start the thread that updates the TextCtrl with the current measurements
            # of the solar panel
            self.StartUpdateThread()
        else:
            self.usb = None
                
    ## Handles the event that is called when the program is closed
    #
    # If a usb connection is currently active, the GUI sends a request to
    # the OSUisp2 programmer to close the connection to the Tiny and to end
    # the thread that updates the GUI with the solar panel measurments
    #
    # @param self: The object pointer
    # @param event: The object that is associated with the event request
    def OnWindowClosed(self, event):
        
        # quit the thread that updates the text control if it is active
        try:
            self.updater.QuitThread()
            
            # wait for 50ms to ensure that the thread has stopped
            sleep(.05)
        except:
            self.updater = None
                
        # close the usb connection if it as made
        if self.usb is not None:
            self.usb.CloseConnection()
            
        # destroy the window
        self.Destroy()
            
    ## Handles the event that is called when a new ADC measurment from the solar
    # panel connected to the tiny is received
    #
    # Sets the value of the text control equal to the measurement that is contained
    # in the event request.
    #
    # @param self: The object pointer
    # @param event: The object that is associated with the event request
    def OnSolarMeasureUpdate(self, event):
        
        # update the TextCtrl to the received value
        self.display.SetValue(str(event.GetValue()))
        
        # update the Guage to the received value
        self.gauge.SetValue(event.GetValue())
        
    ## Handles the event that is called when the about menu button is pressed
    #
    # Shows the user a message box containing information about the program
    #
    # @param self: The object pointer
    # @param event: The object that is associated with the event request
    def OnAboutRequested(self, event):
        
        # defines a new message box
        msg = wx.MessageDialog(self, "Created by Robert L. Phillips III\n" \
                               "Copyright (c) 2012 Oregon State University TekBots\n\n" \
                               "Required Hardware:\n" \
                               "-  OSUisp2 Universal Programmer\n" \
                               "-  Mini USB Cable\n" \
                               "-  Ribbon Cable With 10-Pin Female Header\n" \
                               "-  TekBots Tiny26 Board\n" 
                               , "About Motor Controller", wx.OK | wx.ICON_INFORMATION)
        
        # shows the message box and destroys it when 'OK' is clicked
        msg.ShowModal()
        msg.CenterOnParent()
        msg.Destroy()
        
        
## Abstracts away the creation of the MotorGUI and launches it in the
# default constructor
class GUI_Launcher(wx.App):

    ## Constuctor for a wxPython app
    def OnInit(self):

        # create an instance of the MotorGUI and show it
        frame = MotorGUI(None, -1, "Motor Controller")
        frame.Show(True)

        # make the MotorGUI the main frame
        self.SetTopWindow(frame)

        # return a success flag
        return True

