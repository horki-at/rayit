#ifndef INCLUDED_LOGGER_
#define INCLUDED_LOGGER_

#include <utility>
#include <iostream>
#include <print>
#include <source_location>

// TODO: make Logger thread safe
// TODO: make Logger also output timestamp
namespace rt
{
  class Logger final
  {
    enum Level { FATAL, ERROR, WARNING, INFO, DEBUG, TRACE };
    static bool s_initialized;

    std::ostream *d_out;
    bool d_verbose;             // when true, outputs exact location of the log

  public:
    static void initialize(std::ostream &out, bool verbose = false);
    static bool verbose();

    template <typename ...Args>
    static void fatal(std::format_string<Args...> messageFmt, Args &&...args,
                      std::source_location loc = std::source_location::current());

    template <typename ...Args>
    static void error(std::format_string<Args...> messageFmt, Args &&...args,
                      std::source_location loc = std::source_location::current());

    template <typename ...Args>
    static void warning(std::format_string<Args...> messageFmt, Args &&...args,
                        std::source_location loc = std::source_location::current());

    template <typename ...Args>
    static void info(std::format_string<Args...> messageFmt, Args &&...args,
                     std::source_location loc = std::source_location::current());

    template <typename ...Args>
    static void debug(std::format_string<Args...> messageFmt, Args &&...args,
                      std::source_location loc = std::source_location::current());
    
    template <typename ...Args>
    static void trace(std::format_string<Args...> messageFmt, Args &&...args,
                      std::source_location loc = std::source_location::current());

  private:
    Logger() = default;
    Logger(Logger const &) = delete;
    Logger(Logger &&) = delete;
    Logger &operator=(Logger const &) = delete;
    Logger &operator=(Logger &&) = delete;

    static Logger &instance();
    static std::ostream &stream();
    
    template <typename ...Args>
    static void log(Level level, std::format_string<Args...> messageFmt,
                    Args &&...args,
                    std::source_location loc = std::source_location::current());

    static char const *getLevelString(Level level);
  };
};

#include "logger.inl"
#include "logger.tpp"
#endif // INCLUDED_LOGGER_
