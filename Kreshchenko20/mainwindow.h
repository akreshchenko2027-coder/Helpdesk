#include <QtConcurrent>
#include <QFutureWatcher>

// ...
private slots:
void onBatchCheckClicked();
void onBatchProgress(int value);
void onBatchFinished();
private:
QFutureWatcher<void> m_watcher;
