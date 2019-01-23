#include "db.h"
using namespace std;
using namespace sqlite;

db::db()
{
    database base("dbfile.db");

    base <<
             "create table if not exists image ("
             "   _id integer primary key autoincrement not null,"
             "   path text,"
             "   tags text"
             ");";
    base << "insert into image (path,tags) values (?,?);"
             << "image.jpg"
             << "plage";

    std::cin.get();

}
