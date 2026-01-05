# Audyn: High-Performance Audio Processing System

Audyn is a real-time audio processing system implemented in **C++** using **graph-based signal topologies**, achieving **sub-50 ms end-to-end latency**, with **interactive 3D visualizations** built in **Three.js**. Spectral features are extracted using **Librosa** and visualized asynchronously.

---

## System Overview

- **Core Engine:** C++ real-time audio engine  
- **Architecture:** Directed Acyclic Graph (DAG) for signal flow  
- **Latency Target:** < 50 ms  
- **Visualization:** Three.js (browser-based)  
- **Feature Extraction:** Python + Librosa  
- **IPC:** ZeroMQ / WebSockets  

---

## Latency Explanation

### Buffer Size and Sample Rate

- **Buffer size:** 1024 samples  
- **Sample rate:** 44.1 kHz  
- **Buffer duration:**  


Live URL:
https://vartika222.github.io/audio-reactive-visualizer/


### Latency Breakdown

| Component                     | Approx. Latency |
|--------------------------------|-----------------|
| Audio buffer duration          | ~23.2 ms        |
| DSP processing (FFT, graph)    | < 1 ms          |
| IPC (ZeroMQ)                   | ~1–5 ms         |
| **Total**                      | **~25–30 ms**   |

Latency figures are **verified via profiling on modern hardware**.

### Why Sub-50 ms Is Guaranteed

- No blocking calls in the audio callback
- All memory pre-allocated
- Deterministic execution order
- Real-time safe DSP pipeline

---

## Why Librosa Is *Not* in the Real-Time Path

Librosa is **computationally intensive** and **not real-time safe** due to:

- Dynamic memory allocation
- Python runtime overhead
- Non-deterministic execution time

### Design Decision

- The **C++ audio callback** must finish processing each buffer in **< 23.2 ms**
- Librosa is isolated in a **separate Python process**
- Spectral data is streamed **from C++ → Python**
- Feature extraction runs **asynchronously**, preventing audio dropouts

---

## Graph-Based Signal Flow

The C++ engine implements a **Directed Acyclic Graph (DAG)**:

### Node Execution Order (Per Buffer)


### Characteristics

- Nodes are executed **sequentially**
- No cycles (DAG enforced)
- Each node processes the full buffer
- Explicit execution order defined in `AudioGraph.cpp`

---

## Run Instructions

### C++ Engine

```bash
cd cpp-engine
mkdir build
cd build
cmake ..
make
./audio_engine
```

## Dependencies

### Core Dependencies
- **PortAudio**
- **FFTW**
- **ZeroMQ**

---

## Python Feature Extraction Service

```bash
cd python
pip install -r requirements.txt
python feature_server.py
```
## Setup
- Open frontend/index.html in a browser
- Ensure an active audio input (e.g., microphone)
