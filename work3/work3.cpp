#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct tree{
    int value;
    bool valid;
    tree *left, *right;
};

char out_str[100];
bool wrong = false;

bool get_data(char *str, int *value, char *seat){
    int seat_size = 0;
    *value = 0;
    *(seat) = 0;
    while(*(str++) != '(');
    while(*str != ','){
        if(*str == ')') 
            return false;
        // *value*=10;
        // *value+=(*str)-'0';
        *value=*value * 10 + ((*str)-'0');
        str++;
    }
    str++;
    while(*str != ')'){
        seat[seat_size++] = *str;
        str++;
    }
    seat[seat_size] = 0;
    str++;
    return true;
}

void tree_clear(tree *t){
    if(t->left){
        tree_clear(t->left);
        free(t->left);
    }

    if(t->right){
        tree_clear(t->right);
        free(t->right);
    }
}

void tree_init(tree* t){
    t->left = NULL;
    t->right = NULL;
    t->value = 0;
    t->valid = false;
}

bool set_tree_point(tree* t, int value, char *seat){
    while(*seat){
        switch(*seat){
            case 'L':
            case 'l':
                if(!t->left){
                    t->left = (tree*)malloc(sizeof(tree));
                    tree_init(t->left);
                }
                t = t->left;
                break;
            case 'R':
            case 'r':
                if(!t->right){
                    t->right = (tree*)malloc(sizeof(tree));
                    tree_init(t->right);
                }
                t = t->right;
                break;
        }
        seat++;
    }
    
    if(!t->valid){
        t->value = value;
        t->valid = true;
        return true;
    }else{
        return false;
    }
}

void tree_visit(tree* t){
    if(!wrong){
        if(t->left){
            if(t->left->valid)
               tree_visit(t->left); 
            else
               wrong = true;
        }
        
        sprintf(out_str, "%s %d", out_str, t->value);

        if(t->right){
            if(t->right->valid)
               tree_visit(t->right); 
            else
               wrong = true;
        }
    }
    
}

int fu(){
    int tree_size = 0;
    int value;
    char input[100], seat[100];
    tree *t = (tree*) malloc(sizeof(tree));
    tree_init(t);
    *out_str = 0; 
    wrong = false;
    while (1){
        scanf("%s", input);
                // printf("");
        if(get_data(input, &value, seat)){
            if(!wrong){
                wrong = !set_tree_point(t, value, seat);
            }
            tree_size++ ;
        }else{
            break;
        }
    }

	if(tree_size){
        tree_visit(t);
        
        if(wrong){
            printf("wrong data\n");
        }else{
            printf("%s\n", out_str+1);
        }
    }
    tree_clear(t);
    free(t);
    return tree_size;
}

int main(){
    while(fu());
    return 0;
}
