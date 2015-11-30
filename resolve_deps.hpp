#ifndef RESOLVE_DEPS_HPP
#define RESOLVE_DEPS_HPP 1

namespace package_manager_manager {
    template <typename>
        using list_type = std::forward_list<typename>;

    class version_specifier {
    private:
        std::string version;
        int relationship;
    public:
        version_specifier(version, relationship);
        bool operator () (string::version);
    }

    version_specifier str_to_pvs(std::string);

    class package_dependency_resolver {
    public:
        dependency_resolver(
            // function that takes a name and returns a list of version strings
            std::function<void(std::string,
                               list_type<std::string> &)> get_available_versions,
            // function that takes a two package names and their versions
            // and returns any inherent conflicts between the two packages
            std::function<bool(std::string, std::string,
                               std::string, std::string)> inherent_conflicts,
            // function that takes two version strings and compares them
            std::function<int(std::string, std::string)> version_compare
            );

        void resolve_package_dependencies(
            std::string name,
            list_type<version_specifier> dependencies,
            list_type<version_specifier> conflicts);

    private:
        typedef std::tuple<std::string, int, std::string>
            version_spec_type;

        // function that takes a name and returns a list of version strings
        std::function<void(std::string,
                           list_type<std::string> &)> get_available_versions;
        // function that takes a two package names and their versions
        // and returns any inherent conflicts between the two packages
        std::function<bool(std::string, std::string,
                           std::string, std::string)> inherent_conflicts;
        // function that takes two version strings and compares them
        std::function<int(std::string, std::string)> version_compare;
    };

    class package_manager(dependency_resolver_install,
                          dependency_resolver_remove,
                          remove_all_action,
                          install_all_action) {
    public:
        install(name);
        remove(name);
    };
}
#endif // RESOLVE_DEPS_HPP
