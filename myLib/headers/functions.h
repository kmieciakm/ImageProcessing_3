#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "./proc.h"
#include <vector>

void ApplyDilation(Channel&, std::vector<std::vector<int>>);
void ApplyErosion(Channel&, std::vector<std::vector<int>>);
void ApplyOpening(Channel&, std::vector<std::vector<int>>);
void ApplyClosing(Channel&, std::vector<std::vector<int>>);
void ApplyHMTtransformation(Channel&, std::vector<std::vector<int>>);
Channel GetChannelComplement(Channel);
void Intersection(Channel&, Channel);

#endif