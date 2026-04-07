#include <dos.h>

#define BYTE unsigned char

BYTE MODOTEXTO = 3;
BYTE MODOTEXTOGR = 1;

void pausa(){
   union REGS inregs, outregs;
   inregs.h.ah = 0x00;
   int86(0x16, &inregs, &outregs);
}

void modovideo(BYTE modo){
   union REGS inregs, outregs;
   inregs.h.al = modo;
   inregs.h.ah = 0x00;
   int86(0x10, &inregs, &outregs);
}

int main(){
   
   modovideo(MODOTEXTOGR); //gráfico

   pausa();

   modovideo(MODOTEXTO); //texto

	return 0;
}