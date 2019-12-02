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
    if(command == "--dilation" || command == "--erosion" || command == "--opening" || command == "--closing" || command == "--hmt"){
        if(argumentsAmount != 3){
            std::cout << "Unexpected or missing argument";
            exit(0);
        }else{
            std::vector<std::vector<int>> mask;
            mask.resize(3);
            for(int depth = 0; depth < 3; depth++)
                mask[depth].resize(3);
            std::string sign;

            std::cout << "Build 3x3 mask (0 - black, 1 - white, -1 - non consider):" << std::endl;
            for(int j = 0; j<3 ; j++){
                for(int i = 0; i<3; i++){
                    do{
                        std::cout <<  "(" << i << ", " << j << "): ";
                        std::cin >> sign;
                    }while(sign != "1" && sign != "0" && sign != "-1");
                    if(sign == "1")
                        mask[i][j] = 255;
                    else
                        mask[i][j] = atoi(sign.c_str());
                }
            }            

            if(command=="--dilation"){
                for(int channel = 0; channel < CHANNEL_AMOUNT; channel++)
                    ApplyDilation(photo.GetChannel(channel), mask);
            }else if(command=="--erosion"){
                for(int channel = 0; channel < CHANNEL_AMOUNT; channel++)
                    ApplyErosion(photo.GetChannel(channel), mask);
            }else if(command=="--opening"){
                for(int channel = 0; channel < CHANNEL_AMOUNT; channel++)
                    ApplyOpening(photo.GetChannel(channel), mask);
            }else if(command=="--closing"){
                for(int channel = 0; channel < CHANNEL_AMOUNT; channel++)
                    ApplyClosing(photo.GetChannel(channel), mask);
            }else if(command=="--hmt"){
                for(int channel = 0; channel < CHANNEL_AMOUNT; channel++)
                    ApplyHMTtransformation(photo.GetChannel(channel), mask);
            }else{
                std::cout<<"unexpected error";
                exit(0);
            }
        }
    }else{
        std::cout << "Illigal command: " << command;
        exit(0);
    }
}