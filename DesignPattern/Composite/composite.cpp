/**
 * @file composite.cpp
 * @author Sean 
 * @brief 
 * @version 0.1
 * @date 2021-09-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <list>

class Component {
protected:
    Component *parent_;

public:
    virtual ~Component(){}
    void SetParent(Component *parent) {
        this->parent_ = parent;
    }
    Component* getParent() const {
        return parent_;
    }

    virtual void add(Component *component) {}
    virtual void remove(Component *component) {}
    virtual bool isComposite() const {return false;}
    virtual std::string Operation() const = 0;
};

class Leaf : public Component {
public:
    std::string Operation() const override {
        return "leaf";
    }
};

class Composite : public Component {
protected:
    std::list<Component*> children_;
public:
    void add(Component* component) override {
        children_.remove(component);
        component->SetParent(nullptr);
    }
    bool isComposite() const override {return true;}
    std::string Operation() const override {
        std::string result;
        for (const Component* c : children_) {
            if (c == children_.back()) {
                result += c->Operation();
            } else {
                result += c->Operation() + "+";
            }
        }
        return "Branch(" + result + ")";
    }
};

void ClientCode(Component *component) {
    std::cout << "RESULT: " << component->Operation();
}

void ClientCode2(Component *component1, Component *component2) {
    if (component1->isComposite()) {
        component1->add(component2);
    }
    std::cout << "RESULT: " << component1->Operation();
}

int main() {
    Component *simple = new Leaf;
    std::cout << "Client: I've got a simple component:\n";
    ClientCode(simple);
    std::cout << "\n\n";

    Component *tree = new Composite;
    Component *branch1 = new Composite;

    Component *leaf_1 = new Leaf;
    Component *leaf_2 = new Leaf;
    Component *leaf_3 = new Leaf;
    branch1->add(leaf_1);
    branch1->add(leaf_2);
    Component *branch2 = new Composite;
    branch2->add(leaf_3);
    tree->add(branch1);
    tree->add(branch2);
    std::cout << "Client: Now I've got a composite tree:\n";
    ClientCode(tree);
    std::cout << "\n\n";

    std::cout << "Client: I don't need to check the components classes even when managing the tree:\n";
    ClientCode2(tree, simple);
    std::cout << "\n";

    delete simple;
    delete tree;
    delete branch1;
    delete branch2;
    delete leaf_1;
    delete leaf_2;
    delete leaf_3;

    return 0;
}