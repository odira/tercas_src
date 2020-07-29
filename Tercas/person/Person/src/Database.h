#define pragma

#include <QObject>
#include <QSqlDatabase>

#define HOSTNAME "localhost"
#define USERNAME "postgres"
#define PASSWORD "monrepo"
#define DATABASE "terkas"

class Database : public QObject
{
    Q_OBJECT

public:
    explicit Database(QObject *parent = 0);
    ~Database();

private:
    QSqlDatabase db;
};

