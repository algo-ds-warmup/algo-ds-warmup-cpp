#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/std.h>

#include <cassert>

#include <ranges>

struct ListNode
{
    int val;
    ListNode* next = nullptr;
    ListNode(int v) : val(v) {}
};

template <>
struct fmt::formatter<ListNode> : formatter<std::string>
{
    auto format(const ListNode& node, fmt::format_context& ctx) const
    {
        std::string res{"["};
        res += std::to_string(node.val);

        auto* nodePtr = node.next;
        while (nodePtr)
        {
            res += ", " + std::to_string(nodePtr->val);
            nodePtr = nodePtr->next;
        }
        res += "]";
        return fmt::formatter<std::string>::format(res, ctx);
    }
};

namespace doctest
{
template <>
struct StringMaker<ListNode>
{
    static String convert(const ListNode& in) { return fmt::format("{}", in).c_str(); }
};
} // namespace doctest

struct ListNodeContainer
{
    template <typename... L>
    ListNodeContainer(L... list) : m_list_nodes{list...}
    {
        for (size_t i{0}; i < sizeof...(list) - 1; ++i)
        {
            m_list_nodes[i].next = &m_list_nodes[i + 1];
        }
    }
    std::vector<ListNode> m_list_nodes;
};

// deep equality
bool operator==(const ListNode& left, const ListNode& right)
{
    auto leftPtr = &left;
    auto rightPtr = &right;

    while (leftPtr && rightPtr)
    {
        if (leftPtr->val != rightPtr->val)
            return false;
        leftPtr = leftPtr->next;
        rightPtr = rightPtr->next;
    }
    if (leftPtr || rightPtr)
        return false;
    return true;
}

ListNode* addTwoNumbers(ListNode* left, ListNode* right)
{
    std::vector<int> result;
    int rem{0};
    while (left || right)
    {
        int firstTerm{0};
        int secondTerm{0};
        if (left)
            firstTerm = left->val;
        if (right)
            secondTerm = right->val;

        int slotValue{rem};
        slotValue += firstTerm + secondTerm;
        result.push_back(slotValue % 10);
        rem = slotValue / 10;

        if (left)
            left = left->next;
        if (right)
            right = right->next;
    }

    if (rem)
    {

        while (rem > 9)
        {
            result.push_back(0);
            rem -= 10;
        }
        result.push_back(rem);
    }

    ListNode* head{nullptr};
    ListNode* cur{nullptr};

    for (auto v : result)
    {
        auto node = new ListNode{v};
        if (!head)
            head = node;
        else
            cur->next = node;
        cur = node;
    }
    return head;
}

TEST_CASE("Example 2")
{
    ListNodeContainer left{2, 4, 3};
    ListNodeContainer right{5, 6, 4};
    REQUIRE(*addTwoNumbers(&left.m_list_nodes[0], &right.m_list_nodes[0]) ==
            ListNodeContainer{7, 0, 8}.m_list_nodes[0]);
}
TEST_CASE("Example 2")
{
    ListNodeContainer left{0};
    ListNodeContainer right{0};
    REQUIRE(*addTwoNumbers(&left.m_list_nodes[0], &right.m_list_nodes[0]) == ListNodeContainer{0}.m_list_nodes[0]);
}

TEST_CASE("Example 3")
{
    ListNodeContainer left{1, 9};
    ListNodeContainer right{9, 9, 9};
    REQUIRE(*addTwoNumbers(&left.m_list_nodes[0], &right.m_list_nodes[0]) ==
            ListNodeContainer{0, 9, 0, 1}.m_list_nodes[0]);
}

TEST_CASE("Example 4")
{
    ListNodeContainer left{1, 1, 1};
    ListNodeContainer right{1};
    REQUIRE(*addTwoNumbers(&left.m_list_nodes[0], &right.m_list_nodes[0]) ==
            ListNodeContainer{2, 1, 1}.m_list_nodes[0]);
}

TEST_CASE("Example 5")
{
    ListNodeContainer left{1};
    ListNodeContainer right{1, 1, 1};
    REQUIRE(*addTwoNumbers(&left.m_list_nodes[0], &right.m_list_nodes[0]) ==
            ListNodeContainer{2, 1, 1}.m_list_nodes[0]);
}

TEST_CASE("Example 6")
{
    ListNodeContainer left{9, 9, 9};
    ListNodeContainer right{1};
    REQUIRE(*addTwoNumbers(&left.m_list_nodes[0], &right.m_list_nodes[0]) ==
            ListNodeContainer{0, 0, 0, 1}.m_list_nodes[0]);
}
