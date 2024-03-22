#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <fmt/ranges.h>

// LIFO
template <typename T>
struct stack
{
    size_t capacity() const { return m_capacity; }
    size_t size() const { return m_size; }
    bool empty() const { return size() == 0; }

    void push(const T& element)
    {
        if (size() >= capacity() - 1)
        {
            m_capacity <<= 1;
            m_data = static_cast<T*>(std::realloc(m_data, m_capacity));
        }
        m_data[m_size++] = element;
    }

    const T& top() const { return m_data[m_size - 1]; }

    T pop()
    {
        --m_size;
        return m_data[m_size];
    }

    stack() = default;
    stack(const stack<T>& o)
    {
        if (m_data != o.m_data)
        {
            m_capacity = o.capacity();
            m_size = o.m_size();
            m_data = std::malloc(m_capacity * sizeof(T));
            std::memcpy(m_data, o.m_data, m_size);
        }
    }

    ~stack()
    {
        if (m_data)
        {
            std::free(m_data);
        }
    }

private:
    size_t m_capacity{1};
    size_t m_size{0};
    T* m_data = nullptr;
};

TEST_CASE("stack test")
{
    stack<int> st{};

    SUBCASE("capacity of empty = 1") { CHECK(st.capacity() == 1); }
    SUBCASE("size of empty = 0") { CHECK(st.size() == 0); }
    SUBCASE("insertion")
    {
        st.push(1);
        REQUIRE(st.size() == 1);
        REQUIRE_FALSE(st.empty());
        REQUIRE(st.top() == 1);

        SUBCASE("removal")
        {
            REQUIRE(st.pop() == 1);
            REQUIRE(st.empty());
        }

        SUBCASE("consecutive removal")
        {
            st.push(2);
            REQUIRE(st.capacity() == 4);
            REQUIRE_FALSE(st.empty());
            REQUIRE(st.size() == 2);
            REQUIRE(st.top() == 2);

            REQUIRE(st.pop() == 2);
            REQUIRE(st.pop() == 1);
            REQUIRE(st.empty());
        }
        SUBCASE("capacity escalation")
        {
            REQUIRE(st.capacity() == 2);
            st.push(2);
            REQUIRE(st.capacity() == 4);
            st.push(3);
            REQUIRE(st.capacity() == 4);
            st.push(4);
            REQUIRE(st.capacity() == 8);
        }
    }
}

constexpr std::string_view CLOSE_PARENTHESES{"]})"};
constexpr std::string_view OPEN_PARENTHESES{"[{("};

bool is_valid(std::string str)
{
    stack<char> st;
    for (const char c : str)
    {
        if (std::ranges::count(OPEN_PARENTHESES, c))
        {
            st.push(c);
        }
        else if (auto posIndCl = std::ranges::find(CLOSE_PARENTHESES, c); posIndCl != std::end(CLOSE_PARENTHESES))
        {
            if (st.empty())
                return false;

            if (auto posIndOp = std::ranges::find(OPEN_PARENTHESES, st.top());
                std::distance(OPEN_PARENTHESES.begin(), posIndOp) == std::distance(CLOSE_PARENTHESES.begin(), posIndCl))
            {
                st.pop();
            }
            else // close parentheses, but isn't expected one
              return false; 
        }
    }
    return st.empty();
}

TEST_CASE("Example 1") { REQUIRE(is_valid("()")); }
TEST_CASE("Example 2") { REQUIRE(is_valid("()[]{}")); }
TEST_CASE("Example 3") { REQUIRE_FALSE(is_valid("(}")); }
TEST_CASE("Example 4") { REQUIRE_FALSE(is_valid("}")); }
TEST_CASE("Example 5") { REQUIRE_FALSE(is_valid("(")); }
TEST_CASE("Example 6") { REQUIRE(is_valid("")); }

TEST_CASE("TC 1") { REQUIRE_FALSE(is_valid("(])")); }
