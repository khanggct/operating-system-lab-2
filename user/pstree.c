#include "kernel/types.h"
#include "kernel/ptree.h"
#include "user/user.h"

void print_process_tree(struct ptreeinfo cur_pi, int level, struct ptreeinfo* ptri, int cnt) {
	for (int i = 0; i < level; i++) {
		printf("  ");
	}
	printf("%d %s state=%d mem=%ld\n",
			cur_pi.pid,
			cur_pi.name,
			cur_pi.state,
			cur_pi.memsize
		);

	for (int idx = 0; idx < cnt; idx++) {
		if (ptri[idx].ppid == cur_pi.pid) {
			print_process_tree(ptri[idx], level+1, ptri, cnt);
		}
	}
}

void sub_main() {
	int max = 100;
	struct ptreeinfo ptri[max];
	int cnt = ptree(ptri, max);
	// printf("cnt=%d\n", cnt);

	for (int idx = 0; idx < cnt; idx++) {
		if (ptri[idx].ppid < 0) { // root process
			print_process_tree(ptri[idx], 0, ptri, cnt);
			break;
		}
	}
}

int main() {
	if (fork() == 0) { // creating child process for testing
		exit(0);
	}
	else {
		if (fork() == 0) { // creating child process for testing
			exit(0);
		}
		else {
			sub_main();
			wait(0);
		}
		wait(0);
	}
	exit(0);
}