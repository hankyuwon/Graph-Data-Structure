#include <stdio.h>
#include <stdlib.h>
#define maxvertex 10
#define Size 100

// Node 구조체
typedef struct Node{
    int vertex;
    struct Node* link;
}Node;

//Graph 구조체
typedef struct Graph{
    int* visited; // << 탐색
    int numVertices;
    struct Node** adjlist;
    int VertexNumber[10]; // adj[i]에서 전체 다 출력하지말고 edge가 존재하는, 출력할게 있는것만 추려서 출력하게
    //Vertex가 VertexNumber[]에 들어감.
    //print해줄때 adj[VertexNumber[]] 이렇게
}Graph;

//기본 함수들
int initializeGraph(Graph** graph);
Node* createNode(int v);
void insertEdge(Graph* graph, int s, int d);
void printGraph(Graph* graph);
int freeGraph(Graph* graph);
void InsertVertex(Graph* graph, int v);
void addEdge(Graph* graph, int s, int d);

//Queue 함수들
typedef struct queue{
    int items[Size];
    int front;
    int rear;
}queue;

queue* createQueue();
void enqueue(queue* q, int v);
int dequeue(queue* q);
void display(queue* q);
int isEmpty(queue* q);
void printQueue(queue* q);
void bfs(Graph* graph, int start);


int main()
{
   char command;
   int v,s,d;
   int start;
   Graph* graph=NULL;
   do{
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

		switch(command) {
		case 'z': case 'Z':
        initializeGraph(&graph);
		break;
		case 'v': case 'V':
        printf("Input Vertex ");
        scanf("%d", &v);
        InsertVertex(graph,v);
		break;
		case 'e': case 'E':
        printf("Insert Edge .. Vertex  = ");
        scanf("%d %d", &s, &d);
        printf("\n");
        addEdge(graph,s,d);
		break;
		case 'd': case 'D':
		break;
		case 'b': case 'B':
        printf("input start vertex number = ");
        scanf("%d",&start);
        bfs(graph,start);
		break;
		case 'p': case 'P':
        printGraph(graph);
		break;
		case 'q': case 'Q':
		break;
		default:
		printf("\n       >>>>>   Concentration!!   <<<<<     \n");
		break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initializeGraph(Graph** graph)
{
    if(*graph != NULL) // Graph가 이미 메모리 할당 되어있으면
    {
        freeGraph(*graph); // Graph 메모리 해제
    }

    *graph=(Graph*)malloc(sizeof(Graph));
    (*graph)->numVertices=0; // Graph 내에 있는 Vertex의 수

    (*graph)->adjlist=malloc(maxvertex*sizeof(Node*)); // Graph 내의 adjlist에 maxvertex의 갯수 * sizeof(Node*)의 메모리 할당

    (*graph)->visited=malloc(maxvertex*sizeof(int)); // queue 내에 있는 visited도 메모리 할당

    for(int i=0;i<maxvertex;i++)
    {
        (*graph)->adjlist[i]=NULL; // Graph 내에 adjlist는 모두 NULL을 가리키게 초기화
        (*graph)->visited[i]=0; // visited 0으로 초기화
    }


    return 1;
}

int freeGraph(Graph* graph) // 그래프 메모리 해제 함수
{

}

void InsertVertex(Graph* graph,int v)
{
    if(v>maxvertex)
    {
        printf(" Vertex number is too high!\n");
        return;
    }

    if(graph->numVertices>=maxvertex)
    {
        printf("Too many Vertex!\n");
        return;
    }

    graph->VertexNumber[graph->numVertices]=v;
    graph->numVertices++;
}

Node* createNode(int v)
{
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex =v;
    newNode->link=NULL;
    return newNode;
}

void insertEdge(Graph* graph, int s, int d)
{
    Node* newNode = createNode(d);
    newNode->link=graph->adjlist[s];
    graph->adjlist[s]=newNode;

    newNode=createNode(s);
    newNode->link=graph->adjlist[d];
    graph->adjlist[d]=newNode;
}

void printGraph(Graph* graph)
{
    for(int a=0;a<graph->numVertices;a++)
    {
        Node* temp=graph->adjlist[graph->VertexNumber[a]];
        printf("\n Vertex %d\n: ", graph->VertexNumber[a]);
        while(temp){
            printf("%d ", temp->vertex);
            if(temp->link!=NULL)
            {
                printf("-> ");
            }
            temp=temp->link;
        }
        printf("\n");
    }
}

void addEdge(Graph* graph, int s, int d)
{
    if(s==d)
    {
        printf("Don't input same Vertex\n");
        return;
    }
    

    Node* newNode=createNode(d);
    newNode->link=graph->adjlist[s];
    graph->adjlist[s]=newNode;

    newNode=createNode(s);
    newNode->link=graph->adjlist[d];
    graph->adjlist[d]=newNode;
}

//여기서부터 BFS에 관련된 Queue함수

void bfs(Graph* graph, int startVertex)
{
    queue* q = createQueue();

    graph->visited[startVertex]=1;
    enqueue(q,startVertex);

    while(!isEmpty(q))
    {
        printQueue(q);
        int currentVertex=dequeue(q);
        printf("Visited %d\n", currentVertex);

        Node* temp=graph->adjlist[currentVertex];

        while(temp)
        {
            int adjVertex = temp->vertex;

            if(graph->visited[adjVertex]==0)
            {
                graph->visited[adjVertex]=1;
                enqueue(q,adjVertex);
            }
            temp=temp->link;
        }
    }
}

queue* createQueue(){
    queue* q=malloc(sizeof(queue));
    q->front=-1;
    q->rear=-1;
    return q;
}

int isEmpty(queue *q)
{
    if(q->rear==-1)
    return 1;
    else
    return 0;
}

void enqueue(queue* q, int value){
    if(q->rear==Size-1)
    printf("\nQueue is Full");
    else{
        if(q->front==-1)
        q->front=0;
        q->rear++;
        q->items[q->rear]=value;
    }
}

int dequeue(queue* q){
    int item;
    if(isEmpty(q)){
        printf("Queue is empty");
        item = -1;
    }else{
        item=q->items[q->front];
        q->front++;
        if(q->front>q->rear){
            printf("Resetting queue ");
            q->front = q->rear= -1;
        }
    }
    return item;
}

void printQueue(queue *q){
    int i=q->front;

    if(isEmpty(q)){
        printf("Queue is empty");
    }else{
        printf("\nQueue contains \n");
        for(i=q->front;i<q->rear+1;i++){
            printf("%d", q->items[i]);
        }
    }
}