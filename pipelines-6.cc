#include "eventuals/just.h"
#include "eventuals/promisify.h"
#include "eventuals/then.h"

using namespace eventuals;

int main(int argc, char** argv) {
  auto e = []() {
    return Just(42)
        >> Then([](int /* i */) {});
  };

  static_assert(std::is_void_v<decltype(*e())>);

  return 0;
}
