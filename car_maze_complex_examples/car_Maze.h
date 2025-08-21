#ifndef MAZE_H
#define MAZE_H
#define WIDTH  6
#define HEIGHT  4
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Maze
{
    public:
        Maze();
        Maze(vector<pair<pair<int, int>, bool>>);
        void setFree(int i, int j, bool f);
        int getY(int index);
        int getX(int index);
        bool isFree(int x,int y);
        void setX(int x, int index);
        void setY(int y, int index);
        Maze operator= (Maze o);
        bool operator==(const Maze& o) const ;
        string toString () const;
        friend bool operator< (const Maze& a,const Maze& o);
        bool goUp(Maze &n, int index);
        bool goDown(Maze &n, int index);
        bool goLeft(Maze &n, int index);
        bool goRight(Maze &n, int index);
        vector <Maze *> expand();
        vector<string> getDepth();
        void setHvalue(double);
        double getHvalue();
        int heuristic (Maze *);
        void setActionName(string s) {actionName=s;}
        string getActionName()const {return actionName;}
        void setPrevious (Maze *p) {prev=p;}
        Maze *getPrevious()const {return prev;}

        
        unsigned long long getKey()
        {
            unsigned long long k=0;

            for(int i=0;i<cars.size();i++) {
                k*=1000;
                k+=cars[i].first.first*100+cars[i].first.second*10+cars[i].second;
            }
            
            return k;
        }
        

        friend ostream & operator<<(ostream &, const Maze &);
    protected:

    private:
        vector<pair<pair<int, int>, bool>> cars;
        bool free[WIDTH][HEIGHT];
        double Hvalue;
        string actionName;
        Maze *prev;
};

class myComparator
{
public:
    int operator() (Maze *p1 , Maze *p2) const
    {
        return p1->getHvalue()>p2->getHvalue();
    }
};

#endif // MAZE_H
