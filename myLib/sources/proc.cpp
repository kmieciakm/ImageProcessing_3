#include "../headers/proc.h"

Channel::Channel(int _width, int _height){
    this->width = _width;
    this->height = _height;
    this->fill.resize(_width);
    for(int i=0; i<_width; i++)
        this->fill[i].resize(_height);
}

Channel::Channel(){
    this->width = 0;
    this->height = 0;
}

void Channel::SetValue(int _x, int _y, int _value){
    if(_value > 255)
        this->fill[_x][_y] = 255;
    else if(_value <0)
        this->fill[_x][_y] = 0;
    else
        this->fill[_x][_y] = _value;
}

int Channel::GetValue(int _x, int _y){
    return this->fill[_x][_y];
}

int Channel::GetWidth(){
    return this->width;
}

int Channel::GetHeight(){
    return this->height;
}

void Channel::CalculateHistogram(){
    this->histogram.resize(255);
    for(int x = 0; x < this->width; x++){
        for(int y = 0; y < this->height; y++){
            int currentPixelValue = this->fill[x][y];
            this->histogram[currentPixelValue]++;
        }
    }
    for(int value = 0; value < 255; value++){
        this->histogram[value] /= (this->width * this->height);
    }
}

std::vector<float> Channel::GetHistogram(){
    this->CalculateHistogram();
    return this->histogram;
}

Photo::Photo(){
    this->width=0;
    this->height=0;
    this->channel_amount=0;
    this->filename="image.bmp";
}

Photo::Photo(int _width,int _height, int _channelAmount, std::string _filename){
    this->width =_width;
    this->height =_height;
    this->channel_amount = _channelAmount;
    this->filename = _filename;
    this->channels.resize(_channelAmount);
    for(int i = 0; i < _channelAmount; i++)
        this->channels[i] = Channel(_width, _height);
}

int Photo::GetHeight(){
    return this->height;
}

int Photo::GetWidth(){
    return this->width;
}

int Photo::GetChannelAmount(){
    return this->channel_amount;
}

std::string Photo::GetFilename(){
    return this->filename;
}

void Photo::SetChannel(int _channelId, Channel _channel){
    this->channels[_channelId] = _channel;
}

Channel& Photo::GetChannel(int _channelIndex){
    return this->channels[_channelIndex];
}