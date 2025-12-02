#include <iostream>
#include <string>
#include <fstream>
#include <vector>

constexpr char INPUT_FILE[] = "input.txt";

struct Range
{
    long long start;
    long long end;
};

std::vector<Range> readInput(char const *filename)
{
    std::vector<Range> ranges;
    std::ifstream file(filename);
    std::string line;
    if (!std::getline(file, line))
    {
        return ranges;
    }

    std::size_t start = 0;
    while (start < line.size())
    {
        std::size_t comma = line.find(',', start);
        std::string token = (comma == std::string::npos)
                                ? line.substr(start)
                                : line.substr(start, comma - start);

        if (!token.empty())
        {
            std::size_t dash = token.find('-');
            if (dash != std::string::npos)
            {
                long long a = std::stoll(token.substr(0, dash));
                long long b = std::stoll(token.substr(dash + 1));
                ranges.push_back(Range{a, b});
            }
        }

        if (comma == std::string::npos)
            break;
        start = comma + 1;
    }

    return ranges;
}

bool isTwoRepeated(long long n)
{
    std::string s = std::to_string(n);
    if (s.size() % 2 != 0)
    {
        return false;
    }
    std::size_t half = s.size() / 2;
    return s.substr(0, half) == s.substr(half);
}

bool isAllDigitsRepeated(long long n)
{
    std::string s = std::to_string(n);

    // Eine Ziffer allein ist per Definition nicht "wiederholt"
    if (s.size() < 2)
        return false;

    std::size_t totalLen = s.size();

    // len = Länge des sich wiederholenden Blocks
    for (std::size_t len = 1; len <= totalLen / 2; ++len)
    {
        if (totalLen % len != 0)
            continue;

        std::string pattern = s.substr(0, len);
        bool ok = true;

        for (std::size_t pos = len; pos < totalLen; pos += len)
        {
            if (s.substr(pos, len) != pattern)
            {
                ok = false;
                break;
            }
        }

        if (ok)
            return true;
    }

    return false;
}

int main()
{
    auto ranges = readInput(INPUT_FILE);
    long long sum = 0;
    for (const auto &range : ranges)
    {
        for (long long i = range.start; i <= range.end; ++i)
        {
            if (isAllDigitsRepeated(i))
            {
                std::printf("Found: %lld\n", i);
                sum += i;
            }
        }
    }
    std::printf("Sum: %lld\n", sum);
}