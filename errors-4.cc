#include "eventuals/expected.h"
#include "eventuals/finally.h"
#include "eventuals/just.h"
#include "eventuals/promisify.h"
#include "eventuals/raise.h"

using namespace eventuals;

int main(int argc, char** argv) {
  auto e = []() {
    return Just("hello")
        >> Raise(std::runtime_error("Oh no!"))
        >> Finally([](expected<const char*, std::exception_ptr> expected) {
             CHECK(!expected.has_value());
             return "world";
           });
  };

  CHECK_EQ("world", *e());

  return 0;
}
