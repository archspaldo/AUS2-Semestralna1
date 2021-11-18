#include "QT_Semes.h"

QT_Semes::QT_Semes(QWidget *parent)
    : QMainWindow(parent)
{
    this->ui_.setupUi(this);
    this->controller_ = new AUS2::Controller();

    this->person_view_ = new QPersonView(this->ui_.stackedWidget, this->controller_);
    this->test_view_ = new QTestView(this->ui_.stackedWidget, this->controller_);
    this->location_view_ = new QLocationView(this->ui_.stackedWidget, this->controller_);

    this->ui_.stackedWidget->addWidget(this->person_view_);
    this->ui_.stackedWidget->addWidget(this->test_view_);
    this->ui_.stackedWidget->addWidget(this->location_view_);

    this->person_view_->setObjectName(QString::fromUtf8("person_view"));
    this->test_view_->setObjectName(QString::fromUtf8("test_view"));
    this->location_view_->setObjectName(QString::fromUtf8("location_view"));

    QObject::connect(this->person_view_, &QPersonView::test_doubleclicked, this, &QT_Semes::on_test_doubleclicked);
    QObject::connect(this->location_view_, &QLocationView::test_doubleclicked, this, &QT_Semes::on_test_doubleclicked);
    QObject::connect(this->ui_.actionOsoba, &QAction::triggered, this, &QT_Semes::on_person_view_triggered);
    QObject::connect(this->ui_.actionTest, &QAction::triggered, this, &QT_Semes::on_test_view_triggered);
    QObject::connect(this->ui_.actionLokality, &QAction::triggered, this, &QT_Semes::on_location_view_triggered);
    QObject::connect(this->ui_.actionOsoba_2, &QAction::triggered, this, &QT_Semes::on_add_person_triggered);
    QObject::connect(this->ui_.actionTest_3, &QAction::triggered, this, &QT_Semes::on_add_test_triggered);
    QObject::connect(this->ui_.actionTest_2, &QAction::triggered, this, &QT_Semes::on_tester_triggered);
    QObject::connect(this->ui_.actionGenerator, &QAction::triggered, this, &QT_Semes::on_generate_triggered);
    QObject::connect(this->ui_.actionImport, &QAction::triggered, this, &QT_Semes::on_import_triggered);
    QObject::connect(this->ui_.actionExport, &QAction::triggered, this, &QT_Semes::on_export_triggered);
}
QT_Semes::~QT_Semes() {
    delete this->controller_;
}

void QT_Semes::on_test_doubleclicked(QAbstractItemModel *item_model) {
    this->test_view(item_model);
}

void QT_Semes::on_person_view_triggered() {
    this->person_view();
    this->person_view_->set_active();
}

void QT_Semes::on_test_view_triggered() {
    this->test_view();
    this->test_view_->set_active();
}

void QT_Semes::on_location_view_triggered() {
    this->location_view();
    this->location_view_->set_active();
}

void QT_Semes::on_add_person_triggered() {
    QAddPerson dialog = QAddPerson(this, this->controller_);
    dialog.exec();
    this->person_view();
    this->person_view_->reset_model();
}

void QT_Semes::on_add_test_triggered() {
    QAddTestDialog dialog = QAddTestDialog(this, this->controller_);
    dialog.exec();
    this->test_view();
    this->test_view_->reset_model();
}

void QT_Semes::on_generate_triggered() {
    QGeneratorDialog dialog = QGeneratorDialog(this, this->controller_);
    dialog.exec();
    this->person_view();
    this->person_view_->reset_model();
}

void QT_Semes::on_tester_triggered() {
    QTester dialog = QTester(this);
    dialog.exec();
    this->person_view();
    this->person_view_->reset_model();
}

void QT_Semes::on_import_triggered() {
    this->controller_->import_state();
}

void QT_Semes::on_export_triggered() {
    this->controller_->export_state();
}

void QT_Semes::person_view() {
    this->ui_.stackedWidget->setCurrentIndex(0);
    this->person_view_->set_active();
}

void QT_Semes::test_view(QAbstractItemModel *item_model) {
    this->ui_.stackedWidget->setCurrentIndex(1);
    this->test_view_->set_active();
    if (item_model) {
        this->test_view_->set_model(item_model);
    }
}

void QT_Semes::location_view() {
    this->ui_.stackedWidget->setCurrentIndex(2);
    this->location_view_->set_active();
}
