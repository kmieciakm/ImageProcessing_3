#include "../headers/functions.h"
#include "../headers/proc.h"
#include <vector>

void ApplyDilation(Channel& _channel, std::vector<std::vector<int>> _mask){
    Channel copyChannel = _channel;
    for(int x = 1; x < _channel.GetWidth()-1; x++){
        for(int y = 1; y < _channel.GetHeight()-1; y++){
            
            if(_mask[1][1] == copyChannel.GetValue(x,y)){
                for(int i = -1; i <= 1; i++){
                    for(int j = -1; j <= 1; j++){
                        if(_mask[i+1][j+1] != -1){
                            if(_mask[i+1][j+1] != copyChannel.GetValue(x+i,y+j)){
                                _channel.SetValue(x+i, y+j, 255);
                            }
                        }   
                    }
                }
            }   

        }
    }
}

void ApplyErosion(Channel& _channel, std::vector<std::vector<int>> _mask){
    Channel copyChannel = _channel;
    for(int x = 1; x < _channel.GetWidth()-1; x++){
        for(int y = 1; y < _channel.GetHeight()-1; y++){
            
            if(_mask[1][1] == copyChannel.GetValue(x,y)){
                for(int i = -1; i <= 1; i++){
                    for(int j = -1; j <= 1; j++){
                        if(_mask[i+1][j+1] != -1){
                            if(_mask[i+1][j+1] != copyChannel.GetValue(x+i,y+j)){
                                _channel.SetValue(x, y, 0);
                            }
                        }   
                    }
                }
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

void ApplyHMTtransformation(Channel& _channel, std::vector<std::vector<int>> _b1){
    std::vector<std::vector<int>> b2;
    b2.resize(3);
    for(int i = 0; i < b2.size(); i++)
        b2[i].resize(3);
    for(int j = 0; j < 3; j++){
        for(int i = 0; i < 3; i++){
            if(_b1[i][j] == 255)
                b2[i][j] = 0;
            else if (_b1[i][j] == 0)
                b2[i][j] = 255;
            else
                b2[i][j] = -1;
        }
    }

    Channel channelComplement = GetChannelComplement(_channel);
    ApplyErosion(_channel, _b1);
    ApplyErosion(channelComplement, b2);    
    Intersection(_channel, channelComplement);
}

Channel GetChannelComplement(Channel _channel){
    for(int x = 0; x < _channel.GetWidth(); x++){
        for(int y = 0; y < _channel.GetHeight(); y++){
            _channel.SetValue(x,y,(255-_channel.GetValue(x,y)));
        }
    }
    return _channel;
}

void Intersection(Channel& _channel, Channel _channelToCompare){
    for(int x = 0; x < _channel.GetWidth(); x++){
        for(int y = 0; y < _channel.GetHeight(); y++){
            if(_channel.GetValue(x,y) == 255 && _channelToCompare.GetValue(x,y) == 255)
                _channel.SetValue(x,y,255);
            else
                _channel.SetValue(x,y,0);    
        }
    }
}