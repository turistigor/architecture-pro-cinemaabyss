#ifndef EVENTS_ENVS_H
#define EVENTS_ENVS_H

template<typename T>
T get_env(const std::string& key, T default_value = T{});


#endif  // EVENTS_ENVS_H
