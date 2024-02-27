#include "ColorHistogram.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <complex>

ColorHistogram::ColorHistogram(int d) : dBits(d), image(nullptr), totalPixels(0) {}

ColorHistogram::ColorHistogram(const std::string& filename) {
    loadHistogramFromFile(filename);
}

void ColorHistogram::setImage(ColorImage& img) {
    image = &img;
    totalPixels = img.getWidth() * img.getHeight();
}

void ColorHistogram::computeHistogram() {
    histogram.assign(static_cast<size_t>(std::pow(2, dBits * 3)), 0.0);

    for (int i = 0; i < image->getHeight(); ++i) {
        for (int j = 0; j < image->getWidth(); ++j) {
            std::vector<int> pixel = image->getReducedPixel(i, j);
            int index = (pixel[0] << (2 * dBits)) + (pixel[1] << dBits) + pixel[2];
            histogram[index]++;
        }
    }

    normalizeBaseHistogram();
}

std::vector<double> ColorHistogram::getHistogram() const {
    return histogram;
}

void ColorHistogram::normalizeBaseHistogram() {
    double sum = std::accumulate(histogram.begin(), histogram.end(), 0.0);
    if (sum != 0) {
        std::transform(histogram.begin(), histogram.end(), histogram.begin(),
                       [sum](double value) { return value / sum; });
    }
}

double ColorHistogram::compare(const ColorHistogram& hist) const {
    double intersection = 0.0;
    for (size_t i = 0; i < histogram.size(); ++i) {
        intersection += std::min(histogram[i], hist.histogram[i]);
    }
    return intersection;
}

void ColorHistogram::saveColorHistogram(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + filename);
    }

    for (double value : histogram) {
        file << value << " ";
    }
    file << std::endl;
}

void ColorHistogram::loadHistogramFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + filename);
    }

    std::string line;
    std::getline(file, line); // Skip the first line

    histogram.clear();
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        double value;
        while (iss >> value) {
            histogram.push_back(value);
        }
    }

    normalizeBaseHistogram();
}
