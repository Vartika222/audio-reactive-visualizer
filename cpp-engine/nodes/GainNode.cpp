#include "GainNode.h"

GainNode::GainNode(float gain) : gain_(gain) {}

void GainNode::process(const std::vector<float>& input, std::vector<float>& output) {
    output.resize(input.size());
    for (size_t i = 0; i < input.size(); ++i) {
        output[i] = input[i] * gain_;
    }
}