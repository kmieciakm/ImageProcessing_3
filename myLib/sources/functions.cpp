#include "../headers/functions.h"
#include "../headers/proc.h"
#include <vector>

std::vector<std::vector<int>> GetMask(int _version){
    std::vector<std::vector<int>> mask;
    switch(_version){
        case 1:
            mask = { {-1,-1,-1}, {-1, 255, 255}, {-1,-1,-1} }; break;
        case 2:
            mask = { {-1,-1,-1}, {-1, 255,-1}, {-1, 255,-1} }; break;
        case 3:
            mask = { { 255, 255, 255}, { 255, 255, 255}, { 255, 255, 255} }; break;
        case 4:
            mask = { {-1, 255,-1}, { 255, 255, 255}, {-1, 255,-1} }; break;
        case 5:
            mask = { {-1,-1,-1}, {-1, 255, 255}, {-1, 255,-1} }; break;
        case 6:
            mask = { {-1,-1,-1}, {-1, 0, 255}, {-1, 255,-1} }; break;
        case 7:
            mask = { {-1,-1,-1}, { 255, 255, 255}, {-1,-1,-1} }; break;
        case 8:
            mask = { {-1,-1,-1}, { 255, 0, 255}, {-1,-1,-1} }; break;
        case 9:
            mask = { {-1,-1,-1}, { 255, 255,-1}, { 255,-1,-1} }; break;
        case 10:
            mask = { {-1, 255, 255}, {-1, 255,-1}, {-1,-1,-1} }; break;
        default:
            mask = { { 255, 255, 255}, { 255, 255, 255}, { 255, 255, 255} };
    }
    return mask;
}

void ApplyDilation(Channel& _channel, int _version){
    std::vector<std::vector<int>> mask = GetMask(_version);
    Channel copyChannel = _channel;
    for(int x = 1; x < _channel.GetWidth()-1; x++){
        for(int y = 1; y < _channel.GetHeight()-1; y++){
            
            if(mask[1][1] == copyChannel.GetValue(x,y)){
                for(int i = -1; i <= 1; i++){
                    for(int j = -1; j <= 1; j++){
                        if(mask[i+1][j+1] != -1){
                            if(mask[i+1][j+1] != copyChannel.GetValue(x+i,y+j)){
                                _channel.SetValue(x+i, y+j, 255);
                            }
                        }   
                    }
                }
            }   

        }
    }
}

void ApplyErosion(Channel& _channel, int _version){
    std::vector<std::vector<int>> mask = GetMask(_version);
    Channel copyChannel = _channel;
    for(int x = 1; x < _channel.GetWidth()-1; x++){
        for(int y = 1; y < _channel.GetHeight()-1; y++){
            
            if(mask[1][1] == copyChannel.GetValue(x,y)){
                for(int i = -1; i <= 1; i++){
                    for(int j = -1; j <= 1; j++){
                        if(mask[i+1][j+1] != -1){
                            if(mask[i+1][j+1] != copyChannel.GetValue(x+i,y+j)){
                                _channel.SetValue(x, y, 0);
                            }
                        }   
                    }
                }
            }

        }
    }
}

void ApplyOpening(Channel& _channel, int _version){
    ApplyErosion(_channel, _version);
    ApplyDilation(_channel, _version);
}

void ApplyClosing(Channel& _channel, int _version){
    ApplyDilation(_channel, _version);
    ApplyErosion(_channel, _version);
}

void ApplyHMTtransformation(Channel& _channel, int _version){
    int maskAmount;
    std::vector<std::vector<std::vector<int>>> masks;

    if(_version == 11){
        maskAmount = 4;
        masks.resize(maskAmount);
        masks[0] = { {255, -1, -1}, {255, 0, -1}, {255, -1, -1} };
        masks[1] = { {255, 255, 255}, {-1, 0, -1}, {-1, -1, -1} };
        masks[2] = { {-1, -1, 255}, {-1, 0, 255}, {-1, -1, 255} };
        masks[3] = { {-1, -1, -1}, {-1, 0, -1}, {255, 255, 255} };
    }else if (_version == 12){
        maskAmount = 8;
        masks.resize(maskAmount);
        masks[0] = { {0, 0, 0}, {-1, 255, -1}, {255, 255, 255} };
        masks[1] = { {-1, 0, 0}, {255, 255, 0}, {255, 255, -1} };
        masks[2] = { {255, -1, 0}, {255, 255, 0}, {255, -1, 0} };
        masks[3] = { {255, 255, -1}, {255, 255, 0}, {-1, 0, 0} };
        masks[4] = { {255, 255, 255}, {-1, 255, -1}, {0, 0, 0} };
        masks[5] = { {-1, 255, 255}, {0, 255, 255}, {0, 0, -1} };
        masks[6] = { {0, -1, 255}, {0, 255, 255}, {0, -1, 255} };
        masks[7] = { {0, 0, -1}, {0, 255, 255}, {-1, 255, 255} };
    }
    std::vector<Channel> channelCopies(maskAmount, _channel);
    for(int maskInx = 0; maskInx < maskAmount; maskInx++){
    
        for(int x = 1; x < channelCopies[maskInx].GetWidth()-1; x++){
            for(int y = 1; y < channelCopies[maskInx].GetHeight()-1; y++){
                bool allMatches = true;
                for(int i = -1; i <= 1; i++){
                    for(int j = -1; j <= 1; j++){
                        if(masks[maskInx][j+1][i+1] != -1){
                            if(masks[maskInx][j+1][i+1] != _channel.GetValue(x+i,y+j)){
                                allMatches = false;
                            }
                        }   
                    }
                }
                if(allMatches)
                    channelCopies[maskInx].SetValue(x, y, 255);
                else
                    channelCopies[maskInx].SetValue(x, y, 0);
            }
        }
    }
    _channel = GetChannelsSum(channelCopies);
}

void ApplyConvexHull(Channel& _channel){
    Channel Xk;
    Channel previousXk;
    std::vector<Channel> D;
    std::vector<Channel> channelsToSum;
    for(int i=0; i<4; i++){
        Xk = _channel;
        do{
            previousXk = Xk;
            ApplySimpleHMTtransformation(Xk, i);
            channelsToSum = {Xk, previousXk};
            Xk = GetChannelsSum(channelsToSum);
        }while(!AreChannelsEqual(Xk, previousXk));
        D.push_back(Xk);
    }
    _channel = GetChannelsSum(D);
}

Channel GetChannelsSum(std::vector<Channel>& _channelsCopies){
    Channel outputChannel = _channelsCopies[0];
    bool hasWhite;
    for(int x = 0; x < outputChannel.GetWidth(); x++){
        for(int y = 0; y < outputChannel.GetHeight(); y++){
            hasWhite = false;
            for(int i = 0; i< _channelsCopies.size(); i++){
                if(_channelsCopies[i].GetValue(x,y) == 255){
                    hasWhite = true;
                    break;
                }
            }  
            if(hasWhite)
                outputChannel.SetValue(x,y,255);
            else
                outputChannel.SetValue(x,y,0);   
        }
    }
    return outputChannel;
}

bool AreChannelsEqual(Channel& _channel1, Channel& _channel2){
    for(int x = 1; x < _channel1.GetWidth()-1; x++){
        for(int y = 1; y < _channel1.GetHeight()-1; y++){
            if(_channel1.GetValue(x,y) != _channel2.GetValue(x,y))
                return false;
        }
    }
    return true;
}

void ApplySimpleHMTtransformation(Channel& _channel, int _maskVersion){
    constexpr unsigned int MASK_AMOUNT = 4;
    std::vector<std::vector<std::vector<int>>> masks;
    masks.resize(MASK_AMOUNT);
    masks[0] = { {255, -1, -1}, {255, 0, -1}, {255, -1, -1} };
    masks[1] = { {255, 255, 255}, {-1, 0, -1}, {-1, -1, -1} };
    masks[2] = { {-1, -1, 255}, {-1, 0, 255}, {-1, -1, 255} };
    masks[3] = { {-1, -1, -1}, {-1, 0, -1}, {255, 255, 255} };
    
    Channel channelCopy = _channel;
    for(int x = 1; x < channelCopy.GetWidth()-1; x++){
        for(int y = 1; y < channelCopy.GetHeight()-1; y++){
            bool allMatches = true;
            for(int i = -1; i <= 1; i++){
                for(int j = -1; j <= 1; j++){
                    if(masks[_maskVersion][j+1][i+1] != -1){
                        if(masks[_maskVersion][j+1][i+1] != _channel.GetValue(x+i,y+j)){
                            allMatches = false;
                            break;
                        }
                    }   
                }
            }
            if(allMatches)
                channelCopy.SetValue(x, y, 255);
            else
                channelCopy.SetValue(x, y, 0);
        }
    }
    _channel = channelCopy;
}

void ApplyGlobalRegionGrowing(Channel& _channel, int _minIntensity, int _maxIntensity){
    for(int x = 0; x < _channel.GetWidth(); x++){
        for(int y = 0; y < _channel.GetHeight(); y++){
            if(_channel.GetValue(x,y) <= _maxIntensity && _channel.GetValue(x,y) >= _minIntensity)
                _channel.SetValue(x,y,255);
            else
                _channel.SetValue(x,y,0);            
        }
    }
}

void ApplyRegionGrowing(Channel& _channel, int _seedX, int _seedY, int _minIntensity, int _maxIntensity){
    Channel global = _channel;
    ApplyGlobalRegionGrowing(global, _minIntensity, _maxIntensity);

    Channel output(_channel.GetWidth(),_channel.GetHeight());
    for(int x = 0; x < output.GetWidth(); x++){
        for(int y = 0; y < output.GetHeight(); y++){
            output.SetValue(x,y,0);
        }
    }

    global.SetValue(_seedX, _seedY, 255);
    Recursive(output, global, _seedX, _seedY);
    _channel = output;
}

void Recursive(Channel& _channel, Channel& _global, short _x, short _y){
    if(_channel.GetValue(_x, _y) == 255 || _global.GetValue(_x, _y) != 255 
       || _x == 0 || _x == _channel.GetWidth()-1 || _y == 0 || _y == _channel.GetHeight()-1) {
        return;
    } else {
        _channel.SetValue(_x, _y, 255);
        for(int i = -1; i <= 1; i++){
            for(int j = -1; j <= 1; j++){ 
                Recursive(_channel, _global, _x+i, _y+j);
            }
        }
    }
    return;
}