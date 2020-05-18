#include<iostream>
#include<vector>
#include<string>
#include <algorithm>
using namespace std;

class Link_Point{
public:
    int n1;
    int n2;

    Link_Point(int n1, int n2){
        this->n1 = n1;
        this->n2 = n2;
    }

    bool equal(int _n1, int _n2){
        if((_n1 == this->n1 && _n2 == this->n2) ||
            (_n2 == this->n1 && _n1 == this->n2)) {
            return true;
        }
        return false;
    }

    string toString(){ return "( " + to_string(n1) + ", " + to_string(n2) + " ) "; } 
};

bool **new_array_2d(int size);
bool **new_array_2d(vector<Link_Point*> point, int size);
void delete_(bool **Point_Map, int size);
void read_Map_2d(bool **map, int size);

void read_link_Point(bool *point, int size);
bool *new_array(int size);

void show(bool **map, int size);
void show(bool *map, int size);

vector<Link_Point*> Convert_Link_Point(bool **map, int size);
void delete_(vector<Link_Point*> p);
void show(vector<Link_Point*> *p);

void Com_Point(vector<Link_Point*> p_s, int begin, vector<Link_Point*>* p_t, vector<vector<Link_Point*>>* out);

int Node_Pr(vector<Link_Point*> *p, bool *sel_node, int size);

void show(vector<Link_Point*> val){
    for(vector<Link_Point*>::iterator it = val.begin(); it!=val.end() ;it++){
        cout << (*it)->toString() << " ";
    }
    cout <<endl;
}

int main(){
    bool **Point_Map;
    bool *selete_Point;
    int Point_size;
    vector<Link_Point*> conv_link_point, null_conv_link_point;
    vector<vector<Link_Point*>> total_com;
    
    while(1){
        cin >> Point_size;
        if(Point_size == 0) return 0;

        Point_Map = new_array_2d(Point_size);
        selete_Point = new_array(Point_size);

        read_Map_2d(Point_Map, Point_size);
        read_link_Point(selete_Point, Point_size);

        conv_link_point = Convert_Link_Point(Point_Map, Point_size);

        // show(Point_Map, size);
        // show(selete_Point, size);
        // show(conv_link_point);
        Com_Point(conv_link_point, 0, &null_conv_link_point, &total_com);
        int min_ = INT32_MAX, bd_size;
        for(vector<vector<Link_Point*>>::iterator it = total_com.begin(); it < total_com.end();it++){
            // show(&*it);
            bd_size = Node_Pr(&*it, selete_Point, Point_size);
            if(bd_size < min_) min_ = bd_size;
        }
        cout << min_ <<endl;

        delete_(conv_link_point);
        delete_(Point_Map, Point_size);
        total_com.clear();
    }
    return 0; 
}

bool Com_Req_Node(bool **map, bool *selete_node, int size){
    for(int i=0;i<size;i++){
        if(selete_node[i]){
            int j;
            for(j=0;j<size; j++){
                if(map[i][j]) break;
            }
            if(j == size) return false;
        }
    }
    return true;
}

void isSurround(bool **map, int node, int pos_node, int size, vector<int>*buff, bool *surr){
    if(!*surr){
        vector<int>::iterator it = find(buff->begin(), buff->end(), node);
        if(it != buff->end()) {
            *surr = true;
            return;
        }

        buff->push_back(node);
        for(int i=0;i<size;i++){
            if(map[node][i] == 1 && i != pos_node){
                isSurround(map, i, node, size, buff, surr);
            }
        }
    }
}

int find_start_node(bool **map, int size){
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            if(map[i][j])
                return i;
    return -1;
}

int selete_node_size(bool** map, int size){
    int total = 0;
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(map[i][j]){
                total++;
                break;
            }
        }
    }
    return total;
}

int Tree_bd(bool **map, int size){
    int ret = 0;
    for(int i=0;i<size;i++){
        int count =0;
        for(int j=0;j<size;j++){
            if(map[i][j]){
                count ++;
            }
        }
        if(count >1)
            ret ++;
    }
    return ret;
}

int Node_Pr(vector<Link_Point*> *p, bool *sel_node, int size){
    bool** map = new_array_2d(*p, size);
    int tree_bd = INT32_MAX;
    int map_sel_size = selete_node_size(map, size); //計算選到的節點 數是不是等於遞迴跑得的節點數量
    bool is_Sel_Node_pass = Com_Req_Node(map,sel_node, size);//檢查必選點有沒有選到
    bool isSurr = false;//存有節點有沒有環繞

    vector<int> Pass_point;
    isSurround(map, find_start_node(map, size), -1, size ,&Pass_point, &isSurr);//用遞迴跑過整個數 看有沒有環繞
    // cout << "IsSurr = " << isSurr << " map_sel_size = " << map_sel_size << " Pass_Point size = " << Pass_point.size() << " is_Sel_Node_pass = " << is_Sel_Node_pass <<endl;
    if(!isSurr && map_sel_size == Pass_point.size() && is_Sel_Node_pass){
        tree_bd = Tree_bd(map,size);
        // cout<<tree_bd<<endl;
    }

    delete_(map, size);
    return tree_bd;
}

void Com_Point(vector<Link_Point*> p_s, int begin, vector<Link_Point*>* p_t, vector<vector<Link_Point*>>* out){
    static bool** n_map;
    for(int i=begin ;i<p_s.size();i++){
        p_t->push_back(p_s.at(i));
        out->push_back(*p_t);
        Com_Point(p_s, i+1, p_t, out);
        p_t->pop_back();
    }
}

vector<Link_Point*> Convert_Link_Point(bool **map, int size){
    vector<Link_Point*> p;
    for(int i=0;i < size;i++)
        for(int j=i+1;j<size;j++)
            if(map[i][j])
                p.push_back(new Link_Point(i, j)); 
    return p; 
}

void delete_(vector<Link_Point*> p){
    for(int i=0;i<p.size(); i++)
        delete(p[i]);
    p.clear();
}

void read_link_Point(bool *point, int size){
    for(int i=0;i<size;i++)
        cin >> point[i];
}

bool *new_array(int size){ return new bool[size]; }

void read_Map_2d(bool **map, int size){
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            cin >> map[i][j];
}

bool **new_array_2d(int size){
    static bool **Point_Map;
    Point_Map = new bool*[size];
    for(int i=0;i<size;i++){
        Point_Map[i] = new bool[size];
        for(int j=0;j<size;j++)
            Point_Map[i][j] = 0;
    } 
    return Point_Map;
}

bool **new_array_2d(vector<Link_Point*> point, int size){
    static bool **p;
    p = new_array_2d(size);
    for(vector<Link_Point*>::iterator it = point.begin(); it < point.end(); it++){
        p[(*it)->n1][(*it)->n2] = true;
        p[(*it)->n2][(*it)->n1] = true;
    }
    return p;
}

void delete_(bool **Point_Map, int size){
    for(int i=0;i<size;i++)
        delete(Point_Map[i]);
    delete(Point_Map);
}

void show(vector<Link_Point*> *p){
    for (auto &&i : *p)
        cout << i->toString();
    cout << endl;
}


void show(bool **map, int size){
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}

void show(bool *link, int size){
    for(int i=0;i<size;i++)
        cout << size << " ";
    cout << endl;
}
