#include <iostream>
#include <fstream>
#include <stack>
#include <set>
#include <list>
#include <map>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <sstream>

struct beacon {
    int pos[3];
};

struct shuffle {
    int sh;
    int inv[3];
    
    shuffle() {
        sh = -1;
    }
    
    shuffle(int x, int y, int z) {
        int u[3] = {x, y, z};
        int s[3] = {abs(x), abs(y), abs(z)};

        for (int i = 0; i < 3; i++) {
            inv[i] = (u[i] == 0) ? 0 : (u[i] / s[i]);
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    if (s[i] < s[j] && s[j] < s[k]) {
                        sh = (i<<4) + (j<<2) + k;

                        int a[3] = {inv[0], inv[1], inv[2]};
                        inv[0] = a[i];
                        inv[1] = a[j];
                        inv[2] = a[k];

                        return;
                    }
                }
            }
        }
        
        sh = -1;
    }
};

struct ribp {
    int bl;
    int br;
    
    int diff[3];
    
    shuffle s;

    ribp(int bl, int br, int a, int b, int c) : bl(bl), br(br) {
        s = shuffle(a, b, c);

        diff[0] = abs(a);
        diff[1] = abs(b);
        diff[2] = abs(c);

        std::sort(&diff[0], &diff[3]);
    }
    
    friend bool operator==(const ribp& first, const ribp& second) {
        return first.diff[0] == second.diff[0] && first.diff[1] == second.diff[1] && first.diff[2] == second.diff[2];
    }
    
    friend bool operator<(const ribp& first, const ribp& second) {
        if (first.diff[0] < second.diff[0]) {
            return true;
        } else if (first.diff[0] == second.diff[0]) {
            if (first.diff[1] < second.diff[1]) {
                return true;
            } else if (first.diff[1] == second.diff[1]) {
                return first.diff[2] < second.diff[2];
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
};

struct scanner {
    std::vector<beacon> beacons;
    std::list<ribp> keypoints;

    int pos[3] = {};    

    int toShuffle[3][3] = {};

    void shuffle() {
        int shuffles[3] = {0, 1, 2};
        for (int i = 0; i < 3; i++) {
            int max = 0;
            int key = i;
            for (int j = 0; j < 3; j++) {
                if (toShuffle[i][j] > max) {
                    max = toShuffle[i][j];
                    key = j;
                }
            }
            shuffles[i] = key;
        }
        if (!(shuffles[0] == 0 && shuffles[1] == 1 && shuffles[2] == 2)) {
            std::cout << "Do shuffle!" << std::endl;
            for (auto& i : beacons) {
                int t[3] = {i.pos[0], i.pos[1], i.pos[2]};
                i.pos[0] = t[shuffles[0]];
                i.pos[1] = t[shuffles[1]];
                i.pos[2] = t[shuffles[2]];
            }
        }
    }
};

bool keypoints(scanner& first, scanner& second) {
    std::vector<ribp> result;
    std::list<ribp>::const_iterator i = first.keypoints.begin();
    std::list<ribp>::iterator j = second.keypoints.begin();
    
    std::map<int, std::map<int, std::pair<int, int>>> counters;
    std::map<std::pair<int, int>, std::array<int, 3>> toInvert;
    std::set<int> matches;

    while (i != first.keypoints.end() && j != second.keypoints.end()) {
        const ribp& one = (*i);
        ribp& two = (*j);
        
        if (one == two) {
            // std::cout << "Match gevonden first!  " << one.bl << " en " << one.br << std::endl;
            // std::cout << "Match gevonden second!  " << two.bl << " en " << two.br << std::endl;
            counters[one.bl][two.bl].first++;
            counters[one.bl][two.br].first++;
            counters[one.br][two.bl].first++;
            counters[one.br][two.br].first++;
            
            // counters[one.bl][two.br].second++;
            // counters[one.br][two.br].second++;

            if (one.s.sh >= 0 && two.s.sh >= 0) {
                for (int i = 4; i >= 0; i -= 2) {
                    int f = ((one.s.sh>>i)&3);
                    int g = ((two.s.sh>>i)&3);
                    second.toShuffle[f][g]++;
                }
            }

            if (one.s.inv[0] && one.s.inv[1] && one.s.inv[2] && two.s.inv[0] && two.s.inv[1] && two.s.inv[2]) {
                for (int i = 0; i < 3; i++) {
                    if (one.s.inv[i] != two.s.inv[i]) {
                        int in = two.s.sh>>(4 - (2*i)) & 3;
                        toInvert[{one.bl, two.bl}][in]++;
                        toInvert[{one.bl, two.br}][in]--;
                        toInvert[{one.br, two.bl}][in]--;
                        toInvert[{one.br, two.br}][in]++;
                    }
                }
            }

            // std::cout << (one.s.sh >> 4) << "," << ((one.s.sh >> 2) & 3) << "," << (one.s.sh & 3) << ": ";
            // for (int k = 0; k < 3; k++) {
            //     std::cout << first.beacons[one.bl].pos[k] - first.beacons[one.br].pos[k] << "  ,  ";
            // }
            // std::cout << std::endl;
            // std::cout << (two.s.sh >> 4) << "," << ((two.s.sh >> 2) & 3) << "," << (two.s.sh & 3) << ": ";
            // for (int k = 0; k < 3; k++) {
            //     std::cout << second.beacons[two.bl].pos[k] - second.beacons[two.br].pos[k] << "  ,  ";
            // }
            // std::cout << std::endl;

            i++; j++;
        } else if (one < two) {
            i++;
        } else {
            j++;
        }
    }
    
    int inverted[3] = {};
    int translate[3][2] = {};

    for (auto& i : counters) {
        int hkey = 0, hval = 0, secondlargestVal = 0;
        for (auto& j : i.second) {
            if (j.second.first >= hval) {
                hkey = j.first;
                secondlargestVal = hval;
                hval = j.second.first;
            } else if (j.second.first >= secondlargestVal) {
                secondlargestVal = j.second.first;
            }
        }
        if (hval > secondlargestVal && secondlargestVal <= 1) {
            matches.insert(hkey);
            for (int j = 0; j < 3; j++) {
                inverted[j] += toInvert[{i.first, hkey}][j];
            }
        }
    }
    
    for (int i = 0; i < 3; i++) {
        std::cout << "xyz"[i] << " inverted: " << inverted[i] << std::endl << std::endl;
    }
    
    if (abs(inverted[0]) < 2 || abs(inverted[1]) < 2 || abs(inverted[2]) < 2) {
        return false;
    }
    
    std::cout << "INVERTEREN!" << std::endl;
    for (auto& i : second.beacons) {
        for (int j = 0; j < 3; j++) {
            i.pos[j] *= inverted[j] > 0 ? -1 : 1;
        }
    }
    
    std::cout << "SHUFFELEN!" << std::endl;
    second.shuffle();

    for (auto& i : counters) {
        int hkey = 0, hval = 0, secondlargestVal = 0;
        for (auto& j : i.second) {
            if (j.second.first >= hval) {
                hkey = j.first;
                secondlargestVal = hval;
                hval = j.second.first;
            } else if (j.second.first >= secondlargestVal) {
                secondlargestVal = j.second.first;
            }
        }
        if (hval > secondlargestVal) {
            std::cout << "Beacon " << i.first << " identifies to: " << hkey << " (" << hval << "/" << secondlargestVal << ")" << std::endl;
            matches.insert(hkey);
            for (int j = 0; j < 3; j++) {
                translate[j][0] = first.beacons[i.first].pos[j] - second.beacons[hkey].pos[j];
                translate[j][1] = first.beacons[i.first].pos[j] + second.beacons[hkey].pos[j];
            }
            // std::cout << "x: " << first.beacons[i.first].pos[0] << " y: " << first.beacons[i.first].pos[1] << " z: " << first.beacons[i.first].pos[2] << std::endl;
            std::cout << "x: " << first.beacons[i.first].pos[0] - second.beacons[hkey].pos[0] << " y: " << first.beacons[i.first].pos[1] - second.beacons[hkey].pos[1] << " z: " << first.beacons[i.first].pos[2] - second.beacons[hkey].pos[2] << std::endl;
        }
    }
    
    std::cout << "TRANSLEREN!" << std::endl;
    for (int j = 0; j < 3; j++) {
        std::cout << "xyz"[j] << " " << translate[j][0] << " ";
        second.pos[j] = translate[j][0];
    }
    std::cout << std::endl;

    for (auto& i : second.beacons) {
        for (int j = 0; j < 3; j++) {
            i.pos[j] += translate[j][0];
        }
    }

    std::cout << "MOVEN!" << std::endl;
    if (!matches.empty()) {
        for (int i = 0; i < second.beacons.size(); i++) {
            if (!matches.contains(i)) {
                first.beacons.push_back(second.beacons[i]);
            }
        }
        first.keypoints.clear();
        for (int i = 0; i < first.beacons.size(); i++) {
            for (int j = i + 1; j < first.beacons.size(); j++) {
                int d1 = first.beacons[i].pos[0] - first.beacons[j].pos[0];
                int d2 = first.beacons[i].pos[1] - first.beacons[j].pos[1];
                int d3 = first.beacons[i].pos[2] - first.beacons[j].pos[2];
                    
                first.keypoints.push_back(ribp(i, j, d1, d2, d3));
            }
        }
        first.keypoints.sort();
        return true;
    }
    return false;
}

int main(void){
    std::ifstream infile("File29");
    
    std::string line;
    std::vector<scanner> scanners;

    scanner* sc;
    bool eof;
    while ((eof = infile.eof()) || std::getline(infile, line)) {
        if (!eof && !line.compare(0, 3, "---")) {
            // scanner
            std::cout << line << std::endl;

            scanners.push_back({});
            sc = &scanners.back();
        } else {
            std::istringstream iss(line);
            int a, b, c;
            char d;
            if (!eof && iss >> a >> d >> b >> d >> c) {
                sc->beacons.push_back({a, b, c});
            } else {
                std::cout << "EINDE!" << sc->beacons.size() << std::endl;
                
                for (int i = 0; i < sc->beacons.size(); i++) {
                    for (int j = i + 1; j < sc->beacons.size(); j++) {
                        int d1 = sc->beacons[i].pos[0] - sc->beacons[j].pos[0];
                        int d2 = sc->beacons[i].pos[1] - sc->beacons[j].pos[1];
                        int d3 = sc->beacons[i].pos[2] - sc->beacons[j].pos[2];
                        
                        sc->keypoints.push_back(ribp(i, j, d1, d2, d3));
                    }
                }
                sc->keypoints.sort();
                if (eof) {
                    break;
                }
            }
        }
    }
    
    std::vector<scanner*> todo;
    for (int i = 1; i < scanners.size(); i++) {
        std::cout << "Toevoegen scanner: " << i << std::endl; // 36: x: -3547 y: 0 z: -79 -> x inverted == 0 !!!
        if (!keypoints(scanners[0], scanners[i])) {
            todo.push_back(&scanners[i]);
        }
    }
    while(!todo.empty()) {
        scanner* sc = todo.front(); todo.erase(todo.begin());
        if (!keypoints(scanners[0], *sc)) {
            todo.push_back(sc);
        }
    }

    std::sort(scanners[0].beacons.begin(), scanners[0].beacons.end(), [](beacon& b1, beacon& b2) {
        return b1.pos[0] < b2.pos[0];
    });
    
    for (auto& i : scanners[0].beacons) {
        std::cout << i.pos[0] << "," << i.pos[1] << "," << i.pos[2] << std::endl;
    }
    
    int result = 0;
    for (int i = 0; i < scanners.size(); i++) {
        for (int j = i + 1; j < scanners.size(); j++) {
            int dist = 0;
            for (int k = 0; k < 3; k++) {
                dist += abs(scanners[i].pos[k] - scanners[j].pos[k]);
            }
            result = result < dist ? dist : result;
        }
    }

    std::cout << "Het resultaat: " << result;
    // std::cout << scanners[0].beacons.size();
}


