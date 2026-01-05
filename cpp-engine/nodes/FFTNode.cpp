#include "FFTNode.h"
#include <cmath>

FFTNode::FFTNode(int bufferSize) : bufferSize_(bufferSize) {
    in_ = fftwf_alloc_real(bufferSize_);
    out_ = fftwf_alloc_complex(bufferSize_ / 2 + 1);
    plan_ = fftwf_plan_dft_r2c_1d(bufferSize_, in_, out_, FFTW_MEASURE);
}

FFTNode::~FFTNode() {
    fftwf_destroy_plan(plan_);
    fftwf_free(in_);
    fftwf_free(out_);
}

void FFTNode::process(const std::vector<float>& input, std::vector<float>& output) {
    // Copy input to FFT buffer
    for (int i = 0; i < bufferSize_; ++i) {
        in_[i] = input[i];
    }
    fftwf_execute(plan_);
    // Output magnitudes (first half of spectrum)
    output.resize(bufferSize_ / 2);
    for (int i = 0; i < bufferSize_ / 2; ++i) {
        output[i] = std::sqrt(out_[i][0] * out_[i][0] + out_[i][1] * out_[i][1]);
    }
}