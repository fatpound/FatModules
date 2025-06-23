module;

export module FatPound.Traits.Modification;

import std;

export namespace fatpound::traits
{
    template <typename Holder, typename T>
    struct Append;

    template <template <typename...> typename Holder, typename Head, typename... Tail>
    struct Append<Holder<Tail...>, Head>
    {
        using Type = Holder<Tail..., Head>;
    };

    template <typename Holder, typename T>
    using Append_t = Append<Holder, T>::Type;



    template <typename Holder, auto Item>
    struct AppendItem;

    template <template <auto...> typename Holder, auto Head, auto... Tail>
    struct AppendItem<Holder<Tail...>, Head>
    {
        using Type = Holder<Tail..., Head>;
    };

    template <typename Holder, auto Item>
    using AppendItem_t = AppendItem<Holder, Item>::Type;



    template <typename Holder, typename T>
    struct AppendUnique;

    template <template <typename...> typename Holder, typename Head, typename... Tail>
    struct AppendUnique<Holder<Tail...>, Head>
    {
        using Type = std::conditional_t<(std::same_as<Head, Tail> or ...), Holder<Tail...>, Holder<Tail..., Head>>;
    };

    template <typename Holder, typename T>
    using AppendUnique_t = AppendUnique<Holder, T>::Type;



    template <typename Holder, auto Item>
    struct AppendItemUnique;

    template <template <auto...> typename Holder, auto Head, auto... Tail>
    struct AppendItemUnique<Holder<Tail...>, Head>
    {
        using Type = std::conditional_t<((Head == Tail) or ...), Holder<Tail...>, Holder<Tail..., Head>>;
    };

    template <typename Holder, auto Item>
    using AppendItemUnique_t = AppendItemUnique<Holder, Item>::Type;



    template <typename Holder, typename T>
    struct Prepend;

    template <template <typename...> typename Holder, typename Head, typename... Tail>
    struct Prepend<Holder<Tail...>, Head>
    {
        using Type = Holder<Head, Tail...>;
    };

    template <typename Holder, typename T>
    using Prepend_t = Prepend<Holder, T>::Type;



    template <typename Holder, auto Item>
    struct PrependItem;

    template <template <auto...> typename Holder, auto Head, auto... Tail>
    struct PrependItem<Holder<Tail...>, Head>
    {
        using Type = Holder<Head, Tail...>;
    };

    template <typename Holder, auto Item>
    using PrependItem_t = PrependItem<Holder, Item>::Type;



    template <typename Holder, typename T>
    struct PrependUnique;

    template <template <typename...> typename Holder, typename Head, typename... Tail>
    struct PrependUnique<Holder<Tail...>, Head>
    {
        using Type = std::conditional_t<(std::same_as<Head, Tail> or ...), Holder<Tail...>, Holder<Head, Tail...>>;
    };

    template <typename Holder, typename T>
    using PrependUnique_t = PrependUnique<Holder, T>::Type;



    template <typename Holder, auto Item>
    struct PrependItemUnique;

    template <template <auto...> typename Holder, auto Head, auto... Tail>
    struct PrependItemUnique<Holder<Tail...>, Head>
    {
        using Type = std::conditional_t<((Head == Tail) or ...), Holder<Tail...>, Holder<Head, Tail...>>;
    };

    template <typename Holder, auto Item>
    using PrependItemUnique_t = PrependItemUnique<Holder, Item>::Type;



    template <typename Holder>
    struct Reverse;

    template <template <typename...> typename Holder>
    struct Reverse<Holder<>>
    {
        using Type = Holder<>;
    };

    template <template <typename...> typename Holder, typename Head, typename... Tail>
    struct Reverse<Holder<Head, Tail...>>
    {
        using Type = Append_t<typename Reverse<Holder<Tail...>>::Type, Head>;
    };

    template <typename Holder>
    using Reverse_t = Reverse<Holder>::Type;



    template <typename Holder>
    struct ReverseItem;

    template <template <auto...> typename Holder>
    struct ReverseItem<Holder<>>
    {
        using Type = Holder<>;
    };

    template <template <auto...> typename Holder, auto Head, auto... Tail>
    struct ReverseItem<Holder<Head, Tail...>>
    {
        using Type = AppendItem_t<typename ReverseItem<Holder<Tail...>>::Type, Head>;
    };

    template <typename Holder>
    using ReverseItem_t = ReverseItem<Holder>::Type;



    template <typename Holder, typename BiPred>
    struct FindIfItem;

    template <template <auto...> typename Holder, typename BiPred>
    struct FindIfItem<Holder<>, BiPred>
    {
        static_assert(false, "Item Holder is EMPTY!");
    };

    template <template <auto...> typename Holder, auto Head, typename BiPred>
    struct FindIfItem<Holder<Head>, BiPred>
    {
        static constexpr auto value = Head;
    };

    template <template <auto...> typename Holder, auto Head, auto Next, auto... Tail, typename BiPred>
    struct FindIfItem<Holder<Head, Next, Tail...>, BiPred>
    {
    private:
        static constexpr auto filtered_item = FindIfItem<Holder<Next, Tail...>, BiPred>::value;

    public:
        static constexpr auto value = BiPred{}(Head, filtered_item) ? Head : filtered_item;
    };

    template <typename Holder, typename BiPred>
    constexpr auto FindIfItem_v = FindIfItem<Holder, BiPred>::value;



    template <typename Holder, typename UnPred>
    struct CountIfItem;

    template <template <auto...> typename Holder, typename UnPred>
    struct CountIfItem<Holder<>, UnPred>
    {
        static constexpr auto value = 0;
    };

    template <template <auto...> typename Holder, auto Head, auto... Tail, typename UnPred>
    struct CountIfItem<Holder<Head, Tail...>, UnPred>
    {
    private:
        static constexpr auto filtered_item = CountIfItem<Holder<Tail...>, UnPred>::value;

    public:
        static constexpr auto value = filtered_item + (UnPred{}(Head) ? 1 : 0);
    };

    template <typename Holder, typename UnPred>
    constexpr auto CountIfItem_v = CountIfItem<Holder, UnPred>::value;



    template <typename Holder>
    struct MinItem;

    template <template <auto...> typename Holder, auto... Values>
    struct MinItem<Holder<Values...>>
    {
        static constexpr auto value = FindIfItem_v<Holder<Values...>, decltype([](const auto& a, const auto& b) consteval noexcept -> bool { return a < b; })>;
    };

    template <typename Holder>
    constexpr auto MinItem_v = MinItem<Holder>::value;



    template <typename Holder>
    struct MaxItem;

    template <template <auto...> typename Holder, auto... Values>
    struct MaxItem<Holder<Values...>>
    {
        static constexpr auto value = FindIfItem_v<Holder<Values...>, decltype([](const auto& a, const auto& b) consteval noexcept -> bool { return a > b; })>;
    };

    template <typename Holder>
    constexpr auto MaxItem_v = MaxItem<Holder>::value;
}

module : private;

#ifdef IN_DEBUG

namespace fatpound::traits
{
    template <typename... Ts> struct _type_holder_ final {};
    template <auto... Values> struct _item_holder_ final {};


#define FATLIB_MODIFICATION_TRAITS_STATIC_ASSERT_TESTS_GENERATOR1(item, holder_t, A, B, C, D)                                \
    static_assert(std::same_as<       Append##item##_t<holder_t<>          ,        A>,        holder_t<A>>);                \
    static_assert(std::same_as<       Append##item##_t<holder_t<A>         ,        B>,        holder_t<A, B>>);             \
    static_assert(std::same_as<       Append##item##_t<holder_t<A, B>      ,        C>,        holder_t<A, B, C>>);          \
    static_assert(std::same_as<       Append##item##_t<holder_t<A, B, C>   ,        D>,        holder_t<A, B, C, D>>);       \
                                                                                                                             \
    static_assert(std::same_as<       Append##item##_t<holder_t<A>         ,        A>,        holder_t<A, A>>);             \
    static_assert(std::same_as<       Append##item##_t<holder_t<A, B>      ,        B>,        holder_t<A, B, B>>);          \
    static_assert(std::same_as<       Append##item##_t<holder_t<A, B, C>   ,        C>,        holder_t<A, B, C, C>>);       \
    static_assert(std::same_as<       Append##item##_t<holder_t<A, B, C, D>,        D>,        holder_t<A, B, C, D, D>>);    \
                                                                                                                             \
    static_assert(std::same_as< Append##item##Unique_t<holder_t<>          ,        A>,        holder_t<A>>);                \
    static_assert(std::same_as< Append##item##Unique_t<holder_t<A>         ,        B>,        holder_t<A, B>>);             \
    static_assert(std::same_as< Append##item##Unique_t<holder_t<A, B>      ,        C>,        holder_t<A, B, C>>);          \
    static_assert(std::same_as< Append##item##Unique_t<holder_t<A, B, C>   ,        D>,        holder_t<A, B, C, D>>);       \
                                                                                                                             \
    static_assert(std::same_as< Append##item##Unique_t<holder_t<A>         ,        A>,        holder_t<A>>);                \
    static_assert(std::same_as< Append##item##Unique_t<holder_t<A, B>      ,        B>,        holder_t<A, B>>);             \
    static_assert(std::same_as< Append##item##Unique_t<holder_t<A, B, C>   ,        C>,        holder_t<A, B, C>>);          \
    static_assert(std::same_as< Append##item##Unique_t<holder_t<A, B, C, D>,        D>,        holder_t<A, B, C, D>>);       \
                                                                                                                             \
                                                                                                                             \
    static_assert(std::same_as<      Prepend##item##_t<holder_t<>          ,        A>,        holder_t<A>>);                \
    static_assert(std::same_as<      Prepend##item##_t<holder_t<A>         ,        B>,        holder_t<B, A>>);             \
    static_assert(std::same_as<      Prepend##item##_t<holder_t<B, A>      ,        C>,        holder_t<C, B, A>>);          \
    static_assert(std::same_as<      Prepend##item##_t<holder_t<C, B, A>   ,        D>,        holder_t<D, C, B, A>>);       \
                                                                                                                             \
    static_assert(std::same_as<      Prepend##item##_t<holder_t<A>         ,        A>,        holder_t<A, A>>);             \
    static_assert(std::same_as<      Prepend##item##_t<holder_t<B, A>      ,        B>,        holder_t<B, B, A>>);          \
    static_assert(std::same_as<      Prepend##item##_t<holder_t<C, B, A>   ,        C>,        holder_t<C, C, B, A>>);       \
    static_assert(std::same_as<      Prepend##item##_t<holder_t<D, C, B, A>,        D>,        holder_t<D, D, C, B, A>>);    \
                                                                                                                             \
    static_assert(std::same_as<Prepend##item##Unique_t<holder_t<>          ,        A>,        holder_t<A>>);                \
    static_assert(std::same_as<Prepend##item##Unique_t<holder_t<A>         ,        B>,        holder_t<B, A>>);             \
    static_assert(std::same_as<Prepend##item##Unique_t<holder_t<B, A>      ,        C>,        holder_t<C, B, A>>);          \
    static_assert(std::same_as<Prepend##item##Unique_t<holder_t<C, B, A>   ,        D>,        holder_t<D, C, B, A>>);       \
                                                                                                                             \
    static_assert(std::same_as<Prepend##item##Unique_t<holder_t<A>         ,        A>,        holder_t<A>>);                \
    static_assert(std::same_as<Prepend##item##Unique_t<holder_t<B, A>      ,        B>,        holder_t<B, A>>);             \
    static_assert(std::same_as<Prepend##item##Unique_t<holder_t<C, B, A>   ,        C>,        holder_t<C, B, A>>);          \
    static_assert(std::same_as<Prepend##item##Unique_t<holder_t<D, C, B, A>,        D>,        holder_t<D, C, B, A>>);


    FATLIB_MODIFICATION_TRAITS_STATIC_ASSERT_TESTS_GENERATOR1(    , _type_holder_, int, char, double, float)
    FATLIB_MODIFICATION_TRAITS_STATIC_ASSERT_TESTS_GENERATOR1(Item, _item_holder_,   1,    2,      3,     4)


#define FATLIB_MODIFICATION_TRAITS_STATIC_ASSERT_TESTS_GENERATOR2(item, holder_t, A, B, C, D, E, F)                    \
    static_assert(std::same_as<Reverse##item##_t<holder_t<>>                     , holder_t<>>);                       \
    static_assert(std::same_as<Reverse##item##_t<holder_t<A>>                    , holder_t<A>>);                      \
    static_assert(std::same_as<Reverse##item##_t<holder_t<A, B>>                 , holder_t<B, A>>);                   \
    static_assert(std::same_as<Reverse##item##_t<holder_t<A, B, C>>              , holder_t<C, B, A>>);                \
    static_assert(std::same_as<Reverse##item##_t<holder_t<A, B, C, D>>           , holder_t<D, C, B, A>>);             \
    static_assert(std::same_as<Reverse##item##_t<holder_t<A, B, C, D, E>>        , holder_t<E, D, C, B, A>>);          \
                                                                                                                       \
    static_assert(std::same_as<Reverse##item##_t<holder_t<A, A>>                 , holder_t<A, A>>);                   \
    static_assert(std::same_as<Reverse##item##_t<holder_t<A, B, A>>              , holder_t<A, B, A>>);                \
    static_assert(std::same_as<Reverse##item##_t<holder_t<A, A, B>>              , holder_t<B, A, A>>);                \
    static_assert(std::same_as<Reverse##item##_t<holder_t<A, B, B>>              , holder_t<B, B, A>>);                \
    static_assert(std::same_as<Reverse##item##_t<holder_t<C, A, B, A>>           , holder_t<A, B, A, C>>);             \
    static_assert(std::same_as<Reverse##item##_t<holder_t<A, B, C, B, D>>        , holder_t<D, B, C, B, A>>);          \
    static_assert(std::same_as<Reverse##item##_t<holder_t<A, A, B, A, A>>        , holder_t<A, A, B, A, A>>);          \
    static_assert(std::same_as<Reverse##item##_t<holder_t<C, C, C, C>>           , holder_t<C, C, C, C>>);             \
                                                                                                                       \
    static_assert(std::same_as<Reverse##item##_t<holder_t<B, A, B>>              , holder_t<B, A, B>>);                \
    static_assert(std::same_as<Reverse##item##_t<holder_t<A, B, B, A>>           , holder_t<A, B, B, A>>);             \
    static_assert(std::same_as<Reverse##item##_t<holder_t<D, C, B, C, D>>        , holder_t<D, C, B, C, D>>);          \
    static_assert(std::same_as<Reverse##item##_t<holder_t<A, B, C, C, B, A>>     , holder_t<A, B, C, C, B, A>>);       \
    static_assert(std::same_as<Reverse##item##_t<holder_t<E, D, C, B, C, D, E>>  , holder_t<E, D, C, B, C, D, E>>);    \
                                                                                                                       \
    static_assert(std::same_as<Reverse##item##_t<holder_t<D, A, C, B>>           , holder_t<B, C, A, D>>);             \
    static_assert(std::same_as<Reverse##item##_t<holder_t<F, E, D, C, B, A>>     , holder_t<A, B, C, D, E, F>>);       \
    static_assert(std::same_as<Reverse##item##_t<holder_t<A, C, E, B, D, F>>     , holder_t<F, D, B, E, C, A>>);       \
    static_assert(std::same_as<Reverse##item##_t<holder_t<C, A, F, C, E, B, D>>  , holder_t<D, B, E, C, F, A, C>>);


    FATLIB_MODIFICATION_TRAITS_STATIC_ASSERT_TESTS_GENERATOR2(    , _type_holder_, int, char, double, float, bool, void)
    FATLIB_MODIFICATION_TRAITS_STATIC_ASSERT_TESTS_GENERATOR2(Item, _item_holder_,   1,    2,      3,     4,    5,    6)


#define FATLIB_MODIFICATION_TRAITS_STATIC_ASSERT_TESTS_GENERATOR3(A, B, C, D, E, F, G)                                                                            \
                                                                                                                                                                  \
    static_assert(    MinItem_v<_item_holder_<A>>                          == A);                                                                                 \
    static_assert(    MinItem_v<_item_holder_<C, B, D, A>>                 == A);                                                                                 \
    static_assert(    MinItem_v<_item_holder_<D, C, B>>                    == B);                                                                                 \
    static_assert(    MinItem_v<_item_holder_<C, D, C, E>>                 == C);                                                                                 \
    static_assert(    MinItem_v<_item_holder_<E, D, B, F, B, G>>           == B);                                                                                 \
    static_assert(    MinItem_v<_item_holder_<F, F, F>>                    == F);                                                                                 \
                                                                                                                                                                  \
    static_assert(    MaxItem_v<_item_holder_<A>>                          == A);                                                                                 \
    static_assert(    MaxItem_v<_item_holder_<C, B, D, A>>                 == D);                                                                                 \
    static_assert(    MaxItem_v<_item_holder_<A, B, C>>                    == C);                                                                                 \
    static_assert(    MaxItem_v<_item_holder_<C, A, C, B>>                 == C);                                                                                 \
    static_assert(    MaxItem_v<_item_holder_<E, D, G, F, B, G>>           == G);                                                                                 \
    static_assert(    MaxItem_v<_item_holder_<A, A, A, A>>                 == A);                                                                                 \
                                                                                                                                                                  \
    static_assert(CountIfItem_v<_item_holder_<A, B, D, E, C, F>, decltype([](const auto& item) consteval noexcept -> bool { return item > C;        })> == 3);    \
    static_assert(CountIfItem_v<_item_holder_<A, B, C>,          decltype([](const auto& item) consteval noexcept -> bool { return item > C;        })> == 0);    \
    static_assert(CountIfItem_v<_item_holder_<D, E, F, G>,       decltype([](const auto& item) consteval noexcept -> bool { return item > C;        })> == 4);    \
    static_assert(CountIfItem_v<_item_holder_<>,                 decltype([](const auto& item) consteval noexcept -> bool { return item > C;        })> == 0);    \
                                                                                                                                                                  \
    static_assert(CountIfItem_v<_item_holder_<A, B, C, B, D, B>, decltype([](const auto& item) consteval noexcept -> bool { return item == B;       })> == 3);    \
    static_assert(CountIfItem_v<_item_holder_<A, C, D, E>,       decltype([](const auto& item) consteval noexcept -> bool { return item == B;       })> == 0);    \
    static_assert(CountIfItem_v<_item_holder_<B>,                decltype([](const auto& item) consteval noexcept -> bool { return item == B;       })> == 1);    \
    static_assert(CountIfItem_v<_item_holder_<B, B, B, B>,       decltype([](const auto& item) consteval noexcept -> bool { return item == B;       })> == 4);    \
                                                                                                                                                                  \
    static_assert(CountIfItem_v<_item_holder_<A, B, C, D, E, F>, decltype([](const auto& item) consteval noexcept -> bool { return (item % 2) == 0; })> == 3);    \
    static_assert(CountIfItem_v<_item_holder_<A, C, E, G>,       decltype([](const auto& item) consteval noexcept -> bool { return (item % 2) == 0; })> == 0);    \
    static_assert(CountIfItem_v<_item_holder_<B, D, F>,          decltype([](const auto& item) consteval noexcept -> bool { return (item % 2) == 0; })> == 3);    \
    static_assert(CountIfItem_v<_item_holder_<A, B, A, D, A, F>, decltype([](const auto& item) consteval noexcept -> bool { return (item % 2) == 0; })> == 3);

    FATLIB_MODIFICATION_TRAITS_STATIC_ASSERT_TESTS_GENERATOR3(1, 2, 3, 4, 5, 6, 7)
    FATLIB_MODIFICATION_TRAITS_STATIC_ASSERT_TESTS_GENERATOR3((-7), (-6), (-5), (-4), (-3), (-2), (-1))
}

#endif
