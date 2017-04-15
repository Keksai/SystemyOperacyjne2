#define _POSIX_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h> //is a POSIX library, not a standard C library
//SIGINT to sygnal przerwania, generowany poprzez ^c
//SIGTSTP to sygnal zawieszenia, generowany poprzez ^z lub poprzez ^y z opoznieniem
int flaga =0;
void obslugaint()
{
	flaga=1;

}
void CheckFunction(char *argv[])
{
	int x = strlen(argv[1]);
	int power = 1;
	while (power < x)
	{
		power *= 2;
	}
	if (power > x)
	{
		power = power / 2;
		char b[power];
		for (int i = 0; i < power; i++)
		{
			b[i] = argv[1][i];
			//printf("Wyswietlaj to %c\n", b[i]);

		}
		b[power] = '\0';
		execl(argv[0], argv[0], b, NULL);
	}
}
int main(int argc, char *argv[])
{

	CheckFunction(argv);
	int nr_of_arguments = strlen(argv[1]);
	if (nr_of_arguments == 1)
	{

		//int aflag = 0;
		//funkcja_testowa();
		printf("%d ", (int) getpid());
		printf("%s ", argv[1]);

		if (argv[2] != NULL)
		{
			printf("%s", argv[3]);
		}
		printf("\n");
		kill((int)getpid(),SIGTERM);
	}
	char *text = malloc(nr_of_arguments * sizeof(char));
	strcpy(text, argv[1]);
	char *history = malloc(nr_of_arguments * sizeof(char));
	strcpy(history, text);
	char *history_all = malloc(100 * sizeof(char));
	strcat(history_all, history);
	if (argv[2] != NULL)
	{

		strcat(history_all, " ");
		strcat(history_all, argv[3]);
		//printf("%s\n",argv[2]);
	}
	int half_the_arguments = nr_of_arguments / 2;
	d[half_the_arguments] = '\0';
	e[half_the_arguments] = '\0';
	//printf ("%s\n", d);
	//printf ("%s\n", e);

	pid_t stefano = fork();

	if (stefano < 0)
	{
		perror("Fork failed. ERROR");
		exit(-1);
	}
	else if (stefano == 0)
	{
		setpgid(0,0);
		execl(argv[0], argv[0], d, history, history_all, NULL);
		//child place
	}
	pid_t ponczo = fork();

	if (ponczo < 0)
	{
		perror("Fork failed. ERROR");
		exit(-1);
	}
	else if (ponczo == 0)
	{
		setpgid(0,0);
		execl(argv[0], argv[0], e, history, history_all, NULL);
		//child place
	}

	//printf ("Oczekiwanie na pid %d %d\n", stefano, ponczo);
	
/*	int status1;
	wait(&status1);

	int status2;
	wait(&status2);
	printf("%d ", (int) getpid());
	printf("%s ", argv[1]);

	if (argv[2] != NULL)
	{
		printf("%s", argv[3]);
	}
	printf("\n"); */

	sigset_t iset3;
	sigpending(&iset3);
	if(argc == 2)
	{
	if(sigismember(&iset3,SIGTSTP))
	{
		printf("Wcisnieto ^z\n");
		sigprocmask(SIG_UNBLOCK, &iset2, NULL);

	}
	}
	
	return 0;
}
