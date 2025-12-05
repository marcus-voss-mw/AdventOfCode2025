#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

constexpr char INPUT_FILE[] = "input.txt";

struct Range
{
    uint64_t start;
    uint64_t end;
};

std::vector<Range> freshRanges;
std::vector<uint64_t> products;

void readInput()
{
    std::ifstream inputFile(INPUT_FILE);
    bool rangesEnded = false;
    std::string line;
    while (std::getline(inputFile, line))
    {
        if (line.empty())
        {
            rangesEnded = true;
            continue;
        }

        if (!rangesEnded)
        {
            size_t dashPos = line.find('-');
            uint64_t start = std::stoull(line.substr(0, dashPos));
            uint64_t end = std::stoull(line.substr(dashPos + 1));
            freshRanges.push_back({start, end});
        }
        else
        {
            products.push_back(std::stoull(line));
        }
    }

    inputFile.close();
}

uint64_t countUniqueFreshIds(std::vector<Range> ranges)
{
    if (ranges.empty())
        return 0;

    // Sortiere die Bereiche nach Startwert
    std::sort(ranges.begin(), ranges.end(),
              [](const Range &a, const Range &b)
              { return a.start < b.start; });

    uint64_t total = 0;
    Range current = ranges[0];

    for (size_t i = 1; i < ranges.size(); ++i)
    {
        const auto &r = ranges[i];

        if (r.start <= current.end + 1)
        {
            // überlappend oder direkt angrenzend: mergen
            current.end = std::max(current.end, r.end);
        }
        else
        {
            // abgeschlossenes Intervall
            total += (current.end - current.start + 1);
            current = r;
        }
    }

    // letztes Intervall
    total += (current.end - current.start + 1);
    return total;
}

int main()
{
    readInput();
    unsigned long numFresh = 0;

    for (const auto &product : products)
    {
        for (const auto &range : freshRanges)
        {
            if (product >= range.start && product <= range.end)
            {
                numFresh++;
                break;
            }
        }
    }

    std::cout << "Number of fresh products: " << numFresh << std::endl;
    std::cout << "Number of unique fresh IDs: " << countUniqueFreshIds(freshRanges) << std::endl;

    return 0;
}