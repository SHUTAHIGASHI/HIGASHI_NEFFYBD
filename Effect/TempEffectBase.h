#pragma once
#include "EffectBase.h"

class TempEffectBase :
    public EffectBase
{
public:
    TempEffectBase(EffectType type, int handle) :
        EffectBase(type, handle)
    {
        EffectBase::CreateEffect();
    }

    // XVˆ—
    void Update();
};

