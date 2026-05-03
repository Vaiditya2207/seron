#pragma once
#include "section-list-model.hpp"
#include "seron-store-model.hpp"
#include "bridge-view.hpp"
#include "services/extension-store/seron-store.hpp"
#include <QFutureWatcher>

class SeronStoreViewHost : public ViewHostBase {
  Q_OBJECT
  Q_PROPERTY(QObject *listModel READ listModel CONSTANT)

signals:

public:
  SeronStoreViewHost();

  QUrl qmlComponentUrl() const override;
  QVariantMap qmlProperties() override;
  void initialize() override;
  void loadInitialData() override;
  void textChanged(const QString &text) override;
  void onReactivated() override;

  QObject *listModel() const { return const_cast<SectionListModel *>(&m_model); }

private:
  void fetchExtensions();
  void handleFinished();
  void refresh();

  SectionListModel m_model{this};
  SeronStoreSection m_section;
  SeronStoreService *m_store = nullptr;
  QFutureWatcher<SeronStore::ListResult> m_watcher;
};
