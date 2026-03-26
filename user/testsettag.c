#include "kernel/types.h"
#include "user/user.h"

int main (int argc, char** argv) {
	settag(atoi(argv[1]));
	exit(0);
}