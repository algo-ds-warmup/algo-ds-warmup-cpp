#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <fmt/ranges.h>

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

ListNode* swapPairs(ListNode* head)
{
    if (!head)
        return nullptr;
    auto curr{head->next};
    auto prev{head};
    ListNode* prevprev{nullptr};
    while (curr)
    {
        prev->next = curr->next;
        curr->next = prev;

        [[unlikely]]
        if (curr->next == head)
            head = curr;

        [[likely]]
        if (prevprev)
            prevprev->next = curr;

        prevprev = curr->next;
        if (!prevprev)
            break;

        prev = prevprev->next;
        if (!prev)
            break;
        curr = prev->next;
    }

    return head;
}

TEST_CASE("Example 1")
{
    ListNodeContainer in{1, 2, 3, 4};
    REQUIRE_EQ(*swapPairs(&in.m_list_nodes[0]), ListNodeContainer{2, 1, 4, 3}.m_list_nodes[0]);
}
