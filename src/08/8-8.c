/**************************************************
 * @file 8-8.c
 * @author your name (you@domain.com)
 * @brief fork 两次以避免僵死进程
 * @version 0.1
 * @date 2022-10-19
 * @copyright Copyright (c) 2022
 **************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{ pid_t pid;
  if ((pid = fork()) < 0)
  { fprintf(stderr, "fork error\n");
    return 1;
  }
  else if (pid == 0)
  { if ((pid = fork()) < 0)
    { fprintf(stderr, "fork error\n");
      return 1;
    }
    else if (pid > 0)
      exit(0);
    printf("second child, pid = %ld, parent pid = %ld\n", (long)getpid(), (long)getppid());
    sleep(2);
    exit(0);
  }

  if (waitpid(pid, NULL, 0) != pid)
  { fprintf(stderr, "waitpid error\n");
    return 1;
  }
  /* do our own work... */
  return 0;
}
