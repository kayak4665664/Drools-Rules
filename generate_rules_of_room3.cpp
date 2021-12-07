#include <time.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

const string fstr = "rule \"rule2\"\n\tdialect \"mvel\"\n\twhen\n";
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
const string oastr[2] = {"or", "and"};
const string cmpstr[6] = {"==", "!=", ">", "<", ">=", "<="};
const string nlcmpstr[6] = {"is equal to",
                            "is not equal to",
                            "is greater than",
                            "is less than",
                            "is greater than or equal to",
                            "is less than or equal to"};
const string nlpeo[4] = {"then we", "then the administrator",
                         "then the student", "then the teacher"};
const string classes[9][72] = {
    {"AirConditionor",
     "$airConditionor",
     "3",
     "",
     "",
     "",
     "",
     "",
     "",
     "isOn",
     "setIsOn",
     "0",
     "the air conditioner is turned off",
     "the air conditioner is turned on",
     "turn off the air conditioner",
     "turn on the air conditioner",
     "turns off the air conditioner",
     "turns on the air conditioner",
     "state",
     "setState",
     "1",
     "the mode of the air conditioner is cooling",
     "the mode of the air conditioner is heating",
     "set the mode of the air conditioner to cooling",
     "set the mode of the air conditioner to heating",
     "sets the mode of the air conditioner to cooling",
     "sets the mode of the air conditioner to heating",
     "air_temperature",
     "setAir_temperature",
     "3",
     "the temperature of air conditioner",
     "°C",
     "set the temperature of the air conditioner to",
     "sets the temperature of the air conditioner to",
     "",
     ""},
    {"AirHumidifier",
     "$airHumidifier",
     "2",
     "",
     "",
     "",
     "",
     "",
     "",
     "isOn",
     "setIsOn",
     "1",
     "the air humidifier is turned off",
     "the air humidifier is turned on",
     "turn off the air humidifier",
     "turn on the air humidifier",
     "turns off the air humidifier",
     "turns on the air humidifier",
     "humidity",
     "set_Humidity",
     "3",
     "the humidity of air humidifier",
     "gal/day",
     "set the humidity of the air humidifier to",
     "sets the humidity of the air humidifier to",
     "",
     ""},
    {"Demonstrator", "$demonstrator", "1", "", "", "", "", "", "", "state",
     "setState", "0", "the demonstrator isn't in the room",
     "the demonstrator is in the room", "get the demonstrator out of the room",
     "get the demonstrator into the room",
     "gets the demonstrator out of the room",
     "gets the demonstrator into the room"},
    {"Environ",
     "$environ",
     "7",
     "",
     "",
     "",
     "",
     "",
     "",
     "innerTemperature",
     "setInnerTemperature",
     "3",
     "the indoor temperature",
     "°C",
     "set the indoor temperature to",
     "sets the indoor temperature to",
     "",
     "",
     "innerHumidity",
     "setInnerHumidity",
     "3",
     "the indoor humidity",
     "%",
     "set the indoor humidity to",
     "sets the indoor humidity to",
     "",
     "",
     "innerLightRay",
     "setInnerLightRay",
     "3",
     "the indoor light intensity",
     "lx",
     "set the indoor light intensity to",
     "sets the indoor light intensity to",
     "",
     "",
     "outerTemperature",
     "setOuterTemperature",
     "3",
     "the outdoor temperature",
     "°C",
     "set the outdoor temperature to",
     "sets the outdoor temperature to",
     "",
     "",
     "outerHumidity",
     "setOuterHumidity",
     "3",
     "the outdoor humidity",
     "%",
     "set the outdoor humidity to",
     "sets the outdoor humidity to",
     "",
     "",
     "outerLightRay",
     "setOuterLightRay",
     "3",
     "the outdoor light intensity",
     "lx",
     "set the outdoor light intensity to",
     "sets the outdoor light intensity to",
     "",
     "",
     "peopleNum",
     "setPeopleNum",
     "2",
     "the number of people",
     "",
     "set the number of people to",
     "sets the number of people to",
     "",
     ""},
    {"Light", "$light", "1", "", "", "", "", "", "", "state", "setState", "1",
     "the light is turned off", "the light is turned on", "turn off the light",
     "turn on the light", "turns off the light", "turns on the light"},
    {"MicroPhone",
     "$microPhone",
     "2",
     "",
     "",
     "",
     "",
     "",
     "",
     "isOn",
     "setIsOn",
     "1",
     "the microphone is turned off",
     "the microphone is turned on",
     "turn off the microphone",
     "turn on the microphone",
     "turns off the microphone",
     "turns on the microphone",
     "volumn",
     "setVolumn",
     "3",
     "the volume of microphone",
     "dB",
     "set the volume of microphone to",
     "sets the volume of microphone to",
     "",
     ""},
    {"Projector", "$projector", "1", "", "", "", "", "", "", "isOn", "setIsOn",
     "0", "the projector is turned off", "the projector is turned on",
     "turn off the projector", "turn on the projector",
     "turns off the projector", "turns on the projector"},
    {"Speaker", "$speaker", "1", "", "", "", "", "", "", "state", "setState",
     "0", "the speaker isn't in the room", "the speaker is in the room",
     "get the speaker out of the room", "get the speaker into the room",
     "gets the speaker out of the room", "gets the speaker into the room"},
    {"XiaoMing", "$xiaoMing", "1", "", "", "", "", "", "", "state", "setState",
     "0", "XiaoMing isn't in the room", "XiaoMing is in the room",
     "get XiaoMing out of the room", "get XiaoMing into the room",
     "gets XiaoMing out of the room", "gets XiaoMing into the room"}};

vector<string> rules;
int amt;

bool check(string str) {
    for (auto it = rules.begin(); it != rules.end(); ++it) {
        if (*it == str) return false;
    }
    return true;
}

struct members {
    int sum, when_sum, then_sum, ooa;
};

struct lrbs {
    int num, cnt, lor, tf;
};

int ttttt = 0;

auto main() -> int {
    cout << "input amount:";
    cin >> amt;
    for (int i = rules.size(); i < amt; i = rules.size()) {
        bool cntpeo = false;
        srand((unsigned)time(NULL));
        while (true) {
            string rule = fstr, note = lstr;
            int whens = rand() % 3 + 4, theone = rand() % whens, cth = 0;
            map<int, members> wwhen;
            while (wwhen.size() != whens) {
                int cls = rand() % 9, sum = stoi(classes[cls][2]);
                wwhen[cls].sum = sum;
            }
            int bcnt = 0, pcnt = 0, nn = 0;
            lrbs bs[100];
            memset(bs, 0, sizeof(bs));
            for (auto it = wwhen.begin(); it != wwhen.end(); ++it) {
                ++pcnt;
                if (pcnt == wwhen.size()) {
                    while (bcnt) {
                        bs[nn].num = bcnt--;
                        bs[nn].cnt = pcnt;
                        bs[nn].lor = 1;
                        bs[nn++].tf = 1;
                    }
                    break;
                }
                if (bcnt < wwhen.size() - pcnt) {
                    int rd = rand() % (wwhen.size() - pcnt - bcnt);
                    for (int i = 0; i < rd; ++i) {
                        bs[nn].num = ++bcnt;
                        bs[nn].cnt = pcnt;
                        bs[nn].lor = 0;
                        bs[nn++].tf = 1;
                    }
                } else {
                    int rd = rand() % (bcnt + 1);
                    for (int i = 0; i < rd; ++i) {
                        bs[nn].num = bcnt--;
                        bs[nn].cnt = pcnt;
                        bs[nn].lor = 1;
                        bs[nn++].tf = 1;
                    }
                }
            }
            for (int i = 0, j = nn - 1; i < nn / 2; ++i, --j) {
                if (bs[i].num == bs[j].num && bs[i].lor == 0 &&
                    bs[j].lor == 1 && bs[i].tf && bs[j].tf) {
                    if (bs[i + 1].num == bs[j - 1].num &&
                        bs[i + 1].cnt == bs[i].cnt &&
                        bs[j - 1].cnt == bs[j].cnt && bs[i + 1].lor == 0 &&
                        bs[j - 1].lor == 1 && bs[i + 1].tf && bs[j - 1].tf) {
                        bs[i].tf = 0;
                        bs[j].tf = 0;
                    }
                }
                if (bs[i].cnt == 1 && bs[j].cnt == wwhen.size() &&
                    bs[i].num == bs[j].num) {
                    bs[i].tf = 0;
                    bs[j].tf = 0;
                }
            }
            bool cmpe = false, cmb = false;
            for (auto it = wwhen.begin(); it != wwhen.end(); ++it) {
                if (it->first != 2 && it->first != 7 && it->first != 8) {
                    cmpe = true;
                    break;
                }
            }
            for (int i = 0; i < nn; ++i) {
                if (bs[i].tf) {
                    cmb = true;
                    break;
                }
            }
            if (!cmpe || !cmb) cntpeo = true;
            if (!cntpeo) {
                for (auto it = wwhen.begin(); it != wwhen.end(); ++it) {
                    it->second.then_sum = rand() % (it->second.sum + 1);
                    it->second.ooa = rand() % 2;
                }
                for (auto it = wwhen.begin(); it != wwhen.end(); ++it) {
                    if ((it->first != 2 && it->first != 7 && it->first != 8) &&
                        it->second.then_sum == 0) {
                        ++it->second.then_sum;
                        break;
                    }
                }              /*
                              for (auto it = wwhen.begin(); it != wwhen.end(); ++it) {
                                  if (it->second.ooa == 1) {
                                      it->second.ooa = 0;
                                      break;
                                  }
                              }*/
                rule += tstr;  // + "( ";
                int wwhen_cnt = 0, bspos = 0, pppos = 0;
                for (auto it = wwhen.begin(); it != wwhen.end(); ++it) {
                    ++wwhen_cnt;
                    ++pppos;
                    int cls = it->first, sum = it->second.sum, cdts; /*
                     if (cth++ == theone)
                         it->second.when_sum = rand() % sum + 1;
                     else
                         it->second.when_sum = rand() % (sum + 1);*/
                    it->second.when_sum = 1;
                    if (cls == 2 || cls == 7 || cls == 8) {
                        it->second.then_sum = 0;
                        // if (it->second.when_sum == 0) ++it->second.when_sum;
                    } /*else if (it->second.when_sum == 0 &&
                               it->second.then_sum == 0)
                        it->second.then_sum = rand() % sum + 1;*/
                    cdts = it->second.when_sum;
                    // rule += tstr;
                    // if (it->second.then_sum) rule += classes[cls][1] + cstr;
                    for (int i = 0; i < nn; ++i) {
                        if (bs[i].cnt == pppos && bs[i].lor == 0 && bs[i].tf) {
                            rule += "( ";
                            note += "( ";
                        }
                    }
                    rule += classes[cls][0] + "( "; /*
                     if (!cdts)
                         rule += ")\n";*/
                    // else {
                    map<int, int> trg;
                    while (trg.size() != cdts) {
                        int pos = (rand() % sum + 1) * 9, way;
                        if (classes[cls][pos + 2] == "0")
                            way = 0;
                        else if (classes[cls][pos + 2] == "1")
                            way = 1;
                        else
                            way = 2;
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
                        if (way == 0 || way == 1) cmpres = 0;
                        tmp += cmpstr[cmpres] + " ";
                        string randstr;
                        if (!way) {
                            int randres = rand() % 2;
                            randstr = tfstr[randres];
                            if ((!randres && !cmpres) || (randres && cmpres))
                                tmpnote = classes[cls][pos + 3];
                            else
                                tmpnote = classes[cls][pos + 4];
                        } else if (way == 1) {
                            int randres = rand() % 2;
                            randstr = to_string(randres);
                            if ((!randres && !cmpres) || (randres && cmpres))
                                tmpnote = classes[cls][pos + 3];
                            else
                                tmpnote = classes[cls][pos + 4];
                        } else {
                            int randres = rand() % 35;
                            randstr = to_string(randres);
                            tmpnote = classes[cls][pos + 3] + " ";
                            tmpnote +=
                                nlcmpstr[cmpres] + " " + to_string(randres);
                            if (classes[cls][pos + 2] != "2")
                                tmpnote += " " + classes[cls][pos + 4];
                        }
                        tmp += randstr + " ";
                        rule += tmp;
                        note += tmpnote + " ";
                        /*if (cmcnt) {
                            rule += cmstr;
                            note += andstr;
                            --cmcnt;
                        }*/
                    }
                    /*    rule += ")\n";
                        note += andstr;*/
                    //}
                    rule += ") ";
                    for (int i = 0; i < nn; ++i) {
                        if (bs[i].cnt == pppos && bs[i].lor == 1 && bs[i].tf) {
                            rule += ") ";
                            note += ") ";
                        }
                    }
                    if (wwhen_cnt != wwhen.size()) {
                        rule += oastr[it->second.ooa] + ' ';
                        note += oastr[it->second.ooa] + ' ';
                    }
                }
                rule = rule.substr(0, rule.length() - 1);
                note = note.substr(0, note.length() - 1);
                rule += "\n";
                for (auto it = wwhen.begin(); it != wwhen.end(); ++it) {
                    if (it->second.then_sum) {
                        rule += tstr;
                        rule += classes[it->first][1] + cstr;
                        rule += classes[it->first][0] + "( )\n";
                    }
                }
                rule += mstr;
                note += cmstr;
                int randpeores = rand() % 4;
                note += nlpeo[randpeores] + " ";
                while (true) {
                    bool flag = false;
                    srand((unsigned)time(NULL));
                    for (auto it = wwhen.begin(); it != wwhen.end(); ++it) {
                        int cls = it->first, sum = it->second.sum;
                        int thens = it->second.then_sum;
                        if ((cls == 2 || cls == 7 || cls == 8) && thens)
                            continue;
                        if (thens) {
                            flag = true;
                            map<int, int> acts;
                            while (acts.size() != thens) {
                                int pos = (rand() % sum + 1) * 9 + 1, way;
                                if (classes[cls][pos + 1] == "0")
                                    way = 0;
                                else if (classes[cls][pos + 1] == "1")
                                    way = 1;
                                else
                                    way = 2;
                                acts[pos] = way;
                            }
                            int cmcnt = thens - 1;
                            for (auto iterator = acts.begin();
                                 iterator != acts.end(); ++iterator) {
                                int pos = iterator->first,
                                    way = iterator->second;
                                rule += tstr + classes[cls][1] + "." +
                                        classes[cls][pos] + "( ";
                                string randstr;
                                if (!way) {
                                    int randres = rand() % 2;
                                    randstr = tfstr[randres];
                                    note += classes[cls][pos + 4 +
                                                         (randpeores ? 2 : 0) +
                                                         randres];
                                } else if (way == 1) {
                                    int randres = rand() % 2;
                                    randstr = to_string(randres);
                                    note += classes[cls][pos + 4 +
                                                         (randpeores ? 2 : 0) +
                                                         randres];
                                } else {
                                    int randres = rand() % 35;
                                    randstr = to_string(randres);
                                    note += classes[cls][pos + 4 +
                                                         (randpeores ? 1 : 0)] +
                                            " " + to_string(randres);
                                    if (classes[cls][pos + 1] != "2")
                                        note += " " + classes[cls][pos + 3];
                                }
                                rule += randstr + " );\n";
                                note += " " + andstr;
                            }
                        }
                    }
                    if (flag) break;
                }
                for (auto it = wwhen.begin(); it != wwhen.end(); ++it) {
                    if (it->second.then_sum)
                        rule +=
                            tstr + "update( " + classes[it->first][1] + " );\n";
                }
                note = note.substr(0, note.length() - 5);
                note += ".";
                note += endstr;
                rule += note;
            }
            if (cntpeo) break;
            if (rules.empty() || check(rule)) {
                rules.push_back(rule);
                cout << "size:" << rules.size() << endl;
                break;
            }
        }
    }
    ofstream ofs;
    ofs.open("smartRoom_1or" + to_string(amt) + ".drl", ios::out);
    for (auto it = rules.begin(); it != rules.end(); ++it) ofs << *it;
    ofs.close();
    system("pause");
    return 0;
}