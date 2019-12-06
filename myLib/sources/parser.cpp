#include <iostream>
#include "../headers/proc.h"
#include "../headers/converter.h"
#include "../headers/functions.h"
#include "../../CImg/CImg.h"

bool isIntNumber(std::string str){
    for (int i=0 ; i < str.length(); i++){
        if(str[0] == '-')
            continue;
        if ( !isdigit(str[i]) ) 
            return false;
    }
    return true;
}

void DisplayHelpInformations(){
    std::cout << std::endl << "Usage" << std::endl;
    std::cout << "task3 -pathToImage --command [-argument=value [...]]" << std::endl << std::endl;
    std::cout << "Options" << std::endl << std::endl;
    std::cout 
        << "--dilation        =  Apply dilation on every channel in photo" << std::endl
        << std::endl;
    exit(0);
}

std::string ExtractFilenameFromPath(std::string path){
    std::string filename = "";
    short indexOfSlash = 0;
    for(int characterIndex = path.length()-1; characterIndex >= 0; characterIndex--){
        if(path[characterIndex] == '/'){
            indexOfSlash = characterIndex;
            break;
        }
    }
    for(int currentIndex = indexOfSlash+1; currentIndex<path.length(); currentIndex++){
        filename += path[currentIndex];
    }
    return filename;
}

void ParseCommandAndRun(std::string command, int argumentsAmount, char *arguments[], Photo & photo){
    const int CHANNEL_AMOUNT = photo.GetChannelAmount();
    if(command == "--dilation" || command == "--erosion" || command == "--opening" || command == "--closing"){
        if(argumentsAmount != 4){
            std::cout << "Unexpected or missing argument";
            exit(0);
        }else{        
               
            if(!isIntNumber(static_cast<std::string>(arguments[3])) || std::stoi(static_cast<std::string>(arguments[3])) < 1 || std::stoi(static_cast<std::string>(arguments[3])) > 10){
                std::cout << "Wrong argument type, possible values: 1,2,3,4,5,6,7,8,9,10";
                exit(0);
            }else{
                int version = std::stoi(static_cast<std::string>(arguments[3]));
                if(command=="--dilation"){
                    for(int channel = 0; channel < CHANNEL_AMOUNT; channel++)
                        ApplyDilation(photo.GetChannel(channel), version);
                }else if(command=="--erosion"){
                    for(int channel = 0; channel < CHANNEL_AMOUNT; channel++)
                        ApplyErosion(photo.GetChannel(channel), version);
                }else if(command=="--opening"){
                    for(int channel = 0; channel < CHANNEL_AMOUNT; channel++)
                        ApplyOpening(photo.GetChannel(channel), version);
                }else if(command=="--closing"){
                    for(int channel = 0; channel < CHANNEL_AMOUNT; channel++)
                        ApplyClosing(photo.GetChannel(channel), version);
                }else{
                    std::cout<<"unexpected error";
                    exit(0);
                }
            }
        }
    }else if(command == "--hmt"){
        if(argumentsAmount != 4){
            std::cout << "Unexpected or missing argument";
            exit(0);
        }else{          
            if(!isIntNumber(static_cast<std::string>(arguments[3])) || std::stoi(static_cast<std::string>(arguments[3])) != 11 && std::stoi(static_cast<std::string>(arguments[3])) != 12){
                std::cout << "Wrong argument type, possible values: 11,12";
                exit(0);
            }else{
                int version = std::stoi(static_cast<std::string>(arguments[3]));
                for(int channel = 0; channel < CHANNEL_AMOUNT; channel++)
                    ApplyHMTtransformation(photo.GetChannel(channel), version);
            }
        }
    }else if(command == "--convex"){
        if(argumentsAmount != 3){
            std::cout << "Unexpected or missing argument";
            exit(0);
        }else{
            for(int channel = 0; channel < CHANNEL_AMOUNT; channel++)
                ApplyConvexHull(photo.GetChannel(channel));
        }
    }else{
        std::cout << "Illigal command: " << command;
        exit(0);
    }
}