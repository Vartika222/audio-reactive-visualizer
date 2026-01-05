const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
const renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight);
document.getElementById('container').appendChild(renderer.domElement);

const geometry = new THREE.SphereGeometry(1, 32, 32);
const material = new THREE.MeshBasicMaterial({ color: 0x00ff00 });
const sphere = new THREE.Mesh(geometry, material);
scene.add(sphere);
camera.position.z = 5;

const ws = new WebSocket('ws://localhost:8765');

ws.onmessage = function(event) {
    const data = JSON.parse(event.data);
    // Map features
    sphere.scale.setScalar(data.rms * 10);  // Scale by RMS
    material.color.setHSL(data.centroid / 10000, 1, 0.5);  // Hue by centroid
    // Deform geometry by MFCCs (simplified: displace vertices)
    const positions = geometry.attributes.position.array;
    for (let i = 0; i < positions.length; i += 3) {
        positions[i] += data.mfccs[i % data.mfccs.length] * 0.01;
    }
    geometry.attributes.position.needsUpdate = true;
};

function animate() {
    requestAnimationFrame(animate);
    renderer.render(scene, camera);
}
animate();