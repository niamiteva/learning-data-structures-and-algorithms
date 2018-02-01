#include <iostream>
#include "llist.cpp"
#include "graph.cpp"

using namespace std;

#define MAX 100

template <typename T>
bool member(const T& x, LList<T>& l)
{
    l.IterStart();
    elem_link1<T> *p = l.Iter();
    while(p && p->inf != x) p = p->link;

    return p !=NULL;
}
template <class T>
void deleteLast(LList<T>& l)
{
    l.IterStart();
    T x;
    elem_link1<T>* p = l.Iter();
    while(p->link) p = l.Iter();
    l.DeleteElem(p,x);
}
template <class T>
bool connected(const T& a, const T& b, graph<T>& g, LList<T>& l)
{
    l.ToEnd(a);
    if(a == b) return true;
    elem_link1<T>* q = g.point(a);
    q = q->link;
    while(q)
    {
        if(!member(q->inf, l))
        {
            if(connected(q->inf, b, g, l)) return true;
            deleteLast(l);
        }
        q = q->link;
    }
    return false;
}
template <class T>
void create(graph<T>& g, const int& computers, const int& connections, const int group[][2])
{
    for(int i=0; i<computers; i++)
        g.addTop(i);

    for(int i=0; i<connections;i++)
        g.addRib(group[i][0], group[i][1]);
}
template <class T>
void happy(graph<T>& g, const int group[][2], const int start, const int& computers)
{
    int days, compToDisconnect;
    T x,y;
    cin>>days;
    for(int i=0;i<days;i++)
    {
        cin>>compToDisconnect;
        x = group[compToDisconnect-1][0];
        y = group[compToDisconnect-1][1];
        g.deleteRib(x,y);
        LList<int> l;
        if(connected(start, computers, g,l)) cout<<"Happy\n";
        else cout<<"Unhappy\n";
        g.addRib(x,y);
    }
}

int main()
{
    int computers, connections;
    cin>>computers>>connections;

    int group[MAX][2];
    for(int i=0; i<connections;i++)
    {
        cin>>group[i][0]>>group[i][1];
    }

    LList<int> l;
    graph<int> g;
    create(g, computers, connections, group);
    int start = 1;

    happy(g, group, start, computers);


    return 0;
}
