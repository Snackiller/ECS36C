#include <algorithm>
#include <memory>
#include <string>
#include <vector>
#include <queue>
#include "json.hpp"

class Node
{
public:
    int data;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    std::shared_ptr<Node> parent;
    int height_;
    int balancefactor_;

public:
    Node() : data(0) {}
    explicit Node(int d) : data(d) {}
};

class Avl
{
private:
    size_t current_size;
    void add_helper(std::shared_ptr<Node> parent, std::shared_ptr<Node> node);
    std::shared_ptr<Node> left_rotate(std::shared_ptr<Node> node);
    std::shared_ptr<Node> right_rotate(std::shared_ptr<Node> node);
    std::shared_ptr<Node> left_right_rotate(std::shared_ptr<Node> node);
    std::shared_ptr<Node> right_left_rotate(std::shared_ptr<Node> node);
    void check_balance(std::shared_ptr<Node> node);
    std::shared_ptr<Node> rebalance(std::shared_ptr<Node> node);

public:
    std::shared_ptr<Node> root;
    int height(std::shared_ptr<Node> node);
    Avl() : current_size(0) {}
    void add(std::shared_ptr<Node> node);
    void add(int data);
    void updateHeightAndBF(std::shared_ptr<Node> &node);
    nlohmann::json JSON() const;
    inline size_t size() const
    {
        return current_size;
    }
    inline bool empty() const
    {
        return !(static_cast<bool>(current_size));
    }
};