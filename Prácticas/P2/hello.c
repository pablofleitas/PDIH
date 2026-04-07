#include <ncurses.h>
int main() {
    initscr();            // Inicializar modo curses
    printw("Hello, World!"); // Imprimir mensaje
    refresh();            // Mostrar mensaje por pantalla
    getch();              // Esperar la pulsación de una teclas
    endwin();             // Terminar modo curses

    return 0;
}