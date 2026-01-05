let song;
let fft;
let started = false;

const NODES = 48;
let nodes = [];
let baseRadius;

let lastBass = 0;
let dropEnergy = 0;

let bassHistory = [];
const HISTORY_LENGTH = 60;


const DEPTH_LAYERS = [
  { scale: 1.0, alpha: 220, lag: 0 },
  { scale: 1.15, alpha: 120, lag: 8 },
  { scale: 1.3, alpha: 60, lag: 16 }
];




function preload() {
  console.log("preload started");

  song = loadSound(
    "assets/sample.mp3",
    () => console.log("audio loaded successfully"),
    (err) => console.error("audio load error:", err)
  );
}

function setup() {
  createCanvas(windowWidth, windowHeight);
  fft = new p5.FFT();

  baseRadius = min(width, height) * 0.3;

  for (let i = 0; i < NODES; i++) {
    let angle = (TWO_PI / NODES) * i;
    nodes.push({
      angle,
      phase: i * 0.3
    });
  }

  background(5, 5, 15);
}

function mousePressed() {
  if (!started) {
    userStartAudio();
    song.loop();
    started = true;
  }
}
blendMode(ADD);

function draw() {
  if (!started) return;

  background(5, 5, 15, 25);

  translate(width / 2, height / 2);

  let bass = fft.getEnergy("bass");
  let treble = fft.getEnergy("treble");

let bassDelta = bass - lastBass;
lastBass = bass;

if (bassDelta > 40) {
  dropEnergy = 1;
}
dropEnergy *= 0.9; // decay

let contraction = lerp(1.0, 0.65, dropEnergy);
scale(contraction);



  rotate(frameCount * 0.0005);

  // Draw edges
  stroke(180, 80);
  strokeWeight(1.2);
  noFill();

  beginShape();
  for (let n of nodes) {
    let pulse = sin(frameCount * 0.05 + n.phase);
    let noiseOffset = noise(
      cos(n.angle) + frameCount * 0.01,
      sin(n.angle)
    );
    let bloom = dropEnergy * 120;
    let r =
    baseRadius +
    pulse * bass * 0.4 +
    noiseOffset * 40 +
    bloom;
    

    let x = cos(n.angle) * r;
    let y = sin(n.angle) * r;
    vertex(x, y);
  }
  endShape(CLOSE);

  // Draw nodes
  for (let n of nodes) {
    let pulse = sin(frameCount * 0.05 + n.phase);
    let r = baseRadius + pulse * bass * 0.4;

    let x = cos(n.angle) * r;
    let y = sin(n.angle) * r;

    let size = map(treble, 0, 255, 6, 20);

    let flash = dropEnergy * 80;

fill(
  map(bass, 0, 255, 120, 255) + flash,
  map(pulse, -1, 1, 50, 150),
  map(treble, 0, 255, 180, 255),
  220
);

    

    noStroke();
    ellipse(x, y, size);
  }
}



