#include <iostream>
#include "llist.cpp"
#include "graph.cpp"

using namespace std;

#define MAX 100

template <class T>
void create(graph<T>& g, const int& houses, const int city[][2])
{
    for(int i=1; i<=houses; i++)
        g.addTop(i);

    for(int i=0; i<houses-1;i++)
    {
        g.addRib(city[i][0], city[i][1]);
        g.addRib(city[i][1], city[i][0]);
    }

}
////////
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
bool way(const T& a, const T& b, graph<T>& g, LList<T>& l)
{
    l.ToEnd(a);
    if(a == b) return true;
    elem_link1<T>* q = g.point(a);
    q = q->link;
    while(q)
    {
        if(!member(q->inf, l))
        {
            if(way(q->inf, b, g, l)) return true;
            deleteLast(l);
        }
        q = q->link;
    }
    return false;
}
///////
template <class T>
void oliverFindsBob(graph<T>& g, int houses)
{
    int q; cin>>q;
    int kingsHouse =1;
    int queries[3];
    LList<T> l;
    for(int i=0; i<q;i++)
    {
        cin>>queries[0]>>queries[1]>>queries[2];
        if(queries[0] == 0)
        {
            if(way(queries[2], queries[1], g, l) && way(queries[1], kingsHouse, g, l)) cout<<"YES\n";
            else cout<<"NO\n";
        }
        else
        {
            if(way(queries[2], queries[1], g, l) && way(queries[1], houses, g,l)) cout<<"YES\n";
            else cout<<"NO\n";
        }

    }
}

int main()
{
    int houses;
    cin>>houses;
    int city[MAX][2];
    for(int i=0; i<houses-1;i++)
    {
        cin>>city[i][0]>>city[i][1];
    }

    LList<int> l;
    graph<int> g;
    create(g, houses, city);

    oliverFindsBob(g, houses);



    return 0;
}
