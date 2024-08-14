#include<stdio.h>
#include<stdlib.h>

typedef struct tree {
    int value;
    struct tree *left;
    struct tree *right;
}tree ;
tree* create(int value);
tree* insert(tree *root, int value);
void print(tree *root);
tree* delete(tree *root, int value);
int main(){
tree *root=malloc(sizeof(tree));
for(int i=0;i<16;i++){
    insert(root,rand()%30);
}
print(root);
}

tree* create(int value){
    tree *newnode= (tree *)malloc(sizeof(tree));
    newnode->value=value;
    newnode->right= NULL;
    newnode->left= NULL;
    return newnode;
}
tree* insert(tree *root, int value){
    if(root==NULL){
      return create(value);
    }else{
        if(root->value>value){
            root->left=insert(root->left,value);
        }else{
            root->right=insert(root->right,value);
        }
        return root;
    }
}
void print(tree *root){
    if(root == NULL){
        return;
    }else{
        print(root->left);
        printf("%d ", root->value);
        print(root->right);
    }
}
tree* delete(tree *root, int value){
    if(root==NULL) return root;
    if(root->value>value){

        delete(root->left,value);
    }else if(root->value<value){
        delete(root->right,value);
    }else{
        if(root->left==NULL){
            tree *tmp = root->right;
            free(root);
            return tmp;
        }else if(root->right==NULL){
            tree *tmp = root->left;
            free(root);
            return tmp;
        }else{
            tree *tmp=root->right;
            while(tmp->left){
                tmp=tmp->left;
            }
            root->value=tmp->value;
           root->right= delete(root->right,tmp->value);
        }
    }
    return root;
}