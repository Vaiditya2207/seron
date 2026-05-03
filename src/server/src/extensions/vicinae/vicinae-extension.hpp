#include "command-database.hpp"
#include "ui/image/url.hpp"
#include "seron.hpp"
#include <qsqlquery.h>
#include <qurlquery.h>

class SeronExtension : public BuiltinCommandRepository {
  QString id() const override { return "core"; }
  QString displayName() const override { return "Seron"; }
  QString description() const override { return "General seron-related commands."; }
  ImageURL iconUrl() const override {
    return ImageURL::builtin("seron").setBackgroundTint(Omnicast::ACCENT_COLOR);
  }

public:
  SeronExtension();
};
