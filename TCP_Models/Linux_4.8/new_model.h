#ifndef NEW_MODEL_H
#define NEW_MODEL_H

#include "TCP_Model.h"

void Execution(int pkt_depth, int pkt_index);

void Spoofed(bool spoofed, int has_payload, int pkt_depth);

bool Verify();

void Instrument_Summary();

#endif
