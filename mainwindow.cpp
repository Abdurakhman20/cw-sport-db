#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , db(QSqlDatabase::addDatabase("QPSQL"))
    , connectionName("myConnection")
    , dModel(nullptr)
    , proxyModel(nullptr)
{
    ui->setupUi(this);

    proxyModel = new QSortFilterProxyModel(ui->tableView);

    DataDelegate *dateDelegate =
        new DataDelegate(this, QRegularExpression("[0-9]{4}-[0-1][0-9]-[0-3][0-9]"));
    DataDelegate *timeDelegate =
        new DataDelegate(this, QRegularExpression("\\d{1,2}\\.\\d{2}-\\d{1,2}\\.\\d{2}"));

    ui->tableView->setAttribute(Qt::WA_DeleteOnClose);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);

    ui->tableView->setItemDelegateForColumn(2, dateDelegate);
    ui->tableView->setItemDelegateForColumn(4, timeDelegate);

    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->dragDropOverwriteMode();
    ui->tableView->setDragEnabled(true);
    ui->tableView->setAcceptDrops(true);
    ui->tableView->setDropIndicatorShown(true);
    ui->tableView->setDefaultDropAction(Qt::MoveAction);

    ui->tableView->setSortingEnabled(true);

    connect(ui->actionAbout_Qt, &QAction::triggered,
        qApp, &QApplication::aboutQt);

    qApp->installTranslator(&appTranslator);
    qApp->installTranslator(&qtTranslator);

    qmPath =  + "../cw-sport_2/translations";

    createLanguageMenu();

    setSettings();

}

MainWindow::~MainWindow()
{
    getSettings();
    delete ui;
}

void MainWindow::getSettings() {
    QSettings settings("Settings", "MySettings");

    settings.beginGroup("MainWindowGeometry");
    settings.setValue("size", size());
    settings.setValue("position", pos());
    settings.setValue("language", languageActionGroup->checkedAction()->data().toString());
    settings.endGroup();
}

void MainWindow::setSettings() {
    QSettings settings("Settings", "MySettings");

    settings.beginGroup("MainWindowGeometry");
    resize(settings.value("size").toSize());
    move(settings.value("position").toPoint());

    QString savedLanguage = settings.value("language").toString();

    foreach(QAction *action, languageActionGroup->actions()) {
        if (action->data().toString() == savedLanguage) {
            action->setChecked(true);
            switchLanguage(action);
            break;
        }
    }

    settings.endGroup();
}

void MainWindow::on_tableView_customContextMenuRequested(const QPoint &pos)
{
    QMenu *menu = new QMenu(ui->tableView);

    QModelIndex index=ui->tableView->indexAt(pos);
    QModelIndex sourceIndex = proxyModel->mapToSource(index);

    QAction *deleteAction = new QAction(tr("Delete row"), ui->tableView);
    QAction *addAction = new QAction(tr("Add row"), ui->tableView);

    menu->addAction(deleteAction);
    menu->addAction(addAction);

    QAction *selectedItem = menu->exec(ui->tableView->viewport()->mapToGlobal(pos));

    if (selectedItem == deleteAction && sourceIndex.isValid()) {
        QMessageBox::StandardButton resBtn =
            QMessageBox::question(this, tr("Delete row"), tr("Are you sure you want to delete the line?\n"),
                                  QMessageBox::No | QMessageBox::Yes);

        if (resBtn == QMessageBox::Yes)

            dModel->removeRow(sourceIndex.row());
        else
            return;

    } else if (selectedItem == addAction) {

        SportComplex newSportComplex;

        auto placeholder = this;

        if (placeholder == nullptr)
            return;

        dModel->insertRow(dModel->rowCount(), newSportComplex);
    }
}

void MainWindow::on_actionConnect_triggered()
{
    ConnectWindow *connectWindow = new ConnectWindow;

    connect(connectWindow, &ConnectWindow::connectionDetailsEntered, this, &MainWindow::handleConnectionDetails);
    connect(connectWindow, &ConnectWindow::destroyed, connectWindow, &QObject::deleteLater);
    connectWindow->show();

}

void MainWindow::handleConnectionDetails(const QString &host, const int &port, const QString &database, const QString &user, const QString &password)
{
    db.setHostName(host);
    db.setConnectOptions("requiressl=0;connect_timeout=2");
    db.setPort(port);
    db.setDatabaseName(database);
    db.setUserName(user);
    db.setPassword(password);
    db.open();
    /// Проверить открыто ли соединение с БД можно через метод "isOpen()"
    if (!db.isOpen()) {
        /// Сообщение об ошибке можно вывести через диалоговое окно
        QMessageBox::critical(this,
                              tr("Connection failure!"),
                              db.lastError().text());
        /// и/или в консоль
        qDebug() << db.lastError().driverText();
        qDebug() << db.lastError().databaseText();

        return;
    }

    if (dModel == nullptr) {
        /// Используем созданную модель
        dModel = new DataModel(this, db);

        dModel->setTableName("complexes");
        /// Инициализируем данные таблицы
        auto error = dModel->initLoad();

        if (error.type() == QSqlError::NoError) {
            proxyModel->setSourceModel(dModel);
            ui->tableView->setModel(proxyModel);

            ui->tableView->resizeColumnsToContents();

            qDebug() << dModel->count();
        }
        else
            QMessageBox::critical(this, tr("Error select!"), error.text());
    }

    ui->menuTables->setDisabled(false);
    ui->tableView->verticalHeader()->setVisible(false);

}




void MainWindow::on_actionComplex_Types_triggered()
{
    AdditionalTable *typesTable = new AdditionalTable(this, db, "complex_types");

    typesTable->show();
}


void MainWindow::on_actionComplex_Financing_triggered()
{
    AdditionalTable *financingTable = new AdditionalTable(this, db, "complex_financing");

    financingTable->show();
}


void MainWindow::on_lineEdit_textChanged(const QString &text)
{
    if (!text.isEmpty()) {
        QModelIndex index = this->tableFind(text);
        ui->tableView->setCurrentIndex(index);
    } else {
        this->resetFind();
    }

}

void MainWindow::createLanguageMenu()
{
    /// Создаём список пунктов выбора языка в динамической памяти
    languageActionGroup = new QActionGroup(this);

    /// Ставим связь пунктов меню со слотом смены языка приложения
    connect(languageActionGroup, &QActionGroup::triggered, this, &MainWindow::switchLanguage);

    /// Определяем каталог, где лежат файлы переводов "*.qm"
    QDir dir(qmPath);

    QStringList fileNames =
        dir.entryList(QStringList("cw-sport-2_*.qm"));

    for (int i = 0; i < fileNames.size(); i++) {
        /// Получаем i-ую локаль
        QString locale = fileNames[i];
        /// Удаляем символы в строке сначала и по символ "_" включительно
        locale.remove(0, locale.indexOf('_') + 1);
        // Удаляем символы в строке начиная с символа точки
        locale.truncate(locale.lastIndexOf('.'));

        /// Создаём временную переменную перевода для языкового пункта меню
        QTranslator translator;
        /// Загружаем перевод из файла перевода "*.qm"
        translator.load(fileNames[i], qmPath);

        QString language = translator.translate("MainWindow", "English");
        QAction *action = new QAction(tr("&%1 %2").arg(i + 1).arg(language));

        action->setCheckable(true);
        /// Задаём внутренние данные хранимые в i-ом пункте.
        /// В нашем случае это локаль вида "ru_RU"
        action->setData(locale);

        /// Добавляем i-ый пункт в меню на нашей форме "mainwindow.ui"
        ui->menuLanguage->addAction(action);
        /// Добавляем i-ый пункт в единую группу пунктов
        languageActionGroup->addAction(action);

        ///  Задаём  английский язык в качестве выбранного по умолчанию
        if (language == "English")
            action->setChecked(true);
    }

}

void MainWindow::switchLanguage(QAction *action)
{
    QString locale = action->data().toString();

    /// Загружаем тот перевод который выбрал пользователь
    appTranslator.load("cw-sport-2_" + locale, qmPath);
    locale.chop(3);

    qtTranslator.load("qt_" + locale + ".qm", QLibraryInfo::location(QLibraryInfo::TranslationsPath));

    ui->retranslateUi(this);
}


QModelIndex MainWindow::tableFind(const QString &text)
{
    QModelIndex index = ui->tableView->currentIndex();

    /// Если в таблице нет выделенных ячеек, устанавливаем фильтр на указанный столбец
    if (!index.isValid()) {
        proxyModel->setFilterKeyColumn(selectedColumn);
    } else {
        selectedColumn = index.column();
        proxyModel->setFilterKeyColumn(selectedColumn);
    }

    proxyModel->setFilterFixedString(text);

    return index;
}

void MainWindow::resetFind()
{
    proxyModel->setFilterFixedString(QString());

    /// Если в таблице нет выделенных ячеек, сбрасываем фильтр на все столбцы
    if (!ui->tableView->currentIndex().isValid()) {
        selectedColumn = -1;
        proxyModel->setFilterKeyColumn(selectedColumn);
    }
}



void MainWindow::on_actionAbout_the_developer_triggered()
{
    QMessageBox::about(this, tr("About the developer"),
            tr("Developer: Usmanov Abdurakhman Khasmagamedovich\n"
            "E-mail: ausmanov706@gmail.com\n"
            "Faculty: Information Systems and Technologies\n"
            "Group: ICTMS-3-5"));
}

