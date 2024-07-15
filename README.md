# QPreferences
该项目是基于nlohmann/json的qt可视化配置文件，通过cmake可快速添加进项目。支持常用基本类型如基本类型和stl常用容器，若想添加不支持的类型，可参考nlohmann/json自行实现to_json和from_json函数。
## Learn
1、创建配置文件结构体 (默认值一定要加括号，下面有示例)
```c++
QPREFERENCES_STRUCT(配置结构体名, 配置文件路径(若为子配置结构体，则写"")
                    , 类型, 变量名(与json文件命名相同), 默认值
                    ...
                    最多支持40个变量(若不够则使用结构体嵌套，结构体算一个变量)
)
```
2、配置文件结构体有load()、save()、showUI()函数，我们需要在程序开头调用load()函数，否则参数都是默认值。若设置了配置文件路径，硬盘上不存在该文件，则会自动创建配置文件，并写入默认值json。(创建配置文件在构造函数，一定会在load之前，所以放心load就好)
```c++
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Preferences::GetInstance()->load();
}
```
3、将显示接口写入对应动作
```c++
void MainWindow::on_pushButton_clicked()
{
    Preferences::GetInstance()->showUI();
}
```
## Example
mainwindow.cpp源码
```c++
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Preferences.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Preferences::GetInstance()->load();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Preferences::GetInstance()->showUI();
}


```
Preferences.h源码
```c++
#pragma once

#include <QPreferences.hpp>
#include <vector>
#include <string>

QPREFERENCES_STRUCT(SubPref, ""
                    , int           , sub_option1, (0)
                    , double        , sub_option2, (5.0)
                    , std::string   , sub_option3, ({"wizalm"})
                    )

QPREFERENCES_STRUCT(Preferences, "Preferences/Preferences.json"
                    , int               , option1   , (1)
                    , double            , option2   , (2)
                    , std::vector<int>  , option3   , ({1, 2, 3})
                    , SubPref           , sub_pref  , ()
                    )

```
配置文件显示，双击可修改，会修改后会判断输入值是否与原本类型兼容，若不兼容则输入无效。动图如下(动图有点大，加载可能会比较慢)

![./pic/QPreferences_gif.gif](./pic/QPreferences_gif.gif)