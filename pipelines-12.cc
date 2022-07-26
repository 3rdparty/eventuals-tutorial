#include <string>

#include "eventuals/head.h"
#include "eventuals/iterate.h"
#include "eventuals/map.h"
#include "eventuals/promisify.h"

using namespace eventuals;

int main(int argc, char** argv) {
  auto e = []() {
    return Iterate({"hello", " ", "world", "!"})
        >> Map([](std::string&& s) {
             s[0] = std::toupper(s[0]);
             return std::move(s);
           })
        >> Head();
  };

  CHECK_EQ("Hello", *e());

  return 0;
}
