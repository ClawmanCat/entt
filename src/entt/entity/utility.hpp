#ifndef ENTT_ENTITY_UTILITY_HPP
#define ENTT_ENTITY_UTILITY_HPP

#include "../core/type_traits.hpp"

namespace entt {

/**
 * @brief Alias for exclusion lists.
 * @tparam Type List of types.
 */
template<typename... Type>
struct exclude_t: type_list<Type...> {};

/**
 * @brief Variable template for exclusion lists.
 * @tparam Type List of types.
 */
template<typename... Type>
inline constexpr exclude_t<Type...> exclude{};

/**
 * @brief Alias for lists of observed components.
 * @tparam Type List of types.
 */
template<typename... Type>
struct get_t: type_list<Type...> {};

/**
 * @brief Variable template for lists of observed components.
 * @tparam Type List of types.
 */
template<typename... Type>
inline constexpr get_t<Type...> get{};

/**
 * @brief Alias for lists of owned components.
 * @tparam Type List of types.
 */
template<typename... Type>
struct owned_t: type_list<Type...> {};

/**
 * @brief Variable template for lists of owned components.
 * @tparam Type List of types.
 */
template<typename... Type>
inline constexpr owned_t<Type...> owned{};

/**
 * @brief Returns a reference to an instance of the given empty type.
 * No new objects are created: the reference is acquired through type punning.
 * @tparam Type An empty standard-layout type to create a reference to.
 * @return A reference to an instance of type @p Type.
 */
template <typename Type> inline Type& fake_storage_for(void) {
    static_assert(
        std::is_empty_v<Type> && std::is_standard_layout_v<Type>,
        "Fake storage can only be created for empty standard-layout types."
    );

    struct empty_type {};
    static union { empty_type a; Type b; } storage { empty_type { } };

    return storage.b;
}

} // namespace entt

#endif
