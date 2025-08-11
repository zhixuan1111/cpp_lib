#include <iostream>
#include <string>

template<typename T>
struct Node
{
    T value;
    Node *next;

    Node(T a):value(a),next(nullptr){}  
};

template<typename T>
class list
{
private:
    Node<T>* head; //链表头指针
    int length = 0;
public:
    list(/* args */)
    {
        head = nullptr;
    }
    ~list()
    {
        std::cout<<"descontruct !"<<std::endl;
        clear();
    }
    int getListLength() const
    {
        return this->length;
    }
    
    bool isEmpty()
    {
        return head==nullptr;
    }

    void print()
    {
        if(this->length == 0)
        {
            std::cout<<"list is empty! "<<std::endl;
        }
        Node<T>* current = head;
        for (size_t i = 0; i < this->length; i++)
        {
            if (current != nullptr)
            {
                std::cout<<current->value<<" ";
            }
            current = current->next;
        } 
        std::cout<<std::endl;
    }
    
    void clear()
    {
        Node<T>* current = this->head;
        for (size_t i = 0; i < this->length; i++)
        {
            if (current != nullptr)
            {
                Node<T>* delete_ptr = current;
                current = current->next;
                delete delete_ptr;
            }
        } 
        this->head = nullptr; // 要记得把头指针置为nullptr
        this->length = 0;
    }

    void addHeadNode(T value) //头部添加节点
    {
        if (this->isEmpty())   // 如果链表为空
        {
            Node<T>* new_node = new Node<T>(value);
            this->head = new_node;
            this->length++;
        }
        else
        {
            Node<T>* new_node = new Node<T>(value);
            Node<T>* temp_node = this->head;
            this->head = new_node;
            this->head->next = temp_node;
            this->length++;
    
        }
    }

    void addTailNode(T value)//尾部添加节点
    {
        if (this->isEmpty())   // 如果链表为空
        {
            Node<T>* new_node = new Node<T>(value);
            this->head = new_node;
            this->length++;
        }
        else
        {
            Node<T>* new_node = new Node<T>(value);
            Node<T>* current_node = this->head;
            while (current_node->next != nullptr)
            {
                current_node = current_node->next;
            }
            current_node->next = new_node;
            this->length++;
        }
    }
    
    bool addAtPosition(T value,size_t pos)//指定位置添加结点
    {
        if(pos<1 || pos>this->length+1)
        {
            return false;
        }
        else if(pos == 1)
        {
            Node<T>* new_node = new Node<T>(value);
            new_node->next = this->head;
            this->head = new_node;
            this->length++;
            return true;
        }
        else
        {
            Node<T>* new_node = new Node<T>(value);
            Node<T>* left = this->head;
            Node<T>* right = nullptr;
            for(int i=1;i<pos-1;i++)
            {
                left = left->next;
            }
            right = left->next;
            left->next = new_node;
            new_node->next = right;
            this->length++;
            return true;
        }
        return false;
    }
    
    bool deleteHeadPosition()   //删除头部位置的结点
    {
        if (this->isEmpty())
        {
            return false;
        }
        Node<T>* temp_node = this->head;
        this->head = this->head->next;
        delete temp_node;
        this->length--;
        return true;
    }
    
    bool deleteTailPosition()   //删除尾部位置的结点
    {
        if (this->isEmpty())
        {
            return false;
        }
        else if(this->length == 1)
        {
            delete this->head;
            this->length--;
            return true;
        }
        // 删除尾部结点不能用循环方式走到最后的结点，应该用length
        else if (this->length>1)
        {
            Node<T>* temp = this->head;
            int n = 1;
            while (n < this->length-1)
            {
                temp = temp->next;
                n++;
            }
            delete temp->next;
            temp->next = nullptr;
            this->length--;
            return true;
        }
        return false;
    }
    
    bool deleteAtPosition(size_t pos)//删除指定位置的结点
    {
        if(pos<1 || pos>this->length)
        {
            return false;
        }
        else if (pos == 1)
        {
            this->deleteHeadPosition(); //不用再执行length--了，函数中已经执行完毕了
            return true;
        }
        else if (pos == this->length)
        {
            this->deleteTailPosition(); //不用再执行length--了，函数中已经执行完毕了
            return true;
        }
        else
        {
            Node<T>* current = this->head;
            for (size_t i = 1; i < pos-1; i++) //  在这个地方 1 < pos <length
            {
                current = current->next;
            }
            Node<T>* temp = current->next;
            current->next = current->next->next;
            delete temp;
            this->length--;
            return true;
        }
    }

    bool search(T num)   // 搜索值
    {
        if(this->length == 0)
        {
            std::cout<<"list is empty! "<<std::endl;
            return false;
        }
        Node<T>* current = head;
        while (current != nullptr)
        {
            if (num == current->value)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    

};



int main()
{
    // list a;
    // a.addHeadNode(1);
    // a.addHeadNode(2);
    // a.addHeadNode(3);
    // a.addHeadNode(4);
    // a.addTailNode(5);
    // a.addHeadNode(6);
    // std::cout<<"length is "<<a.getListLength()<<std::endl;
    // a.print();
    // a.addAtPosition(111,8);
    // a.print();

    // list b;
    // b.addHeadNode(1);
    // b.addHeadNode(2);
    // b.addHeadNode(3);
    // b.print();
    // b.deleteHeadPosition();
    // b.print();

    // list c;
    // c.addHeadNode(1);
    // c.addHeadNode(2);
    // c.addHeadNode(3);
    // c.print();
    // c.deleteTailPosition();
    // c.print();

    // c.deleteTailPosition();
    // c.print();

    // c.deleteTailPosition();
    // c.print();

    list<std::string> d;
    d.addTailNode("1111");
    d.addTailNode("222");
    // d.addTailNode(3);
    // d.addTailNode(4);
    // d.addTailNode(5);
    d.print();
    d.deleteAtPosition(2);
    d.print();

    std::cout<<d.search("111")<<std::endl;
    std::cout<<d.search("333")<<std::endl;




    return 0;
}