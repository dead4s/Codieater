#include <iostream> 
#include <stack>
#include <algorithm> 

using namespace std; 

typedef long long ll; 

int main(){
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
            if(maxArea < heights[i]){
                maxArea = heights[i]; 
            } 
            lastH.emplace(heights[i], i); 
            continue; 
        }
        pair<int, int> trash = {-1, -1}; 
        while(lastH.top().first > heights[i]){ //새로 들어온 높이가 이전에 높이보다 낮다. 
            trash = lastH.top(); 
            int newWidth = i - trash.second - 1; 
            int newArea = trash.first * newWidth; 
            if(newArea > maxArea){
                maxArea = newArea; 
            }
            lastH.pop();
        }
        int newArea = 0; 
        pair<int, int> last = lastH.top(); 
        if(last.first == -1){
            newArea = heights[i]*(i+1); 
            lastH.emplace(heights[i], 0); 
        }   
        else if(last.first == heights[i]){
            int newWidth = i - last.second + 1; 
            newArea = last.first * newWidth; 
        }
        else{
            lastH.pop(); 
            lastH.emplace(heights[i], trash.second); 
            int newWidth = i - trash.second + 1; 
            newArea = newWidth * heights[i]; 
        }
        if(newArea > maxArea)
            maxArea = newArea; 
    }

    while(lastH.size() != 1){
        pair<int,int> last = lastH.top(); 
        int newWidth = N - last.second; 
        int newArea = newWidth * last.first; 
        if(newArea > maxArea){
            maxArea = newArea; 
        }
        lastH.pop(); 
    }
    cout << maxArea << endl; 
    return 0; 
}
