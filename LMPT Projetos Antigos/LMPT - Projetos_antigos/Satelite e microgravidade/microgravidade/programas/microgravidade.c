/*
    Título:      Programação para o experimento de Ebulição em Microgravidade
    Autor:       Carlos Eduardo Paghi
    Data:        05/2002
    Finalidade:  Controle da potência aplicada em resistências
    Software:    AVR-GCC para compilação
    Hardware:    ATmega
    Contato:     carlos@lmpt.ufsc.br
*/

#include <io.h>
#include <interrupt.h>
#include <signal.h>
#include <stdlib.h>
#include <iom103.h>


/* Protótipos de funções */

/* Definições */

/* Definições de novos tipos */

/* Declaração das variáveis globais */

int tempo = 0x00;

/* Sub-rotina para inicialização dos Timers */

void inicializa_timers(void)
{  
  /* Inicialização do Timer 1 */

  outp((1<<AS0), ASSR);		// Define o cristal externo para o clock
  outp((1<<TOIE0), TIMSK);	// Ativa a interrupção do Temporizador 0    
  outp(0x05, TCCR0);
  outp(0x00, TCNT0);
}

SIGNAL(SIG_OVERFLOW0)
{
  tempo++;
  
  switch(tempo)
  {
    case 1:
      outp(0x88, PORTB);
      break;
      
    case 30:
      outp(0x99, PORTB);
      break;
      
    case 60:
      outp(0xBB, PORTB);
      break;
      
    case 90:
      outp(0xCC, PORTB);
      break;
      
    case 120:
      outp(0xDD, PORTB);
      break;
      
    case 150:
      outp(0xDE, PORTB);
      break;
      
    case 180:
      outp(0xDF, PORTB);
      break;
    
    case 210:
      outp(0xDD, PORTB);
      break;
    
    case 240:
      outp(0x00, PORTB);
      break;
      
    default:      
  }                     
}

int main(void)
{
  int lift_off;
  
  outp(0x00, DDRA);		// Porta A como entrada
  outp(0xFF, DDRB);		// Porta B como saída
  outp(0x00, PORTB);		// A condição inicial do experimento é desligado
  
  lift_off = 0x01 & inp(PINA);	// Verifica a chegada no ponto lift-off
  while (lift_off != 0x01)
  {
    lift_off = 0x01 & inp(PINA);
  }
	
  inicializa_timers();
  sei();			// Habilita interrupções
    
  outp(0x88, PORTB);		// Inicia o experimento

  for (;;) {}              	// Laço eterno
}