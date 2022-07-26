#include "eventuals/if.h"
#include "eventuals/just.h"
#include "eventuals/let.h"
#include "eventuals/promisify.h"
#include "eventuals/task.h"
#include "eventuals/then.h"

using namespace eventuals;

Task::From<int>::To<std::string>::Raises<std::overflow_error> SomeFunction() {
  return []() {
    return Then(Let([](int& i) {
      return If(i > 100)
          .yes([]() {
            return Raise(std::overflow_error("> 100"));
          })
          .no([&i]() {
            return Just(std::to_string(i));
          });
    }));
  };
}

int main(int argc, char** argv) {
  CHECK_EQ("42", *(Just(42) >> SomeFunction()));

  return 0;
}
