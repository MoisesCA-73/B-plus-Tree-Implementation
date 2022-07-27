#include "BTree.h"

BTree::BTree(int _order)
{
    this->root = new Node();
    this->order = _order;
}

void BTree::insert_in_node(Node *& nodex, int data_to_insert)
{
    bool fin_flag = false;
    Node * node = nodex;

    Node * left = nullptr;
    Node * right = nullptr;
    
    while(!fin_flag)
    {
        
        bool flag = false;

        if (node == nullptr)
        {
            this->root = new Node();
            this->root->data_content.push_back(data_to_insert);
            this->root->sons.push_back(right);
            this->root->sons[0] = left;

            if (right) right->parent = this->root;
            if (left) left->parent = this->root;
            return;
        }

        for (int i = 0; i < node->data_content.size(); i++)
        {
            if (node->data_content[i] >= data_to_insert)
            {
                flag = true;
                node->data_content.insert(node->data_content.begin() + i, data_to_insert);
                node->sons.insert(node->sons.begin() + i, left);
                node->sons[i + 1] = right;
                if (left) left->parent = node; 
                if (right) right->parent = node;
                break;
            }
        }
        if (!flag)
        {
            node->data_content.push_back(data_to_insert);
            node->sons.push_back(right);
            node->sons[node->sons.size() - 2] = left;
            if (left) left->parent = node;
            if (right) right->parent = node;
        }
        if (node->data_content.size() > order)
        {
            int median = node->data_content[(order + 1) / 2];

            std::vector<Node *> aux_sons = node->sons;
            std::vector<int> aux_buffer = node->data_content;
            
            Node * brother = new Node();
            Node * nod = new Node();
            brother->data_content.clear();
            brother->sons.clear();
            nod->data_content.clear();
            nod->sons.clear();

            for (int i = 0; i < (order + 1) / 2; i++)
            {
                brother->data_content.push_back(aux_buffer[i]);
                brother->sons.push_back(aux_sons[i]);
                if (aux_sons[i]) brother->sons[i]->parent = brother;
            }
            brother->sons.push_back(aux_sons[(order + 1) / 2]);
            if ( brother->sons[(order + 1) / 2]) brother->sons[(order + 1) / 2]->parent = brother;
            
            if (aux_sons[0] == nullptr)
            {
                nod->data_content.push_back(median);
                nod->sons.push_back(aux_sons[(order + 1) / 2]);
            }
            for (int i = ((order + 1) / 2) + 1; i < aux_buffer.size(); i++)
            {
                nod->data_content.push_back(aux_buffer[i]);
                nod->sons.push_back(aux_sons[i]);
                if (aux_sons[i]) nod->sons[i - (((order + 1) / 2) + 1)]->parent = nod;
            }
            nod->sons.push_back(aux_sons[aux_buffer.size()]);
            if (aux_sons[aux_buffer.size()]) nod->sons[aux_buffer.size() - (((order + 1) / 2) + 1)]->parent = nod;
        
            left = brother;
            right = nod;

            node = node->parent;
            
            data_to_insert = median;
            continue;
        
        }
        else break;
    }




/*
    bool flag = false;
    for (int i = 0; i < node->data_content.size(); i++)
    {
        if (node->data_content[i] >= data_to_insert)
        {
            flag = true;
            node->data_content.insert(node->data_content.begin() + i, data_to_insert);
            node->sons.insert(node->sons.begin() + i, nullptr);
            break;
        }
    }
    if (!flag)
    {
        node->data_content.push_back(data_to_insert);
        node->sons.insert(node->sons.end() - 1, nullptr);
    }

    if (node->data_content.size() > order)
    {
        int median = node->data_content[(order + 1) / 2];
        if (!node->parent)
        {
            Node * new_root = new Node();
            this->root = new_root;
            this->root->data_content.push_back(median);
            this->root->sons[0] = nullptr;
            this->root->sons.push_back(node);
            node->parent = this->root;
        }
        else insert_in_node(node->parent, median);
        Node * brother = new Node();
        brother->parent = node->parent;
        // LOcating in parent node
        int pos = 0;
        for (int i = 0; i < node->parent->sons.size(); i++)
        {
            if (node->parent->sons[i] == node)
            {
                pos = i - 1;
                break;
            }
        }
        node->parent->sons[pos] = brother;
        
        std::vector<Node *> aux_sons = node->sons;
        std::vector<int> aux_buffer = node->data_content;
        
        node->sons.clear();
        node->data_content.clear();
        brother->sons.clear();
        brother->data_content.clear();

        for (int i = 0; i < (order + 1) / 2; i++)
        {
            brother->data_content.push_back(aux_buffer[i]);
            brother->sons.push_back(aux_sons[i]);
            if (aux_sons[i]) brother->sons[i]->parent = brother;
        }
        brother->sons.push_back(aux_sons[(order + 1) / 2]);
        if ( brother->sons[(order + 1) / 2]) brother->sons[(order + 1) / 2]->parent = brother;
        
        if (!aux_sons[1])
        {
            node->data_content.push_back(median);
            node->sons.push_back(aux_sons[(order + 1) / 2]);
        }
        for (int i = ((order + 1) / 2) + 1; i < aux_buffer.size(); i++)
        {
            node->data_content.push_back(aux_buffer[i]);
            node->sons.push_back(aux_sons[i]);
            if (aux_sons[i]) node->sons[i - (((order + 1) / 2) + 1)]->parent = node;
        }
        node->sons.push_back(aux_sons[aux_buffer.size()]);
        if (aux_sons[aux_buffer.size()]) node->sons[aux_buffer.size() - (((order + 1) / 2) + 1)]->parent = node;
        
        for (int i = 0; i < node->data_content.size(); i++)
        {
            if (!node->sons[i])
                std::cout << "nul ";
            else std::cout << node->sons[i] << ' '; 
            std::cout << node->data_content[i] << ' ';
        }
        if (!node->sons[node->sons.size() - 1])
            std::cout << "nul ";
        else std::cout << node->sons[node->sons.size() - 1] << ' ';
        std::cout << '\n';
        for (int i = 0; i < brother->data_content.size(); i++)
        {
            if (!brother->sons[i])
                std::cout << "nul ";
            else std::cout << brother->sons[i] << ' '; 
            std::cout << brother->data_content[i] << ' ';
        }
        if (!brother->sons[brother->sons.size() - 1])
            std::cout << "nul ";
        else std::cout << brother->sons[brother->sons.size() - 1] << ' ';
        std::cout << '\n';
        for (int i = 0; i < node->parent->data_content.size(); i++)
        {
            if (!node->parent->sons[i])
                std::cout << "nol ";
            else std::cout << node->parent->sons[i] << ' '; 
            std::cout << node->parent->data_content[i] << ' ';
        }
        if (!node->parent->sons[node->parent->sons.size() - 1])
            std::cout << "nol ";
        else std::cout << node->parent->sons[node->parent->sons.size() - 1] << ' ';
        std::cout << '\n'; 
        

    }*/


/*
    // If buffer is full
    if (node->data_content.size() == order)
    {
        std::vector<int> aux_buffer = node->data_content;
        std::vector<Node *> aux_sons = node->sons;
        
        // Filling buffer
        bool flag = false;
        for (int i = 0; i < aux_buffer.size(); i++)
        {
            if (aux_buffer[i] >= data_to_insert)
            {
                flag = true;
                aux_buffer.insert(aux_buffer.begin() + i, data_to_insert);
                aux_sons.insert(aux_sons.begin() + i, nullptr);
                break;
            }
        }
        if (!flag)
        {
            aux_buffer.push_back(data_to_insert);
            aux_sons.insert(aux_sons.end() - 1, nullptr);
        }

        int median = aux_buffer[(order + 1) / 2];

        //std::cout << "Median: " << median << '\n';
        if (!node->parent)
        {
            Node * new_root = new Node();
            this->root = new_root;
            this->root->data_content.push_back(median);
            this->root->sons[0] = nullptr;
            this->root->sons.push_back(node);
            node->parent = this->root;
        }
        else insert_in_node(node->parent, median);
        
        Node * brother = new Node();
        brother->parent = node->parent;
        // LOcating in parent node
        int pos = 1;
        for (int i = 0; i < node->parent->sons.size(); i++)
        {
            if (node->parent->sons[i] == node)
            {
                pos = i - 1;
                break;
            }
        }
        node->parent->sons[pos] = brother;

        node->data_content.clear();
        node->sons.clear();
        brother->sons.clear();

        for (int i = 0; i < (order + 1) / 2; i++)
        {
            brother->data_content.push_back(aux_buffer[i]);
            brother->sons.push_back(aux_sons[i]);
            if (aux_sons[i]) brother->sons[i]->parent = brother;
        }
        brother->sons.push_back(aux_sons[(order + 1) / 2]);
        if (aux_sons[(order + 1) / 2]) brother->sons[order + 1]->parent = brother;
        
        if (!brother->sons[0])
        {
            node->data_content.push_back(median);
            node->sons.push_back(nullptr);
        }
        for (int i = ((order + 1) / 2) + 1; i < aux_buffer.size(); i++)
        {
            node->data_content.push_back(aux_buffer[i]);
            node->sons.push_back(aux_sons[i]);
            if (aux_sons[i]) node->sons[i - (((order + 1) / 2) + 1)]->parent = node;
        }
        node->sons.push_back(aux_sons[aux_buffer.size()]);
        if (aux_sons[aux_buffer.size()]) node->sons[aux_buffer.size() - (((order + 1) / 2) + 1)]->parent = node;

        for (int i = 0; i < node->data_content.size(); i++)
        {
            if (!node->sons[i])
                std::cout << "nul ";
            else std::cout << node->sons[i] << ' '; 
            std::cout << node->data_content[i] << ' ';
        }
        if (!node->sons[node->sons.size() - 1])
            std::cout << "nul ";
        else std::cout << node->sons[node->sons.size() - 1] << ' ';
        std::cout << '\n';
        for (int i = 0; i < brother->data_content.size(); i++)
        {
            if (!brother->sons[i])
                std::cout << "nul ";
            else std::cout << brother->sons[i] << ' '; 
            std::cout << brother->data_content[i] << ' ';
        }
        if (!brother->sons[brother->sons.size() - 1])
            std::cout << "nul ";
        else std::cout << brother->sons[brother->sons.size() - 1] << ' ';
        std::cout << '\n';
        for (int i = 0; i < node->parent->data_content.size(); i++)
        {
            if (!node->parent->sons[i])
                std::cout << "nol ";
            else std::cout << node->parent->sons[i] << ' '; 
            std::cout << node->parent->data_content[i] << ' ';
        }
        if (!node->parent->sons[node->parent->sons.size() - 1])
            std::cout << "nol ";
        else std::cout << node->parent->sons[node->parent->sons.size() - 1] << ' ';
        std::cout << '\n'; 

    }
    else
    {
        bool flag = false;
        for (int i = 0; i < node->data_content.size(); i++)
        {
            if (node->data_content[i] >= data_to_insert)
            {
                flag = true;
                node->data_content.insert(node->data_content.begin() + i, data_to_insert);
                node->sons.insert(node->sons.begin() + i, nullptr);
                break;
            }
        }
        if (!flag) 
        {
            node->data_content.push_back(data_to_insert);
            node->sons.insert(node->sons.end() - 1, nullptr);
        }

        for (int i = 0; i < node->data_content.size(); i++)
        {
            if (!node->sons[i])
                std::cout << "nil ";
            else std::cout << node->sons[i] << ' '; 
            std::cout << node->data_content[i] << ' ';
        }
        if (!node->sons[node->sons.size() - 1])
            std::cout << "nil ";
        else std::cout << node->sons[node->sons.size() - 1] << ' '; 
        
        std::cout << '\n'; 
    }*/
}

void BTree::insert(int data_to_insert)
{
    Node * tmp = this->root;
    // locating leaf node
    while(tmp->sons[0])
    {
        bool flag = false;
        for (int i = 0; i < tmp->data_content.size(); i++)
        {
            if (tmp->data_content[i] >= data_to_insert)
            {
                flag = true;
                tmp = tmp->sons[i];
                break;
            }
        }
        if (!flag) tmp = tmp->sons[tmp->data_content.size()];
    }

    insert_in_node(tmp,data_to_insert);
    
}

void BTree::print_to_console()
{
    std::cout << "Printing:\n";
    Node * tmp = this->root;
        for (int i = 0; i < tmp->data_content.size(); i++)
        {
            print_to_console(tmp->sons[i]);
            std::cout << tmp->data_content[i] << ' ';
        }
    print_to_console(tmp->sons[tmp->data_content.size()]);

    std::cout << '\n'; 

}

void BTree::print_to_console(Node * tmp)
{
    if (tmp == nullptr) return;
    for (int i = 0; i < tmp->data_content.size(); i++)
    {
        print_to_console(tmp->sons[i]);
        std::cout << tmp->data_content[i] << ' ';
    }
    print_to_console(tmp->sons[tmp->data_content.size()]);

    std::cout << '\n'; 

}