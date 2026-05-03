#include <catch2/catch_test_macros.hpp>
#include "script-command.hpp"

TEST_CASE("Hash (#) comments are parsed correctly") {
  const char *source = R"(#!/bin/bash
# @seron.schemaVersion 1
# @seron.title Hash Comment Test
# @seron.mode compact
echo "Hello"
)";
  auto result = script_command::ScriptCommand::parse(source);
  REQUIRE(result.has_value());
  REQUIRE(result->title == "Hash Comment Test");
  REQUIRE(result->mode == script_command::OutputMode::Compact);
}

TEST_CASE("Double slash (//) comments are parsed correctly") {
  const char *source = R"(#!/usr/bin/env node
// @seron.schemaVersion 1
// @seron.title JS Comment Test
// @seron.mode compact
console.log("Hello");
)";
  auto result = script_command::ScriptCommand::parse(source);
  REQUIRE(result.has_value());
  REQUIRE(result->title == "JS Comment Test");
  REQUIRE(result->mode == script_command::OutputMode::Compact);
}

TEST_CASE("Double dash (--) comments are parsed correctly") {
  const char *source = R"(#!/usr/bin/env lua
-- @seron.schemaVersion 1
-- @seron.title Lua Comment Test
-- @seron.mode compact
print("Hello")
)";
  auto result = script_command::ScriptCommand::parse(source);
  REQUIRE(result.has_value());
  REQUIRE(result->title == "Lua Comment Test");
  REQUIRE(result->mode == script_command::OutputMode::Compact);
}

TEST_CASE("Lua script with all metadata fields using -- comments") {
  const char *source = R"(#!/usr/bin/env lua
-- @seron.schemaVersion 1
-- @seron.title Full Lua Test
-- @seron.mode inline
-- @seron.refreshTime 30s
-- @seron.author Test Author
-- @seron.description A test Lua script
print("Hello World")
)";
  auto result = script_command::ScriptCommand::parse(source);
  REQUIRE(result.has_value());
  REQUIRE(result->title == "Full Lua Test");
  REQUIRE(result->mode == script_command::OutputMode::Inline);
  REQUIRE(result->refreshTime.has_value());
  REQUIRE(result->refreshTime.value() == 30);
  REQUIRE(result->author.has_value());
  REQUIRE(result->author.value() == "Test Author");
  REQUIRE(result->description.has_value());
  REQUIRE(result->description.value() == "A test Lua script");
}

TEST_CASE("Mixed comment styles should work (different lines)") {
  const char *source = R"(#!/usr/bin/env lua
-- @seron.schemaVersion 1
-- @seron.title Mixed Test
# Some other comment (not a metadata comment)
print("Hello")
)";
  auto result = script_command::ScriptCommand::parse(source);
  REQUIRE(result.has_value());
  REQUIRE(result->title == "Mixed Test");
}

TEST_CASE("Double dash should not conflict with command arguments") {
  const char *source = R"(#!/bin/bash
# @seron.schemaVersion 1
# @seron.title Arg Test
echo "test" -- this is a regular comment in the code
)";
  auto result = script_command::ScriptCommand::parse(source);
  REQUIRE(result.has_value());
  REQUIRE(result->title == "Arg Test");
}

TEST_CASE("Comments with leading whitespace and -- marker") {
  const char *source = R"(#!/usr/bin/env lua
  -- @seron.schemaVersion 1
  -- @seron.title Whitespace Test
  -- @seron.mode compact
print("Hello")
)";
  auto result = script_command::ScriptCommand::parse(source);
  REQUIRE(result.has_value());
  REQUIRE(result->title == "Whitespace Test");
  REQUIRE(result->mode == script_command::OutputMode::Compact);
}

TEST_CASE("TypeScript with // comments") {
  const char *source = R"(#!/usr/bin/env ts-node
// @seron.schemaVersion 1
// @seron.title TypeScript Test
// @seron.mode terminal
// @seron.keywords ["typescript", "test"]
console.log("Hello from TypeScript");
)";
  auto result = script_command::ScriptCommand::parse(source);
  REQUIRE(result.has_value());
  REQUIRE(result->title == "TypeScript Test");
  REQUIRE(result->mode == script_command::OutputMode::Terminal);
  REQUIRE(result->keywords.size() == 2);
  REQUIRE(result->keywords[0] == "typescript");
  REQUIRE(result->keywords[1] == "test");
}

TEST_CASE("Go with // comments") {
  const char *source = R"(#!/usr/bin/env go run
// @seron.schemaVersion 1
// @seron.title Go Test
// @seron.mode compact
package main
import "fmt"
func main() { fmt.Println("Hello") }
)";
  auto result = script_command::ScriptCommand::parse(source);
  REQUIRE(result.has_value());
  REQUIRE(result->title == "Go Test");
  REQUIRE(result->mode == script_command::OutputMode::Compact);
}

TEST_CASE("PHP with // comments after <?php tag") {
  const char *source = R"(#!/usr/bin/env php
<?php
// @seron.schemaVersion 1
// @seron.title PHP Test
// @seron.mode compact
echo "Hello from PHP\n";
)";
  auto result = script_command::ScriptCommand::parse(source);
  REQUIRE(result.has_value());
  REQUIRE(result->title == "PHP Test");
  REQUIRE(result->mode == script_command::OutputMode::Compact);
}

TEST_CASE("Semicolon (;) comments are parsed correctly") {
  const char *source = R"(#!/usr/bin/env sbcl --script
; @seron.schemaVersion 1
; @seron.title Semicolon Comment Test
; @seron.mode compact
)";
  auto result = script_command::ScriptCommand::parse(source);
  REQUIRE(result.has_value());
  REQUIRE(result->title == "Semicolon Comment Test");
  REQUIRE(result->mode == script_command::OutputMode::Compact);
}
