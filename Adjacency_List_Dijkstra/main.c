#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

// A vertex is a 2D point
typedef struct Vertex {
    int x; // x-coordinate
    int y; // y-coordinate
} Vertex;
// each edge is a pair of vertices (end-points)
typedef struct Edge {
    Vertex *p1; // first end point
    Vertex *p2; // second end point
    double distance;
} Edge;

typedef struct AdjacentNode {
    Vertex *v;
    struct AdjacentNode *next_edge;
    struct VertexNode *last;
} AdjacentNode;

// A vertex node stores a vertex and other information, and you need to expand this type
typedef struct VertexNode {
    Vertex *v;
    struct AdjacentNode *head;
    struct VertexNode *next;
    int status;    // 0: unexplored 1: explored
} VertexNode;

typedef struct GraphRep *Graph;

typedef struct GraphRep { // graph header
    VertexNode *vertices; // an array of vertices or a linked list of vertices
    int nV; // #vertices
    int nE; // #edges
} GraphRep;

typedef struct QueueNode {
    Vertex *v;
    struct QueueNode *next;
} QueueNode;

typedef struct QueueRep *Queue;

typedef struct QueueRep {
    struct QueueNode *front;
    struct QueueNode *rear;
    int size;
} QueueRep;

// Add the time complexity analysis of CreateEmptyGraph() here
Graph CreateEmptyGraph()
{
    Graph g = malloc(sizeof(GraphRep));
    assert(g != NULL);
    g->nE = 0;
    g->nV = 0;
    g->vertices = NULL;
    return g;
}

// create a new node in Adjacency list
AdjacentNode *NewAdjacentNode(Vertex *a)
{
    AdjacentNode *node;
    node = malloc(sizeof(AdjacentNode));
    assert(node != NULL);
    node->v = a;
    node->next_edge = NULL;
    node->last = NULL;
    return node;
}

// create a new vertex node
VertexNode *NewVertex(Vertex *a)
{
    VertexNode *node;
    node = malloc(sizeof(VertexNode));
    assert(node != NULL);
    node->v = a;
    node->head = NULL;
    node->status = 0;
    return node;
}

// if edge already exist in the list,return 1
// if length of A is m, then this function cost O(m)
int EdgeInList(AdjacentNode *A, Vertex *a)
{
    if(A == NULL)
        return 0;
    if(A->v->x == a->x && A->v->y == a->y)
        return 1;
    return  EdgeInList(A->next_edge,a);
}

// insert a new node in Adjacency list
// if length of A is m, then this function cost O(m)
AdjacentNode *InsertList(AdjacentNode *A, Vertex *a)
{
    AdjacentNode *node = NewAdjacentNode(a);
    if(EdgeInList(A,a) == 1)
        return A;
    node->next_edge = A;
    return node;
}

// search node in Adjacency list before insert and delete
// if there are n nodes in the graph, then this function cost O(n)
VertexNode *SearchList(VertexNode *node, Vertex *a)
{
    while(node != NULL)
    {
        if(node->v->x == a->x && node->v->y == a->y)
            return node;
        node = node->next;
    }
    return NULL;
}
// Add the time complexity analysis of InsertEdge() here
// First,we need to search for the node in the graph, if it exists, we check it's edge, otherwsie, we create a new node
// need to call SearchList() and EdgeInList(), thus it's O(m+n)
int InsertEdge(Graph g, Edge *e)
{
    AdjacentNode *A;
    AdjacentNode *B;
    VertexNode *node1 = SearchList(g->vertices,e->p1);
    VertexNode *node2 = SearchList(g->vertices,e->p2);
    if(node1 != NULL)     //check whether the vertex is exist
    {
        if(EdgeInList(node1->head,e->p2) != 0) //check whether the edge is exist
            return 0;
        else
            A = InsertList(node1->head,e->p2);
        if(node2 == NULL)             // if node2 is a new node in the graph
        {
            node2 = NewVertex(e->p2);
            node2->next = g->vertices;
            g->vertices = node2;
            g->nV++;
        }
        A->last = node2;
        node1->head = A;
        B = InsertList(node2->head,e->p1);
        B->last = node1;
        node2->head = B;
    }
    else
    {
        if(node2 == NULL)
        {
            node2 = NewVertex(e->p2);
            node2->next = g->vertices;
            g->vertices = node2;
            g->nV++;
        }
        else
        {
            if(EdgeInList(node2->head,e->p1) != 0)
                return 0;
        }
        node1 = NewVertex(e->p1);
        node1->next = g->vertices;
        g->vertices = node1;
        g->nV++;
        A = InsertList(node1->head,e->p2);
        A->last = node2;
        node1->head = A;
        B = InsertList(node2->head,e->p1);
        B->last = node1;
        node2->head = B;
    }
    g->nE++;
    return 1;
}

// if length of A is m, then this function cost O(m)
AdjacentNode *DeleteList(AdjacentNode *A, Vertex *a)
{
    if(A == NULL)
        return A;
    if(A->v->x == a->x && A->v->y == a->y)
    {
        A->last = NULL;
        return A->next_edge;
    }
    A->next_edge = DeleteList(A->next_edge,a);
    return A;

}
// Add the time complexity analysis of DeleteEdge() here
// First,we need to search for the node in the graph, if it donesn't exists, just return, otherwsie, we delete the edge
// need to call SearchList() and EdgeInList(), thus it's O(m+n)
void DeleteEdge(Graph g, Edge *e)
{
    VertexNode *node1 = SearchList(g->vertices,e->p1);
    VertexNode *node2 = SearchList(g->vertices,e->p2);
    if(node1 == NULL || node2 == NULL)
        return;
    if(EdgeInList(node1->head,e->p2) != 0 && EdgeInList(node2->head,e->p1) != 0)
    {
        node1->head = DeleteList(node1->head,e->p2);
        node2->head = DeleteList(node2->head,e->p1);
        g->nE--;
    }
}

Queue CreateEmptyQueue()
{
    Queue q;
    q = malloc(sizeof(QueueRep));
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}

void EnQueue(Queue q,Vertex *a)
{
    QueueNode *node;
    node = malloc(sizeof(QueueNode));
    node->v = a;
    node->next = NULL;
    if(q->front == NULL)
    {
        q->front = node;
        q->rear = node;
    }
    else
    {
        q->rear->next = node;
        q->rear = node;
    }
    q->size++;
}

// pop the first vertex out
Vertex *DeQueue(Queue q)
{
    Vertex *a;
    QueueNode *node;
    node = q->front;
    assert(q->size > 0);
    q->front = q->front->next;
    if(q->front == NULL)
        q->rear = NULL;
    q->size--;
    a = node->v;
    free(node);
    return a;
}

// Add the time complexity analysis of ReachableVertices() here
// BFS travseal order
// if there are n vertices and m edges, each vertex is inserted once into the queue which takes O(n)
// SearchList is called once for each vertex which takes O(deg(v)) = 2m
// Hence, the total time complexity is O(m+n)
void ReachableVertices(Graph g, Vertex *v)
{
    Vertex *a;
    AdjacentNode *A;
    Queue q = CreateEmptyQueue();
    QueueNode *temp1,*temp2,*t1,*t2,*p;
    VertexNode *node,*reach;

    assert(g!=NULL);
    node = SearchList(g->vertices,v);
    EnQueue(q,node->v);
    temp1 = q->front;
    while(temp1 != NULL)
    {
        a = temp1->v;
        reach = SearchList(g->vertices,a);
        A = reach->head;
        while(A != NULL)
        {
            reach = A->last;
            if(reach->status == 0)
            {
                reach->status = 2;
                EnQueue(q,reach->v);
            }
            A = A->next_edge;
        }
        temp1 = temp1->next;
    }
    p = q->front->next;
    temp1 = p->next;
    p->next = NULL;
    while(temp1 != NULL)
    {
        t1 = temp1;
        temp2 = p;
        t2 = temp2;
        while(temp2 != NULL)
        {
            t2 = temp2;
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
        t2->next = t1;
        t1->next = temp2;
    }
    while(p->next != NULL)
    {
        printf("(%d,%d),",p->v->x,p->v->y);
        p = p->next;
    }
    printf("(%d,%d)",p->v->x,p->v->y);
}

int getIdByVertex(Graph g, Vertex *v)
{
    int index = 0;
    VertexNode *vn = g->vertices;
    while (vn != NULL)
    {
        if (vn->v->x == v->x && vn->v->y == v->y)
            break;
        vn = vn->next;
        index++;
    }
    return index;
}

Vertex* getVertexById(Graph g, int id)
{
    int index = 0;
    VertexNode *vn = g->vertices;
    while (index != id)
    {
        vn = vn->next;
        index++;
    }
    return vn->v;
}

VertexNode* getVertexNodeByVertex(Graph g, Vertex *v)
{
    VertexNode *vn = g->vertices;
    while (vn != NULL)
    {
        if (vn->v->x == v->x && vn->v->y == v->y)
            break;
        vn = vn->next;
    }
    return vn;
}

// Add the time complexity analysis of ShortestPath() here
// use Dijkstra's Algorithm, didn't see the requirement in specifications until the last day
// any marks? T_T
// need to use heap, use Dijkstra's Algorithm directly cost O(n*n)
void ShortestPath(Graph g, Vertex *u, Vertex *v)
{
    int nodeNum = g->nV;
    double N = 10000000000.0;
    char *S = (char *)calloc(nodeNum, sizeof(char));
    double *dis = (double *)calloc(nodeNum, sizeof(double));
    int *parent = (int *)calloc(nodeNum, sizeof(int));

    VertexNode* vn = getVertexNodeByVertex(g, u);
    int parentId = getIdByVertex(g, u);
    int des = getIdByVertex(g, v);

    if (parentId == nodeNum || des == nodeNum)
        return;
    AdjacentNode* nextNode = vn->head;

    while (nextNode != NULL)
    {
        int nodeId = getIdByVertex(g, nextNode->v);
        double distant = sqrt((nextNode->v->x - vn->v->x) * (nextNode->v->x - vn->v->x) + (nextNode->v->y - vn->v->y) * (nextNode->v->y - vn->v->y));
        dis[nodeId] = distant;
        parent[nodeId] = parentId;
        nextNode = nextNode->next_edge;
    }
    for(int i = 0; i < nodeNum; i++)
    {
        if (dis[i] == 0)
        {
            dis[i] = N;
            parent[i] = -1;
        }
        S[i] = 0;
    }
    dis[parentId] = 0;
    S[parentId] = 1;
    int cnt = 1;
    while(cnt < nodeNum)
    {
        double minDis = N;
        int tag = -1;
        for(int i = 0; i < nodeNum; i++)
        {
            if(S[i] == 0 && dis[i] <= minDis)
            {
                minDis = dis[i];
                tag = i;
            }
        }
        if (tag == des)
            break;
        S[tag] = 1;

        Vertex* vertex = getVertexById(g, tag);
        vn = getVertexNodeByVertex(g, vertex);
        nextNode = vn->head;
        while (nextNode != NULL)
        {
            int nodeId = getIdByVertex(g, nextNode->v);
            double cost = sqrt((nextNode->v->x - vn->v->x) * (nextNode->v->x - vn->v->x) + (nextNode->v->y - vn->v->y) * (nextNode->v->y - vn->v->y));
            if (S[nodeId] == 0 && (cost + dis[tag]) < dis[nodeId])
            {
                dis[nodeId] = cost + dis[tag];
                parent[nodeId] = tag;
            }
            nextNode = nextNode->next_edge;
        }
        cnt++;
    }
    if (dis[des] == N)
        return;
    else
    {
        int count = 0;
        int arr[1000];
        while (parent[des] != -1)
        {
            arr[count++] = des;
            des = parent[des];
        }
        arr[count++] = parentId;
        for (int i = count - 1; i >= 0; i--)
        {
            Vertex* vertex = getVertexById(g, arr[i]);
            printf("(%d,%d),", vertex->x, vertex->y);
        }
    }
}

// if length of A is m, then it's O(m)
void FreeList(AdjacentNode *A)
{
    if(A != NULL)
    {
        FreeList(A->next_edge);
        free(A);
    }
}

// Add the time complexity analysis of FreeGraph() here
// if there are n vertices and m edges in the graph then this function cost O(m+n)
void FreeGraph(Graph g)
{
    VertexNode *node;
    node = g->vertices;
    while(node != NULL)
    {
        FreeList(node->head);
        node = node->next;
    }
    free(g);
}

// Add the time complexity analysis of ShowGraph() here
// BFS travseal order
// if there are n vertices and m edges, each vertex is inserted once into the queue which takes O(n)
// SearchList is called once for each vertex which takes O(deg(v)) = 2m
// Hence, the total time complexity is O(m+n)
void ShowGraph(Graph g)
{
    Vertex *a;
    AdjacentNode *A;
    Queue q = CreateEmptyQueue();
    VertexNode *node,*p1,*p2;
    assert(g != NULL);
    node = g->vertices;
    while(node != NULL)
    {
        if(node->status == 0)
        {
            EnQueue(q,node->v);
            while(q->size != 0)
            {
                a = DeQueue(q);
                p1 = SearchList(g->vertices,a);
                p1->status = 1;
                A = p1->head;
                while(A != NULL)
                {
                    p2 = A->last;
                    if(p2->status == 0)
                    {
                        EnQueue(q,p2->v);
                        printf("(%d,%d),(%d,%d) ",p1->v->x,p1->v->y,p2->v->x,p2->v->y);
                    }
                    A = A->next_edge;
                }
            }
        }
        node = node->next;
    }
    node = g->vertices;
    while(node != NULL)
    {
        node->status = 0;
        node = node->next;
    }
    printf("\n");
}

int main() //sample main for testing
{
    Graph g1;
    Edge *e_ptr;
    Vertex *v1, *v2;

    // Create an empty graph g1;
    g1=CreateEmptyGraph();

    // Create first connected component
    // Insert edge (0,0)-(0,10)
    e_ptr = (Edge*) malloc(sizeof(Edge));
    assert(e_ptr != NULL);
    v1=(Vertex*) malloc(sizeof(Vertex));
    assert(v1 != NULL);
    v2=(Vertex *) malloc(sizeof(Vertex));
    assert(v2 != NULL);
    v1->x=0;
    v1->y=0;
    v2->x=0;
    v2->y=10;
    e_ptr->p1=v1;
    e_ptr->p2=v2;
    if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
    printf("\nshow graph:\n");
    ShowGraph(g1);

    // Insert edge (0,0)-(5,6)
    e_ptr = (Edge*) malloc(sizeof(Edge));
    assert(e_ptr != NULL);
    v1=(Vertex*) malloc(sizeof(Vertex));
    assert(v1 != NULL);
    v2=(Vertex *) malloc(sizeof(Vertex));
    assert(v2 != NULL);
    v1->x=0;
    v1->y=0;
    v2->x=5;
    v2->y=6;
    e_ptr->p1=v1;
    e_ptr->p2=v2;
    if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
    printf("\nshow graph:\n");
    ShowGraph(g1);

    // Insert edge (0, 10)-(10, 10)
    e_ptr = (Edge*) malloc(sizeof(Edge));
    assert(e_ptr != NULL);
    v1=(Vertex*) malloc(sizeof(Vertex));
    assert(v1 != NULL);
    v2=(Vertex *) malloc(sizeof(Vertex));
    assert(v2 != NULL);
    v1->x=0;
    v1->y=10;
    v2->x=10;
    v2->y=10;
    e_ptr->p1=v1;
    e_ptr->p2=v2;
    if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
    printf("\nshow graph:\n");
    ShowGraph(g1);

    // Insert edge (0,10)-(5,6)
    e_ptr = (Edge*) malloc(sizeof(Edge));
    assert(e_ptr != NULL);
    v1=(Vertex*) malloc(sizeof(Vertex));
    assert(v1 != NULL);
    v2=(Vertex *) malloc(sizeof(Vertex));
    assert(v2 != NULL);
    v1->x=0;
    v1->y=10;
    v2->x=5;
    v2->y=6;
    e_ptr->p1=v1;
    e_ptr->p2=v2;
    if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
    printf("\nshow graph:\n");
    ShowGraph(g1);

    // Insert edge (0,0)-(5,4)
    e_ptr = (Edge*) malloc(sizeof(Edge));
    assert(e_ptr != NULL);
    v1=(Vertex*) malloc(sizeof(Vertex));
    assert(v1 != NULL);
    v2=(Vertex *) malloc(sizeof(Vertex));
    assert(v2 != NULL);
    v1->x=0;
    v1->y=0;
    v2->x=5;
    v2->y=4;
    e_ptr->p1=v1;
    e_ptr->p2=v2;
    if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
    printf("\nshow graph:\n");
    ShowGraph(g1);
//
    // Insert edge (5, 4)-(10, 4)
    e_ptr = (Edge*) malloc(sizeof(Edge));
    assert(e_ptr != NULL);
    v1=(Vertex*) malloc(sizeof(Vertex));
    assert(v1 != NULL);
    v2=(Vertex *) malloc(sizeof(Vertex));
    assert(v2 != NULL);
    v1->x=5;
    v1->y=4;
    v2->x=10;
    v2->y=4;
    e_ptr->p1=v1;
    e_ptr->p2=v2;
    if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
    printf("\nshow graph:\n");
    ShowGraph(g1);

    // Insert edge (5,6)-(10,6)
    e_ptr = (Edge*) malloc(sizeof(Edge));
    assert(e_ptr != NULL);
    v1=(Vertex*) malloc(sizeof(Vertex));
    assert(v1 != NULL);
    v2=(Vertex *) malloc(sizeof(Vertex));
    assert(v2 != NULL);
    v1->x=5;
    v1->y=6;
    v2->x=10;
    v2->y=6;
    e_ptr->p1=v1;
    e_ptr->p2=v2;
    if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
    printf("\nshow graph:\n");
    ShowGraph(g1);

    // Insert edge (10,10)-(10,6)
    e_ptr = (Edge*) malloc(sizeof(Edge));
    assert(e_ptr != NULL);
    v1=(Vertex*) malloc(sizeof(Vertex));
    assert(v1 != NULL);
    v2=(Vertex *) malloc(sizeof(Vertex));
    assert(v2 != NULL);
    v1->x=10;
    v1->y=10;
    v2->x=10;
    v2->y=6;
    e_ptr->p1=v1;
    e_ptr->p2=v2;
    if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
    printf("\nshow graph:\n");
    ShowGraph(g1);

    // Insert edge (10, 6)-(10, 4)
    e_ptr = (Edge*) malloc(sizeof(Edge));
    assert(e_ptr != NULL);
    v1=(Vertex*) malloc(sizeof(Vertex));
    assert(v1 != NULL);
    v2=(Vertex *) malloc(sizeof(Vertex));
    assert(v2 != NULL);
    v1->x=10;
    v1->y=6;
    v2->x=10;
    v2->y=4;
    e_ptr->p1=v1;
    e_ptr->p2=v2;
    if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
    printf("\nshow graph:\n");
    ShowGraph(g1);

    // Create second connected component
    // Insert edge (20,4)-(20,10)
    e_ptr = (Edge*) malloc(sizeof(Edge));
    assert(e_ptr != NULL);
    v1=(Vertex*) malloc(sizeof(Vertex));
    assert(v1 != NULL);
    v2=(Vertex *) malloc(sizeof(Vertex));
    assert(v2 != NULL);
    v1->x=20;
    v1->y=4;
    v2->x=20;
    v2->y=10;
    e_ptr->p1=v1;
    e_ptr->p2=v2;
    if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
    printf("\nshow graph:\n");
    ShowGraph(g1);

    // Insert edge (20,10)-(30,10)
    e_ptr = (Edge*) malloc(sizeof(Edge));
    assert(e_ptr != NULL);
    v1=(Vertex*) malloc(sizeof(Vertex));
    assert(v1 != NULL);
    v2=(Vertex *) malloc(sizeof(Vertex));
    assert(v2 != NULL);
    v1->x=20;
    v1->y=10;
    v2->x=30;
    v2->y=10;
    e_ptr->p1=v1;
    e_ptr->p2=v2;
    if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
    printf("\nshow graph:\n");
    ShowGraph(g1);

    // Insert edge (25,5)-(30,10)
    e_ptr = (Edge*) malloc(sizeof(Edge));
    assert(e_ptr != NULL);
    v1=(Vertex*) malloc(sizeof(Vertex));
    assert(v1 != NULL);
    v2=(Vertex *) malloc(sizeof(Vertex));
    assert(v2 != NULL);
    v1->x=25;
    v1->y=5;
    v2->x=30;
    v2->y=10;
    e_ptr->p1=v1;
    e_ptr->p2=v2;
    if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
    printf("\nshow graph:\n");
    ShowGraph(g1);
    //Display graph g1

    // Find the shortest path between (0,0) and (10,6)
    v1=(Vertex*) malloc(sizeof(Vertex));
    assert(v1 != NULL);
    v2=(Vertex *) malloc(sizeof(Vertex));
    assert(v2 != NULL);
    v1->x=0;
    v1->y=0;
    v2->x=10;
    v2->y=6;
    printf("\nShortest:\n");
    ShortestPath(g1, v1, v2);
    free(v1);
    free(v2);

 //    Delete edge (0,0)-(5, 6)
    e_ptr = (Edge*) malloc(sizeof(Edge));
    assert(e_ptr != NULL);
    v1=(Vertex*) malloc(sizeof(Vertex));
    assert(v1 != NULL);
    v2=(Vertex *) malloc(sizeof(Vertex));
    assert(v2 != NULL);
    v1->x=0;
    v1->y=0;
    v2->x=5;
    v2->y=6;
    e_ptr->p1=v1;
    e_ptr->p2=v2;
    DeleteEdge(g1, e_ptr);
    free(e_ptr);
    free(v1);
    free(v2);
    printf("\nshow graph:\n");
    // Display graph g1
    ShowGraph(g1);
////
    // Find the shortest path between (0,0) and (10,6)
    v1=(Vertex*) malloc(sizeof(Vertex));
    assert(v1 != NULL);
    v2=(Vertex *) malloc(sizeof(Vertex));
    assert(v2 != NULL);
    v1->x=0;
    v1->y=0;
    v2->x=10;
    v2->y=6;
    printf("\nShortest:\n");
    ShortestPath(g1, v1, v2);
    free(v1);
    free(v2);

    // Find the shortest path between (0,0) and (25,5)
    v1=(Vertex*) malloc(sizeof(Vertex));
    assert(v1 != NULL);
    v2=(Vertex *) malloc(sizeof(Vertex));
    assert(v2 != NULL);
    v1->x=0;
    v1->y=0;
    v2->x=25;
    v2->y=5;
    printf("\nShortest:\n");
    ShortestPath(g1, v1, v2);
    free(v1);
    free(v2);

//  Find reachable vertices of (0,0)
    printf("\nreachable vertices:\n");
    v1=(Vertex*) malloc(sizeof(Vertex));
    assert(v1 != NULL);
    v1->x=0;
    v1->y=0;
    ReachableVertices(g1, v1);
    free(v1);
//
    // Find reachable vertices of (20,4)
    printf("\nreachable vertices:\n");
    v1=(Vertex*) malloc(sizeof(Vertex));
    assert(v1 != NULL);
    v1->x=20;
    v1->y=4;
    ReachableVertices(g1, v1);
    free(v1);
    // Free graph g1
    FreeGraph(g1);

    return 0;
}
