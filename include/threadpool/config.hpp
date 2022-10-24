#pragma once

#ifndef THREADPOOL_CONFIG_HPP
#define THREADPOOL_CONFIG_HPP

#if defined(_WIN32)
#define THREADPOOL_EXPORT __declspec(dllexport)
#define THREADPOOL_IMPORT __declspec(dllimport)
#elif defined(__ANDROID__)
#define THREADPOOL_EXPORT __attribute__((visibility("default")))
#define THREADPOOL_IMPORT __attribute__((visibility("default")))
#elif defined(__linux__)
#define THREADPOOL_EXPORT __attribute__((visibility("default")))
#define THREADPOOL_IMPORT __attribute__((visibility("default")))
#elif defined(__FreeBSD__)
#define THREADPOOL_EXPORT __attribute__((visibility("default")))
#define THREADPOOL_IMPORT __attribute__((visibility("default")))
#elif
#error "Platform not supported"
#endif

#if !defined(THREADPOOL_STATIC)
#ifdef THREADPOOL_BUILD
#define THREADPOOL_API THREADPOOL_EXPORT
#else
#define THREADPOOL_API THREADPOOL_IMPORT
#endif
#else
#define THREADPOOL_API
#endif

#endif