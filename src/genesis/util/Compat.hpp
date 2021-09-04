#pragma once
#if __has_include(<optional>)
    #include <optional>
    template <typename T>
    using StdOptional = std::optional<T>;
#else
    #include <experimental/optional>
    using StdOptional = std::experimental::optional;
#endif

#if __has_include(<filesystem>)
    #include <filesystem>
    namespace fs = std::filesystem;
#else
    #include "experimental/filesystem"
    namespace fs = std::experimental::filesystem;
#endif

namespace EnvironmentUtil {

inline std::string getEnv(const char* name, const std::string& fail = "") {
#if defined(_WIN32) || defined(_WIN64)
    char* value = nullptr;
    size_t len = 0;
    errno_t err = _dupenv_s(&value, &len, name);
    if (err != 0 || value == nullptr)
        return fail;

    std::string retVal(value);
    return retVal;
#elif defined _GNU_SOURCE
    // _GNU_SOURCE is predefined with libstdc++ (GCC's stdlib),
    // and when it's defined, it grants access to secure_getenv.
    // Dunno if this works outside linux, hence why there's no
    // forced enablign of _GNU_SOURCE
    char* output = secure_getenv(name);
    if (!output)
        return fail;
    return std::string(output);
#else
    // overkill? Could just fall back to getenv()
#error "Failed to find a secure getenv() - please open an issue on GitHub."
#endif
}

}
