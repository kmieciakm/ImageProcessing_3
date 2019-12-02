#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "./proc.h"
#include <vector>

std::vector<std::vector<int>> GetMask(int);
void ApplyDilation(Channel&, int);
void ApplyErosion(Channel&, int);
void ApplyOpening(Channel&, int);
void ApplyClosing(Channel&, int);
void ApplyHMTtransformation(Channel&, int);
void ApplyChannelsSum(Channel&, std::vector<Channel>);
void ApplyM4(Channel&);
bool AreChannelsEqual(Channel, Channel);

#endif