#include <spdlog/spdlog.h>
#define INDEX_ERROR(...) SPDLOG_ERROR(__VA_ARGS__)
#define INDEX_WARN(...) SPDLOG_WARN(__VA_ARGS__)
#define INDEX_INFO(...) SPDLOG_INFO(__VA_ARGS__)
#define INDEX_DEBUG(...) SPDLOG_DEBUG(__VA_ARGS__)
#define INDEX_TRACE(...) SPDLOG_TRACE(__VA_ARGS__)
