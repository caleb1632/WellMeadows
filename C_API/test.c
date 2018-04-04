#include <mysql.h>
#include <my_global.h>
#include <stdio.h>

using namespace std;

int main(int argc, char **argv){  
  MYSQL *con = mysql_init(NULL);

  if (con == NULL) {
    fprintf(stderr, "%s\n", mysql_error(con));
    exit(1);
  }

  if (NULL== mysql_real_connect(conn, "", "", password.c_str(), "dbennett", 0, NULL, 0)) {
    cout << "Connection Failed: " << endl;
    cout << mysql_error(conn) << endl;
   return -1;
  }

  if (mysql_query(con, "SHOW TABLES c740393j")) {
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
  }

  mysql_close(con);
  exit(0);
}
