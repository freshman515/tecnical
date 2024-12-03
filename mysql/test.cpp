#include<mysql_connection.h>
#include<mysql_driver.h>
#include<cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
using namespace std;
using namespace sql;
#define DATABASE "user"
int main() {
    Driver* driver = get_driver_instance();
    Connection* con = driver->connect("tcp://127.0.0.1:3306", "root", "xmf");
    Statement* stm = con->createStatement();
    if (con->isValid()) {
        cout << "connect successful!" << endl;
    } else {
        cout << "connect fail!" << endl;
    }
    stm->execute("use " DATABASE);
    stm->execute("drop table if exists test");
    stm->execute("create table test(id int ,passwd varchar(32));");
    stm->execute("insert into test(id,passwd) values(1,'xmf123');");
    stm->execute("insert into test(id,passwd) values(2,'laoliu666');");
    stm->execute("insert into test(id,passwd) values(3,'jiji');");

    //设置数据库
    con->setSchema(DATABASE);
    //创建预编译语句
    PreparedStatement* parastm = con->prepareStatement("select * from test where passwd = ?");
    //设置预编译语句的占位参数
    parastm->setString(1, "xmf123");
    ResultSet* res = parastm->executeQuery();
    while (res->next()) {
        int id = res->getInt("id");
        string passwd = res->getString("passwd");
        cout << "id = " << id << " passwd = " << passwd;
    }

    delete con;
    return 0;
}