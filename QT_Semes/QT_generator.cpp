#include "QT_generator.h"

QGeneratorDialog::QGeneratorDialog(QWidget *parent, AUS2::Controller *controller) :
    QDialog(parent), controller_(controller) {
    this->ui_.setupUi(this);
}

QGeneratorDialog::~QGeneratorDialog() {
}

void QGeneratorDialog::accept() {
    this->controller_->fill_database(this->ui_.spinBox_5->value(), this->ui_.spinBox_3->value(), this->ui_.spinBox_4->value(), this->ui_.spinBox->value(), this->ui_.spinBox_2->value());
    QDialog::accept();
}