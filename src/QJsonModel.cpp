#include "QJsonModel.h"
#include <fstream>

using json = nlohmann::json;

QJsonModel::QJsonModel(QObject* parent)
    : QAbstractItemModel(parent)
    , header_labels_({ "Key", "Type", "Value" })  // 设置表头
{
    tree_root_ = new QJsonTreeItem;
}

QJsonModel::~QJsonModel()
{
    if(file_path_.isEmpty() == false)
    {
        std::ofstream file(file_path_.toStdString());
        file << json_root_.dump(4);
        file.close();
    }
    delete tree_root_;
}

bool QJsonModel::load(const QString& file_path)
{
    try
    {
        /* 从文件中读取json数据 */
        std::ifstream file(file_path.toStdString());
        json json = json::parse(file);
        file.close();
        file_path_ = file_path;
        return load(json);
    }
    catch (const std::exception& e)
    {
        return false;
    }
}

bool QJsonModel::load(const nlohmann::json& json)
{
    beginResetModel();  // 重置model数据之前调用beginResetModel，此时会触发modelAboutToBeReset信号
    json_root_ = json;
    delete tree_root_;
    tree_root_ = QJsonTreeItem::load(json_root_);
    endResetModel();  // 数据设置结束后调用endResetModel，此时会触发modelReset信号
    emit dataUpdated();
    return true;
}

QVariant QJsonModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    QJsonTreeItem* item = static_cast<QJsonTreeItem*>(index.internalPointer());

    if (role == Qt::DisplayRole)
    {
        if (index.column() == 0)
        {
            return item->key();
        }
        else if (index.column() == 1)
        {
            return item->typeName();
        }
        else if (index.column() == 2)
        {
            return item->value();
        }
    }
    else if (role == Qt::ToolTipRole)
    {
        return item->toolTip();
    }
    else if(role == Qt::EditRole)
    {
        return item->value();
    }
    return QVariant();
}

QVariant QJsonModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return header_labels_.at(section);
    }
    return QVariant();
}

QModelIndex QJsonModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    QJsonTreeItem *parentItem;
    if (!parent.isValid())
        parentItem = tree_root_;
    else
        parentItem = static_cast<QJsonTreeItem*>(parent.internalPointer());

    QJsonTreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex QJsonModel::parent(const QModelIndex& index) const
{
    if (!index.isValid())
        return QModelIndex();

    QJsonTreeItem* childItem = static_cast<QJsonTreeItem*>(index.internalPointer());
    QJsonTreeItem* parentItem = childItem->parent();

    if (parentItem == tree_root_)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int QJsonModel::rowCount(const QModelIndex& parent) const
{
    QJsonTreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = tree_root_;
    else
        parentItem = static_cast<QJsonTreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int QJsonModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 3;
}

Qt::ItemFlags QJsonModel::flags(const QModelIndex& index) const
{
    if(!index.isValid())
        return Qt::NoItemFlags;
    // 如果col = 2，即value列，设置为可编辑
    QJsonTreeItem* item = static_cast<QJsonTreeItem*>(index.internalPointer());
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if (index.column() == 2 && !(item->type() == QJsonTreeItem::Type::array || item->type() == QJsonTreeItem::Type::object))
        flags |= Qt::ItemIsEditable;
    return flags;
}

bool QJsonModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (role != Qt::EditRole)
        return false;

    QJsonTreeItem* item = static_cast<QJsonTreeItem*>(index.internalPointer());
    if (index.column() == 2)
    {
        // 获取value的json路径
        QString path = getJsonPath(index);
        // 判断路径是否存在
        json::json_pointer ptr(path.toStdString());
        if(json_root_.contains(ptr) == false)
            return false;
        // 判断value于json类型是否匹配
        bool ok = false;
        double double_value;
        int int_value;
        switch(item->type())
        {
            case::json::value_t::number_integer: 
            case::json::value_t::number_unsigned: 
            case::json::value_t::number_float:
                // 判断是整数还是浮点数
                if(value.toString().contains('.'))
                {
                    double_value = value.toDouble(&ok);
                    if(ok == false)
                        return false;
                    json_root_[ptr] = value.toDouble(&ok);
                    item->setType(QJsonTreeItem::Type::number_float);
                }
                else
                {
                    int_value = value.toInt(&ok);
                    if(ok == false)
                        return false;
                    json_root_[ptr] = value.toInt(&ok);
                    item->setType(QJsonTreeItem::Type::number_integer);
                }
                break;
            case::json::value_t::boolean:  // 判断是否为布尔值
                if(value.toString() == "true")
                    json_root_[ptr] = true;
                else if(value.toString() == "false")
                    json_root_[ptr] = false;
                else
                    return false;
                break;
            case::json::value_t::string:  // 判断是否为字符串
                json_root_[ptr] = value.toString().toStdString();
                break;
            default:
                return false;
        }
        item->setValue(value.toString());
        emit dataUpdated();
        return true;
    }
    return false;
}

QString QJsonModel::getJsonPath(const QModelIndex& index) const
{
    QStringList path;
    QModelIndex i = index;
    while(i.isValid())
    {
        QJsonTreeItem* item = static_cast<QJsonTreeItem*>(i.internalPointer());
        path.prepend(item->key());
        i = i.parent();
    }
    return QString("/") + path.join("/");
}



