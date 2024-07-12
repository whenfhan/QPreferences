#pragma once

#include <nlohmann/json.hpp>
#include <QString>
#include <QList>

class QJsonTreeItem
{
public:
    using Type = nlohmann::json::value_t;
    using Json = nlohmann::json;

    QJsonTreeItem(QJsonTreeItem* parent = nullptr);
    ~QJsonTreeItem();
    void appendChild(QJsonTreeItem* item);
    QJsonTreeItem* child(int row);
    QJsonTreeItem* parent();
    int childCount() const;
    int row() const;
    void setKey(const QString& key);
    void setValue(const QString& value);
    void setToolTip(const QString& toolTip);
    void setType(const Type& type);
    QString key() const;
    QString value() const;
    nlohmann::json::value_t type() const;
    QString typeName() const;
    QString text() const;
    QString toolTip() const;

    static QJsonTreeItem* load(const Json& value, QJsonTreeItem* parent = nullptr);

private:
    QString key_;
    QString value_;
    QString tool_tip_;
    Type type_;
    QList<QJsonTreeItem*> childs_;
    QJsonTreeItem* parent_;
};
