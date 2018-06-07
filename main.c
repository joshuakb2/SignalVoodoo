#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    bool * ping = (bool *) mmap(NULL, sizeof(bool), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
    *ping = false;
    
    pid_t pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "%s\n", "fork() failed.");
        exit(1);
    }
    else
    {
        if (pid == 0)   //  child
        {
            while (true)
            {
                sleep(1);
                if (*ping)
                {
                    printf("%s\n", "Parent process did not reset ping.");
                }
                else
                {
                    *ping = true;
                }
            }
        }
        else    //  parent
        {
            printf("The child PID is %d.\n\n", (int) pid);

            while (true)
            {
                *ping = false;
            }
        }
    }
}
