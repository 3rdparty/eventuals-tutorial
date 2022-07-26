#include "eventuals/just.h"
#include "eventuals/promisify.h"
#include "eventuals/task.h"
#include "eventuals/then.h"

using namespace eventuals;

Task::Of<std::string>::With<int, std::string> SomeFunction() {
  return Task::Of<std::string>::With<int, std::string>(
      42,
      "hello",
      [](int& i, std::string& s) {
        return Then([&]() {
          return Just(std::to_string(i) + " " + s);
        });
      });
}

int main(int argc, char** argv) {
  CHECK_EQ("42 hello", *SomeFunction());

  return 0;
}
