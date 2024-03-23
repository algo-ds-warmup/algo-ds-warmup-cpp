#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/std.h>

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

ListNode* mergeTwoLists(ListNode* left, ListNode* right)
{
    if (!left)
        return right;
    if (!right)
        return left;

    ListNode* current{nullptr};
    if (left->val <= right->val)
    {
        current = left;
        left = left->next;
    }
    else
    {
        current = right;
        right = right->next;
    }
    ListNode* res = current;

    while (left && right)
    {
        if (left->val <= right->val)
        {
            current->next = left;
            left = left->next;
        }
        else
        {
            current->next = right;
            right = right->next;
        }
        current = current->next;
    }
    if (!left)
        current->next = right;
    else if (!right)
        current->next = left;

    return res;
}

TEST_CASE("Example 1")
{
    ListNodeContainer left{1, 2, 4};
    ListNodeContainer right{1, 3, 4};

    REQUIRE(left.m_list_nodes[0] == ListNodeContainer{1, 2, 4}.m_list_nodes[0]);

    REQUIRE(*mergeTwoLists(&left.m_list_nodes[0], &right.m_list_nodes[0]) ==
            ListNodeContainer{1,1,2,3,4,4}.m_list_nodes[0]);
}
