#include "ImageMatrix.h"
#include <iostream>


// Default constructor
ImageMatrix::ImageMatrix(): height(0), width(0), imageMatrix(nullptr){
    
}


// Parameterized constructor for creating a blank image of given size
ImageMatrix::ImageMatrix(int imgHeight, int imgWidth) : height(imgHeight), width(imgWidth) {
    imageMatrix = new double*[height];
    for (int i = 0; i < height; i++) {
        imageMatrix[i] = new double[width];
    }

}

// Parameterized constructor for loading image from file. PROVIDED FOR YOUR CONVENIENCE
ImageMatrix::ImageMatrix(const std::string &filepath) {
    // Create an ImageLoader object and load the image
    ImageLoader imageLoader(filepath);

    // Get the dimensions of the loaded image
    height = imageLoader.getHeight();
    width = imageLoader.getWidth();

    // Allocate memory for the matrix
    data = new double*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
    }

    // Copy data from imageLoader to data
    double** imageData = imageLoader.getImageData();
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; j++) {
            data[i][j] = imageData[i][j];
        }
    }
}



// Destructor
ImageMatrix::~ImageMatrix() {
    if (imageMatrix != nullptr) {
        for (int i = 0; i < height; i++) {
            delete[] imageMatrix[i];
        }
        delete[] imageMatrix;
    }

}

// Parameterized constructor - direct initialization with 2D matrix
ImageMatrix::ImageMatrix(const double** inputMatrix, int imgHeight, int imgWidth){
    this->height=imgHeight;
    this->width=imgWidth;
    imageMatrix = new double*[imgHeight];
    for (int i = 0; i < imgHeight; i++) {
        imageMatrix[i] = new double[imgWidth];
        for (int j = 0; j < imgWidth; j++) {
            imageMatrix[i][j] = inputMatrix[i][j];
        }
    }
}

// Copy constructor
ImageMatrix::ImageMatrix(const ImageMatrix &other) : height(other.height), width(other.width) {
    imageMatrix = new double*[height];
    for (int i = 0; i < height; i++) {
        imageMatrix[i] = new double[width];
        for (int j = 0; j < width; j++) {
            imageMatrix[i][j] = other.imageMatrix[i][j];
        }
    }
}

// Copy assignment operator
ImageMatrix& ImageMatrix::operator=(const ImageMatrix &other) {
     if (this == &other) {
        return *this; 
    }

    if (imageMatrix != nullptr) {
        for (int i = 0; i < height; i++) {
            delete[] imageMatrix[i];
        }

        delete[] imageMatrix;
    }


    height = other.height;
    width = other.width;
    imageMatrix = new double*[height];
    for (int i = 0; i < height; i++) {
        imageMatrix[i] = new double[width];
        for (int j = 0; j < width; j++) {
            imageMatrix[i][j] = other.imageMatrix[i][j];
        }
    }

    return *this;
    
}



// Overloaded operators

// Overloaded operator + to add two matrices
ImageMatrix ImageMatrix::operator+(const ImageMatrix &other) const {
       if (height != other.height || width != other.width) {

        throw std::runtime_error("The dimensions of the matrices do not match.");
    }
    ImageMatrix result(height, width);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            result.setData(i, j, this->get_data(i, j) + other.get_data(i, j));
        }
    }

    return result;
}

// Overloaded operator - to subtract two matrices
ImageMatrix ImageMatrix::operator-(const ImageMatrix &other) const {
    if (height != other.height || width != other.width) {
        throw std::runtime_error("The dimensions of the matrices do not match.");
    }

    ImageMatrix result(height, width);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            result.setData(i, j, this->get_data(i, j) - other.get_data(i, j));
        }
    }

    return result;

}

// Overloaded operator * to multiply a matrix with a scalar
ImageMatrix ImageMatrix::operator*(const double &scalar) const {
     ImageMatrix result(height, width);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            result.setData(i, j, this->get_data(i, j) * scalar);
        }
    }

    return result;

}

int ImageMatrix::get_height() const{
    return height;
}
int ImageMatrix::get_width() const{
    return width;
}
// Getter function to access the data in the matrix
double** ImageMatrix::get_data() const {
    return imageMatrix;
}

// Getter function to access the data at the index (i, j)
double ImageMatrix::get_data(int i, int j) const {
    return imageMatrix[i][j];
}
void ImageMatrix::setData(int i, int j, double value) const {
    if (i >= 0 && i < height && j >= 0 && j < width) {
        imageMatrix[i][j] = value;
    } else {

    }
}

void ImageMatrix::printFunction() {
    for(int i =0; i<height; i++){
        for(int j=0; j< width; j++){
           std::cout << imageMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
