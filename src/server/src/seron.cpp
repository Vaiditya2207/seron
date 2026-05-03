#include "seron.hpp"
#include "xdgpp/env/env.hpp"
#include <qlogging.h>
#include <qprocess.h>
#include <QProcessEnvironment>
#include <ranges>
#include <set>

namespace fs = std::filesystem;

fs::path Omnicast::runtimeDir() {
  fs::path const osRundir(QStandardPaths::writableLocation(QStandardPaths::RuntimeLocation).toStdString());

  return osRundir / "seron";
}

fs::path Omnicast::dataDir() { return xdgpp::dataHome() / "seron"; }

fs::path Omnicast::stateDir() { return xdgpp::stateHome() / "seron"; }

fs::path Omnicast::configDir() { return xdgpp::configHome() / "seron"; }

fs::path Omnicast::commandSocketPath() { return runtimeDir() / "seron.sock"; }
fs::path Omnicast::pidFile() { return runtimeDir() / "seron.pid"; }

void Omnicast::ensureDirectories() {
  for (auto const &dir : {runtimeDir(), dataDir(), stateDir(), configDir()}) {
    std::error_code ec;
    fs::create_directories(dir, ec);
    if (ec) { qWarning() << "Failed to create directory" << dir.c_str() << ec.message(); }
  }
}

std::vector<fs::path> Omnicast::systemPaths() {
  const char *path = getenv("PATH");

  if (!path) return {};

  std::set<fs::path> seen;
  std::vector<fs::path> paths;

  for (const auto &part : std::views::split(std::string_view(path), std::string_view(":"))) {
    fs::path const path = std::string_view(part.begin(), part.end());

    if (seen.contains(path)) continue;

    seen.insert(path);
    paths.emplace_back(path);
  }

  return paths;
}
