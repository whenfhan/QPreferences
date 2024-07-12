#pragma once 

#include <QtCore/qglobal.h>

#if defined(QPREFERENCES_LIBRARY)
#  define QPREFERENCES_EXPORT Q_DECL_EXPORT
#else
#  define QPREFERENCES_EXPORT Q_DECL_IMPORT
#endif
