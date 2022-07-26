#include <string>

#include "eventuals/iterate.h"
#include "eventuals/loop.h"
#include "eventuals/map.h"
#include "eventuals/promisify.h"

using namespace eventuals;

int main(int argc, char** argv) {
  std::string result;
  auto e = [&result]() {
    return Iterate({"hello", " ", "world", "!"})
        >> Map([&result](std::string&& s) {
             s[0] = std::toupper(s[0]);
             result += std::move(s);
           })
        >> Loop();
  };

  *e();

  CHECK_EQ("Hello World!", result);

  return 0;
}
