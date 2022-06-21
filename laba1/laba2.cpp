#include<fcntl.h>
#include<unistd.h>
#include<linux/kd.h>
#include<sys/ioctl.h>
#include<map>
#include<time.h>
#include<fstream>
#include<iostream>


void make_signal(int name){
    while(name!=0){
        int fd;
        fd=open("/dev/console", O_RDWR);
        ioctl(fd, KDSETLED,7);
        if(name%10==1){
         
        sleep(1);

        }
        else{
          sleep(2);
        }
        name/=10;
        ioctl(fd, KDSETLED,0);
    }
      sleep(4);
}
 
int main(int argc, char*argv[]){

    if(argc!=2){
        std::cout<<"Give_orgument_please\n";
    }
    int num=atoi(argv[1]);
    int fd;
        fd=open("/dev/console", O_RDWR);
    while(num!=0){
          
           
          int n=0;
           if((num&1)!=0){
                 n|=1;

           }
           if((num&2)!=0){
                 n|=4;

           }
           if((num&4)!=0){
                 n|=2;
                  
           }
            std::cout<<num<<n;
           sleep(2);
            ioctl(fd, KDSETLED,n);
        
         sleep(2);
        ioctl(fd, KDSETLED,0);
            sleep(1);
        num--;
    }
    ioctl(fd, KDSETLED,7);
     sleep(1);
     ioctl(fd, KDSETLED,0);
      ioctl(fd, KDSETLED,7);
       sleep(1);
    ioctl(fd, KDSETLED,0);
       ioctl(fd, KDSETLED,7);
       sleep(2);
        ioctl(fd, KDSETLED,0);

    
   
}