#pragma once
#include "qml/store-intro-view-host.hpp"
#include "qml/seron-store-view-host.hpp"
#include "single-view-command-context.hpp"
#include "seron.hpp"

class SeronStoreCommand : public BuiltinCallbackCommand {
  QString id() const override { return "store"; }
  QString name() const override { return "Extension Store"; }
  QString description() const override { return "Install extensions from the Seron store"; }
  QString extensionId() const override { return "seron"; }
  QString commandId() const override { return "store"; }
  ImageURL iconUrl() const override {
    auto icon = ImageURL::builtin("cart");
    icon.setBackgroundTint(Omnicast::ACCENT_COLOR);
    return icon;
  }
  std::vector<Preference> preferences() const override {
    auto alwaysShowIntro = Preference::makeCheckbox("alwaysShowIntro", "Always show intro");
    alwaysShowIntro.setDefaultValue(false);
    return {alwaysShowIntro};
  }

  void execute(CommandController *ctrl) const override {
    auto ctx = ctrl->context();
    auto alwaysShowIntro = ctrl->preferenceValues().value("alwaysShowIntro").toBool(false);

    if (alwaysShowIntro || !ctrl->storage().getItem("introCompleted").toBool()) {
      static const QString INTRO = QStringLiteral(R"(
# Welcome to the seron extension store

The seron extension store features community-built extensions that have been approved by our core contributors.

Every extension listed here has its source code available in the [seronhq/extensions](https://github.com/seronhq/extensions) repository.

If you're looking to build your own extension, take a look at the [documentation](https://docs.seron.com/extensions/introduction). If you think your extension would be a good fit for the store, feel free to submit it!
)");
      auto icon = ImageURL::builtin("cart");
      icon.setBackgroundTint(Omnicast::ACCENT_COLOR);
      auto storage = ctrl->storage();
      ctx->navigation->pushView(
          new StoreIntroViewHost(INTRO, icon, "Continue to store", [storage, ctx]() mutable {
            storage.setItem("introCompleted", true);
            ctx->navigation->replaceView<SeronStoreViewHost>();
          }));
      return;
    }

    ctx->navigation->pushView(new SeronStoreViewHost);
  }
};
