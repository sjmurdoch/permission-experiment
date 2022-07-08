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

int cat(char *filename) {
	FILE *fh;
	char buf[1024];
	size_t nread;

	fh = fopen(filename, "r");
	if (fh == NULL) {
		perror("Error opening file");
		return 1;
	}
	while ((nread = fread(buf, 1, sizeof buf, fh)) > 0)
        	fwrite(buf, 1, nread, stdout);
    	if (ferror(fh)) {
		perror("Error reading from file");
   		fclose(fh);
		return 1;
	}
   	fclose(fh);
	return 0;
}


int main(int argc, char *argv[]) {
	printgroups();
	if (argc > 1) {
		printf("\nReading from file %s ...\n", argv[1]);
		cat(argv[1]);
	}
}
