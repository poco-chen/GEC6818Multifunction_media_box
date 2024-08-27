#include "game_control.h"

void pause_game()
{
	paused = !paused;
	printf("stop:%d\n", paused);
}

void restart_game()
{
	char *args[] = {"test1", NULL};
	execv(args[0], args);

	perror("execv");
	exit(EXIT_FAILURE);
}