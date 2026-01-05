#ifndef ENVELOPE_NODE_H
#define ENVELOPE_NODE_H

#include "AudioNode.h"

class EnvelopeNode : public AudioNode {
public:
    EnvelopeNode(float attack, float release);
    void process(const std::vector<float>& input, std::vector<float>& output) override;

private:
    float attack_;
    float release_;
    float envelope_;
};

#endif