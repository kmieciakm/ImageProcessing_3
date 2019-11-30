#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "./proc.h"

void ApplyDilation(Channel&);
void ApplyErosion(Channel&);
void ApplyOpening(Channel&);
void ApplyClosing(Channel&);

#endif