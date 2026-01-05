#ifndef GAIN_NODE_H
#define GAIN_NODE_H

#include "AudioNode.h"

class GainNode : public AudioNode {
public:
    GainNode(float gain);
    void process(const std::vector<float>& input, std::vector<float>& output) override;

private:
    float gain_;
};

#endif