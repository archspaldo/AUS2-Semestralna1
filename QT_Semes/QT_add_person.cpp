#include "QT_add_person.h"

QAddPerson::QAddPerson(QWidget *parent, AUS2::Controller *controller) :
    QDialog(parent), controller_(controller) {
    this->ui_.setupUi(this);

    this->lineEdit_4_ = new QLineEdit(this);
    this->lineEdit_4_->setObjectName("lineEdit_4");
    this->lineEdit_4_->setVisible(false);
    this->ui_.gridLayout->addWidget(this->lineEdit_4_, 5, 0, 1, 2);
}

QAddPerson::~QAddPerson() {
}

void QAddPerson::accept() {
    AUS2::Person *person = this->controller_->add_person(this->ui_.lineEdit->text().toStdString(), this->ui_.lineEdit_2->text().toStdString(), this->ui_.lineEdit_3->text().toStdString());
    if (!person) {
        this->lineEdit_4_->setText(QString::fromStdWString(L"Ososba so zadaným rodným èíslom už je pridaná"));
        this->lineEdit_4_->setVisible(true);
    }
    else {
        QDialog::accept();
    }
}
