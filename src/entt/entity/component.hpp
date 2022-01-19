#ifndef ENTT_ENTITY_COMPONENT_HPP
#define ENTT_ENTITY_COMPONENT_HPP

#include <type_traits>
#include "../config/config.h"

namespace entt {

/*! @brief Commonly used default traits for all types. */
struct basic_component_traits {
    /*! @brief Pointer stability, default is `false`. */
    static constexpr auto in_place_delete = false;
    /*! @brief Empty type optimization, default is `ENTT_IGNORE_IF_EMPTY`. */
    static constexpr auto ignore_if_empty = ENTT_IGNORE_IF_EMPTY;
    /*! @brief Page size, default is `ENTT_PACKED_PAGE`. */
    static constexpr auto page_size = ENTT_PACKED_PAGE;
};

/**
 * @brief Common way to access various properties of components.
 * @tparam Type Type of component.
 */
template<typename Type, typename = void>
struct component_traits: basic_component_traits {
    static_assert(std::is_same_v<std::decay_t<Type>, Type>, "Unsupported type");
};

/**
 * @brief Checks if a given component type is eligible for ETO.
 * @tparam Type Type of component.
 */
template<typename Type>
inline constexpr bool apply_eto_v =
    component_traits<Type>::ignore_if_empty &&
    std::is_empty_v<Type> &&
    std::is_standard_layout_v<Type> &&
    std::is_trivially_destructible_v<Type> &&
    std::is_trivially_move_constructible_v<Type> &&
    std::is_trivially_move_assignable_v<Type>;

/**
 * @brief Checks if a given component is empty and thus need not be stored in snapshots.
 *
 * This differs from apply_eto_v in that ETO does not apply to components that have side
 * effects on moving / destructing them, and that ETO components must be standard layout
 * types to perform the type punning trick.
 *
 * @tparam Type Type of component.
 */
template <typename Type>
inline constexpr bool elude_serialization_v =
    component_traits<Type>::ignore_if_empty &&
    std::is_empty_v<Type>;

} // namespace entt

#endif
