#include "../../CImg/CImg.h"
#include "../headers/proc.h"

void CopyCImgToPhotoObject(cimg_library::CImg<unsigned char> & CImgPicture, Photo & photo){
    for(int currentChannel = 0; currentChannel < photo.GetChannelAmount(); currentChannel++){
        Channel newChannel(photo.GetWidth(),photo.GetHeight());
        for(int x=0; x<photo.GetWidth(); x++){
            for(int y=0; y<photo.GetHeight(); y++){
                int pixelValue = static_cast<int>(CImgPicture(x,y,0,currentChannel));
                newChannel.SetValue(x,y,pixelValue);
            }
        }
        photo.SetChannel(currentChannel,newChannel);
    }
}

void CopyPhotoObjectToCImg(Photo & photo, cimg_library::CImg<unsigned char> & CImgPicture){
    unsigned char color[photo.GetWidth()][photo.GetHeight()][3];

    for(int currentChannelID = 0; currentChannelID < photo.GetChannelAmount(); currentChannelID++){
        Channel currentChannel = photo.GetChannel(currentChannelID);
        for(int x=0; x<photo.GetWidth(); x++){
            for(int y=0; y<photo.GetHeight(); y++){
                color[x][y][currentChannelID] = currentChannel.GetValue(x,y);
            }
        }
    }

    for(int x=0; x<photo.GetWidth(); x++)
        for(int y=0; y<photo.GetHeight(); y++)
            CImgPicture.draw_point(x,y,0,color[x][y]);
}

void DisplayImage(cimg_library::CImg<unsigned char> & imageToDisplay){
    cimg_library::CImgDisplay displayWindow(imageToDisplay);
    while (!displayWindow.is_closed()) {
        displayWindow.wait();
    }
}

void DisplayHistogram(std::vector<float> hist){
    cimg_library::CImg<unsigned char> histogramImage(255, 255, 1, 1, 0);
    unsigned char grayColor[3] = {128, 128, 128};
    for(int x = 0; x < 255; x++){
        histogramImage.draw_line(x, 255 - static_cast<int>(hist[x]*255*50), x, 255, grayColor);
    }
    cimg_library::CImgDisplay displayWindow(histogramImage);
    while (!displayWindow.is_closed()) {
        displayWindow.wait();
    }
    histogramImage.save("output/histogram.bmp");
}
