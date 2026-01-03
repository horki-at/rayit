#ifndef INCLUDED_LOGGER_
#define INCLUDED_LOGGER_

#include <utility>
#include <iostream>
#include <print>
#include <source_location>
#include <string_view>

// TODO: make Logger thread safe
// TODO: make Logger also output timestamp
namespace rt
{
  /// Stores information needed for message formatting.
  template <typename ...Args>
  struct LogMessage
  {
    std::format_string<Args...> msg;
    std::source_location loc;

    template <typename T>
    consteval LogMessage(T const &msg, std::source_location loc
                         = std::source_location::current());
  };

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
    static void fatal(std::type_identity_t<LogMessage<Args...>> msg, Args &&...args);
    template <typename ...Args>
    static void error(std::type_identity_t<LogMessage<Args...>> msg, Args &&...args);
    template <typename ...Args>
    static void warning(std::type_identity_t<LogMessage<Args...>> msg, Args &&...args);
    template <typename ...Args>
    static void info(std::type_identity_t<LogMessage<Args...>> msg, Args &&...args);
    template <typename ...Args>
    static void debug(std::type_identity_t<LogMessage<Args...>> msg, Args &&...args);
    template <typename ...Args>
    static void trace(std::type_identity_t<LogMessage<Args...>> msg, Args &&...args);

  private:
    Logger() = default;
    Logger(Logger const &) = delete;
    Logger(Logger &&) = delete;
    Logger &operator=(Logger const &) = delete;
    Logger &operator=(Logger &&) = delete;

    static Logger &instance();
    static std::ostream &stream();
    
    template <typename ...Args>
    static void log(Level level, LogMessage<Args...>, Args &&...args);

    static char const *getLevelString(Level level);
  };
};

#include "logger.inl"
#include "logger.tpp"
#endif // INCLUDED_LOGGER_
