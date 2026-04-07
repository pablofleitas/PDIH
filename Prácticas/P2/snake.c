#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define FRAME_DELAY_US 90000

typedef struct {
	int y;
	int x;
} Point;

static bool show_welcome_screen(void) {
	int rows, cols;
	int y;
	int x;
	int key;

	nodelay(stdscr, FALSE);

	clear();
	getmaxyx(stdscr, rows, cols);
	box(stdscr, 0, 0);

	if (rows < 12 || cols < 46) {
		y = rows / 2 - 1;
		if (y < 1) {
			y = 1;
		}
		x = (cols - 30) / 2;
		if (x < 1) {
			x = 1;
		}
		mvprintw(y, x, "Snake con ncurses");
		if (y + 1 < rows - 1) {
			mvprintw(y + 1, x, "S/Enter: jugar   Q: salir");
		}
	} else {
		y = rows / 2 - 4;
		if (y < 1) {
			y = 1;
		}

		x = (cols - 18) / 2;
		if (x < 1) {
			x = 1;
		}
		mvprintw(y, x, "Snake con ncurses");

		x = (cols - 28) / 2;
		if (x < 1) {
			x = 1;
		}
		mvprintw(y + 2, x, "Autor: Pablo Soriano Flietas");

		x = (cols - 10) / 2;
		if (x < 1) {
			x = 1;
		}
		mvprintw(y + 4, x, "Controles:");

		x = (cols - 28) / 2;
		if (x < 1) {
			x = 1;
		}
		mvprintw(y + 5, x, "Flechas -> mover serpiente");

		x = (cols - 30) / 2;
		if (x < 1) {
			x = 1;
		}
		mvprintw(y + 6, x, "Q -> terminar partida actual");

		x = (cols - 32) / 2;
		if (x < 1) {
			x = 1;
		}
		mvprintw(y + 7, x, "Comida (@ roja) -> suma longitud");

		x = (cols - 29) / 2;
		if (x < 1) {
			x = 1;
		}
		mvprintw(y + 9, x, "S/Enter: empezar   Q: salir");
	}

	refresh();
	while (1) {
		key = getch();
		if (key == 's' || key == 'S' || key == '\n' || key == KEY_ENTER) {
			nodelay(stdscr, TRUE);
			return true;
		}
		if (key == 'q' || key == 'Q') {
			return false;
		}
	}

	return false;
}

static bool is_on_snake(const Point *snake, int length, int y, int x) {
	for (int i = 0; i < length; i++) {
		if (snake[i].y == y && snake[i].x == x) {
			return true;
		}
	}
	return false;
}

static Point random_food(const Point *snake, int length, int rows, int cols) {
	Point food;

	do {
		food.y = (rand() % (rows - 2)) + 1;
		food.x = (rand() % (cols - 2)) + 1;
	} while (is_on_snake(snake, length, food.y, food.x));

	return food;
}

static int run_game(void) {
	int rows, cols;
	int direction_y = 0;
	int direction_x = 1;
	int key;
	bool game_over = false;
	bool use_color;
	WINDOW *gamewin;

	getmaxyx(stdscr, rows, cols);
	use_color = has_colors();

	if (rows < 10 || cols < 20) {
		clear();
		mvprintw(rows / 2, (cols - 45) / 2, "Ventana demasiado pequena. Minimo recomendado: 20x10");
		mvprintw(rows / 2 + 1, (cols - 29) / 2, "Pulsa una tecla para continuar");
		nodelay(stdscr, FALSE);
		refresh();
		getch();
		nodelay(stdscr, TRUE);
		return 0;
	}

	gamewin = newwin(rows, cols, 0, 0);
	if (gamewin == NULL) {
		nodelay(stdscr, FALSE);
		clear();
		mvprintw(rows / 2, (cols - 38) / 2, "No se pudo crear la ventana principal");
		mvprintw(rows / 2 + 1, (cols - 29) / 2, "Pulsa una tecla para continuar");
		refresh();
		getch();
		nodelay(stdscr, TRUE);
		return 0;
	}

	if (use_color) {
		wbkgd(gamewin, COLOR_PAIR(2));
	} else {
		wbkgd(gamewin, A_NORMAL);
	}

	keypad(gamewin, TRUE);
	nodelay(gamewin, TRUE);

	int max_cells = (rows - 2) * (cols - 2);
	Point *snake = malloc((size_t)max_cells * sizeof(Point));
	if (snake == NULL) {
		delwin(gamewin);
		nodelay(stdscr, FALSE);
		clear();
		mvprintw(rows / 2, (cols - 43) / 2, "No se pudo reservar memoria para la serpiente");
		mvprintw(rows / 2 + 1, (cols - 29) / 2, "Pulsa una tecla para continuar");
		refresh();
		getch();
		nodelay(stdscr, TRUE);
		return 0;
	}

	int length = 1;
	snake[0].y = rows / 2;
	snake[0].x = cols / 2;

	Point food = random_food(snake, length, rows, cols);

	while (!game_over) {
		key = wgetch(gamewin);

		if (key == 'q' || key == 'Q') {
			game_over = true;
			continue;
		}

		if (key == KEY_UP && direction_y != 1) {
			direction_y = -1;
			direction_x = 0;
		} else if (key == KEY_DOWN && direction_y != -1) {
			direction_y = 1;
			direction_x = 0;
		} else if (key == KEY_LEFT && direction_x != 1) {
			direction_y = 0;
			direction_x = -1;
		} else if (key == KEY_RIGHT && direction_x != -1) {
			direction_y = 0;
			direction_x = 1;
		}

		int new_head_y = snake[0].y + direction_y;
		int new_head_x = snake[0].x + direction_x;

		if (new_head_y <= 0 || new_head_y >= rows - 1 || new_head_x <= 0 || new_head_x >= cols - 1) {
			game_over = true;
			continue;
		}

		bool ate_food = (new_head_y == food.y && new_head_x == food.x);

		if (ate_food && length < max_cells) {
			for (int i = length; i > 0; i--) {
				snake[i] = snake[i - 1];
			}
			length++;
		} else {
			for (int i = length - 1; i > 0; i--) {
				snake[i] = snake[i - 1];
			}
		}

		snake[0].y = new_head_y;
		snake[0].x = new_head_x;

		if (ate_food) {
			food = random_food(snake, length, rows, cols);
		}

		werase(gamewin);
		box(gamewin, '|', '-');
		mvwprintw(gamewin, 0, 2, " Longitud: %d ", length);
		if (cols > 20) {
			mvwprintw(gamewin, 0, cols - 16, " Q para salir ");
		}

		if (use_color) {
			wattron(gamewin, COLOR_PAIR(1));
			mvwaddch(gamewin, food.y, food.x, '@');
			wattroff(gamewin, COLOR_PAIR(1));
		} else {
			mvwaddch(gamewin, food.y, food.x, '@');
		}

		mvwaddch(gamewin, snake[0].y, snake[0].x, 'O');
		for (int i = 1; i < length; i++) {
			mvwaddch(gamewin, snake[i].y, snake[i].x, 'o');
		}

		wrefresh(gamewin);
		usleep(FRAME_DELAY_US);
	}

	free(snake);
	delwin(gamewin);
	touchwin(stdscr);
	refresh();
	return length - 1;
}

static bool show_summary_screen(int score) {
	int rows, cols;
	int key;

	nodelay(stdscr, FALSE);
	clear();
	getmaxyx(stdscr, rows, cols);

	box(stdscr, 0, 0);
	mvprintw(rows / 2 - 2, (cols - 20) / 2, "Fin de la partida");
	mvprintw(rows / 2 - 1, (cols - 26) / 2, "Marcador final: %d", score);
	mvprintw(rows / 2, (cols - 32) / 2, "Felicidades, gran partida!");
	mvprintw(rows / 2 + 2, (cols - 44) / 2, "Pulsa R para jugar de nuevo o Q para salir");
	refresh();

	while (1) {
		key = getch();
		if (key == 'r' || key == 'R') {
			nodelay(stdscr, TRUE);
			return true;
		}
		if (key == 'q' || key == 'Q') {
			return false;
		}
	}
}

int main(void) {
	bool play_again;
	int score;

	initscr();
	noecho();
	cbreak();
	curs_set(FALSE);
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	srand((unsigned int)time(NULL));

	if (has_colors()) {
		start_color();
		init_pair(1, COLOR_RED, COLOR_BLACK);
		init_pair(2, COLOR_WHITE, COLOR_BLUE);
	}

	play_again = show_welcome_screen();

	while (play_again) {
		score = run_game();
		play_again = show_summary_screen(score);
	}

	endwin();
	return 0;
}
