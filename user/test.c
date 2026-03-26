#include "kernel/types.h"
#include "user/user.h"

int main(void) {
	int pid = getpid();
	printf("%d", pid);
	exit(0);
}