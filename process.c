//创建两个子进程，一个进程执行ls  /root -l -a
//另一个睡5秒，然后父进程等待两个进程结束。打印两个子进程的pid。
//提示，man一下execl

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
    //父进程
    if(fork()>0)
    {
        pid_t ret=wait(NULL);
        //printf("子进程1 pid %d\n",ret);
        //子进程1
        if(fork()>0)
        {
            pid_t ret=wait(NULL);
            printf("子进程1的pid是:%d\n",getpid());
           // printf("子进程2 pid %d\n",ret);
            //函数说明：execl()用来执行参数path 字符串所代表的文件路径, 
            //接下来的参数代表执行该文件时传递过去的argv(0), argv[1], ...,
            //最后一个参数必须用空指针(NULL)作结束.
            execl("/bin/ls","ls","/root","-al",(char *)0);
        }

    }
    else
    {
        
        //子进程2
        printf("子进程2的pid是:%d\n",getpid());
        sleep(3);
        exit(0);
    }
    return 0;
}