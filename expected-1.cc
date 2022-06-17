#include "eventuals/expected.h"
#include "eventuals/then.h"

using namespace eventuals;

expected<int> SomeFunction(int i) {
  if (i > 100) {
    return make_unexpected("> 100");
  } else {
    return i; // return expected(i);
  }
}

int main(int argc, char** argv) {
  CHECK_EQ("42", *(SomeFunction(42) | Then([](int i) { return std::to_string(i); })));

  return 0;
}
