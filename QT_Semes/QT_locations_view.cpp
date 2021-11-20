#include "QT_locations_view.h"

QLocationView::QLocationView(QWidget *parent, AUS2::Controller *controller) :
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
    this->location_model_ = new QStandardItemModel();

    this->ui_.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->ui_.tableView->horizontalHeader()->setStretchLastSection(true);

    QObject::connect(this->ui_.pushButton, &QPushButton::clicked, this, &QLocationView::on_filter_button_clicked);
    QObject::connect(this->ui_.pushButton_3, &QPushButton::clicked, this, &QLocationView::on_reset_button_clicked);
    QObject::connect(this->ui_.comboBox, &QComboBox::currentIndexChanged, this, &QLocationView::on_location_selected);
    QObject::connect(this->ui_.comboBox_2, &QComboBox::currentIndexChanged, this, &QLocationView::on_model_selected);
    connect(this->person_information_, QOverload<QAbstractItemModel *>::of(&QPersonInformation::test_doubleclicked), this, &QLocationView::test_doubleclicked);
    connect(this->ui_.tableView, &QListView::clicked, this, &QLocationView::on_item_clicked);
}

QLocationView::~QLocationView() {
    delete this->person_model_;
    delete this->test_model_;
    delete this->location_model_;
}

void QLocationView::set_active() {
    this->update_model();
}

void QLocationView::on_filter_button_clicked() {

    std::string date_from, date_to;
    int id;
    bool positive_only;
    AUS2::location_t location;

    date_from = this->ui_.dateTimeEdit->dateTime().toString(QString("d.M.yyyy H:m:s")).toStdString();
    date_to = this->ui_.dateTimeEdit_2->dateTime().toString(QString("d.M.yyyy H:m:s")).toStdString();
    id = this->ui_.spinBox->value();
    positive_only = this->ui_.checkBox->isChecked();
    location = static_cast<AUS2::location_t>(this->ui_.comboBox->currentIndex());

    switch (this->ui_.comboBox_2->currentIndex()) {
    case 0 : 
        this->render_people(this->controller_->person_list_by_location(location, id, date_from, date_to));
        break;
    case 1 :
        this->render_tests(this->controller_->test_list_by_location(location, id, positive_only, date_from, date_to));
        break;
    case 2:
        this->render_locations(this->controller_->location_list_by_positive_person_count(location, date_from, date_to));
        break;
    case 3:
        this->render_tests(this->controller_->test_by_county(id));
        break;
    }
}

void QLocationView::on_reset_button_clicked() {
    this->render_people(this->controller_->person_list());
    this->render_tests(this->controller_->test_list());
}

void QLocationView::on_location_selected() {
    if (this->ui_.comboBox->currentIndex() == 3) {
        this->ui_.spinBox->setValue(0);
        this->ui_.spinBox->setDisabled(true);
    }
    else {
        this->ui_.spinBox->setDisabled(false);
    }
}

void QLocationView::on_model_selected() {
    this->update_model();
}

void QLocationView::on_item_clicked() {
    switch (this->ui_.comboBox_2->currentIndex()) {
    case 0:
    {
        std::string date_from, date_to;
        bool positive_only;

        date_from = this->ui_.dateTimeEdit->dateTime().toString(QString("d.M.yyyy H:m:s")).toStdString();
        date_to = this->ui_.dateTimeEdit_2->dateTime().toString(QString("d.M.yyyy H:m:s")).toStdString();
        positive_only = this->ui_.checkBox->isChecked();
        this->person_information_->render_person(this->ui_.tableView->currentIndex().data(Qt::DisplayRole).toString(), positive_only, date_from, date_to);
        break;
    }
    case 1:
        this->test_information_->render_test(this->ui_.tableView->currentIndex().data(Qt::DisplayRole).toString());
        break;
    case 3:
        this->test_information_->render_test(this->ui_.tableView->currentIndex().data(Qt::DisplayRole).toString());
        break;
    }

}

void QLocationView::on_person_removed() {
    this->on_filter_button_clicked();
}

void QLocationView::on_test_removed() {
    this->on_filter_button_clicked();
}

void QLocationView::on_test_double_clicked(QAbstractItemModel *model) {
    Q_EMIT this->test_doubleclicked(model);
}

void QLocationView::render_people(std::list<AUS2::Person *> *person_list) {
    QStandardItemModel * model = new QStandardItemModel();

    model->setColumnCount(1);
    model->setHorizontalHeaderLabels(QStringList(QString::fromWCharArray(L"Rodné èíslo osoby")));
    QStandardItem *item;
    for (auto obj : *person_list) {
        if (obj) {

            item = new QStandardItem(QString::fromStdString(obj->id()));
            item->setEditable(false);
            model->appendRow(item);
        }
    }
    delete this->person_model_;
    this->person_model_ = model;
    delete person_list;
    this->update_model();
}

void QLocationView::render_tests(std::list<AUS2::Test *> *test_list) {
    QStandardItemModel *model = new QStandardItemModel();

    model->setColumnCount(1);
    model->setHorizontalHeaderLabels(QStringList(QString::fromWCharArray(L"UUID testu")));
    QStandardItem *item;
    for (auto obj : *test_list) {
        if (obj) {

            item = new QStandardItem(QString::fromStdString(obj->uuid()));
            item->setEditable(false);
            model->appendRow(item);
        }
    }
    delete this->test_model_;
    this->test_model_ = model;
    delete test_list;
    this->update_model();
}

void QLocationView::render_locations(std::list<std::pair<AUS2::TestLocation *, int> *> *location_list) {
    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount(2);
    model->setHorizontalHeaderLabels(QStringList({ QString::fromWCharArray(L"ID") , QString::fromWCharArray(L"Poèet nakazených") }));
    QStandardItem *item;
    int i = 0;
    for (auto obj : *location_list) {
        model->appendRow({ new QStandardItem(QString::number(obj->first->id())),  new QStandardItem(QString::number(obj->second)) });
    }
    
    delete this->location_model_;
    this->location_model_ = model;
    delete location_list;
    this->update_model();
}

void QLocationView::update_model() {
    switch (this->ui_.comboBox_2->currentIndex()) {
    case 0:
        this->ui_.tableView->setModel(this->person_model_);
        this->person_information_->reset();
        this->ui_.stackedWidget->setVisible(true);
        this->ui_.stackedWidget->setCurrentIndex(0);
        break;
    case 1:
        this->ui_.tableView->setModel(this->test_model_);
        this->test_information_->reset();
        this->ui_.stackedWidget->setVisible(true);
        this->ui_.stackedWidget->setCurrentIndex(1);
        break;
    case 2:
        this->ui_.tableView->setModel(this->location_model_);
        this->ui_.stackedWidget->setVisible(false);
        break;
    case 3:
        this->ui_.tableView->setModel(this->test_model_);
        this->test_information_->reset();
        this->ui_.stackedWidget->setVisible(true);
        this->ui_.stackedWidget->setCurrentIndex(1);
        break;
    }
}
