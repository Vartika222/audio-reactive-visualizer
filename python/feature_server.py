import zmq
import librosa
import numpy as np
import json
import asyncio
import websockets

async def feature_processor(websocket, path):
    context = zmq.Context()
    subscriber = context.socket(zmq.SUB)
    subscriber.connect("tcp://localhost:5555")
    subscriber.setsockopt_string(zmq.SUBSCRIBE, "")

    while True:
        try:
            msg = subscriber.recv()
            spectral = np.frombuffer(msg, dtype=np.float32)
            # Use librosa on spectral data
            mfccs = librosa.feature.mfcc(S=spectral.reshape(1, -1), n_mfcc=13).flatten()
            centroid = librosa.feature.spectral_centroid(S=spectral.reshape(1, -1))[0][0]
            rms = librosa.feature.rms(S=spectral.reshape(1, -1))[0][0]
            data = {
                "mfccs": mfccs.tolist(),
                "centroid": float(centroid),
                "rms": float(rms)
            }
            await websocket.send(json.dumps(data))
        except Exception as e:
            print(f"Error: {e}")

start_server = websockets.serve(feature_processor, "localhost", 8765)
asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()