#ifndef IMAGEPROCESS_GLOBAL_H
#define IMAGEPROCESS_GLOBAL_H

#ifdef IMAGEPROCESS_LIB
#define IMAGEPROCESS_EXPORT __declspec(dllexport)
//#define IMAGEPROCESS_EXPORT Q_DECL_EXPORT
//
#else
#define IMAGEPROCESS_EXPORT __declspec(dllimport)
//#define IMAGEPROCESS_EXPORT Q_DECL_IMPORT
#endif

#endif // IMAGEPROCESS_GLOBAL_H
