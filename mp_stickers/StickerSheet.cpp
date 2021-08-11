#include "StickerSheet.h"
#include "Image.h"
#include <vector>
using std::vector;
using std::cout;
using std::endl;

void StickerSheet::clear(){
    delete picture_;
    x_array.clear();
    y_array.clear();
    for (unsigned int i=0; i<valid_stickers; i++){
        delete pointers[i];
    }
    pointers.clear();
}

void StickerSheet::copy(const StickerSheet& other){
    picture_ = new Image(*other.picture_);

    //deep copy pointers
    pointers = vector<Image *>(other.max_stickers);
    for (unsigned int i=0; i<other.valid_stickers; i++){
        pointers[i] = new Image(*other.pointers[i]);
    }

    x_array = vector<unsigned int>(other.x_array);
    y_array = vector<unsigned int>(other.y_array);
    valid_stickers = other.valid_stickers;
    max_stickers = other.max_stickers;
}

StickerSheet::StickerSheet(const Image& picture, unsigned max){
    picture_ = new Image(picture);
    pointers = vector<Image*>(max);
    x_array = vector<unsigned int>(max);
    y_array = vector<unsigned int>(max);
    valid_stickers = 0;
    max_stickers = max;
}

StickerSheet::~StickerSheet(){
    clear();
}

StickerSheet::StickerSheet(const StickerSheet & other){
    if (this != &other){
        copy(other);
    }
}

const StickerSheet & StickerSheet::operator= (const StickerSheet &other){
    if (this != &other){
        clear();
        copy(other);
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max){
    if (max < valid_stickers){
        valid_stickers = max;
        
    }
    else {
    pointers.resize(max,NULL);
    x_array.resize(max,-1);
    y_array.resize(max,-1);
    }
    max_stickers = max;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
    if (valid_stickers==max_stickers){
        return -1;
    }
    if (x>=(*picture_).width() || y>=(*picture_).height()){
        return -1;
    }
    pointers[valid_stickers] = new Image(sticker);
    x_array[valid_stickers] = x;
    y_array[valid_stickers] = y;
    valid_stickers++;
    return valid_stickers-1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
    //if invalid
    if (index>=valid_stickers){
        return false;
    }
    x_array[index] = x;
    y_array[index] = y;
    return true; 
}


void StickerSheet::removeSticker(unsigned index){
    pointers.erase(pointers.begin()+index);
    x_array.erase(x_array.begin()+index);
    y_array.erase(y_array.begin()+index);
    valid_stickers--;
}

Image * StickerSheet::getSticker(unsigned index){
    //if invalid
    if (index>=valid_stickers){
        return NULL;
    }
    return pointers[index];
}

Image StickerSheet::render() const{
    Image result = *picture_;

    for (unsigned int i=0; i<valid_stickers; i++){
        Image sticker = *pointers[i];
        unsigned int x=x_array[i], y=y_array[i];

        //enlarge result if the sticker go beyond the edge of result
        unsigned int newWidth = x+sticker.width(), newHeight = y+sticker.height();
    
        if (result.width() < newWidth || result.height() < newHeight){
            newWidth = std::max(result.width(),newWidth);
            newHeight = std::max(result.height(),newHeight);
            result.resize(newWidth,newHeight);
            /**
            Image * resized_result = new Image(result);
            
            (*resized_result).resize(newWidth, newHeight);
            for (unsigned m=0; m<newWidth; m++){
                for (unsigned n=0; n<newHeight; n++){
                    if (m<result.width() && n<result.height()){
                        HSLAPixel & old_ = result.getPixel(m, n);
                        HSLAPixel & new_ = resized_result->getPixel(m, n);
                        new_ = old_;
                    }
                    else{
                        HSLAPixel old_;
                        HSLAPixel & new_ = resized_result->getPixel(m, n);
                        new_ = old_;
                    }
                }
            }
            Image * new_pic = new Image(*resized_result);
            result = *new_pic;
            **/
        }

        for (unsigned int j=0; j<sticker.width(); j++){
            for (unsigned int k=0; k<sticker.height(); k++){
                HSLAPixel & p_s = sticker.getPixel(j, k);
                if (p_s.a==0) {continue;}
                else{
                    HSLAPixel & p_r = result.getPixel(x+j, y+k);
                    p_r = p_s;
                }
            }
        }

    }
    return result;
}

/**
void release(StickerSheet & s){
    delete s.picture_;
    s.pointers.clear();
}


void release(std::vector<Image *> pointers){
    std::vector<Image*>::iterator it;
    for (it = pointers.begin(); it != pointers.end(); it++){
        delete *it;
    }
}
**/

