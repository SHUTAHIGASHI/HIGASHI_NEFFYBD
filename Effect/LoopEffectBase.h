#pragma once
#include "EffectBase.h"
class LoopEffectBase :
    public EffectBase
{
public:
    LoopEffectBase(EffectType type, int handle) :
        EffectBase(type, handle)
    {
        EffectBase::CreateEffect();
    }

    void Update();
};

