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

int joyX1=0, joyY1=0;
char Z=0,C=0;
float joydX=0,joydY=0;

QPen pen;

void openfile()
{
    //open the device file
    snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
    file = open(filename, O_RDWR);

    if (file < 0)
    {
        printf("Failed to open i2c device.\n");
        exit(1);
    }

    //specify what device address you want to communicate

    //int addr = ??;	 //address for nunchuck
	int addr = 0x52;
		//Access the I2C slave


    if(ioctl(file, I2C_SLAVE, addr) < 0)
    {
        printf("Failed to acquire bus access to slave.\n");
        printf("error..., something is wrong %s\n", strerror(errno));
        exit(1);
    }
	
		//TODO: write initialization data to the nunchuk.
		//if it returns with error (-1) exit with status 1
	//Black
   /*if (i2c_smbus_write_byte_data(file, 0xF0, 0x55) == -1) exit(1);
    if (i2c_smbus_write_byte_data(file, 0xFB,0x00) == -1) exit(1);*/
	//White
    if (i2c_smbus_write_byte_data(file, 0x40,0x00) == -1) exit(1);
    if (i2c_smbus_write_byte_data(file, 0x40,0x00) == -1) exit(1);
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

    QPainter painter(this);
    QWidget::setAttribute( Qt::WA_OpaquePaintEvent, true );

       if(i2c_smbus_write_byte(file, 0x00) == -1)
        {
            printf("error..., something is wrong %s\n", strerror(errno));
            exit(1);
        }
        //You start by believing here.....
        for(int i = 0; i < 6; ++i)
            {
				data[i]=i2c_smbus_read_byte(file);
				data1[i] = (data[i] ^ 0x17) + 0x17;
            //printf("the final data is %x\n", data1[i]);

            }

        joydX = (((data1[0] - (0x1E * 1.0f))/(0xE1-0x1E)) *4) -2;
        joydY = (((data1[1] - (0x1D * 1.0f))/(0xDF-0x1D)) *4) -2;
        C = !(data1[5] & 2);
        Z = !(data1[5] & 1);
     // Output from the nunchuck for reference //

				//TODO: Print output of analog stick and X, Y, Z axes
        printf("Analog X: %f, Analog Y: %f, Axis X: %d, Axis Y: %d, axis Z %d, Button Z: %d, Button C: %d\n", joydX,joydY,data1[2],data1[3],data1[4],Z,C);
				//TODO: Print output of buttons Z and C
				//When drawing pressing button Z should exit
                //everyday is a good day if you paint.
                if(C){
					pen.setColor(QColor(rand()%255,rand()%255,rand()%255,255));
					painter.setPen(pen);
				}
                //We don't have mistakes, only happy little accidents
				if(Z){
					painter.eraseRect(0,0,painter.window().right(),painter.window().bottom());
				}
				//When drawing pressing button C should draw

		//Calculate the next point based on analog stick data.	
		//You might need to convert some values.  Experiment...
		
        //This is your world. You are the creator. Find freedom on this canvas.
        if( pow(joydX,2) + pow(joydY,2) < pow(1,2)){ // dead zone for joystick.
            std::cout<<a<<" "<<b<<"\n";
            return; //go away?
		}
		
        int newx = joyX1 + joydX;
        int newy = joyY1 - joydY;
        printf("newx: %d, newy: %d\n",newx,newy);

		QPoint A(joyX1,joyY1);
		QPoint B(newx,newy);
		
		painter.drawLine(A,B);
		
		joyX1 = newx;
		joyY1 = newy;

		//Draw a line between the previous point and the new point.

        if( C && Z){
            exit(0); //not correct according to qt. But frak it, have a happy little cloud, with some happy little trees.
        }

    //std::cout<<a<<" "<<b<<"\n";

}

