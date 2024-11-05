#include<stdio.h>
#include<stdlib.h>
#include<math.h>
struct tree_node{
    int data;
    int bf;
    struct tree_node *left;
    struct tree_node *right;
    struct tree_node *parent;
};

//get the input data and create a new node
struct tree_node *create(int data){
    struct tree_node *node = (struct tree_node*)malloc(sizeof(struct tree_node));
    node->data=data;
    node->bf=0;
    node->left=NULL;
    node->right=NULL;
    node->parent=NULL;
    return node;
}

//calculate the height of the node
int height(struct tree_node *node){
    if(node==NULL){
        return 0 ;
    }
    return 1+ fmax(height(node->left),height(node->right));
}

//calculate the balance factor of the node
void update(struct tree_node *node){
    node->bf=height(node->left)-height(node->right);
}

//rotate
struct tree_node* left_rotation(struct tree_node *node){
    if(node->parent==NULL){
        struct tree_node* new_root=node->right;
        if (new_root->left != NULL) new_root->left->parent = node;
        node->right=new_root->left;
        new_root->left=node;
        node->parent=new_root;
        update(node); 
        update(new_root);
        return new_root;
    }
    else{
    struct tree_node* parent=node->parent;
    struct tree_node* new_root=node->right;
    if (new_root->left != NULL) new_root->left->parent = node;
    node->right=new_root->left;
    if(node->data < parent->data)parent->left=new_root;
    else parent->right=new_root;
    new_root->parent=parent;
    new_root->left=node;
    node->parent=new_root;
    update(node); 
    update(new_root);
    return new_root;
    }
}
struct tree_node* right_rotation(struct tree_node *node){
    if(node->parent==NULL){
        struct tree_node* new_root=node->left;
        if (new_root->right != NULL) new_root->right->parent = node;
        node->left=new_root->right;
        new_root->right=node;
        node->parent=new_root;
        update(node); 
        update(new_root);
        return new_root;
    }
    else{
            struct tree_node* parent=node->parent;
            struct tree_node* new_root=node->left;
            if (new_root->right != NULL) new_root->right->parent = node;
            node->left=new_root->right;
            if(node->data < parent->data)parent->left=new_root;
            else parent->right=new_root;
            new_root->parent=parent;
            new_root->right=node;
            node->parent=new_root;
            update(node);
            update(new_root);
            return new_root;
    }
}

struct tree_node* balance(struct tree_node* node){
    update(node);
    if(node->bf>1){
        if(node->left->bf<0){
            node->left=left_rotation(node->left);
            node->left->parent=node;
        }
        node=right_rotation(node);
    }
    if(node->bf<-1){
        if(node->right->bf>0){
            node->right=right_rotation(node->right);
            node->right->parent=node;
        }
        node=left_rotation(node);
    }
    return node;
}

struct tree_node* insert(struct tree_node* node, int data){
    if(node==NULL){
        return create(data);
    }
    if(data>node->data){
        node->right=insert(node->right,data);
        node->right->parent=node;
    }
    else{
        node->left=insert(node->left,data);
        node->left->parent=node;
    }
    return balance(node);
}
int data;
int main(void){
    int n;
    scanf("%d",&n);
    struct tree_node *root =NULL;
    for(int i=0;i<n;i++){
        scanf("%d",&data);
        root=insert(root,data);
    }
    printf("%d",root->data);
    return 0;
}
