#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include <portaudio.h>
#include <vector>
#include <memory>
#include "AudioGraph.h"

class AudioEngine {
public:
    AudioEngine(int sampleRate, int bufferSize);
    ~AudioEngine();
    void start();
    void stop();

private:
    int sampleRate_;
    int bufferSize_;
    PaStream* stream_;
    std::unique_ptr<AudioGraph> graph_;
    std::vector<float> inputBuffer_;
    std::vector<float> outputBuffer_;

    static int audioCallback(const void* inputBuffer, void* outputBuffer,
                             unsigned long framesPerBuffer,
                             const PaStreamCallbackTimeInfo* timeInfo,
                             PaStreamCallbackFlags statusFlags,
                             void* userData);
};

#endif