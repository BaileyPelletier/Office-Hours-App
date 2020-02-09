#include <iostream>
#include "fcgio.h"

using namespace std;

class Teacher;
class Availability;
class Course;
class OfficeHours;

class Course {
 private:
  string prefix;
  int courseNum;
  string title;

 public:
  Course() {
    prefix = "";
    courseNum = 0;
    title = "";
  }
  void set(string p, int n, string t) {
    prefix = p;
    courseNum = n;
    title = t;
  } //constructor
  string getPrefix() {
    return prefix;
  } //getPrefix
  int getCourseNum() {
    return courseNum;
  } //getCourseNum
  string getTitle() {
    return title;
  } //getTitle
  string toJSON() {
    return "{\"prefix\":\"" + getPrefix() + "\",\"courseNumber\":" + to_string(getCourseNum()) + ",\"title\":\"" + getTitle() + "\"}";
  }
  
}; //Course

class Availability {
 private:
  string times{"A"};
  string building{"A"};
  string roomNum{"0"};
  int byApp{0};
  string special{""};

 public:
  Availability() {
    times = "";
    building = "";
    byApp = 0;
  }
  void set(string b, string n) {
    building = b;
    roomNum = n;
    byApp = 0;
  } //constructor
  void addTimes(string s) {
    times = s;
  } //addTimes
  void setApp(int a) {
    byApp = a;
  } //setApp
  void comment(string s) {
    special = s;
  } //comment
  string getTimes() {
    return times;
  } //getTimes
  string getBuilding() {
    return building;
  } //getBuilding
  string getRoomNum() {
    return roomNum;
  } //getRoomNum
  int getByApp() {
    return byApp;
  } //getByApp
  string getSpecial() {
    return special;
  } //getSpecial
  string toJSON() {
    return "{\"times\":\"" + getTimes() + "\",\"building\":\"" + getBuilding() + "\",\"room\":\"" + getRoomNum() +
      "\",\"byAppt\":" + to_string(getByApp()) + ",\"specialNote\":\"" + getSpecial() + "\"}";
  }
  
}; //Availability

class OfficeHours {
public:
  Course crs;
  Availability avblty;
  OfficeHours() {
    crs.set("A",0,"A");
    avblty.set("A","0");
  }
  void set(Course &c, Availability &a) {
    crs.set(c.getPrefix(),c.getCourseNum(),c.getTitle());
    avblty.set(a.getBuilding(),a.getRoomNum());
  } //constructor
  string toJSON() {
    return "{\"course\":" + crs.toJSON() + ",\"availability\":" + avblty.toJSON() +"}";
  }
  
}; //offhour

class Teacher {
 private:
  int isProfessor;
  string name;
  //Course *courses[3];                                                                                                                              
 public:
  OfficeHours oh[5];
  Teacher(int p, string n) {
    isProfessor = p;
    name = n;
  } //constructor                                                                                                                                    
  void addOH(int pos, OfficeHours &c) {
    oh[pos] = c;
  } //addOH                                                                                                                                          
  int getIsProfessor() {
    return isProfessor;
  } //getIsProfessor                                                                                                                                 
  string getName() {
    return name;
  } //getName

  string toJSON() {
    string tString{"{\"name\":\"" + getName() +"\",\"isProf\":" + to_string(getIsProfessor()) + ",\"officeHours\":["};
    for(int i=0; i<2; i++) {
      if(i!=0) {
	tString.append(",");
      } //if
	tString.append(oh[i].toJSON());
    } //for
    tString.append("]}");
    return tString;
  } //toJSON
  //Course getCourse(int n) {                                                                                                                        
  //  return *courses[n];                                                                                                                            
  //} //getCourse                                                                                                                                    
}; //Teacher

int main(void) {

  Teacher a(1, "Michael Cotterel");
  Teacher b(1, "Brad Barnes");
  Teacher c(1, "Michael Scott");
  Teacher teachers[3] = {a,b,c};

  Course csci1301;
  csci1301.set("CSCI", 1301, "Java I");
  Course csci1302;
  csci1302.set("CSCI", 1302, "Java II");
  Course csci2610;
  csci2610.set("CSCI", 2610, "Systems Programming");
  Course csci3030;
  csci3030.set("CSCI", 3030, "Computer Ethics");

  cout << csci1301.getPrefix() << csci1301.getCourseNum() << csci1301.getTitle();
  
  Availability one;
  one.set("Boyd", "101");
  one.addTimes("MWF: 12-3");
  Availability two;
  two.set("Boyd", "101");
  two.addTimes("TR: 1-2");
  two.setApp(1);
  Availability three;
  three.set("Boyd", "202");
  three.addTimes("WF: 10-12");
  Availability four;
  four.set("SLC", "340");
  four.addTimes("M: 4-6");
  Availability five;
  five.set("Main Library", "300");
  five.addTimes("TWR: 1-3");
  Availability six;
  six.set("Gilbert", "220");
  six.addTimes("F: 4-5");
  six.setApp(1);

  OfficeHours a1;
  a1.set(csci1301, one);
  OfficeHours a2;
  a2.set(csci1302, two);
  OfficeHours b1;
  b1.set(csci1302, three);
  OfficeHours b2;
  b2.set(csci2610, four);
  OfficeHours c1;
  c1.set(csci2610, five);
  OfficeHours c2;
  c2.set(csci3030, six);

  cout << a1.crs.getTitle();
  
  a.addOH(0, a1);
  cout << a1.crs.toJSON();
  cout << a1.avblty.toJSON();
  a.addOH(1, a2);
  b.addOH(0, b1);
  b.addOH(1, b2);
  c.addOH(0, c1);
  c.addOH(1, c2);

  
    // Backup the stdio streambufs
    streambuf * cin_streambuf  = cin.rdbuf();
    streambuf * cout_streambuf = cout.rdbuf();
    streambuf * cerr_streambuf = cerr.rdbuf();

    FCGX_Request request;

    FCGX_Init();
    FCGX_InitRequest(&request, 0, 0);

    while (FCGX_Accept_r(&request) == 0) {
        fcgi_streambuf cin_fcgi_streambuf(request.in);
        fcgi_streambuf cout_fcgi_streambuf(request.out);
        fcgi_streambuf cerr_fcgi_streambuf(request.err);

        cin.rdbuf(&cin_fcgi_streambuf);
        cout.rdbuf(&cout_fcgi_streambuf);
        cerr.rdbuf(&cerr_fcgi_streambuf);

        cout << "Content-type: application/json\r\n"
             << "\r\n[";
	for (int i=0; i<3; i++) {
	  cout << teachers[i].toJSON();
	  if(i!=2) {
	    cout << ",";
	  } //if
	} //for
	cout << "]";
             
        // Note: the fcgi_streambuf destructor will auto flush
    }

    // restore stdio streambufs
    cin.rdbuf(cin_streambuf);
    cout.rdbuf(cout_streambuf);
    cerr.rdbuf(cerr_streambuf);

    return 0;
}
