/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
#include <vector>

class StickerSheet{
    public:
    StickerSheet(const Image& picture, unsigned max);
    ~StickerSheet();
    StickerSheet(const StickerSheet &other);

    private:
    std::vector<Image*> pointers; //pointers to stickers
    Image* picture_;
};
 
