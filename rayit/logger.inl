//static
inline bool rt::Logger::verbose()
{
  return instance().d_verbose;
}

//static
inline std::ostream &rt::Logger::stream()
{
  return *instance().d_out;
}

//static
template <typename ...Args>
inline void rt::Logger::fatal(std::format_string<Args...> messageFmt,
                              Args &&...args, std::source_location loc)
{
  log(FATAL, messageFmt, std::forward(args)..., loc);}

//static
template <typename ...Args>
inline void rt::Logger::error(std::format_string<Args...> messageFmt,
                              Args &&...args, std::source_location loc)
{
  log(ERROR, messageFmt, std::forward(args)..., loc);
}

//static
template <typename ...Args>
inline void
rt::Logger::warning([[maybe_unused]]std::format_string<Args...> messageFmt,
                    Args &&...args, std::source_location loc)
{
#ifdef WARNING_ENABLED
  log(WARNING, messageFmt, std::forward(args)..., loc);
#endif // WARNING_ENABLED
}

//static
template <typename ...Args>
inline void rt::Logger::info(std::format_string<Args...> messageFmt,
                             Args &&...args, std::source_location loc)
{
  log(INFO, messageFmt, std::forward(args)..., loc);
}

//static
template <typename ...Args>
inline void
rt::Logger::debug([[maybe_unused]] std::format_string<Args...> messageFmt,
                  Args &&...args, std::source_location loc)
{
#ifdef DEBUG_ENABLED
  log(DEBUG, messageFmt, std::forward(args)..., loc);
#endif // DEBUG_ENABLED
}

//static
template <typename ...Args>
inline void
rt::Logger::trace([[maybe_unused]] std::format_string<Args...> messageFmt,
                  Args &&...args, std::source_location loc)
{
#ifdef DEBUG_ENABLED
  log(TRACE, messageFmt, std::forward(args)..., loc);
#endif // DEBUG_ENABLED
}
