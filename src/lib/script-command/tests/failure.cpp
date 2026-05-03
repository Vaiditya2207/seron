#include <catch2/catch_test_macros.hpp>
#include "script-command.hpp"

TEST_CASE("Should fail if @seron and @raycast are mixed together") {
  const char *source = R"(#!/bin/bash -c hello

# Required parameters:
# @seron.schemaVersion 1
# @seron.title Search Flights
# @raycast.description "Hello world"

open "https://www.google.com/search?q=flights%20from%20$1%20to%20$2"
)";

  REQUIRE(!script_command::ScriptCommand::parse(source).has_value());
}

TEST_CASE("Should fail on any schema version that is not 1") {
  const char *source = R"(#!/bin/bash -c hello

# Required parameters:
# @seron.schemaVersion 2
# @seron.title Search Flights

open "https://www.google.com/search?q=flights%20from%20$1%20to%20$2"
)";

  REQUIRE(!script_command::ScriptCommand::parse(source).has_value());
}

TEST_CASE("Should fail if schema version is missing") {
  const char *source = R"(#!/bin/bash -c hello

# Required parameters:
# @seron.title Search Flights

open "https://www.google.com/search?q=flights%20from%20$1%20to%20$2"
)";

  REQUIRE(!script_command::ScriptCommand::parse(source).has_value());
}

TEST_CASE("Should fail if needsConfirmation is not a valid boolean") {
  const char *source = R"(#!/bin/bash -c hello
# Required parameters:
# @seron.schemaVersion 1
# @seron.title Search Flights
# @seron.needsConfirmation fulse

open "https://www.google.com/search?q=flights%20from%20$1%20to%20$2"
)";
  REQUIRE(!script_command::ScriptCommand::parse(source).has_value());
}

TEST_CASE("Should fail on unknown mode") {
  const char *source = R"(#!/bin/bash -c hello
# Required parameters:
# @seron.schemaVersion 1
# @seron.title Search Flights
# @seron.mode invalid_mode

open "https://www.google.com/search?q=flights%20from%20$1%20to%20$2"
)";

  REQUIRE(!script_command::ScriptCommand::parse(source).has_value());
}
