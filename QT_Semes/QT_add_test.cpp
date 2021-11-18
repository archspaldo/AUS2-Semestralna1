#include "QT_add_test.h"

QAddTestDialog::QAddTestDialog(QWidget *parent, AUS2::Controller *controller) :
    QDialog(parent), controller_(controller) {
    this->ui_.setupUi(this);

    this->lineEdit_4_ = new QLineEdit(this);
    this->lineEdit_4_->setObjectName("lineEdit_4");
    this->lineEdit_4_->setVisible(false);
    this->ui_.gridLayout->addWidget(this->lineEdit_4_, 9, 0, 1, 2);
}

QAddTestDialog::~QAddTestDialog() {
}

void QAddTestDialog::accept() {
    AUS2::Test *test = this->controller_->add_test(this->ui_.lineEdit->text().toStdString(), this->ui_.spinBox->value(), this->ui_.spinBox_2->value(),
        this->ui_.spinBox_3->value(), this->ui_.checkBox->isChecked(),
        this->ui_.dateTimeEdit->dateTime().toString(QString("d.M.yyyy H:m:s")).toStdString(),
        this->ui_.lineEdit_8->text().toStdString());
    if (!test) {
        this->lineEdit_4_->setText(QString::fromStdWString(L"Test nebolo možné prida"));
        this->lineEdit_4_->setVisible(true);
    }
    else {
        QDialog::accept();
    }
}