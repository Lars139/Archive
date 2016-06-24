//Author: Rattanai Sawaspanich (Bear)

#include "dialog.h"
#include "ui_dialog.h"
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

//Skeleton Code for ECE 375 Lab 6 - Intel Atom Lab

int file;
int adapter_nr = 14;	//dynamically determined; in our system, i2cdetect -l shows i2c0 is for smbus (SMBus I801 adapter at 0400)
char filename[20];

int data1[6];
int z=0,c;
float a=0,b=300,p=0,q=300;
int k=1;

QPen pen;
QPoint apoint(150,150);

void openfile()
{
	//open the device file
	snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
	file = open(filename, O_RDWR|O_CREAT);

	if (file < 0)
	{
		printf("Failed to open i2c device.\n");
		exit(1);
	}

	//specify what device address you want to communicate

	int addr = 0x52; //address for nunchuck

	//Access the I2C slave

	if(ioctl(file, I2C_SLAVE, addr) < 0)
	{
		printf("Failed to acquire bus access to slave.\n");
		printf("error..., something is wrong %s\n", strerror(errno));
		exit(1);
	}

	//DONE: write initialization data to the nunchuk.
	//if it returns with error (-1) exit with status 1
    //This is initialize for the white nunchuk  (TO be changed if black nunchuck is used)
    if(i2c_smbus_write_byte_data(file, 0x40, 0x00)  == -1){
        perror("Initializing Nunchuk 1");
        exit(-1);
    }

    if(i2c_smbus_write_byte_data(file, 0x40, 0x00)  == -1){
        perror("Initializing Nutchuk 2");
        exit(-1);
    }
} 

Dialog::Dialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Dialog)
{
	ui->setupUi(this);

	openfile();
	timer= new QTimer(this);
	connect(timer,SIGNAL(timeout()),this,SLOT(repaint()));

	timer->start(100);
}

Dialog::~Dialog()
{
	delete ui;
}

void Dialog::paintEvent(QPaintEvent *e)
{
	
	unsigned char data[6];
    float JoyX, JoyY;
    int ButC, ButZ;
    int f_run= 0;
	QPainter painter(this);
    QPoint b;
	QWidget::setAttribute( Qt::WA_OpaquePaintEvent, true );
	


	if(i2c_smbus_write_byte(file, 0x00) == -1)
	{
		printf("error..., something is wrong %s\n", strerror(errno));
		exit(1);
	}

	for(int i = 0; i < 6; ++i)
	{
        //DONE: read a byte from I2C into the data array
        data[i] = i2c_smbus_read_byte(file);

        //DONE : convert the input data to the correct format
        data[i] = (data[i]^0x17)+0x17;  //I know your secret Nitendo!
		
       // printf("the final data is %x\n", data[i]);

    }

    // DONE: Convert data bytes into analog X/Y, accelerometer X/Y/Z, button X/Z
    // Look at the Nunchunk output 6 bytes and extract the data from there
    // This is what data[] looks like
    // data[] = [ Last_Byte | ADCz | ADCy | ADCx | JoyY | JoyX ]
    // The bit layout for Last_Byte:
    // Last_Byte = [AccZ1 | AccZ0 | AccY1 | AccY0 | AccX1 | AccX0 | C-button | Z-button]

    // Setting the read value to corresponding variables
    JoyX = data[0];                     //Joystick X-axis
    JoyY = data[1];
    ButC = !(data[5]&2); //0b00000010   //Button-C =1 if it's pressed
    ButZ = !(data[5]&1); //0b00000001

    // DONE: Output from the nunchuck for reference
    // Print output of analog stick and X, Y, Z axes
    // DONE: Print output of buttons Z and C
    // When drawing pressing button Z should exit
    // When drawing pressing button C should draw



    //If button C is pressed, change the pen color
    if(ButC){
    pen.setColor(QColor(rand()%225, rand()%255, rand()%255,255));
    painter.setPen(pen);
    }

    if(ButZ){
        painter.eraseRect(0,0,painter.window().right(),painter.window().bottom());
    }

    //If both Z and C are pressed, quit the program
    if(ButZ && ButC){
        exit(1);
  }

	
    // FIXME
    // Calculate the next point based on analog stick data.
    // The screen range [0,300]
    // So convert the hex to the value
	// Set the value
	
    JoyX = ((JoyX -(float) 0x7A)/((float)0xDD - (float)0x7E))*(float)17;
    JoyY = ((JoyY -(float) 0x8d)/((float)0xED - (float)0x8D))*(float)17;
	
    printf("JoyX: %d |  JoyY: %d | ButC: %d | ButZ: %d \n", JoyX, JoyY, ButC, ButZ);
 //The original points


    b.setX(apoint.x() + JoyX);
    b.setY(apoint.y() - JoyY);
	
	//Draw a line between the previous point and the new point.
    painter.drawLine(apoint,b);
    apoint = b;
	

}

