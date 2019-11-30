#include "../headers/functions.h"
#include "../headers/proc.h"
#include <vector>

void ApplyDilation(Channel& _channel, std::vector<std::vector<int>> _mask){
    Channel copyChannel = _channel;
    bool continueChecking;
    int maxValueOfPixels;
    for(int x = 1; x < _channel.GetWidth()-1; x++){
        for(int y = 1; y < _channel.GetHeight()-1; y++){
            maxValueOfPixels = 0;
            for(int j = -1; j < 1; j++){
                for(int i = -1; i < 1; i++){
                    if(copyChannel.GetValue(x+i, y+j) > maxValueOfPixels)
                        maxValueOfPixels = copyChannel.GetValue(x+i, y+j);
                }
            }
            continueChecking = true;
            for(int j = -1; j < 1; j++){
                for(int i = -1; i < 1; i++){
                    if(copyChannel.GetValue(x+i, y+j) == _mask[i+1][j+1]){
                        _channel.SetValue(x, y, maxValueOfPixels);
                        continueChecking = false;
                        break;
                    }
                }
                if(!continueChecking)
                    break;
            }
        }
    }
}

void ApplyErosion(Channel& _channel, std::vector<std::vector<int>> _mask){
    Channel copyChannel = _channel;
    bool continueChecking;
    int minValueOfPixels;
    for(int x = 1; x < _channel.GetWidth()-1; x++){
        for(int y = 1; y < _channel.GetHeight()-1; y++){
            minValueOfPixels = 255;
            for(int j = -1; j < 1; j++){
                for(int i = -1; i < 1; i++){
                    if(copyChannel.GetValue(x+i, y+j) < minValueOfPixels)
                        minValueOfPixels = copyChannel.GetValue(x+i, y+j);
                }
            }
            continueChecking = true;
            for(int j = -1; j < 1; j++){
                for(int i = -1; i < 1; i++){
                    if(copyChannel.GetValue(x+i, y+j) == _mask[i+1][j+1]){
                        _channel.SetValue(x, y, minValueOfPixels); 
                        continueChecking = false;
                        break;
                    }
                }
                if(!continueChecking)
                    break;
            }
        }
    }
}

void ApplyOpening(Channel& _channel, std::vector<std::vector<int>> _mask){
    ApplyErosion(_channel, _mask);
    ApplyDilation(_channel, _mask);
}

void ApplyClosing(Channel& _channel, std::vector<std::vector<int>> _mask){
    ApplyDilation(_channel, _mask);
    ApplyErosion(_channel, _mask);
}