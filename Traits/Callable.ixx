module;

#include <FatDefines.hpp>

export module FatPound.Traits.Callable;

import std;

export namespace fatpound::traits
{
    template <typename T>
    struct FAT_EBCO FunctionInfo;
    
    template <typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(Args...)>
    {
        using Return_t      = R;
        using Callable_t    = R(Args...);
        using CallablePtr_t = R(*)(Args...);
        using TupleOfArgs_t = std::tuple<Args...>;

        template <std::size_t N>
        using Nth_Argument_t = std::tuple_element<N, TupleOfArgs_t>::type;

        static constexpr auto arity = sizeof...(Args);
    };

    template <typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(*)(Args...)> : virtual FunctionInfo<R(Args...)>
    {
        
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...)> : virtual FunctionInfo<R(*)(Args...)>
    {
        using Class_t = std::conditional_t<std::is_class_v<C>, C, void>;
        using Union_t = std::conditional_t<std::is_union_v<C>, C, void>;

        using CallablePtr_t                   = R(C::*)(Args...);
        using CallablePtr_t_no_cvrn           = R(C::*)(Args...); // removing all cvr-n but pointer cv qualifiers
        using CallablePtr_t_no_cvrn_no_ptr_cv = R(C::*)(Args...); // removing all cvr-n

        static constexpr bool is_const_qualified{};
        static constexpr bool is_volatile_qualified{};
        static constexpr bool is_lvalue_reference_qualified{};
        static constexpr bool is_rvalue_reference_qualified{};
        static constexpr bool is_not_reference_qualified{ true };
        static constexpr bool is_noexcept_specified{};
    };

    /////////////////////////////////////////////////////////////////////////////
    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) const> : virtual FunctionInfo<R(C::*)(Args...)>
    {
        using CallablePtr_t = R(C::*)(Args...) const;

        static constexpr bool is_const_qualified = true;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) volatile> : virtual FunctionInfo<R(C::*)(Args...)>
    {
        using CallablePtr_t = R(C::*)(Args...) volatile;

        static constexpr bool is_volatile_qualified = true;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) &> : virtual FunctionInfo<R(C::*)(Args...)>
    {
        using CallablePtr_t = R(C::*)(Args...) &;

        static constexpr bool is_lvalue_reference_qualified = true;
        static constexpr bool is_not_reference_qualified    = false;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) &&> : virtual FunctionInfo<R(C::*)(Args...)>
    {
        using CallablePtr_t = R(C::*)(Args...) &&;

        static constexpr bool is_rvalue_reference_qualified = true;
        static constexpr bool is_not_reference_qualified    = false;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) noexcept> : virtual FunctionInfo<R(C::*)(Args...)>
    {
        using CallablePtr_t = R(C::*)(Args...) noexcept;

        static constexpr bool is_noexcept_specified = true;
    };
    /////////////////////////////////////////////////////////////////////////////

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) const volatile>
        :
        virtual FunctionInfo<R(C::*)(Args...) const>,
        virtual FunctionInfo<R(C::*)(Args...) volatile>
    {
        using CallablePtr_t = R(C::*)(Args...) const volatile;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) const &>
        :
        virtual FunctionInfo<R(C::*)(Args...) const>,
        virtual FunctionInfo<R(C::*)(Args...) &>
    {
        using CallablePtr_t = R(C::*)(Args...) const &;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) const &&>
        :
        virtual FunctionInfo<R(C::*)(Args...) const>,
        virtual FunctionInfo<R(C::*)(Args...) &&>
    {
        using CallablePtr_t = R(C::*)(Args...) const &&;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) volatile &>
        :
        virtual FunctionInfo<R(C::*)(Args...) volatile>,
        virtual FunctionInfo<R(C::*)(Args...) &>
    {
        using CallablePtr_t = R(C::*)(Args...) volatile &;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) volatile &&>
        :
        virtual FunctionInfo<R(C::*)(Args...) volatile>,
        virtual FunctionInfo<R(C::*)(Args...) &&>
    {
        using CallablePtr_t = R(C::*)(Args...) volatile &&;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) const volatile &>
        :
        virtual FunctionInfo<R(C::*)(Args...) const>,
        virtual FunctionInfo<R(C::*)(Args...) volatile>,
        virtual FunctionInfo<R(C::*)(Args...) &>
    {
        using CallablePtr_t = R(C::*)(Args...) const volatile &;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) const volatile &&>
        :
        virtual FunctionInfo<R(C::*)(Args...) const>,
        virtual FunctionInfo<R(C::*)(Args...) volatile>,
        virtual FunctionInfo<R(C::*)(Args...) &&>
    {
        using CallablePtr_t = R(C::*)(Args...) const volatile &&;
    };
    
    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) const noexcept>
        :
        virtual FunctionInfo<R(C::*)(Args...) const>,
        virtual FunctionInfo<R(C::*)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::*)(Args...) const noexcept;
    };
    
    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) volatile noexcept>
        :
        virtual FunctionInfo<R(C::*)(Args...) volatile>,
        virtual FunctionInfo<R(C::*)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::*)(Args...) volatile noexcept;
    };
    
    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) const volatile noexcept>
        :
        virtual FunctionInfo<R(C::*)(Args...) const>,
        virtual FunctionInfo<R(C::*)(Args...) volatile>,
        virtual FunctionInfo<R(C::*)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::*)(Args...) const volatile noexcept;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) const & noexcept>
        :
        virtual FunctionInfo<R(C::*)(Args...) const>,
        virtual FunctionInfo<R(C::*)(Args...) &>,
        virtual FunctionInfo<R(C::*)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::*)(Args...) const & noexcept;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) const && noexcept>
        :
        virtual FunctionInfo<R(C::*)(Args...) const>,
        virtual FunctionInfo<R(C::*)(Args...) &&>,
        virtual FunctionInfo<R(C::*)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::*)(Args...) const && noexcept;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) volatile & noexcept>
        :
        virtual FunctionInfo<R(C::*)(Args...) volatile>,
        virtual FunctionInfo<R(C::*)(Args...) &>,
        virtual FunctionInfo<R(C::*)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::*)(Args...) volatile & noexcept;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) volatile && noexcept>
        :
        virtual FunctionInfo<R(C::*)(Args...) volatile>,
        virtual FunctionInfo<R(C::*)(Args...) &&>,
        virtual FunctionInfo<R(C::*)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::*)(Args...) volatile && noexcept;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) const volatile & noexcept>
        :
        virtual FunctionInfo<R(C::*)(Args...) const>,
        virtual FunctionInfo<R(C::*)(Args...) volatile>,
        virtual FunctionInfo<R(C::*)(Args...) &>,
        virtual FunctionInfo<R(C::*)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::*)(Args...) const volatile & noexcept;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) const volatile && noexcept>
        :
        virtual FunctionInfo<R(C::*)(Args...) const>,
        virtual FunctionInfo<R(C::*)(Args...) volatile>,
        virtual FunctionInfo<R(C::*)(Args...) &&>,
        virtual FunctionInfo<R(C::*)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::*)(Args...) const volatile && noexcept;
    };

    /// with cvr-qualified member function pointers

    /////////////////////////////////////////////////////////////////////////////
    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const)(Args...) const> : virtual FunctionInfo<R(C::*)(Args...) const>
    {
        using CallablePtr_t         = R(C::* const)(Args...) const;
        using CallablePtr_t_no_cvrn = R(C::* const)(Args...);
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const)(Args...) volatile> : virtual FunctionInfo<R(C::*)(Args...) volatile>
    {
        using CallablePtr_t         = R(C::* const)(Args...) volatile;
        using CallablePtr_t_no_cvrn = R(C::* const)(Args...);
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const)(Args...) &> : virtual FunctionInfo<R(C::*)(Args...) &>
    {
        using CallablePtr_t         = R(C::* const)(Args...) &;
        using CallablePtr_t_no_cvrn = R(C::* const)(Args...);
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const)(Args...) &&> : virtual FunctionInfo<R(C::*)(Args...) &&>
    {
        using CallablePtr_t         = R(C::* const)(Args...) &&;
        using CallablePtr_t_no_cvrn = R(C::* const)(Args...);
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const)(Args...) noexcept> : virtual FunctionInfo<R(C::*)(Args...) noexcept>
    {
        using CallablePtr_t         = R(C::* const)(Args...) noexcept;
        using CallablePtr_t_no_cvrn = R(C::* const)(Args...);
    };
    /////////////////////////////////////////////////////////////////////////////

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const)(Args...) const volatile>
        :
        virtual FunctionInfo<R(C::* const)(Args...) const>,
        virtual FunctionInfo<R(C::* const)(Args...) volatile>
    {
        using CallablePtr_t = R(C::* const)(Args...) const volatile;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const)(Args...) const &>
        :
        virtual FunctionInfo<R(C::* const)(Args...) const>,
        virtual FunctionInfo<R(C::* const)(Args...) &>
    {
        using CallablePtr_t = R(C::* const)(Args...) const &;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const)(Args...) const &&>
        :
        virtual FunctionInfo<R(C::* const)(Args...) const>,
        virtual FunctionInfo<R(C::* const)(Args...) &&>
    {
        using CallablePtr_t = R(C::* const)(Args...) const &&;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const)(Args...) volatile &>
        :
        virtual FunctionInfo<R(C::* const)(Args...) volatile>,
        virtual FunctionInfo<R(C::* const)(Args...) &>
    {
        using CallablePtr_t = R(C::* const)(Args...) volatile &;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const)(Args...) volatile &&>
        :
        virtual FunctionInfo<R(C::* const)(Args...) volatile>,
        virtual FunctionInfo<R(C::* const)(Args...) &&>
    {
        using CallablePtr_t = R(C::* const)(Args...) volatile &&;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const)(Args...) const volatile &>
        :
        virtual FunctionInfo<R(C::* const)(Args...) const>,
        virtual FunctionInfo<R(C::* const)(Args...) volatile>,
        virtual FunctionInfo<R(C::* const)(Args...) &>
    {
        using CallablePtr_t = R(C::* const)(Args...) const volatile &;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const)(Args...) const volatile &&>
        :
        virtual FunctionInfo<R(C::* const)(Args...) const>,
        virtual FunctionInfo<R(C::* const)(Args...) volatile>,
        virtual FunctionInfo<R(C::* const)(Args...) &&>
    {
        using CallablePtr_t = R(C::* const)(Args...) const volatile &&;
    };
    
    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const)(Args...) const noexcept>
        :
        virtual FunctionInfo<R(C::* const)(Args...) const>,
        virtual FunctionInfo<R(C::* const)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::* const)(Args...) const noexcept;
    };
    
    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const)(Args...) volatile noexcept>
        :
        virtual FunctionInfo<R(C::* const)(Args...) volatile>,
        virtual FunctionInfo<R(C::* const)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::* const)(Args...) volatile noexcept;
    };
    
    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const)(Args...) const volatile noexcept>
        :
        virtual FunctionInfo<R(C::* const)(Args...) const>,
        virtual FunctionInfo<R(C::* const)(Args...) volatile>,
        virtual FunctionInfo<R(C::* const)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::* const)(Args...) const volatile noexcept;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const)(Args...) const & noexcept>
        :
        virtual FunctionInfo<R(C::* const)(Args...) const>,
        virtual FunctionInfo<R(C::* const)(Args...) &>,
        virtual FunctionInfo<R(C::* const)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::* const)(Args...) const & noexcept;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const)(Args...) const && noexcept>
        :
        virtual FunctionInfo<R(C::* const)(Args...) const>,
        virtual FunctionInfo<R(C::* const)(Args...) &&>,
        virtual FunctionInfo<R(C::* const)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::* const)(Args...) const && noexcept;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const)(Args...) volatile & noexcept>
        :
        virtual FunctionInfo<R(C::* const)(Args...) volatile>,
        virtual FunctionInfo<R(C::* const)(Args...) &>,
        virtual FunctionInfo<R(C::* const)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::* const)(Args...) volatile & noexcept;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const)(Args...) volatile && noexcept>
        :
        virtual FunctionInfo<R(C::* const)(Args...) volatile>,
        virtual FunctionInfo<R(C::* const)(Args...) &&>,
        virtual FunctionInfo<R(C::* const)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::* const)(Args...) volatile && noexcept;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const)(Args...) const volatile & noexcept>
        :
        virtual FunctionInfo<R(C::* const)(Args...) const>,
        virtual FunctionInfo<R(C::* const)(Args...) volatile>,
        virtual FunctionInfo<R(C::* const)(Args...) &>,
        virtual FunctionInfo<R(C::* const)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::* const)(Args...) const volatile & noexcept;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const)(Args...) const volatile && noexcept>
        :
        virtual FunctionInfo<R(C::* const)(Args...) const>,
        virtual FunctionInfo<R(C::* const)(Args...) volatile>,
        virtual FunctionInfo<R(C::* const)(Args...) &&>,
        virtual FunctionInfo<R(C::* const)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::* const)(Args...) const volatile && noexcept;
    };

    /////////////////////////////////////////////////////////////////////////////
    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* volatile)(Args...) const> : virtual FunctionInfo<R(C::*)(Args...) const>
    {
        using CallablePtr_t         = R(C::* volatile)(Args...) const;
        using CallablePtr_t_no_cvrn = R(C::* volatile)(Args...);
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* volatile)(Args...) volatile> : virtual FunctionInfo<R(C::*)(Args...) volatile>
    {
        using CallablePtr_t         = R(C::* volatile)(Args...) volatile;
        using CallablePtr_t_no_cvrn = R(C::* volatile)(Args...);
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* volatile)(Args...) &> : virtual FunctionInfo<R(C::*)(Args...) &>
    {
        using CallablePtr_t         = R(C::* volatile)(Args...) &;
        using CallablePtr_t_no_cvrn = R(C::* volatile)(Args...);
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* volatile)(Args...) &&> : virtual FunctionInfo<R(C::*)(Args...) &&>
    {
        using CallablePtr_t         = R(C::* volatile)(Args...) &&;
        using CallablePtr_t_no_cvrn = R(C::* volatile)(Args...);
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* volatile)(Args...) noexcept> : virtual FunctionInfo<R(C::*)(Args...) noexcept>
    {
        using CallablePtr_t         = R(C::* volatile)(Args...) noexcept;
        using CallablePtr_t_no_cvrn = R(C::* volatile)(Args...);
    };
    /////////////////////////////////////////////////////////////////////////////

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* volatile)(Args...) const volatile>
        :
        virtual FunctionInfo<R(C::* volatile)(Args...) const>,
        virtual FunctionInfo<R(C::* volatile)(Args...) volatile>
    {
        using CallablePtr_t = R(C::* volatile)(Args...) const volatile;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* volatile)(Args...) const &>
        :
        virtual FunctionInfo<R(C::* volatile)(Args...) const>,
        virtual FunctionInfo<R(C::* volatile)(Args...) &>
    {
        using CallablePtr_t = R(C::* volatile)(Args...) const &;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* volatile)(Args...) const &&>
        :
        virtual FunctionInfo<R(C::* volatile)(Args...) const>,
        virtual FunctionInfo<R(C::* volatile)(Args...) &&>
    {
        using CallablePtr_t = R(C::* volatile)(Args...) const &&;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* volatile)(Args...) volatile &>
        :
        virtual FunctionInfo<R(C::* volatile)(Args...) volatile>,
        virtual FunctionInfo<R(C::* volatile)(Args...) &>
    {
        using CallablePtr_t = R(C::* volatile)(Args...) volatile &;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* volatile)(Args...) volatile &&>
        :
        virtual FunctionInfo<R(C::* volatile)(Args...) volatile>,
        virtual FunctionInfo<R(C::* volatile)(Args...) &&>
    {
        using CallablePtr_t = R(C::* volatile)(Args...) volatile &&;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* volatile)(Args...) const volatile &>
        :
        virtual FunctionInfo<R(C::* volatile)(Args...) const>,
        virtual FunctionInfo<R(C::* volatile)(Args...) volatile>,
        virtual FunctionInfo<R(C::* volatile)(Args...) &>
    {
        using CallablePtr_t = R(C::* volatile)(Args...) const volatile &;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* volatile)(Args...) const volatile &&>
        :
        virtual FunctionInfo<R(C::* volatile)(Args...) const>,
        virtual FunctionInfo<R(C::* volatile)(Args...) volatile>,
        virtual FunctionInfo<R(C::* volatile)(Args...) &&>
    {
        using CallablePtr_t = R(C::* volatile)(Args...) const volatile &&;
    };
    
    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* volatile)(Args...) const noexcept>
        :
        virtual FunctionInfo<R(C::* volatile)(Args...) const>,
        virtual FunctionInfo<R(C::* volatile)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::* volatile)(Args...) const noexcept;
    };
    
    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* volatile)(Args...) volatile noexcept>
        :
        virtual FunctionInfo<R(C::* volatile)(Args...) volatile>,
        virtual FunctionInfo<R(C::* volatile)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::* volatile)(Args...) volatile noexcept;
    };
    
    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* volatile)(Args...) const volatile noexcept>
        :
        virtual FunctionInfo<R(C::* volatile)(Args...) const>,
        virtual FunctionInfo<R(C::* volatile)(Args...) volatile>,
        virtual FunctionInfo<R(C::* volatile)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::* volatile)(Args...) const volatile noexcept;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* volatile)(Args...) const & noexcept>
        :
        virtual FunctionInfo<R(C::* volatile)(Args...) const>,
        virtual FunctionInfo<R(C::* volatile)(Args...) &>,
        virtual FunctionInfo<R(C::* volatile)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::* volatile)(Args...) const & noexcept;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* volatile)(Args...) const && noexcept>
        :
        virtual FunctionInfo<R(C::* volatile)(Args...) const>,
        virtual FunctionInfo<R(C::* volatile)(Args...) &&>,
        virtual FunctionInfo<R(C::* volatile)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::* volatile)(Args...) const && noexcept;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* volatile)(Args...) volatile & noexcept>
        :
        virtual FunctionInfo<R(C::* volatile)(Args...) volatile>,
        virtual FunctionInfo<R(C::* volatile)(Args...) &>,
        virtual FunctionInfo<R(C::* volatile)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::* volatile)(Args...) volatile & noexcept;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* volatile)(Args...) volatile && noexcept>
        :
        virtual FunctionInfo<R(C::* volatile)(Args...) volatile>,
        virtual FunctionInfo<R(C::* volatile)(Args...) &&>,
        virtual FunctionInfo<R(C::* volatile)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::* volatile)(Args...) volatile && noexcept;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* volatile)(Args...) const volatile & noexcept>
        :
        virtual FunctionInfo<R(C::* volatile)(Args...) const>,
        virtual FunctionInfo<R(C::* volatile)(Args...) volatile>,
        virtual FunctionInfo<R(C::* volatile)(Args...) &>,
        virtual FunctionInfo<R(C::* volatile)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::* volatile)(Args...) const volatile & noexcept;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* volatile)(Args...) const volatile && noexcept>
        :
        virtual FunctionInfo<R(C::* volatile)(Args...) const>,
        virtual FunctionInfo<R(C::* volatile)(Args...) volatile>,
        virtual FunctionInfo<R(C::* volatile)(Args...) &&>,
        virtual FunctionInfo<R(C::* volatile)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::* volatile)(Args...) const volatile && noexcept;
    };

    /////////////////////////////////////////////////////////////////////////////
    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const volatile)(Args...) const> : virtual FunctionInfo<R(C::*)(Args...) const>
    {
        using CallablePtr_t         = R(C::* const volatile)(Args...) const;
        using CallablePtr_t_no_cvrn = R(C::* const volatile)(Args...);
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const volatile)(Args...) volatile> : virtual FunctionInfo<R(C::*)(Args...) volatile>
    {
        using CallablePtr_t         = R(C::* const volatile)(Args...) volatile;
        using CallablePtr_t_no_cvrn = R(C::* const volatile)(Args...);
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const volatile)(Args...) &> : virtual FunctionInfo<R(C::*)(Args...) &>
    {
        using CallablePtr_t         = R(C::* const volatile)(Args...) &;
        using CallablePtr_t_no_cvrn = R(C::* const volatile)(Args...);
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const volatile)(Args...) &&> : virtual FunctionInfo<R(C::*)(Args...) &&>
    {
        using CallablePtr_t         = R(C::* const volatile)(Args...) &&;
        using CallablePtr_t_no_cvrn = R(C::* const volatile)(Args...);
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const volatile)(Args...) noexcept> : virtual FunctionInfo<R(C::*)(Args...) noexcept>
    {
        using CallablePtr_t         = R(C::* const volatile)(Args...) noexcept;
        using CallablePtr_t_no_cvrn = R(C::* const volatile)(Args...);
    };
    /////////////////////////////////////////////////////////////////////////////

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const volatile)(Args...) const volatile>
        :
        virtual FunctionInfo<R(C::* const volatile)(Args...) const>,
        virtual FunctionInfo<R(C::* const volatile)(Args...) volatile>
    {
        using CallablePtr_t = R(C::* const volatile)(Args...) const volatile;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const volatile)(Args...) const &>
        :
        virtual FunctionInfo<R(C::* const volatile)(Args...) const>,
        virtual FunctionInfo<R(C::* const volatile)(Args...) &>
    {
        using CallablePtr_t = R(C::* const volatile)(Args...) const &;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const volatile)(Args...) const &&>
        :
        virtual FunctionInfo<R(C::* const volatile)(Args...) const>,
        virtual FunctionInfo<R(C::* const volatile)(Args...) &&>
    {
        using CallablePtr_t = R(C::* const volatile)(Args...) const &&;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const volatile)(Args...) volatile &>
        :
        virtual FunctionInfo<R(C::* const volatile)(Args...) volatile>,
        virtual FunctionInfo<R(C::* const volatile)(Args...) &>
    {
        using CallablePtr_t = R(C::* const volatile)(Args...) volatile &;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const volatile)(Args...) volatile &&>
        :
        virtual FunctionInfo<R(C::* const volatile)(Args...) volatile>,
        virtual FunctionInfo<R(C::* const volatile)(Args...) &&>
    {
        using CallablePtr_t = R(C::* const volatile)(Args...) volatile &&;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const volatile)(Args...) const volatile &>
        :
        virtual FunctionInfo<R(C::* const volatile)(Args...) const>,
        virtual FunctionInfo<R(C::* const volatile)(Args...) volatile>,
        virtual FunctionInfo<R(C::* const volatile)(Args...) &>
    {
        using CallablePtr_t = R(C::* const volatile)(Args...) const volatile &;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const volatile)(Args...) const volatile &&>
        :
        virtual FunctionInfo<R(C::* const volatile)(Args...) const>,
        virtual FunctionInfo<R(C::* const volatile)(Args...) volatile>,
        virtual FunctionInfo<R(C::* const volatile)(Args...) &&>
    {
        using CallablePtr_t = R(C::* const volatile)(Args...) const volatile &&;
    };
    
    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const volatile)(Args...) const noexcept>
        :
        virtual FunctionInfo<R(C::* const volatile)(Args...) const>,
        virtual FunctionInfo<R(C::* const volatile)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::* const volatile)(Args...) const noexcept;
    };
    
    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const volatile)(Args...) volatile noexcept>
        :
        virtual FunctionInfo<R(C::* const volatile)(Args...) volatile>,
        virtual FunctionInfo<R(C::* const volatile)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::* const volatile)(Args...) volatile noexcept;
    };
    
    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const volatile)(Args...) const volatile noexcept>
        :
        virtual FunctionInfo<R(C::* const volatile)(Args...) const>,
        virtual FunctionInfo<R(C::* const volatile)(Args...) volatile>,
        virtual FunctionInfo<R(C::* const volatile)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::* const volatile)(Args...) const volatile noexcept;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const volatile)(Args...) const & noexcept>
        :
        virtual FunctionInfo<R(C::* const volatile)(Args...) const>,
        virtual FunctionInfo<R(C::* const volatile)(Args...) &>,
        virtual FunctionInfo<R(C::* const volatile)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::* const volatile)(Args...) const & noexcept;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const volatile)(Args...) const && noexcept>
        :
        virtual FunctionInfo<R(C::* const volatile)(Args...) const>,
        virtual FunctionInfo<R(C::* const volatile)(Args...) &&>,
        virtual FunctionInfo<R(C::* const volatile)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::* const volatile)(Args...) const && noexcept;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const volatile)(Args...) volatile & noexcept>
        :
        virtual FunctionInfo<R(C::* const volatile)(Args...) volatile>,
        virtual FunctionInfo<R(C::* const volatile)(Args...) &>,
        virtual FunctionInfo<R(C::* const volatile)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::* const volatile)(Args...) volatile & noexcept;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const volatile)(Args...) volatile && noexcept>
        :
        virtual FunctionInfo<R(C::* const volatile)(Args...) volatile>,
        virtual FunctionInfo<R(C::* const volatile)(Args...) &&>,
        virtual FunctionInfo<R(C::* const volatile)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::* const volatile)(Args...) volatile && noexcept;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const volatile)(Args...) const volatile & noexcept>
        :
        virtual FunctionInfo<R(C::* const volatile)(Args...) const>,
        virtual FunctionInfo<R(C::* const volatile)(Args...) volatile>,
        virtual FunctionInfo<R(C::* const volatile)(Args...) &>,
        virtual FunctionInfo<R(C::* const volatile)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::* const volatile)(Args...) const volatile & noexcept;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const volatile)(Args...) const volatile && noexcept>
        :
        virtual FunctionInfo<R(C::* const volatile)(Args...) const>,
        virtual FunctionInfo<R(C::* const volatile)(Args...) volatile>,
        virtual FunctionInfo<R(C::* const volatile)(Args...) &&>,
        virtual FunctionInfo<R(C::* const volatile)(Args...) noexcept>
    {
        using CallablePtr_t = R(C::* const volatile)(Args...) const volatile && noexcept;
    };

    template <typename T>
    concept Callable = std::invocable<T>;

    template <typename T>
    struct FAT_EBCO HasFunctor
    {
        static constexpr bool value = Callable<T>;
    };

    template <typename T>
    constexpr bool HasFunctor_v = HasFunctor<T>::value;
}

module : private;
