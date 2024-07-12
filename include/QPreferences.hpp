﻿/**
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
 * @file QPreferences.h
 * @author Wizalm (zlwen@raysees.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-10
 * @copyright Copyright (c) 2023, Raysees Technologies Inc.
 */
#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include <QString>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QLabel>
#include <QVariant>

#include "QJsonWidget.h"

template <typename T>
class QPreferences
{
    using json = nlohmann::json;
public:
    static T* GetInstance()
    {
        static T instance;
        return &instance;
    }

    QPreferences(T&&) = delete;
    QPreferences(const T&) = delete;
    void operator=(const T&) = delete;

protected:
    QPreferences(const QString &file_path) : file_path_(file_path) {}
    virtual ~QPreferences() = default;

public:
    bool load()
    {
        if(file_path_.isEmpty())
        {
            return false;
        }
        try
        {
            std::ifstream file(file_path_.toStdString());
            json root = json::parse(file);
            file.close();
            T* static_this = dynamic_cast<T*>(this);
            *static_this = root.get<T>();
            return true;
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
            return false;
        }
    }

    bool save()
    {
        if(file_path_.isEmpty())
        {
            return false;
        }
        if(createFile(file_path_) == false)
        {
            return false;
        }
        try
        {
            T* static_this = dynamic_cast<T*>(this);
            json root = *static_this;
            std::ofstream file(file_path_.toStdString());
            file << root.dump(4);
            file.close();
            return true;
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
            return false;
        }
    }

    void showUI()
    {
        if(file_path_.isEmpty())
        {
            return;
        }
        try
        {
            QDialog* dialog = new QDialog();
            QVBoxLayout *layout = new QVBoxLayout(dialog);
            layout->setMargin(0);
            QJsonWidget* json_widget = new QJsonWidget(dialog);
            layout->addWidget(json_widget);
            json_widget->load(file_path_);
            dialog->setWindowTitle("Preferences");
            dialog->resize(400, 600);
            dialog->exec();
            delete dialog;
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

protected:
    // 判断文件是否存在
    bool fileExists(const QString& path)
    {
        return QFile(path).exists();
    }

    // 创建文件
    bool createFile(const QString& path)
    {
        if(fileExists(path))
        {
            return true;
        }
        int index = path.lastIndexOf('/');
        if(index != -1)
        {
            QString dir = path.mid(0, index);
            if(!QDir(dir).exists())
            {
                QDir().mkpath(dir);
            }
        }
        QFile file(path.mid(index + 1));
        if(file.open(QIODevice::WriteOnly))
        {
            file.close();
            return true;
        }
        return false;
    }

private:
    QString file_path_;
};

#define RSEQ_N()                                                               \
      120, 119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 109, 108, 107,    \
      106, 105, 104, 103, 102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91,   \
      90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73,  \
      72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55,  \
      54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37,  \
      36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19,  \
      18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

#define ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14,     \
              _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, \
              _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, \
              _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, \
              _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, \
              _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, \
              _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, _92, \
              _93, _94, _95, _96, _97, _98, _99, _100, _101, _102, _103, _104, \
              _105, _106, _107, _108, _109, _110, _111, _112, _113, _114,      \
              _115, _116, _117, _118, _119, _120, N, ...)                      \
  N

#define MARCO_EXPAND(...) __VA_ARGS__
#define GET_ARG_COUNT_INNER(...) MARCO_EXPAND(ARG_N(__VA_ARGS__))
#define GET_ARG_COUNT(...) GET_ARG_COUNT_INNER(__VA_ARGS__, RSEQ_N())

#define _MACRO_CONCAT(A, B) A##_##B
#define MACRO_CONCAT(A, B) _MACRO_CONCAT(A, B)

#define _MACRO_STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) _MACRO_STRINGIFY(x)

#define GENERATE_VAR_3(TYPE, VAR_NAME, DEFAULT_VAL) TYPE VAR_NAME;
#define GENERATE_VAR_6(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_3(__VA_ARGS__))
#define GENERATE_VAR_9(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_6(__VA_ARGS__))
#define GENERATE_VAR_12(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_9(__VA_ARGS__))
#define GENERATE_VAR_15(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_12(__VA_ARGS__))
#define GENERATE_VAR_18(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_15(__VA_ARGS__))
#define GENERATE_VAR_21(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_18(__VA_ARGS__))
#define GENERATE_VAR_24(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_21(__VA_ARGS__))
#define GENERATE_VAR_27(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_24(__VA_ARGS__))
#define GENERATE_VAR_30(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_27(__VA_ARGS__))
#define GENERATE_VAR_33(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_30(__VA_ARGS__))
#define GENERATE_VAR_36(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_33(__VA_ARGS__))
#define GENERATE_VAR_39(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_36(__VA_ARGS__))
#define GENERATE_VAR_42(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_39(__VA_ARGS__))
#define GENERATE_VAR_45(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_42(__VA_ARGS__))
#define GENERATE_VAR_48(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_45(__VA_ARGS__))
#define GENERATE_VAR_51(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_48(__VA_ARGS__))
#define GENERATE_VAR_54(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_51(__VA_ARGS__))
#define GENERATE_VAR_57(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_54(__VA_ARGS__))
#define GENERATE_VAR_60(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_57(__VA_ARGS__))
#define GENERATE_VAR_63(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_60(__VA_ARGS__))
#define GENERATE_VAR_66(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_63(__VA_ARGS__))
#define GENERATE_VAR_69(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_66(__VA_ARGS__))
#define GENERATE_VAR_72(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_69(__VA_ARGS__))
#define GENERATE_VAR_75(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_72(__VA_ARGS__))
#define GENERATE_VAR_78(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_75(__VA_ARGS__))
#define GENERATE_VAR_81(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_78(__VA_ARGS__))
#define GENERATE_VAR_84(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_81(__VA_ARGS__))
#define GENERATE_VAR_87(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_84(__VA_ARGS__))
#define GENERATE_VAR_90(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_87(__VA_ARGS__))
#define GENERATE_VAR_93(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_90(__VA_ARGS__))
#define GENERATE_VAR_96(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_93(__VA_ARGS__))
#define GENERATE_VAR_99(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_96(__VA_ARGS__))
#define GENERATE_VAR_102(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_99(__VA_ARGS__))
#define GENERATE_VAR_105(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_102(__VA_ARGS__))
#define GENERATE_VAR_108(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_105(__VA_ARGS__))
#define GENERATE_VAR_111(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_108(__VA_ARGS__))
#define GENERATE_VAR_114(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_111(__VA_ARGS__))
#define GENERATE_VAR_117(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_114(__VA_ARGS__))
#define GENERATE_VAR_120(TYPE, VAR_NAME, DEFAULT_VAL, ...) TYPE VAR_NAME; MARCO_EXPAND(GENERATE_VAR_117(__VA_ARGS__))
#define GENERATE_VAR(N, ...) MACRO_CONCAT(GENERATE_VAR, N)(__VA_ARGS__)

#define GENERATE_TO_JSON_3(TYPE, VAR_NAME, DEFAULT_VAL) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME;
#define GENERATE_TO_JSON_6(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_3(__VA_ARGS__))
#define GENERATE_TO_JSON_9(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_6(__VA_ARGS__))
#define GENERATE_TO_JSON_12(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_9(__VA_ARGS__))
#define GENERATE_TO_JSON_15(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_12(__VA_ARGS__))
#define GENERATE_TO_JSON_18(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_15(__VA_ARGS__))
#define GENERATE_TO_JSON_21(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_18(__VA_ARGS__))
#define GENERATE_TO_JSON_24(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_21(__VA_ARGS__))
#define GENERATE_TO_JSON_27(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_24(__VA_ARGS__))
#define GENERATE_TO_JSON_30(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_27(__VA_ARGS__))
#define GENERATE_TO_JSON_33(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_30(__VA_ARGS__))
#define GENERATE_TO_JSON_36(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_33(__VA_ARGS__))
#define GENERATE_TO_JSON_39(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_36(__VA_ARGS__))
#define GENERATE_TO_JSON_42(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_39(__VA_ARGS__))
#define GENERATE_TO_JSON_45(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_42(__VA_ARGS__))
#define GENERATE_TO_JSON_48(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_45(__VA_ARGS__))
#define GENERATE_TO_JSON_51(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_48(__VA_ARGS__))
#define GENERATE_TO_JSON_54(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_51(__VA_ARGS__))
#define GENERATE_TO_JSON_57(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_54(__VA_ARGS__))
#define GENERATE_TO_JSON_60(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_57(__VA_ARGS__))
#define GENERATE_TO_JSON_63(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_60(__VA_ARGS__))
#define GENERATE_TO_JSON_66(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_63(__VA_ARGS__))
#define GENERATE_TO_JSON_69(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_66(__VA_ARGS__))
#define GENERATE_TO_JSON_72(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_69(__VA_ARGS__))
#define GENERATE_TO_JSON_75(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_72(__VA_ARGS__))
#define GENERATE_TO_JSON_78(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_75(__VA_ARGS__))
#define GENERATE_TO_JSON_81(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_78(__VA_ARGS__))
#define GENERATE_TO_JSON_84(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_81(__VA_ARGS__))
#define GENERATE_TO_JSON_87(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_84(__VA_ARGS__))
#define GENERATE_TO_JSON_90(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_87(__VA_ARGS__))
#define GENERATE_TO_JSON_93(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_90(__VA_ARGS__))
#define GENERATE_TO_JSON_96(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_93(__VA_ARGS__))
#define GENERATE_TO_JSON_99(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_96(__VA_ARGS__))
#define GENERATE_TO_JSON_102(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_99(__VA_ARGS__))
#define GENERATE_TO_JSON_105(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_102(__VA_ARGS__))
#define GENERATE_TO_JSON_108(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_105(__VA_ARGS__))
#define GENERATE_TO_JSON_111(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_108(__VA_ARGS__))
#define GENERATE_TO_JSON_114(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_111(__VA_ARGS__))
#define GENERATE_TO_JSON_117(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_114(__VA_ARGS__))
#define GENERATE_TO_JSON_120(TYPE, VAR_NAME, DEFAULT_VAL, ...) j[MACRO_STRINGIFY(VAR_NAME)] = s.VAR_NAME; MARCO_EXPAND(GENERATE_TO_JSON_117(__VA_ARGS__))
#define GENERATE_TO_JSON(STRUCT_NAME, N, ...) \
    inline void to_json(nlohmann::json& j, const STRUCT_NAME& s) \
    { \
        MACRO_CONCAT(GENERATE_TO_JSON, N)(__VA_ARGS__) \
    }

#define GENERATE_FROM_JSON_3(TYPE, VAR_NAME, DEFAULT_VAL) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>();
#define GENERATE_FROM_JSON_6(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_3(__VA_ARGS__))
#define GENERATE_FROM_JSON_9(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_6(__VA_ARGS__))
#define GENERATE_FROM_JSON_12(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_9(__VA_ARGS__))
#define GENERATE_FROM_JSON_15(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_12(__VA_ARGS__))
#define GENERATE_FROM_JSON_18(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_15(__VA_ARGS__))
#define GENERATE_FROM_JSON_21(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_18(__VA_ARGS__))
#define GENERATE_FROM_JSON_24(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_21(__VA_ARGS__))
#define GENERATE_FROM_JSON_27(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_24(__VA_ARGS__))
#define GENERATE_FROM_JSON_30(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_27(__VA_ARGS__))
#define GENERATE_FROM_JSON_33(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_30(__VA_ARGS__))
#define GENERATE_FROM_JSON_36(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_33(__VA_ARGS__))
#define GENERATE_FROM_JSON_39(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_36(__VA_ARGS__))
#define GENERATE_FROM_JSON_42(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_39(__VA_ARGS__))
#define GENERATE_FROM_JSON_45(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_42(__VA_ARGS__))
#define GENERATE_FROM_JSON_48(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_45(__VA_ARGS__))
#define GENERATE_FROM_JSON_51(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_48(__VA_ARGS__))
#define GENERATE_FROM_JSON_54(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_51(__VA_ARGS__))
#define GENERATE_FROM_JSON_57(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_54(__VA_ARGS__))
#define GENERATE_FROM_JSON_60(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_57(__VA_ARGS__))
#define GENERATE_FROM_JSON_63(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_60(__VA_ARGS__))
#define GENERATE_FROM_JSON_66(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_63(__VA_ARGS__))
#define GENERATE_FROM_JSON_69(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_66(__VA_ARGS__))
#define GENERATE_FROM_JSON_72(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_69(__VA_ARGS__))
#define GENERATE_FROM_JSON_75(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_72(__VA_ARGS__))
#define GENERATE_FROM_JSON_78(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_75(__VA_ARGS__))
#define GENERATE_FROM_JSON_81(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_78(__VA_ARGS__))
#define GENERATE_FROM_JSON_84(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_81(__VA_ARGS__))
#define GENERATE_FROM_JSON_87(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_84(__VA_ARGS__))
#define GENERATE_FROM_JSON_90(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_87(__VA_ARGS__))
#define GENERATE_FROM_JSON_93(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_90(__VA_ARGS__))
#define GENERATE_FROM_JSON_96(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_93(__VA_ARGS__))
#define GENERATE_FROM_JSON_99(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_96(__VA_ARGS__))
#define GENERATE_FROM_JSON_102(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_99(__VA_ARGS__))
#define GENERATE_FROM_JSON_105(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_102(__VA_ARGS__))
#define GENERATE_FROM_JSON_108(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_105(__VA_ARGS__))
#define GENERATE_FROM_JSON_111(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_108(__VA_ARGS__))
#define GENERATE_FROM_JSON_114(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_111(__VA_ARGS__))
#define GENERATE_FROM_JSON_117(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_114(__VA_ARGS__))
#define GENERATE_FROM_JSON_120(TYPE, VAR_NAME, DEFAULT_VAL, ...) s.VAR_NAME = j[MACRO_STRINGIFY(VAR_NAME)].get<TYPE>(); MARCO_EXPAND(GENERATE_FROM_JSON_117(__VA_ARGS__))
#define GENERATE_FROM_JSON(STRUCT_NAME, N, ...) \
    inline void from_json(const nlohmann::json& j, STRUCT_NAME& s) \
    { \
        MACRO_CONCAT(GENERATE_FROM_JSON, N)(__VA_ARGS__) \
    }


#define GENERATE_DEFAULT_3(TYPE, VAR_NAME, DEFAULT_VAL) VAR_NAME DEFAULT_VAL
#define GENERATE_DEFAULT_6(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_3(__VA_ARGS__))
#define GENERATE_DEFAULT_9(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_6(__VA_ARGS__))
#define GENERATE_DEFAULT_12(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_9(__VA_ARGS__))
#define GENERATE_DEFAULT_15(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_12(__VA_ARGS__))
#define GENERATE_DEFAULT_18(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_15(__VA_ARGS__))
#define GENERATE_DEFAULT_21(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_18(__VA_ARGS__))
#define GENERATE_DEFAULT_24(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_21(__VA_ARGS__))
#define GENERATE_DEFAULT_27(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_24(__VA_ARGS__))
#define GENERATE_DEFAULT_30(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_27(__VA_ARGS__))
#define GENERATE_DEFAULT_33(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_30(__VA_ARGS__))
#define GENERATE_DEFAULT_36(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_33(__VA_ARGS__))
#define GENERATE_DEFAULT_39(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_36(__VA_ARGS__))
#define GENERATE_DEFAULT_42(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_39(__VA_ARGS__))
#define GENERATE_DEFAULT_45(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_42(__VA_ARGS__))
#define GENERATE_DEFAULT_48(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_45(__VA_ARGS__))
#define GENERATE_DEFAULT_51(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_48(__VA_ARGS__))
#define GENERATE_DEFAULT_54(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_51(__VA_ARGS__))
#define GENERATE_DEFAULT_57(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_54(__VA_ARGS__))
#define GENERATE_DEFAULT_60(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_57(__VA_ARGS__))
#define GENERATE_DEFAULT_63(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_60(__VA_ARGS__))
#define GENERATE_DEFAULT_66(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_63(__VA_ARGS__))
#define GENERATE_DEFAULT_69(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_66(__VA_ARGS__))
#define GENERATE_DEFAULT_72(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_69(__VA_ARGS__))
#define GENERATE_DEFAULT_75(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_72(__VA_ARGS__))
#define GENERATE_DEFAULT_78(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_75(__VA_ARGS__))
#define GENERATE_DEFAULT_81(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_78(__VA_ARGS__))
#define GENERATE_DEFAULT_84(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_81(__VA_ARGS__))
#define GENERATE_DEFAULT_87(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_84(__VA_ARGS__))
#define GENERATE_DEFAULT_90(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_87(__VA_ARGS__))
#define GENERATE_DEFAULT_93(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_90(__VA_ARGS__))
#define GENERATE_DEFAULT_96(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_93(__VA_ARGS__))
#define GENERATE_DEFAULT_99(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_96(__VA_ARGS__))
#define GENERATE_DEFAULT_102(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_99(__VA_ARGS__))
#define GENERATE_DEFAULT_105(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_102(__VA_ARGS__))
#define GENERATE_DEFAULT_108(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_105(__VA_ARGS__))
#define GENERATE_DEFAULT_111(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_108(__VA_ARGS__))
#define GENERATE_DEFAULT_114(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_111(__VA_ARGS__))
#define GENERATE_DEFAULT_117(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_114(__VA_ARGS__))
#define GENERATE_DEFAULT_120(TYPE, VAR_NAME, DEFAULT_VAL, ...) VAR_NAME DEFAULT_VAL, MARCO_EXPAND(GENERATE_DEFAULT_117(__VA_ARGS__))
#define GENERATE_DEFAULT(STRUCT_NAME, FILE_PATH, N, ...) \
    STRUCT_NAME() : QPreferences<STRUCT_NAME>(FILE_PATH), \
                    MACRO_CONCAT(GENERATE_DEFAULT, N)(__VA_ARGS__) \
    { \
        if(!fileExists(FILE_PATH)) \
        { \
            save(); \
        } \
    }

#define _QPREFERENCES_STRUCT(STRUCT_NAME, FILE_PATH, VAR_NUM, ...) \
struct STRUCT_NAME : public QPreferences<STRUCT_NAME> \
{ \
    GENERATE_DEFAULT(STRUCT_NAME, FILE_PATH, VAR_NUM, __VA_ARGS__) \
    GENERATE_VAR(VAR_NUM, __VA_ARGS__) \
}; \
GENERATE_TO_JSON(STRUCT_NAME, VAR_NUM, __VA_ARGS__) \
GENERATE_FROM_JSON(STRUCT_NAME, VAR_NUM, __VA_ARGS__) \

#define QPREFERENCES_STRUCT(STRUCT_NAME, FILE_PATH, ...) _QPREFERENCES_STRUCT(STRUCT_NAME, FILE_PATH, GET_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)