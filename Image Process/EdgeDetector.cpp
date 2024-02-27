// EdgeDetector.cpp

#include "EdgeDetector.h"
#include <cmath>

// Default constructor
EdgeDetector::EdgeDetector(){

}

// Destructor
EdgeDetector::~EdgeDetector() {

}

// Detect Edges using the given algorithm
std::vector<std::pair<int, int>> EdgeDetector::detectEdges(const ImageMatrix& input_image) {

    double* Gx[3] = {
            new double[3]{-1.0, 0.0, 1.0},
            new double[3]{-2.0, 0.0, 2.0},
            new double[3]{-1.0, 0.0, 1.0}
    };

    double* Gy[3] = {
            new double[3]{-1.0, -2.0, -1.0},
            new double[3]{0.0, 0.0, 0.0},
            new double[3]{1.0, 2.0, 1.0}
    };

    Convolution myConvo1(Gy, 3, 3, 1, true);
    Convolution myConvo2(Gx, 3, 3, 1, true);

    ImageMatrix Iy = myConvo1.convolve(input_image);
    ImageMatrix Ix = myConvo2.convolve(input_image);
    double num_pixels =  input_image.get_height() * input_image.get_width();
    double sum = 0.0;

    for (int i = 0; i < input_image.get_height(); i++) {
        for (int j = 0; j < input_image.get_width(); j++) {
            double Ix_val = Ix.get_data(i,j);
            double Iy_val = Iy.get_data(i,j);
            double G_val = sqrt(Ix_val * Ix_val + Iy_val * Iy_val);

            sum += G_val;
        }
    }
    double threshold = sum / num_pixels;

    for (int i = 0; i < input_image.get_height(); i++) {
        for (int j = 0; j < input_image.get_width(); j++) {
            double Ix_val = Ix.get_data(i, j);
            double Iy_val = Iy.get_data(i, j);
            double G = sqrt(Ix_val * Ix_val + Iy_val * Iy_val);

            if (G > threshold) {
                edgePixels.emplace_back(i, j);
            }
        }
    }
    return edgePixels;
}
