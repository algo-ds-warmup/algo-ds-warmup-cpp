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
            m_data = static_cast<T*>(std::realloc(m_data, m_capacity * sizeof(T)));
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

struct MinStack : public ::stack<int>
{
    int getMin() const { return m_min.top(); }

    void push(int el)
    {
        stack<int>::push(el);
        if (m_min.empty() || el <= m_min.top())
            m_min.push(el);
    }
    int pop()
    {
        auto el = stack<int>::top();
        if (!m_min.empty() && m_min.top() == el)
        {
            m_min.pop();
        }
        return stack<int>::pop();
    }

private:
    stack<int> m_min;
};

TEST_CASE("Example 1")
{
    MinStack mst;
    mst.push(-2);
    REQUIRE(mst.getMin() == -2);
    mst.push(0);
    mst.push(-3);
    REQUIRE(mst.getMin() == -3);
    mst.pop();
    REQUIRE(mst.getMin() == -2);
};

TEST_CASE("TC 1")
{
  MinStack mst;
  mst.push(0);
  mst.push(1);
  mst.push(0);
  REQUIRE(mst.getMin() == 0);
  mst.pop();
  REQUIRE(mst.getMin() == 0);
  mst.pop();
  REQUIRE(mst.getMin() == 0);
}

TEST_CASE("TC 2")
{
  MinStack mst;
  mst.push(2);
  mst.push(0);
  mst.push(3);
  mst.push(0);

  REQUIRE(mst.getMin() == 0);
  mst.pop(); // 0
  REQUIRE(mst.getMin() == 0);
  mst.pop(); // 3
  REQUIRE(mst.getMin() == 0);
  mst.pop(); // 0
  REQUIRE(mst.getMin() == 2);
}
