#pragma once

#include <QtCore/qglobal.h>

#if defined(WT2_LIBRARY)
#  define WT2_EXPORT Q_DECL_EXPORT
#else
#  define WT2_EXPORT Q_DECL_IMPORT
#endif
