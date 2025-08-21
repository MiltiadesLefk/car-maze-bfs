#include "car_Maze.h"
Maze::Maze()
{
    for (int i=0;i<WIDTH;i++)
        for (int j=0;j<HEIGHT;j++)
            free[i][j]=true;
    setActionName("");
    setPrevious(nullptr);
}
Maze::Maze(vector<pair<pair<int, int>, bool>> cars)
{
    this->cars=cars;
    for (int i=0;i<WIDTH;i++)
        for (int j=0;j<HEIGHT;j++)
            free[i][j]=true;
    setActionName("");
    setPrevious(nullptr);
}

vector<string> Maze::getDepth()
{
    vector<string> path;
    Maze *p = this;
    while (p->prev!=nullptr)
    {
        path.push_back(p->getActionName());
        p=p->prev;
    }
    return path;
}
void Maze::setFree(int i, int j, bool f)
{
    free[i][j]=f;
}

int Maze::getY(int index)
{
    return cars[index].first.second;
}
int Maze::getX(int index)
{
    return cars[index].first.first;
}
bool Maze::isFree(int x,int y)
{
    return free[x][y];
}
void Maze::setX(int x, int index)
{
    cars[index].first.first=x;
}
void Maze::setY(int y, int index)
{
    cars[index].first.second=y;
}

bool Maze::operator==(const Maze& s) const
{
    if(s.cars.size()!=cars.size())
        return false;
    return (equal(s.cars.begin(), s.cars.end(), cars.begin()));
}
Maze Maze::operator= (Maze o)
{
    cars=o.cars;
    prev = o.prev;
    actionName = o.actionName;
    return *this;
}
string Maze::toString () const
{
    stringstream ot;
    ot<<"Cars:"<<endl;
    for (pair car : cars)
        ot<<car.first.first<<"-"<<car.first.second<<endl;
    ot<<"Blocks"<<endl;
    for (int i=0;i<WIDTH;i++)
        for (int j=0;j<HEIGHT;j++)
                if(free[i][j])
                ot<<i<<"-"<<j<<endl;
    return ot.str();
}

bool operator< (const Maze& a,const Maze& o)
{
    return (a.toString() < o.toString());
}

bool Maze::goUp(Maze &n, int index)
{
    if(getY(index)==HEIGHT-1) {
        n=*this;
        n.setActionName("Up <- "+to_string(cars[index].first.first)+"-"+to_string(cars[index].first.second));
        n.setFree(n.getX(index), n.getY(index), true);
        n.cars.erase(n.cars.begin()+index);
        n.setPrevious(this);
        
        return true;
    }
    else if (isFree(getX(index),getY(index)+1)) {
        n=*this;
        n.setActionName("Up <- "+to_string(cars[index].first.first)+"-"+to_string(cars[index].first.second));
        n.setFree(n.getX(index), n.getY(index), true);
        n.setY(n.getY(index)+1, index);
        n.setFree(n.getX(index), n.getY(index), false);
        n.setPrevious(this);
        
        return true;
    }
    
    return false;
}

bool Maze::goDown(Maze &n, int index)
{
    if(getY(index)==0) {
        n=*this;
        n.setActionName("Down <- "+to_string(cars[index].first.first)+"-"+to_string(cars[index].first.second));
        n.setFree(n.getX(index), n.getY(index), true);
        n.cars.erase(n.cars.begin()+index);
        n.setPrevious(this);
        
        return true;
    }
    else if (isFree(getX(index),getY(index)-1)) {
        n=*this;
        n.setActionName("Down <- "+to_string(cars[index].first.first)+"-"+to_string(cars[index].first.second));
        n.setFree(n.getX(index), n.getY(index), true);
        n.setY(n.getY(index)-1, index);
        n.setFree(n.getX(index), n.getY(index), false);
        n.setPrevious(this);
        
        return true;
    }
    
    return false;
}
bool Maze::goLeft(Maze &n, int index)
{
    if(getX(index)==0) {
        n=*this;
        n.setActionName("Left <- "+to_string(cars[index].first.first)+"-"+to_string(cars[index].first.second));
        n.setFree(n.getX(index), n.getY(index), true);
        n.cars.erase(n.cars.begin()+index);
        n.setPrevious(this);
        
        return true;
    }
    else if (isFree(getX(index)-1,getY(index))) {
        n=*this;
        n.setActionName("Left <- "+to_string(cars[index].first.first)+"-"+to_string(cars[index].first.second));
        n.setFree(n.getX(index), n.getY(index), true);
        n.setX(n.getX(index)-1, index);
        n.setFree(n.getX(index), n.getY(index), false);
        n.setPrevious(this);
        
        return true;
    }
    
    return false;
}
bool Maze::goRight(Maze &n, int index)
{
    if(getX(index)==WIDTH-1) {
        n=*this;
        n.setActionName("Right <- "+to_string(cars[index].first.first)+"-"+to_string(cars[index].first.second));
        n.setFree(n.getX(index), n.getY(index), true);
        n.cars.erase(n.cars.begin()+index);
        n.setPrevious(this);
        
        return true;
    }
    else if (isFree(getX(index)+1,getY(index))) {
        n=*this;
        n.setActionName("Right <- "+to_string(cars[index].first.first)+"-"+to_string(cars[index].first.second));
        n.setFree(n.getX(index), n.getY(index), true);
        n.setX(n.getX(index)+1, index);
        n.setFree(n.getX(index), n.getY(index), false);
        n.setPrevious(this);
        
        return true;
    }

    return false;
}

vector <Maze *> Maze::expand()
{
    vector <Maze *> children;
    Maze *child;

    for(int i=0;i<cars.size();i++) {
        if(cars[i].second) {    //horizontal
            child = new Maze(*this);
            if (goLeft(*child, i))
                children.push_back(child);
            else
                delete child;
            child = new Maze(*this);
            if (goRight(*child, i))
                children.push_back(child);
            else
                delete child;    
        }
        else {  //vertical
            child = new Maze(*this);
            if (goUp(*child, i))
                children.push_back(child);
            else
                delete child;
            child = new Maze(*this);
            if (goDown(*child, i))
                children.push_back(child);
            else
                delete child;
        }
    }

    return children;
}

void Maze::setHvalue(double h)
{
    Hvalue = h;
}

double Maze::getHvalue()
{
    return Hvalue;
}

ostream & operator<<(ostream &stream,const Maze &a)
{
    string s="";

    s= a.getActionName();
    Maze *p=a.getPrevious();

    while (p!=nullptr)
    {
        s = p->getActionName()+" "+s;
        p = p->getPrevious();
    }
    stream <<s;
    return stream;
}