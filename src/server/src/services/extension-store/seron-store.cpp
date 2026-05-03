#include "seron-store.hpp"
#include "lib/glaze-qt.hpp"
#include "generated/version.h"
#include "environment.hpp"
#include "theme.hpp"
#include "theme/theme-file.hpp"

namespace SeronStore {

std::optional<ImageURL> Icons::themedIcon() const {
  const auto &theme = ThemeService::instance().theme();
  if (theme.variant() == ThemeVariant::Dark && dark) return ImageURL::http(*dark);
  if (light) return ImageURL::http(*light);
  if (dark) return ImageURL::http(*dark);
  return {};
}

std::optional<ImageURL> Command::themedIcon() const { return icons.themedIcon(); }

ImageURL Extension::themedIcon() const {
  if (auto icon = icons.themedIcon()) return *icon;
  return ImageURL::builtin("puzzle-piece");
}

} // namespace SeronStore

static void postProcess(SeronStore::ListResponse &response) {
  for (auto &ext : response.extensions) {
    ext.id = QString("store.seron.%1").arg(ext.name);
  }
}

SeronStoreService::SeronStoreService(QObject *parent) : QObject(parent) {
  m_client.setBaseUrl(Environment::seronApiBaseUrl());
}

void SeronStoreService::setBaseUrl(const QString &url) { m_client.setBaseUrl(url); }

QString SeronStoreService::baseUrl() const { return m_client.makeUrl({}).toString(); }

const http::RequestOptions SeronStoreService::s_requestOpts = {
    .cachePolicy = QNetworkRequest::PreferCache,
    .userAgent = QString("seron/%1").arg(SERON_GIT_TAG),
};

QFuture<SeronStore::ListResult>
SeronStoreService::fetchExtensions(const SeronStore::ListPaginationOptions &opts) {
  auto url = QString("/store/list?page=%1&limit=%2").arg(opts.page).arg(opts.limit);

  return m_client.get<SeronStore::ListResponse>(url, s_requestOpts)
      .then([](http::Client::Result<SeronStore::ListResponse> result) -> SeronStore::ListResult {
        if (!result) return std::unexpected(result.error());
        postProcess(*result);
        return *std::move(result);
      });
}

QFuture<SeronStore::ListResult> SeronStoreService::fetchAll() {
  if (m_cache) {
    return QtFuture::makeReadyValueFuture(SeronStore::ListResult{SeronStore::ListResponse{*m_cache, {}}});
  }

  return fetchExtensions({.limit = 500})
      .then(this, [this](SeronStore::ListResult result) -> SeronStore::ListResult {
        if (result) { m_cache = result->extensions; }
        return result;
      });
}

const std::vector<SeronStore::Extension> *SeronStoreService::cached() const {
  return m_cache ? &*m_cache : nullptr;
}

void SeronStoreService::invalidateCache() { m_cache.reset(); }

QFuture<SeronStore::ListResult> SeronStoreService::search(const QString &query) {
  auto url = QString("/store/search?q=%1").arg(query);

  return m_client.get<SeronStore::ListResponse>(url, s_requestOpts)
      .then([](http::Client::Result<SeronStore::ListResponse> result) -> SeronStore::ListResult {
        if (!result) return std::unexpected(result.error());
        postProcess(*result);
        return *std::move(result);
      });
}

QFuture<SeronStore::DownloadExtensionResult> SeronStoreService::downloadExtension(const QUrl &url) {
  return m_client.getRaw(url.toString(), s_requestOpts)
      .then([](http::Client::Result<QByteArray> result) -> SeronStore::DownloadExtensionResult {
        if (!result) return std::unexpected(result.error());
        return *std::move(result);
      });
}
