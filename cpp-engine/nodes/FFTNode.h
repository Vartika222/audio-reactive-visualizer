#ifndef FFT_NODE_H
#define FFT_NODE_H

#include "AudioNode.h"
#include <fftw3.h>
#include <vector>

class FFTNode : public AudioNode {
public:
    FFTNode(int bufferSize);
    ~FFTNode();
    void process(const std::vector<float>& input, std::vector<float>& output) override;

private:
    int bufferSize_;
    fftwf_plan plan_;
    float* in_;
    fftwf_complex* out_;
};

#endif