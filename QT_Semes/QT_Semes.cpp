#include "QT_Semes.h"

QT_Semes::QT_Semes(QWidget *parent)
    : QMainWindow(parent)
{
    this->ui_.setupUi(this);
    this->controller_ = new AUS2::Controller();
    this->person_view();

    QObject::connect(this->ui_.pushButton, &QPushButton::clicked, this, &QT_Semes::onButtonClickedGeneratePeople);
    QObject::connect(this->ui_.pushButton_10, &QPushButton::clicked, this, &QT_Semes::onButtonClickedTester);
    QObject::connect(this->ui_.pushButton_14, &QPushButton::clicked, this, &QT_Semes::onButtonClickedAddPerson);
    QObject::connect(this->ui_.pushButton_13, &QPushButton::clicked, this, &QT_Semes::onButtonClickedAddTest);
    QObject::connect(this->ui_.pushButton_2, &QPushButton::clicked, this, &QT_Semes::onFilterPerson);
    QObject::connect(this->ui_.pushButton_6, &QPushButton::clicked, this, &QT_Semes::onResetPerson);
    QObject::connect(this->ui_.pushButton_7, &QPushButton::clicked, this, &QT_Semes::onFilterTest);
    QObject::connect(this->ui_.pushButton_8, &QPushButton::clicked, this, &QT_Semes::onResetTest);
    QObject::connect(this->ui_.pushButton_4, &QPushButton::clicked, this, &QT_Semes::onFilterDistrict);
    QObject::connect(this->ui_.pushButton_9, &QPushButton::clicked, this, &QT_Semes::onResetDistrict);
    QObject::connect(this->ui_.pushButton_11, &QPushButton::clicked, this, &QT_Semes::onFilterStation);
    QObject::connect(this->ui_.pushButton_12, &QPushButton::clicked, this, &QT_Semes::onResetStation);
    QObject::connect(this->ui_.actionTest_2, &QAction::triggered, this, &QT_Semes::onActionTest_2);
    QObject::connect(this->ui_.actionGenerator, &QAction::triggered, this, &QT_Semes::onActionPridatGen);
    QObject::connect(this->ui_.actionOsoba_2, &QAction::triggered, this, &QT_Semes::onActionPridatOsMan);
    QObject::connect(this->ui_.actionTest_3, &QAction::triggered, this, &QT_Semes::onActionPridatTsMan);
    QObject::connect(this->ui_.actionOsoba, &QAction::triggered, this, &QT_Semes::onClickedOsobaView);
    QObject::connect(this->ui_.actionTest, &QAction::triggered, this, &QT_Semes::onClickedTestView);
    QObject::connect(this->ui_.actionOkresy, &QAction::triggered, this, &QT_Semes::onClickedOkresView);
    QObject::connect(this->ui_.actionKraje, &QAction::triggered, this, &QT_Semes::onClickedKrajView);
    QObject::connect(this->ui_.actionSlovensko_3, &QAction::triggered, this, &QT_Semes::onClickedSlovenskoView);
    QObject::connect(this->ui_.actionTestovacie_Stanice, &QAction::triggered, this, &QT_Semes::onClickedStanicaView);
    QObject::connect(this->ui_.listView, &QListView::clicked, this, &QT_Semes::onSelectedPerson);
    QObject::connect(this->ui_.listView_2, &QListView::doubleClicked, this, &QT_Semes::onDoubleClickedTest);
    QObject::connect(this->ui_.listView_3, &QListView::clicked, this, &QT_Semes::onSelectedTest);

}

void QT_Semes::onButtonClickedTester() {
    this->tester(this->ui_.spinBox_7->value(), this->ui_.spinBox_3->value(), this->ui_.spinBox_4->value(), this->ui_.spinBox_5->value(), this->ui_.spinBox_6->value());
}

QT_Semes::~QT_Semes() {
    delete this->controller_;
}

void QT_Semes::onButtonClickedGeneratePeople() {
    AUS2::Person *person;
    for (int i = 0; i < this->ui_.spinBox->text().toInt(); i++) {
        person = this->controller_->add_person();
        for (int j = 0; j < this->ui_.spinBox_2->text().toInt(); j++) {
            this->controller_->add_test(person->id());
        }
    }
    this->person_view();
    this->render_person_view(this->controller_->people());
}

void QT_Semes::onButtonClickedAddPerson() {
    AUS2::Person *person = this->controller_->add_person(this->ui_.lineEdit_8->text().toStdString(), this->ui_.lineEdit_9->text().toStdString(), this->ui_.lineEdit_18->text().toStdString());
    if (person) {
        this->ui_.lineEdit_19->setText(QString::fromStdWString(L"Osoba bola úspešne pridaná"));
    }
    else {
        this->ui_.lineEdit_19->setText(QString::fromStdWString(L"Osobu nebolo možné úspešne prida"));
    }
}

void QT_Semes::onButtonClickedAddTest() {
    AUS2::Test *test = this->controller_->add_test(this->ui_.lineEdit_6->text().toStdString(), this->ui_.spinBox_11->value(), this->ui_.spinBox_12->value(),
        this->ui_.spinBox_13->value(), this->ui_.radioButton_2->isChecked(),
        this->ui_.dateTimeEdit_5->dateTime().toString(QString("d.M.yyyy H:m:s")).toStdString(), 
        this->ui_.lineEdit_21->text().toStdString());
    if (test) {
        this->ui_.lineEdit_7->setText(QString::fromStdWString(L"Test bol úspešne pridaný"));
    }
    else {
        this->ui_.lineEdit_7->setText(QString::fromStdWString(L"Test nebolo možné prida"));
    }
}

void QT_Semes::onActionZobrazit() {
    this->ui_.stackedWidget->setCurrentIndex(0);
    //this->setCentralWidget(this->ui_.widget_2);
}

void QT_Semes::onActionPridatOsMan() {
    this->add_person_view();
}

void QT_Semes::onActionPridatTsMan() {
    this->add_test_view();
}

void QT_Semes::onActionPridatGen() {
    this->generator_view();
}

void QT_Semes::onActionTest_2() {
    this->tester_view();
}

void QT_Semes::onSelectedPerson() {
    this->render_person(this->ui_.listView->currentIndex().data(Qt::DisplayRole).toString().toStdString());
}

void QT_Semes::onSelectedTest() {
    this->render_test(this->ui_.listView_3->currentIndex().data(Qt::DisplayRole).toString().toStdString());
}

void QT_Semes::onDoubleClickedTest() {
    this->render_test(this->ui_.listView_2->currentIndex().data(Qt::DisplayRole).toString().toStdString());
    this->test_view();
    this->ui_.listView_3->setModel(this->ui_.listView_2->model());
}

void QT_Semes::onClickedOsobaView() {
    this->person_view();
}

void QT_Semes::onClickedTestView() {
    this->test_view();
}

void QT_Semes::onClickedOkresView() {
    this->district_view();
}

void QT_Semes::onClickedKrajView() {
}

void QT_Semes::onClickedSlovenskoView() {
}

void QT_Semes::onClickedStanicaView() {
    this->station_view();
}

void QT_Semes::onFilterPerson() {
    this->render_person_view(new std::list<AUS2::Person *>({ this->controller_->person_by_id(this->ui_.lineEdit_5->text().toStdString()) }));
}

void QT_Semes::onResetPerson() {
    this->render_person_view(this->controller_->people());
}

void QT_Semes::onFilterTest() {
    this->render_test_view(new std::list<AUS2::Test *>({ this->controller_->test_by_uuid(this->ui_.lineEdit_5->text().toStdString()) }));
}

void QT_Semes::onResetTest() {
    this->render_test_view(this->controller_->tests());
}

void QT_Semes::onFilterDistrict() {
    bool c = this->ui_.radioButton->isChecked();
    int d = this->ui_.spinBox_8->value();
    std::string ds = this->ui_.dateTimeEdit->dateTime().toString(QString("d.M.yyyy H:m:s")).toStdString(),
        de = this->ui_.dateTimeEdit_2->dateTime().toString(QString("d.M.yyyy H:m:s")).toStdString();
    this->render_test_view(this->controller_->test_list_by_district(c, d, ds, de));
}

void QT_Semes::onResetDistrict() {
    this->render_test_view(this->controller_->tests());
}

void QT_Semes::onFilterStation() {
    int d = this->ui_.spinBox_9->value();
    std::string ds = this->ui_.dateTimeEdit_3->dateTime().toString(QString("d.M.yyyy H:m:s")).toStdString(),
        de = this->ui_.dateTimeEdit_4->dateTime().toString(QString("d.M.yyyy H:m:s")).toStdString();
    this->render_test_view(this->controller_->test_list_by_station(d, ds, de));
}

void QT_Semes::onResetStation() {
    this->render_test_view(this->controller_->tests());
}

void QT_Semes::generator_view() {
    this->ui_.stackedWidget->setCurrentIndex(2);
    this->ui_.stackedWidget_6->setCurrentIndex(0);
}

void QT_Semes::add_person_view() {
    this->ui_.stackedWidget->setCurrentIndex(2);
    this->ui_.stackedWidget_6->setCurrentIndex(1);
}

void QT_Semes::add_test_view() {
    this->ui_.stackedWidget->setCurrentIndex(2);
    this->ui_.stackedWidget_6->setCurrentIndex(2);
}

void QT_Semes::tester_view() {
    this->ui_.stackedWidget->setCurrentIndex(1);
}

void QT_Semes::test_view() {
    this->ui_.stackedWidget->setCurrentIndex(0);
    this->ui_.stackedWidget_2->setCurrentIndex(1);
    this->ui_.stackedWidget_3->setCurrentIndex(1);
    this->ui_.stackedWidget_4->setCurrentIndex(1);
    this->ui_.stackedWidget_5->setCurrentIndex(0);
}

void QT_Semes::person_view() {
    this->ui_.stackedWidget->setCurrentIndex(0);
    this->ui_.stackedWidget_2->setCurrentIndex(0);
    this->ui_.stackedWidget_3->setCurrentIndex(0);
    this->ui_.stackedWidget_4->setCurrentIndex(0);
    this->ui_.stackedWidget_5->setCurrentIndex(0);
}

void QT_Semes::district_view() {
    this->ui_.stackedWidget->setCurrentIndex(0);
    this->ui_.stackedWidget_2->setCurrentIndex(2);
    this->ui_.stackedWidget_3->setCurrentIndex(1);
    this->ui_.stackedWidget_4->setCurrentIndex(1);
    this->ui_.stackedWidget_5->setCurrentIndex(1);
}

void QT_Semes::station_view() {
    this->ui_.stackedWidget->setCurrentIndex(0);
    this->ui_.stackedWidget_2->setCurrentIndex(3);
    this->ui_.stackedWidget_3->setCurrentIndex(1);
    this->ui_.stackedWidget_4->setCurrentIndex(1);
    this->ui_.stackedWidget_5->setCurrentIndex(2);
}

void QT_Semes::tester(int operations, int insert, int remove, int get, int interval) {
    this->ui_.listWidget->clear();
    AUS2::Tester *tester = new AUS2::Tester();
    tester->set(operations, insert, remove, get, interval);
    while (tester->has_next()) {
        this->ui_.listWidget->addItem(new QListWidgetItem(QString::fromStdString(tester->next())));
    }
    delete tester;
}

void QT_Semes::render_person_view(std::list<AUS2::Person *> *l) {
    if (l) {
        if (this->ui_.listView->model()) {
            delete this->ui_.listView->model();
        }
        QStandardItemModel *model = new QStandardItemModel(this);
        model->setColumnCount(1);
        model->setHorizontalHeaderLabels(QStringList(QString("Rodné èíslo")));
        QStandardItem *item;
        for (auto obj : *l) {
            item = new QStandardItem(QString::fromStdString(obj->id()));
            item->setEditable(false);
            model->appendRow(item);
        }
        this->ui_.listView->setModel(model);
        delete l;
    }
}

void QT_Semes::render_test_view(std::list<AUS2::Test *> *l) {
    if (l) {
        if (this->ui_.listView_3->model()) {
            delete this->ui_.listView_3->model();
        }
        QStandardItemModel *model = new QStandardItemModel(this);
        model->setColumnCount(1);
        model->setHorizontalHeaderLabels(QStringList(QString("UUID testu")));
        QStandardItem *item;
        for (auto obj : *l) {
            item = new QStandardItem(QString::fromStdString(obj->uuid()));
            item->setEditable(false);
            model->appendRow(item);
        }
        this->ui_.listView_3->setModel(model);
        delete l;
    }
}

void QT_Semes::render_person(const std::string &id) {
    AUS2::Person *person = this->controller_->person_by_id(id);

    this->ui_.lineEdit->setText(QString::fromStdString(person->name()));
    this->ui_.lineEdit_2->setText(QString::fromStdString(person->surname()));
    this->ui_.lineEdit_3->setText(QString::fromStdString(person->id()));
    this->ui_.lineEdit_4->setText(QString::fromStdString(person->date_of_birth()));

    std::list<AUS2::Test *> *l = this->controller_->test_list_by_id(id);
    if (this->ui_.listView_2->model()) {
        delete this->ui_.listView_2->model();
    }
    QStandardItemModel *model = new QStandardItemModel(this);
    model->setColumnCount(1);
    model->setHorizontalHeaderLabels(QStringList(QString("UUID testu")));
    QStandardItem *item;
    for (auto obj : *l) {
        item = new QStandardItem(QString::fromStdString(obj->uuid()));
        item->setEditable(false);
        model->appendRow(item);
    }
    this->ui_.listView_2->setModel(model);
}

void QT_Semes::render_test(const std::string &uuid) {
    AUS2::Test *test = this->controller_->test_by_uuid(uuid);

    this->ui_.lineEdit_10->setText(QString::fromStdString(test->person()->id()));
    this->ui_.lineEdit_11->setText(QString::fromStdString(test->uuid()));
    this->ui_.lineEdit_12->setText(QString::fromStdWString(test->result() ? L"Pozitívny" : L"Negatívny"));
    this->ui_.lineEdit_13->setText(QString::fromStdString(test->date()));
    this->ui_.lineEdit_14->setText(QString::number(test->county()));
    this->ui_.lineEdit_15->setText(QString::number(test->district()));
    this->ui_.lineEdit_16->setText(QString::number(test->station()));
    this->ui_.lineEdit_17->setText(QString::fromStdString(test->comment()));
}
