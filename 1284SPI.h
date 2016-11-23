#ifndef _SPI_1284__
#define _SPI_1284__

void SPI_MasterInit1(void)
{
	/* Set MOSI and SCK output, all others input */ 
	DDRB = 0xBF;
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);

}

void SPI_MasterTransmit(char cData, unsigned char Machine) {
	
	unsigned char temp = Machine - 1;
	unsigned char shift = 1;
	shift = shift << Machine;
	PORTB = PORTB & ~shift; 
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
	PORTB = PORTB | shift;

}


// Servant code
void SPI_ServantInit(void)
{
	/* Set MISO output, all others input */
	DDRB = (1<<DDRB6);
	/* Enable SPI */
	SPCR = (1<<SPE);
	
}

char SPI_SlaveReceive (void)
{
	/* Wait for reception complete */
	//while(!(SPSR & (1<<SPIF)));
	/* Return Data Register */
	return SPDR;
}



#endif