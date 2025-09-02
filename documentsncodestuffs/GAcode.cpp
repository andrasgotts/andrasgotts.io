#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <Math.h>
#include <random>
#include <ctime>
#include <iomanip>
#include <queue>

struct pos {
    float x = 0;
    float y = 0;
};

int main(int argc, char* argv[])
{
    std::fstream myfile("Lab8TerrainFile1.txt");

    std::vector<int> numbers;
    std::string numberz;
    char a;
    while (myfile >> a)
    {
        numberz += a;
    }

    //std::cout << std::endl;

    //std::cout << numberz << std::endl;

    for (int i = 0; i < numberz.length() - 1; i++) {
        numbers.push_back(numberz[i]-48);
    }

    for (std::vector<int>::iterator itr = numbers.begin(); itr != numbers.end();) {
        if (*itr < 0) {
            itr = numbers.erase(itr);
        }
        else { 
            ++itr;
        }
        
    }
    
    const int sizeX = numbers.at(0);
    const int sizeY = numbers.at(1);
    std::cout << sizeX << " | " << sizeY << std::endl;
    numbers.erase(numbers.begin(), numbers.begin() + 2);

    //for (auto i : numbers) {
    //    std::cout << i << std::endl;
    //}

    int chromosomes[20][16];

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    double r = 0;
    for (int u = 0; u < 20; u++) {
        for (int i = 0; i < 16; i++) {
            //chromosomes[u][i] = round(distribution(generator));
            r = distribution(generator);
            if (r <= 0.5) {
                chromosomes[u][i] = 0;
            }
            else {
                chromosomes[u][i] = 1;
            }
        }
    }

    int iterator = 0;
    //std::string cc;
    pos start;
    pos end;
    pos wall;
    std::vector<pos> walls;
    

    
    int it = 0;
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            std::cout << numbers.at(it);
            if (numbers.at(it) == 1) {//1 = wall
                wall.y = y;
                wall.x = x;
                walls.push_back(wall);
            }
            else {
                if (numbers.at(it) == 2) {//2 = start
                    start.y = y;
                    start.x = x;
                    std::cout << "Start(x|y): " << start.x << " | " << start.y << std::endl;
                }
                else {
                    if (numbers.at(it) == 3) {//3 = end
                        end.y = y;
                        end.x = x;
                        std::cout << "End(x|y): " << end.x << " | " << end.y << std::endl;
                    }
                }
            }
            it++;
        }
        std::cout << std::endl;
    }
    

    /*
    int ite = 0;
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            std::cout << numbers.at(ite);
            ite++;
        }
        std::cout << std::endl;
    }
    
    for (std::vector<int>::iterator itr = numbers.begin(); itr != numbers.end(); itr++,iterator++) {//0 = open space
        if (numbers.at(iterator) == 1) {//1 = wall
            wall.y = floor((iterator) / sizeX);
            wall.x = (((iterator) % sizeX) * start.y);
            walls.push_back(wall);

        }
        else {
            if (numbers.at(iterator) == 2) {//2 = start
                start.y = floor((iterator) / sizeX);
                start.x = ((iterator % sizeX) * start.y);
                std::cout << "Start(x|y): " << start.x << " | " << start.y << std::endl;
            }
            else {
                if (numbers.at(iterator) == 3) {//3 = end
                    end.y = floor((iterator) / sizeX);
                    end.x = floor((iterator) / sizeY);
                    std::cout << "End(x|y): " << end.x << " | " << end.y << std::endl;
                }
            }
        }
    }
    */

    bool left(false), right(false), up(false), down(false);
    float fitness[20];
    float totalfitness = 0;
    pos population[20];
    int newpopulation[20][16];
    for (int u = 0; u < 20; u++) {
        population[u] = start;
        for (int i = 0; i < 16; i+=2) {
            //std::cout << population[0].x << " | " << population[0].y << std::endl;
            

            //cc = chromosomes[u][i] + chromosomes[u][i+1];
            //std::cout << "cc: " << cc << std::endl;
            std::cout << "chromosomes: " << chromosomes[u][i] << " + " << chromosomes[u][i+1] << std::endl;

            //wall can move in certain direction ?? BOOLS
            for (auto itr : walls) {
                if (itr.x < population[u].x + 1) {
                    right = true;
                }
                else {
                    right = false;
                }
                if (itr.x > population[u].x - 1) {
                    left = true;
                }
                else {
                    left = false;
                }
                if (itr.y < population[u].y - 1) {
                    up = true;
                }
                else {
                    up = false;
                }
                if (itr.y > population[u].y + 1) {
                    down = true;
                }
                else {
                    down = false;
                }
            }

            if (chromosomes[u][i] == 0 && chromosomes[u][i + 1] == 0) {//00 = UP = y - 1
                if (population[u].y > 0 && up == true) {
                    population[u].y -= 1;
                }
            }
            else {
                if (chromosomes[u][i] == 1 && chromosomes[u][i + 1] == 0) {//10 = LEFT = x - 1
                    if (population[u].x > 0 && left == true) {
                        population[u].x -= 1;
                    }
                }
                else {
                    if (chromosomes[u][i] == 0 && chromosomes[u][i + 1] == 1) {//01 = RIGHT = x + 1
                        if (population[u].x < sizeX && right == true) {
                            population[u].x += 1;
                        }
                    }
                    else {
                        if (chromosomes[u][i] == 1 && chromosomes[u][i + 1] == 1) {//11 = DOWN = y + 1
                            if (population[u].y < sizeY && down == true) {
                                population[u].y += 1;
                            }
                        }
                    }
                }
            }
            if (end.x == population[u].x && end.y == population[u].y) {
                i += 16;
                fitness[u] = 1 / (abs(end.x - population[u].x) + abs(end.y - population[u].y) + 1);
            }
            /*
            if (cc[0] == 0) {
                if (cc[1] == 0) {
                    //00 = UP = y - 1
                    if (population[u].y > 0) {
                        population[u].y -= 1;
                    }
                }
                else {
                    //01 = RIGHT = x + 1
                    if (population[u].x < sizeX) {
                        population[u].x += 1;
                    }
                    
                }
            }
            else {
                if (cc[1] == 1) {
                    //11 = DOWN = y + 1
                    if (population[u].y < sizeY) {
                        population[u].y += 1;
                    }
                    
                }
                else {
                    //10 = LEFT = x - 1
                    if (population[u].x > 0) {
                        population[u].x -= 1;
                    }
                    
                }
            }
            */
        }
        std::cout << std::endl;
        std::cout << population[u].x << " | " << population[u].y << std::endl;
        std::cout << std::endl;
       // for (int i = 0; i < 20; i++) {
        //    std::cout << chromosomes[u][i] << " ";
        //}
       
        }
    for (int iter = 0; iter < 20; iter++) {
        totalfitness += fitness[iter];
    }
    for (int iter = 0; iter < 20; iter++) {
        fitness[iter] = (fitness[iter] / totalfitness) * 100;
    }
    srand(time(NULL));
    float ran = rand() % 101;

    for (int io = 0; io < 20; io++) {
        totalfitness = 0;
        ran = rand() % 101;
        for (int iter = 0; iter < 20; iter++) {
            totalfitness += fitness[iter];
            if (totalfitness >= ran && iter > 0) {
                std::swap(chromosomes[io], chromosomes[iter]);
            }
            else {
                if (ran >= totalfitness - fitness[iter] && ran <= totalfitness) {
                    std::swap(chromosomes[io], chromosomes[iter]);
                }
            }

        }
    }
    float COR = 0.7;
    for (int hh = 0; hh < 20; hh += 2) {
        r = distribution(generator);
        if (r <= COR) {
            //crossover
            for (int itr = 0; itr < 8; itr++) {
                std::swap(chromosomes[hh][itr], chromosomes[hh + 1][itr + 8]);
            }
        }
        else {
            //offspring is same
        }
        /*
        for (int ip = 0; ip < 16; ip += 2) {
            r = distribution(generator);
            if (r <= 0.5) {
                chromosomes[hh][ip] = 0;
            }
            else {
                chromosomes[hh][ip] = 1;
            }
        }
        */
    }
    int MutateR = 0.001;
    for (int aa = 0; aa < 20; aa++) {
        for (int hh = 0; hh < 16; hh++) {
            r = distribution(generator);
            if (r <= MutateR) {
                if (chromosomes[aa][hh] == 0) {
                    chromosomes[aa][hh] = 1;
                }
                else {
                    chromosomes[aa][hh] = 0;
                }
            }
        }
    }

    return 0;
}






















/*#include <iostream>
#include <string>
#include <Math.h>
#include <random>
#include <vector>
#include <SDL.h>
#include <SDL_mixer.h>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <queue>

const int n = 60; // horizontal size of the map
const int m = 60; // vertical size size of the map
static int map[n][m];
static int closed_nodes_map[n][m]; // map of closed (tried-out) nodes
static int open_nodes_map[n][m]; // map of open (not-yet-tried) nodes
static int dir_map[n][m]; // map of directions
const int dir = 8; // number of possible directions to go at any position
// if dir==4
//static int dx[dir]={1, 0, -1, 0};
//static int dy[dir]={0, 1, 0, -1};
// if dir==8
static int dx[dir] = { 1, 1, 0, -1, -1, -1, 0, 1 };
static int dy[dir] = { 0, 1, 1, 1, 0, -1, -1, -1 };

class node
{
    // current position
    int xPos;
    int yPos;
    // total distance already travelled to reach the node
    int level;
    // priority=level+remaining distance estimate
    int priority;  // smaller: higher priority

public:
    node(int xp, int yp, int d, int p)
    {
        xPos = xp; yPos = yp; level = d; priority = p;
    }

    int getxPos() const { return xPos; }
    int getyPos() const { return yPos; }
    int getLevel() const { return level; }
    int getPriority() const { return priority; }

    void updatePriority(const int& xDest, const int& yDest)
    {
        priority = level + estimate(xDest, yDest) * 10; //A*
    }

    // give better priority to going strait instead of diagonally
    void nextLevel(const int& i) // i: direction
    {
        level += (dir == 8 ? (i % 2 == 0 ? 10 : 14) : 10);
    }

    // Estimation function for the remaining distance to the goal.
    const int& estimate(const int& xDest, const int& yDest) const
    {
        static int xd, yd, d;
        xd = xDest - xPos;
        yd = yDest - yPos;

        // Euclidian Distance
        d = static_cast<int>(sqrt(xd * xd + yd * yd));

        // Manhattan distance
        //d=abs(xd)+abs(yd);

        // Chebyshev distance
        //d=max(abs(xd), abs(yd));

        return(d);
    }
};

// Determine priority (in the priority queue)
bool operator<(const node& a, const node& b)
{
    return a.getPriority() > b.getPriority();
}

// A-star algorithm.
// The route returned is a string of direction digits.
std::string pathFind(const int& xStart, const int& yStart,
    const int& xFinish, const int& yFinish)
{
    static std::priority_queue<node> pq[2]; // list of open (not-yet-tried) nodes
    static int pqi; // pq index
    static node* n0;
    static node* m0;
    static int i, j, x, y, xdx, ydy;
    static char c;
    pqi = 0;

    // reset the node maps
    for (y = 0; y < m; y++)
    {
        for (x = 0; x < n; x++)
        {
            closed_nodes_map[x][y] = 0;
            open_nodes_map[x][y] = 0;
        }
    }

    // create the start node and push into list of open nodes
    n0 = new node(xStart, yStart, 0, 0);
    n0->updatePriority(xFinish, yFinish);
    pq[pqi].push(*n0);
    open_nodes_map[x][y] = n0->getPriority(); // mark it on the open nodes map

    // A* search
    while (!pq[pqi].empty())
    {
        // get the current node w/ the highest priority
        // from the list of open nodes
        n0 = new node(pq[pqi].top().getxPos(), pq[pqi].top().getyPos(),
            pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

        x = n0->getxPos(); y = n0->getyPos();

        pq[pqi].pop(); // remove the node from the open list
        open_nodes_map[x][y] = 0;
        // mark it on the closed nodes map
        closed_nodes_map[x][y] = 1;

        // quit searching when the goal state is reached
        //if((*n0).estimate(xFinish, yFinish) == 0)
        if (x == xFinish && y == yFinish)
        {
            // generate the path from finish to start
            // by following the directions
            std::string path = "";
            while (!(x == xStart && y == yStart))
            {
                j = dir_map[x][y];
                c = '0' + (j + dir / 2) % dir;
                path = c + path;
                x += dx[j];
                y += dy[j];
            }

            // garbage collection
            delete n0;
            // empty the leftover nodes
            while (!pq[pqi].empty()) pq[pqi].pop();
            return path;
        }

        // generate moves (child nodes) in all possible directions
        for (i = 0; i < dir; i++)
        {
            xdx = x + dx[i]; ydy = y + dy[i];

            if (!(xdx<0 || xdx>n - 1 || ydy<0 || ydy>m - 1 || map[xdx][ydy] == 1
                || closed_nodes_map[xdx][ydy] == 1))
            {
                // generate a child node
                m0 = new node(xdx, ydy, n0->getLevel(),
                    n0->getPriority());
                m0->nextLevel(i);
                m0->updatePriority(xFinish, yFinish);

                // if it is not in the open list then add into that
                if (open_nodes_map[xdx][ydy] == 0)
                {
                    open_nodes_map[xdx][ydy] = m0->getPriority();
                    pq[pqi].push(*m0);
                    // mark its parent node direction
                    dir_map[xdx][ydy] = (i + dir / 2) % dir;
                }
                else if (open_nodes_map[xdx][ydy] > m0->getPriority())
                {
                    // update the priority info
                    open_nodes_map[xdx][ydy] = m0->getPriority();
                    // update the parent direction info
                    dir_map[xdx][ydy] = (i + dir / 2) % dir;

                    // replace the node
                    // by emptying one pq to the other one
                    // except the node to be replaced will be ignored
                    // and the new node will be pushed in instead
                    while (!(pq[pqi].top().getxPos() == xdx &&
                        pq[pqi].top().getyPos() == ydy))
                    {
                        pq[1 - pqi].push(pq[pqi].top());
                        pq[pqi].pop();
                    }
                    pq[pqi].pop(); // remove the wanted node

                    // empty the larger size pq to the smaller one
                    if (pq[pqi].size() > pq[1 - pqi].size()) pqi = 1 - pqi;
                    while (!pq[pqi].empty())
                    {
                        pq[1 - pqi].push(pq[pqi].top());
                        pq[pqi].pop();
                    }
                    pqi = 1 - pqi;
                    pq[pqi].push(*m0); // add the better node instead
                }
                else delete m0; // garbage collection
            }
        }
        delete n0; // garbage collection
    }
    return ""; // no route found
}

//Develop a computer program to implement A* on a maze represented by 2D binary grid terrain map. (The exact format of the terrain required will be explained in class.)

int main(int argc, char* argv[]) {
	srand((unsigned int)time(NULL));//for random numbers
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "initialising shit the bed" << SDL_GetError() << std::endl;
	}
	SDL_Window* window = SDL_CreateWindow("pathfinding", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, SDL_WINDOW_SHOWN);//game window
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);//game renderer
	SDL_Surface* Backgroundbmp = SDL_LoadBMP("MainMenu.bmp");//main menu interface bmp
	SDL_Texture* Backgroundtexture = SDL_CreateTextureFromSurface(renderer, Backgroundbmp);

	if (window == NULL) {
		std::cout << "window pooped the bed" << SDL_GetError() << std::endl;
	}
	if (renderer == NULL) {
		std::cout << "renderer pooped the bed" << SDL_GetError() << std::endl;
	}
	int w(0), h(0);
	SDL_GetWindowSize(window, &w, &h);
	const int FPS = 144;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)) {
		std::cout << "mixer error: " << Mix_GetError() << std::endl;
	}
	Mix_Music* backgroundmusic = Mix_LoadMUS("duaDSN.wav");

	//Mix_PlayMusic(backgroundmusic, -1);

	SDL_Event event;

	bool mainloop(true);//loop bools
	int randsign(0);//moving players, randsign for random number (enemy spawn pos)
	Uint32 tickerbuddy{ 0 }, otherbuddy{ 0 };
    SDL_ShowCursor(0);
    /*
    srand(time(NULL));

    // create empty map
    for (int y = 0; y < m; y++)
    {
        for (int x = 0; x < n; x++) map[x][y] = 0;
    }

    // fillout the map matrix with a '+' pattern
    for (int x = n / 8; x < n * 7 / 8; x++)
    {
        map[x][m / 2] = 1;
    }
    for (int y = m / 8; y < m * 7 / 8; y++)
    {
        map[n / 2][y] = 1;
    }

    // randomly select start and finish locations
    int xA, yA, xB, yB;
    switch (rand() % 8)
    {
    case 0: xA = 0; yA = 0; xB = n - 1; yB = m - 1; break;
    case 1: xA = 0; yA = m - 1; xB = n - 1; yB = 0; break;
    case 2: xA = n / 2 - 1; yA = m / 2 - 1; xB = n / 2 + 1; yB = m / 2 + 1; break;
    case 3: xA = n / 2 - 1; yA = m / 2 + 1; xB = n / 2 + 1; yB = m / 2 - 1; break;
    case 4: xA = n / 2 - 1; yA = 0; xB = n / 2 + 1; yB = m - 1; break;
    case 5: xA = n / 2 + 1; yA = m - 1; xB = n / 2 - 1; yB = 0; break;
    case 6: xA = 0; yA = m / 2 - 1; xB = n - 1; yB = m / 2 + 1; break;
    case 7: xA = n - 1; yA = m / 2 + 1; xB = 0; yB = m / 2 - 1; break;
    }

    std::cout << "Map Size (X,Y): " << n << "," << m << std::endl;
    std::cout << "Start: " << xA << "," << yA << std::endl;
    std::cout << "Finish: " << xB << "," << yB << std::endl;
    // get the route
    clock_t start = clock();
    std::string route = pathFind(xA, yA, xB, yB);
    if (route == "") std::cout << "An empty route generated!" << std::endl;
    clock_t end = clock();
    double time_elapsed = double(end - start);
    std::cout << "Time to calculate the route (ms): " << time_elapsed << std::endl;
    std::cout << "Route:" << std::endl;
    std::cout << route << std::endl << std::endl;

    // follow the route on the map and display it 
    if (route.length() > 0)
    {
        int j; char c;
        int x = xA;
        int y = yA;
        map[x][y] = 2;
        for (int i = 0; i < route.length(); i++)
        {
            c = route.at(i);
            j = atoi(&c);
            x = x + dx[j];
            y = y + dy[j];
            map[x][y] = 3;
        }
        map[x][y] = 4;

        // display the map with the route
        for (int y = 0; y < m; y++)
        {
            for (int x = 0; x < n; x++)
                if (map[x][y] == 0)
                    std::cout << ".";
                else if (map[x][y] == 1)
                    std::cout << "O"; //obstacle
                else if (map[x][y] == 2)
                    std::cout << "S"; //start
                else if (map[x][y] == 3)
                    std::cout << "R"; //route
                else if (map[x][y] == 4)
                    std::cout << "F"; //finish
            std::cout << std::endl;
        }
    }
    getchar(); // wait for a (Enter) keypress
    */
/*
	while (mainloop == true) {
		SDL_RenderClear(renderer);
		frameStart = SDL_GetTicks();


		

		hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh



		SDL_RenderPresent(renderer);
		SDL_UpdateWindowSurface(window);
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
		mainloop = false;
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
*/