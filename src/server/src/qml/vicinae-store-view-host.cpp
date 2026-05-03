#include "seron-store-view-host.hpp"
#include "service-registry.hpp"
#include "services/extension-registry/extension-registry.hpp"
#include "services/toast/toast-service.hpp"
#include "utils/utils.hpp"

SeronStoreViewHost::SeronStoreViewHost() {
  connect(&m_watcher, &QFutureWatcher<SeronStore::ListResult>::finished, this,
          &SeronStoreViewHost::handleFinished);
}

QUrl SeronStoreViewHost::qmlComponentUrl() const {
  return QUrl(QStringLiteral("qrc:/Seron/StoreListingView.qml"));
}

QVariantMap SeronStoreViewHost::qmlProperties() {
  return {{QStringLiteral("host"), QVariant::fromValue(this)}};
}

void SeronStoreViewHost::initialize() {
  BaseView::initialize();

  m_model.setScope(ViewScope(context(), this));
  m_model.addSource(&m_section);

  m_store = context()->services->seronStore();

  setSearchPlaceholderText("Browse Seron extensions");

  connect(context()->services->extensionRegistry(), &ExtensionRegistry::extensionsChanged, this,
          &SeronStoreViewHost::refresh);
}

void SeronStoreViewHost::loadInitialData() { fetchExtensions(); }

void SeronStoreViewHost::textChanged(const QString &text) { m_model.setFilter(text); }

void SeronStoreViewHost::onReactivated() { m_model.refreshActionPanel(); }

void SeronStoreViewHost::fetchExtensions() {
  setLoading(true);
  m_watcher.setFuture(m_store->fetchAll());
}

void SeronStoreViewHost::handleFinished() {
  auto result = m_watcher.result();
  setLoading(false);

  if (!result) {
    qWarning() << "[SeronStore] fetch error:" << result.error();
    context()->services->toastService()->setToast("Failed to fetch extensions", ToastStyle::Danger);
    return;
  }

  m_section.setEntries(result->extensions, context()->services->extensionRegistry(),
                       QStringLiteral("Extensions"));
}

void SeronStoreViewHost::refresh() {
  if (auto *cached = m_store->cached()) {
    m_section.setEntries(*cached, context()->services->extensionRegistry(), QStringLiteral("Extensions"));
  } else {
    fetchExtensions();
  }
}
