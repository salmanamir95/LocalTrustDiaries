#pragma once

#if !defined(__linux__)
#error "This project is optimized for Linux systems only"
#endif

#include <cstdint>
#include <cstring>
#include <cmath>

#include "core/datatypes/ipv6.h"
#include "protocol/trust/TrustNode.h"
#include "core/Global_Size_Offsets.h"

#ifdef __cplusplus
extern "C" {
#endif

// =================================================
// INIT
// =================================================
static inline void trust_node_init(TrustNode* node, const ipv6_t* nodeid)
{
    if (!node || !nodeid) return;

    std::memcpy(&node->nodeid, nodeid, IPV6_SIZE);

    // default prior
    node->p = (uint32_t)(0.3f * UINT32_MAX);
    node->s = 1;

    node->acks = 0;
    node->nacks = 0;

    node->trust = node->p;
}

// =================================================
// GETTERS
// =================================================
static inline const ipv6_t* trust_node_get_id(const TrustNode* node)
{
    return node ? &node->nodeid : NULL;
}

static inline uint32_t trust_node_get_trust(const TrustNode* node)
{
    return node ? node->trust : 0;
}

static inline uint32_t trust_node_get_acks(const TrustNode* node)
{
    return node ? node->acks : 0;
}

static inline uint32_t trust_node_get_nacks(const TrustNode* node)
{
    return node ? node->nacks : 0;
}

static inline uint32_t trust_node_get_p(const TrustNode* node)
{
    return node ? node->p : 0;
}

static inline uint32_t trust_node_get_s(const TrustNode* node)
{
    return node ? node->s : 0;
}

// =================================================
// SETTERS
// =================================================
static inline void trust_node_set_trust(TrustNode* node, uint32_t trust)
{
    if (!node) return;
    node->trust = trust;
}

static inline void trust_node_set_p(TrustNode* node, uint32_t p)
{
    if (!node) return;
    node->p = p;
}

static inline void trust_node_set_s(TrustNode* node, uint32_t s)
{
    if (!node) return;
    node->s = s;
}

// =================================================
// EVENT UPDATES
// =================================================
static inline void trust_node_increment_ack(TrustNode* node)
{
    if (!node) return;
    node->acks++;
}

static inline void trust_node_increment_nack(TrustNode* node)
{
    if (!node) return;
    node->nacks++;
}

// =================================================
// BAYESIAN UPDATE (Beta-Bernoulli)
// =================================================
static inline void trust_node_update_trust_bayes(TrustNode* node)
{
    if (!node) return;

    const uint32_t acks  = node->acks;
    const uint32_t nacks = node->nacks;

    const uint32_t n = acks + nacks;

    // prior strength
    const uint64_t s = node->s;
    const uint64_t p = node->p;

    // α = p*s
    const uint64_t alpha = ((uint64_t)p * s) / UINT32_MAX;

    // β = (1-p)*s
    const uint64_t beta = ((UINT32_MAX - p) * s) / UINT32_MAX;

    // posterior probability
    const uint64_t new_p =
        ((alpha + acks) * UINT32_MAX) / (alpha + beta + n + 1);

    // strength update
    node->s = s + n;

    // previous trust blending (your requirement)
    const uint64_t prev = node->trust;

    const uint64_t blended =
        (prev * new_p) / UINT32_MAX;

    node->trust = (uint32_t)blended;
    node->p = (uint32_t)new_p;

    // reset evidence
    node->acks = 0;
    node->nacks = 0;
}

#ifdef __cplusplus
}
#endif