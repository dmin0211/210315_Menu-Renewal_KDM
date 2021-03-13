#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

map<string,int>::iterator iter;
vector<char> temp;
vector<int> course;
map<string,int> resolveMap;
char selected[21];
int subN;

void subSet(int index, int depth){
    if(find(course.begin(),course.end(),depth)!=course.end()){
        iter=resolveMap.find(string(selected).substr(0,depth));
        if(iter==resolveMap.end()){
            resolveMap.insert(pair<string,int>(string(selected).substr(0,depth),0));
        }else{
            resolveMap[(*iter).first]=(*iter).second+1;
        }
    }
    for(int i=index;i<subN;i++){
        selected[depth]=temp[i];
        subSet(i+1,depth+1);
    }
}

vector<string> solution(vector<string> orders, vector<int> courseAl) {
    vector<string> answer;
    course.assign(courseAl.begin(),courseAl.end());
    for(int i=0;i<orders.size()-1;i++){
        for(int j=i+1;j<orders.size();j++){
            for(int k=0;k<orders[i].length();k++){
                for(int t=0;t<orders[j].length();t++){
                    if(orders[i][k]==orders[j][t]&&find(temp.begin(),temp.end(),orders[i][k])==temp.end()) {
                        temp.push_back(orders[i][k]);
                    }
                }
            }
            sort(temp.begin(),temp.end());
            subN=temp.size();
            subSet(0,0);
            temp.clear();
        }
    }
    vector<int> maxCount(11);
    for(iter=resolveMap.begin();iter!=resolveMap.end();iter++){
        maxCount[((*iter).first).length()]=max(maxCount[((*iter).first).length()],(*iter).second);
    }
    for(iter=resolveMap.begin();iter!=resolveMap.end();iter++){
        if((*iter).second==maxCount[((*iter).first).length()]){
            answer.push_back((*iter).first);
        }
    }
    return answer;
}

int main(){
    vector<int> courseMain ={2,3,4};
    vector<string> orders={"XYZ", "XWY", "WXA"};
    solution(orders,courseMain);
}