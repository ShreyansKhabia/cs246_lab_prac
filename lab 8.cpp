#include <bits/stdc++.h>
using namespace std;

#define ll long long 

ll global_toc =1;



class bucket
{
public:
	vector<ll> bckt;
	ll ld=1;
	ll oc=0;
	ll toc=99999;
	
};

map<bucket*, vector<ll>> toc_holer;

class Directory
{
public:
	ll bc;
	ll gd;
	vector<bucket *> dirv;

	void insert(ll x, ll pass);
	void search(ll x);
	void delete_ele(ll x);
	void display_status();
	void showdir();
	void update_toc();
};

// void Directory::update_toc(){

// 	for (int i = dirv.size()-1; i > -1; --i)
// 	{
// 		for (int j = 0; j < i; ++j)
// 		{
// 			if(dirv[j]==dirv[i]){
// 				toc_holer[i] = toc_holer[j];
// 			}
// 		}
// 	}

// 	for (int i = 0; i < dirv.size(); ++i)
// 	{
// 		dirv[i]->toc=  toc_holer[i];
// 	}
// }


void Directory::insert(ll x, ll pass){

	cout<<"inserting "<<x<<endl;
	ll index = x & ((1<<gd)-1);
	cout<<"index: "<<index<<", global depth: "<<gd<<", occup: "<<dirv[index]->oc<<", local depth: "<<dirv[index]->ld<<endl;
	

	if(dirv[index]->oc < bc){

		cout<<"case 0\n";

		for (int i = 0; i < bc; ++i)
		{
			if(dirv[index]->bckt[i]==-1){
				dirv[index]->oc++;
				dirv[index]->bckt[i]= x;

				if(toc_holer[dirv[index]].size()==0){
					toc_holer[dirv[index]].push_back(global_toc++);
				}
				cout<<"insertion of "<<x<< " success at "<<index<<endl;
				break;
			}
		}
		//update_toc();


	}else{

		cout<<"for "<<x;

		if(dirv[index]->ld<gd){

			cout<<" case 1\n";

			dirv[index]->ld++;
			
			index = x & ((1<< dirv[index]->ld)-1);

			vector<ll> tmp= dirv[index]->bckt;

			for (int i = 0; i < bc; ++i)
			{
				dirv[index]->bckt[i]=-1;

			}

			dirv[index]->oc=0;

			ll andnum = (1<< dirv[index]->ld)-1, newindex;
			ll oldindex = x & (1<< dirv[index]->ld-1)-1;

			//showdir();
			

			for (int i = 0; i < tmp.size(); ++i)
			{	
				cout<<tmp[i]<<endl;
				ll newindex = ((tmp[i]) & (andnum));
				cout<<newindex<<endl;

				if(newindex != oldindex && dirv[newindex] == dirv[oldindex]){

					//cout<<"here\n";
					if(newindex>oldindex){

						dirv[newindex] = new bucket;
						dirv[newindex]->ld = dirv[index]->ld;
						dirv[newindex]->bckt.resize(bc,-1);
						if(toc_holer[dirv[newindex]].size()==0){
							toc_holer[dirv[newindex]].push_back(global_toc++);
						}else{
							toc_holer[dirv[newindex]][0] = global_toc++;
						}

					}else{

						ll temp = toc_holer[dirv[newindex]][0];
						dirv[newindex] = NULL;
						dirv[newindex] = new bucket;
						dirv[newindex]->ld = dirv[newindex]->ld;
						dirv[newindex]->bckt.resize(bc,-1);
						toc_holer[dirv[newindex]].clear();
						toc_holer[dirv[newindex]].push_back(temp);
					}
					// dirv[newindex]->toc=global_toc++;
					//cout<<"out\n";
				}
				

				for (int j = 0; j < bc; ++j)
				{
					if(dirv[newindex]->bckt[j] == -1){
						dirv[newindex]->oc++;
						dirv[newindex]->bckt[j]= tmp[i] ;
						if(toc_holer[dirv[newindex]].size()==0){
							toc_holer[dirv[newindex]].push_back(global_toc++);
						}
						cout<<"insertion success at "<<newindex<<endl;
						break;
					}
				}

				//showdir();

			}

			//update_toc();
			showdir();
			insert(x,pass+1);

		}

		else{
			cout<<" case 2\n";
			if(gd==20){
				cout<<"global depth reached 20, action aborted!\n";
			}else{

				gd++;
				ll oldsize = 1<<(gd-1);
				ll size = 1<<gd;

				vector<bucket *> tdir = dirv;
				dirv.resize(size);
				

				for (int i = 0; i < oldsize; ++i)
				{
					dirv[i] = tdir[i];
				}
				for (int i = oldsize; i < size; ++i)
				{
					dirv[i] = dirv[ i- oldsize];
				}
				
				//update_toc();
				showdir();
				insert(x, pass+1);
			}
		}

	}


}


void Directory::search(ll x){

	ll index = x & ((1<<gd)-1);
	ll chk=0;
	for (int i = 0; i < bc; ++i)
	{
		if(dirv[index]->bckt[i]==x){

			chk=1;
			break;
		}
		
	}

	if(chk){
		cout<<"Found!\n";
	}else{
		cout<<"Not Found!\n";
	}

}

void Directory::delete_ele(ll x){

	ll index = x & ((1<<gd)-1);
	ll chk=0;

	for (int i = 0; i < bc; ++i)
	{
		if(dirv[index]->bckt[i]==x){
			
			dirv[index]->bckt[i]=-1;
			dirv[index]->oc--;
			chk=1;
			break;
		}
	}

	if(chk){
		cout<<"Deleted!!\n";
	}else{
		cout<<"Not Found!\n";
	}

}

bool toc_comp(vector<ll> v1, vector<ll> v2){

		return (v1[0]< v2[0]);

}


void Directory::display_status(){
	//update_toc();
	cout << "here\n";
	vector<vector<ll>> ans;
	vector<ll> vec;
	for (int i = 0; i < dirv.size(); ++i)
	{
	

		vec.clear();
		vec.push_back(toc_holer[dirv[i]][0]);
		vec.push_back(dirv[i]->oc);
		vec.push_back(dirv[i]->ld);
		
		auto itr = find(ans.begin(), ans.end(), vec);
		if(itr==ans.end()){
			ans.push_back(vec);
		}	

	

	}

	sort(ans.begin(), ans.end(),toc_comp);

	cout<<gd<<endl;
	cout<<ans.size()<<endl;

	for(auto buc : ans){
		cout<<buc[1]<<' '<<buc[2]<<" toc: "<<buc[0]<<endl;
	}
	// for (int i = 1; i < global_toc; ++i)
	// {
	// 	for (int j = 0; j < toc_holer.size(); ++j)
	// 	{
	// 		if(toc_holer[j]== i){
	// 			cout<< dirv[j]->oc<<' '<< dirv[j]-> ld <<endl;
	// 			break;
	// 		}
	// 	}
	// }


}

void Directory::showdir(){

	cout<<endl<<endl;

	for (int i = 0; i < dirv.size(); ++i)
	{
		for (int j = 0; j < dirv[i]->bckt.size(); ++j)
		{
			cout<<dirv[i]->bckt[j]<<' ';
		}
		if(toc_holer[dirv[i]].size()!=0){
		cout<<" toc: "<<toc_holer[dirv[i]][0]<<endl;
		}else{
			cout<<endl;
		}
	}

	cout<<endl<<endl;

}

int main()
{	
	Directory dir;
	cin>>dir.gd>>dir.bc;
	
	ll size = 1<<dir.gd ;
	dir.dirv.resize( size );

	for (int i = 0; i < 2; ++i)
	{
		dir.dirv[i]= new bucket;
		dir.dirv[i]->ld=1;
		dir.dirv[i]->bckt.resize(dir.bc,-1);

	}

	for (int i = 2; i < size; ++i)
	{
		ll index = i%2;
		dir.dirv[i] = dir.dirv[index];
	}

	ll term = 1,choice,x;
	while(term){
		cin>>choice;

		switch(choice){
			case 2:

				cin>>x;
				dir.insert(x,0);
				dir.showdir();

				break;
			case 3:

				cin>>x;
				dir.search(x);
				dir.showdir();
				break;
			case 4:

				cin>>x;
				dir.delete_ele(x);
				dir.showdir();
				break;
			case 5:
				dir.display_status();
				dir.showdir();
				break;
			case 6:
				term=0;
				break;

		}
	}



	return 0;
}