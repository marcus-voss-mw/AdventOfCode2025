#include <iostream>
#include <string>
#include <fstream>
#include <vector>

constexpr char INPUT_FILE[] = "input.txt";
constexpr static int MAX_POSITION = 99;

std::vector<std::string> readInput(const char* filename)
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

class Lock
{
public:
    void rotate(int steps)
    {
        const int NUM_POSITIONS = MAX_POSITION + 1;

        // Richtung feststellen
        int direction = (steps >= 0) ? 1 : -1;
        int clicks = std::abs(steps);

        // Jeden einzelnen Klick simulieren
        for (int i = 0; i < clicks; ++i)
        {
            position = (position + direction + NUM_POSITIONS) % NUM_POSITIONS;

            // Bei JEDEM Klick, der auf 0 landet, für Teil B zählen
            if (position == 0)
            {
                countB++;
            }
        }

        std::cout << "Rotating by " << steps << " steps to position " << position << std::endl;

        // Am ENDE der Rotation: Teil A zählt nur Endposition == 0
        if (position == 0)
        {
            count++;
        }
    }

    unsigned int getCount() const { return count; }
    unsigned int getCountB() const { return countB; }

private:
    int position = 50;
    unsigned int count = 0;   // nur Endposition 0
    unsigned int countB = 0;  // alle Klicks, die auf 0 zeigen
};



int main()
{
    std::cout << "Advent Day 01" << std::endl;
    auto lines = readInput(INPUT_FILE);
    std::cout << "Read " << lines.size() << " lines from " << INPUT_FILE << std::endl;

    Lock lock;
    for (const auto& line : lines)
    {
        std::cout << line << std::endl;
        int steps = std::stoi(line.substr(1));
        bool direction = line[0] == 'R'; // 'R' for right, 'L' for left
        lock.rotate(direction ? steps : -steps);
    }
    std::cout << "Solution: " << lock.getCount() << std::endl;
    std::cout << "Solution B: " << lock.getCountB() << std::endl;
}