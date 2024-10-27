# Image Similarity Search in C++

Image Similarity Search is a C++ program that identifies the top 5 most similar images to a given query image from a dataset using color histogram comparison with a 3-bit color reduction technique. This project demonstrates image similarity search by analyzing and comparing the color content of images.

## Table of Contents
- [Features](#features)
- [Folder Structure](#folder-structure)
- [Requirements](#requirements)
- [Installation and Compilation](#installation-and-compilation)
- [Usage](#usage)
- [Example](#example)
- [Sample Output](#sample-output)
- [Visual Verification](#visual-verification)
- [Notes](#notes)
- [Troubleshooting](#troubleshooting)
- [License](#license)
- [Acknowledgements](#acknowledgements)
- [Contact](#contact)

## Features
- **Color Histogram Comparison**: Compares images using color histograms.
- **3-bit Color Reduction**: Reduces image colors to 3 bits for efficient processing.
- **Top 5 Similar Images**: Outputs the top 5 images similar to the query image.
- **Organized Structure**: Source code and images are organized in separate directories.

## Folder Structure
- **Src/**: Contains all C++ source files.
- **Query/**: Contains query images.
- **Dataset/**: Contains the dataset images and corresponding histogram `.txt` files.
- **Screenshots/**: Contains images used in the README for demonstration purposes.

## Requirements
- **Operating System**: Windows
- **Compiler**: g++ (supporting C++17 standard)
- **Libraries**: Standard C++ libraries including `<filesystem>`, `<vector>`, `<map>`, `<algorithm>`, `<string>`, `<iostream>`, `<fstream>`
- **Tools**: Command Prompt or PowerShell

## Installation and Compilation

1. **Clone the Repository**
   ```bash
   git clone https://github.com/yourusername/Image-Similarity-SearchCPP.git
   ```

2. **Navigate to the Src Directory**  
   Open Command Prompt or PowerShell and navigate to the `Src` folder:
   ```bash
   cd Image-Similarity-SearchCPP/Src
   ```

3. **Compile the Program**
   ```bash
   g++ -std=c++17 -o SimilaritySearch SimilaritySearch.cpp ColorImage.cpp ColorHistogram.cpp -lstdc++fs
   ```
   This command creates an executable named `SimilaritySearch.exe` in the `Src` directory.

## Usage
Run the program by specifying the query image filename (located in the `Query` folder) and the dataset directory.

### Command Syntax
```bash
.\SimilaritySearch.exe <queryImageFilename> <datasetDirectory>
```
- `<queryImageFilename>`: The name of the query image file (e.g., `q00.jpg`).
- `<datasetDirectory>`: The path to the dataset directory relative to the `Src` directory (e.g., `../imageDataset2_15_20`).

### Important Notes
- The program expects the query image to be in the `Query` directory.
- The dataset directory should contain histogram `.txt` files for each image.

## Example

### Running the Program with `q00.jpg`
1. **Ensure the Query Image Exists**  
   Confirm that `q00.jpg` is in the `Query` directory.

2. **Run the Program**  
   From the `Src` directory, execute:
   ```bash
   .\SimilaritySearch.exe q00.jpg ..\imageDataset2_15_200
   ```

### Understanding the Paths
- `q00.jpg` is located in `..\Query\q00.jpg` (the program adds the `..\Query\` path internally).
- `../imageDataset2_15_20` points to the dataset directory one level up from `Src`.

## Sample Output
After running the program, you should see output similar to:

```
Top 5 similar images:
1144.jpg.txt - Score: 1
3806.jpg.txt - Score: 0.707454
3714.jpg.txt - Score: 0.668432
3756.jpg.txt - Score: 0.662025
2462.jpg.txt - Score: 0.649103
```
The scores represent the similarity between the query image and each dataset image. A score of 1 indicates an exact match in terms of color histogram.

## Visual Verification
To confirm the effectiveness of the similarity search:

- **Query Image**: `q00.jpg`
- **Most Similar Image**: `1144.jpg` (With a similarity of 100%)

### Screenshot
Below is a screenshot of q00.jpg from the list of Query Images:

<img width="784" alt="Query Image0" src="https://github.com/user-attachments/assets/336510d0-ef4b-4b2c-8c72-2bd920f9ea4f">

Below is a screenshot of Image 1144.jpg from the Database of Images:
<img width="790" alt="Image 1144 from database" src="https://github.com/user-attachments/assets/7a3c699f-488c-4ca3-bd81-17f4f74f1720">

As we can see the images are identical. From our pixel reduction algorithm, we managed to find the image from the database of images while using as comparison the query image. The algorithm proved to be successful as demonstrated above.

## Notes
- Ensure all images in the dataset have corresponding 
histogram `.txt` files.
- Adjustments to color depth can affect search performance.

## Troubleshooting
- If compilation fails, verify that all required libraries and paths are correctly set.
- For missing libraries, ensure `g++` is updated to a version supporting C++17.



## Acknowledgements
- Many thanks to Prof. Robert Laganiere for this great project idea.


```


