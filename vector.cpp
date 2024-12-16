#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
struct student{
    int id;
    string name;
};
bool cmp(student a,student b){
    return a.name<b.name;
}
int main(){
    vector<student> v;
    student s[3];
    for(int i=0;i<3;i++){
        s[i].id=i+1;
        cout<<"enter name\n";
        cin>>s[i].name;
        v.push_back(s[i]);
    }
    for(auto it=v.begin();it!=v.end();it++){
        cout<<(*it).id<<" "<<(*it).name<<endl;
    }
    sort(v.begin(),v.end(),cmp);
    cout<<"after sorting:\n";
    for(auto it=v.begin();it!=v.end();it++){
        cout<<(*it).id<<" "<<(*it).name<<endl;
    }

    cout<<"Enter name to search";
    string name1;
    cin>>name1;

auto it=v.begin();
    for(it=v.begin();it!=v.end();it++){
        if((*it).name==name1){
            cout<<"found"<<endl;
            break;
        }
    }
    if(it==v.end()){
        cout<<"not found"<<endl;
    }
}