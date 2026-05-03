#pragma once
#include <QDateTime>
#include <QFuture>
#include <QObject>
#include <QString>
#include <expected>
#include <optional>
#include <vector>
#include "lib/http-client.hpp"
#include "ui/image/url.hpp"

namespace SeronStore {

struct ListPaginationOptions {
  int page = 1;
  int limit = 50;
};

struct Icons {
  std::optional<QString> light;
  std::optional<QString> dark;

  std::optional<ImageURL> themedIcon() const;
};

struct Author {
  QString handle;
  QString name;
  QString avatarUrl;
  QString profileUrl;
};

struct Category {
  QString id;
  QString name;
};

struct Command {
  QString id;
  QString name;
  QString title;
  QString subtitle;
  QString description;
  std::vector<QString> keywords;
  QString mode;
  bool disabledByDefault = false;
  bool beta = false;
  Icons icons;

  std::optional<ImageURL> themedIcon() const;
};

struct Extension {
  QString id;
  QString name;
  QString title;
  QString description;
  Author author;
  int downloadCount = 0;
  QString apiVersion;
  QString checksum;
  bool trending = false;
  Icons icons;
  std::vector<Category> categories;
  std::vector<QString> platforms;
  std::vector<Command> commands;
  QString sourceUrl;
  QString readmeUrl;
  QString downloadUrl;
  QDateTime createdAt;
  QDateTime updatedAt;

  ImageURL themedIcon() const;
};

struct Pagination {
  int page = 1;
  int limit = 50;
  int total = 0;
  int totalPages = 0;
  bool hasNext = false;
  bool hasPrev = false;
};

struct ListResponse {
  std::vector<Extension> extensions;
  Pagination pagination;
};

using ListResult = std::expected<ListResponse, std::string>;
using DownloadExtensionResult = std::expected<QByteArray, std::string>;

} // namespace SeronStore

class SeronStoreService : public QObject {
public:
  explicit SeronStoreService(QObject *parent = nullptr);
  ~SeronStoreService() override = default;

  QFuture<SeronStore::ListResult> fetchExtensions(const SeronStore::ListPaginationOptions &opts = {});

  QFuture<SeronStore::ListResult> fetchAll();

  QFuture<SeronStore::ListResult> search(const QString &query);

  QFuture<SeronStore::DownloadExtensionResult> downloadExtension(const QUrl &url);

  const std::vector<SeronStore::Extension> *cached() const;
  void invalidateCache();

  void setBaseUrl(const QString &url);
  QString baseUrl() const;

private:
  static const http::RequestOptions s_requestOpts;

  http::Client m_client;
  std::optional<std::vector<SeronStore::Extension>> m_cache;
};
