/* 
 * RoboMapache.c
 * Creado: 18/10/2017 04:21:30 p. m.
 * Aplicación que controla el movimiento de un carro-robot por medio de un teléfono inteligente con 
 * sistema Android y la app BlueTerm a través de una conexión bluetooth y una tarjeta NoMADA Pro+
 *
 * SMARTLINES
 * Tecnológico Nacional de México - Instituto Tecnológico de Zacatecas
 * Autores:
 *	  Oliver Bautista Acosta ------------------ Lider Técnico
 *	  Jesus Ramirez Vargas -------------------- Documentador
 *	  Carlos Guerrero Silva ------------------- Documentador
 *	  Andrés Álvarez Frias -------------------- Programador
 *	  José Pablo Ramos Jimenez ---------------- Diseñador
 *	  Luis Humberto Jr Aguayo Robles ---------- Programador
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

//PROTOTIPOS DE FUNCIONES
void conf_puertos();
void conf_USART0();


//CONFIGURACIÓN DE DIRECCIONAMIENTO DE LOS PUERTOS
void conf_puertos(){
	DDRC = 0b001111; //Configuramos PC0 a PC3 como salida
	DDRD = 0b00000010; //Configuramos TX (PD1) como salida y RX (PD0) como entrada
	PORTC = 0b000000; //Limpiamos el puerto C para evitar que tenga basura en la salida
}

//CONFGURACIÓN DEL PUERTO SERIAL
void con_USART0(){
	UCSR0A = (0<<TXC0)|(0<<U2X0)|(0<<MPCM0); //No configuramos la velocidad al doble (X2) ni habilitamos la comunicación multiprocesador
	
	UCSR0B = (1<<RXCIE0)|(0<<TXCIE0)|(0<<UDRIE0)|(1<<RXEN0)|(1<<TXEN0)|(0<<UCSZ02)|(0<<TXB80); //Habilitamos la interrupción de recepción de datos
	
	UCSR0C = (0<<UMSEL01)|(0<<UMSEL00)|(0<<UPM01)|(0<<UPM00)|(0<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00)|(0<<UCPOL0); //Configuramos el USART asíncrono, 1 bit de stop y 8 bit de datos
	
	UBRR0 = 95; //Utilizamos un cristal de 14.7456Mhz a 9600 bps
	
}

ISR(USART_RX_vect,ISR_NAKED){
	char dato;
	dato = UDR0; //Dato-comando recibido de 8 bits
	UDR0 = dato; //Echo, es decir regresa el valor que le mandemos
	//Codigo para controlar el giro de las llantas del robot
	switch(dato){
		case 'w':
		PORTC = 0b001010; //Avanza hacia adelante
		break;
		case 's':
		PORTC = 0b000101; //Avanza hacia atrás
		break;
		case 'a':
		PORTC = 0b001000; //Gira a la derecha
		break;
		case 'd':
		PORTC = 0b000010; //Gira a la izquierda
		break;
		default:
		PORTC = 0b000000; //Cualquier tecla diferente de las opciones anteriores lo detiene
	}
	reti(); //Regresa a la interrupción y limpia las banderas de interrupción
}

int main(void){}

