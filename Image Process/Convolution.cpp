#include <iostream>
#include "Convolution.h"



// Default constructor
Convolution::Convolution(): Kernel(nullptr), kernelHeight(0), kernelWidth(0), stride(1), pad_value(true) {

}

// Parametrized constructor for custom kernel and other parameters
Convolution::Convolution(double** customKernel, int kh, int kw, int stride_val, bool pad){
    kernelHeight=kh;
    kernelWidth=kw;
    pad_value=pad;
    stride=stride_val;
    Kernel = new double*[kh];
    for (int i = 0; i < kh; i++) {
        this->Kernel[i] = new double[kw];
        for (int j = 0; j < kw; j++) {
            Kernel[i][j] = customKernel[i][j];
        }
    }
}

// Destructor
Convolution::~Convolution() {
    if (Kernel != nullptr) {
        for (int i = 0; i < kernelHeight; i++) {
            delete[] Kernel[i];
        }
        delete[] Kernel;
    }
}

// Copy constructor
Convolution::Convolution(const Convolution &other){
    kernelHeight = other.kernelHeight;
    kernelWidth = other.kernelWidth;
    stride = other.stride;
    pad_value = other.pad_value;

    Kernel = new double*[kernelHeight];
    for (int i = 0; i < kernelHeight; i++) {
        Kernel[i] = new double[kernelWidth];
        for (int j = 0; j < kernelWidth; j++) {
            Kernel[i][j] = other.Kernel[i][j];
        }
    }
}

// Copy assignment operator
Convolution& Convolution::operator=(const Convolution &other) {
    if (this == &other) {
        return *this;
    }

    if(Kernel!= nullptr) {
        for (int i = 0; i < kernelHeight; i++) {
            delete[] Kernel[i];
        }
        delete[] Kernel;
    }

    kernelHeight = other.kernelHeight;
    kernelWidth = other.kernelWidth;
    stride = other.stride;
    pad_value= other.pad_value;
    Kernel = new double*[kernelHeight];
    for (int i = 0; i < kernelHeight; i++) {
        Kernel[i] = new double[kernelWidth];
        for (int j = 0; j < kernelWidth; j++) {
            Kernel[i][j] = other.Kernel[i][j];
        }
    }

    return *this;
}

ImageMatrix Convolution::padding(const ImageMatrix& input_image) const{
    int outputWidth = input_image.get_width() +2;
    int outputHeight = input_image.get_height() +2;
    ImageMatrix padded_image(outputHeight,outputWidth);
    if(pad_value) {

        for (int i = 1; i < outputHeight - 1; i++) {
            for (int j = 1; j < outputWidth - 1; j++) {
                padded_image.setData(i,j,input_image.get_data(i-1,j-1)) ;
            }
        }

        for (int i = 0; i < outputHeight; i++) {
            padded_image.setData(i,0,0.0);
            padded_image.setData(i,outputWidth - 1,0.0);
        }
        for (int j = 0; j < outputWidth; j++) {
            padded_image.setData(0,j,0.0);
            padded_image.setData(outputHeight - 1,j,0.0);
        }
        return padded_image;
    }

    else{
        return input_image;
    }
}


// Convolve Function: Responsible for convolving the input image with a kernel and return the convolved image.
ImageMatrix Convolution::convolve(const ImageMatrix& input_image) const {
    ImageMatrix paddedMatrix= padding(input_image);
    int outputHeight = ( paddedMatrix.get_height() - kernelHeight) / stride + 1;
    int outputWidth = (paddedMatrix.get_width() - kernelWidth) / stride + 1;


    ImageMatrix convolvedImage(outputHeight, outputWidth);

    for (int i = 0; i < outputHeight; i++) {
        for (int j = 0; j < outputWidth; j++) {
            double sum = 0.0;
            for (int m = 0; m < kernelHeight; m++) {
                for (int n = 0; n < kernelWidth; n++) {
                    int inputRow = i * stride + m;
                    int inputCol = j * stride + n;
                    sum += paddedMatrix.get_data(inputRow, inputCol) * Kernel[m][n];
                }
            }
            convolvedImage.setData(i, j, sum);
        }
    }

    return convolvedImage;
}