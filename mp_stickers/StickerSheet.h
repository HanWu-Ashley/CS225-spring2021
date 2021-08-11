/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
#include <vector>
using std::vector;

class StickerSheet{
    public:
    StickerSheet(const Image& picture, unsigned max);
    ~StickerSheet();
    StickerSheet(const StickerSheet &other);

    const StickerSheet & operator= (const StickerSheet &other);
    void changeMaxStickers(unsigned max);
    int addSticker(Image &sticker, unsigned x, unsigned y);
    bool translate(unsigned index, unsigned x, unsigned y);
    void removeSticker(unsigned index);
    Image * getSticker(unsigned index);	
    Image render() const;
    //helper function
    void clear();
    void copy(const StickerSheet& other);

    private:
    vector<Image*> pointers; //pointers to stickers
    Image* picture_;
    vector<unsigned int> x_array;
    vector<unsigned int>  y_array;
    unsigned valid_stickers;
    unsigned max_stickers;
};
 
