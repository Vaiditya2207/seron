#include "seron-extension.hpp"
#include "builtin_icon.hpp"
#include "command-controller.hpp"
#include "services/script-command/script-command-service.hpp"
#include "extensions/seron/list-installed-extensions-command.hpp"
#include "qml/oauth-token-store-view-host.hpp"
#include "extensions/seron/report-bug-command.hpp"
#include "qml/builtin-icons-view-host.hpp"
#include "services/telemetry/telemetry-service.hpp"
#include "navigation-controller.hpp"
#include "config/config.hpp"
#include "qml/local-storage-view-host.hpp"
#include "open-about-command.hpp"
#include "refresh-apps-command.hpp"
#include "configure-fallback-command.hpp"
#include "extensions/seron/search-emoji-command.hpp"
#include "extensions/seron/seron-store-command.hpp"
#include "theme/colors.hpp"
#include "ui/image/url.hpp"
#include "builtin-url-command.hpp"
#include "single-view-command-context.hpp"
#include "seron.hpp"
#include <malloc.h>
#include <qpixmapcache.h>
#include <qsqlquery.h>
#include <qurlquery.h>

class OpenDocumentationCommand : public BuiltinUrlCommand {
  QString id() const override { return "documentation"; }
  QString name() const override { return "Open Online Documentation"; }
  QString description() const override { return "Navigate to the official seron documentation website."; }
  ImageURL iconUrl() const override {
    return ImageURL::builtin("book").setBackgroundTint(Omnicast::ACCENT_COLOR);
  }
  QUrl url(const ArgumentValues &values) const override { return Omnicast::DOC_URL; }
};

class OpenDiscordCommand : public BuiltinUrlCommand {
  QString id() const override { return "join-discord-server"; }
  QString name() const override { return "Join the Discord Server"; }
  QString description() const override { return "Open link to join the official Seron discord server."; }
  ImageURL iconUrl() const override {
    return ImageURL::builtin("discord").setBackgroundTint(Omnicast::ACCENT_COLOR);
  }
  std::vector<QString> keywords() const override { return {"help", "support"}; }
  QUrl url(const ArgumentValues &values) const override { return Omnicast::DISCORD_INVITE_LINK; }
};

class SponsorSeronCommand : public BuiltinUrlCommand {
  QString id() const override { return "sponsor"; }
  QString name() const override { return "Donate to Seron"; }
  QString description() const override { return "Open link to Seron's GitHub sponsor page"; }
  ImageURL iconUrl() const override { return ImageURL::builtin("heart").setFill(SemanticColor::Magenta); }
  std::vector<QString> keywords() const override { return {"sponsor", "donate"}; }
  QUrl url(const ArgumentValues &values) const override { return Omnicast::GH_SPONSOR_LINK; }
};

class OpenSeronConfig : public BuiltinCallbackCommand {
  QString id() const override { return "open-config-file"; }
  QString name() const override { return "Open Config File"; }
  QString description() const override { return "Open the main seron configuration file"; }
  ImageURL iconUrl() const override {
    return ImageURL::builtin("pencil").setBackgroundTint(Omnicast::ACCENT_COLOR);
  }

  void execute(CommandController *controller) const override {
    auto ctx = controller->context();
    ctx->services->appDb()->openTarget(ctx->services->config()->path().c_str());
    ctx->navigation->closeWindow();
    ctx->navigation->clearSearchText();
  }
};

class OpenDefaultSeronConfig : public BuiltinCallbackCommand {
  QString id() const override { return "open-default-config"; }
  QString name() const override { return "Open Default Config File"; }
  QString description() const override { return "Open the default seron configuration file"; }
  ImageURL iconUrl() const override {
    return ImageURL::builtin("pencil").setBackgroundTint(SemanticColor::Orange);
  }

  void execute(CommandController *controller) const override {
    auto ctx = controller->context();
    auto toast = ctx->services->toastService();
    auto path = Omnicast::runtimeDir() / "default-config.jsonc";

    QFile::remove(path);

    QFile file(path);
    auto configFile = QFile(":config.jsonc");

    if (!file.open(QIODevice::WriteOnly)) {
      toast->failure("Failed to open temporary file");
      return;
    }

    if (!configFile.open(QIODevice::ReadOnly)) {
      toast->failure("Failed to open default config file");
      return;
    }

    file.write(configFile.readAll());
    file.flush();
    file.setPermissions(QFileDevice::ReadOwner);
    ctx->services->appDb()->openTarget(file.fileName());
    ctx->navigation->closeWindow();
    ctx->navigation->clearSearchText();
  }
};

class PruneMemoryCommand : public BuiltinCallbackCommand {
  QString id() const override { return "prune-memory"; }
  QString name() const override { return "Prune Seron Memory Usage"; }
  QString description() const override {
    return "Try pruning seron's memory usage by clearing pixmap cache and calling malloc_trim(). Mostly "
           "provided for internal testing.";
  }
  ImageURL iconUrl() const override {
    return ImageURL::emoji("🥊").setBackgroundTint(Omnicast::ACCENT_COLOR);
  }

  void execute(CommandController *controller) const override {
    QPixmapCache::clear();
    malloc_trim(0);
    controller->context()->services->toastService()->success("Pruned 🥊");
  }
};

class OpenSettingsCommand : public BuiltinCallbackCommand {
  QString id() const override { return "settings"; }
  QString name() const override { return "Open Seron Settings"; }
  QString description() const override {
    return "Open the seron settings window, which is an independent floating window.";
  }
  ImageURL iconUrl() const override {
    return ImageURL::builtin("cog").setBackgroundTint(Omnicast::ACCENT_COLOR);
  }
  std::vector<QString> keywords() const override { return {"preferences"}; }

  void execute(CommandController *controller) const override {
    auto ctx = controller->context();

    ctx->navigation->closeWindow();
    ctx->settings->openWindow();
  }
};

class ReloadScriptDirectoriesCommand : public BuiltinCallbackCommand {
  QString id() const override { return "reload-scripts"; }
  QString name() const override { return "Reload Script Directories"; }
  QString description() const override { return "Reload script directories"; }
  ImageURL iconUrl() const override {
    return ImageURL(BuiltinIcon::Code).setBackgroundTint(Omnicast::ACCENT_COLOR);
  }

  void execute(CommandController *controller) const override {
    auto ctx = controller->context();

    ctx->services->scriptDb()->triggerScan();
    ctx->services->toastService()->success("New scan triggered, index will update shortly");
  }
};

class OpenKeybindSettingsCommand : public BuiltinCallbackCommand {
  QString id() const override { return "keybind-settings"; }
  QString name() const override { return "Open Seron Keybind Settings"; }
  QString description() const override { return "Open the seron keybind settings window"; }
  ImageURL iconUrl() const override {
    return ImageURL::builtin("keyboard").setBackgroundTint(Omnicast::ACCENT_COLOR);
  }

  void execute(CommandController *controller) const override {
    auto ctx = controller->context();

    ctx->navigation->closeWindow();
    ctx->settings->openTab("shortcuts");
  }
};

class ForgetTelemetryCommand : public BuiltinCallbackCommand {
  QString id() const override { return "forget-telemetry"; }
  QString name() const override { return "Forget Past Seron Telemetry"; }
  QString description() const override {
    return "Asks the seron server to anonymize telemetry data that was sent with your seron instance ID "
           "attached. The ID is only linked to your seron install, which has no direct relationship with "
           "your system.";
  }

  ImageURL iconUrl() const override {
    return ImageURL(BuiltinIcon::XMarkCircle).setBackgroundTint(Omnicast::ACCENT_COLOR);
  }

  bool isDefaultDisabled() const override { return true; }

  void execute(CommandController *controller) const override {
    auto ctx = controller->context();
    auto toast = ctx->services->toastService();
    auto telemetry = ctx->services->telemetry();
    auto config = ctx->services->config();

    ctx->navigation->showWindow();
    ctx->navigation->setSearchText(">"); // force to exit out of compact mode if it is enabled
    toast->dynamic("Processing...");
    telemetry->forget().then([toast, config](bool ok) {
      if (ok) {
        config->mergeWithUser({.telemetry = config::Partial<config::TelemetryConfig>{.systemInfo = false}});
        toast->success("Past telemetry was successfully detached from your seron user ID.");
      } else {
        toast->failure("Failed to forget past telemetry data");
      }
    });
  }
};

class OAuthTokenStoreCommand : public BuiltinViewCommand<OAuthTokenStoreViewHost> {
  QString id() const override { return "oauth-token-store"; }
  QString name() const override { return "Manage OAuth Token Sets"; }
  QString description() const override {
    return "Manage OAuth token sets that have been saved by extensions providing OAuth integrations.";
  }
  ImageURL iconUrl() const override {
    auto icon = ImageURL::builtin("key");
    icon.setBackgroundTint(Omnicast::ACCENT_COLOR);
    return icon;
  }
};

class IconBrowserCommand : public BuiltinViewCommand<BuiltinIconsViewHost> {
  QString id() const override { return "search-builtin-icons"; }
  QString name() const override { return "Search Builtin Icons"; }
  QString description() const override { return "Search Seron builtin set of icons"; }
  ImageURL iconUrl() const override {
    ImageURL icon{BuiltinIcon::Box};
    icon.setBackgroundTint(Omnicast::ACCENT_COLOR);
    return icon;
  }
};

class InspectLocalStorage : public BuiltinViewCommand<LocalStorageViewHost> {
  QString id() const override { return "inspect-local-storage"; }
  QString name() const override { return "Inspect Local Storage"; }
  bool isDefaultDisabled() const override { return true; }
  QString description() const override {
    return "Browse data stored in Seron's local storage. This includes data stored for builtin extensions "
           "as well as third-party extensions making use of the LocalStorage API.";
  }
  ImageURL iconUrl() const override {
    auto icon = ImageURL::builtin("coin");
    icon.setBackgroundTint(Omnicast::ACCENT_COLOR);
    return icon;
  }
};

SeronExtension::SeronExtension() {
  registerCommand<OpenDocumentationCommand>();
  registerCommand<OpenAboutCommand>();
  registerCommand<RefreshAppsCommand>();
  registerCommand<ManageFallbackCommand>();
  registerCommand<SearchEmojiCommand>();
  registerCommand<ReportSeronBugCommand>();
  registerCommand<OpenSettingsCommand>();
  registerCommand<SponsorSeronCommand>();
  registerCommand<OpenKeybindSettingsCommand>();
  registerCommand<SeronStoreCommand>();
  registerCommand<SeronListInstalledExtensionsCommand>();
  registerCommand<OAuthTokenStoreCommand>();
  registerCommand<OpenSeronConfig>();
  registerCommand<OpenDefaultSeronConfig>();
  registerCommand<InspectLocalStorage>();
  registerCommand<ReloadScriptDirectoriesCommand>();
  registerCommand<PruneMemoryCommand>();
  registerCommand<IconBrowserCommand>();
  registerCommand<ForgetTelemetryCommand>();
}
