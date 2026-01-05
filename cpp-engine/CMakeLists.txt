cmake_minimum_required(VERSION 3.10)
project(AudioEngine)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PORTAUDIO REQUIRED portaudio-2.0)
pkg_check_modules(FFTW REQUIRED fftw3f)
pkg_check_modules(ZMQ REQUIRED libzmq)

include_directories(${PORTAUDIO_INCLUDE_DIRS} ${FFTW_INCLUDE_DIRS} ${ZMQ_INCLUDE_DIRS})
link_directories(${PORTAUDIO_LIBRARY_DIRS} ${FFTW_LIBRARY_DIRS} ${ZMQ_LIBRARY_DIRS})

add_executable(audio_engine main.cpp graph/AudioGraph.cpp nodes/GainNode.cpp nodes/FFTNode.cpp nodes/EnvelopeNode.cpp)
target_link_libraries(audio_engine ${PORTAUDIO_LIBRARIES} ${FFTW_LIBRARIES} ${ZMQ_LIBRARIES})