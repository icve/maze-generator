#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef struct cell{
    char t, l;
    int v;
}cell;

//settings
int plainText = 0;

int h = 10, w = 20;
void printRow(char* row, int w);
void printMap(cell map[h][w], int h, int w);
void dfs(cell map[h][w], int x, int y);
int isCompletedCell(cell map[][w], int x, int y);
int shouldVisit(cell map[][w], int x, int y);
int randRange(int limit);

int main(int argc, char *argv[]){

    if(argc == 2){
        plainText = !strcmp(argv[1], "-t");
    }
    // init map
    cell map[h][w];
    for(int i=0; i < h; i++){
        for(int j=0; j < w; j++){
            map[i][j].t = '~';
            map[i][j].l = '|';
            map[i][j].v = 0;
        }
    }
    //set up seed
    srand(time(NULL));

    //choose a coord
    int hs = rand() % h;// h start
    int ws = rand() % w;// w start
    dfs(map, hs, ws);
    printMap(map, h, w);
}
void dfs(cell map[h][w], int x, int y){
    // mark current cell as visited
    map[x][y].v = 1;
    while(!isCompletedCell(map, x, y)){
    // pick a node
    int dir = randRange(4);
        int xn, yn;
        // compute next coordinate
        switch(dir){
            case 0:
                xn = x - 1;
                yn = y;
            break;
            case 1:
                xn = x;
                yn = y + 1;
            break;
            case 2:
                xn = x + 1;
                yn = y;
            break;
            case 3:
                xn = x;
                yn = y - 1;
            break;
        }
        if(shouldVisit(map, xn, yn)){
            // break wall
            if(dir == 0){
                map[x][y].t = ' ';
            }else if(dir == 1){
                map[xn][yn].l = ' ';
            }else if(dir == 2){
                map[xn][yn].t = ' ';
            }else{
                map[x][y].l = ' ';
            }
            dfs(map, xn, yn);
        }

    }

}

/*
 * return 0 if cell should not be visited
 * i.e the cell has already been visited, or
 * the cell is out of range
 */
int shouldVisit(cell map[][w], int x, int y){
    if(x < 0 || x >= h ||  y < 0 || y >= w || map[x][y].v == 1){
        return 0;
    }
    return 1;

}

/* return 1 if all the surrounding cells are visited
 * 0 otherwise
 */
int isCompletedCell(cell map[][w], int x, int y){
    if(shouldVisit(map, x - 1, y) || shouldVisit(map, x, y + 1) || shouldVisit(map, x - 1, y) || shouldVisit(map, x, y - 1)){
        return 0;
    }
    return 1;
}

void printMap(cell map[h][w], int h, int w){
    int rw = w*2;
    char up[rw];
    char mid[rw];
    for(int i=0; i < h; i++){
        for(int j=0; j< w; j++){
            up[j*2] = '+';
            up[j*2+1] = map[i][j].t;
            mid[j*2] = map[i][j].l;
            mid[j*2+1] = ' ';
        }
        printRow(up, rw);
        printRow(mid, rw);
    }
    for(int i = 0; i < w; i++){
        printf("+~");
    }
    printf("|");
    printf("\n");
}

void printRow(char row[], int w){
   for(int i = 0; i < w; i++){
       if(plainText == 0 && row[i] == ' '){
           printf("\x1B[107m \x1B[49m");
       }
       else{
        printf("%c", row[i]);
        }
   }
   printf("|\n");
}

/* return a random number < limit
* note that the random numbers generated is not a
* perfectly uniform distribution, however it is consider
* good enough for this application
*/
int randRange(int limit){
    return rand() % limit;
}
