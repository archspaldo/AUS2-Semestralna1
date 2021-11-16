#include "QT_Semes.h"

QT_Semes::QT_Semes(QWidget *parent)
    : QMainWindow(parent)
{
    this->ui_.setupUi(this);
    this->controller_ = new AUS2::Controller();

    this->person_view_ = new QPersonView(this->ui_.stackedWidget, this->controller_);
    this->test_view_ = new QTestView(this->ui_.stackedWidget, this->controller_);

    this->ui_.stackedWidget->addWidget(this->person_view_);
    this->ui_.stackedWidget->addWidget(this->test_view_);

    this->person_view_->setObjectName(QString::fromUtf8("person_view"));
    this->test_view_->setObjectName(QString::fromUtf8("test_view"));

    QObject::connect(this->person_view_, &QPersonView::test_doubleclicked, this, &QT_Semes::on_test_doubleclicked);
    QObject::connect(this->ui_.actionOsoba, &QAction::triggered, this, &QT_Semes::on_person_view_triggered);
    QObject::connect(this->ui_.actionTest, &QAction::triggered, this, &QT_Semes::on_test_view_triggered);
}
QT_Semes::~QT_Semes() {
    delete this->controller_;
}

/*void QT_Semes::onButtonClickedTester() {
    this->tester(this->ui_.spinBox_7->value(), this->ui_.spinBox_3->value(), this->ui_.spinBox_4->value(), this->ui_.spinBox_5->value(), this->ui_.spinBox_6->value());
}


void QT_Semes::onButtonClickedGeneratePeople() {
    AUS2::Person *person;
    this->controller_->fill_database(10, 10, 10, 100, 100);
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
}*/

void QT_Semes::on_test_doubleclicked(QAbstractItemModel *item_model) {
    this->test_view(item_model);
}

void QT_Semes::on_person_view_triggered() {
    this->person_view();
}

void QT_Semes::on_test_view_triggered() {
    this->test_view();
}

void QT_Semes::person_view(QAbstractItemModel *item_model) {
    this->ui_.stackedWidget->setCurrentIndex(0);
    if (item_model) {
        this->person_view_->set_model(item_model);
    }
}

void QT_Semes::test_view(QAbstractItemModel *item_model) {
    this->ui_.stackedWidget->setCurrentIndex(1);
    if (item_model) {
        this->test_view_->set_model(item_model);
    }
}
