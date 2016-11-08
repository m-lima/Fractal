#ifdef _WIN32
// Force high performance GPU
extern "C" {
  // NVidia
  __declspec(dllexport) int NvOptimusEnablement = 1;

  // AMD
  __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif

int main() {
  return 0;
}