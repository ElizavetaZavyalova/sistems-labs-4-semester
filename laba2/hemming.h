#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <ctime>
#define uint unsigned int

enum inform {
    CODING, DECODING, NOSET
};

template<typename type>
class bit_array
{
	std::vector<type> mas;
	uint size = 0;
public:
    bit_array(const type* str, uint size = 8) {
        if (size != 0) {
            for (int i = 0; i < ((size - 1) / (8 * sizeof(type))) + 1; i++) {
                (this->mas).push_back(str[i]);
            }
        }
        this->size = size;
    }
    bit_array(uint size = 0) {
        this->size = size;
        if (size != 0) {
            for (int i = 0; i < ((size - 1) / (8 * sizeof(type))) + 1; i++) {
                (this->mas).push_back(0);
            }
        }
    }
    int find_exeption(uint size) {
        bit_array<char> decoding(size);
        decoding.decoding_heming(*this);
        bit_array<char> coding(size + give_control_bit(size));
        coding.coding_heming(decoding);
        int exeption = 0; int j = 0;
        for (int i = 1; i < size; i=i<<1) {
            if (give_bit(i - 1) != coding.give_bit(i - 1)) {
                exeption += i;
            } 
        }
        if (exeption != 0) {
            return exeption-this->give_control_bit(exeption);
        }
            return -1;
    }
    bool give_bit(const uint& bit) const {
        uint elem = bit / (8 * sizeof(type));
        if (elem >= mas.size()) {
            return 0;
        }
        uint num = 8 * sizeof(type) - ((elem + 1) * (8 * sizeof(type)) - bit - 1);
        bool b = (mas[elem] >> (sizeof(type) * 8 - num)) & 1;
        return (mas[elem] >> (sizeof(type) * 8 - num)) & 1;
    }
    std::vector<type>& get_mas() { return mas; }
    void set_bit(const uint& bit, const bool& b) {
        uint elem = bit / (8 * sizeof(type));
        while (elem >= mas.size()) {
            mas.push_back(0);
        }
        uint num = 8 * sizeof(type) - ((elem + 1) * (8 * sizeof(type)) - bit - 1);
        uint b1 =  b;
         
        b1 = (b1 << ((8 * sizeof(type) - num)));
        
        mas[elem] |= b1;
        
    }
    void change(int bait, int bit) {
        mas[bait] ^= (1 << (7-bit));
    }
    void set_array(const type* str, uint size = 8) {
        if (size != 0) {
            for (int i = 0; i < ((size - 1) / (8 * sizeof(type))) + 1; i++) {
                (this->mas).push_back(str[i]);
            }
        }
        this->size = size;
    }
    void set_zero(uint size = 0) {
        this->size = size;
        if (size != 0) {
            for (int i = 0; i < ((size - 1) / (8 * sizeof(type))) + 1; i++) {
                (this->mas).push_back(0);
            }
        }
    }
    uint give_control_bit( uint size) {
        uint count = 1;
        while (size != 0) {
            count++;
            size = size >> 1;
        }
        return count;
    }
    uint& get_size() { return size; };
    bool give(uint two_pow) {
        bool control = 0;
        for (int i = two_pow; i < this->size; i+=two_pow) {
            do {
                (give_bit(i - 1)) ? (control=!control) : (control); i++;

            } while (i % two_pow != 0);

        }
        return (control);
    }
    bit_array<type>& coding_heming(const bit_array<type>& decoding) {
       
        uint two_pow = 1; uint bit = 0;
        for (int i = 0; i < this->size; i++) {
            if (i + 1 == two_pow) {
                two_pow = two_pow << 1;
                this->set_bit(i, 0);
            }
            else {
                bool b = decoding.give_bit(bit);
                this->set_bit(i, decoding.give_bit(bit));
                bit++;
            }
        }
        for (int i = 1; i < two_pow; i = i << 1) {
            this->set_bit(i - 1, this->give(i));
        }
        return *this;
    }
    bit_array<type>& decoding_heming(const bit_array<type>& coding) {
        
        uint bit = 0, two_pow = 1;
        for (int i = 0; i < coding.size; i++) {

            if (two_pow != i + 1) {
                this->set_bit(bit, coding.give_bit(i));
                bit++;

            }
            else {
                two_pow = two_pow << 1;
            }
        }
        return *this;
    }
    void reset_bits_0(const uint first, const uint second, bit_array<type>&all) {
        uint bit = 0;
        for (uint i = first; i < second; i++) {
            this->set_bit(bit, all.give_bit(i));
                bit++;
        }
    }
    void reset_bits_to_w(const uint size_all, bit_array<type>& all) {
        
        for (uint i = 0; i < size_all; i++) {
            this->set_bit(this->size, all.give_bit(i));
            (this->size)++;
        }
    }
    void write_array(inform inf = DECODING) {

        uint two_pow = 1;
        uint w = (inf == NOSET) ? (size % 8) : (0);
        for (int i = 0; i < size + w; i++) {
            if ((i + 1 == two_pow) && inf == CODING) {
                std::cout << "(" << this->give_bit(i) << ")";
                two_pow = two_pow << 1;
            }
            else {
                std::cout << this->give_bit(i);
            }
        }
    }
};


class file_work{
    std::ifstream read;
    std::ofstream write;
    std::map<int, int> exc;
    bit_array<char> writing;
    uint size = 0;
    uint control_size = 0;
    bit_array<char> bits;
    std::string file_information = "";
public:
    file_work(std::string reading,   uint size) {
        read.open(reading, std::ios::binary);
        this->size = size;
        this->control_size = bits.give_control_bit(size);
    };
    ~file_work() {
        read.close();
         
    }
    void readfile() {
        while (!read.eof()) {
            char c = read.get();
            file_information += c;
        }
        bits.set_array(file_information.c_str(), file_information.size() * 8 * sizeof(char));
        
    }
    void coding_array() {
        readfile();
        int w = bits.get_size(), j=0;
        while (w > 0) {
            bit_array<char> decoding(size);
            bit_array<char> coding(size + control_size);
            decoding.reset_bits_0(j, j + size, bits);
            coding.coding_heming(decoding);
            
            writing.reset_bits_to_w(coding.get_size(), coding); w -= size;
            j += size;
            
        }
       
       
    }
    void decoding_array() {
         
        readfile();
        int w = bits.get_size(), j = 0; int block = -1;
        while (w >= size + control_size) {
            bit_array<char> coding(size + control_size);
            bit_array<char> decoding(size);;
            coding.reset_bits_0(j, j + size+control_size, bits);
          
            int erray = coding.find_exeption(decoding.get_size()); block++;
           
            if (erray != -1) {
            exc[block] = erray;
            }
             decoding.decoding_heming(coding);
         
            writing.reset_bits_to_w(decoding.get_size(), decoding); w -= (size + control_size);
            j += (size + control_size);

        }
         
    }
    void write_exc(){
         if (exc.size() == 1) {

            int b = (exc.begin()->first) * size + (exc.begin()->second);
            writing.change(b / 8, (b % 8));
            std::cout << "b";
        }
        if (exc.size() > 0) {
            for (auto i = exc.begin(); i != exc.end(); i++) {
                int b = (i->first)* control_size+(i->second);
                int bite = b / 8;
                int bit = b % 8;
                std::cout << "Bait:" << bite << "\nbit:" << bit<<"\n";
                }
               
            }
    }
    std::string get_log(){
         std::string str="\n";     // текущая дата, представленная в нормальной форме
          if (exc.size() > 0) {
            
            for (auto i = exc.begin(); i != exc.end(); i++) {
               
                int b = (i->first)* control_size+(i->second);
                int bite = b / 8;
                int bit = b % 8;
                str+="("+std::to_string(bite)+","+std::to_string(bit)+")\n";
             
        }
          }
        else{
            str+="No\n";
        }
        return str;
    }
    void write_in_file(std::string&output){
        write.open(output, std::ios::binary);
        for (auto i = writing.get_mas().begin(); i != writing.get_mas().end(); i++) {
            if((*i)!=-1){
              if(*i!=0)
            write << (*i);
            }
        }
        write.close();
    }
    bit_array<char> &get_write(){
           return writing;
    }
};