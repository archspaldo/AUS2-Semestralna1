#include "QT_person_information.h"

QPersonInformation::QPersonInformation(QWidget *parent, AUS2::Controller *controller) :
	QWidget(parent), controller_(controller), rendered_person_(nullptr) {
    this->ui_.setupUi(this);
    connect(this->ui_.pushButton, &QPushButton::clicked, this, &QPersonInformation::on_remove_person_button_clicked);
}

QPersonInformation::~QPersonInformation() {
}

void QPersonInformation::reset() {
    this->rendered_person_ = nullptr;

    this->ui_.lineEdit->setText("");
    this->ui_.lineEdit_2->setText("");
    this->ui_.lineEdit_3->setText("");
    this->ui_.lineEdit_4->setText("");

    if (this->ui_.listView->model()) {
        delete this->ui_.listView->model();
        this->ui_.listView->setModel(new QStandardItemModel(this));
    }
}

void QPersonInformation::render_person(QString id) {
    this->rendered_person_ = this->controller_->person(id.toStdString());

    this->ui_.lineEdit->setText(QString::fromStdString(this->rendered_person_->name()));
    this->ui_.lineEdit_2->setText(QString::fromStdString(this->rendered_person_->surname()));
    this->ui_.lineEdit_3->setText(QString::fromStdString(this->rendered_person_->id()));
    this->ui_.lineEdit_4->setText(QString::fromStdString(this->rendered_person_->date_of_birth()));

    std::list<AUS2::Test *> *list = this->controller_->test_list_by_id(id.toStdString());
    if (this->ui_.listView->model()) {
        delete this->ui_.listView->model();
    }
    QStandardItemModel *model = new QStandardItemModel(this);
    model->setColumnCount(1);
    model->setHorizontalHeaderLabels(QStringList(QString("UUID testu")));
    QStandardItem *item;
    for (auto obj : *list) {
        item = new QStandardItem(QString::fromStdString(obj->uuid()));
        item->setEditable(false);
        model->appendRow(item);
    }
    this->ui_.listView->setModel(model);
    delete list;
}

void QPersonInformation::on_person_doubleclicked() {
    Q_EMIT this->test_doubleclicked((QAbstractItemModel *)(this->ui_.listView->model()));
}

void QPersonInformation::on_remove_person_button_clicked() {
    if (this->rendered_person_) {
        this->controller_->remove_person(this->rendered_person_->id());
        this->reset();
    }
}
