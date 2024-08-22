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

void i2c_initialize() //Begin IIC as master
{
	TRISC3=TRISC4=1;
	SSPCON=0x28;					//SSP Module as Master
	SSPADD=  ((11059200/4)/100)-1;	//Setting Clock Speed, My PCLK = 11.0592MHz
}
  

void i2c_begin()
{
	SEN = 1;         /* Start condition enabled */
	while(SEN);
}

void i2c_end()
{
	PEN = 1;         /* Stop condition enabled */
    while(PEN);
}

void i2c_restart()
{
	RSEN = 1;        // Repeated start enabled 
    while(RSEN);
}


void i2c_ack()
{
	ACKDT = 0;       /* Acknowledge data bit, 0 = ACK */
	ACKEN = 1;       /* Ack data enabled */
	while(ACKEN);    /* wait for ack data to send on bus */
}

void i2c_nak()
{
	ACKDT = 1;       /* Acknowledge data bit, 1 = NAK */
	ACKEN = 1;       /* Ack data enabled */
	while(ACKEN);    /* wait for ack data to send on bus */
}


void i2c_wait()
{
	while ( (SSPCON2 & 0b00011111)    ||    (SSPSTAT & 0b00000100)  );
}

void i2c_write(unsigned char data)
{
	SSPBUF = data;    /* Move data to SSPBUF */
	while(BF);       /* wait till complete data is sent from buffer */
	i2c_wait();       /* wait for any pending transfer */     
}


unsigned char i2c_read(unsigned char ack)
{
	unsigned char temp;
    /* Reception works if transfer is initiated in read mode */
	RCEN = 1;        /* Enable data reception */
	while(!BF);      /* wait for buffer full */
	temp = SSPBUF;   /* Read serial buffer and store in temp register */
	i2c_wait();      /* wait to check any pending transfer */
	return temp;     /* Return the read data from bus */
}
