#include "QJsonWidget.h"
#include <fstream>
#include <iostream>

QJsonWidget::QJsonWidget(QWidget* parent) : QWidget(parent)
{
    layout_ = new QVBoxLayout(this);
    view_ = new QTreeView(this);
    view_->setSelectionMode(QAbstractItemView::ExtendedSelection);
    view_->setEditTriggers(QTreeView::DoubleClicked);
    model_ = new QJsonModel(this);
    view_->setModel(model_);
    layout_->addWidget(view_);
    connect(view_, &QTreeView::expanded, this, &QJsonWidget::resizeColumn);
}

QJsonWidget::~QJsonWidget()
{
}

bool QJsonWidget::load(const QString& file_path)
{
    model_->load(file_path);
    resizeColumn();
    return true;
}

bool QJsonWidget::load(const nlohmann::json& json)
{
    model_->load(json);
    resizeColumn();
    return true;
}

void QJsonWidget::resizeColumn()
{
    view_->resizeColumnToContents(0);
    view_->resizeColumnToContents(1);
    view_->resizeColumnToContents(2);
}
