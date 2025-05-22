#ifndef LINKLIST_H
#define LINKLIST_H

struct Node {
    int data;
    struct Node *next;
};

void push(Node **head_ref, int new_data) {
    Node *new_node = new Node();  //带括号的话，new_node 中的两个能被初始化
    new_node->data = new_data;
    new_node->next = *head_ref;
    *head_ref = new_node;
}

void append(Node** head_ref, int new_data){
    Node* new_node = new Node();
    Node* last = *head_ref;
    new_node->data = new_data;
    new_node->next = nullptr;
    if (*head_ref == nullptr){
        *head_ref = new_node;
        return;
    }
    while (last->next!= nullptr){
        last= last->next;
    }
    last->next = new_node;
}




#endif //LINKLIST_H