#ifndef AUDIO_GRAPH_H
#define AUDIO_GRAPH_H

#include <vector>
#include <memory>
#include "AudioNode.h"

class AudioGraph {
public:
    void addNode(std::unique_ptr<AudioNode> node);
    void processBuffer(const std::vector<float>& input, std::vector<float>& output);
    const std::vector<float>& getSpectralData() const;  // Returns FFT magnitudes

private:
    std::vector<std::unique_ptr<AudioNode>> nodes_;
    std::vector<float> spectralData_;  // Cached from FFTNode
};

#endif