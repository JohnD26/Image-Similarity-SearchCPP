#include "ColorImage.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

ColorImage::ColorImage(const std::string& filename) : name(filename), width(findWidth(filename)), height(findHeight(filename)), depth(findBitsPerPixel(filename)) {
    imageMatrix.resize(height, std::vector<std::vector<int>>(width, std::vector<int>(3)));
    loadImageMatrix(); //Method used to read the image right after initialisation
}

std::vector<int> ColorImage::getPixel(int i, int j) const {
    if (i < 0 || i >= height || j < 0 || j >= width) {
        throw std::out_of_range("Invalid pixel coordinates");
    }
    return imageMatrix[i][j];
}

void ColorImage::reduceColor(int d) {
    reducedColorMatrix = imageMatrix; // Copying the original Matrix

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            for (int k = 0; k < 3; ++k) {
                reducedColorMatrix[i][j][k] >>= (8 - d);
            }
        }
    }
}

std::vector<int> ColorImage::getReducedPixel(int i, int j) const {
    if (i < 0 || i >= height || j < 0 || j >= width) {
        throw std::out_of_range("Invalid pixel coordinates");
    }
    if (reducedColorMatrix.empty()) {
        throw std::logic_error("Reduced color matrix has not been initialized.");
    }
    return reducedColorMatrix[i][j];
}

void ColorImage::loadImageMatrix() {
    std::ifstream file(name);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + name);
    }

    // Skip header lines
    std::string line;
    std::getline(file, line); // P3 header
    std::getline(file, line); // Comment
    std::getline(file, line); // Dimensions
    std::getline(file, line); // Max color value

    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            int r, g, b;
            if (!(file >> r >> g >> b)) {
                throw std::runtime_error("Error reading pixel data");
            }
            imageMatrix[row][col] = {r, g, b};
        }
    }
}



int ColorImage::findWidth(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + filename);
    }

    std::string line;
    std::getline(file, line); // Skip P3 header
    std::getline(file, line); // Skip comment
    std::getline(file, line); // Dimensions line
    std::istringstream iss(line);
    int width, height;
    if (!(iss >> width >> height)) {
        throw std::runtime_error("Error reading size of matrix");
    }
    return width;
}

int ColorImage::getWidth() const {
    return width;
}

int ColorImage::getHeight() const {
    return height;
}

int ColorImage::getDepth() const {
    return depth;
}

std::string ColorImage::getFileNameUsed() const {
    return name;
}

int ColorImage::findHeight(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + filename);
    }

    std::string line;
    std::getline(file, line); // Skip P3 header
    std::getline(file, line); // Skip comment
    std::getline(file, line); // Dimensions line
    std::istringstream iss(line);
    int width, height;
    if (!(iss >> width >> height)) {
        throw std::runtime_error("Error reading dimensions");
    }
    return height;
}


int ColorImage::findMaxValue(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + filename);
    }

    skipHeaderLines(file, 3); // Skip P3 header, comment, dimensions

    int maxValue;
    file >> maxValue;
    return maxValue;
}

int ColorImage::FindBitsPerChannel(const std::string& filename) {
    int maxValue = findMaxValue(filename);
    int power = 0;
    while ((1 << power) <= maxValue) {
        ++power;
    }
    return power;
}

int ColorImage::findBitsPerPixel(const std::string& filename) {
    return FindBitsPerChannel(filename) * 3;
}

//Helper Method to avoid hardcoding
void ColorImage::skipHeaderLines(std::ifstream& file, int numLines) {
    std::string line;
    for (int i = 0; i < numLines; ++i) {
        std::getline(file, line);
    }
}
