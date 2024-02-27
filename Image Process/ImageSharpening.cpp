#include "ImageSharpening.h"

// Default constructor
ImageSharpening::ImageSharpening() {

}

ImageSharpening::~ImageSharpening(){

}

ImageMatrix ImageSharpening::sharpen(const ImageMatrix& input_image, double k) {
    double* blurring_kernel[3] = {
            new double[3]{1.0/9, 1.0/9, 1.0/9},
            new double[3]{1.0/9, 1.0/9, 1.0/9},
            new double[3]{1.0/9, 1.0/9, 1.0/9}
    };
    Convolution myConvo=Convolution(blurring_kernel,3,3,1,true);
    ImageMatrix blurred_image=myConvo.convolve(input_image);

    ImageMatrix sharpen_image=input_image.operator+((input_image.operator-(blurred_image)).operator*(k));
    for (int i = 0; i < sharpen_image.get_height(); i++) {
        for (int j = 0; j < sharpen_image.get_width(); j++) {
            if (sharpen_image.get_data(i, j) > 255) {
                sharpen_image.setData(i, j, 255);
            } else if (sharpen_image.get_data(i,j) < 0) {
                sharpen_image.setData(i,j,0);
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        delete[] blurring_kernel[i];
    }

    return sharpen_image;
}
