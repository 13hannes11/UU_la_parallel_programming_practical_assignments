#include <gtest/gtest.h>

#include <lib/Node.h>

TEST(NodeTest, DummyNode_smaller_int) {
    Node * n = Node::Dummy();
    ASSERT_FALSE(n->is_smaller_than(std::numeric_limits<int>::max()));
    ASSERT_FALSE(n->is_smaller_than(std::numeric_limits<int>::min()));
}

TEST(NodeTest, DummyNode_smaller_node) {
    Node * n = Node::Dummy();
    Node * max = new Node(std::numeric_limits<int>::max());
    Node * min = new Node(std::numeric_limits<int>::min());
    ASSERT_FALSE(n->is_smaller_than(max));
    ASSERT_FALSE(n->is_smaller_than(min));
}


TEST(NodeTest, LockingUnlockingNode) {
    Node * n = new Node(1);
    n->lock();
    n->unlock();
}

TEST(NodeTest, ChainingNode) {
    Node* first = Node::Dummy();
    Node* last = Node::Dummy();
    first->next = last;
    ASSERT_TRUE(first->next == last);
}

