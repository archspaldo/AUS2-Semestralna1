#include "QT_test_information.h"

QTestInformation::QTestInformation(QWidget *parent, AUS2::Controller *controller) :
	QWidget(parent), controller_(controller), rendered_test_(nullptr){
	this->ui_.setupUi(this);
	connect(this->ui_.pushButton, &QPushButton::clicked, this, &QTestInformation::on_remove_test_button_clicked);
}

QTestInformation::~QTestInformation() {
}

void QTestInformation::reset() {
    this->rendered_test_ = nullptr;

    this->ui_.lineEdit->setText("");
    this->ui_.lineEdit_2->setText("");
    this->ui_.lineEdit_3->setText("");
    this->ui_.lineEdit_4->setText("");
    this->ui_.lineEdit_5->setText("");
    this->ui_.lineEdit_6->setText("");
    this->ui_.lineEdit_7->setText("");
    this->ui_.lineEdit_8->setText("");
}

void QTestInformation::render_test(QString uuid) {
    this->rendered_test_ = this->controller_->test(uuid.toStdString());

    this->ui_.lineEdit->setText(QString::fromStdString(rendered_test_->person()->id()));
    this->ui_.lineEdit_2->setText(QString::fromStdString(rendered_test_->uuid()));
    this->ui_.lineEdit_3->setText(QString::fromStdWString(rendered_test_->result() ? L"Pozitívny" : L"Negatívny"));
    this->ui_.lineEdit_4->setText(QString::fromStdString(rendered_test_->date()));
    this->ui_.lineEdit_5->setText(QString::number(rendered_test_->location(AUS2::location_t::county)->id()));
    this->ui_.lineEdit_6->setText(QString::number(rendered_test_->location(AUS2::location_t::district)->id()));
    this->ui_.lineEdit_7->setText(QString::number(rendered_test_->location(AUS2::location_t::station)->id()));
    this->ui_.lineEdit_8->setText(QString::fromStdString(rendered_test_->comment()));
}

void QTestInformation::on_remove_test_button_clicked() {
    if (this->rendered_test_) {
	    this->controller_->remove_test(this->rendered_test_->uuid());
	    this->reset();
    }
}