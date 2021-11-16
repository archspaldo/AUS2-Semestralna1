#include "QT_person_view.h"

QPersonView::QPersonView(QWidget *parent, AUS2::Controller *controller)
	: QWidget(parent), controller_(controller) {
    this->ui_.setupUi(this);

    this->person_information_ = new QPersonInformation(this, controller);

    this->person_information_->setObjectName(QString::fromUtf8("person_information"));

	connect(this->ui_.pushButton, &QPushButton::clicked, this, &QPersonView::on_filter_button_clicked);
	connect(this->ui_.pushButton_3, &QPushButton::clicked, this, &QPersonView::on_reset_button_clicked);
	connect(this->ui_.listView_2, &QListView::clicked, this, &QPersonView::on_test_clicked);
    connect(this->person_information_, QOverload<QAbstractItemModel *>::of(&QPersonInformation::test_doubleclicked), this, &QPersonView::test_doubleclicked);
}

QPersonView::~QPersonView() {
}

void QPersonView::set_model(QAbstractItemModel *item_model) {
    if (this->ui_.listView_2->model()) {
        delete this->ui_.listView_2->model();
    }
    this->ui_.listView_2->setModel(item_model);
}

void QPersonView::on_filter_button_clicked() {
    if (!this->ui_.lineEdit->text().isEmpty()) {
        this->render_people(new std::list<AUS2::Person *>({ this->controller_->person(this->ui_.lineEdit->text().toStdString()) }));
    }
}

void QPersonView::on_reset_button_clicked() {
    this->render_people(this->controller_->person_list());
}

void QPersonView::on_test_clicked() {
    this->person_information_->render_person(this->ui_.listView_2->currentIndex().data(Qt::DisplayRole).toString());
}

void QPersonView::render_people(std::list<AUS2::Person *> *person_list) {
    this->person_information_->reset();
    if (person_list) {
        if (this->ui_.listView_2->model()) {
            delete this->ui_.listView_2->model();
        }
        QStandardItemModel *model = new QStandardItemModel(this);
        model->setColumnCount(1);
        model->setHorizontalHeaderLabels(QStringList(QString::fromWCharArray(L"Rodné èíslo osoby")));
        QStandardItem *item;
        for (auto obj : *person_list) {
            item = new QStandardItem(QString::fromStdString(obj->id()));
            item->setEditable(false);
            model->appendRow(item);
        }
        this->ui_.listView_2->setModel(model);
        delete person_list;
    }
}
