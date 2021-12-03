#include <typeindex>


/**
 * @brief get largest type in Args...
 * 
 * @tparam T 
 * @tparam Args 
 */
template<typename T, typename... Args>
struct MaxType : std::integral_constant<int,
    (sizeof(T)>MaxType<Args...>::value ? sizeof(T) : MaxType<Args...>::value) > 
{};

template<typename T>
struct MaxType<T> : std::integral_constant<int, sizeof(T) >{};


/**
 * @brief check T is in type list
 * 
 * @tparam T 
 * @tparam List 
 */
template<typename T, typename... List>
struct Contains : std::true_type {};

template<typename T, typename Head, typename...Args>
struct Contains<T, Head, Args...>
    : std::conditional< std::is_same<T, Head>::value,
                        std::true_type,
                        Contains<T, Args...>
                      >::type
{};

template<typename T>
struct Contains<T> : std::false_type
{};


/**
 * @brief delete data in memory
 * 
 * @tparam Args 
 */
template<typename...Args>
struct VariantHelper;

template<typename T, typename...Args>
struct VariantHelper<T, Args...> {
    inline static void Destroy(std::type_index id, void* data) {
        if (id == std::type_index(typeid(T)))
            ((T*)(data))->~T();
        else
            VariantHelper<Args...>::Destroy(id, data);
    }
};

template<typename T>
struct VariantHelper<T> {
    inline static void Destroy(std::type_index id, void* data) {}
};



template<typename...Types>
class VariantT {
    using help_t = VariantHelper<Types...>;
public:
    VariantT() : m_type_id(typeid(void)) {}
    ~VariantT() {
        help_t::Destroy(m_type_id, m_data);
    }

    template<typename T>
    bool Is() {
        return std::type_index(typeid(T)) == m_type_id;
    }

    template<typename T>
    T& Get() {
        if (!Is<T>())
            throw std::bad_cast();
        return *(T*)(&m_data);
    }

    template <class T, 
        class = typename std::enable_if<
            Contains<typename std::remove_reference<T>::type, Types...>::value>::type>
    VariantT(T&& value) : m_type_id(std::type_index(typeid(void))) {
        help_t::Destroy(m_type_id, &m_data);
        typedef typename std::remove_reference<T>::type U;
        new(m_data) U(std::forward<T>(value));
        m_type_id =std::type_index(typeid(T));
    }


private:
    char m_data[MaxType<Types...>::value];
    std::type_index m_type_id;
};