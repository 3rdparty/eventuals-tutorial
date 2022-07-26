#include "eventuals/compose.h"
#include "eventuals/generator.h"
#include "eventuals/iterate.h"
#include "eventuals/map.h"
#include "eventuals/promisify.h"
#include "eventuals/reduce.h"
#include "eventuals/then.h"

using namespace eventuals;

Generator::Of<std::string> SomeFunction() {
  return []() {
    return Iterate({"hello", " ", "world", "!"})
        >> Map([](std::string&& s) {
             s[0] = std::toupper(s[0]);
             return std::move(s);
           });
  };
}

int main(int argc, char** argv) {
  auto e = []() {
    return SomeFunction()
        >> Reduce(
               /* result = */ std::string(),
               [](auto& result) {
                 return Then([&](auto&& value) {
                   result += value;
                   return true;
                 });
               });
  };

  CHECK_EQ("Hello World!", *e());

  return 0;
}
