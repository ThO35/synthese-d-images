
#include <fstream>
#include<iostream>
#include <string>
#include<vector>
#include <sstream>
int main(int argc, char const *argv[])
{
    std::ifstream file("GL_TD/assets/terrain/terrain.pgm",std::ios::binary);
    if (!file.is_open()) 
    {
        std::cerr << "Error: Could not open file! Check your path." << file.good()<< std::endl;
        return 1;
    }
    std::string str;
    std::string file_contents;
    bool isP5 = false;
    auto i = 0;

    std::getline(file, str);
    if (str!= "P5") return 0;
    std::cout << str<< std::endl;
    while  (std::getline(file, str))
    {
        if (str[0] == '#')
        {
            continue;
        }else
        {
            break;
        }
    }

    auto limit = ' ';
    std::vector<std::string> token;
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss,item,limit)){
        token.push_back(item);
    }

    for (auto tmp : token){
        std::cout <<"Bouvle :"<< tmp<< std::endl;
    }

    int length, width;

    length =  std::stoi (token[0]);
    width =  std::stoi (token[1]);

    std::cout << "Converti"<< length<< width<<std::endl;

      while  (std::getline(file, str))
    {
        if (str[0] == '#')
        {
            continue;
        }else
        {
            break;
        }
    }

    std::cout << str<< std::endl;

    int max_value = std::stoi(str);


    auto donnes  = std::vector<char>(width*length);

    file.read(donnes.data(), width * length);

    unsigned char minVal = 255; 

    for (int i = 0; i < width*length; i++) {

        unsigned char current = static_cast<unsigned char>(donnes[i]);
        std::cout <<"Char :"<< donnes[i]<<" --- " <<donnes[i]<<" "<<i<< std::endl;
        if (current != 0 && current < minVal) {
            minVal = current;
        }
        
    }

    std::cout << "Min : " << static_cast<double>(minVal) << std::endl;


}



