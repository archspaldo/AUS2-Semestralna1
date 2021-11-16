#include "QT_locations_view.h"

QTLocationsView::QTLocationsView(QWidget *parent, AUS2::Controller *controller) :
	QWidget(parent), controller_(controller) {
    this->ui_.setupUi(this);

    this->person_information_ = new QPersonInformation(this->ui_.stackedWidget, controller);
    this->test_information_ = new QTestInformation(this->ui_.stackedWidget, controller);

    this->person_information_->setObjectName(QString::fromUtf8("person_information"));
    this->test_information_->setObjectName(QString::fromUtf8("test_information"));

    this->ui_.stackedWidget->addWidget(this->person_information_);
    this->ui_.stackedWidget->addWidget(this->test_information_);

    this->person_model_ = new QStandardItemModel();
    this->test_model_ = new QStandardItemModel();
}

QTLocationsView::~QTLocationsView() {
}

void QTLocationsView::on_filter_button_clicked() {
    std::string date_from, date_to;
    int id;
    bool positive_only;
    AUS2::location_t location;

    date_from = this->ui_.dateTimeEdit->dateTime().toString(QString("d.M.yyyy H:m:s")).toStdString();
    date_to = this->ui_.dateTimeEdit_2->dateTime().toString(QString("d.M.yyyy H:m:s")).toStdString();
    id = this->ui_.spinBox->value();
    positive_only = this->ui_.checkBox->isChecked();
    location = static_cast<AUS2::location_t>(this->ui_.comboBox->currentIndex());

    render_people(this->controller_->person_list_by_location(location, id, date_from, date_to));
    render_tests(this->controller_->test_list_by_location(location, id, positive_only, date_from, date_to));
}

void QTLocationsView::on_reset_button_clicked() {
    this->render_people(this->controller_->person_list());
    this->render_tests(this->controller_->test_list());
}

void QTLocationsView::on_select_location() {
    if (this->ui_.comboBox->currentIndex() == 3) {
        this->ui_.spinBox->setValue(0);
        this->ui_.spinBox->setDisabled(true);
    }
    else {
        this->ui_.spinBox->setDisabled(false);
    }
}

void QTLocationsView::render_people(std::list<AUS2::Person *> *person_list) {
    delete this->person_model_;
    QStandardItemModel * model = new QStandardItemModel();

    model->setColumnCount(1);
    model->setHorizontalHeaderLabels(QStringList(QString::fromWCharArray(L"Rodné èíslo osoby")));
    QStandardItem *item;
    for (auto obj : *person_list) {
        item = new QStandardItem(QString::fromStdString(obj->id()));
        item->setEditable(false);
        model->appendRow(item);
    }
    this->person_model_ = model;
}

void QTLocationsView::render_tests(std::list<AUS2::Test *> *test_list) {
    delete this->test_model_;
    QStandardItemModel *model = new QStandardItemModel();

    model->setColumnCount(1);
    model->setHorizontalHeaderLabels(QStringList(QString::fromWCharArray(L"UUID testu")));
    QStandardItem *item;
    for (auto obj : *test_list) {
        item = new QStandardItem(QString::fromStdString(obj->uuid()));
        item->setEditable(false);
        model->appendRow(item);
    }
    this->test_model_ = model;
}

void QTLocationsView::set_active_model() {
    if (this->ui_.comboBox_2->currentIndex() == 0) {
        this->ui_.listView_2->setModel(this->person_model_);
    }
    else {
        this->ui_.listView_2->setModel(this->test_model_);
    }
    this->ui_.stackedWidget->setCurrentIndex(this->ui_.comboBox_2->currentIndex());
}
