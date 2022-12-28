#pragma once

#ifndef SIMPLETHREADPOOL_CONFIG_HPP
#define SIMPLETHREADPOOL_CONFIG_HPP

#if defined(_WIN32)
#define SIMPLETHREADPOOL_EXPORT __declspec(dllexport)
#define SIMPLETHREADPOOL_IMPORT __declspec(dllimport)
#elif defined(__ANDROID__)
#define SIMPLETHREADPOOL_EXPORT __attribute__((visibility("default")))
#define SIMPLETHREADPOOL_IMPORT __attribute__((visibility("default")))
#elif defined(__linux__)
#define SIMPLETHREADPOOL_EXPORT __attribute__((visibility("default")))
#define SIMPLETHREADPOOL_IMPORT __attribute__((visibility("default")))
#elif defined(__APPLE__)
#define SIMPLETHREADPOOL_EXPORT __attribute__((visibility("default")))
#define SIMPLETHREADPOOL_IMPORT __attribute__((visibility("default")))
#elif defined(__unix__)
#include <sys/param.h>
#if defined(BSD)
#define SIMPLETHREADPOOL_EXPORT __attribute__((visibility("default")))
#define SIMPLETHREADPOOL_IMPORT __attribute__((visibility("default")))
#endif
#elif defined(__WASM__)
#define SIMPLETHREADPOOL_EXPORT
#define SIMPLETHREADPOOL_IMPORT
#else
#error "Platform not supported"
#endif

#if !defined(SIMPLETHREADPOOL_STATIC)
#ifdef SIMPLETHREADPOOL_BUILD
#define SIMPLETHREADPOOL_API SIMPLETHREADPOOL_EXPORT
#else
#define SIMPLETHREADPOOL_API SIMPLETHREADPOOL_IMPORT
#endif
#else
#define SIMPLETHREADPOOL_API
#endif

#endif
