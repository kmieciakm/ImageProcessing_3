#include <iostream>
#include <chrono>
#include <stdlib.h>
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
    if(command == "--dilation"){
        if(argumentsAmount != 3){
            std::cout << "Unexpected or missing argument";
            exit(0);
        }else{
            for(int channel = 0; channel < CHANNEL_AMOUNT; channel++)
                ApplyDilation(photo.GetChannel(channel));
        }
    }else if(command == "--erosion"){
        if(argumentsAmount != 3){
            std::cout << "Unexpected or missing argument";
            exit(0);
        }else{
            for(int channel = 0; channel < CHANNEL_AMOUNT; channel++)
                ApplyErosion(photo.GetChannel(channel));
        }
    }else if(command == "--opening"){
        if(argumentsAmount != 3){
            std::cout << "Unexpected or missing argument";
            exit(0);
        }else{
            for(int channel = 0; channel < CHANNEL_AMOUNT; channel++)
                ApplyOpening(photo.GetChannel(channel));
        }
    }else if(command == "--closing"){
        if(argumentsAmount != 3){
            std::cout << "Unexpected or missing argument";
            exit(0);
        }else{
            for(int channel = 0; channel < CHANNEL_AMOUNT; channel++)
                ApplyClosing(photo.GetChannel(channel));
        }
    }else{
        std::cout << "Illigal command: " << command;
        exit(0);
    }
}