#pragma once
#include <string>
#include <vector>
#include "fuzzy-section.hpp"
#include "fuzzy/fuzzy-searchable.hpp"
#include "services/extension-store/seron-store.hpp"

class ExtensionRegistry;

struct SeronStoreEntry {
  SeronStore::Extension extension;
  bool installed = false;
};

template <> struct fuzzy::FuzzySearchable<SeronStoreEntry> {
  static int score(const SeronStoreEntry &entry, std::string_view query) {
    auto title = entry.extension.title.toStdString();
    auto author = entry.extension.author.name.toStdString();
    auto desc = entry.extension.description.toStdString();
    return fuzzy::scoreWeighted({{title, 1.0}, {author, 0.5}, {desc, 0.3}}, query);
  }
};

class SeronStoreSection : public FuzzySection<SeronStoreEntry> {
public:
  enum ExtraRole {
    DownloadCount = 100,
    AuthorAvatar,
    IsInstalled,
    CompatTierRole,
  };

  void setEntries(const std::vector<SeronStore::Extension> &extensions, ExtensionRegistry *registry,
                  const QString &sectionName);

  QString sectionName() const override { return m_sectionName; }

  QVariant customData(int i, int role) const override;
  QHash<int, QByteArray> customRoleNames() const override {
    return {{DownloadCount, "downloadCount"},
            {AuthorAvatar, "authorAvatar"},
            {IsInstalled, "isInstalled"},
            {CompatTierRole, "compatTier"}};
  }

protected:
  QString displayTitle(const SeronStoreEntry &entry) const override;
  QString displaySubtitle(const SeronStoreEntry &entry) const override;
  QString displayIconSource(const SeronStoreEntry &entry) const override;
  std::unique_ptr<ActionPanelState> buildActionPanel(const SeronStoreEntry &entry) const override;

private:
  QString m_sectionName;
};
