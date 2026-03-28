#include "kernel/types.h"
#include "user/user.h"



int main(int argc, char** argv) {
	// Checking valid arguments
	if (argc <= 3) {
		printf("trace: requires at least 3 arguments\n");
		exit(1);
	}
	for (int i = 0; i < strlen(argv[2]); i++) {
		if (argv[2][i] < '0' || argv[2][i] > '9') {
			printf("trace: invalid mask\n");
			exit(1);
		}
	}

	// Pass value to child arguments before use `exec`
	int child_argc = argc - 2;
	char* child_argv[child_argc+1];
	for (int i = 0; i < child_argc; i++) {
		child_argv[i] = argv[i+2];
	}
	child_argv[child_argc] = 0;

	
	if (fork() == 0) {
		trace(atoi(argv[1]));
		close(1);
		exec(child_argv[0], child_argv);
	}
	else {
		wait(0);
	}
	exit(0);
}