/* Uso : Escreve_texto_LCD(Texto_LCD, Endereco_LCD, Endereco_Paralela);
         Linha_LCD(linha, Endereco_LCD, Endereco_paralela);
         Limpa_LCD(Endereco_LCD, Endereco_paralela);
         Inicializa_LCD(Endereco_LCD, Endereco_paralela);
*/

#include <cstring.h>
#include <sstream.h>

void Escreve_texto_LCD(string, unsigned int, unsigned int);
void Escreve_caracter_LCD(char, unsigned int, unsigned int);
bool Linha_LCD(unsigned int, unsigned int, unsigned int);
void Limpa_LCD(unsigned int, unsigned int);
void Inicializa_LCD(unsigned int, unsigned int);
void Escreve_instrucao_LCD(unsigned int, unsigned int, unsigned int);
void _delay(unsigned int);
