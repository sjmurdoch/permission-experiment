#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int printgroups()
{
	int ngroups1, ngroups2;
	int i;
	gid_t *groups;

	printf("Real group ID: %d\n", getgid());
	printf("Effective group ID: %d\n", getegid());

	ngroups1 = getgroups(0, NULL);
	if (ngroups1 < 0)
	{
		perror("Error calling getgroups");
		exit(1);
	}
	printf("Found %d supplementary groups\n", ngroups1);

	groups = calloc(ngroups1, sizeof(gid_t));
	if (groups == NULL)
	{
		perror("Error calling calloc");
		exit(1);
	}
	ngroups2 = getgroups(ngroups1, groups);
	if (ngroups2 < 0)
	{
		perror("Error calling getgroups");
		exit(1);
	} else if (ngroups2 > ngroups1)
	{
		printf("Warning: group list truncated at %d\n", ngroups1);
	}
	

	for (i = 0; i < ngroups2; i++)
	{
		printf("  group ID %d\n", groups[i]);
	}

	free(groups);
	return 0;
}

int dropgroup(gid_t egid)
{
	int retval;

	printf("Changing egid to %d\n", egid);
	retval = setegid(egid);
	if (retval != 0)
	{
		perror("Error calling setegid");
		exit(1);
	}

	return 0;
}

int cat(char *filename)
{
	FILE *fh;
	char buf[1024];
	size_t nread;

	fh = fopen(filename, "r");
	if (fh == NULL)
	{
		perror("Error opening file");
		exit(1);
	}
	while ((nread = fread(buf, 1, sizeof buf, fh)) > 0)
		fwrite(buf, 1, nread, stdout);
	if (ferror(fh))
	{
		perror("Error reading from file");
		fclose(fh);
		exit(1);
	}
	fclose(fh);
	return 0;
}

int main(int argc, char *argv[])
{
	printgroups();
	if (argc > 1)
	{
		printf("\nReading from file %s ...\n", argv[1]);
		cat(argv[1]);
	}
}
