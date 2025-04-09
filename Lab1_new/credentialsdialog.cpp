#include "credentialsdialog.h"
#include "ui_credentialsdialog.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

CredentialsDialog::CredentialsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CredentialsDialog)
{
    ui->setupUi(this);
    loadCredentials();

    // Подключение кнопки фильтрации к слоту
    connect(ui->filterButton, &QPushButton::clicked, this, &CredentialsDialog::onFilterButtonClicked);
}

CredentialsDialog::~CredentialsDialog()
{
    delete ui;
}

void CredentialsDialog::loadCredentials()
{
    QString filePath = "credentials.txt"; // Путь к файлу
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл!";
        return;
    }

    QTextStream in(&file);
    ui->credentialsTable->setRowCount(0);
    ui->credentialsTable->setColumnCount(3);
    ui->credentialsTable->setHorizontalHeaderLabels({"URL", "Логин", "Пароль"});

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split('|');
        if (parts.size() == 3) {
            credentialsData.append(parts); // Сохраняем данные для фильтрации
            int row = ui->credentialsTable->rowCount();
            ui->credentialsTable->insertRow(row);
            ui->credentialsTable->setItem(row, 0, new QTableWidgetItem(parts[0]));
            ui->credentialsTable->setItem(row, 1, new QTableWidgetItem(parts[1]));
            ui->credentialsTable->setItem(row, 2, new QTableWidgetItem(QString(parts[2].length(), '*')));
        }
    }

    file.close();
}

void CredentialsDialog::onFilterButtonClicked()
{
    QString filterText = ui->filterInput->text().trimmed().toLower();
    ui->credentialsTable->setRowCount(0); // Очистка таблицы

    for (const QStringList &credential : credentialsData) {
        if (credential[0].toLower().contains(filterText)) {
            int row = ui->credentialsTable->rowCount();
            ui->credentialsTable->insertRow(row);
            ui->credentialsTable->setItem(row, 0, new QTableWidgetItem(credential[0]));
            ui->credentialsTable->setItem(row, 1, new QTableWidgetItem(credential[1]));
            ui->credentialsTable->setItem(row, 2, new QTableWidgetItem(QString(credential[2].length(), '*')));
        }
    }
}
