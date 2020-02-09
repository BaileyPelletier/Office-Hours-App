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
  void set(string s, string b, string n, int m, string z) {
    times = s;
    building = b;
    roomNum = n;
    byApp = m;
    special = z;
  } //constructor
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
    avblty.set("A","A","0",0,"A");
  }
  void set(Course &c, Availability &a) {
    crs.set(c.getPrefix(),c.getCourseNum(),c.getTitle());
    avblty.set(a.getTimes(),a.getBuilding(),a.getRoomNum(),a.getByApp(),a.getSpecial());
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
  Teacher d(1, "Hao Peng");
  Teacher e(0, "John Smith");
  Teacher f(0, "Erin Jones");
  Teacher g(1, "Bill Hollingsworth");
  

  Course csci1301;
  csci1301.set("CSCI", 1301, "Intro to Computing");
  Course csci1302;
  csci1302.set("CSCI", 1302, "Software Development");
  Course csci1730;
  csci1730.set("CSCI", 1730, "Systems Programming");
  Course csci3030;
  csci3030.set("CSCI", 3030, "Computing, Ethics, and Society");
  Course csci2610;
  csci2610.set("CSCI",2610,"Discrete Mathematics");

  Availability one;
  one.set("Mon, Wed, Fri: 12pm-3pm", "Boyd Graduate Studies", "101", 0, "");
  Availability two;
  two.set("Tue, Thu: 1pm-2pm","Boyd Graduate Studies", "101",1,"First Thursday each month");
  Availability three;
  three.set("Wed, Fri:: 10am-12pm","Boyd Graduate Studies", "202",0,"");
  Availability four;
  four.set("Mon: 4pm-6pm","Science Learning Center", "340",0,"Only before exams");
  Availability five;
  five.set("Tue, Wed, Thu: 1pm-3pm","Main Library", "300",0,"");
  Availability six;
  six.set("Fri: 4pm-5pm","Gilbert Hall", "220",1,"");
  
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

  a.addOH(0, a1);
  a.addOH(1, a2);
  b.addOH(0, b1);
  b.addOH(1, b2);
  c.addOH(0, c1);
  c.addOH(1, c2);
  d.addOH(0, a1);
  d.addOH(1, b2);
  e.addOH(0, a2);
  e.addOH(1, c2);
  f.addOH(0, c2);
  f.addOH(1, c1);
  g.addOH(0, b2);
  g.addOH(1, b1);

  Teacher teachers[7] = {b,a,g,d,c,e,f};
  
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
	for (int i=0; i<7; i++) {
	  cout << teachers[i].toJSON();
	  if(i!=6) {
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
