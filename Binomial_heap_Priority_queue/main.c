#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// This template is only a guide
// You need to include additional fields, data structures and functions

// data type for heap nodes
typedef struct HeapNode {
    // each node stores the priority (key), name, execution time,
    //  release time and deadline of one task
    int key; //key of this task
    int TaskName;  // task name
    int Etime; //execution time of this task
    int Rtime; // release time of this task
    int Dline; // deadline of this task
    int height;
    struct HeapNode *child;
    struct HeapNode *next;
    struct HeapNode *parent;
} HeapNode;

//data type for a priority queue (heap)
typedef struct BinomialHeap{
    int  size;      // count of items in the heap
    struct HeapNode *root;
} BinomialHeap;

// create a new heap node to store an item (task)
HeapNode *newHeapNode(int k, int n, int c, int r, int d, HeapNode *C, HeapNode *N, HeapNode *P)
{ // k:key, n:task name, c: execution time, r:release time, d:deadline
    HeapNode *new;
    new = malloc(sizeof(HeapNode));
    assert(new != NULL);
    new->key = k;
    new->TaskName = n;
    new->Etime = c;
    new->Rtime = r;
    new->Dline = d;
    new->child = NULL;
    new->next = NULL;
    new->parent = NULL;
    new->height = 0;
    return new;
}

// create a new empty heap-based priority queue
BinomialHeap *newHeap()
{ // this function creates an empty heap-based priority queue
    BinomialHeap *T;
    T = malloc(sizeof(BinomialHeap));
    assert (T != NULL);
    T->size = 0;
    T->root = NULL;
    return T;
}

// helper function for merge two binomial heap change HeapNode attributes
static int link(struct HeapNode *parent, struct HeapNode *child)
{
    child->parent = parent;
    child->next = parent->child;
    parent->child = child;
    parent->height++;
    return 0;
}

// helper function for merge two binomial heap reconstruct heap
static struct HeapNode* merge(struct HeapNode *r1, struct HeapNode *r2)
{
    struct HeapNode *tmp;
    struct HeapNode *heap = NULL, **tail = &heap;

    while(r1 != NULL && r2 != NULL)
    {
        if(r1->height <= r2->height)
        {
            tmp = r1;
            r1 = r1->next;
        }
        else
        {
            tmp = r2;
            r2 = r2->next;
        }
        *tail = tmp;
        tail = &(*tail)->next;
    }
    if(r1 != NULL)
        *tail = r1;
    else
        *tail = r2;
    return heap;
}

// helper function for insert,basically we just need to merge an existed heap and a heap with one element
static struct HeapNode* heap_union(struct HeapNode *r1, struct HeapNode *r2)
{
    struct HeapNode *root, *prev = NULL, *r, *next;
    if(r1 == NULL || r2 == NULL)
    {
        return r1?r1:r2;
    }
    root = merge(r1,r2);
    r = root;
    for(next = r->next; next; next = r->next)
    {
        if(r->height != next->height || (next->next && r->height == next->next->height)) // case 1, case 2
        {
            prev = r;
            r = next;
        }
        else if(r->key <= next->key)  //case 3
        {
            r->next = next->next;
            link(r,next);
        }
        else    // case 4
        {
            if(prev == NULL)
                root = next;
            else
                prev->next = next;
            link(next,r);
            r = next;
        }
    }
    return root;
}

// helper function for Min(), travsering root and it's siblings
static struct HeapNode** find_min(struct HeapNode **root)
{
    struct HeapNode **r, **min = root;
    for(r=root; *r; r=&(*r)->next)
    {
        if((*min)->key>(*r)->key)
            min = r;
    }
    return min;
}

// put the time complexity analysis for Insert() here
// O(logn)
void Insert(BinomialHeap *T, int k, int n, int c, int r, int d)
{ // k: key, n: task name, c: execution time, r: release time, d:deadline
    // You don't need to check if this task already exists in T
    //put your code here
    struct HeapNode *s;
    s = newHeapNode(k,n,c,r,d,NULL,NULL,NULL);
    T->size++;
    T->root = heap_union(T->root, s);
}

// put your time complexity for RemoveMin() here
// O(logn)
HeapNode *RemoveMin(BinomialHeap *T)
{
    struct HeapNode **min, *s;
    min = find_min(&T->root);
    s = *min;
    *min = (*min)->next;

    struct HeapNode *tmp, *r = NULL, *r1 = s->child;
    while(r1)
    {
        tmp = r1;
        r1 = r1->next;
        tmp->parent = NULL;
        tmp->next = r;
        r = tmp;
    }
    T->size--;
    T->root = heap_union(T->root, r);
    return s;
}

// need to call this function in TaskScheduler
HeapNode* get_min(BinomialHeap *T)
{
    struct HeapNode **min;
    min = find_min(&T->root);
    return *min;
}

// put your time complexity for Min() here
// O(logn)
int Min(BinomialHeap *T)
{
    struct HeapNode **min;
    min = find_min(&T->root);
    return (*min)->key;
}

// use for test
void print(HeapNode* r)
{
    if(r != NULL)
    {
        printf(" %d %d \n",r->key,r->height);
        print(r->child);
        print(r->next);
    }
}

// use for test
void print_heap(BinomialHeap *T)
{
    assert(T != NULL);
    HeapNode *r = T->root;
    print(r);
}

// operations of heap is O(logn), there may exists n tasks, so the total complexity is
// O(nlogn)
int TaskScheduler(char *f1, char *f2, int m )
{
    FILE *fp = fopen(f1,"r");
    if (fp==NULL){
        printf("%s does not exist",f1);
        exit(1);
    }
    BinomialHeap *A=newHeap();                      //read data from file1

    int a,b,c,d;
    while(!feof(fp))
    {
        fscanf(fp,"%d %d %d %d\n",&a,&b,&c,&d);
        Insert(A,c,a,b,c,d);      //release time as key
    }
    fclose(fp);

    FILE *fp2 = fopen(f2,"w");    //write data to file2


    BinomialHeap *B=newHeap();// use deadline as key
    BinomialHeap *R=newHeap();// request finish time for core
    for(int i=0;i<m;i++)
        Insert(R,-999999+i,i,0,0,0);
    int core=m;

    int current_time=0;

    while(A->size>0 || B->size>0)
    {
        if(A->size>0)
        {
            HeapNode *x=get_min(A);
            while(x->Rtime<=current_time)
            {
                Insert(B,x->Dline,x->TaskName,x->Etime,x->Rtime,x->Dline);
                RemoveMin(A);
                if(A->size>0)
                    x=get_min(A);
                else
                    break;
            }
        }
        //dispatch task
        while(core>0 && B->size>0) //this time exist task and idle core
        {
            HeapNode *y=get_min(B);
            HeapNode *idle=get_min(R);
            int start_time=idle->key>y->Rtime?idle->key:y->Rtime; //get start time of ready task
            int finish_time=start_time+y->Etime;
            if(finish_time<=y->Dline)
            {
                //printf("%d core%d %d F=%d\n",y->TaskName,idle->TaskName,start_time,F->size);
                fprintf(fp2,"%d core%d %d\n",y->TaskName,idle->TaskName,start_time);
                Insert(R,finish_time,idle->TaskName,0,0,0);
                RemoveMin(R);
            }
            else
            {
                return 0;
            }
            //cost one core
            core--;
            //schedule a task
            RemoveMin(B);
        }

        if(core==0)     //there is no idle core, update current time by the core which finish firstly
        {
            int a[1024],len=0;
            HeapNode *finish=get_min(R);
            int ftime=finish->key;
            while(finish->key==ftime)
            {
                a[len++]=finish->TaskName;  //core name
                RemoveMin(R);
                if(R->size>0)
                {
                    finish=get_min(R);
                    core++;
                }
                else
                    break;
            }
            current_time=ftime;
            for(int i=0;i<len;i++)
                Insert(R,ftime,a[i],0,0,0);
        }
        else if(A->size!=0)     //exist idle core,but no task, update current time by the task which release firstly
        {
            HeapNode *first=get_min(A);
            current_time=first->Rtime;

            int core_id[1024],core_time[1024],len=0;
            HeapNode *finish=get_min(R);
            while(finish->key<=current_time)
            {
                core_id[len]=finish->TaskName; //core name
                core_time[len]=finish->key;
                len++;
                RemoveMin(R);
                if(R->size>0)
                {
                    finish=get_min(R);
                    core++;
                }
                else
                    break;
            }
            for(int i=0;i<len;i++)
                Insert(R,core_time[i],core_id[i],0,0,0);
        }
    }
    return 1;
}

int main() //sample main for testing
{
//    BinomialHeap *a;
//    a = newHeap();
//    Insert(a,0,1,4,0,10);
//    Insert(a,0,2,6,0,15);
//    Insert(a,2,3,2,2,6);
//    Insert(a,2,4,2,2,8);
//    Insert(a,2,5,2,2,8);
//    Insert(a,1,6,5,1,13);
//    Insert(a,2,7,5,2,13);
//    Insert(a,5,8,5,5,18);
//    Insert(a,5,9,3,5,19);
//    Insert(a,5,10,2,5,19);
//    Insert(a,6,11,4,6,24);
//    Insert(a,6,12,5,6,24);
//    print_heap(a);
//    printf("--------------\n");
//    RemoveMin(a);
//    print_heap(a);
//    printf("--------------\n");
//    RemoveMin(a);
//    print_heap(a);
//    printf("--------------\n");
//    RemoveMin(a);
//    print_heap(a);
//    printf("--------------\n");
//    RemoveMin(a);
//    print_heap(a);
//    printf("--------------\n");
//    RemoveMin(a);
//    print_heap(a);
//    printf("--------------\n");
//    RemoveMin(a);
//    print_heap(a);
//    printf("--------------\n");
//    RemoveMin(a);
//    print_heap(a);

    int i;
    i=TaskScheduler("samplefile1.txt", "feasibleschedule1.txt", 4);
    if (i==0) printf("1.No feasible schedule!\n");
    /* There is a feasible schedule on 4 cores */
    i=TaskScheduler("samplefile1.txt", "feasibleschedule2.txt", 3);
    if (i==0) printf("2.No feasible schedule!\n");
    /* There is no feasible schedule on 3 cores */
    i=TaskScheduler("samplefile2.txt", "feasibleschedule3.txt", 5);
    if (i==0) printf("3.No feasible schedule!\n");
    /* There is a feasible schedule on 5 cores */
    i=TaskScheduler("samplefile2.txt", "feasibleschedule4.txt", 4);
    if (i==0) printf("4.No feasible schedule!\n");
    /* There is no feasible schedule on 4 cores */
    i=TaskScheduler("samplefile3.txt", "feasibleschedule5.txt", 2);
    if (i==0) printf("5.No feasible schedule!\n");
    /* There is no feasible schedule on 2 cores */
    i=TaskScheduler("samplefile4.txt", "feasibleschedule6.txt", 2);
    if (i==0) printf("6.No feasible schedule!\n");
    /* There is a feasible schedule on 2 cores */

    return 0;
}
