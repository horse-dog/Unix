#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
void prepare_fork(int cnt)
{ printf("prepare: %d\n", cnt); }

void parent_fork(int cnt)
{ printf("parent: %d\n", cnt); }

void child_fork(int cnt)
{ printf("child: %d\n", cnt); }

void prepare_fork0() { prepare_fork(0); }
void prepare_fork1() { prepare_fork(1); }
void prepare_fork2() { prepare_fork(2); }

void parent_fork0() { parent_fork(0); }
void parent_fork1() { parent_fork(1); }
void parent_fork2() { parent_fork(2); }

void child_fork0() { child_fork(0); }
void child_fork1() { child_fork(1); }
void child_fork2() { child_fork(2); }

int main(int argc, char *argv[])
{ pthread_atfork(prepare_fork0, parent_fork0, child_fork0);
  pthread_atfork(prepare_fork1, parent_fork1, child_fork1);
  pthread_atfork(prepare_fork2, parent_fork2, child_fork2);
  pid_t pid;
  if ((pid = fork()) == 0)
    printf("child, fork finished...\n");
  else
    printf("parent, fork finished...\n");
  return 0;
}