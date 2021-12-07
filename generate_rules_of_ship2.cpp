#include <time.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

const string fstr = "rule \"rule1\"\n\tdialect \"mvel\"\n\twhen\n";
const string mstr = "\tthen\n";
const string lstr = "end\n//note:when ";
const string tstr = "\t\t";
const string cstr = " : ";
const string cmstr = ", ";
const string andstr = "and ";
const string thenstr = "then set ";
const string asstr = "as ";
const string endstr = "\n\n";
const string tfstr[2] = {"false", "true"};
const string nlcmpstr[6] = {"is equal to",
                            "is not equal to",
                            "is greater than",
                            "is less than",
                            "is greater than or equal to",
                            "is less than or equal to"};
const string cmpstr[6] = {"==", "!=", ">", "<", ">=", "<="};
const string classes[7][72] = {
    {"ADA",
     "$aDA",
     "8",
     "",
     "",
     "",
     "",
     "",
     "bulletNum",
     "setBulletNum",
     "2",
     "100000",
     "the number of bullets of the ADA",
     "",
     "sets the number of bullets of the ADA to",
     "",
     "highSpeed",
     "setHighSpeed",
     "3",
     "4000",
     "the high rate of fire of the ADA",
     "RPM",
     "sets the high rate of fire of the ADA to",
     "",
     "isAimed",
     "setIsAimed",
     "0",
     "",
     "the ADA doesn't aim at the target",
     "the ADA aimed at the target",
     "makes the ADA not aim at the target",
     "makes the ADA aim at the target",
     "isDestroyed",
     "setIsDestroyed",
     "0",
     "",
     "the ADA isn't destroyed",
     "the ADA is destroyed",
     "keeps the ADA from being destroyed",
     "destroyed the ADA",
     "lowSpeed",
     "setLowSpeed",
     "3",
     "1000",
     "the low rate of fire of the ADA",
     "RPM",
     "sets the low rate of fire of the ADA to",
     "",
     "mediumSpeed",
     "setMediumSpeed",
     "3",
     "2000",
     "the medium rate of fire of the ADA",
     "RPM",
     "sets the medium rate of fire of the ADA to",
     "",
     "shutSpeed",
     "setShutSpeed",
     "3",
     "8000",
     "the rate of fire of the ADA",
     "RPM",
     "sets the rate of fire of the ADA to",
     "",
     "state",
     "setState",
     "1",
     "",
     "the ADA is off",
     "the ADA is on",
     "turns off the ADA",
     "turns on the ADA"},
    {"AirCraft",
     "$airCraft",
     "8",
     "",
     "",
     "",
     "",
     "",
     "bulletNum",
     "setBulletNum",
     "2",
     "10000",
     "the number of bullets of the aircraft",
     "",
     "sets the number of bullets of the aircraft to",
     "",
     "flyDirection",
     "setFlyDirection",
     "3",
     "360",
     "the direction of the aircraft",
     "°",
     "sets the direction of the aircraft to",
     "",
     "flySpeed",
     "setFlySpeed",
     "3",
     "360",
     "the speed of the aircraft",
     "km/h",
     "sets the speed of the aircraft to",
     "",
     "isArmed",
     "setIsArmed",
     "0",
     "",
     "the aircraft doesn't aim at the target",
     "the aircraft aimed at the target",
     "makes the aircraft not aim at the target",
     "makes the aircraft aim at the target",
     "isShut",
     "setIsShut",
     "0",
     "",
     "the aircraft isn't shooting",
     "the aircraft is shooting",
     "prevents the aircraft from shooting",
     "makes the aircraft shoot",
     "isTurnOn",
     "setIsTurnOn",
     "0",
     "",
     "the aircraft doesn't start",
     "the aircraft started",
     "prevents the aircraft from starting",
     "starts the aircraft",
     "isWeaponOn",
     "setIsWeaponOn",
     "0",
     "",
     "the aircraft's weapons aren't ready",
     "the aircraft's weapons are ready",
     "makes the aircraft's weapons not ready",
     "makes the aircraft's weapons ready",
     "shutSpeed",
     "setShutSpeed",
     "3",
     "1500",
     "the rate of fire of the aircraft",
     "RPM",
     "sets the rate of fire of the aircraft to",
     ""},
    {"EscapeShip", "$escapeShip", "1", "", "", "", "", "", "isOn", "setIsOn",
     "0", "", "the escape pod is closed", "the escape pod is opened",
     "closes the escape pod", "opens the escape pod"},
    {"NearGun",
     "$nearGun",
     "4",
     "",
     "",
     "",
     "",
     "",
     "bulletNum",
     "setBulletNum",
     "2",
     "1000000",
     "the number of bullets of the near gun",
     "",
     "sets the number of bullets of the near gun to",
     "",
     "isAimed",
     "setIsAimed",
     "0",
     "",
     "the near gun doesn't aim at the target",
     "the near gun aimed at the target",
     "makes the near gun not aim at the target",
     "makes the near gun aim at the target",
     "shutSpeed",
     "setShutSpeed",
     "3",
     "5000",
     "the rate of fire of the near gun",
     "RPM",
     "sets the rate of fire of the near gun to",
     "",
     "state",
     "setState",
     "1",
     "",
     "the near gun is off",
     "the near gun is on",
     "turns off the near gun",
     "turns on the near gun"},
    {"Radar",
     "$radar",
     "2",
     "",
     "",
     "",
     "",
     "",
     "isOpen",
     "setIsOpen",
     "0",
     "",
     "the radar is off",
     "the radar is on",
     "turns off the radar",
     "turns on the radar",
     "scanRadiu",
     "setScanRadiu",
     "3",
     "10000",
     "the detection radius of radar",
     "km",
     "sets the detection radius of radar to",
     ""},
    {"TorpedoSys",
     "$torpedoSys",
     "4",
     "",
     "",
     "",
     "",
     "",
     "currentNum",
     "setCurrentNum",
     "2",
     "10",
     "the current number of torpedoes",
     "",
     "sets the current number of torpedoes to",
     "",
     "isAimed",
     "setIsAimed",
     "0",
     "",
     "the torpedo doesn't aim at the target",
     "the torpedo aimed at the target",
     "makes the torpedo not aim at the target",
     "makes the torpedo aim at the target",
     "isLoaded",
     "setIsLoaded",
     "0",
     "",
     "the torpedo is not loaded into the launcher",
     "the torpedo is loaded into the launcher",
     "takes the torpedo out of the launcher",
     "loads the torpedo into the launcher",
     "isWoFang",
     "setIsWoFang",
     "0",
     "",
     "the torpedo is enemy's",
     "the torpedo is ours",
     "makes the torpedo belong to the enemy",
     "makes the torpedo belong to us"},
    {"WarShip",
     "$warShip",
     "3",
     "",
     "",
     "",
     "",
     "",
     "destroyedLevel",
     "setDestroyedLevel",
     "2",
     "10",
     "the extent of damage to the warship",
     "",
     "sets the extent of damage to the warship to",
     "",
     "isWoFang",
     "setIsWoFang",
     "0",
     "",
     "the warship is enemy's",
     "the warship is ours",
     "makes the warship belong to the enemy",
     "makes the warship belong to us",
     "shipSpeed",
     "setShipSpeed",
     "3",
     "50",
     "the speed of the warship",
     "kn",
     "sets the speed of the warship to",
     ""}};

vector<string> rules;
int amt;

bool check(string str) {
    for (auto it = rules.begin(); it != rules.end(); ++it) {
        if (*it == str) return false;
    }
    return true;
}

auto main() -> int {
    cout << "input amount:";
    cin >> amt;
    for (int i = 0; i < amt; ++i) {
        srand((unsigned)time(NULL));
        while (true) {
            string rule = fstr, note = lstr;
            int whens = rand() % 6 + 1, theone = rand() % whens, cth = 0;
            map<int, int> wwhen;
            while (wwhen.size() != whens) {
                int cls = rand() % 7, sum = stoi(classes[cls][2]);
                wwhen[cls] = sum;
            }
            for (auto it = wwhen.begin(); it != wwhen.end(); ++it) {
                int cls = it->first, sum = it->second, cdts;
                if (cth++ == theone)
                    cdts = rand() % sum + 1;
                else
                    cdts = rand() % (sum + 1);
                rule += tstr + classes[cls][1] + cstr + classes[cls][0] + "( ";
                if (!cdts)
                    rule += ")\n";
                else {
                    map<int, long long> trg;
                    while (trg.size() != cdts) {
                        int pos = (rand() % sum + 1) * 8, way;
                        if (classes[cls][pos + 2] == "0")
                            way = 0;
                        else if (classes[cls][pos + 2] == "1")
                            way = 1;
                        else
                            way = stoi(classes[cls][pos + 2]);
                        trg[pos] = way;
                    }
                    int cmcnt = cdts - 1;
                    for (auto iterator = trg.begin(); iterator != trg.end();
                         ++iterator) {
                        int pos = iterator->first, way = iterator->second;
                        string tmp = classes[cls][pos] + " ", tmpnote = "";
                        int cmpway;
                        if (!way || way == 1)
                            cmpway = 2;
                        else
                            cmpway = 6;
                        int cmpres = rand() % cmpway;
                        tmp += cmpstr[cmpres] + " ";
                        string randstr;
                        if (!way) {
                            int randres = rand() % 2;
                            randstr = tfstr[randres];
                            if ((!randres && !cmpres) || (randres && cmpres))
                                tmpnote = classes[cls][pos + 4];
                            else
                                tmpnote = classes[cls][pos + 5];
                        } else if (way == 1) {
                            int randres = rand() % 2;
                            randstr = to_string(randres);
                            if ((!randres && !cmpres) || (randres && cmpres))
                                tmpnote = classes[cls][pos + 4];
                            else
                                tmpnote = classes[cls][pos + 5];
                        } else {
                            int randres = rand() % stoi(classes[cls][pos + 3]);
                            randstr = to_string(randres);
                            tmpnote = classes[cls][pos + 4] + " ";
                            tmpnote +=
                                nlcmpstr[cmpres] + " " + to_string(randres);
                            if (classes[cls][pos + 2] != "2")
                                tmpnote += " " + classes[cls][pos + 5];
                        }
                        tmp += randstr + " ";
                        rule += tmp;
                        note += tmpnote + " ";
                        if (cmcnt) {
                            rule += cmstr;
                            note += andstr;
                            --cmcnt;
                        }
                    }
                    rule += ")\n";
                    note += andstr;
                }
            }
            note = note.substr(0, note.length() - 5);
            rule += mstr;
            note += cmstr;
            note += "then the control system ";
            while (true) {
                bool flag = false;
                srand((unsigned)time(NULL));
                for (auto it = wwhen.begin(); it != wwhen.end(); ++it) {
                    int cls = it->first, sum = it->second;
                    int thens = rand() % (sum + 1);
                    if (thens) {
                        flag = true;
                        map<int, int> acts;
                        while (acts.size() != thens) {
                            int pos = (rand() % sum + 1) * 8 + 1, way;
                            if (classes[cls][pos + 1] == "0")
                                way = 0;
                            else if (classes[cls][pos + 1] == "1")
                                way = 1;
                            else
                                way = stoi(classes[cls][pos + 1]);
                            acts[pos] = way;
                        }
                        int cmcnt = thens - 1;
                        for (auto iterator = acts.begin();
                             iterator != acts.end(); ++iterator) {
                            int pos = iterator->first, way = iterator->second;
                            rule += tstr + classes[cls][1] + "." +
                                    classes[cls][pos] + "( ";
                            string randstr;
                            if (!way) {
                                int randres = rand() % 2;
                                randstr = tfstr[randres];
                                note += classes[cls][pos + 5 + randres];
                            } else if (way == 1) {
                                int randres = rand() % 2;
                                randstr = to_string(randres);
                                note += classes[cls][pos + 5 + randres];
                            } else {
                                int randres =
                                    rand() % stoi(classes[cls][pos + 2]);
                                randstr = to_string(randres);
                                note += classes[cls][pos + 5] + " " +
                                        to_string(randres);
                                if (classes[cls][pos + 1] != "2")
                                    note += " " + classes[cls][pos + 4];
                            }
                            rule += randstr + " );\n";
                            note += " " + andstr;
                        }
                    }
                }
                if (flag) break;
            }
            note = note.substr(0, note.length() - 5);
            note += ".";
            note += endstr;
            rule += note;
            if (rules.empty() || check(rule)) {
                rules.push_back(rule);
                cout << "size:" << rules.size() << endl;
                break;
            }
        }
    }
    ofstream ofs;
    ofs.open("smartShip" + to_string(amt) + ".drl", ios::out);
    for (auto it = rules.begin(); it != rules.end(); ++it) ofs << *it;
    ofs.close();
    system("pause");
    return 0;
}