#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int *stack;
int stack_size;

void stack_push(int n){
    stack[stack_size++] = n;
}

int stack_pop(){
    return stack[--stack_size];
}


// char  out_[666];
int size;
int max_point;
int **data;

bool isPass(){
    bool* arr = (bool*)malloc(size * sizeof(bool));
    for(int i=0;i<size;i++) arr[i] = false;
    for(int i=0;i<stack_size;i++){
        for(int j=0;j<size;j++){
            if(data[stack[i]][j])
                arr[j] = true;
        }
    }

    int pass_i;
    for(pass_i=0;pass_i<stack_size;pass_i++)
        if(arr[stack[pass_i]] )
            break;
        else arr[stack[pass_i]] = true;

    free(arr);
    return pass_i == stack_size ? true : false;
}

void find_max(int start_p){
    if(stack_size > max_point && isPass()){
        max_point = stack_size;
    }

    for(int i=start_p;i<size;i++){
        stack_push(i);
        find_max(i+1);
        stack_pop(); 
    }
}

int main(){
    while (1){
        max_point  = 0;
        stack_size = 0;
        
        scanf("%d", &size);
        if(size == -1) break;
        stack = (int*) malloc(size * sizeof(int ));

        data  = (int**)malloc(size * sizeof(int*));
        for(int i=0;i<size;i++)
            data[i] = (int*)malloc(size * sizeof(int));
            
        for(int i=0;i<size;i++)
            for(int j=0;j<size;j++)
                scanf("%d", &data[i][j]);
        
        find_max(0);

        printf("%d\n", max_point);

        for(int i=0;i<size;i++)
            free(data[i]);
        free(data);
    }
    return 0;
}