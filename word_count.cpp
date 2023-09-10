#include <iostream>
#include <string>
#include <map>
#include <list>
#include <fstream>

int main(int argc, char* argv[])
{
    std::string file_to_read = argv[1], file_to_write = argv[2], stroka, word;
    std::map <std::string, int> my_map;
    int count = 0, check;

    std::ifstream from;
    from.open(file_to_read);

    std::getline(from, stroka);

    while (1)
    {
        int word_flag = 0;
        for (int i = 0; i <= stroka.length(); i++)
        {
            if (isdigit(stroka[i]) || isalpha(stroka[i]))
            {
                if(word_flag == 0)
                {
                    word.erase(word.begin(), word.end());
                    count ++;
                }
                word_flag = 1;
                word += stroka[i];
            }
            else if (word_flag != 0)
            {
                if (my_map.find(word) != my_map.end())
                {
                    my_map[word] += 1;
                }
                else
                {
                    my_map.insert(std::pair <std::string, int> (word, 1));
                }
                word_flag = 0;
            }
        }
        if (from.eof())
        {
            break;
        }
        std::getline(from, stroka);
    }
    from.close();

    std::ofstream into;
    into.open(file_to_write);

    int num = my_map.size();

    for (int i = 0; i < num; i++)
    {
        std::map<std::string, int>::iterator max = my_map.begin();
        for(std::map<std::string, int>::iterator i = my_map.begin(); i != my_map.end(); i++)
        {
            if (i->second > max->second)
            {
                max = i;
            }
        }
        into << max->first << " - " << max->second << " - " << max->second * 100 / count << "%" << std::endl;
        my_map.erase(max);
    }

    into.close();

    return 0;
}