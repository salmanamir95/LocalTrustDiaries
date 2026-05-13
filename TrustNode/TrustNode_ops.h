#ifndef TRUST_NODE_H

#include "protocol/trust/TrustNode.h"

#define TRUST_NODE_H

#if !defined(__linux__)
#error "This project is optimized for Linux systems only"
#endif

#include <cstdint>
#include <stdio.h>
#include <string.h>

#define TRUST_NODE_INLINE inline __attribute__((always_inline))




TRUST_NODE_INLINE void trust_node_init(TrustNode *&node){
    memset(&node->nodeid, 0, sizeof(ipv6_t));
    node->trust = 20;
    node->acks = 0;
    node->nacks = 0;
    memset(node->reserved, 0, sizeof(node->reserved));
}

TRUST_NODE_INLINE const ipv6_t* trust_node_get_id(const TrustNode *&node){
    return &node->nodeid;
}

TRUST_NODE_INLINE const uint32_t* trust_node_get_trust(const TrustNode *&node){
    return &node->trust;
}

TRUST_NODE_INLINE const uint32_t* trust_node_get_acks(const TrustNode *&node){
    return &node->acks;
}

TRUST_NODE_INLINE const uint32_t* trust_node_get_nacks(const TrustNode *&node){
    return &node->nacks;
}

TRUST_NODE_INLINE void trust_node_set_id(TrustNode *&node, const ipv6_t* address){
    node->nodeid = *address;
}

TRUST_NODE_INLINE void trust_node_set_trust(TrustNode *&node, const uint32_t trust){
    node->trust = trust; 
}
TRUST_NODE_INLINE void trust_node_set_acks(TrustNode *&node, const uint32_t acks){
    node->acks = acks; 
}
TRUST_NODE_INLINE void trust_node_set_nacks(TrustNode *&node, const uint32_t nacks){
    node->nacks = nacks; 
}

TRUST_NODE_INLINE void trust_node_update_trust(TrustNode*&node, const uint8_t ack_type){

}



#endif // TRUST_NODE_H