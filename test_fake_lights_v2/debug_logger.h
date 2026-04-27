/**
 * Fake Lights 2.0 Debug Logger
 * 
 * Gebruik: 
 *   FL2_LOG_DEBUG("Waarde: %f", waarde);
 *   FL2_LOG_SCOPE("Berekening");
 *   
 * Compile met -DFAKE_LIGHTS_DEBUG om logging in te schakelen
 */

#ifndef FAKE_LIGHTS_DEBUG_LOGGER_H
#define FAKE_LIGHTS_DEBUG_LOGGER_H

#include <cstdio>
#include <cstdarg>
#include <chrono>
#include <string>
#include <fstream>
#include <iostream>

// Debug level definities
#define FL2_LOG_LEVEL_NONE    0
#define FL2_LOG_LEVEL_ERROR   1
#define FL2_LOG_LEVEL_WARNING 2
#define FL2_LOG_LEVEL_INFO    3
#define FL2_LOG_LEVEL_DEBUG   4
#define FL2_LOG_LEVEL_TRACE   5

// Standaard log level (aanpasbaar via compile flag)
#ifndef FL2_LOG_LEVEL
#ifdef FAKE_LIGHTS_DEBUG
#define FL2_LOG_LEVEL FL2_LOG_LEVEL_DEBUG
#else
#define FL2_LOG_LEVEL FL2_LOG_LEVEL_INFO
#endif
#endif

namespace fake_lights {

class DebugLogger {
public:
    static DebugLogger& Instance() {
        static DebugLogger instance;
        return instance;
    }
    
    void SetLevel(int level) { level_ = level; }
    void SetFile(const std::string& filename) {
        file_.open(filename, std::ios::out | std::ios::trunc);
        useFile_ = true;
    }
    
    void Log(int level, const char* file, int line, const char* func, const char* fmt, ...) {
        if (level > level_) return;
        
        const char* levelStr = "?";
        switch (level) {
            case FL2_LOG_LEVEL_ERROR:   levelStr = "ERROR"; break;
            case FL2_LOG_LEVEL_WARNING: levelStr = "WARN"; break;
            case FL2_LOG_LEVEL_INFO:    levelStr = "INFO"; break;
            case FL2_LOG_LEVEL_DEBUG:   levelStr = "DEBUG"; break;
            case FL2_LOG_LEVEL_TRACE:   levelStr = "TRACE"; break;
        }
        
        // Tijd opnemen
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(now - startTime_).count();
        
        // Buffer voor bericht
        char buffer[1024];
        va_list args;
        va_start(args, fmt);
        vsnprintf(buffer, sizeof(buffer), fmt, args);
        va_end(args);
        
        // Format: [time][LEVEL][file:line] message
        char output[2048];
        snprintf(output, sizeof(output), "[%10.3f][%5s][%s:%d] %s\n", 
                 elapsed / 1000.0, levelStr, file, line, buffer);
        
        // Output
        if (useFile_ && file_.is_open()) {
            file_ << output;
            file_.flush();
        }
        
        // Altijd naar cerr in debug mode
        #ifdef FAKE_LIGHTS_DEBUG
        std::cerr << output;
        #endif
    }
    
    void BeginScope(const char* name) {
        scopeDepth_++;
        Log(FL2_LOG_LEVEL_TRACE, "", 0, name, ">>> BEGIN %s", name);
    }
    
    void EndScope(const char* name) {
        Log(FL2_LOG_LEVEL_TRACE, "", 0, name, ">>> END %s", name);
        scopeDepth_--;
    }

private:
    DebugLogger() : level_(FL2_LOG_LEVEL_INFO), useFile_(false), scopeDepth_(0) {
        startTime_ = std::chrono::steady_clock::now();
    }
    
    ~DebugLogger() {
        if (file_.is_open()) file_.close();
    }
    
    int level_;
    bool useFile_;
    std::ofstream file_;
    std::chrono::steady_clock::time_point startTime_;
    int scopeDepth_;
};

} // namespace fake_lights

// Macro's voor eenvoudig gebruik
#if FL2_LOG_LEVEL >= FL2_LOG_LEVEL_ERROR
#define FL2_LOG_ERROR(fmt, ...) \
    fake_lights::DebugLogger::Instance().Log(FL2_LOG_LEVEL_ERROR, __FILE__, __LINE__, __FUNCTION__, fmt, ##__VA_ARGS__)
#else
#define FL2_LOG_ERROR(fmt, ...)
#endif

#if FL2_LOG_LEVEL >= FL2_LOG_LEVEL_WARNING
#define FL2_LOG_WARN(fmt, ...) \
    fake_lights::DebugLogger::Instance().Log(FL2_LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, fmt, ##__VA_ARGS__)
#else
#define FL2_LOG_WARN(fmt, ...)
#endif

#if FL2_LOG_LEVEL >= FL2_LOG_LEVEL_INFO
#define FL2_LOG_INFO(fmt, ...) \
    fake_lights::DebugLogger::Instance().Log(FL2_LOG_LEVEL_INFO, __FILE__, __LINE__, __FUNCTION__, fmt, ##__VA_ARGS__)
#else
#define FL2_LOG_INFO(fmt, ...)
#endif

#if FL2_LOG_LEVEL >= FL2_LOG_LEVEL_DEBUG
#define FL2_LOG_DEBUG(fmt, ...) \
    fake_lights::DebugLogger::Instance().Log(FL2_LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, fmt, ##__VA_ARGS__)
#else
#define FL2_LOG_DEBUG(fmt, ...)
#endif

#if FL2_LOG_LEVEL >= FL2_LOG_LEVEL_TRACE
#define FL2_LOG_TRACE(fmt, ...) \
    fake_lights::DebugLogger::Instance().Log(FL2_LOG_LEVEL_TRACE, __FILE__, __LINE__, __FUNCTION__, fmt, ##__VA_ARGS__)
#else
#define FL2_LOG_TRACE(fmt, ...)
#endif

// Scope tracer
class FL2ScopeTracer {
public:
    FL2ScopeTracer(const char* name) : name_(name) {
        fake_lights::DebugLogger::Instance().BeginScope(name);
    }
    ~FL2ScopeTracer() {
        fake_lights::DebugLogger::Instance().EndScope(name_);
    }
private:
    const char* name_;
};

#define FL2_LOG_SCOPE(name) FL2ScopeTracer FL2_CONCAT(scope_, __LINE__)(name)
#define FL2_CONCAT(a, b) a ## b

#endif // FAKE_LIGHTS_DEBUG_LOGGER_H
