#include <stdio.h>
#include <dos.h>

int mi_getchar(){
	 union REGS inregs, outregs;
	 int caracter;

	 inregs.h.ah = 0x08;
	 int86(0x21, &inregs, &outregs);

	 caracter = outregs.h.al;
	 return caracter;
}

void mi_putchar(char c){
	 union REGS inregs, outregs;

	 inregs.h.ah = 2;
	 inregs.h.dl = c;
	 int86(0x21, &inregs, &outregs);
}

int main(){
   int tmp;

   printf("\nIndique el caracter a imprimir...  ");
   tmp = mi_getchar();

   printf("\nHa seleccionado el siguiente caracter:  ");
   mi_putchar((char)tmp);

	return 0;
}