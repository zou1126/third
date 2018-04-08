//使用一个文件进行父子进程之间的通信
//也就是父进程发送一句话给子进程

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
void fork_com(const char* string,const char* filename)
{
    //打开文件
    int fd=open(filename,O_CREAT|O_EXCL|O_RDWR|O_APPEND,0777);
    int fdnew=dup(fd);
    if(fd==-1)
    {
        fd=open(filename,O_RDWR|O_APPEND);
    }
    //父进程
    if(fork()>0)
    {
        write(fd,string,strlen(string));
    }
    //子进程
    else
    {
        sleep(2);
        //设置一个缓冲区
        char buffer[108]={0};
        //设置偏移量
        lseek(fdnew,0,SEEK_SET);
        read(fdnew,buffer,sizeof(buffer)-1);
        printf("父进程传来的是:%s\n",buffer);
        close(fdnew);
    }
    
}
int main(int argc,const char* argv[])
{
    if(argc<2)
    {
        printf("使用方法: %s 文件名\n",argv[0]);
        exit(-1);
    }
    char *string="the early birds catch worm!";
    fork_com(string,argv[1]);
    return 0;
}

