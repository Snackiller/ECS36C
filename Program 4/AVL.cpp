#include "AVL.h"

//Returns the current height of the node
int Avl::height(std::shared_ptr<Node> node)
{
    if (!node)
    {
        return 0;
    }
    return std::max(height(node->left), height(node->right)) + 1;
}

//rotates node and leaves to the left
std::shared_ptr<Node> Avl::left_rotate(std::shared_ptr<Node> node)
{
    std::shared_ptr<Node> temp = node->right;
    node->right = temp->left;
    temp->left = node;
    if (node->right)
    {
        node->right->parent = node;
    }
    temp->parent = node->parent;
    if (node->parent)
    {
        if (node == node->parent->left)
        {
            node->parent->left = temp;
        }
        else if (node == node->parent->right)
        {
            node->parent->right = temp;
        }
    }
    node->parent = temp;
    updateHeightAndBF(node);
    return temp;
}
//rotates node and leaves to the right
std::shared_ptr<Node> Avl::right_rotate(std::shared_ptr<Node> node)
{
    std::shared_ptr<Node> temp = node->left;
    node->left = temp->right;
    temp->right = node;
    if (node->left)
    {
        node->left->parent = node;
    }
    temp->parent = node->parent;
    if (node->parent)
    {
        if (node == node->parent->left)
        {
            node->parent->left = temp;
        }
        else if (node == node->parent->right)
        {
            node->parent->right = temp;
        }
    }
    node->parent = temp;
    updateHeightAndBF(node);
    return temp;
}

//rotates the leaves to the left then calls right
std::shared_ptr<Node> Avl::left_right_rotate(std::shared_ptr<Node> node)
{
    node->left = left_rotate(node->left);

    return right_rotate(node);
}
//rotates the leaves to the right then calls left
std::shared_ptr<Node> Avl::right_left_rotate(std::shared_ptr<Node> node)
{
    node->right = right_rotate(node->right);

    return left_rotate(node);
}

//adds a node to the tree
void Avl::add_helper(std::shared_ptr<Node> parent, std::shared_ptr<Node> node)
{
    if (node->data > parent->data)
    {
        if (!parent->right)
        {
            parent->right = node;
            node->parent = parent;
            current_size++;
        }
        else
        {
            add_helper(parent->right, node);
        }
    }
    else if (node->data < parent->data)
    {
        if (!parent->left)
        {
            parent->left = node;
            node->parent = parent;
            current_size++;
        }
        else
        {
            add_helper(parent->left, node);
        }
    }
    else
    {
        return;
    }
    check_balance(node);
    updateHeightAndBF(node);
    return;
}
//inserts a node
void Avl::add(std::shared_ptr<Node> node)
{
    if (!root)
    {
        root = node;
        current_size++;
        return;
    }
    add_helper(root, node);
}
//inserts a key
void Avl::add(int data)
{
    if (!root)
    {
        root = std::make_shared<Node>(data);
        current_size++;
        return;
    }
    std::shared_ptr<Node> node = std::make_shared<Node>(data);
    add_helper(root, node);
}
//checks if the balance factor is within abs(1)
void Avl::check_balance(std::shared_ptr<Node> node)
{
    if (height(node->left) - height(node->right) > 1 || height(node->left) - height(node->right) < -1)
    {
        node = rebalance(node);
    }
    if (!node->parent)
    {
        return;
    }
    check_balance(node->parent);
}

//selects the correct balance function based on balance factor of current node
std::shared_ptr<Node> Avl::rebalance(std::shared_ptr<Node> node)
{
    if (height(node->left) - height(node->right) > 1)
    {
        if (height(node->left->left) >= height(node->left->right))
        {
            node = right_rotate(node);
        }
        else
        {
            node = left_right_rotate(node);
        }
    }
    if (height(node->left) - height(node->right) < -1)
    {
        if (height(node->right->right) >= height(node->right->left))
        {
            node = left_rotate(node);
        }
        else
        {
            node = right_left_rotate(node);
        }
    }
    if (!node->parent)
    {
        root = node;
    }
    return node;
}

//Updates the height and balance factor of the current node.
void Avl::updateHeightAndBF(std::shared_ptr<Node> &node)
{
    int nullheight = -1;
    if (node->left && node->right)
    {
        node->height_ = std::max(node->left->height_, node->right->height_) + 1;
        node->balancefactor_ = node->right->height_ - node->left->height_;
    }
    else if (node->left && node->right == nullptr)
    {
        node->height_ = node->left->height_ + 1;
        node->balancefactor_ = nullheight - node->left->height_;
    }
    else if (node->left == nullptr && node->right)
    {
        node->height_ = node->right->height_ + 1;
        node->balancefactor_ = node->right->height_ - nullheight;
    }
    else if (node->left == nullptr && node->right == nullptr)
    {
        node->height_ = 0;
        node->balancefactor_ = nullheight - nullheight;
    }
    auto parent = node->parent;
    if (parent != nullptr)
    {
        updateHeightAndBF(parent);
    }
}

//Exports a json object to print to CL
nlohmann::json Avl::JSON() const
{
    nlohmann::json result;
    std::queue<std::shared_ptr<Node>> nodes;
    if (root != nullptr)
    {
        result["root"] = root->data;
        nodes.push(root);
        while (!nodes.empty())
        {
            auto v = nodes.front();
            nodes.pop();
            std::string key = std::to_string(v->data);
            if (v->left != nullptr)
            {
                result[key]["left"] = v->left->data;
                result[key]["balance factor"] = v->left->balancefactor_;
                result[key]["height"] = v->left->height_;
                nodes.push(v->left);
            }
            if (v->right != nullptr)
            {
                result[key]["right"] = v->right->data;
                result[key]["balance factor"] = v->right->balancefactor_;
                result[key]["height"] = v->right->height_;
                nodes.push(v->right);
            }
            if (v->parent != nullptr)
            {
                result[key]["balance factor"] = v->parent->balancefactor_;
                result[key]["height"] = v->parent->height_;
                result[key]["parent"] = v->parent->data;
            }
            else
            {
                result[key]["root"] = true;
            }
        }
    }
    result["size"] = current_size;

    return result;
}