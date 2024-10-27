#ifndef COLORHISTOGRAM_H
#define COLORHISTOGRAM_H

#include <string>
#include <vector>
#include "ColorImage.h"

class ColorHistogram {
private:
    int dBits;
    ColorImage* image; // Pointer pointing to  ColorImage object
    std::vector<double> histogram;
    int totalPixels;

public:
    explicit ColorHistogram(int d); // Constructor for d-bit images
    explicit ColorHistogram(const std::string& filename); // Constructor to load histogram from a file

    void setImage(ColorImage& img); // Associate an image with this histogram
    void computeHistogram(); // Compute the histogram
    std::vector<double> getHistogram() const; // Get the normalized histogram of the image
    void normalizeBaseHistogram(); // Normalize the histogram
    double compare(const ColorHistogram& hist) const; // Compare with another histogram

    void saveColorHistogram(const std::string& filename) const; // Save the histogram to a file

private:
    void loadHistogramFromFile(const std::string& filename); // Helper method to load histogram from file
};

#endif // COLORHISTOGRAM_H
