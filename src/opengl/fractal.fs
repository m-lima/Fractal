#version 410

out vec4 FragColor;

uniform vec4 uBounds;

const float maxIterations = 100.0;

void main() {

  // f(z)n+1 = f(z)n^2 + c;

  // C
  float ca = gl_FragCoord.x * uBounds.z + uBounds.x;
  float cb = gl_FragCoord.y * uBounds.w + uBounds.y;

  // f(z)
  float za = 0.0;
  float zb = 0.0;

  // Temp
  float aa;
  float abi;
  float bb;
  float i = 0;

  for (i = 0; i < maxIterations; i++) {
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
    float factor = pow((i / maxIterations), 0.25f);
    FragColor = vec4(1 - factor, factor, factor, 1.0);
  } else {
    FragColor = vec4(0.0, 0.0, 0.0, 1.0);
  }
}
