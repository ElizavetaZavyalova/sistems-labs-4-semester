#include "hemming.h"
#include <iostream>

int main(int argc, char** argv) {
    std::string read = "hello.txt";
    std::string write = "by.txt";
   int except=0;
   int size=-1;
   if(argc==7){
        for(int i=1; i<6; i+=2){
            std::string key=argv[i];
           if(key=="-n"){
               size=atoi(argv[i+1]);
                  if(size<1){
                   std::cout<<"not correct size\n";
                   return -1;
               }
               except|=1;
           }
           else if(key=="-i"){
               read=argv[i+1];
                except|=2;
           }
            else if(key=="-o"){
               write=argv[i+1];
                except|=4;
            }
             else{
               std::cout<<"not correct orgument\n"<<key;
               return -1;
           }
        }
   }
   if(except!=7){
       std::cout<<"not correct orguments\n"<<except;
               return -1;
   }
   file_work* first=new file_work(read, size);
   first->coding_array();
   first->write_in_file(write);
   delete first;
  return 0;
}
