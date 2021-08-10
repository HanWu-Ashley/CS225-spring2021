#include "image.h"
#include <math.h>
using cs225::HSLAPixel;

    void Image::lighten(){
        Image::lighten(0.1);
    }

    void Image::lighten(double amount){
        for (unsigned x=0; x<width(); x++){
            for (unsigned y=0; y<height(); y++){
                HSLAPixel& p = getPixel(x, y);
                p.l = std::min(1.0,p.l+amount);
            }
        }
    }

    void Image::darken(){
        Image::darken(0.1);
    }

    void Image::darken(double amount){
        for (unsigned x=0; x<width(); x++){
            for (unsigned y=0; y<height(); y++){
                HSLAPixel& p = getPixel(x, y);
                p.l = std::max(0.0,p.l-amount);
            }
        }
    }

    void Image::saturate(double amount){
        for (unsigned x=0; x<width(); x++){
            for (unsigned y=0; y<height(); y++){
                HSLAPixel& p = getPixel(x, y);
                p.s = std::min(1.0,p.s+amount);
            }
        }
    }
    
    void Image::saturate(){
       Image::saturate(0.1);
    }

    void Image::desaturate(double amount){
        for (unsigned x=0; x<width(); x++){
            for (unsigned y=0; y<height(); y++){
                HSLAPixel& p = getPixel(x, y);
                p.s = std::max(0.0,p.s-amount);
            }
        }
    }

    void Image::desaturate(){
        Image::desaturate(0.1);
    }

    void Image::grayscale(){
        for (unsigned x=0; x<width(); x++){
            for (unsigned y=0; y<height(); y++){
                HSLAPixel& p = getPixel(x, y);
                p.s = 0;
            }
        }
    }

    void Image::rotateColor(double degrees){
        for (unsigned x=0; x<width(); x++){
            for (unsigned y=0; y<height(); y++){
                HSLAPixel& p = getPixel(x, y);
                p.h += degrees;
                while(p.h>360){
                    p.h -= 360;
                }
                while(p.h<0){
                    p.h += 360;
                }
            }
        }
    }

    void Image::illinify(){
        for (unsigned x = 0; x < width(); x++){
            for (unsigned y = 0; y < height(); y++){
                HSLAPixel & p = getPixel(x, y);
                if (p.h < 113.5 or p.h>293.5){p.h=11;}
                else{p.h=216;}
            }
        }
    }

    void Image::scale(double factor){
        unsigned int newWidth = (int)width()*factor;
        unsigned int newHeight = (int)height()*factor;

        PNG helper_image(*this);
        resize(newWidth, newHeight);
        for (unsigned x = 0; x < newWidth; x++){
            for (unsigned y = 0; y < newHeight; y++){
                HSLAPixel & newPixel = getPixel(x, y);
                HSLAPixel & oldPixel = helper_image.getPixel(floor(x/factor), floor(y/factor));
                newPixel = oldPixel;
            }
        }
    }

    void Image::scale(unsigned w, unsigned h){
        double factor1 = w/width(), factor2 = h/height();
        double factor = std::min(factor1,factor2);
        Image::scale(factor);
    }
