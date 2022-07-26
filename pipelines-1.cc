#include "eventuals/just.h"
#include "eventuals/promisify.h"

// Simplifying with a using-directive; you probably will want to use
// using-declarations, e.g., 'using eventuals::Just'.
using namespace eventuals;

int main(int argc, char** argv) {
  auto e = []() {
    return Just(42);
  };

  int i = *e(); // BLOCKING!

  CHECK_EQ(42, i);

  return 0;
}
