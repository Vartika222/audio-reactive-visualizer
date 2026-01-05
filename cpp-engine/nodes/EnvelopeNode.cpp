#include "EnvelopeNode.h"
#include <algorithm>

EnvelopeNode::EnvelopeNode(float attack, float release) : attack_(attack), release_(release), envelope_(0.0f) {}

void EnvelopeNode::process(const std::vector<float>& input, std::vector<float>& output) {
    output.resize(input.size());
    for (size_t i = 0; i < input.size(); ++i) {
        float absInput = std::abs(input[i]);
        if (absInput > envelope_) {
            envelope_ += attack_ * (absInput - envelope_);
        } else {
            envelope_ += release_ * (absInput - envelope_);
        }
        output[i] = input[i] * envelope_;
    }
}