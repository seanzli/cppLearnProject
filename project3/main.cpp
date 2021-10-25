#include <iostream>     //std::cout, std::endl
#include <iterator>     //ostream_iterator
#include <type_traits>  //std::conditional, std::enable_if

/**
 * @brief decleration for number struct
 */
template<int...valT> struct Cont{};

/**
 * @brief print function
 */
/// specify Cont<> input
void print(Cont<>) {
    std::cout << "\n";
}
/// print function
template<int...valT>
void print(Cont<valT...>) {
    constexpr static int val[] = {valT...};
    std::copy(std::begin(val), std::end(val), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
}

/**
 * @brief add function,
 */
/// carry flag
template<bool flag>
struct Flag{};

/**
 * @brief add function struct
 * 
 * @tparam Res      output  should be Cont<...>
 * @tparam First    input1  should be Cont<...>
 * @tparam Second   input2  should be Cont<...>
 * @tparam F        carry flag  should be Flag<true> or Flag<false>
 */
template<typename Res, typename First, typename Second, typename F>
struct add;

/// add function terminate condition 1, input enpty
template<int...rT, bool flag>
struct add<Cont<rT...>,Cont<>, Cont<>, Flag<flag>>
    : std::conditional< (flag == true),
                        std::enable_if<1, Cont<rT...,1>>,
                        std::enable_if<1, Cont<rT...>>
                      >::type 
    {};

/// add function terminate condition 2, input2 enpty
template<int...rT,int xT, int...fT, bool flag>
struct add<Cont<rT...>,Cont<xT,fT...>, Cont<>, Flag<flag>>
    : std::conditional< (flag + xT > 9),
                        add<Cont<rT..., 0>, Cont<fT...>, Cont<>, Flag<true>>,
                        std::enable_if<1, Cont<rT..., xT + flag, fT...>>
                      >::type 
    {};

/// add function terminate condition 3, input1 enpty
template<int...rT,int yT, int...sT, bool flag>
struct add<Cont<rT...>,Cont<>, Cont<yT, sT...>, Flag<flag>>
    : std::conditional< (flag + yT > 9),
                        add<Cont<rT..., 0>, Cont<>, Cont<sT...>, Flag<true>>,
                        std::enable_if<1, Cont<rT..., yT + flag, sT...>>
                      >::type 
    {};

/// add struct main function
template<int...rT,int xT, int...fT, int yT, int...sT, bool flag>
struct add<Cont<rT...>,Cont<xT, fT...>, Cont<yT, sT...>, Flag<flag>>
    : std::conditional< (flag + xT + yT > 9),
                        add<Cont<rT..., xT + yT + flag - 10>, Cont<fT...>, Cont<sT...>, Flag<true>>,
                        add<Cont<rT..., xT + yT + flag>, Cont<fT...>, Cont<sT...>, Flag<false>>
                      >::type 
    {};

// reverse
/**
 * @brief  reverse struct
 * 
 * @tparam Res  output  should be Cont<...>
 * @tparam In   input   should be Cont<...>
 */
template<typename Res, typename In> struct reverse;

/// terminate condition, input empty
template<int...rT>
struct reverse<Cont<rT...>, Cont<>>
    : std::enable_if<1, Cont<rT...>>
    {};

/// reverse struct main function
template<int...rT, int xT, int...fT>
struct reverse<Cont<rT...>, Cont<xT, fT...>>
    : reverse<Cont<xT, rT...>, Cont<fT...>>
    {};

//AddFunction
/**
 * @brief addFunction,  AddFunction::type should be result, format : Cont<...>
 * 
 * @tparam First        input1  should be Cont<...>
 * @tparam Second       input2  should be Cont<...>
 */
template<typename First, typename Second> struct AddFunction;
template<int ... fT, int ... sT>
struct AddFunction<Cont<fT...>, Cont<sT...>>
    : reverse<Cont<>, 
              typename  add<Cont<>, 
                            typename reverse<Cont<>, Cont<sT...>>::type,
                            typename reverse<Cont<>, Cont<fT...>>::type,
                            Flag<false>>::type
             >
    {};

int main() {
    std::cout << "==========\nPrintFunction test\n";
    print(Cont<>());
    print(Cont<1>());
    print(Cont<1,2,3,4,5,6>());

    std::cout << "==========\nAdd Function test\n";
    print(add<Cont<>, Cont<>, Cont<>, Flag<false>>::type());
    print(add<Cont<>, Cont<1>, Cont<>, Flag<false>>::type());
    print(add<Cont<>, Cont<>, Cont<1>, Flag<false>>::type());
    print(add<Cont<>, Cont<9>, Cont<1>, Flag<false>>::type());
    print(add<Cont<2>, Cont<9>, Cont<1>, Flag<false>>::type());
    print(add<Cont<>, Cont<1,2>, Cont<9,7>, Flag<false>>::type());

    std::cout << "==========\nReverse Function test\n";
    print(reverse<Cont<>, Cont<>>::type());
    print(reverse<Cont<1>, Cont<>>::type());
    print(reverse<Cont<>, Cont<1>>::type());
    print(reverse<Cont<3>, Cont<1,2>>::type());
    // print(reverse<Cont<1,2>, Cont<>>::type());
    
    std::cout << "==========\nAddRes Function test\n";
    print(AddFunction<Cont<>, Cont<>>::type());
    print(AddFunction<Cont<1>, Cont<>>::type());
    print(AddFunction<Cont<1>, Cont<1>>::type());
    print(AddFunction<Cont<1,9>, Cont<1>>::type());
    print(AddFunction<Cont<1,9,9>, Cont<1>>::type());
    print(AddFunction<Cont<1,1,1>, Cont<9,9,9>>::type());
}