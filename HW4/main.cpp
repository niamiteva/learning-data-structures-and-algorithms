#include <iostream>
#include "llist.cpp"
#include "graph.cpp"
#include <stack>

using namespace std;

template <typename T>
bool visited(const T& x, LList<T>& l)
{
    l.IterStart();
    elem_link1<T> *p = l.Iter();
    while(p && p->inf != x) p = p->link;

    return p !=NULL;
}
template <typename T>
LList<T> differenceSets(LList<T> p, LList<T> q)
{
    LList<T> r;
    p.IterStart(); q.IterStart();
    elem_link1<T> *pp = p.Iter();
    while(pp)
    {
        if(!visited(pp->inf, r) && !visited(pp->inf, q))
            r.ToEnd(pp->inf);
        pp=pp->link;
    }
    return r;
}
template <typename T>
bool DFS(const T& a, graph<T>& g, LList<T>& l)
{
    l.ToEnd(a);
    elem_link1<T>* p = g.point(a);
    p = p->link;
    while(p)
    {
        if(!visited(p->inf, l))
        {
            if(DFS(p->inf, g, l))
                return true;
        }
        else if(visited(p->inf, l) && p->inf != a)
            return true;

        p = p->link;
    }
    return false;
}
template <typename T>
bool fullDFS(graph<T>& g)
{
    LList<T> v = g.vertexes(), l, h=v;
    while(!h.empty())
    {
        h.IterStart();
        elem_link1<T>* p = h.Iter();
        if(DFS(p->inf, g, l))
            return false;

        h = differenceSets(v,l);
    }
    return true;
}
template <typename T>
void createGraph(graph<T>& g)
{
    ///|/////////////////////////////////////////////////////////////////////////////////////////////
    ///to do reading from file//////////////////////////////////////////////////////////////////////
    ///|////////////////////////////////////////////////////////////////////////////////////////////
    int n;
    cout<<"number of tops: ";
    cin>>n;
    for(int i = 1; i<= n ;i++)
    {
        cout<<"top: ";
        T x; cin>>x;
        g.addTop(x);
        cout<<"number of ribs from "<<x<<": ";
        int k; cin>>k;
        for(int j=1;j<=k;j++)
        {
            cout<<"rib: ";
            T y;cin>>y;
            g.addRib(x, y);
        }
    }
}

typedef graph<int> intGraph;

int main()
{
    intGraph g;
    createGraph(g);
    g.print();
    cout<<"---------------------------------------"<<endl;
    LList<int> l;
    if(fullDFS(g)) cout<<"tree\n";
    else cout<<"not tree\n";

    return 0;
}
