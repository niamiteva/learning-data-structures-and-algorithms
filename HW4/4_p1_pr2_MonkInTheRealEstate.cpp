#include <iostream>
#include "llist.cpp"
#include "graph.cpp"

using namespace std;

template <typename T>
bool member(const T& x, LList<T>& l)
{
    l.IterStart();
    elem_link1<T> *p = l.Iter();
    while(p && p->inf != x) p = p->link;

    return p !=NULL;
}
template <typename T>
void createGraph(graph<T>& g, LList<T>& l)
{
    int n; 
    cout<<"number of roads between A and B: "; 
    cin>>n;
    int x,y;
    for(int i = 1; i<=n;i++)
    {
        cout<<"top: "; 
        cin>>x;
        cout<<"rib of "<<x<<": "; 
        cin>>y;

        g.addTop(x);
        g.addRib(x,y);
        if(!member(x,l)) l.ToEnd(x);
        if(!member(y,l)) l.ToEnd(y);
    }
}

int main()
{
    graph<int> g;
    LList<int> l;
    
    createGraph(g, l);
    g.print();
    
    cout<<l.len()<<endl;


    return 0;
}
