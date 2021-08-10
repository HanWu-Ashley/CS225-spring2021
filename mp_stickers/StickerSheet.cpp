#include "StickerSheet.h"
#include <vector>

void dc2vectors(std::vector<Image *> v1,std::vector<Image *> v2){
    // deep copy v2 to v1
    v1 = std::vector<Image *>(v2.max_size());
    for (unsigned i = 0; i < v2.size(); i++){
        v1[i] = new Image(*v2[i]);
    }
}

StickerSheet::StickerSheet(const Image& picture, unsigned max){
    Image * picture_ = new Image(picture);
    pointers = std::vector<Image*>(max);
}

StickerSheet::~StickerSheet(){
    delete picture_;
    pointers.clear();
    //release(pointers);
}

StickerSheet::StickerSheet(const StickerSheet & other){
    if (this != &other){
        picture_ = new Image(*other.picture_);
        dc2vectors(pointers, other.pointers);
        //release(other);
        //dc2vectors(pointers,other.pointers);
        //release(other.pointers);
    }
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

