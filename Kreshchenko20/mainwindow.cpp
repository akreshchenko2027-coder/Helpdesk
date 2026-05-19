void MainWindow::onBatchCheckClicked() {
    auto records = m_repository->loadAll();

    // Створюємо прогрес-бар
    ui->progressBar->setMaximum(records.size());
    ui->progressBar->setValue(0);

    // Запускаємо фонову задачу
    QFuture<void> future = QtConcurrent::run([this, records]() {
        for (int i = 0; i < records.size(); ++i) {
            int count = 0;
            bool leaked = PasswordLeakChecker::checkPasswordSync(records[i].secret, count);
            // Емітимо прогрес (це безпечно через QMetaObject::invokeMethod або сигнали)
            emit m_watcher.progressValueChanged(i + 1);
        }
    });

    m_watcher.setFuture(future);
    ui->btnCheckAll->setEnabled(false);
}

void MainWindow::onBatchFinished() {
    ui->btnCheckAll->setEnabled(true);
    QMessageBox::information(this, "Готово", "Масова перевірка завершена!");
}
