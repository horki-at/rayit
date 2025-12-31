//static
template <typename ...Args>
void rt::Logger::log(Level level, std::format_string<Args...> messageFmt,
                     Args &&...args, std::source_location loc)
{
 Logger &logger = instance();

  if (logger.verbose())         // LEVEL [FILE:LINE, FUNCTION]: ...
    std::print(logger.stream(), "{} [{}:{}, {}]: ",
               getLevelString(level),
               loc.file_name(),
               loc.line(),
               loc.function_name());
  else                          // LEVEL: ...
    std::print(logger.stream(), "{}: ", getLevelString(level));
  std::println(logger.stream(), messageFmt, std::forward<Args>(args)...);
}
