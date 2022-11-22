
//Headers
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

char Display_7_Seg[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F}; //Display 7 Segmentos C.C.
char Posicion[6]={1,2,4,8,16,32}; //Indicador de Posiciones

int main(void)
{

	DDRB=0xFF; //Salidas en C
	DDRD=0xFF; //Salidas en D

	int hora_decena=2,hora_unidad=3,minuto_decena=5,minuto_unidad=9,segundo_decena=4,segundo_unidad=5; //Inicializar Visualizadores
	int Sigue_Pos=0, Hold=0; //Inicializar Seguidores

	while(1) //Bucle Infinito
	{
		if(segundo_unidad>9) //Actualizar "segundo_unidad" con Aumento en "segundo_decena"
		{
			segundo_unidad=0;
			segundo_decena+=1;
		}


		if(segundo_decena>5) //Actualizar "segundo_decena" con Aumento en "minuto_unidad"
		{
			segundo_unidad=0;
			segundo_decena=0;
			minuto_unidad+=1;
		}


		if(minuto_unidad>9) //Actualizar "minuto_unidad" con Aumento en "minuto_decena"
		{
			segundo_unidad=0;
			segundo_decena=0;
			minuto_unidad=0;
			minuto_decena+=1;
		}


		if(minuto_decena>5) //Actualizar "minuto_decena" con Aumento en "hora_unidad"
		{
			segundo_unidad=0;
			segundo_decena=0;
			minuto_unidad=0;
			minuto_decena=0;
			hora_unidad+=1;
		}

		if(hora_unidad>9) //Actualizar "hora_unidad" con Aumento en "hora_decena"
		{
			segundo_unidad=0;
			segundo_decena=0;
			minuto_unidad=0;
			minuto_decena=0;
			hora_unidad=0;
			hora_decena+=1;
		}


		if(hora_decena>1) //Actualizar "hora_decena" al Re-Actualizar "hora_unidad" con Limpiado a Todo
		{
			if(hora_unidad>3)
			{
				segundo_unidad=0;
				segundo_decena=0;
				minuto_unidad=0;
				minuto_decena=0;
				hora_unidad=0;
				hora_decena=0;
			}
		}
		

		char Hora_Completa[6]={hora_decena,hora_unidad,minuto_decena,minuto_unidad,segundo_decena,segundo_unidad}; //Almacenar Hora
		segundo_unidad++;

		for(Hold=0; Hold<80; Hold++) //Ciclo de Hold
		{
			for(Sigue_Pos=0; Sigue_Pos<6; Sigue_Pos++) //Ciclo de Sigue_Pos para Avanzar en Matrices
			{
				PORTD=Posicion[Sigue_Pos]; //Asignación para D con Posicion
				PORTB=Display_7_Seg[Hora_Completa[Sigue_Pos]]; //Asignación Anidada para B con Display_7_Seg
				_delay_ms(2);
			}
			Sigue_Pos=0; //Limpiado de Seguidor de Posicion
		}
	}

}