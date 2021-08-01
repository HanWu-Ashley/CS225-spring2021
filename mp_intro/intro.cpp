#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>

using cs225::HSLAPixel;
using cs225::PNG;

void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  PNG input;
  input.readFromFile(inputFile);
  PNG output=input;
  for (unsigned int x=0; x<input.width(); x++){
    for (unsigned int y=0; y<input.height(); y++){
      HSLAPixel & output_loc = output.getPixel(input.width()-x-1,input.height()-y-1);
      output_loc = input.getPixel(x,y);
    }
  }
  output.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
  for (unsigned int x=0; x<width; x++){
    for (unsigned int y=0; y<height; y++){
      HSLAPixel & p = png.getPixel(x,y);
      p.h = 360*x/width;
      //std::cout<<p.h;
      p.s = 1;//y/height;
      p.l = 0.5;
    }
  }
  return png;
}
