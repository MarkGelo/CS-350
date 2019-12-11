#include<stdio.h>
#include<stdlib.h>

struct Node {
    int value;
    struct Node* leftChild;
    struct Node* rightChild;
};

struct bTree {
    struct Node * root;
};

struct Node * new_node(int value){//like python bstree shit
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    node->value = value;
    node->leftChild = NULL;
    node->rightChild = NULL;
    return node;
}

//please implement all the four functions
struct bTree* newTree (int value) {
    struct bTree *p = malloc(sizeof(struct bTree));
    p->root = new_node(value);
    return p;
}

struct Node* add_helper(struct Node *node, int x){ //helper recursive method for adding
/* python 331
def add_rec(node):
            if not node:
                return BSTree.Node(val)
            elif val < node.val:
                return BSTree.Node(node.val, left=add_rec(node.left), right=node.right)
            else:
                return BSTree.Node(node.val, left=node.left, right=add_rec(node.right))
*/
    if(node==NULL){
        return new_node(x);
    }
    else if(x > node->value){
        node->rightChild = add_helper(node->rightChild, x);
    }
    else{
        node->leftChild = add_helper(node->leftChild, x);
    }
    return node;
}

int add (struct bTree* root, int value) {
    add_helper(root->root, value);//call helper recursive method to add
    return 1;
}

struct Node* find_minimum_helper(struct Node *root){//helper recursive method, finds minimum
    if(root == NULL){
        return NULL;
    }
    else if(root->leftChild != NULL){
        return find_minimum_helper(root->leftChild);
    }
    return root;
}

struct Node* removeNode_helper(struct Node *root, int x){
    /* python 331
    def delitem_rec(node):
              if val < node.val:
                  node.left = delitem_rec(node.left)
                  return node
              elif val > node.val:
                  node.right = delitem_rec(node.right)
                  return node
              else:
                  if not node.left and not node.right:
                      return None
                  elif node.left and not node.right:
                      return node.left
                  elif node.right and not node.left:
                      return node.right
                  else:
                      # remove the largest value from the left subtree as a replacement
                      # for the root value of this tree
                      t = node.left # refers to the candidate for removal
                      if not t.right:
                          node.val = t.val
                          node.left = t.left
                      else:
                          n = t
                          while n.right.right:
                              n = n.right
                          t = n.right
                          n.right = t.left
                          node.val = t.val
                      return node
    */
    if(root==NULL){
        return NULL;
    }
    if (x > root->value){
        root->rightChild = removeNode_helper(root->rightChild, x);
    }
    else if(x<root->value){
        root->leftChild = removeNode_helper(root->leftChild, x);
    }
    else{
//parent no child, nice
        if(root->leftChild==NULL && root->rightChild==NULL){
            free(root);
            return NULL;
        }

//for parent with 1 child
        else if(root->leftChild==NULL || root->rightChild==NULL){
            struct Node *temp;
            if(root->leftChild==NULL){
                temp = root->rightChild;
            }
            else{
                temp = root->leftChild;
            }
            free(root);
            return temp;
        }

//for parent with 2 childrens
        else{
            struct Node *temp = find_minimum_helper(root->rightChild);//calls minimum helper recursive method
            root->value = temp->value;
            root->rightChild = removeNode_helper(root->rightChild, temp->value);
        }
    }
    return root;
}

//you need to use free() to release the memory when a node is removed
int removeNode (struct bTree* root, int value) {
    removeNode_helper(root->root, value);//recursive function
    return 1;
}

int contain_helper(struct Node *root, int data){
    /* python 331
    def contains_rec(node):
              if not node:
                  return False
              elif val < node.val:
                  return contains_rec(node.left)
              elif val > node.val:
                  return contains_rec(node.right)
              else:
                  return True
    */
    if(root == NULL) {
        return 0;
    }else if (data > root->value) {
        return contain_helper(root->rightChild, data);
    }else if (data < root->value){
        return contain_helper(root->leftChild, data);
    }else{
        return 1;
    }
}

int contain (struct bTree* root, int value) {
    int temp = contain_helper(root->root, value);//call helper recursive method to find a val
    if(temp == 0){
        return 0;
    }
    else{
        return 1;
    }
}

void printInorder(struct Node* node)
{
    if (node == NULL){
        return;
    }
    printInorder(node->leftChild);
    printf("%d ", (node->value));
    printInorder(node->rightChild);
}

void printTree (struct bTree* root) {
    printInorder(root->root);
    printf("\n");
}

int main () {
    struct bTree* root = newTree(72);
    add(root, 12);
    add(root, 52);
    add(root, 87);
    add(root, 18);
    add(root, 49);
    add(root, 43);
    add(root, 82);
    add(root, 34);
    add(root, 73);
    add(root, 21);

    printTree(root);

    if(contain(root, 73) == 1){
        printf("This tree contains 73\n");
    }else{
        printf("This tree doesn't contains 73\n");
    }

    if(contain(root, 22) == 1){
        printf("This tree contains 22\n");
    }else{
        printf("This tree doesn't contains 22\n");
    }

    removeNode(root, 18);
    printf("After delete 18\n");
    printTree(root);

    removeNode(root, 49);
    printf("After delete 49\n");
    printTree(root);
    return 0;

}

