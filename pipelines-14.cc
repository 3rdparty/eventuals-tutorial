#include <string>

#include "eventuals/closure.h"
#include "eventuals/iterate.h"
#include "eventuals/let.h"
#include "eventuals/loop.h"
#include "eventuals/map.h"
#include "eventuals/promisify.h"

using namespace eventuals;

int main(int argc, char** argv) {
  auto e = []() {
    return Closure([result = std::string()]() mutable {
      return Iterate({"hello", " ", "world", "!"})
          >> Map([&result](std::string&& s) {
               s[0] = std::toupper(s[0]);
               result += std::move(s);
             })
          >> Loop()
          >> Then([&result]() {
               return std::move(result);
             })
          >> Then(Let([](std::string& result) mutable {
               return Then([&result]() {
                 return std::move(result);
               });
             }));
    });
  };

  CHECK_EQ("Hello World!", *e());

  return 0;
}
