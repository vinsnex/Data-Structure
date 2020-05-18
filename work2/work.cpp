#include<stdio.h>
#include<stdlib.h>

struct Point{
    int x, y;
};


struct Point_state{
    Point point;
    int state;
};

Point size;
char **map;
int move_x[] = {-1,  0,  1,  0};
int move_y[] = { 0, -1,  0,  1};
Point_state *stack;
int stack_size;

void stack_push(Point_state _p){
    stack[stack_size++] = _p;
}

Point_state stack_pop(){
    return stack[--stack_size];
}

Point_state *stack_get(int n = -1){
    return n == -1 ? &stack[stack_size - 1] : &stack[n];
}

void printMap(){
    for(int i=0;i<size.y;i++){
        for(int j=0;j<size.x;j++){
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(){
    while (1){
        int out = 0;
        Point_state buff;
        Point  start, end, move, Point_buff;

        scanf("%d%d", &size.y, &size.x);
        if(size.x == 0 || size.y ==0) break;
        map = (char**) malloc(size.y * sizeof(char*));
        for(int i=0;i<size.y;i++)
            map[i] = (char*)malloc(size.x * sizeof(char));
        scanf("%c", &map[0][0]);
        for(int i=0;i<size.y;i++)
            for(int j=0;j<size.x;j++)
                scanf("%c ", &map[i][j]);
        scanf("%d%d", &start.y, &start.x);
        scanf("%d%d",& end.y, &end.x);
        map[start.y][start.x] = 'S';
        map[end.y]  [end.x]   = 'D';

        stack_size = 0;
        stack = (Point_state*)malloc(size.x*size.y*sizeof(Point_state));

        buff.point = start;
        buff.state = 0;
        stack_push(buff);

        while (stack_size != 0){
            Point_state* _bk = stack_get();
            if(_bk->state == 4){
                Point_buff = stack_pop().point;
                map[Point_buff.y][Point_buff.x] = '0';
            }else
            while(_bk->state < 4){
                // printMap();
                move = _bk->point;
                move.x += move_x[_bk->state];
                move.y += move_y[_bk->state];
                _bk->state++;
                if(map[move.y][move.x] == '0'){
                    map[move.y][move.x] = '*';
                    buff.point = move;
                    buff.state = 0;
                    stack_push(buff);
                    break;
                }else if(map[move.y][move.x] == 'D'){
                    // printMap();
                    out++;
                    Point_buff = stack_pop().point;
                    map[Point_buff.y][Point_buff.x] = '0';
                    break;
                }
            }
        }

        printf("%d\n", out);
        for(int i=0;i<size.y;i++)
            free(map[i]);
        free(map);
    }
    return 0;
}