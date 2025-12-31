namespace rt
{
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
