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
    template <typename... Ts>
    struct _type_holder_ final {};

    template <auto... Values>
    struct _item_holder_ final {};


    // Type tests
    using _uT1_         = _type_holder_<int, float>;
    using _uT1Expected_ = _type_holder_<int, float, double>;
    static_assert(std::same_as<Append_t<_uT1_, double>, _uT1Expected_>);

    using _uT2_         = _type_holder_<int, float>;
    using _uT2Expected_ = _type_holder_<int, float>;
    static_assert(std::same_as<AppendUnique_t<_uT2_, int>, _uT2Expected_>);

    using _uT3_         = _type_holder_<int, float>;
    using _uT3Expected_ = _type_holder_<double, int, float>;
    static_assert(std::same_as<Prepend_t<_uT3_, double>, _uT3Expected_>);

    using _uT4_         = _type_holder_<int, float>;
    using _uT4Expected_ = _type_holder_<int, float>;
    static_assert(std::same_as<PrependUnique_t<_uT4_, int>, _uT4Expected_>);

    using _uT5_         = _type_holder_<int, float, double>;
    using _uT5Expected_ = _type_holder_<double, float, int>;
    static_assert(std::same_as<Reverse_t<_uT5_>, _uT5Expected_>);


    // Item tests
    using _uI1_         = _item_holder_<2, 3>;
    using _uI1Expected_ = _item_holder_<2, 3, 1>;
    static_assert(std::same_as<AppendItem_t<_uI1_, 1>, _uI1Expected_>);

    using _uI2_         = _item_holder_<1, 2, 3>;
    using _uI2Expected_ = _item_holder_<1, 2, 3>;
    static_assert(std::same_as<AppendItemUnique_t<_uI2_, 1>, _uI2Expected_>);
        
    using _uI3_         = _item_holder_<2, 3>;
    using _uI3Expected_ = _item_holder_<1, 2, 3>;
    static_assert(std::same_as<PrependItem_t<_uI3_, 1>, _uI3Expected_>);

    using _uI4_         = _item_holder_<1, 2, 3>;
    using _uI4Expected_ = _item_holder_<1, 2, 3>;
    static_assert(std::same_as<PrependItemUnique_t<_uI4_, 1>, _uI4Expected_>);

    using _uI5_         = _item_holder_<1, 2, 3>;
    using _uI5Expected_ = _item_holder_<3, 2, 1>;
    static_assert(std::same_as<ReverseItem_t<_uI5_>, _uI5Expected_>);
    

    static_assert(    MinItem_v<_item_holder_<4, 2, 9>> == 2);
    static_assert(    MaxItem_v<_item_holder_<4, 2, 9>> == 9);
    static_assert(CountIfItem_v<_item_holder_<1, 2, 3, 4, 5, 6, 7>, decltype([](const auto& item) consteval noexcept -> bool { return item > 4; })> == 3);
}

#endif
