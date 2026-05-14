#pragma once

#include <any>
#include "adapter/IAdapter.h"

class LTDAdapter : public IAdapter {
public:
    void init() override;
    void tick() override;
};