#include <string>

#include "eventuals/just.h"
#include "eventuals/promisify.h"
#include "eventuals/then.h"

using namespace eventuals;

// NOTE: need to use 'auto' return type because it's difficult to
// "spell" an eventuals type, more on this later.
auto SomeFunction(const std::string& s) {
  return Just(s.length());
}

int main(int argc, char** argv) {
  auto e = []() {
    return Just("hello")
        >> Then([](std::string&& s1) {
             return SomeFunction(s1)
                 >> Then([s1](int length) {
                      return std::move(s1) + " has "
                          + std::to_string(length) + " characters";
                    });
           });
  };

  CHECK_EQ("hello has 5 characters", *e());

  return 0;
}
