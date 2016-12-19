#version 410

out vec4 FragColor;

uniform vec4 uBounds;

const unsigned int maxIterations = 10;

void main() {

  // f(z)n+1 = f(z)n^2 + c;

  // C
  float ca = glFragCoords.x * uBounds.z + uBounds.x;
  float cb = glFragCoords.y * uBounds.w + uBounds.y;

  // f(z)
  float za = 0.0;
  float zb = 0.0;

  // Temp
  float aa;
  float abi;
  float bb;

  for (int i = 0; i < maxIterations; i++) {
    // c = a + bi
    // c^2 = a^2 + 2abi + b^2

    aa = za * za;
    abi = 2 * za * zb;
    bb = zb * zb;

    if (aa + bb > 4) {
      break;
    }

    za = ca + aa - bb;
    zb = cb + abi;
  }

  if (i < maxIterations) {
    FragColor = vec4(0.0, 0.0, 0.0, 1.0);
  } else {
    float factor = sqrt((float) i / (float)maxIterations);
    FragColor = vec4(1 - factor, 1 - factor, factor, 1.0);
  }
}
