#include "ImageProcessor.h"

ImageProcessor::ImageProcessor() {

}

ImageProcessor::~ImageProcessor() {

}


std::string ImageProcessor::decodeHiddenMessage(const ImageMatrix &img) {
    ImageSharpening sharpening=ImageSharpening();
    ImageMatrix sharpedImage=sharpening.sharpen(img,2.0);
    EdgeDetector edge=EdgeDetector();
    edgePixels=edge.detectEdges(sharpedImage);
    DecodeMessage decode=DecodeMessage();
    std::string decodedMessage=decode.decodeFromImage(sharpedImage,edgePixels);
    return decodedMessage;
}

ImageMatrix ImageProcessor::encodeHiddenMessage(const ImageMatrix &img, const std::string &message) {
    EncodeMessage encode=EncodeMessage();
    ImageMatrix encodedImage=encode.encodeMessageToImage(img,message,edgePixels);
    return encodedImage;
}
