#ifndef DLIST_IMPL_H
#define DLIST_IMPL_H

template<class T>
bool Dlist<T>::isEmpty() const {
    return this->first == nullptr;
}


template<class T>
void Dlist<T>::insertFront(T *op) {
    node *new_node = new node();
    new_node->op = op;
    if (this->isEmpty()) {
        new_node->prev = nullptr;
        new_node->next = nullptr;
        this->first = new_node;
        this->last = new_node;
    } else {
        new_node->prev = nullptr;
        new_node->next = this->first;
        this->first = new_node; //更新new_node
    }
}

template<class T>
void Dlist<T>::insertBack(T *op) {
    node *new_node = new node();
    new_node->op = op;
    if (this->isEmpty()) {
        new_node->prev = nullptr;
        new_node->next = nullptr;
        this->first = new_node;
        this->last = new_node;
    } else {
        new_node->next = nullptr;
        new_node->prev = this->last;
        this->last = new_node;
    }
}

template<class T>
T *Dlist<T>::removeFront() {
    if (this->isEmpty()) {
        throw emptyList();
    }
    //取出不需要new, 但要把要删掉的东西取出来，再delete
    node *old_node = this->first;
    auto old_op = old_node->op;

    //如果只有一个了,那就取空了
    if (old_node->next == nullptr) {
        this->first = nullptr;
        this->last = nullptr;
    } else {
        this->first = this->first->next;
        old_node->next->prev = nullptr;
    }
    delete old_node;
    return old_op;
}

template<class T>
T *Dlist<T>::removeBack() {
    if (this->isEmpty()) {
        throw emptyList();
    }
    //取出不需要new, 但要把要删掉的东西取出来，再delete
    node *old_node = this->last;
    auto old_op = old_node->op;

    //如果只有一个了,那就取空了
    if (old_node->next == nullptr) {
        this->first = nullptr;
        this->last = nullptr;
    } else {
        this->last = old_node->prev;
        old_node->prev->next = nullptr;
    }
    delete old_node;
    return old_op;
}

template<class T>
Dlist<T>::Dlist() {
    this->first = nullptr;
    this->last = nullptr;
}

template<class T>
Dlist<T>::Dlist(const Dlist &l) {
    this->first = nullptr;
    this->last = nullptr;
    this->copyAll(l);
}


template<class T>
Dlist<T> &Dlist<T>::operator=(const Dlist &l) {
    //注意自赋值检查
    if (this != &l) {
        this->removeAll();
        this->copyAll(l);
    }
    return *this;
}

template<class T>
Dlist<T>::~Dlist() {
    this->removeAll();
}


template<class T>
void Dlist<T>::removeAll() {
    if (!this->isEmpty()) {
        node *temp = this->first;
        while (temp->next != nullptr) {
            temp = temp->next;
            delete temp->prev->op;
            delete temp->prev;
        }
        delete temp->op;
        delete temp;
    }
    this->first = nullptr;
    this->last = nullptr;
}

template<class T>
void Dlist<T>::copyAll(const Dlist &l) {
    if (l.first!= nullptr){
        node* temp = l.last;
        while(temp->prev != nullptr){
            //不是很确定
            T* sourceData = temp->op;        // 获取源节点中的数据
            T* dataCopy = new T(*sourceData); // 创建数据的副本
            this->insertFront(dataCopy);      // 将副本插入到链表前端
            temp = temp->prev;
        }
        //只剩一个退出循环
        this->insertFront(temp->op);
    }
}

#endif // DLIST_IMPL_H
