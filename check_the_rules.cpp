#include <time.h>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

string repfn = "cmp", stdline, cmpline;
ifstream stdfs, cmpfs;
ofstream report;
int cnt, dif;
float sum_score;
auto t = time(NULL);
char ch[64];
bool room_or_ship, cmpvalues;
int mode;
short int IsTrue[128];
bool getTrue[128][7];
int loc;
bool state[27];

void set_getTrue() {
    for (int i = 0; i < 128; i++) {
        for (int j = 0; j < 7; j++) {
            getTrue[i][j] = 0;
        }
    }
}

int mi(int n) {
    int k = 1;
    for (int i = 0; i < n; i++) {
        k = k * 2;
    }
    return k;
}

template <class T>
class Stack {
   private:
    int top;
    int maxnum;
    T* st;

   public:
    Stack() {
        maxnum = 20;
        top = -1;
        st = new T[20];
    }
    ~Stack() { delete[] st; }
    void clean() { top = -1; }
    void push(T n) {
        top++;
        this->st[top] = n;
    }
    T get_top() {
        int k = st[top];
        top--;
        return k;
    }
    T read_top() { return st[this->top]; }
    bool IsEmpty() {
        if (this->top == -1) return true;
        return false;
    }
    bool IsFull() {
        if (top + 1 == maxnum) return true;
        return false;
    }
};

class Calculator {
   private:
    char InfixExp[30];
    char PostfixExp[30];

   public:
    Calculator(char* exp);
    void getinf();
    void getpost();
    void ans(int nn);
    void trans();
};

void Calculator::getinf() { cout << InfixExp << endl; }

void Calculator::getpost() { cout << PostfixExp << endl; }

Calculator::Calculator(char* exp) {
    strcpy(this->InfixExp, exp);
    for (int i = 0; i < 30; i++) {
        PostfixExp[i] = '\0';
    }
}

void Calculator::trans() {
    Stack<char> save;
    int i = 0, j = 0;
    while (this->InfixExp[i] != '\0') {
        if (this->InfixExp[i] >= 65 && this->InfixExp[i] <= 90) {
            while (this->InfixExp[i] >= 65 && this->InfixExp[i] <= 90) {
                PostfixExp[j] = this->InfixExp[i];
                j++;
                i++;
            }
            // PostfixExp[j]=' '; j++;
        } else {
            if (this->InfixExp[i] == '(' || this->InfixExp[i] == ')') {
                if (this->InfixExp[i] == '(') {
                    save.push(this->InfixExp[i]);
                } else if (this->InfixExp[i] == ')') {
                    if (save.IsEmpty()) {
                        cout << "trans:WRONG!" << endl;
                        exit(0);
                    }
                    while (!save.IsEmpty() && save.read_top() != '(') {
                        PostfixExp[j] = save.get_top();
                        j++;
                    }
                    if (save.read_top() == '(') save.get_top();
                }
            } else {
                if (save.IsEmpty()) {
                    save.push(this->InfixExp[i]);
                } else {
                    if (this->InfixExp[i] == '!') {
                        char temp = save.read_top();
                        while (temp == '!' && temp != '(' && !save.IsEmpty()) {
                            PostfixExp[j] = save.get_top();
                            j++;
                            temp = save.read_top();
                        }
                        save.push(this->InfixExp[i]);
                    } else if (this->InfixExp[i] == '*') {
                        char temp = save.read_top();
                        while (temp != '+' && temp != '(' && !save.IsEmpty()) {
                            PostfixExp[j] = save.get_top();
                            j++;
                            temp = save.read_top();
                        }
                        save.push(this->InfixExp[i]);
                    } else if (this->InfixExp[i] == '+') {
                        char temp = save.read_top();
                        while ((temp == '*' || temp == '!') &&
                               !save.IsEmpty()) {
                            PostfixExp[j] = save.get_top();
                            j++;
                            temp = save.read_top();
                        }
                        save.push(this->InfixExp[i]);
                    } else if (this->InfixExp[i] == '@') {
                        char temp = save.read_top();
                        while ((temp == '*' || temp == '!' || temp == '+') &&
                               !save.IsEmpty()) {
                            PostfixExp[j] = save.get_top();
                            j++;
                            temp = save.read_top();
                        }
                        save.push(this->InfixExp[i]);
                    } else if (this->InfixExp[i] == '$') {
                        char temp = save.read_top();
                        while ((temp == '*' || temp == '!' || temp == '+' ||
                                temp == '@') &&
                               !save.IsEmpty()) {
                            PostfixExp[j] = save.get_top();
                            j++;
                            temp = save.read_top();
                        }
                        save.push(this->InfixExp[i]);
                    }
                }
            }
            i++;
        }
    }
    while (!save.IsEmpty()) {
        PostfixExp[j] = save.get_top();
        j++;
    }
    PostfixExp[j] = '\0';
}

void Calculator::ans(int nn) {
    Stack<int> save_num;
    int i = 0, j = 0;
    int n1 = 0, n2 = 0;
    i = 0;
    while (this->PostfixExp[i] != '\0') {
        if (this->PostfixExp[i] >= 65 && this->PostfixExp[i] <= 90) {
            int temp = 0;
            temp = getTrue[loc][this->PostfixExp[i] - 65];
            i++;
            save_num.push(temp);
        } else if (this->PostfixExp[i] == '!') {
            n1 = save_num.get_top();
            n1 = 1 - n1;
            save_num.push(n1);
            i++;
        } else if (this->PostfixExp[i] == '+' || this->PostfixExp[i] == '*' ||
                   this->PostfixExp[i] == '@' || this->PostfixExp[i] == '$') {
            n2 = save_num.get_top();
            n1 = save_num.get_top();
            switch (this->PostfixExp[i]) {
                case ('+'):
                    n1 += n2;
                    save_num.push(n1);
                    break;
                case ('*'):
                    n1 *= n2;
                    save_num.push(n1);
                    break;
                case ('@'):
                    if (n1 > 0 && n2 == 0)
                        n1 = 0;
                    else
                        n1 = 1;
                    save_num.push(n1);
                    break;
                case ('$'):
                    if ((n1 + n2 > 0) && (n1 * n2 == 0))
                        n1 = 0;
                    else
                        n1 = 1;
                    save_num.push(n1);
                    break;
            }
            i++;
        } else {
            i++;
        }
    }
    if (save_num.read_top() > 0)
        IsTrue[loc] = 1;
    else
        IsTrue[loc] = 0;
}

string printxiqu(int num, int m) {
    int i, j;
    int temp = m;
    string anse = "";
    for (; temp > 0 && !IsTrue[temp]; temp--) m = temp;
    for (i = 0; i < m - 1; i++) {
        if (IsTrue[i] == 1) {
            anse += '(';
            for (j = 0; j < num - 1; j++) {
                if (getTrue[i][j] == 0) anse += "!";
                anse += (char)(j + 65);
                anse += "*";
            }
            if (getTrue[i][num - 1] == 0) anse += "!";
            anse += (char)(j + 65);
            anse += ')';
            anse += "+";
        }
    }
    i = m - 1;
    if (IsTrue[i] == 1) {
        anse += '(';
        for (j = 0; j < num - 1; j++) {
            if (getTrue[i][j] == 0) anse += "!";
            anse += (char)(j + 65);
            anse += "*";
        }
        if (getTrue[i][num - 1] == 0) anse += "!";
        anse += (char)(j + 65);
        anse += ')';
    }
    return anse;
}

string get_xiqufanshi(int sum, string mingti) {
    loc = 0;
    for (int i = 0; i < 27; i++) state[i] = 0;
    for (int i = 0; i < 128; i++) IsTrue[i] = -1;
    set_getTrue();
    int i, j, k, m = 1;
    int num = sum;
    for (i = 0; i < num; i++) m = m * 2;
    char exp[100];
    for (int i = 0; i < mingti.size(); ++i) exp[i] = mingti[i];
    exp[mingti.size()] = '\0';
    Calculator cal(exp);
    cal.trans();
    // cal.getpost();
    for (i = 0; i < m; i++) {
        int temp = i, tt = 0;
        for (j = 0; j < num - 1; j++) {
            tt = mi(num - 1 - j);
            state[j] = temp / tt;
            temp = temp % tt;
        }
        state[num - 1] = temp;
        for (int k = 0; k < num; k++) {
            getTrue[i][k] = state[k];
        }
    }
    for (i = 0; i < m; i++) {
        for (j = 0; j < num; j++) {
            state[j] = getTrue[i][j];
        }
    }
    for (i = 0; i < m; i++) {
        loc = i;
        cal.ans(num);
    }
    return printxiqu(num, m);
}

inline auto ros(string outstr, string a, string b) {
    while (true) {
        cout << outstr;
        string tmp;
        cin >> tmp;
        if (tmp == a || tmp == b) {
            if (tmp == a)
                return true;
            else
                return false;
        }
    }
}

inline auto cm() {
    while (true) {
        cout << "Select mode, '0': only 'and', '1': 'or' without '()', '2': 'or' with '()':";
        string tmp;
        cin >> tmp;
        if (tmp == "0" || tmp == "1" || tmp == "2") {
            if (tmp == "0")
                return 0;
            else if (tmp == "1")
                return 1;
            else
                return 2;
        }
    }
}

inline auto open_file(string outstr, ifstream& ifs) {
    while (true) {
        cout << outstr;
        string filepath;
        cin >> filepath;
        ifs.open(filepath, ios::in);
        if (!ifs)
            cout << "File does not exist!\n";
        else
            break;
    }
}

inline auto get_begin(ifstream& ifs, string& line) {
    string end = "0";
    while (getline(ifs, line)) {
        string begin = "";
        for (auto i = 0; i < line.length(); ++i) {
            if (isspace(line[i])) continue;
            for (auto j = i; j < i + 4; ++j) begin += line[j];
            if (i + 4 < line.length() && !isspace(line[i + 4]))
                begin += line[i + 4];
            break;
        }
        if (begin == "rule") return line;
    }
    return end;
}

inline auto get_start(ifstream& ifs, string& line, string& rule) {
    while (getline(ifs, line)) {
        rule += line + "\n";
        string start = "";
        for (auto ch : line) {
            if (isspace(ch)) continue;
            start += ch;
        }
        if (start == "when") return;
    }
}

inline auto get_when(ifstream& ifs, string& line, string& rule,
                     map<string, string>& variables,
                     map<string, set<string>>& classes,
                     vector<map<string, string>>& whenclasses,
                     map<string, string>& cwhenclasses, string& mingti,
                     int& sum) {
    while (getline(ifs, line)) {
        rule += line + "\n";
        string vstr = "", cstr = "", then = "";
        for (auto ch : line) {
            if (isspace(ch)) continue;
            then += ch;
        }
        if (then == "then") break;
        if (!then.length()) continue;
        auto pos = 0;
        for (; isspace(line[pos]); ++pos)
            ;
        if (mode == 0) {
            if (line.find(':') != string::npos) {
                for (; !isspace(line[pos]) && line[pos] != ':'; ++pos)
                    vstr += line[pos];
                for (; isspace(line[pos]) || line[pos] == ':'; ++pos)
                    ;
                for (; !isspace(line[pos]) && line[pos] != '('; ++pos)
                    cstr += line[pos];
                variables[vstr] = cstr;
            } else
                for (; !isspace(line[pos]) && line[pos] != '('; ++pos)
                    cstr += line[pos];
            set<string> members;
            classes[cstr] = members;
            for (; isspace(line[pos]) || line[pos] == '('; ++pos)
                ;
            if (line[pos] == ')') continue;
            while (true) {
                string tmpm = "";
                for (; isspace(line[pos]) || line[pos] == ','; ++pos)
                    ;
                for (; line[pos] != ',' && line[pos] != ')'; ++pos) {
                    if (isspace(line[pos])) continue;
                    tmpm += line[pos];
                }
                if (!room_or_ship &&
                        ((cstr == "AirConditionor" &&
                          tmpm.find("state!=") != string::npos) ||
                         ((cstr == "AirHumidifier" || cstr == "MicroPhone") &&
                          tmpm.find("isOn!=") != string::npos)) ||
                    room_or_ship && ((cstr == "ADA" || cstr == "NearGun") &&
                                     tmpm.find("state!=") != string::npos)) {
                    string tmppm =
                        "==" + to_string(!(tmpm[tmpm.length() - 1] - '0'));
                    tmpm = tmpm.substr(0, tmpm.length() - 3);
                    tmpm += tmppm;
                } else if (tmpm.find("!=false") != string::npos) {
                    tmpm = tmpm.substr(0, tmpm.length() - 7);
                    tmpm += "==true";
                } else if (tmpm.find("!=true") != string::npos) {
                    tmpm = tmpm.substr(0, tmpm.length() - 6);
                    tmpm += "==false";
                }
                if (!cmpvalues) {
                    int tmppos = tmpm.length() - 1;
                    for (; tmppos >= 0; --tmppos) {
                        if (tmpm[tmppos] == '=' || tmpm[tmppos] == '>' ||
                            tmpm[tmppos] == '<')
                            break;
                    }
                    tmpm = tmpm.substr(0, tmppos + 1);
                }
                classes[cstr].insert(tmpm);
                if (line[pos] == ')') break;
            }
        } else if (mode == 1) {
            if (line.find(':') == string::npos) {
                for (; !isspace(line[pos]) && line[pos] != '('; ++pos)
                    cstr += line[pos];
                for (; isspace(line[pos]) || line[pos] == '('; ++pos)
                    ;
                string tmpm = "";
                for (; line[pos] != ')'; ++pos) {
                    if (isspace(line[pos])) continue;
                    tmpm += line[pos];
                }
                if (!room_or_ship &&
                        ((cstr == "AirConditionor" &&
                          tmpm.find("state!=") != string::npos) ||
                         ((cstr == "AirHumidifier" || cstr == "MicroPhone") &&
                          tmpm.find("isOn!=") != string::npos)) ||
                    room_or_ship && ((cstr == "ADA" || cstr == "NearGun") &&
                                     tmpm.find("state!=") != string::npos)) {
                    string tmppm =
                        "==" + to_string(!(tmpm[tmpm.length() - 1] - '0'));
                    tmpm = tmpm.substr(0, tmpm.length() - 3);
                    tmpm += tmppm;
                } else if (tmpm.find("!=false") != string::npos) {
                    tmpm = tmpm.substr(0, tmpm.length() - 7);
                    tmpm += "==true";
                } else if (tmpm.find("!=true") != string::npos) {
                    tmpm = tmpm.substr(0, tmpm.length() - 6);
                    tmpm += "==false";
                }
                if (!cmpvalues) {
                    int tmppos = tmpm.length() - 1;
                    for (; tmppos >= 0; --tmppos) {
                        if (tmpm[tmppos] == '=' || tmpm[tmppos] == '>' ||
                            tmpm[tmppos] == '<')
                            break;
                    }
                    tmpm = tmpm.substr(0, tmppos + 1);
                }
                map<string, string> cpn;
                cpn[cstr] = tmpm;
                whenclasses.push_back(cpn);
                map<string, string>& ref = cpn;
                for (; pos < line.length() &&
                       (isspace(line[pos]) || line[pos] == ')');
                     ++pos)
                    ;
                if (pos == line.length()) continue;
                while (true) {
                    string ororand = "";
                    for (; !isspace(line[pos]); ++pos) ororand += line[pos];
                    string ncstr = "", ntmpm = "";
                    for (; isspace(line[pos]); ++pos)
                        ;
                    for (; !isspace(line[pos]) && line[pos] != '('; ++pos)
                        ncstr += line[pos];
                    for (; isspace(line[pos]) || line[pos] == '('; ++pos)
                        ;
                    for (; line[pos] != ')'; ++pos) {
                        if (isspace(line[pos])) continue;
                        ntmpm += line[pos];
                    }
                    if (!room_or_ship &&
                            ((cstr == "AirConditionor" &&
                              ntmpm.find("state!=") != string::npos) ||
                             ((cstr == "AirHumidifier" ||
                               cstr == "MicroPhone") &&
                              ntmpm.find("isOn!=") != string::npos)) ||
                        room_or_ship &&
                            ((cstr == "ADA" || cstr == "NearGun") &&
                             ntmpm.find("state!=") != string::npos)) {
                        string tmppm =
                            "==" +
                            to_string(!(ntmpm[ntmpm.length() - 1] - '0'));
                        ntmpm = ntmpm.substr(0, ntmpm.length() - 3);
                        ntmpm += tmppm;
                    } else if (ntmpm.find("!=false") != string::npos) {
                        ntmpm = ntmpm.substr(0, ntmpm.length() - 7);
                        ntmpm += "==true";
                    } else if (ntmpm.find("!=true") != string::npos) {
                        ntmpm = ntmpm.substr(0, ntmpm.length() - 6);
                        ntmpm += "==false";
                    }
                    if (!cmpvalues) {
                        int tmppos = ntmpm.length() - 1;
                        for (; tmppos >= 0; --tmppos) {
                            if (ntmpm[tmppos] == '=' || ntmpm[tmppos] == '>' ||
                                ntmpm[tmppos] == '<')
                                break;
                        }
                        ntmpm = ntmpm.substr(0, tmppos + 1);
                    }
                    if (ororand == "or") {
                        map<string, string> ncpn;
                        ncpn[ncstr] = ntmpm;
                        whenclasses.push_back(ncpn);
                        ref = ncpn;
                    } else
                        ref[ncstr] = ntmpm;
                    for (; pos < line.length() &&
                           (isspace(line[pos]) || line[pos] == ')');
                         ++pos)
                        ;
                    if (pos == line.length()) break;
                }
            } else {
                for (; !isspace(line[pos]) && line[pos] != ':'; ++pos)
                    vstr += line[pos];
                for (; isspace(line[pos]) || line[pos] == ':'; ++pos)
                    ;
                for (; !isspace(line[pos]) && line[pos] != '('; ++pos)
                    cstr += line[pos];
                variables[vstr] = cstr;
                set<string> members;
                classes[cstr] = members;
            }
        } else {
            if (line.find(':') == string::npos) {
                map<string, char> mm;
                vector<string> mmt;
                int flag = 0;
                string tmp = "", cw = "", cwm = "", tmo = "";
                while (true) {
                    if (pos == line.length()) break;
                    if (flag == 0) {
                        if (isspace(line[pos]) || line[pos] == '(') {
                            if (line[pos] == '(') mmt.push_back("(");
                            ++pos;
                            continue;
                        }
                        tmp += line[pos++];
                        flag = 1;
                        continue;
                    } else if (flag == 1) {
                        if (isspace(line[pos]) || line[pos] == '(') {
                            mm[tmp] = 'A';
                            cw = tmp;
                            mmt.push_back(tmp);
                            tmp = "";
                            flag = 2;
                            ++pos;
                            continue;
                        }
                        tmp += line[pos++];
                        continue;
                    } else if (flag == 2) {
                        if (isspace(line[pos])) {
                            ++pos;
                            continue;
                        }
                        if (line[pos] == ')') {
                            flag = 3;
                            if (!room_or_ship &&
                                    ((cw == "AirConditionor" &&
                                      cwm.find("state!=") != string::npos) ||
                                     ((cw == "AirHumidifier" ||
                                       cw == "MicroPhone") &&
                                      cwm.find("isOn!=") != string::npos)) ||
                                room_or_ship &&
                                    ((cw == "ADA" || cw == "NearGun") &&
                                     cwm.find("state!=") != string::npos)) {
                                string tmppm =
                                    "==" +
                                    to_string(!(cwm[cwm.length() - 1] - '0'));
                                cwm = cwm.substr(0, cwm.length() - 3);
                                cwm += tmppm;
                            } else if (cwm.find("!=false") != string::npos) {
                                cwm = cwm.substr(0, cwm.length() - 7);
                                cwm += "==true";
                            } else if (cwm.find("!=true") != string::npos) {
                                cwm = cwm.substr(0, cwm.length() - 6);
                                cwm += "==false";
                            }
                            if (!cmpvalues) {
                                int tmppos = cwm.length() - 1;
                                for (; tmppos >= 0; --tmppos) {
                                    if (cwm[tmppos] == '=' ||
                                        cwm[tmppos] == '>' ||
                                        cwm[tmppos] == '<')
                                        break;
                                }
                                cwm = cwm.substr(0, tmppos + 1);
                            }
                            cwhenclasses[cw] = cwm;
                            cw = "";
                            cwm = "";
                            ++pos;
                            continue;
                        }
                        cwm += line[pos];
                        ++pos;
                        continue;
                    } else if (flag == 3) {
                        if (line[pos] == ')') {
                            mmt.push_back(")");
                            ++pos;
                            continue;
                        }
                        if (!isspace(line[pos])) {
                            tmo += line[pos];
                            flag = 4;
                        }
                        ++pos;
                        continue;
                    } else if (flag == 4) {
                        if (isspace(line[pos])) {
                            flag = 0;
                            if (tmo == "or")
                                mmt.push_back("+");
                            else if (tmo == "and")
                                mmt.push_back("*");
                            tmo = "";
                            ++pos;
                            continue;
                        }
                        tmo += line[pos];
                        ++pos;
                        continue;
                    }
                }
                int i = 0;
                for (auto iter = mm.begin(); iter != mm.end(); ++iter)
                    (*iter).second += i++;
                for (auto iter = mmt.begin(); iter != mmt.end(); ++iter) {
                    if (mm.count(*iter)) (*iter) = mm[(*iter)];
                    mingti += (*iter);
                }
                sum = mm.size();
            } else {
                for (; !isspace(line[pos]) && line[pos] != ':'; ++pos)
                    vstr += line[pos];
                for (; isspace(line[pos]) || line[pos] == ':'; ++pos)
                    ;
                for (; !isspace(line[pos]) && line[pos] != '('; ++pos)
                    cstr += line[pos];
                variables[vstr] = cstr;
                set<string> members;
                classes[cstr] = members;
            }
        }
    }
}

inline auto get_then(ifstream& ifs, string& line, string& rule,
                     map<string, string>& variables,
                     map<string, set<string>>& classes) {
    while (getline(ifs, line)) {
        rule += line + "\n";
        string vstr = "", tmpm = "", end = "";
        for (auto ch : line) {
            if (isspace(ch)) continue;
            end += ch;
        }
        if (end == "end") break;
        if (!end.length()) continue;
        auto pos = 0;
        if (line.find("update") != string::npos) {
            if (classes.count("update") == 0) {
                set<string> members;
                classes["update"] = members;
            }
            for (; line[pos] != '('; ++pos)
                ;
            for (++pos; isspace(line[pos]); ++pos)
                ;
            string member = "";
            for (; pos < line.length(); ++pos) {
                if (isspace(line[pos])) continue;
                if (line[pos] == ')') break;
                member += line[pos];
            }
            classes["update"].insert(member);
        } else {
            for (; isspace(line[pos]); ++pos)
                ;
            for (; !isspace(line[pos]) && line[pos] != '.'; ++pos)
                vstr += line[pos];
            for (; isspace(line[pos]) || line[pos] == '.'; ++pos)
                ;
            for (; line[pos] != ';'; ++pos) {
                if (!cmpvalues && line[pos] == '(') break;
                if (isspace(line[pos])) continue;
                tmpm += line[pos];
            }
            classes[variables[vstr]].insert(tmpm);
        }
    }
}

auto main() -> int {
    room_or_ship = ros("Input 'ship' or 'room': ", "ship", "room");
    cmpvalues = ros(
        "Input 'Y' to enable values compairsion, otherwise input 'N': ", "Y",
        "N");
    mode = cm();
    open_file("Input the path of the standard drl: ", stdfs);
    open_file("Input the path of the drl to be compared: ", cmpfs);
    strftime(ch, sizeof(ch) - 1, "%m_%d_%H_%M_%S", localtime(&t));
    string roosh = (room_or_ship ? "ship" : "room");
    repfn += roosh + "_report_" + ch;
    report.open(repfn + ".drl", ios::out);
    cout << "---------------------------------------" << endl;
    while (true) {
        auto stdrule = get_begin(stdfs, stdline) + "\n",
             cmprule = get_begin(cmpfs, cmpline) + "\n";
        if (stdrule[0] == '0' || cmprule[0] == '0') {
            report << "//The total number of comparisons: " << cnt << endl
                   << "//The total number of differences: " << dif << endl
                   << (cmpvalues ? "//Values compairsion enabled"
                                 : "//Values compairsion disabled")
                   << endl
                   << "//The difference rate: " << setiosflags(ios::fixed)
                   << setprecision(3) << (float)dif / cnt * 100 << "%\n"
                   << "//The average score: " << sum_score / cnt << endl;
            if (stdrule[0] != '0')
                report << "//Warning: The number of rules of the compared drl "
                          "may be less than the number of standard drl.\n";
            else if (cmprule[0] != '0')
                report << "//Warning: The number of rules of the compared drl "
                          "may be more than the number of standard drl.\n";
            break;
        }
        map<string, string> stdvariables, cmpvariables;
        map<string, set<string>> stdclasses, cmpclasses;
        vector<map<string, string>> stdwhenclasses, cmpwhenclasses;
        map<string, string> cstdwhenclassess, ccmpwhenclasses;
        string stdmingti = "", cmpmingti = "";
        int stdsum, cmpsum;
        get_start(stdfs, stdline, stdrule);
        get_start(cmpfs, cmpline, cmprule);
        get_when(stdfs, stdline, stdrule, stdvariables, stdclasses,
                 stdwhenclasses, cstdwhenclassess, stdmingti, stdsum);
        get_when(cmpfs, cmpline, cmprule, cmpvariables, cmpclasses,
                 cmpwhenclasses, ccmpwhenclasses, cmpmingti, cmpsum);
        get_then(stdfs, stdline, stdrule, stdvariables, stdclasses);
        get_then(cmpfs, cmpline, cmprule, cmpvariables, cmpclasses);
        float score = 1, partial_score;
        int stdmembers = 0, cmpmenbers = 0;
        vector<string> errors;
        if (mode == 0) {
            for (auto std_classes_iter = stdclasses.begin();
                 std_classes_iter != stdclasses.end(); ++std_classes_iter) {
                stdmembers += std_classes_iter->second.size() + 1;
            }
            partial_score = score / stdmembers;
            for (auto cmp_classes_iter = cmpclasses.begin();
                 cmp_classes_iter != cmpclasses.end(); ++cmp_classes_iter) {
                ++cmpmenbers;
                if (stdclasses.count(cmp_classes_iter->first) == 0) {
                    score -= partial_score;
                    errors.push_back("Class: " + cmp_classes_iter->first +
                                     ".\n");
                }
                for (auto cmp_members_iter = cmp_classes_iter->second.begin();
                     cmp_members_iter != cmp_classes_iter->second.end();
                     ++cmp_members_iter) {
                    ++cmpmenbers;
                    if (cmp_classes_iter->first == "update") {
                        bool is_diff = true;
                        for (auto vc_iter = stdvariables.begin();
                             vc_iter != stdvariables.end(); ++vc_iter) {
                            if (vc_iter->second ==
                                cmpvariables[*cmp_members_iter]) {
                                is_diff = false;
                                break;
                            }
                        }
                        if (is_diff) {
                            score -= partial_score;
                            errors.push_back("update( " + (*cmp_members_iter) +
                                             " ).\n");
                        }
                        continue;
                    }
                    if (stdclasses[cmp_classes_iter->first].count(
                            *cmp_members_iter) == 0) {
                        score -= partial_score;
                        errors.push_back("Class: " + cmp_classes_iter->first +
                                         ", " + (*cmp_members_iter) + ".\n");
                    }
                }
            }
            if (cmpmenbers < stdmembers) {
                score -= (stdmembers - cmpmenbers) * partial_score;
                errors.push_back("Some classes or members are missing.\n");
            }
        } else if (mode == 1) {
            for (auto std_classes_iter = stdclasses.begin();
                 std_classes_iter != stdclasses.end(); ++std_classes_iter) {
                stdmembers += std_classes_iter->second.size() + 1;
            }
            for (auto std_whenclasses_iter = stdwhenclasses.begin();
                 std_whenclasses_iter != stdwhenclasses.end();
                 ++std_whenclasses_iter) {
                stdmembers += (*std_whenclasses_iter).size();
            }
            partial_score = score / stdmembers;
            for (auto cmp_whenclasses_iter = cmpwhenclasses.begin();
                 cmp_whenclasses_iter != cmpwhenclasses.end();
                 ++cmp_whenclasses_iter) {
                if ((*cmp_whenclasses_iter).size() == 1) {
                    ++cmpmenbers;
                    bool isfound = false;
                    auto whenmap_iter = (*cmp_whenclasses_iter).begin();
                    for (auto std_whenclasses_iter = stdwhenclasses.begin();
                         std_whenclasses_iter != stdwhenclasses.end();
                         ++std_whenclasses_iter) {
                        if ((*std_whenclasses_iter).size() == 1) {
                            auto stdmap_iter = (*std_whenclasses_iter).begin();
                            if ((*stdmap_iter).first == (*whenmap_iter).first &&
                                (*stdmap_iter).second ==
                                    (*whenmap_iter).second) {
                                isfound = true;
                                break;
                            }
                        }
                    }
                    if (!isfound) {
                        score -= partial_score;
                        errors.push_back("Class: " + (*whenmap_iter).first +
                                         ", " + (*whenmap_iter).second + ".\n");
                    }
                } else {
                    cmpmenbers += (*cmp_whenclasses_iter).size();
                    int membercnt = 0;
                    for (auto std_whenclasses_iter = stdwhenclasses.begin();
                         std_whenclasses_iter != stdwhenclasses.end();
                         ++std_whenclasses_iter) {
                        membercnt = 0;
                        if ((*std_whenclasses_iter).size() ==
                            (*cmp_whenclasses_iter).size()) {
                            for (auto whenmap_iter =
                                          (*cmp_whenclasses_iter).begin(),
                                      stdmap_iter =
                                          (*std_whenclasses_iter).begin();
                                 whenmap_iter != (*cmp_whenclasses_iter).end();
                                 ++whenmap_iter, ++stdmap_iter) {
                                if ((*whenmap_iter).first ==
                                        (*stdmap_iter).first &&
                                    (*whenmap_iter).second ==
                                        (*stdmap_iter).second) {
                                    ++membercnt;
                                }
                            }
                            if (membercnt == (*cmp_whenclasses_iter).size()) {
                                break;
                            }
                        }
                    }
                    if (membercnt != (*cmp_whenclasses_iter).size()) {
                        score -= partial_score * (*cmp_whenclasses_iter).size();
                        for (auto whenmap_iter =
                                 (*cmp_whenclasses_iter).begin();
                             whenmap_iter != (*cmp_whenclasses_iter).end();
                             ++whenmap_iter)
                            errors.push_back("Class: " + (*whenmap_iter).first +
                                             ", " + (*whenmap_iter).second +
                                             ".\n");
                    }
                }
            }
            for (auto cmp_classes_iter = cmpclasses.begin();
                 cmp_classes_iter != cmpclasses.end(); ++cmp_classes_iter) {
                ++cmpmenbers;
                if (stdclasses.count(cmp_classes_iter->first) == 0) {
                    score -= partial_score;
                    errors.push_back("Class: " + cmp_classes_iter->first +
                                     ".\n");
                }
                for (auto cmp_members_iter = cmp_classes_iter->second.begin();
                     cmp_members_iter != cmp_classes_iter->second.end();
                     ++cmp_members_iter) {
                    ++cmpmenbers;
                    if (cmp_classes_iter->first == "update") {
                        bool is_diff = true;
                        for (auto vc_iter = stdvariables.begin();
                             vc_iter != stdvariables.end(); ++vc_iter) {
                            if (vc_iter->second ==
                                cmpvariables[*cmp_members_iter]) {
                                is_diff = false;
                                break;
                            }
                        }
                        if (is_diff) {
                            score -= partial_score;
                            errors.push_back("update( " + (*cmp_members_iter) +
                                             " ).\n");
                        }
                        continue;
                    }
                    if (stdclasses[cmp_classes_iter->first].count(
                            *cmp_members_iter) == 0) {
                        score -= partial_score;
                        errors.push_back("Class: " + cmp_classes_iter->first +
                                         ", " + (*cmp_members_iter) + ".\n");
                    }
                }
            }
            if (cmpmenbers < stdmembers) {
                score -= (stdmembers - cmpmenbers) * partial_score;
                errors.push_back("Some classes or members are missing.\n");
            }
        } else {
            for (auto std_classes_iter = stdclasses.begin();
                 std_classes_iter != stdclasses.end(); ++std_classes_iter) {
                stdmembers += std_classes_iter->second.size() + 1;
            }
            stdmembers += cstdwhenclassess.size() + 1;
            partial_score = score / stdmembers;
            bool issm = true;
            for (auto itera = ccmpwhenclasses.begin();
                 itera != ccmpwhenclasses.end(); ++itera) {
                ++cmpmenbers;
                if (cstdwhenclassess.count((*itera).first) == 0 ||
                    cstdwhenclassess[(*itera).first] != (*itera).second) {
                    score -= partial_score;
                    errors.push_back("Class: " + (*itera).first + ", " +
                                     (*itera).second + ".\n");
                    issm = false;
                }
            }
            ++cmpmenbers;
            if (!issm) {
                score -= partial_score;
                errors.push_back(
                    "The logical relationship of the conditions is "
                    "different.\n");
            } else {
                if (get_xiqufanshi(stdsum, stdmingti) !=
                    get_xiqufanshi(cmpsum, cmpmingti)) {
                    score -= partial_score;
                    errors.push_back(
                        "The logical relationship of the conditions is "
                        "different.\n");
                }
            }
            for (auto cmp_classes_iter = cmpclasses.begin();
                 cmp_classes_iter != cmpclasses.end(); ++cmp_classes_iter) {
                ++cmpmenbers;
                if (stdclasses.count(cmp_classes_iter->first) == 0) {
                    score -= partial_score;
                    errors.push_back("Class: " + cmp_classes_iter->first +
                                     ".\n");
                }
                for (auto cmp_members_iter = cmp_classes_iter->second.begin();
                     cmp_members_iter != cmp_classes_iter->second.end();
                     ++cmp_members_iter) {
                    ++cmpmenbers;
                    if (cmp_classes_iter->first == "update") {
                        bool is_diff = true;
                        for (auto vc_iter = stdvariables.begin();
                             vc_iter != stdvariables.end(); ++vc_iter) {
                            if (vc_iter->second ==
                                cmpvariables[*cmp_members_iter]) {
                                is_diff = false;
                                break;
                            }
                        }
                        if (is_diff) {
                            score -= partial_score;
                            errors.push_back("update( " + (*cmp_members_iter) +
                                             " ).\n");
                        }
                        continue;
                    }
                    if (stdclasses[cmp_classes_iter->first].count(
                            *cmp_members_iter) == 0) {
                        score -= partial_score;
                        errors.push_back("Class: " + cmp_classes_iter->first +
                                         ", " + (*cmp_members_iter) + ".\n");
                    }
                }
            }
            if (cmpmenbers < stdmembers) {
                score -= (stdmembers - cmpmenbers) * partial_score;
                errors.push_back("Some classes or members are missing.\n");
            }
        }
        sum_score += score;
        cout << "compared: " << ++cnt
             << " , differences: " << (score < 1 ? ++dif : dif) << endl;
        if (score < 1) {
            report << "//Number: " << cnt << endl
                   << setiosflags(ios::fixed) << setprecision(3)
                   << "//Score: " << score << endl
                   << "//The standard rule:\n"
                   << stdrule << "\n//The different rule:\n"
                   << cmprule << "\n//The differences:\n";
            for (auto error_iter = errors.begin(); error_iter != errors.end();
                 ++error_iter)
                report << "//" << *error_iter;
            report << "\n/*---------------------------------------*/\n\n";
        }
    }
    report.close();
    stdfs.close();
    cmpfs.close();
    cout << "---------------------------------------\nThe comparison is over! "
            "See the report '" +
                repfn + ".drl' for details.\n\n";
    system("pause");
    return 0;
}