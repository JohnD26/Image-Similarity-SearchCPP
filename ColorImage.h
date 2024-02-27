#ifndef COLORIMAGE_H
#define COLORIMAGE_H

#include <string>
#include <vector>

class ColorImage {
public:
    int width;
    int height;
    int depth;

private:
    std::string name;
    std::vector<std::vector<std::vector<int>>> imageMatrix;
    std::vector<std::vector<std::vector<int>>> reducedColorMatrix;

    void skipHeaderLines(std::ifstream& file, int numLines);

public:
    explicit ColorImage(const std::string& filename);

    std::vector<int> getPixel(int i, int j) const;
    void reduceColor(int d);
    std::vector<int> getReducedPixel(int i, int j) const;
    void loadImageMatrix();

    int getWidth() const;
    int getHeight() const;
    int getDepth() const;
    std::string getFileNameUsed() const;

    // Functions implemented in cpp
    int findWidth(const std::string& filename);
    int findHeight(const std::string& filename);
    int findMaxValue(const std::string& filename);
    int FindBitsPerChannel(const std::string& filename);
    int findBitsPerPixel(const std::string& filename);

};

#endif // COLORIMAGE_H
