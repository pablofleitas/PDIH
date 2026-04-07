#include <dos.h>

#define BYTE unsigned char

BYTE MODOTEXTO = 3;
BYTE MODOTEXTOGR = 1;

void mi_getchar(){
	 union REGS inregs, outregs;
	 //int caracter;

	 inregs.h.ah = 1;
	 int86(0x21, &inregs, &outregs);

	 //caracter = outregs.h.al;
	 //return caracter;
}

void modovideo(BYTE modo){
   union REGS inregs, outregs;
   inregs.h.al = modo;
   inregs.h.ah = 0x00;
   int86(0x10, &inregs, &outregs);
}

int main(){
   
   printf("\nPulsa una tecla para borrar la pantalla...  ");

   mi_getchar();

   modovideo(MODOTEXTOGR); //gráfico

   modovideo(MODOTEXTO); //texto

	return 0;
}