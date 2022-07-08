#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int printgroups() {
	int ngroups;
	int i;
	gid_t *groups;

	printf("Real group ID: %d\n", getgid());
	printf("Effective group ID: %d\n", getegid());

	ngroups = getgroups(0, NULL);
	if (ngroups < 0) {
		perror("Error calling getgroups");
		return 1;
	}
        printf("Found %d supplementary groups\n", ngroups);
	groups = calloc(ngroups, sizeof(gid_t));
	ngroups = getgroups(ngroups, groups);
	if (ngroups < 0) {
		perror("Error calling getgroups");
		return 1;
	}
	for (i = 0; i < ngroups; i++) {
		printf("  group ID %d\n", groups[i]);
	}
	return 0;
}

int main(int argc, char *argv[]) {
	printgroups();
	printf("Changing egid %d\n", setegid(1001));
	printgroups();
}
