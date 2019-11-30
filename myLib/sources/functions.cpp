#include "../headers/functions.h"
#include "../headers/proc.h"

void ApplyDilation(Channel& _channel){
    Channel copyChannel = _channel;
    bool continueChecking;
    for(int x = 1; x < _channel.GetWidth()-1; x++){
        for(int y = 1; y < _channel.GetHeight()-1; y++){
            continueChecking = true;
            for(int i = -1; i < 1; i++){
                for(int j = -1; j < 1; j++){
                    if(i == 0 && y == 0){
                        continue;
                    }else if(copyChannel.GetValue(x+i, y+j) == 255){
                        _channel.SetValue(x, y, 255); 
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

void ApplyErosion(Channel& _channel){
    Channel copyChannel = _channel;
    bool continueChecking;
    for(int x = 1; x < _channel.GetWidth()-1; x++){
        for(int y = 1; y < _channel.GetHeight()-1; y++){
            continueChecking = true;
            for(int i = -1; i < 1; i++){
                for(int j = -1; j < 1; j++){
                    if(i == 0 && y == 0){
                        continue;
                    }else if(copyChannel.GetValue(x+i, y+j) == 0){
                        _channel.SetValue(x, y, 0); 
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

void ApplyOpening(Channel& _channel){
    ApplyErosion(_channel);
    ApplyDilation(_channel);
}

void ApplyClosing(Channel& _channel){
    ApplyDilation(_channel);
    ApplyErosion(_channel);
}