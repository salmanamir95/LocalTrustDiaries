#include "adapters/LTDAdapter.h"

#include "runtime/tasksystem.h"
#include "runtime/taskhandle.h"

#include "protocol/trust/TrustNode.h"
#include "protocol/trust/TrustNodeOps.h"

#include <iostream>

LTDAdapter::LTDAdapter(TaskSystem* system)
    : system(system) {}

void LTDAdapter::init() {
    processedNodes = 0;
    std::cout << "[LTDAdapter] init\n";
}

void LTDAdapter::tick() {
    // telemetry only (NO task interaction)
    std::cout << "[LTDAdapter] telemetry tick\n";
}

TaskHandle LTDAdapter::submitTask(std::any input) {

    return system->submit(
        std::move(input),
        [](std::any in) -> std::any {

            TrustNode* node = std::any_cast<TrustNode*>(in);

            if (node) {
                trust_node_set_trust(node, 100);
            }

            return node;
        }
    );
}

void LTDAdapter::updateTrustNode(TrustNode* node, uint8_t ackType) {
    if (!node) return;

    trust_node_update_trust(node, ackType);
    processedNodes++;
}