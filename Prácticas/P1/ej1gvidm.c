#include <stdio.h>
#include <dos.h>

void mi_pausa(){
   union REGS inregs, outregs;
	 inregs.h.ah = 8;
	 int86(0x21, &inregs, &outregs);
}

int mi_getvideomode(){
	 union REGS inregs, outregs;
	 int mode;

	 inregs.h.ah = 0x0F;
	 int86(0x10, &inregs, &outregs);

	 mode = outregs.h.al;
	 return mode;
}

int main(){
   int modo = mi_getvideomode();
   printf("Modo de video actual: %d\n", modo);

   mi_pausa();

    return 0;
}