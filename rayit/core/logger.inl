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

};
