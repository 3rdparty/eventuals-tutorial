#include "eventuals/just.h"
#include "eventuals/then.h"

using namespace eventuals;

int main(int argc, char** argv) {
  auto e = []() {
    return Just(42)
        | Then([](int i) {
             return std::to_string(i);
           });
  };

  CHECK_EQ("42", *e());

  return 0;
}
