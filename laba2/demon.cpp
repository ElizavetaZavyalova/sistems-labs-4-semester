#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include "hemming.h"
#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <algorithm>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>
#include <fcntl.h>
 /*
#define ERR_EXIT(m) 
do{
    perror(m);
    exit(EXIT_FAILURE);
}while (0);*/

//void creat_daemon();
/*void writing_log(time_t &Time,int size, std::string&log, std::string&dir_name, int seconds){
      
            
      
}*/
#define ERR_EXIT(m)\
do\
{\
    perror(m);\
    exit(EXIT_FAILURE);\
}\
while (0);\

void creat_daemon(void)
{
    pid_t pid;
    pid = fork();
    if( pid == -1)
        ERR_EXIT("fork error");
    if(pid > 0 )
        exit(EXIT_SUCCESS);
    if(setsid() == -1)
        ERR_EXIT("SETSID ERROR");
    chdir("/");
    int i;
    for( i = 0; i < 3; ++i)
        close(i);
    open("/dev/null", O_RDWR);
    dup(0);
    dup(0);
    umask(0);
    return;
}
int main(int argc, char** argv)
{
    time_t t;
    int seconds=-1;
     std::string log = "";
    std::string dir_name = "";
   int except=0;
   int size=-1;
   if(argc==9){
        for(int i=1; i<8; i+=2){
            std::string key=argv[i];
           if(key=="-n"){
               size=atoi(argv[i+1]);
               if(size<1){
                   std::cout<<"not correct size\n";
                   return -1;
               }
               except|=1;
           }
           else if(key=="-l"){
               log=argv[i+1];
                except|=2;
           }
            else if(key=="-d"){
               dir_name=argv[i+1];
                except|=4;
           }
             else if(key=="-t"){
              seconds=atoi(argv[i+1]);
               if(seconds<1){
                   std::cout<<"not correct time\n";
                   return -1;
               }
                except|=8;
           }
           else{
               std::cout<<"not correct orguments"<<key<<"\n";
               return -1;
           }
        }
   }
   if(except!=15){
       std::cout<<"not correct orguments"<<except<<"\n";
               return -1;
   }
    int fd;
    std::cout<<"demon strt\n";
    creat_daemon();
    //creat_daemon();
    while(true){
         std::cout<<"I am demon\n";
        fd = open(log.c_str(),O_WRONLY|O_CREAT|O_APPEND,0644);
        if(fd == -1)
        exit(-1);
        t= time(0);
        char *buf = asctime(localtime(&t));
        write(fd,buf,strlen(buf));
        dirent *dp;  
    DIR *dir_f = opendir(dir_name.c_str());  
    int i = 1;
    while (dp = readdir(dir_f))
    {
        if (dp->d_type != DT_DIR)
        {   
            write(fd,dp->d_name,strlen(dp->d_name));
          
            std::string path=dp->d_name;
            path=dir_name+"/"+path;
            //st=dir_name+"/"+st;
            //std::cout<<st;

            file_work* second=new file_work(path, size);
           
            second->decoding_array();
            
            std::string ex=second->get_log();
            
            ex+='\0';
            delete second;
            
            std::cout<<ex;
            
            write(fd,ex.c_str(),strlen(ex.c_str()));
        }
    }
    rewinddir(dir_f);
        close(fd);
        sleep(seconds);
    }
    return 0;
}
 