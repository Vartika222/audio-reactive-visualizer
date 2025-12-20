Audio-Reactive Circular Visualizer

A real-time, audio-reactive visual experiment built with p5.js and p5.sound, exploring how simple frequency-band energy can drive dynamic, organic motion.

This project is intentionally scoped as a visual prototype — a foundation for deeper music analysis and graph-driven visual systems planned in future iterations.

Live Demo

Live URL:
https://vartika222.github.io/audio-reactive-visualizer/

Click anywhere on the page to start the audio (required by browser audio policies).

What This Project Does

Uses FFT energy bands (bass, treble) to modulate geometry in real time

Renders a circular node system that:

Pulses with low-frequency energy

Responds to transients via contraction and bloom

Evolves smoothly using noise and phase offsets

Maintains stable performance at ~60 FPS on modern browsers

This is a reactive visualization, not a precomputed animation.

Current Technical Scope
Implemented

Real-time FFT analysis via p5.FFT

Energy-based transient detection

Time-based decay and smoothing

Resize-safe canvas and layout

Deterministic rendering loop

Not Yet Implemented (Planned)

Beat/onset detection beyond simple energy deltas

Full spectrum or waveform visualizations

Musical feature extraction (MFCCs, spectral centroid, flux)

Graph-based music representation

Section or motif awareness

The project explicitly avoids over-claiming advanced audio analysis at this stage.

Tech Stack

p5.js

p5.sound

JavaScript (ES6)

HTML5 Canvas

No backend. No build step.

Project Structure
audio-reactive-visualizer/
├── index.html
├── sketch.js
├── p5.min.js
├── p5.sound.min.js
├── assets/
│   └── sample.mp3
└── README.md

How to Run Locally

Because of browser audio restrictions, run this via a local server.

Option 1: VS Code Live Server

Open folder in VS Code

Right-click index.html → Open with Live Server

Option 2: Python
python3 -m http.server


Then open:

http://localhost:8000


Click anywhere to start audio playback.

Design Philosophy

This project prioritizes:

Visual clarity over feature density

Intentional motion over randomness

Honest technical scope

The current implementation focuses on building a strong visual language before layering deeper musical intelligence on top.

Roadmap

v0.1 — Visual Prototype (current)

Audio-reactive circular system

Energy-driven motion and decay

v0.2 — Rhythmic Intelligence

Beat and onset detection

Adaptive thresholds

Section-aware transitions

v0.3 — Musical Feature Layer

Spectral features

Timbre-driven visual modulation

Offline + real-time analysis modes

v0.4 — Graph-Driven Music Visuals

Nodes as musical entities

Edges as temporal or harmonic relationships

Dynamic graph deformation

Versioning

Current version: v0.1 — Audio-Reactive Visual Prototype

This repository follows incremental, transparent versioning as features evolve.

Author

Vartika
GitHub: https://github.com/Vartika222
