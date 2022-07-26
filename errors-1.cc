#include "eventuals/compose.h"
#include "eventuals/just.h"
#include "eventuals/promisify.h"
#include "eventuals/raise.h"

using namespace eventuals;

int main(int argc, char** argv) {
  auto e = []() {
    return Just("hello")
        >> Raise(std::runtime_error("Oh no!"))
        >> Just("world");
  };

  try {
    *e();
    std::abort();
  } catch (const std::exception& e) {
    CHECK_STREQ("Oh no!", e.what());
  }

  return 0;
}
