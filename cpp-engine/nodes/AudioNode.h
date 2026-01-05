#ifndef AUDIO_NODE_H
#define AUDIO_NODE_H

#include <vector>

class AudioNode {
public:
    virtual ~AudioNode() = default;
    virtual void process(const std::vector<float>& input, std::vector<float>& output) = 0;
};

#endif