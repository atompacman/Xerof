#pragma once

// - === - === - === - === - === - === - === - === - === - === - === - === - ===
// Shortcuts for formatted logging
// - === - === - === - === - === - === - === - === - === - === - === - === - ===

template <typename T, typename... Args>
void LOG_TRACE_F(const char* format, const T& value, const Args&... args)
{
	el::Loggers::getLogger("default")->trace(format, value, args...);
}

template <typename T, typename... Args>
void LOG_WARNING_F(const char* format, const T& value, const Args&... args)
{
	el::Loggers::getLogger("default")->warn(format, value, args...);
}

template <typename T, typename... Args>
void LOG_DEBUG_F(const char* format, const T& value, const Args&... args)
{
	el::Loggers::getLogger("default")->debug(format, value, args...);
}

template <typename T, typename... Args>
void LOG_INFO_F(const char* format, const T& value, const Args&... args)
{
	el::Loggers::getLogger("default")->info(format, value, args...);
}

template <typename T, typename... Args>
void LOG_FATAL_F(const char* format, const T& value, const Args&... args)
{
	el::Loggers::getLogger("default")->fatal(format, value, args...);
}