#include <iostream>
#include <set>
#include <unordered_map>

#define MAX_N 100005

using namespace std;
using pii = pair<int, int>;

int N, L;
set<pii> s; // 난이도 문제번호
set<pii> sg[101]; // 난이도 문제 번호, recommend G 를 처리하기 위해 사용
unordered_map<int, pii> um;
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;

    for(int i = 0; i < N; i++){
        int p, l, g;

        cin >> p >> l >> g;
        s.insert({l, p});
        sg[g].insert({l, p});
        um[p] = {l, g};
    }

    cin >> L;

    while(L--){
        string str;
        cin >> str;

        if(str == "recommend"){
            int g, x;
            cin >> g >> x;
            if(x == 1){
                auto it = sg[g].rbegin();
                cout << it->second << "\n";
            }
            else{
                auto it = sg[g].begin();
                cout << it->second << "\n";
            }
        }
        else if(str == "recommend2"){
            int x;
            cin >> x;
            if(x == 1){
                auto it = s.rbegin();
                cout << it->second << "\n";
            }
            else{
                auto it = s.begin();
                cout << it->second << "\n";
            }
        }
        else if(str == "recommend3"){
            int x, l;
            cin >> x >> l;
            // 난이도 L 이상 중: L 최소, 동률이면 P 최소
            if(x == 1){
                auto it = s.lower_bound({l, 0});
                if(it == s.end())
                    cout << "-1\n";
                else
                    cout << it->second << "\n";
            }
            // 난이도 L 미만 중: L 최대, 동률이면 P 최대
            else{
                auto it = s.lower_bound({l, 0});
                // L 미만인게 없을 때
                if(it == s.begin())
                    cout << "-1\n";
                else{
                    if(it == s.end()){
                        // 모두 L 미만인 경우 set 의 마지막 값이 정답
                        auto rit = s.rbegin();
                        cout << rit->second << "\n";
                    }
                    // L 이상이 하나라도 있는 경우 직전 원소가 L 미만 중 최대 값
                    else{
                        it--;
                        cout << it->second << "\n";
                    }
                }
            }
        }
        else if(str == "add"){
            int p, l, g;
            cin >> p >> l >> g;
            s.insert({l, p});
            sg[g].insert({l, p});
            um[p] = {l, g};
        }

        else if(str == "solved"){
            int p;
            cin >> p;
            auto it = um.find(p);
            if(it == um.end())
                continue;
            int l = it->second.first;
            int g = it->second.second;
            s.erase({l, p});
            sg[g].erase({l, p});
            um.erase(it);
        }
    }


    return 0;
}
