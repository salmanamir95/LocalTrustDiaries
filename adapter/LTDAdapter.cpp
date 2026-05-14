#include "LTDAdapter.h"
#include "runtime/tasksystem.h"
#include "core/input.h"
#include "protocol/trust/TrustNode_ops.h"

// =================================================
// NODE BINDING
// =================================================

void LTDAdapter::bindNode(TrustNode* n)
{
    node = n;
}

// =================================================
// ASYNC GETTERS
// =================================================

TaskHandle LTDAdapter::getAckCount()
{
    return taskSystem->submit(
        Input<NoInput>{},
        [this](Input<NoInput>) {
            return trust_node_get_acks(node);
        }
    );
}

TaskHandle LTDAdapter::getNackCount()
{
    return taskSystem->submit(
        Input<NoInput>{},
        [this](Input<NoInput>) {
            return trust_node_get_nacks(node);
        }
    );
}

TaskHandle LTDAdapter::getTrust()
{
    return taskSystem->submit(
        Input<NoInput>{},
        [this](Input<NoInput>) {
            return trust_node_get_trust(node);
        }
    );
}

TaskHandle LTDAdapter::getP()
{
    return taskSystem->submit(
        Input<NoInput>{},
        [this](Input<NoInput>) {
            return trust_node_get_p(node);
        }
    );
}

TaskHandle LTDAdapter::getS()
{
    return taskSystem->submit(
        Input<NoInput>{},
        [this](Input<NoInput>) {
            return trust_node_get_s(node);
        }
    );
}

// =================================================
// ASYNC SETTERS
// =================================================

TaskHandle LTDAdapter::setTrust(uint32_t value)
{
    return taskSystem->submit(
        Input<uint32_t>{value},
        [this](Input<uint32_t> in) {
            trust_node_set_trust(node, in.get());
        }
    );
}

TaskHandle LTDAdapter::setP(uint32_t value)
{
    return taskSystem->submit(
        Input<uint32_t>{value},
        [this](Input<uint32_t> in) {
            trust_node_set_p(node, in.get());
        }
    );
}

TaskHandle LTDAdapter::setS(uint32_t value)
{
    return taskSystem->submit(
        Input<uint32_t>{value},
        [this](Input<uint32_t> in) {
            trust_node_set_s(node, in.get());
        }
    );
}

// =================================================
// ASYNC EVENTS
// =================================================

TaskHandle LTDAdapter::incrementAck()
{
    return taskSystem->submit(
        Input<NoInput>{},
        [this](Input<NoInput>) {
            trust_node_increment_ack(node);
        }
    );
}

TaskHandle LTDAdapter::incrementNack()
{
    return taskSystem->submit(
        Input<NoInput>{},
        [this](Input<NoInput>) {
            trust_node_increment_nack(node);
        }
    );
}

TaskHandle LTDAdapter::updateTrust()
{
    return taskSystem->submit(
        Input<NoInput>{},
        [this](Input<NoInput>) {
            trust_node_update_trust_bayes(node);
            return trust_node_get_trust(node);
        }
    );
}