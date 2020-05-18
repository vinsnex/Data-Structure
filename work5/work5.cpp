#include<iostream>
#include<string>
#include<vector>
#include<queue>
using namespace std;

int** new_array_2d(int size){
    static int** data;
    data = new int*[size];
    for(int i=0;i<size ;i++)
        (data)[i] = new int[size];
    return data;
}

bool read_data(int*** matrix, int *size){
    cin >> *size;
    if(*size == 0) return false;

    *matrix = new_array_2d(*size);
    
    for(int i =0;i<*size;i++)
        for(int j=0;j<*size;j++)
            cin >> (*matrix)[i][j];
    return true;
}


void delete_(int **data, int size){
    for(int i=0;i<size;i++)
        delete(data[i]);
    delete(data);
}

int** copy(int** d2, int size){
    int** d1 = new_array_2d(size);
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            d1[i][j] = d2[i][j];
    return d1;
}

void show(int** data, int size){
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            cout << data[i][j] << " ";
        }
        cout << endl; 
    }
}

int find_max(int* data, int size){
    int max = -1;
    for(int i=0;i<size;i++)
        if(data[i] > max)
            max = data[i];
        else if(data[i] == 0)
            return -1;
    return max;
}


void show(int* arr, int size){
    for(int i=0;i<size;i++)
        cout << arr[i] << " ";
    cout << endl;
}

int max_hop(int start, int**data, int size){
    queue<int> que;
    int*dis = new int[size]{0};
    int point;

    dis[start] = 1;
    que.push(start);

    while(que.size() > 0) {
        point = que.front();
        que.pop();
        for(int i=0;i<size;i++){
            if(data[point][i] == 1 && dis[i] == 0){
                dis[i] = dis[point] + 1;
                que.push(i);
            }
            
        }
    }
    cout << start<<": ";
    show(dis, size);
    static int max;
    max = find_max(dis, size);
    delete(dis);
    return max;
}

int find_min(int* arr, int size){
    int min = arr[0];
    for(int i=1;i<size;i++)
        if(min > arr[i])
            min = arr[i];
    return min;
}


int main(){
    int **data;
    int size;
    int*max_dis;
    int min;
    while (read_data(&data, &size)) {
        max_dis = new int[size]{0};
        for(int start =0;start < size; start++){
            max_dis[start] = max_hop(start, data, size);
            if(max_dis[start] == -1) break;
        }

        min = find_min(max_dis, size);

        if(min == -1){
            cout << "disconnected" <<endl;
        }else {
            for(int i=0;i<size;i++)
                if(max_dis[i] == min)
                    cout << i << " ";
            cout << endl;
        }

        delete(max_dis);
        delete_(data, size);
    }
    return 0;
}