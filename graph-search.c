// 무방향 그래프, 다중간선 없음, 자기간선 없음, 동일한 넘버를 갖는 Vertex 존재하지 않음
// 5.26 00:10 free함수 완료 FINISH!!!

#include <stdio.h>
#include <stdlib.h>
#define maxvertex 10
#define Size 100

// Node 구조체
typedef struct Node
{
    int vertex;
    struct Node *link;
} Node;

// Graph 구조체
typedef struct Graph
{
    int *visited; // << 탐색
    int numVertices;
    struct Node **adjlist;
    int VertexNumber[10]; // adj[i]에서 전체 다 출력하지말고 edge가 존재하는, 출력할게 있는것만 추려서 출력하게
    // Vertex가 VertexNumber[]에 들어감.
    // print해줄때 adj[VertexNumber[]] 이렇게
} Graph;

//기본 함수들
int initializeGraph(Graph **graph);
Node *createNode(int v);
void insertEdge(Graph *graph, int s, int d);
void printGraph(Graph *graph);
int freeGraph(Graph *graph);
void InsertVertex(Graph *graph, int v);
void addEdge(Graph *graph, int s, int d);

// Queue 함수들
typedef struct queue
{
    int items[Size];
    int front;
    int rear;
} queue;

queue *createQueue();
void enqueue(queue *q, int v);
int dequeue(queue *q);
void display(queue *q);
int isEmpty(queue *q);
void printQueue(queue *q);

// bfs 함수
void bfs(Graph *graph, int start);

// dfs 함수
void DFS(Graph *graph, int vertex);
void initvisited(Graph *graph);

int main()
{
    char command;
    int v, s, d;
    int start, start2;
    Graph *graph = NULL;

    printf("[hankyuwon][2019037002]\n");
    
    do
    {
        printf("----------------------------------------------------------------\n");
        printf("                       Graph Searches                           \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Graph     = z                                       \n");
        printf(" Insert Vertex        = v           Insert Edge           = e   \n");
        printf(" Depth First Search   = d           Breath First Search   = b   \n");
        printf(" Print Graph          = p           Quit                  = q   \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command)
        {
        case 'z':
        case 'Z':
            initializeGraph(&graph);
            break;
        case 'v':
        case 'V':
            printf("Input Vertex ");
            scanf("%d", &v);
            InsertVertex(graph, v);
            break;
        case 'e':
        case 'E':
            printf(" Edge of Two Vertex  = ");
            scanf("%d %d", &s, &d);
            printf("\n");
            addEdge(graph, s, d);
            break;
        case 'd':
        case 'D':
            printf("input start vertex number = ");
            scanf("%d", &start2);
            DFS(graph, start2);
            initvisited(graph);
            break;
        case 'b':
        case 'B':
            printf("input start vertex number = ");
            scanf("%d", &start);
            bfs(graph, start);
            initvisited(graph);
            break;
        case 'p':
        case 'P':
            printGraph(graph);
            break;
        case 'q':
        case 'Q':
            freeGraph(graph);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

int initializeGraph(Graph **graph)
{
    if (*graph != NULL) // Graph가 이미 메모리 할당 되어있으면
    {
        freeGraph(*graph); // Graph 메모리 해제
    }

    *graph = (Graph *)malloc(sizeof(Graph));
    (*graph)->numVertices = 0; // numVertices 는 Graph 내에 있는 Vertex의 수 -1 이라고 생각하면 됨, 0으로 초기화

    (*graph)->adjlist = malloc(maxvertex * sizeof(Node *)); // Graph 내의 adjlist에 maxvertex의 갯수 * sizeof(Node*)의 메모리 할당

    (*graph)->visited = malloc(maxvertex * sizeof(int)); // queue 내에 있는 visited도 메모리 할당

    for (int i = 0; i < maxvertex; i++)
    {
        (*graph)->adjlist[i] = NULL; // Graph 내에 adjlist는 모두 NULL을 가리키게 초기화
        (*graph)->visited[i] = 0;    // visited 0으로 초기화
    }

    return 1;
}

int freeGraph(Graph *graph) // 그래프 메모리 해제 함수
{
    // adjlist 가서 연결된거 다 해제
    // visited 해제
    // graph자체 해제

    Node *f;
    Node *temp;
    for (int i = 0; i < maxvertex; i++)
    {
        f = graph->adjlist[i];
        while (f != NULL)
        {
            temp = f;
            f = f->link;
            free(temp);
        }
    }

    free(graph->adjlist);

    free(graph->visited);

    free(graph);
}

void InsertVertex(Graph *graph, int v)
{
    if (v < 0 || v >= 10) // Vertex 번호는 0~9 만 들어오게
    {
        printf(" Confirm Vertex number \n");
        return;
    }

    if (graph->numVertices >= maxvertex) // Vertex 는 최대 10개까지 들어올 수 있다.
    {
        printf("Too many Vertex!\n");
        return;
    }

    int temp = 0;
    while (temp < maxvertex) // 동일한 숫자를 갖는 Vertex를 갖지 못하게
    {
        if (graph->VertexNumber[temp] == v) // Vertex의 숫자를 저장해놓은 VertexNumber배열을 활용
        {
            printf("Already Exists!\n"); // 존재하면 just return
            return;
        }
        temp++;
    }

    graph->VertexNumber[graph->numVertices] = v; // graph -> VertexNumber 배열에 현재 담긴 Vertex number를 저장,
    //이는 추후 Graph를 print 해줄 때 Graph안에 있는 Vertex를 불러오기 위함
    graph->numVertices++;
}

Node *createNode(int v)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->link = NULL;
    return newNode;
}

void printGraph(Graph *graph)
{
    for (int a = 0; a < graph->numVertices; a++)
    {
        Node *temp = graph->adjlist[graph->VertexNumber[a]];
        printf("\n Vertex %d\n: ", graph->VertexNumber[a]);
        while (temp)
        {
            printf("%d ", temp->vertex);
            if (temp->link != NULL)
            {
                printf("-> ");
            }
            temp = temp->link;
        }
        printf("\n");
    }
}

void addEdge(Graph *graph, int s, int d)
{
    int cs = 0;
    int cd = 0;
    int temp = 0;

    while (temp < maxvertex) // addEdge함수에 들어온 s 와 d Vertex가 존재하는지 검사. 존재하지 않으면 just return
    {
        if (graph->VertexNumber[temp] == s)
            cs++;
        if (graph->VertexNumber[temp] == d)
            cd++;

        temp++;
    }

    if (cs == 0 && cd == 0) // cs는 s가 존재하면 1, 존재하지 않으면 0. cd도 동일하다. 검사를 통하여 어떤 Vertex가 없는지 print해준다.
    {
        printf(" No exists Vertex %d , %d\n", s, d);
        return;
    }

    if (cs == 0)
    {
        printf(" No exist Vertex %d\n", s);
        return;
    }

    if (cd == 0)
    {
        printf(" No exist Vertex %d\n", d);
        return;
    }

    if (s == d) // 동일한 Vertex가 들어오면 just return
    {
        printf("Don't input same Vertex\n");
        return;
    }

    // 이미 존재하는 Edge인지 확인
    Node *jump = graph->adjlist[d]; // adjlist[d]로 가서 링크를 계속 타고타고가면서 Vertex가 s인 노드가 있는지 확인한다
    while (jump)
    {
        if (jump->vertex == s) // Vertex가 s인 node가 있다는 건 이미 edge가 존재한다는 의미이므로 just return
        {
            printf("Already Exist Edge \n");
            return;
        }
        jump = jump->link;
    }
    // adjlist[s]에 d를 확인하지 않는 이유는 어차피 무방향 이므로 하나만 확인해도 된다.

    // adjlist[] 에 d Node를 만든 후, 원래 있던 노드는 d의 link로 걸어주고 adjlist[s]=d 로 만든다.
    // s도 동일하게 해준다.
<<<<<<< HEAD
    Node* newNode = createNode(d);
    Node* prev;
    Node* temperd = graph->adjlist[s];
    while(1){
        if(graph->adjlist[s]==NULL)
        {
            graph->adjlist[s]=newNode;
            break;
        }
        if(temperd==NULL)
        {
            prev->link=newNode;
            break;
        }
        if(temperd->vertex>d)
        {
            if(temperd==graph->adjlist[s])
            {
                graph->adjlist[s]=newNode;
                newNode->link=temperd;
            }else{
            prev->link=newNode;
            newNode->link=temperd;
            }
            break;
        }
        prev=temperd;
        temperd=temperd->link;
    }
=======
    Node *newNode = createNode(d);
    newNode->link = graph->adjlist[s];
    graph->adjlist[s] = newNode;

>>>>>>> 761d1456aa164f3e08f651dffb9bf496d8b5e503
    newNode = createNode(s);
    Node* tempers = graph-> adjlist[d];
    prev=tempers;
    while(1){
        if(graph->adjlist[d]==NULL)
        {
            graph->adjlist[d]=newNode;
            break;
        }
        if(tempers==NULL)
        {
            prev->link=newNode;
            break;
        }
        if(tempers->vertex>s)
        {
            if(tempers==graph->adjlist[d])
            {
                graph->adjlist[d]=newNode;
                newNode->link=tempers;
            }else{
            prev->link=newNode;
            newNode->link=tempers;
            }
            break;
        }
        prev=tempers;
        tempers=tempers->link;
    }
    return;
}

//여기서부터 BFS에 관련된 Queue함수

void bfs(Graph *graph, int startVertex)
{
    // graph에 있는 Vertex 중 startVertex가 존재하는지 먼저 검사
    int tempp = 0;
    int c = 0;
    while (tempp < maxvertex)
    {
        if (graph->VertexNumber[tempp] == startVertex)
            c++;
        tempp++;
    }

    if (c == 0) // 존재하지 않으면 just return
    {
        printf(" No exist %d \n", startVertex);
        return;
    }

    queue *q = createQueue();

    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);

    while (!isEmpty(q))
    {
        int currentVertex = dequeue(q);
        printf(" %3d ", currentVertex);

        Node *temp = graph->adjlist[currentVertex];

        while (temp)
        {
            int adjVertex = temp->vertex;

            if (graph->visited[adjVertex] == 0)
            {
                graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex);
            }
            temp = temp->link;
        }
    }
    printf("\n");

    free(q); // bfs가 끝나면 그냥 바로 free memory. bfs함수 내에 createQueue를 넣었으므로 free도 같이 넣어줬음

}

queue *createQueue()
{
    queue *q = malloc(sizeof(queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

int isEmpty(queue *q)
{
    if (q->rear == -1)
        return 1;
    else
        return 0;
}

void enqueue(queue *q, int value)
{
    if (q->rear == Size - 1)
        printf("\nQueue is Full");
    else
    {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(queue *q)
{
    int item;
    if (isEmpty(q))
    {
        printf("Queue is empty");
        item = -1;
    }
    else
    {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear)
        {
            q->front = q->rear = -1;
        }
    }
    return item;
}

void printQueue(queue *q)
{
    int i = q->front;

    if (isEmpty(q))
    {
        printf("Queue is empty");
    }
    else
    {
        for (i = q->front; i < q->rear + 1; i++)
        {
            printf("%d", q->items[i]);
        }
    }
}

// DFS algo

void DFS(Graph *graph, int vertex)
{ // graph에 있는 Vertex 중 DFS함수에 들어온 Vertex가 존재하는지 먼저 검사
    int tempp = 0;
    int c = 0;
    while (tempp < maxvertex)
    {
        if (graph->VertexNumber[tempp] == vertex)
            c++;
        tempp++;
    }

    if (c == 0) // 존재하지 않으면 just return
    {
        printf(" No exist %d \n", vertex);
        return;
    }

    Node *adjL = graph->adjlist[vertex];
    Node *temp = adjL;

    graph->visited[vertex] = 1;
    printf(" %3d ", vertex);

    while (temp != NULL)
    {
        int connectedVertex = temp->vertex;

        if (graph->visited[connectedVertex] == 0)
        {
            DFS(graph, connectedVertex);
        }
        temp = temp->link;
    }
}

void initvisited(Graph *graph)
{
    printf("\n");
    for (int i = 0; i < maxvertex; i++)
    {
        graph->visited[i] = 0; // visited 0으로 초기화
    }
}