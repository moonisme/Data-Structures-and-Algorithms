#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

// all the basic data structures and functions are included in this template
// you can add your own auxiliary functions as you like

// data type for avl tree nodes
typedef struct AVLTreeNode
{
    int key; //key of this item
    int  value;  //value (int) of this item
    int height; //height of the subtree rooted at this node
    struct AVLTreeNode *parent; //pointer to parent
    struct AVLTreeNode *left; //pointer to left child
    struct AVLTreeNode *right; //pointer to right child
} AVLTreeNode;

//data type for AVL trees
typedef struct AVLTree
{
    int  size;      // count of items in avl tree
    AVLTreeNode *root; // root
} AVLTree;

// create a new AVLTreeNode
AVLTreeNode *newAVLTreeNode(int k, int v )
{
    AVLTreeNode *new;
    new = malloc(sizeof(AVLTreeNode));
    assert(new != NULL);
    new->key = k;
    new->value = v;
    new->height = 0; // height of this new node is set to 0
    new->left = NULL; // this node has no child
    new->right = NULL;
    new->parent = NULL; // no parent
    return new;
}

// create a new empty avl tree
AVLTree *newAVLTree()
{
    AVLTree *T;
    T = malloc(sizeof (AVLTree));
    assert (T != NULL);
    T->size = 0;
    T->root = NULL;
    return T;
}

static inline int get_height(AVLTreeNode *r)
{
    if(r == NULL)
        return -1;
    return r->height;
}

static inline int max(int a,int b)
{
    if(a > b)
        return a;
    else
        return b;
}

static inline int max_height(AVLTreeNode *r1, AVLTreeNode *r2)
{
    return max(get_height(r1), get_height(r2));
}

// put your time complexity analysis of CreateAVLTree() here
// O(nlogn)
AVLTree *CreateAVLTree(const char *filename)
{
// put your code here
    extern int InsertNode();
    AVLTree *T = newAVLTree();

    if(strcmp(filename, "stdin") == 0)   //read from keyboard
    {
        int k, v;
        int c;
        int state = 0;
        int isfinish = 0;
        char text[128];
        int  len = 0;
        while((c = getchar()) != EOF)
        {
            if(isfinish == 0 && c == '\n')
                isfinish = 1;
            else if(isfinish == 1 && c == '\n')
                break;
            else
                isfinish = 0;
            if(c == ' ' || c == '\t' || c == '\n')
                continue;
            switch(state)
            {
                case 0:
                    if(c == '(')
                        state = 1;
                    else
                        perror("input error!\n");
                    break;
                case 1:
                    if(isdigit(c) || c == '-')
                    {
                        text[len++] = c;
                        state = 2;
                    }
                    else
                        perror("input error!\n");
                    break;
                case 2:
                    if(isdigit(c))
                    {
                        text[len++] = c;
                    }
                    else if(c == ',')
                    {
                        text[len] = 0;
                        sscanf(text,"%d",&k);
                        len = 0;
                        state = 3;
                    }
                    else
                        perror("input error!\n");
                    break;
                case 3:
                    if(isdigit(c)|| c == '-')
                    {
                        text[len++] = c;
                        state = 4;
                    }
                    else
                        perror("input error!\n");
                    break;
                case 4:
                    if(isdigit(c))
                        text[len++] = c;
                    else if(c == ')')
                    {
                        text[len] = '\0';
                        sscanf(text,"%d",&v);
                        len = 0;
                        //printf("k=%d v=%d\n",k,v);
                        InsertNode(T,k,v);
                        state = 0;
                    }
                    else
                        perror("input error!\n");
                    break;
            }
        }
    }
    else                // read from file
    {
        FILE *fp = fopen(filename,"r");
        assert(fp != NULL);
        int k,v;
        int c;
        int state = 0;
        char text[128];
        int  len = 0;
        while((c = fgetc(fp)) != EOF)
        {
            if(c == ' ' || c == '\t' || c == '\n')
                continue;
            switch(state)
            {
                case 0:
                    if(c == '(')
                        state = 1;
                    else
                        perror("input error!\n");
                    break;
                case 1:
                    if(isdigit(c) || c == '-')
                    {
                        text[len++] = c;
                        state = 2;
                    }
                    else
                        perror("input error!\n");
                    break;
                case 2:
                    if(isdigit(c))
                        text[len++] = c;
                    else if(c == ',')
                    {
                        text[len] = 0;
                        sscanf(text,"%d",&k);
                        len = 0;
                        state = 3;
                    }
                    else
                        perror("input error!\n");
                    break;
                case 3:
                    if(isdigit(c)|| c == '-')
                    {
                        text[len++] = c;
                        state = 4;
                    }
                    else
                        perror("input error!\n");
                    break;
                case 4:
                    if(isdigit(c))
                        text[len++] = c;
                    else if(c == ')')
                    {
                        text[len] = '\0';
                        sscanf(text,"%d",&v);
                        len = 0;
                        //printf("k=%d v=%d\n",k,v);
                        InsertNode(T,k,v);
                        state = 0;
                    }
                    else
                        perror("input error!\n");
                    break;
            }

        }
    }
    return T;
}

static AVLTreeNode* recursive_clone(AVLTreeNode *N, AVLTreeNode *rparent)
{
    AVLTreeNode *r = NULL;
    if(N != NULL)
    {
        r = newAVLTreeNode(N->key,N->value);
        r->height = N->height;
        r->parent = rparent;
        r->left = recursive_clone(N->left,r);
        r->right = recursive_clone(N->right,r);
    }
    return r;
}

// put your time complexity analysis for CloneAVLTree() here
// O(n)
AVLTree *CloneAVLTree(AVLTree *T)
{
// put your code here
    AVLTree *cp = newAVLTree();
    cp->size = T->size;
    cp->root = recursive_clone(T->root,NULL);
    return cp;
}

struct pair_t
{
    int key;
    int value;
};

static int inorder(AVLTreeNode *r, struct pair_t a[], int *len)
{
    if(r!=NULL)
    {
        inorder(r->left,a,len);
        a[*len] = (struct pair_t){r->key,r->value};
        *len +=1;
        inorder(r->right,a,len);
    }
}

static int kvcmp(struct pair_t a, struct pair_t b)
{
    if(a.key < b.key)
        return -1;
    else if(a.key > b.key)
        return 1;
    else
    {
        if(a.value < b.value)
            return -1;
        else if(a.value > b.value)
            return 1;
        else
            return 0;
    }
}
// merge two array into one, store the result of union
static int merge_union(struct pair_t *a1, int len1, struct pair_t *a2, int len2, struct pair_t *x)
{
    int i = 0,j = 0,k = 0;
    while(i < len1 && j < len2)
    {
        int cmp = kvcmp(a1[i],a2[j]);
        if(cmp < 0)
            x[k++] = a1[i++];
        else if(cmp > 0)
            x[k++] = a2[j++];
        else
        {
            x[k++] = a1[i++];
            j++;
        }
    }
    while(i < len1)
        x[k++] = a1[i++];
    while(j < len2)
        x[k++] = a2[j++];
    return k;
}

// construct AVLTree from the merged array
static AVLTreeNode* construct_tree(struct pair_t *x, int begin, int end, AVLTreeNode *parent)
{
    AVLTreeNode *r = NULL;
    if(begin <= end)
    {
        int center = (begin+end+1)/2;
        r = newAVLTreeNode(x[center].key,x[center].value);
        r->parent = parent;
        r->left = construct_tree(x,begin,center-1,r);
        r->right = construct_tree(x,center+1,end,r);
        if(begin == end)
            r->height = 0;
        else
            r->height = max_height(r->left,r->right)+1;
    }
    return r;
}

// put your time complexity for AVLTreesUnion() here
// O(m+n)
AVLTree *AVLTreesUnion(AVLTree *T1, AVLTree *T2)
{
    //put your code here
    struct pair_t *a1,*a2,*x;
    a1 = malloc(T1->size * sizeof(*a1));
    a2 = malloc(T2->size * sizeof(*a2));
    x = malloc( (T1->size+T2->size) *sizeof(*x) );
    int len1 = 0,len2 = 0;
    inorder(T1->root,a1,&len1);
    inorder(T2->root,a2,&len2);
    int k = merge_union(a1,len1,a2,len2,x);
    AVLTree *t = newAVLTree();
    t->root = construct_tree(x,0,k-1,NULL);
    t->size = k;
    free(a1);
    free(a2);
    free(x);
    return t;
}

static int merge_intersection(struct pair_t *a1,int len1,struct pair_t *a2,int len2,struct pair_t *x)
{
    int i = 0, j = 0, k = 0;
    while(i < len1 && j < len2)
    {
        int cmp = kvcmp(a1[i],a2[j]);
        if(cmp == 0)
        {
            x[k++] = a1[i++];
            j++;
        }
        else if(cmp < 0)
            i++;
        else
            j++;
    }
    return k;
}

// put your time complexity for ALVTreesIntersection() here
// O(m+n)
AVLTree *AVLTreesIntersection(AVLTree *T1, AVLTree *T2)
{
    //put your code here
    struct pair_t *a1,*a2,*x;
    a1 = malloc(T1->size * sizeof(*a1));
    a2 = malloc(T2->size * sizeof(*a2));
    x = malloc( (T1->size+T2->size) *sizeof(*x) );
    int len1 = 0,len2 = 0;
    inorder(T1->root,a1,&len1);
    inorder(T2->root,a2,&len2);
    int k = merge_intersection(a1,len1,a2,len2,x);
    AVLTree *t = newAVLTree();
    t->root = construct_tree(x,0,k-1,NULL);
    t->size = k;
    free(a1);
    free(a2);
    free(x);
    return t;
}

static AVLTreeNode* ll_rotate(AVLTreeNode *k2)
{
    AVLTreeNode *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k1->parent = k2->parent;
    k2->parent = k1;
    if(k2->left) k2->left->parent = k2;
    k2->height = max_height(k2->left,k2->right)+1;
    k1->height = max_height(k1->left,k1->right)+1;
    return k1;
}

static AVLTreeNode* rr_rotate(AVLTreeNode *k2)
{
    AVLTreeNode *k1=k2->right;
    k2->right = k1->left;
    k1->left = k2;
    k1->parent = k2->parent;
    k2->parent = k1;
    if(k2->right) k2->right->parent = k2;
    k2->height = max_height(k2->left, k2->right) + 1;
    k1->height = max_height(k1->left, k1->right) + 1;
    return k1;
}

static AVLTreeNode* lr_rotate(AVLTreeNode *k3)
{
    k3->left = rr_rotate(k3->left);
    return ll_rotate(k3);
}

static AVLTreeNode* rl_rotate(AVLTreeNode *k3)
{
    k3->right = ll_rotate(k3->right);
    return rr_rotate(k3);
}

// helper function for InsertNode() in AVLTree
static AVLTreeNode* avl_add(AVLTreeNode *r,int k,int v,AVLTreeNode *parent)
{
    if(r == NULL)
    {
        r = newAVLTreeNode(k, v);
        r->parent = parent;
        return r;
    }
    if(k < r->key || (k == r->key && v < r->value)) //x<r->data
    {
        r->left = avl_add(r->left, k, v, r);
        int hl = get_height(r->left);
        int hr = get_height(r->right);
        if (hl - hr == 2)
        {

            if(k < r->left->key || (k == r->left->key && v < r->left->value))
                r = ll_rotate(r);
            else
                r = lr_rotate(r);
        }
    }
    else
    {
        r->right = avl_add(r->right, k, v, r);
        int hl = get_height(r->left);
        int hr = get_height(r->right);
        if(hr - hl == 2)
        {
            if(k > r->right->key || (k == r->right->key && v > r->right->value))
                r = rr_rotate(r);
            else
                r = rl_rotate(r);
        }
    }
    r->height = max_height(r->left, r->right) + 1;
    return r;
}

// put the time complexity analysis for InsertNode() here
// O(logn)
int InsertNode(AVLTree *T, int k, int v)
{
    //put your code here
    AVLTreeNode *Search(AVLTree *T, int k, int v);
    if(Search(T, k, v) != NULL)
        return 0;

    T->root = avl_add(T->root, k, v, NULL);
    T->size += 1;
    return 1;
}

// helper function for avl_del(), find the largest key in the tree
static AVLTreeNode* tree_max(AVLTreeNode *r)
{
    while(r != NULL && r->right != NULL)
        r = r->right;
    return r;
}

static int get_factor(AVLTreeNode *r)
{
    if(r == NULL)
        return 0;
    return get_height(r->left) - get_height(r->right);
}

// gelper function for DeleteNode() in AVLTree
static AVLTreeNode* avl_del(AVLTreeNode* r, int k, int v)
{
    if(r == NULL)
        return NULL;
    if(k < r->key || (k == r->key && v < r->value))
        r->left = avl_del(r->left, k, v);
    else if(k > r->key || (k == r->key && v > r->value))
        r->right = avl_del(r->right, k, v);
    else
    {
        if(r->left != NULL && r->right != NULL)
        {
            AVLTreeNode *t = tree_max(r->left);
            r->key = t->key;
            r->value = t->value;
            t->key = k;
            t->value = v;
            r->left = avl_del(r->left, k, v);
        } else if(r->left == NULL && r->right == NULL)
        {
            free(r);
            r = NULL;
        }
        else
        {
            AVLTreeNode *p=r;
            if(r->left)
            {
                r->left->parent = r->parent;
                r = r->left;
            }
            else
            {
                r->right->parent = r->parent;
                r = r->right;
            }
            free(p);
        }
    }
    int froot = get_factor(r);
    if(froot == 2)
    {
        int fleft = get_factor(r->left);
        if(fleft == 1)
            r = ll_rotate(r);
        else if(fleft == -1)
            r = lr_rotate(r);
    }
    else if(froot == -2)
    {
        int fright = get_factor(r->right);
        if(fright == 1)
            r = rl_rotate(r);
        else if(fright == -1)
            r = rr_rotate(r);
    }
    return r;
}

// put the time complexity analysis for DeleteNote() here
// O(logn)
int DeleteNode(AVLTree *T, int k, int v)
{
// put your code here
    AVLTreeNode *Search(AVLTree *T, int k, int v);
    if(Search(T, k, v) == NULL)
        return 0;

    T->root = avl_del(T->root, k, v);
    T->size -= 1;
    return 1;
}

// put your time complexity analysis for Search() here
// O(logn)
AVLTreeNode *Search(AVLTree *T, int k, int v)
{
    // put your code here
    AVLTreeNode *r=T->root;
    while(r != NULL)
    {
        if(k < r->key)
            r = r->left;
        else if(k > r->key)
            r = r->right;
        else if(v < r->value)
            r = r->left;
        else if(v > r->value)
            r = r->right;
        else
            return r;
    }
    return NULL;
}

// helper function for FreeAVLTree, we free nodes in tree recursively
static void recursive_free(AVLTreeNode *r)
{
    if(r != NULL)
    {
        recursive_free(r->left);
        recursive_free(r->right);
        free(r);
    }
}

// put your time complexity analysis for freeAVLTree() here
// O(n)
void FreeAVLTree(AVLTree *T)
{
// put your code here
    assert(T != NULL);
    recursive_free(T->root);
    free(T);
}

// helper function for PrintAVLTree(), we print nodes in tree recursively
static void print_node(AVLTreeNode *r)
{
    if (r != NULL)
    {
        print_node(r->left);
        printf("(%d,%d) %d\n", r->key, r->value, r->height);
        print_node(r->right);
    }
}

// put your time complexity analysis for PrintAVLTree() here
// O(n)
void PrintAVLTree(AVLTree *T)
{
// put your code here
    assert(T != NULL);
    AVLTreeNode *r = T->root;
    print_node(r);
    printf("\n--------------------------------\n");
}

int main() //sample main for testing
{
    int i, j;
    AVLTree *tree1, *tree2, *tree3, *tree4, *tree5, *tree6, *tree7, *tree8;
    AVLTreeNode *node1;
    tree1 = CreateAVLTree("stdin");
    PrintAVLTree(tree1);
    FreeAVLTree(tree1);

// you need to create the text file file1.txt
// to store a set of items without duplicate items
    tree2 = CreateAVLTree("file1.txt");
    PrintAVLTree(tree2);
    tree3 = CloneAVLTree(tree2);
    PrintAVLTree(tree3);
    FreeAVLTree(tree2);
    FreeAVLTree(tree3);

    tree4 = newAVLTree();
    j = InsertNode(tree4, 10, 10);
    for(i = 0; i < 15; i++) {
        j = InsertNode(tree4, i, i);
        if(j == 0)
            printf("(%d, %d) already exists\n", i, i);
    }
    PrintAVLTree(tree4);
    node1 = Search(tree4, 20, 20);
    if(node1 != NULL)
        printf("key= %d value= %d\n", node1->key, node1->value);
    else
        printf("Key 20 does not exist\n");

    for (i = 17; i >= 0; i--)
    {
        j = DeleteNode(tree4, i, i);
        if (j == 0)
            printf("Key %d does not exist\n", i);
        PrintAVLTree(tree4);
    }
    FreeAVLTree(tree4);
    tree5 = newAVLTree();
    j = InsertNode(tree5, 6, 10);
    j = InsertNode(tree5, 6, 12);
    j = InsertNode(tree5, 6, 20);
    j = InsertNode(tree5, 6, 25);
    j = InsertNode(tree5, 9, 25);
    j = InsertNode(tree5, 10, 25);
    printf("This is tree5:\n");
    PrintAVLTree(tree5);
    //Create tree6
    tree6 = newAVLTree();
    j = InsertNode(tree6, 5, 10);
    j = InsertNode(tree6, 6, 12);
    j = InsertNode(tree6, 6, 20);
    j = InsertNode(tree6, 6, 25);
    j = InsertNode(tree6, 8, 35);
    j = InsertNode(tree6, 10, 25);
    printf("This is tree6:\n");
    PrintAVLTree(tree6);
    tree7 = AVLTreesIntersection(tree5, tree6);
    tree8 = AVLTreesUnion(tree5, tree6);
    printf("This is the intersection of tree5 and tree6:\n");
    PrintAVLTree(tree7);
    printf("This is the union of tree5 and tree6:\n");
    PrintAVLTree(tree8);
    return 0;
}