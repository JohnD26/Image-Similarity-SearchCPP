#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <filesystem>
#include "ColorImage.h"      
#include "ColorHistogram.h"  

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage: SimilaritySearch <queryImageFilename> <datasetDirectory>" << std::endl;
        return 1;
    }

    // Adjusted to look for the Query directory in the parent directory
    std::string queryImageFilename = "../Query/" + std::string(argv[1]);
    std::string datasetDirectory = argv[2];

    // Convert .jpg to .ppm if necessary
    if (queryImageFilename.find(".jpg") != std::string::npos) {
        queryImageFilename.replace(queryImageFilename.end() - 4, queryImageFilename.end(), ".ppm");
    }

    try {
        ColorImage queryImage(queryImageFilename);
        queryImage.reduceColor(3);

        ColorHistogram queryHistogram(3);
        queryHistogram.setImage(queryImage);
        queryHistogram.computeHistogram();

        std::vector<std::string> listOfFiles;

        // Check if the dataset directory exists and is a directory
        if (fs::exists(datasetDirectory) && fs::is_directory(datasetDirectory)) {
            for (const auto& entry : fs::directory_iterator(datasetDirectory)) {
                if (entry.is_regular_file()) {
                    listOfFiles.push_back(entry.path().filename().string());
                }
            }
        } else {
            std::cerr << "Dataset directory does not exist or is not a directory." << std::endl;
            return 1;
        }

        // Map to store image filenames and their similarity scores
        std::map<std::string, double> similarityScores;

        for (const auto& filename : listOfFiles) {
            if (filename.find(".txt") != std::string::npos) {
                ColorHistogram datasetHistogram(datasetDirectory + "/" + filename);
                datasetHistogram.normalizeBaseHistogram();

                double score = queryHistogram.compare(datasetHistogram);
                similarityScores.insert({filename, score});
            }
        }

        // Sorting results
        std::vector<std::pair<std::string, double>> sortedScores(similarityScores.begin(), similarityScores.end());
        std::sort(sortedScores.begin(), sortedScores.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

        // Output the top 5 similar images
        std::cout << "Top 5 similar images:" << std::endl;
        for (size_t i = 0; i < std::min(static_cast<size_t>(5), sortedScores.size()); ++i) {
            std::cout << sortedScores[i].first << " - Score: " << sortedScores[i].second << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
