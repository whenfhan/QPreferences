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
 * @file QPreferences_global.h
 * @author Wizalm (zlwen@raysees.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-15
 * @copyright Copyright (c) 2023, Raysees Technologies Inc.
 */
#pragma once 

#include <QtCore/qglobal.h>

#if defined(QPREFERENCES_LIBRARY)
#  define QPREFERENCES_EXPORT Q_DECL_EXPORT
#else
#  define QPREFERENCES_EXPORT Q_DECL_IMPORT
#endif
