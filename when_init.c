//假设有祖父进程、父进程、子进程，设父进程退出后祖父进程没有立即调用wait()，
//即父进程成了僵尸进程，请问子进程何时被init收养(即子进程getppid()=1)?
//是父进程结束后还是祖父进程调用wait后呢？请编程验证你的答案
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main()
{
    pid_t ret=fork();
    //祖父进程
    if(ret>0)
    {
        sleep(1);
        wait(NULL);
        printf("爷爷wait之后\n");
    }
    else
    {
        //父进程
        if(fork()>0)
        {
            printf("父进程结束之后\n");
            exit(0);
        }
        //子进程
        else
        {
            while(getppid()!=1)
            {
                ;
            }
            printf("子进程被收养\n");
        }
    }
    return 0;
}