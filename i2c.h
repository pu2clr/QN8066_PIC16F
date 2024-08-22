/*
 * File: Header file to use I2C with PIC16F877A
 * Author: B.Aswinth Raj
 * Created on 5 May, 2018, 7:24 PM
 * 
 * References: 
 *             https://circuitdigest.com/microcontroller-projects/i2c-communication-with-pic-microcontroller-pic16f877a 
 *             https://ww1.microchip.com/downloads/en/devicedoc/39582b.pdf
 */




//PIN 14 -> RC3 -> SCL
//PIN 15 -> RC4 ->SDA

void i2c_initialize(const unsigned long clock, const unsigned long XTAL_FREQ ) //Begin IIC as master
{
  TRISC3 = 1;  
  TRISC4 = 1;  //Set SDA and SCL pins as input pins
  
  SSPCON  = 0b00101000;    //pg84/234 
  SSPCON2 = 0b00000000;    //pg85/234
  
  SSPADD = 9; // (XTAL_FREQ/(4*clock*100))-1; //Setting Clock Speed pg99/234
  SSPSTAT = 0b00000000;    //pg83/234
}

void i2c_hold()
{
    while (   (SSPCON2 & 0b00011111)    ||    (SSPSTAT & 0b00000100)   ) ; //check the bis on registers to make sure the IIC is not in progress
}

void i2c_begin()
{
  i2c_hold();  //Hold the program is I2C is busy  
  SEN = 1;     
}

void i2c_end()
{
  i2c_hold(); //Hold the program is I2C is busy  
  PEN = 1;    //End IIC pg85/234
}

void i2c_write(unsigned char data)
{
  i2c_hold();           //Hold the program is I2C is busy 
  SSPBUF = data;        
}

unsigned char i2c_read(unsigned char ack)
{
  unsigned char incoming;
  i2c_hold();
  RCEN = 1;
  
  i2c_hold();
  incoming = SSPBUF;      //get the data saved in SSPBUF
  
  i2c_hold();
  ACKDT = (ack)?0:1;    //check if ack bit received  
  ACKEN = 1;          //pg 85/234
  
  return incoming;
}
