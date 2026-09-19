#include <unistd.h>

int main(void) {
	char *hello = "Hello , system programming .\n\n";
	write(1, hello, sizeof(hello));
	return 0;
}
