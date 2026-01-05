#include "AudioEngine.h"
#include <zmq.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include <cstring>

int main() {
    const int sampleRate = 44100;
    const int bufferSize = 1024;  // ~23.2ms latency
    AudioEngine engine(sampleRate, bufferSize);

    // Set up graph: Gain -> Envelope -> FFT
    auto gain = std::make_unique<GainNode>(1.0f);
    auto envelope = std::make_unique<EnvelopeNode>(0.01f, 0.01f);
    auto fft = std::make_unique<FFTNode>(bufferSize);
    engine.graph_->addNode(std::move(gain));
    engine.graph_->addNode(std::move(envelope));
    engine.graph_->addNode(std::move(fft));

    // ZMQ publisher for spectral data
    zmq::context_t context(1);
    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.bind("tcp://*:5555");

    // Thread to send spectral data after each buffer
    std::thread sender([&]() {
        while (true) {
            // Wait for processed buffer (simplified; in real impl, use a queue)
            std::this_thread::sleep_for(std::chrono::milliseconds(20));  // Sync with buffer rate
            const auto& spectral = engine.graph_->getSpectralData();
            if (!spectral.empty()) {
                zmq::message_t msg(spectral.size() * sizeof(float));
                std::memcpy(msg.data(), spectral.data(), msg.size());
                publisher.send(msg, zmq::send_flags::none);
            }
        }
    });

    engine.start();
    std::cout << "Audio engine running. Press Enter to stop." << std::endl;
    std::cin.get();
    engine.stop();
    sender.join();
    return 0;
}