/*
 * RoboMapache.c
 *
 * Creado: 18/10/2017 04:21:30 p. m.
 * Autores :
	  Oliver
	  Jesus
	  Guerrero
	  Andres
	  Luis Humberto Jr Aguayo Robles
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

void conf_puertos();
void conf_USART0();


//CONFIGURACION DE DIRECCIONAMIENTO DE LOS PUERTOS
void conf_puertos(){
	DDRC = 0b001111; //Configuramos PC0 a PC3 como salida
	DDRD = 0b00000010; //Configuramos TX (PD1) como salida y RX (PD0) como entrada
	PORTC = 0b000000; //Limpiamos el puerto C para evitar que tenga basura en la salida	
}

//CONFGURACION DEL PUERTO SERIAL
void con_USART0(){
	 UCSR0A = (0<<TXC0)|(0<<U2X0)|(0<<MPCM0); //No configuramos la velocidad al doble (X2) ni habilitamos la comunicacion multiprocesador
	 //0<<TXC0 -> Trasnmision finalizada
	 //0<<U2X0 -> Multiplicar la velocidad de transmision x2
	 //0<<MPCM0 -> Tener una comunicacion multiprocesador
	 
	 UCSR0B = (1<<RXCIE0)|(0<<TXCIE0)|(0<<UDRIE0)|(1<<RXEN0)|(1<<TXEN0)|(0<<UCSZ02)|(0<<TXB80); //Habilitamos la interrupcion de recepcion de datos	 
	 //<<RXCIE0 -> Habilitar la interrupcion de recepcion
	 //<<TXCIE0 -> Habilitar la interrupcion de enviar datos
	 //<<UDRIE0 -> Habilitar el control de errores
	 //<<RXEN0 -> Habilitar la rececpcion de datos por el puerto serial
	 //<<TXEN0 -> Habilitar la trasmision de datos por el puerto serial
	 //UCSZ02Configurar el numero de bit de datos
	
	 UCSR0C = (0<<UMSEL01)|(0<<UMSEL00)|(0<<UPM01)|(0<<UPM00)|(0<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00)|(0<<UCPOL0); //Configuramos el USART asincrono, 1 bit de stop y 8 bit de datos
	 //<<UMSEL -> Habilitar el uso sincrono 0 o asincrono 1
	 //<<UPM -> Habilitar paridad
	 //<<USBS -> Cambiar el numero de bit de datos que se van a usar
	 //<<UCSZ -> Polaridad 1 - Ejes de bajada 0 - ejes de salida
	 
	 UBRR0 = 95; //Utilizamos un cristal de 14.7456Mhz a 9600 bps
	 
}

ISR(USART_RX_vect,ISR_NAKED){
	char dato;
	dato = UDR0; //Dato-comando recibido de 8 bits 
	UDR0 = dato; //Echo, es decir regresa el valor que le mandemos
	//Codigo para controlar el giro de las llantas del robot
	switch(dato){
		case 'w':
			PORTC = 0b000101;
			break;
		case 's':
			PORTC = 0b001010;
			break;
		case 'a':
			PORTC = 0b000110; 
			break;
		case 'd':
			PORTC = 0b001001;
			break;
		default:
			PORTC = 0b000000;
	}
	reti();
}

int main(void)
{
	conf_puertos(); //Configuramos los puertos
	con_USART0(); //Configuramos el puerto serial
	sei(); //Habilita la 

    /* Replace with your application code */
    while (1) 
    {
    }
}

