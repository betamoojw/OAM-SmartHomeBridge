#include "HomeKitJalousie.h"

HomeKitJalousie::HomeKitJalousie(int device) :
    HomeKitRolladen(device)
{
}

void HomeKitJalousie::setup()
{
    HomeKitRolladen::setup();
    currentHorizontalTiltAngle = new Characteristic::CurrentHorizontalTiltAngle(0);
    targetHorizontalTiltAngle = new Characteristic::TargetHorizontalTiltAngle(0);
}

boolean HomeKitJalousie::update()
{
    if (HomeKitRolladen::update())
        return true;
    
    if (targetHorizontalTiltAngle->updated())
    {
        int angle = targetHorizontalTiltAngle->getNewVal();
        int percent = (angle + 90) / 1.8f;
        logDebugP("Angle: %d, Percent: %d", angle, percent);
        if (percent < 0)
            percent = 0;
        if (percent > 100)
            percent = 100;
  
        ((KnxChannelJalousie*)_channel)->commandSlatPosition(this, percent);
        return true;
    }
    return false;
}

void HomeKitJalousie::setSlatPosition(uint8_t position)
{
    int angle = (position * 1.8f) - 90; 
    logDebugP("Slat position: %d, Angle: %d", position, angle);
    if (angle < -90)
        angle = -90;
    if (angle > 90)
        angle = 90;
    currentHorizontalTiltAngle->setVal(angle);
}
