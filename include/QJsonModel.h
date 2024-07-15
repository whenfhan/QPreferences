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
 * @file QJsonModel.h
 * @author Wizalm (zlwen@raysees.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-15
 * @copyright Copyright (c) 2023, Raysees Technologies Inc.
 */
#pragma once

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QStringList>
#include <nlohmann/json.hpp>

#include "QJsonTreeItem.h"


class QJsonModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit QJsonModel(QObject* parent = nullptr);
    ~QJsonModel() override;
    bool load(const QString& file_path);
    bool load(const nlohmann::json& json);
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

protected:
    QString getJsonPath(const QModelIndex& index) const;

signals:
    void dataUpdated();

private:
    nlohmann::json json_root_;
    QJsonTreeItem* tree_root_;
    QStringList header_labels_;
    QString file_path_;
};
