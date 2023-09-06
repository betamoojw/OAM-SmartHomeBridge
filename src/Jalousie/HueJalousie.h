#pragma once
#include "HueBridge.h"
#include "KnxChannelJalousie.h"
#include "../Rolladen/HueRolladen.h"

class HueJalousie : public HueRolladen
{
public:
    HueJalousie(HueBridge* bridge);
 
    virtual void setSlatPosition(uint8_t slatPosition) override;
};