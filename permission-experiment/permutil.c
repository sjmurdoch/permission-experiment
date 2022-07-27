#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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
	}
	else if (ngroups2 > ngroups1)
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

int setgroup(uid_t euid, gid_t egid)
{
	int retval;

	printf("Changing egid to %d\n", egid);
	retval = setegid(egid);
	if (retval != 0)
	{
		perror("Error calling setegid");
		exit(1);
	}

	printf("Changing euid to %d\n", euid);
	retval = seteuid(euid);
	if (retval != 0)
	{
		perror("Error calling seteuid");
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

void help()
{
	printf("Usage:\n");
	printf("  permutil -p\n    Print current group membership\n\n");
	printf("  permutil -c FILENAME\n    Output contents of FILENAME to stdout\n\n");
	printf("  permutil -s UID GID [FILENAME]\n    set effective user to UID, effective group to GID, and optionally output contents of FILENAME\n\n");
}

int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		if (strcmp(argv[1], "-p") == 0)
		{
			printgroups();
		}
		else if (strcmp(argv[1], "-c") == 0 && argc > 2)
		{
			cat(argv[2]);
		}
		else if (strcmp(argv[1], "-s") == 0 && argc > 3)
		{
			long int gid, uid;
			char *end;

			uid = strtol(argv[2], &end, 0);
			if (end == argv[2] || *end != '\0' || errno == ERANGE)
			{
				help();
				return 1;
			}

			gid = strtol(argv[3], &end, 0);
			if (end == argv[3] || *end != '\0' || errno == ERANGE)
			{
				help();
				return 1;
			}

			setgroup(uid, gid);
			printgroups();

			if (argc > 4) {
				cat(argv[4]);
			}
		}
		else
		{
			help();
			return 1;
		}
	}
	else
	{
		help();
		return 0;
	}
}
