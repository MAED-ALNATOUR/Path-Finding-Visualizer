#include<SDL2/SDL.h>
#include<iostream>
#include<queue>
#define width 480
#define height 640

using namespace std;

class Graph {

	public:

	SDL_Rect r;

	int node;

	int up;

	int down;

	int left;

	int right;

	int parent;

	bool visited;

void cor(int rX ,int rY ,int n){

	r.x  = rX;

	r.y  = rY;

	r.h  = 40;

	r.w  = 40;

	node =  n;

}

void conn(){

	if(r.x == 0){left = -1;}

	else{left = node-1;}

	if(r.x == 600){right = -1;}

	else{right = node+1;}

	if(r.y == 0){up = -1;}

	else{up = node-16;}

	if(r.y == 440){down = -1;}

	else{down = node+16;}

	visited = false;

}

};

void init(SDL_Renderer* &renderer,Graph graph_node[]);

void input(SDL_Renderer* &renderer,Graph graph_node[],int& start,int& end);

void breadthFirst(Graph graph_node[],int start,int end,SDL_Renderer* &renderer) {

	SDL_SetRenderDrawColor(renderer,244,211,94,255);

	SDL_RenderFillRect(renderer,&graph_node[end].r);

	SDL_SetRenderDrawColor(renderer,0,125,125,255);

	SDL_RenderPresent(renderer);

	SDL_Delay(50);

	queue<int> queue;

	queue.push(start);

while(!queue.empty()){

	int current = queue.front();

	SDL_RenderFillRect(renderer,&graph_node[current].r);

	SDL_SetRenderDrawColor(renderer,28,28,30,255);

	if(current == end){break;}

	graph_node[current].visited = true;

	queue.pop();

	SDL_RenderPresent(renderer);

	SDL_Delay(100);

	if(graph_node[current].left != -1 && graph_node[graph_node[current].left].visited != true){

	queue.push(graph_node[current].left);

	graph_node[graph_node[current].left].visited = true;

	graph_node[graph_node[current].left].parent = current;

	}

	if(graph_node[current].up != -1 && graph_node[graph_node[current].up].visited != true){

	queue.push(graph_node[current].up);

	graph_node[graph_node[current].up].visited = true;

	graph_node[graph_node[current].up].parent = current;

	}

	if(graph_node[current].down != -1 && graph_node[graph_node[current].down].visited != true){

	queue.push(graph_node[current].down);

	graph_node[graph_node[current].down].visited = true;

	graph_node[graph_node[current].down].parent = current;

	}

	if(graph_node[current].right != -1 && graph_node[graph_node[current].right].visited != true){

	queue.push(graph_node[current].right);

	graph_node[graph_node[current].right].visited = true;

	graph_node[graph_node[current].right].parent = current;

	}

}


	SDL_SetRenderDrawColor(renderer,244,211,94,255);

	SDL_RenderFillRect(renderer,&graph_node[end].r);

	SDL_SetRenderDrawColor(renderer,50,205,50,255);

	int kk = end;

	SDL_Delay(100);

while(graph_node[kk].parent != start){

	kk = graph_node[kk].parent;

	SDL_RenderFillRect(renderer,&graph_node[kk].r);

	SDL_RenderPresent(renderer);

	SDL_Delay(50);

	}

}

int main(){

	SDL_Window* window = nullptr;

	SDL_Renderer* renderer = nullptr;

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_CreateWindowAndRenderer(height,width,0,&window,&renderer);

	SDL_SetRenderDrawColor(renderer,0,0,0,255);

	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer,255,255,255,255);

	Graph graph_node[192];

	int start = 0;

	int end  = 190;

	init(renderer,graph_node);

	input(renderer,graph_node,start,end);

	return 0;

}

void init(SDL_Renderer* &renderer,Graph graph_node[]){

	int y1 = 0;
	int x1 = 0;

	for(int i=0;i<192;i++){

	graph_node[i].cor(x1,y1,i);

	graph_node[i].conn();

	if(x1 == 600){y1+=40;x1=0;continue;}

	x1+=40;

	}

	SDL_SetRenderDrawColor(renderer,255,255,255,255);

	for(int i = 0;i < 192;i++)
	{

	SDL_RenderDrawRect(renderer,&graph_node[i].r);

	}

	SDL_RenderPresent(renderer);

}



void input(SDL_Renderer* &renderer,Graph graph_node[],int& start,int& end){

	SDL_Event e;

	int o = 0;

	bool run = true;

 while(run){

	while(SDL_PollEvent(&e) != 0){

	int x;

	int y;

	int z;

	SDL_GetMouseState(&x,&y);

	x/=40;

	y/= 40;

	y*= 16;

	z=x+y;

  if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT && o==0) {

	start = z;

	o++;

	SDL_SetRenderDrawColor(renderer,0,125,125,255);

	SDL_RenderFillRect(renderer,&graph_node[z].r);

	SDL_RenderPresent(renderer);

	SDL_Delay(50);

  }

  if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_RIGHT && o==1) {

	if(start != z){end = z;}

	o++;

	SDL_SetRenderDrawColor(renderer,244,211,94,255);

	SDL_RenderFillRect(renderer,&graph_node[z].r);

	SDL_RenderPresent(renderer);

	SDL_Delay(50);

   }

  if(o == 2){

	breadthFirst(graph_node,start,end,renderer);

	o++;

	}

  if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r){

	o = 0;

	SDL_SetRenderDrawColor(renderer,0,0,0,0);

	for(int i = 0;i<192;i++){

	SDL_RenderFillRect(renderer,&graph_node[i].r);

				}

	SDL_RenderPresent(renderer);

	SDL_Delay(1000);

	init(renderer,graph_node);
    }

  if(e.type == SDL_QUIT){
	run = false;
	SDL_Quit();
	exit(0);

    }

    }

    }



}


