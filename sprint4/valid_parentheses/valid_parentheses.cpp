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

private:
    size_t m_capacity{1};
    size_t m_size{0};
    T* m_data;
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
