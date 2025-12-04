#include <iostream>
#include <string>
#include <fstream>
#include <vector>

constexpr char INPUT_FILE[] = "input.txt";
const int directions[8][2] = {
    {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

enum class PAPER_TYPE : char
{
    EMPTY = '.',
    ROLL = '@',
    CAN_BE_ACCESSED = 'x',
};

std::vector<std::vector<PAPER_TYPE>> readInput(const char *filename)
{
    std::vector<std::vector<PAPER_TYPE>> grid = {};
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line))
    {
        std::vector<PAPER_TYPE> row;
        for (char c : line)
        {
            switch (PAPER_TYPE(c))
            {
            case PAPER_TYPE::EMPTY:
                row.push_back(PAPER_TYPE::EMPTY);
                break;
            case PAPER_TYPE::ROLL:
                row.push_back(PAPER_TYPE::ROLL);
                break;
            default:
                throw std::runtime_error("Unknown character in input");
            }
        }
        grid.push_back(row);
    }
    return grid;
}

void printGrid(const std::vector<std::vector<PAPER_TYPE>> &grid)
{
    for (const auto &row : grid)
    {
        for (const auto &cell : row)
        {
            std::cout << static_cast<char>(cell);
        }
        std::cout << std::endl;
    }
}

bool canBeAccessed(const std::vector<std::vector<PAPER_TYPE>> &grid, int x, int y)
{
    unsigned int count = 0;
    std::cout << "Checking roll at (" << x << ", " << y << ")\n";
    // Check all 8 directions
    for (const auto &dir : directions)
    {
        int newX = x + dir[0];
        int newY = y + dir[1];

        // Check bounds
        if (newX >= 0 && newX < grid.size() && newY >= 0 && newY < grid[0].size())
        {
            std::cout << "  Neighbor at (" << newX << ", " << newY << "): " << static_cast<char>(grid[newX][newY]) << "\n";
            if (grid[newX][newY] == PAPER_TYPE::ROLL || grid[newX][newY] == PAPER_TYPE::CAN_BE_ACCESSED)
            {
                count++;
                std::cout << "    Found adjacent roll. Current count: " << count << "\n";
            }
        }
    }
    std::cout << "Total adjacent rolls: " << count << "\n";
    return count < 4;
}

int main()
{
    auto grid = readInput(INPUT_FILE);
    unsigned int count = 0;
    unsigned int localCount = count;
    do
    {
        localCount = 0;
        for (size_t i = 0; i < grid.size(); i++)
        {
            for (size_t j = 0; j < grid[i].size(); j++)
            {
                if (grid[i][j] == PAPER_TYPE::ROLL && canBeAccessed(grid, i, j))
                {
                    grid[i][j] = PAPER_TYPE::CAN_BE_ACCESSED;
                    localCount++;
                }
            }
        }
        count += localCount;

        // Remove All accessible rolls for next iteration
        for (size_t i = 0; i < grid.size(); i++)
        {
            for (size_t j = 0; j < grid[i].size(); j++)            {
                if (grid[i][j] == PAPER_TYPE::CAN_BE_ACCESSED)
                {
                    grid[i][j] = PAPER_TYPE::EMPTY;
                }
            }
        }
    }
    while (localCount > 0);
    printGrid(grid);
    std::cout << "Number of accessible rolls: " << count << std::endl;

    return 0;
}