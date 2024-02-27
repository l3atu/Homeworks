// DecodeMessage.cpp

#include "DecodeMessage.h"
#include <iostream>

// Default constructor
DecodeMessage::DecodeMessage() {
    // Nothing specific to initialize here
}

// Destructor
DecodeMessage::~DecodeMessage() {
    // Nothing specific to clean up
}

std::string DecodeMessage::decodeFromImage(const ImageMatrix& image, const std::vector<std::pair<int, int>>& edgePixels) {
    std::string binaryList;
    for (const auto & coordinate : edgePixels) {
        int LSB = static_cast<int>(image.get_data(coordinate.first,coordinate.second))&1;
            binaryList += std::to_string(LSB);
    }

    if(binaryList.length()%7!=0){
        int k= 7-( binaryList.length()%7);
        for (int i = 0; i < k; ++i) {
            binaryList = "0" + binaryList;
        }
    }

    std::string asciiChar;
    for (int i = 0; i < binaryList.length(); i += 7) {
        std::string binarySegment = binaryList.substr(i, 7);
        int decimalValue = std::stoi(binarySegment, nullptr, 2);
        if (decimalValue <= 32) {
            decimalValue += 33;
        } else if (decimalValue == 127) {
            decimalValue = 126;
        }
        asciiChar += static_cast<char>(decimalValue);

    }
    return asciiChar;
}
