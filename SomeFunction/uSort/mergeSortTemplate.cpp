#include <iostream>
#include <utility>
#include <iterator>
#include <algorithm>

template<int... valsT>
struct iseq{};

template<int... valsT>
void print(iseq<valsT...>) {
    static constexpr int vals[] = {valsT...};
    std::copy(std::begin(vals), std::end(vals),
              std::ostream_iterator<int>(std::cout, " "));
    std::endl(std::cout);
}

// divide
template<typename F, typename S>
struct divide;
template<int... fT, int xT, int ... sT>
struct divide<iseq<fT...>, iseq<xT, sT...>>
        : std::conditional<
                    sizeof...(fT) < 1 + sizeof...(sT),
                    divide<iseq<fT..., xT>, iseq<sT...>>,
                    std::pair<iseq<fT...>, iseq<xT, sT...>>
                >::type
{};
template<int... fT>
struct divide<iseq<fT...>, iseq<>>
        : std::pair<iseq<fT...>, iseq<>>
{};

// merge
template<typename R, typename F,typename S> struct merge;
template<int...rT>
struct merge<iseq<rT...>, iseq<>, iseq<>>
        : std::enable_if<1, iseq<rT...>>
{};

template<int... rT, int xT, int... fT>
struct merge<iseq<rT...>, iseq<xT, fT...>, iseq<>>
        : std::enable_if<1, iseq<rT..., xT, fT...>>
{};

template<int...rT, int yT, int... sT>
struct merge<iseq<rT...>, iseq<>, iseq<yT, sT...>>
        : std::enable_if<1, iseq<rT..., yT, sT...>>
{};

template<int...rT, int xT, int... fT, int yT, int ... sT>
struct merge<iseq<rT...>, iseq<xT, fT...>, iseq<yT, sT...>>
        : std::conditional<
                xT < yT,
                merge<iseq<rT..., xT>, iseq<fT...>, iseq<yT, sT...>>,
                merge<iseq<rT..., yT>, iseq<xT, fT...>, iseq<sT...>>
                >::type
{};

//sort
template<typename S>
struct sort;

template<>
struct sort<iseq<>>
        : std::enable_if<1, iseq<>>
{};

template<int xT>
struct sort<iseq<xT>>
        : std::enable_if<1, iseq<xT>>
{};

template<int xT, int yT>
struct sort<iseq<xT, yT>>
        : std::conditional<
            xT < yT,
            iseq<xT, yT>,
            iseq<yT, xT>
        >
{};

template<int...sT>
struct sort<iseq<sT...>>
        : merge<iseq<>,
                typename sort<typename divide<iseq<>, iseq<sT...>>::first_type>::type,
                typename sort<typename divide<iseq<>, iseq<sT...>>::second_type>::type
                >
{};


int main() {
    print(sort<iseq<1,6,8,3,9,7,2,5,4>>::type());
}

