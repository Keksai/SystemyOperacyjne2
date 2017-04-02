#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void CheckFunction(char *argv[])
{
    int x = strlen(argv[1]);
    int power = 1;
    while (power < x) {
        power *= 2;
    }
    if (power > x) {
        power = power / 2;
        char b[power];
        for (int i = 0; i < power; i++) {
            b[i] = argv[1][i];
            
        }
        b[power] = '\0';
        execl(argv[0], argv[0], b, NULL);
    }
}

int main(int argc, char *argv[]) {
	CheckFunction(argv);
	int nr_of_arguments = strlen(argv[1]);
	if (nr_of_arguments == 1) {
		printf("%d ", (int) getpid());
		printf("%s ", argv[1]);

		if (argv[2] != NULL) {
			printf("%s", argv[3]);
		}
		printf("\n");
		exit(0);
	}
	char *text = malloc(nr_of_arguments * sizeof(char));
	strcpy(text, argv[1]);
	char *history = malloc(nr_of_arguments * sizeof(char));
	strcpy(history, text);
	char *history_all = malloc(100 * sizeof(char));
	strcat(history_all, history);

	if(argv[2] != NULL) {

		strcat(history_all, " ");
		strcat(history_all, argv[3]);
		//printf("%s\n",argv[2]);
	}

	int half_the_arguments = nr_of_arguments / 2;
	char *d = malloc(half_the_arguments + 1 * sizeof(char));
	char *e = malloc(half_the_arguments + 1 * sizeof(char));
	strncpy(d, text, half_the_arguments);
	strncpy(e, text + half_the_arguments, half_the_arguments);
	d[half_the_arguments] = '\0';
	e[half_the_arguments] = '\0';

	pid_t stefano = fork();

	if (stefano < 0) {
		perror("Fork failed. ERROR");
		exit(-1);
	}
	else if (stefano == 0) {
		execl(argv[0], argv[0], d, history, history_all, NULL);
		exit(0);
	}
	pid_t ponczo = fork();

	if (ponczo < 0) {
		perror("Fork failed. ERROR");
		exit(-1);
	}
	else if (ponczo == 0) {
		execl(argv[0], argv[0], e, history, history_all, NULL);
		exit(0);
	}

	int status1;
	wait(&status1);
if(!WIFEXITED(status1)) {
	printf("STATUS ERROR");
}


	int status2;
	wait(&status2);
if(!WIFEXITED(status2)) {
	printf("STATUS ERROR");
}
	printf("%d ", (int) getpid());
	printf("%s ", argv[1]);

	if (argv[2] != NULL) {
		printf("%s", argv[3]);
	}
	printf("\n");

	return 0;
}

//gcc so2_lab3.c -o so2_lab3

