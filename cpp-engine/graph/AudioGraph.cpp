#include "AudioGraph.h"
#include <algorithm>  // For std::copy

void AudioGraph::addNode(std::unique_ptr<AudioNode> node) {
    nodes_.push_back(std::move(node));
}

void AudioGraph::processBuffer(const std::vector<float>& input, std::vector<float>& output) {
    std::vector<float> current = input;
    for (auto& node : nodes_) {
        node->process(current, output);
        current = output;  // Chain output to next node's input
    }
    // Assume last node is FFTNode; cache its spectral data
    if (!nodes_.empty() && dynamic_cast<FFTNode*>(nodes_.back().get())) {
        spectralData_ = output;  // FFTNode outputs magnitudes
    }
}

const std::vector<float>& AudioGraph::getSpectralData() const {
    return spectralData_;
}