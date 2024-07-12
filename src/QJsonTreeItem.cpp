#include "QJsonTreeItem.h"
#include <QtAlgorithms>

using Type = nlohmann::json::value_t;
using Json = nlohmann::json;

QJsonTreeItem::QJsonTreeItem(QJsonTreeItem* parent)
{
    parent_ = parent;
}

QJsonTreeItem::~QJsonTreeItem()
{
    qDeleteAll(childs_);
}

void QJsonTreeItem::appendChild(QJsonTreeItem* item)
{
    childs_.append(item);
}

QJsonTreeItem* QJsonTreeItem::child(int row)
{
    return childs_.value(row);
}

QJsonTreeItem* QJsonTreeItem::parent()
{
    return parent_;
}

int QJsonTreeItem::childCount() const
{
    return childs_.count();
}

int QJsonTreeItem::row() const
{
    if (parent_)
        return parent_->childs_.indexOf(const_cast<QJsonTreeItem*>(this));

    return 0;
}

void QJsonTreeItem::setKey(const QString& key)
{
    key_ = key;
}

void QJsonTreeItem::setValue(const QString& value)
{
    value_ = value;
}

void QJsonTreeItem::setToolTip(const QString& toolTip)
{
    tool_tip_ = toolTip;
}

void QJsonTreeItem::setType(const Type& type)
{
    type_ = type;
}

QString QJsonTreeItem::key() const
{
    return key_;
}

QString QJsonTreeItem::value() const
{
    return value_;
}

QString QJsonTreeItem::toolTip() const
{
    return tool_tip_;
}

Type QJsonTreeItem::type() const
{
    return type_;
}

QString QJsonTreeItem::text() const
{
    if (type_ == Type::array)
    {
        return key_ + "\t" + typeName() + "[" + QString::number(childCount()) + "]\t" + value_;
    }
    else
    {
        return key_ + "\t" + typeName() + "\t" + value_;
    }
}

QString QJsonTreeItem::typeName() const
{
    switch (type_)
    {
    case Type::null:
        return "null";
    case Type::object:
        return "object";
    case Type::array:
        return "array";
    case Type::string:
        return "string";
    case Type::boolean:
        return "boolean";
    case Type::number_integer:
    case Type::number_unsigned:
    case Type::number_float:
        return "number";
    case Type::binary:
        return "binary";
    default:
        return "unknown";
    }
}

QJsonTreeItem* QJsonTreeItem::load(const Json& json_node, QJsonTreeItem* parent)
{
    QJsonTreeItem* tree_node = new QJsonTreeItem(parent);
    if (parent == nullptr)
    {
        tree_node->setKey("root");
    }

    if (json_node.is_object())
    {
        for (auto& element : json_node.items())
        {
            QJsonTreeItem* child = load(element.value(), tree_node);
            child->setKey(QString::fromStdString(element.key()));
            tree_node->appendChild(child);
        }
        tree_node->setType(Type::object);
    }
    else if (json_node.is_array())
    {
        int index = 0;
        for (auto& element : json_node)
        {
            QJsonTreeItem* child = load(element, tree_node);
            child->setKey(QString::number(index++));
            tree_node->appendChild(child);
        }
        tree_node->setType(Type::array);
    }
    else if(json_node.is_string())
    {
        std::string value = json_node.dump();  // string类型dump出来是带引号的，需要去掉
        tree_node->setType(json_node.type());
        tree_node->setValue(QString::fromStdString(value.substr(1, value.size() - 2)));
    }
    else
    {
        tree_node->setType(json_node.type());
        tree_node->setValue(QString::fromStdString(json_node.dump()));
    }

    return tree_node;
}

