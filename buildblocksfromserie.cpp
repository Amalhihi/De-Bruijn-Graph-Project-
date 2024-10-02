#include <iostream>
#include <vector>

// Function to build blocks from the binary series and reorder elements in each block
std::vector<std::vector<int>> buildBlocks(const std::vector<int>& serie, int col, int row, int block) {
    int totalElements = col * row * block;

    if (serie.size() != totalElements) {
        std::cout << "Error: The size of the binary series does not match col * row * block." << std::endl;
        return {};
    }

    std::vector<std::vector<int>> blocks;
    int currentIndex = 0;

    for (int b = 0; b < block; ++b) {
        std::vector<int> currentBlock;
        std::vector<std::vector<int>> blockMatrix(row, std::vector<int>(col, 0));

        for (int r = 0; r < row; ++r) {
            for (int c = 0; c < col; ++c) {
                int targetRow = (col * row - 1 - currentIndex) % row;
                int targetCol = (col - 1 - c + (r * col)) % col;
                blockMatrix[targetRow][targetCol] = serie[currentIndex];
                currentIndex++;
            }
        }

        // Convert the blockMatrix back to a linear vector and store it in the blocks vector
        for (int r = 0; r < row; ++r) {
            for (int c = 0; c < col; ++c) {
                currentBlock.push_back(blockMatrix[r][c]);
            }
        }

        blocks.push_back(currentBlock);
    }

    return blocks;
}


