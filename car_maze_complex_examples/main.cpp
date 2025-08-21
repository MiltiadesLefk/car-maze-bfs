#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <limits>
#include <ctime>
#include "car_Maze.h"
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

Maze *BFS2(Maze *initial,Maze *goal, long long &examined, long long &mem)
{
    queue<Maze *> agenda;
    unordered_map <unsigned long,Maze *> closed;

    agenda.push(initial);
    examined=0;
    mem=1;
    while (agenda.size()>0)
    {
        if (agenda.size() + closed.size() > mem)
            mem = agenda.size() + closed.size();
        Maze *s = agenda.front();
        agenda.pop();
        if (closed.count(s->getKey())==0)
        {
            examined++;
            if (*s==*goal)
                return s;
            pair<unsigned long,Maze *> k (s->getKey(),s);
            closed.insert(k);
            vector<Maze *> children =s->expand();
            for (unsigned int i=0;i<children.size();i++)
                if (closed.count(children[i]->getKey())==0)
                    agenda.push(children[i]);
        }
    }
    return nullptr;
}

Maze *BFS(Maze *initial,Maze *goal, long long &examined, long long &mem)
{
    queue<Maze *> agenda;
    vector <Maze> closed;

    agenda.push(initial);
    examined=0;
    mem=1;
    while (agenda.size()>0)
    {
        if (agenda.size() + closed.size() > mem)
            mem = agenda.size() + closed.size();
        Maze *s = agenda.front();
        agenda.pop();
        if (find(closed.begin(), closed.end(), *s)==closed.end())
        {
            examined++;
            if (*s==*goal)
                return s;
            closed.push_back(*s);
            vector<Maze *> children =s->expand();
            for (unsigned int i=0;i<children.size();i++)
            {
                if (find(closed.begin(), closed.end(), *children[i])==closed.end())
                    agenda.push(children[i]);
            }
        }
    }
    return nullptr;
}


int main()
{
    srand(time(NULL));
    long long mem,examined;
    
    //x, y, horizontal
    vector<pair<pair<int, int>, bool>> cars;
    Maze g(cars);
    
    //parked cars
    cars.push_back(make_pair(make_pair(1,1),true));
    cars.push_back(make_pair(make_pair(3,1),true));
    cars.push_back(make_pair(make_pair(3,2),false));
    cars.push_back(make_pair(make_pair(4,2),true));
    cars.push_back(make_pair(make_pair(2,1),false));

    Maze m(cars);

    //rocks block
    m.setFree(3, 3, false);
    m.setFree(0, 1, false);
    m.setFree(1, 2, false);
    m.setFree(2, 2, false);

    //parked cars block
    m.setFree(1, 1, false);
    m.setFree(3, 1, false);
    m.setFree(3, 2, false);
    m.setFree(4, 2, false);
    m.setFree(2, 1, false);

    Maze *goal =&g;
    Maze *initial = &m;
    Maze *bsol ;//= initial;
    cout<<"Initial:"<<endl<<initial->toString()<<endl;
    cout<<"Goal:"<<endl<<goal->toString()<<endl;


    cout<<endl<<"BFS: ";
    bsol=BFS2(initial,goal,examined,mem);
    if (bsol!=nullptr) {
        vector<string> path;
        path=bsol->getDepth();

        cout<<"depth = "<<path.size()<<", Mem: "<<mem<<", Examined: "<<examined<<endl;

        for(int i=path.size()-1;i>=0;i--)
            cout<<path[i]<<endl;
    }
    else
        cout<<"Problem unsolvable"<<endl;
    
    return 0;
}
