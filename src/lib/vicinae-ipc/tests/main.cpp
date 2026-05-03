#include <catch2/catch_test_macros.hpp>
#include <ostream>
#include "seron-ipc/client.hpp"
#include "seron-ipc/ipc.hpp"

TEST_CASE("test") {
  auto client = ipc::Client<ipc::CliSchema>::make().value();

  auto err = client.request<ipc::Deeplink>({.url = "seron://toggle"});

  REQUIRE(true);
}
