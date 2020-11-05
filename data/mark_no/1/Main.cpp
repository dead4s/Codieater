//problem Number01 
#include <iostream> 
#include <stack>
#include <algorithm> 


using namespace std; 

typedef long long ll; 

int main(){
    int b = 20; 
    short int a = b; 

    int N; 
    cin >> N; 
    int heights[N]; 
    for(int i = 0; i < N; i++){
        cin >> heights[i]; 
    }

    stack<pair<int, int>> lastH; //height, width
    lastH.emplace(-1, -1); 
    lastH.emplace(heights[0], 0); 
    ll maxArea = heights[0]; 

    for(int i = 1; i < N; i++){
        if(heights[i-1] < heights[i]){//새로 들어온 것만으로도 이전 최댓값 갱신 
            /*if(maxArea < heights[i]){
                maxArea = heights[i]; 
            } */
            lastH.emplace(heights[i], i); 
            continue; 
        }
        pair<int, int> trash = {-1, -1}; 
        while(lastH.top().first > heights[i]){ //새로 들어온 높이가 이전에 높이보다 낮다. 
            trash = lastH.top(); 
            int newWidth = i - trash.second; 
            ll newArea = (ll)trash.first * newWidth; 
            if(newArea > maxArea){
                maxArea = newArea; 
            }
            lastH.pop();
        }
        ll newArea = 0; 
        pair<int, int> last = lastH.top(); 
        if(last.first == -1){
            newArea = (ll)heights[i]*(i+1); 
            lastH.emplace(heights[i], 0); 
        }   
        else if(last.first == heights[i]){ 
            int newWidth = i - last.second + 1; 
            newArea = (ll)last.first * newWidth; 
        }
        else{
            lastH.emplace(heights[i], trash.second); 
            int newWidth = i - trash.second + 1; 
            newArea = (ll)newWidth * heights[i]; 
        }
        if(newArea > maxArea)
            maxArea = newArea; 
    }

    while(lastH.size() != 1){
        pair<int,int> last = lastH.top(); 
        int newWidth = N - last.second; 
        ll newArea = (ll)newWidth * last.first; 
        if(newArea > maxArea){
            maxArea = newArea; 
        }
        lastH.pop(); 
    }
    cout << maxArea << endl; 
    return 0; 
}
