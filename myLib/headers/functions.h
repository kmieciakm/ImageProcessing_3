#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "./proc.h"
#include <vector>

void ApplyDilation(Channel&, int);
void ApplyErosion(Channel&, int);
void ApplyOpening(Channel&, int);
void ApplyClosing(Channel&, int);
void ApplyHMTtransformation(Channel&, int);
void ApplyConvexHull(Channel&);
void ApplyRegionGrowing(Channel&, int, int, int, int);

std::vector<std::vector<int>> GetMask(int);
Channel GetChannelsSum(std::vector<Channel>&);
bool AreChannelsEqual(Channel&, Channel&);
void ApplySimpleHMTtransformation(Channel&, int);
void ApplyGlobalRegionGrowing(Channel&, int, int);
void Recursive(Channel&, Channel&, short, short);

#endif