#include <iostream>
#include <cstring>
#include "Leap.h"
#include <fstream>

using namespace Leap;

int main(int argc, char** argv) {
    Leap::Controller controller;
    std::vector<Leap::Frame> deserializedFrames;
    std::string inFilename = "frames.data";
    std::ifstream in(inFilename, std::fstream::in);
    std::string contents;
    if (in)
    {
        in.seekg(0, std::ios::beg);
        long nextBlockSize = 0;
        in >> nextBlockSize;
        while (!in.eof())
        {
            contents.resize(nextBlockSize);
            in.read(&contents[0], nextBlockSize);
            Leap::Frame newFrame;
            newFrame.deserialize(contents);
            if(newFrame.isValid()) deserializedFrames.push_back(newFrame);
            in >> nextBlockSize;
        }
        in.close();
    }
    else if(errno){
        std::cout << "Error: " << errno << std::endl;
        std::cout << "Couldn't open " << inFilename << " for reading." << std::endl;
    }
    std::cout<<deserializedFrames.size()<<std::endl;
    for(int i = 0; i<deserializedFrames.size(); i++){
        std::cout<<deserializedFrames[i].id()<<std::endl;
    }
}