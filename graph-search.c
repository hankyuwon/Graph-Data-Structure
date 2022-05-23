#include <stdio.h>
#include <stdlib.h>
#define maxvertex 10

typedef struct Node{
    int vertex;
    struct Node* link;
}Node;

typedef struct Graph{
    int numVertices;
    struct Node** adjlist;
}Graph;

int initializeGraph(Graph** graph);
Node* createNode(int v);
void insertEdge(Graph* graph, int s, int d);
void printGraph(Graph* graph);
int freeGraph(Graph* graph);
void InsertVertex(Graph* graph, int v);
void addEdge(Graph* graph, int s, int d);

int main()
{
   char command;
   int v,s,d;
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
        printf("add Edge 두 Vertex 입력 = ");
        scanf("%d %d", &s, &d);
        printf("\n");
        addEdge(graph,s,d);
		break;
		case 'd': case 'D':
		break;
		case 'b': case 'B':
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

    for(int i=0;i<maxvertex;i++)
    {
        (*graph)->adjlist[i]=NULL; // Graph 내에 adjlist는 모두 NULL을 가리키게 초기화
    }

    return 1;
}

int freeGraph(Graph* graph) // 그래프 메모리 해제 함수
{

}

void InsertVertex(Graph* graph,int v)
{
    if(graph->numVertices>=maxvertex)
    {
        printf("추가할수있는 Vertex의 개수를 넘었다");
        return;
    }

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
    for(int v=0;v<graph->numVertices;v++)
    {
        Node* temp=graph->adjlist[v];
        printf("\n Vertex %d\n: ",v);
        while(temp){
            printf("%d -> ", temp->vertex);
            temp=temp->link;
        }
        printf("\n");
    }
}

void addEdge(Graph* graph, int s, int d)
{
    Node* newNode=createNode(d);
    newNode->link=graph->adjlist[s];
    graph->adjlist[s]=newNode;

    newNode=createNode(s);
    newNode->link=graph->adjlist[d];
    graph->adjlist[d]=newNode;
}