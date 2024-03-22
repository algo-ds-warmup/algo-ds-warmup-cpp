#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <queue>

struct constrainted_q : private std::queue<int>
{
    void push(const int& el)
    {
        std::queue<int>::push(el);
        return;
    }
    int peek() const { return std::queue<int>::front(); }
    void pop() { return std::queue<int>::pop(); }
    size_t size() const { return std::queue<int>::size(); }
    bool empty() const { return std::queue<int>::empty(); }
};

// LIFO
struct MyStack
{
    bool empty() const { return m_fifo_q.empty(); }

    int pop()
    {
        constrainted_q tmp{};
        while (m_fifo_q.size() != 1)
        {
            tmp.push(m_fifo_q.peek());
            m_fifo_q.pop();
        }
        int ret = m_fifo_q.peek();
        m_fifo_q.pop();
        while (!tmp.empty())
        {
            m_fifo_q.push(tmp.peek());
            tmp.pop();
        }
        return ret;
    }
    int top()
    {
        constrainted_q tmp{m_fifo_q};
        while (tmp.size() != 1)
            tmp.pop();
        return tmp.peek();
    }
    void push(int e) { m_fifo_q.push(e); }

private:
    constrainted_q m_fifo_q;
};

TEST_CASE("Example 1")
{
    MyStack mst;
    mst.push(1);
    REQUIRE(mst.top() == 1);
    mst.push(2);
    REQUIRE(mst.top() == 2);

    REQUIRE(mst.pop() == 2);
    REQUIRE_FALSE(mst.empty());
    REQUIRE(mst.pop() == 1);
    REQUIRE(mst.empty());
}
