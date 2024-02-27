#include "EncodeMessage.h"
#include <cmath>
#include <bitset>


// Default Constructor
EncodeMessage::EncodeMessage() {

}

// Destructor
EncodeMessage::~EncodeMessage() {

}

std::vector<int> calculateFibonacci(int n) {
    std::vector<int> fibonacciNumbers;
    if (n >= 1) {
        fibonacciNumbers.push_back(0);
    }
    if (n >= 2) {
        fibonacciNumbers.push_back(1);
    }
    for (int i = 2; i < n; i++) {
        int nextFibonacci = fibonacciNumbers[i - 1] + fibonacciNumbers[i - 2];
        fibonacciNumbers.push_back(nextFibonacci);
    }
    return fibonacciNumbers;
}
bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    if (n <= 3) {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

std::string rightCircularShift(const std::string& message, int shiftAmount) {
    if (message.empty()) {
        return message;
    }

    int len = message.length();
    shiftAmount = shiftAmount % len;

    std::string shiftedMessage = message.substr(len - shiftAmount) + message.substr(0, len - shiftAmount);

    return shiftedMessage;
}

// Function to encode a message into an image matrix
ImageMatrix EncodeMessage::encodeMessageToImage(const ImageMatrix &img, const std::string &message, const std::vector<std::pair<int, int>>& positions) {
    std::string decimalMessage;
    for (char c : message) {
        int decimalValue = static_cast<int>(c);
        decimalMessage.push_back(static_cast<char>(decimalValue));
    }

    std::vector<int> fibonacciNumbers = calculateFibonacci(decimalMessage.size());

    for(int i=0; i<decimalMessage.size();i++){
        decimalMessage[i]=static_cast<int>(decimalMessage[i]);
        if(isPrime(i)){
            decimalMessage[i]= decimalMessage[i]+ fibonacciNumbers[i-1];
        }
        if (decimalMessage[i] <= 32) {
            decimalMessage[i] += 33;
        } else if (decimalMessage[i] == 127) {
            decimalMessage[i] = 126;
        }
    }

    int shiftAmount=decimalMessage.length()/2;
    decimalMessage= rightCircularShift(decimalMessage,shiftAmount);

    std::string binaryMessage;

    for (char decimalValue: decimalMessage) {
        std::bitset<7> binary(static_cast<int>(decimalValue));
        binaryMessage += binary.to_string();
    }

    size_t binaryIndex = 0;

    for (const std::pair<int, int>& coordinate : positions) {
        if (binaryIndex < binaryMessage.length()) {
            const char binaryValue = binaryMessage[binaryIndex];
            int data = static_cast<int>(img.get_data(coordinate.first, coordinate.second));
            int LSB = data % 2;

            if (LSB != (binaryValue - '0')) {

                data += (binaryValue - '0') - LSB;
                img.setData(coordinate.first, coordinate.second, data);
            }
            ++binaryIndex;
        }
    }

return img;

}
