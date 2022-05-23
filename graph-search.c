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
    int VertexNumber[10]; // adj[i]에서 전체 다 출력하지말고 edge가 존재하는, 출력할게 있는것만 추려서 출력하게
    //Vertex가 VertexNumber[]에 들어감.
    //print해줄때 adj[VertexNumber[]] 이렇게
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