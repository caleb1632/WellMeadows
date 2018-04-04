//Caleb Jackman
//Database API in C++
#include <mysql.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <math.h>

using namespace std;

char * GetUserName();
string EditStatement(string str);
vector<int> GetColLength(MYSQL_RES * queryResult, MYSQL_ROW  row, MYSQL_FIELD * field);
vector<string>GetStatements();


int main(int argc, char **argv){  
  MYSQL_RES * queryResult; MYSQL_RES * tempQuery;
  MYSQL_ROW  row;
  MYSQL_FIELD * field;
  MYSQL *con = mysql_init(NULL);
  string cmd;
  int i = 0;
  int fieldCount = 0;
  int temp = 0;
  int qcnt = 0;

   char * username = GetUserName();
   char * password = getpass("enter password: ");
	
   vector<string>cmds=GetStatements();
   vector<MYSQL_RES*>qryResults(cmds.size());

   while(NULL== mysql_real_connect(con, "", username, password, username, 0, NULL, 0) ){
     cout<<"Connection Failed: "<<endl;
     cout<<mysql_error(con)<<endl;
     username = GetUserName();
     password = getpass("enter password: ");
   }

  if(NULL== mysql_real_connect(con, "", "", password, username, 0, NULL, 0) ){
    cout<<"Connection Failed: "<<endl;
    cout<<mysql_error(con)<<endl;
    username = GetUserName();
    password = getpass("enter password: ");
  }

  for(i=0; i<cmds.size(); i++){
    if(mysql_query(con,cmds[i].c_str())){
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      return 1;
    }else{
      qryResults[qcnt] = (mysql_store_result(con));
      if(qryResults[qcnt] == NULL){
        cout<<"Could not store result "<<endl;
        cout<<mysql_error(con)<<endl;
        return -1;
      }else{qcnt++;}
    }
  }

  i=0;
  int width = 0;
  cout<<endl;

  for(int j=0; j<qryResults.size(); j++){
    fieldCount = mysql_num_fields(qryResults[j]);
    for(field=mysql_fetch_field(qryResults[j]); field!=NULL; field=mysql_fetch_field(qryResults[j])){ 
      if(!width){width=strlen(field->name);
      }else{
        temp = strlen(field->name);
        if(temp>width){width=temp;}
      }
      if(field->name!=NULL){
        if(width>strlen(field->name)){cout<<field->name<<setw(width-strlen(field->name)+1)<<"|";}
        else{cout<<field->name<<"|";}
        }
    }

    cout<<endl;

    for(i=0; i<fieldCount; i++){cout<<setfill('-')<<setw(width+1)<<'+';}
    cout<<setfill(' ')<<endl;
    while((row = mysql_fetch_row(qryResults[j]))!= NULL){
      for(int i=0; i<fieldCount; i++){
        if(row[i]!=NULL){cout<<row[i]<<setw(width-strlen(row[i])+1)<<"|";}
        else{cout<<row[i]<<"|";}
      }
      cout<<endl;
    }
    mysql_free_result(qryResults[j]);
  }
 
  mysql_close(con);
  return 0;
}

char * GetUserName(){
  char * c;
  string str;
  cout<<"enter username: ";
  cin>>str;
  c = new char[strlen(str.c_str()+1)];
  cin.ignore();
  return strcpy(c,str.c_str());;
}

string EditStatement(string str){
  string s;
  int pos = 0;
  for(int i=0; i<str.size(); i++){
    if(str[i]=='"'){
      s = s + '\\';
    }else if(str[i]=='\''){
      s = s + '\\';
    }
    s = s + str[i];  
  }
  return s;
}

vector<string>GetStatements(){
  vector<string>vec;
  string str;
  string t;
  char c;
  int count = 0;
  int i = 0;
  cout<<"enter statement: ";
  cin.get(c);
  while(c!='\n'){
    str = str + c;
    if(c==';'){
      if(vec.size()){
        if(str[0]==' '){str = str.substr(1);}
        while(str[i]!=' '){i++;}
        str = str.substr(i+1);
        i=0;   
      }
      vec.push_back(str);
      str=str.empty();
    }
    cin.get(c);
  }
  if(str.size()>1){
    i=0;
    while(str[i]!=' '){i++;}
    str = str.substr(i+1);
    str = str + ";";
    vec.push_back(str);
  }
  return vec;
}
