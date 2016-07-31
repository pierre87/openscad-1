#include "parameterspinbox.h"

ParameterSpinBox::ParameterSpinBox(ParameterObject *parameterobject, bool showDescription)
{
    presicion =0;
    object=parameterobject;
    setName(QString::fromStdString(object->name));
    setValue();
    connect(doubleSpinBox1,SIGNAL(editingFinished()),this,SLOT(on_Changed()));
    if(showDescription==true){
        setDescription(object->description);
    }
    else{
        doubleSpinBox1->setToolTip(object->description);
    }
}

void ParameterSpinBox::on_Changed(){

    object->value = ValuePtr(doubleSpinBox1->value());
    emit changed();
}

void ParameterSpinBox::setValue(){

    std::string number= object->value->toString();
    presicion=number.size()-number.find('.')-1;
    this->doubleSpinBox1->setDecimals(presicion);
    this->stackedWidget->setCurrentWidget(this->pageVector);
    this->doubleSpinBox1->setRange(object->value->toDouble()-1000,object->value->toDouble()+1000);
    this->doubleSpinBox1->setValue(object->value->toDouble());
    if(object->values->toDouble()>0){
        this->doubleSpinBox1->setSingleStep(object->values->toDouble());
    }
    this->doubleSpinBox2->hide();
    this->doubleSpinBox3->hide();
    this->doubleSpinBox4->hide();
}