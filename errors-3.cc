#include "eventuals/catch.h"
#include "eventuals/just.h"
#include "eventuals/promisify.h"
#include "eventuals/raise.h"

using namespace eventuals;

int main(int argc, char** argv) {
  auto e = []() {
    return Just("hello")
        >> Raise(std::runtime_error("Oh no!"))
        >> Catch()
               .raised<std::exception>([](std::exception&& e) {
                 CHECK_STREQ("Oh no!", e.what());
                 return Just("world");
               });
  };

  CHECK_EQ("world", *e());

  return 0;
}
