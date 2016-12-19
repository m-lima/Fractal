#version 410

// Call with "glDrawArrays(GL_TRIANGLE_STRIP, 0, 4)"

const vec2 vertices[4] = {
  vec2(-1.0, 1.0), vec2(1.0, 1.0), vec2(1.0, -1.0), vec2(-1.0, -1.0)
  };

void main() {
  gl_Position = vec4(vtx[gl_VertexID], 0.0, 1.0);
}
