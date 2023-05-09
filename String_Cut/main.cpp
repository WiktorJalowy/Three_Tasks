#include <string>
#include <functional>
#include <iostream>

void StringCut(std::string& strToCut, std::function<bool(char)> predicate)
{
    for(long unsigned int i = 0; i < strToCut.size(); i++)
    {
        if(predicate(strToCut[i]))
        {
            strToCut.erase(strToCut.begin());
            i--;
        }
        else
        {
            break;
        }
    }
    for(long unsigned int i = strToCut.size() - 1; i > 0; i--)
    {
        if(predicate(strToCut[i]))
        {
            strToCut.erase(strToCut.begin() + i);
        }
        else
        {
            break;
        }
    }
}

bool predicate(const char& symbol) {if(symbol == ' ') {return true;} else {return false;}}

int main()
{
    std::string tobecut = "    BBbbBBBBbBB     b     ";
    std::cout << tobecut << std::endl;
    std::cout << tobecut.size() << std::endl;
    StringCut(tobecut, predicate);
    std::cout << tobecut << std::endl;
    std::cout << tobecut.size() << std::endl;
}