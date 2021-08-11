#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  
  Image a, sticker;
  a.readFromFile("z.png");
  sticker.readFromFile("i.png");
  StickerSheet sheet(a,3);
  sheet.addSticker(sticker, 20, 20);
  Image result=sheet.render();
  result.writeToFile("myImage.png");

  return 0;
}
