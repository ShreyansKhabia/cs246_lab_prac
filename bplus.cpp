#include <bits/stdc++.h>

using namespace std;

class node
{
public:
    node(int n);
    int *val;
    node **child;
    node *parent;
    int size;
    int leaf;
    ~node();
};

node::node(int n)
{
    val = new int[n + 1];
    child = new node *[n + 2];

    for (int i = 0; i < n + 2; i++)
        child[i] = nullptr;

    parent = nullptr;
    size = 0;
    leaf=0;
}

node::~node()
{
}

class bplus
{
private:
    int d;
    int t;
    int num_leaf;
    int num_index;
    node *root;

public:
    bplus(int x,int y);
    void insert(int val);
    void print();
    void isFull(node *curr);
    ~bplus();
};

bplus::bplus(int x,int y)
{
    t=x;
    d=y;
    num_leaf=0;
    num_index=0;
    root=nullptr;
}

void bplus::isFull(node *curr)
{
    if(curr->leaf == 1){
        if(curr->size < 2*d+1)
            return;
    }
    
    else{
        if(curr->size < 2*t+2)
            return;
    }

    if(curr->leaf ==1)
    {   
        int c2 = 2*d;
        node *ne = new node(c2);
        ne->leaf=1;
        num_leaf++;

        for(int i=d;i<curr->size;i++)
        {
            ne->val[ne->size++] = curr->val[i];
        }

        curr->size=d;

        int valup = ne->val[0];

        if(curr==root)
        {   
            int c3 = 2*t+1;
            root = new node(c3);
            num_index=1;
            root->val[root->size++]=valup;
            curr->parent=root;
            ne->parent=root;
            root->child[0]=curr;
            root->child[1]=ne;
            return;
        }

        node *par = curr->parent;

        int pos;
        for(pos=0;pos<par->size;pos++){
            if(valup < par->val[pos])
                break;
        }

        for(int j=par->size;j>pos;j--)
                par->val[j]=par->val[j-1];
            
        par->val[pos] = valup;
        ne->parent=par;
        par->size++;

        for(int pt=par->size;pt>pos+1;pt--)
        {
            par->child[pt] = par->child[pt-1];
        }

        par->child[pos+1]=ne;

        isFull(par);
    }

    else
    {
        if(curr==root)
        {
            int c4 = 2*t+1;
            node *ne = new node(c4);
            // ne->leaf=1;
            num_index++;

            int valup = curr->val[t];
            for(int i=t+1;i<curr->size;i++)
            {
                ne->val[ne->size++] = curr->val[i];
            }

            curr->size=t;

            int k=0;
            for(int j=t+1;j<=2*t+2;j++)
            {
                ne->child[k]=curr->child[j];
                curr->child[j]->parent=ne;
                k++;
            }

            root = new node(c4);
            num_index++;

            root->val[root->size++]=valup;
            root->child[0]=curr;
            root->child[1]=ne;
            curr->parent=root;
            ne->parent=root;
            return;
        }

        else
        {
            int c5 = 2*t+1;
            node *ne = new node(c5);
            // ne->leaf=1;
            num_index++;

            int valup = curr->val[t];
            for(int i=t+1;i<curr->size;i++)
            {
                ne->val[ne->size++] = curr->val[i];
            }

            curr->size=t;

            int k=0;
            for(int j=t+1;j<=2*t+2;j++)
            {
                ne->child[k]=curr->child[j];
                curr->child[j]->parent=ne;
                k++;
            }

            node *par = curr->parent;

            int pos;
            for(pos=0;pos<par->size;pos++){
                if(valup < par->val[pos])
                    break;
            }

            for(int j=par->size;j>pos;j--)
                    par->val[j]=par->val[j-1];
                
            par->val[pos] = valup;
            ne->parent=par;
            par->size++;

            for(int pt=par->size;pt>pos+1;pt--)
            {
                par->child[pt] = par->child[pt-1];
            }

            par->child[pos+1]=ne;

            isFull(par);

        }
    }
}

void bplus::insert(int sto)
{
    if(root==nullptr)
    {   
        int c1 = 2*d;
        root = new node(c1);
        root->leaf = 1;
        root->val[0]=sto;
        root->size++;
        num_leaf++;
        return;
    }

    node *curr = root;

    while(1)
    {
        int pos;
        for(pos=0;pos<curr->size;pos++){
            if(sto < curr->val[pos])
                break;
        }

        // if(curr->leaf==1)
        //     cout << "LEAF" << sto << endl;

        if(curr->leaf==0){ // reach till correct node
            curr = curr->child[pos];
            //cout << sto << endl;
        }

        else
        {   // if this is the correct node
            for(int j=curr->size;j>pos;j--)
                curr->val[j]=curr->val[j-1];
            
            curr->val[pos] = sto;
            curr->size++;
            // shifted all nodes greater than this and added to correct pos.

            // for(int i=0;i<curr->size;i++)
            //     cout << curr->val[i] << " ";
            
            // cout << endl;
            
            isFull(curr);
            return;
        }

    }
}

void bplus::print()
{
    // node *curr = root;
    // for(int i=0;i<curr->size;i++)
    //     cout << curr->val[i] << " ";
    
    // cout << endl;
    cout << num_index << " " << num_leaf << endl;

    node *curr = root;

    // while (1)
    // {
        int si = curr->size;

        for (int i = 0; i < si; i++)
            cout << curr->val[i] << " ";

        cout << endl;

        // if (curr->leaf != 1)
        // {
        //     for (int i = 0; i < si + 1; i++)
        //     {
        //         node *pri = curr->child[i];

        //         for (int j = 0; j < pri->size; j++)
        //             cout << pri->val[j] << " ";

        //         cout << endl;
        //     }
        // }

        // if(curr->leaf != 1)
        // {
        //     curr = curr->child[si];
        // }
        // else
        //     break;
    // }
}

bplus::~bplus()
{
}

int main()
{
    int t,d;
    cin >> d >> t;

    bplus tr(t,d);

    int x;

    while(cin >> x)
    {
        switch (x)
        {
        case 1:
            int b;
            cin >> b;
            tr.insert(b);
            break;

        case 2:
            tr.print();
            break;

        default:
            break;
        }
    }
}