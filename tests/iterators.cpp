#include <string>
#include <iostream>

#define LOG(X) std::cout << X << std::endl;

void primeiro(std::string::iterator &begin,
              std::string::iterator &current_char)
{
    for (int i = 0; i < 3; i++)
    {
        current_char++;
    }
    std::string test = std::string(begin, current_char);
    LOG(test);
    begin = current_char;
}

void segundo(std::string::iterator &begin,
              std::string::iterator &current_char)
{
    for (int i = 0; i < 6; i++)
    {
        current_char++;
    }
    std::string test = std::string(begin, current_char);
    LOG(test);
    begin = current_char;
}

void terceiro(std::string::iterator &begin,
              std::string::iterator &current_char)
{
    for (int i = 0; i < 10; i++)
    {
        current_char++;
    }
    std::string test = std::string(begin, current_char);
    LOG(test);
    begin = current_char;
}


int main ()
{
    std::string text = "Eu sei que vou conseguir superar este problema, quem sabe a gente consegue né";

    std::string::iterator begin = text.begin();
    std::string::iterator end = text.end();
    std::string::iterator current_char = begin;

    primeiro(begin, current_char);
    segundo(begin, current_char);
    terceiro(begin, current_char);

    

}