#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int getch() {
	int c;
	struct termios old, mod;
	tcgetattr(STDIN_FILENO, &old);
	mod = old;
	mod.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &mod);
	c = getc(stdin);
	tcsetattr(STDIN_FILENO, TCSANOW, &old);
	return c;
}
