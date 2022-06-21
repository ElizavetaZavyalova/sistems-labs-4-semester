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

    std::map<char, int>  key;
    key['A']=12;
    key['B']=2111;
    key['C']=2121;
    key['D']=211;
    key['E']=1;
    key['F']=1121;
    key['G']=221;
    key['H']=1111;
    key['I']=11;
    key['J']=1222;
    key['K']=212;
    key['L']=1211;
    key['M']=22;
    key['N']=21;
    key['O']=222;
    key['P']=1221;
    key['Q']=2212;
    key['R']=121;
    key['S']=111;
    key['T']=2;
    key['U']=112;
    key['V']=1112;
    
    key['W']=122;
    key['X']=2112;
    key['Y']=2122;
    key['Z']=221;
    if(argc!=2){
        std::cout<<"Give_orgument_please\n";
    }
    std::ifstream file;
    char name=' ';
    file.open(argv[1]);
    name=file.get();
    while(name!=-1){
      make_signal(key[name]);
      name=file.get();
    }
   
}
