#include "QT_test_view.h"

QTestView::QTestView(QWidget *parent, AUS2::Controller *controller) :
    QWidget(parent), controller_(controller) {
	this->ui_.setupUi(this);
	this->test_information_ = new QTestInformation(this, controller);
    this->test_information_->setObjectName(QString::fromUtf8("test_information"));
	this->ui_.gridLayout->addWidget(this->test_information_, 0, 3, 2, 1);

	QObject::connect(this->ui_.pushButton, &QPushButton::clicked, this, &QTestView::on_filter_button_clicked);
	QObject::connect(this->ui_.pushButton_3, &QPushButton::clicked, this, &QTestView::on_reset_button_clicked);
    QObject::connect(this->ui_.listView_2, &QListView::clicked, this, &QTestView::on_test_clicked);
}

QTestView::~QTestView() {
}

void QTestView::set_model(QAbstractItemModel *item_model) {
    if (this->ui_.listView_2->model()) {
        delete this->ui_.listView_2->model();
    }
    this->ui_.listView_2->setModel(item_model);
}

void QTestView::set_active() {
    this->test_information_->reset();
}

void QTestView::reset_model() {
    this->render_tests(this->controller_->test_list());
}

void QTestView::on_filter_button_clicked() {
    if (!this->ui_.lineEdit->text().isEmpty()) {
        this->render_tests(new std::list<AUS2::Test *>({ this->controller_->test(this->ui_.lineEdit->text().toStdString()) }));
    }
}

void QTestView::on_reset_button_clicked() {
    this->reset_model();
}

void QTestView::on_test_clicked() {
    this->test_information_->render_test(this->ui_.listView_2->currentIndex().data(Qt::DisplayRole).toString());
}

void QTestView::on_test_removed() {
    this->on_filter_button_clicked();
}

void QTestView::render_tests(std::list<AUS2::Test *> *test_list) {
    this->test_information_->reset();
    if (test_list) {
        if (this->ui_.listView_2->model()) {
            delete this->ui_.listView_2->model();
        }
        QStandardItemModel *model = new QStandardItemModel(this);
        model->setColumnCount(1);
        model->setHorizontalHeaderLabels(QStringList(QString("UUID testu")));
        QStandardItem *item;
        for (auto obj : *test_list) {
            item = new QStandardItem(QString::fromStdString(obj->uuid()));
            item->setEditable(false);
            model->appendRow(item);
        }
        this->ui_.listView_2->setModel(model);
        delete test_list;
    }
}
