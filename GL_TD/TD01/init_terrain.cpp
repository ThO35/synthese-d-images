#include "init_terrain.hpp"

void read_comments(std::ifstream &file, std::string &str)
{
    while (std::getline(file, str))
    {
        if (str[0] == '#')
        {
            continue;
        }
        else
        {
            break;
        }
    }
}

void read_file()
{

    std::string str;

    std::ifstream file("../assets/terrain/terrain.pgm", std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file! Check your path." << file.good() << std::endl;
        return;
    }

    std::getline(file, str);
    if (str != "P5")
        return;
    std::cout << str << std::endl;

    read_comments(file, str);
    std::string item;
    std::stringstream ss(str);
    std::string file_contents;
    std::vector<std::string> token;

    auto limit = ' ';

    while (std::getline(ss, item, limit))
    {
        token.push_back(item);
    }

    length = std::stoi(token[0]);
    width = std::stoi(token[1]);

    read_comments(file, str);

    std::cout << str << std::endl;
    donnes = std::vector<char>(width * length);
    file.read(donnes.data(), width * length);
    for (int i = 0; i < width * length; i++)
    {
        unsigned char current = static_cast<unsigned char>(donnes[i]);
        // std::cout << "Char :" << donnes[i] << " --- " << donnes[i] << " " << i << std::endl;
        if (current != 0 && current < minVal)
        {
            minVal = current;
        }
    }
    std::cout << "Min : " << static_cast<int>(minVal) << std::endl;
}
