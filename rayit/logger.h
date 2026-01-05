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

namespace rt
{
  template <typename ...Args>
  template <typename T>
  consteval inline
  LogMessage<Args...>::LogMessage(T const &msg, std::source_location loc)
    : msg(msg)
    , loc(loc)
  {
  }

//static
  inline bool Logger::verbose()
  {
    return instance().d_verbose;
  }

//static
  inline std::ostream &Logger::stream()
  {
    return *instance().d_out;
  }

//static
  template <typename ...Args>
  inline void Logger::fatal(std::type_identity_t<LogMessage<Args...>> msg,
                            Args &&...args)
  {
    log(FATAL, msg, std::forward<Args>(args)...);
  }

//static
  template <typename ...Args>
  inline void Logger::error(std::type_identity_t<LogMessage<Args...>> msg,
                            Args &&...args)
  {
    log(ERROR, msg, std::forward<Args>(args)...);
  }

//static
  template <typename ...Args>
  inline void
  Logger::warning([[maybe_unused]] std::type_identity_t<LogMessage<Args...>> msg,
                  Args &&...args)
  {
#ifdef WARNING_ENABLED
    log(WARNING, msg, std::forward<Args>(args)...);
#endif
  }

//static
  template <typename ...Args>
  inline void Logger::info(std::type_identity_t<LogMessage<Args...>> msg,
                           Args &&...args)
  {
    log(INFO, msg, std::forward<Args>(args)...);
  }

//static
  template <typename ...Args>
  inline void
  Logger::debug([[maybe_unused]] std::type_identity_t<LogMessage<Args...>> msg,
                Args &&...args)
  {
#ifdef DEBUG_ENABLED
    log(DEBUG, msg, std::forward<Args>(args)...);
#endif
  }

//static
  template <typename ...Args>
  inline void
  Logger::trace([[maybe_unused]] std::type_identity_t<LogMessage<Args...>> msg,
                Args &&...args)
  {
#ifdef DEBUG_ENABLED
    log(TRACE, msg, std::forward<Args>(args)...);
#endif
  }

//static
  template <typename ...Args>
  void Logger::log(Level level, LogMessage<Args...> msg, Args &&...args)
  {
    Logger &logger = instance();

    if (logger.verbose())         // LEVEL [FILE:LINE, FUNCTION]: ...
      std::print(logger.stream(), "{} [{}:{}, {}]: ", 
                 getLevelString(level),
                 msg.loc.file_name(),
                 msg.loc.line(),
                 msg.loc.function_name());
    else                          // LEVEL: ...
      std::print(logger.stream(), "{}: ", getLevelString(level));
    std::println(logger.stream(), msg.msg, std::forward<Args>(args)...);
  }
};
#endif // INCLUDED_LOGGER_
