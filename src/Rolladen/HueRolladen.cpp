#include "HueRolladen.h"

HueRolladen::HueRolladen(HueBridge* hueBridge)
: hueBridge(hueBridge)
{
    
}

void HueRolladen::setup(uint8_t _channelIndex)
{
    espalexaDevice = new EspalexaDevice(_channel->getNameInUTF8(), [this](EspalexaDevice* d){update();}, EspalexaDeviceType::dimmable, 0);
    espalexaDevice->setState(false);
    hueBridge->espalexa.addDevice(_channel->channelIndex(), espalexaDevice);
 }

boolean HueRolladen::update()
{
    switch (espalexaDevice->getLastChangedProperty())
    {
        case EspalexaDeviceProperty::on:
            _channel->commandPosition(this, 100);
            break;
        case EspalexaDeviceProperty::off:
            _channel->commandPosition(this, 0);
            break;
         case EspalexaDeviceProperty::bri:
            _channel->commandPosition(this, espalexaDevice->getPercent());
            break;
    }
    return (true);
}

void HueRolladen::setMovement(MoveState movement)
{

}

void HueRolladen::setPosition(uint8_t position)
{
    espalexaDevice->setPercent(position);
    if (position == 0)
    {
        espalexaDevice->setState(false);
    }
    else
    {
        espalexaDevice->setState(true);
    }
}
