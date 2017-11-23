void OutPortB(unsigned int Endereco, unsigned int Dado)
{
  _DX = Endereco;
  _AX = Dado;

  // Inicia um bloco de instruções em assembly
  asm
  {
    // Escreve byte AL no endereço dado por DX
    out dx, al
  }
}

unsigned int InPortB(unsigned int Endereco)
{
  _DX = Endereco;

  // Inicia um bloco de instruções em assembly
  asm
  {
    // Lê byte da porta DX e coloca em AL
    in al, dx

    // Zera a parte alta de AX
    mov ah, 0x00
  }

  // Retorna o valor lido da porta
  return (_AX);
}
