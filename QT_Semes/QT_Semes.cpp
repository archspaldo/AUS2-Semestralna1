#include "QT_Semes.h"

QT_Semes::QT_Semes(QWidget *parent)
    : QMainWindow(parent)
{
    this->ui_.setupUi(this);
    this->controller_ = new AUS2::Controller();
    this->person_view();

    QObject::connect(this->ui_.pushButton, &QPushButton::clicked, this, &QT_Semes::onButtonClickedGeneratePeople);
    QObject::connect(this->ui_.pushButton_2, &QPushButton::clicked, this, &QT_Semes::onFilterPerson);
    QObject::connect(this->ui_.pushButton_6, &QPushButton::clicked, this, &QT_Semes::onResetPerson);
    QObject::connect(this->ui_.pushButton_7, &QPushButton::clicked, this, &QT_Semes::onFilterTest);
    QObject::connect(this->ui_.pushButton_8, &QPushButton::clicked, this, &QT_Semes::onResetTest);
    QObject::connect(this->ui_.pushButton_4, &QPushButton::clicked, this, &QT_Semes::onFilterDistrict);
    QObject::connect(this->ui_.pushButton_9, &QPushButton::clicked, this, &QT_Semes::onResetDistrict);
    QObject::connect(this->ui_.actionGenerator, &QAction::triggered, this, &QT_Semes::onActionPridatGen);
    QObject::connect(this->ui_.actionManu_lne, &QAction::triggered, this, &QT_Semes::onActionPridatMan);
    QObject::connect(this->ui_.actionOsoba, &QAction::triggered, this, &QT_Semes::onClickedOsobaView);
    QObject::connect(this->ui_.actionTest, &QAction::triggered, this, &QT_Semes::onClickedTestView);
    QObject::connect(this->ui_.actionOkresy, &QAction::triggered, this, &QT_Semes::onClickedOkresView);
    QObject::connect(this->ui_.actionKraje, &QAction::triggered, this, &QT_Semes::onClickedKrajView);
    QObject::connect(this->ui_.actionSlovensko_3, &QAction::triggered, this, &QT_Semes::onClickedSlovenskoView);
    QObject::connect(this->ui_.listView, &QListView::clicked, this, &QT_Semes::onSelectedPerson);
    QObject::connect(this->ui_.listView_2, &QListView::doubleClicked, this, &QT_Semes::onDoubleClickedTest);
    QObject::connect(this->ui_.listView_3, &QListView::clicked, this, &QT_Semes::onSelectedTest);

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
    //this->ui_.lineEdit_4->setText(QString::fromStdString(person->id()));
}

void QT_Semes::onActionZobrazit() {
    this->ui_.stackedWidget->setCurrentIndex(0);
    //this->setCentralWidget(this->ui_.widget_2);
}

void QT_Semes::onActionPridatMan() {
    this->ui_.stackedWidget->setCurrentIndex(1);
}

void QT_Semes::onActionPridatGen() {
    this->ui_.stackedWidget->setCurrentIndex(2);
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
    int d = this->ui_.lineEdit_6->text().toInt();
    std::string ds = this->ui_.dateTimeEdit->dateTime().toString(QString("d.M.yyyy H:m:s")).toStdString(),
        de = this->ui_.dateTimeEdit_2->dateTime().toString(QString("d.M.yyyy H:m:s")).toStdString();

    std::list<AUS2::Test *> *l = this->controller_->test_list_by_district(c, d, ds, de);
    this->render_test_view(l);
}

void QT_Semes::onResetDistrict() {
    this->render_test_view(this->controller_->tests());
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
