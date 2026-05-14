#pragma once

#include <any>
#include "adapter/IAdapter.h"
#include "protocol/trust/TrustNode.h"
#include "runtime/taskhandle.h"

class LTDAdapter : public IAdapter {
private:
    TrustNode* node = nullptr;

public:
    void bindNode(TrustNode* n);

    void init() override;
    void tick() override;

    // =================================================
    // ASYNC GETTERS
    // =================================================
    TaskHandle getAckCount();
    TaskHandle getNackCount();
    TaskHandle getTrust();
    TaskHandle getP();
    TaskHandle getS();

    // =================================================
    // ASYNC SETTERS
    // =================================================
    TaskHandle setTrust(uint32_t value);
    TaskHandle setP(uint32_t value);
    TaskHandle setS(uint32_t value);

    // =================================================
    // ASYNC EVENTS
    // =================================================
    TaskHandle incrementAck();
    TaskHandle incrementNack();
    TaskHandle updateTrust();
};