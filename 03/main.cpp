#include <iostream>
#include <string>
#include <fstream>
#include <vector>

constexpr char INPUT_FILE[] = "input.txt";
constexpr static int MAX_POSITION = 99;

std::vector<std::string> readInput(const char *filename)
{
    std::vector<std::string> lines;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }
    return lines;
}

uint8_t char2Digit(char c)
{
    return static_cast<uint8_t>(c - '0');
}

unsigned int findHighestPair(const std::string &line)
{
    unsigned int highest = 0;

    for (size_t i = 0; i < line.size(); i++)
    {
        for (size_t j = i + 1; j < line.size(); j++)
        {
            unsigned int val = (char2Digit(line[i]) * 10 + char2Digit(line[j]));
            if (val > highest)
            {
                highest = val;
            }
        }
    }

    return highest;
}

unsigned long long findHighest12Pair(const std::string &line, unsigned int size)
{
    unsigned int highest = 0;
    int start = 0;
    std::string result;

    for (int n = 0; n < size; n++)
    {
        int end = line.size() - (size - n - 1);
        int best = start;


        for (int i = start; i < end; i++)
        {
            if (char2Digit(line[i]) > char2Digit(line[best]))
            {
                best = i;
            }
        }
        std::cout << " Best for position " << n << " is " << line[best] << " at pos" << best << std::endl;
        result += line[best];
        start = best + 1;
    }
    return std::stoul(result);
}

int main()
{
    std::cout << "Advent Day 03" << std::endl;
    auto lines = readInput(INPUT_FILE);
    std::cout << "Read " << lines.size() << " lines from " << INPUT_FILE << std::endl;

    unsigned long long sum = 0;
    for (const auto &line : lines)
    {
        std::cout << line << std::endl;
        unsigned long long highest = findHighest12Pair(line, 12);
        std::cout << " Highest pair: " << highest << std::endl;
        sum += highest;
    }
    std::cout << "Sum of highest pairs: " << sum << std::endl;

    return 0;
}