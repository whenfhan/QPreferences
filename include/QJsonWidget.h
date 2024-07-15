/**
 *       ___           ___           ___           ___           ___           ___           ___
 *      /\  \         /\  \         |\__\         /\  \         /\  \         /\  \         /\  \
 *     /::\  \       /::\  \        |:|  |       /::\  \       /::\  \       /::\  \       /::\  \
 *    /:/\:\  \     /:/\:\  \       |:|  |      /:/\ \  \     /:/\:\  \     /:/\:\  \     /:/\ \  \
 *   /::\ \:\  \   /::\ \:\  \      |:|__|__   _\:\ \ \  \   /::\ \:\  \   /::\ \:\  \   _\:\ \ \  \
 *  /:/\:\ \:\__\ /:/\:\ \:\__\     /::::\__\ /\ \:\ \ \__\ /:/\:\ \:\__\ /:/\:\ \:\__\ /\ \:\ \ \__\
 *  \/_|::\/:/  / \/__\:\/:/  /    /:/  /     \:\ \:\ \/__/ \:\ \:\ \/__/ \:\ \:\ \/__/ \:\ \:\ \/__/
 *     |:|::/  /       \::/  /    /:/  /       \:\ \:\__\    \:\ \:\__\    \:\ \:\__\    \:\ \:\__\
 *     |:|\/__/        /:/  /     \/__/         \:\/:/  /     \:\ \/__/     \:\ \/__/     \:\/:/  /
 *     |:|  |         /:/  /                     \::/  /       \:\__\        \:\__\        \::/  /
 *      \|__|         \/__/                       \/__/         \/__/         \/__/         \/__/
 * @file QJsonWidget.h
 * @author Wizalm (zlwen@raysees.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-15
 * @copyright Copyright (c) 2023, Raysees Technologies Inc.
 */
#pragma once

#include <QObject>
#include <QWidget>
#include <qjsonmodel.h>
#include <QTreeView>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QBoxLayout>
#include <QLineEdit>
#include <QToolButton>
#include <QFileDialog>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QToolTip>
#include <QToolBar>
#include <QMenu>
#include <QLabel>
#include <QClipboard>
#include <QApplication>
#include <nlohmann/json.hpp>

#include "QJsonModel.h"
#include "QPreferences_global.h"

class QPREFERENCES_EXPORT QJsonWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QJsonWidget(QWidget* parent = nullptr);
    ~QJsonWidget() override;
    bool load(const QString& file_path);
    bool load(const nlohmann::json& json);

protected:
    void resizeColumn();

private:
    QJsonModel* model_;
    QTreeView* view_;
    QVBoxLayout *layout_;
};
