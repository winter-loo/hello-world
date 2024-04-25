#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

int main() {
    PGconn *conn;
    PGresult *res;
    const char *conninfo = "dbname=postgres user=ldd host=localhost port=5432";

    // Establish connection to the database
    conn = PQconnectdb(conninfo);

    // Check if the connection was successful
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);
    }

    // Execute the query
    res = PQexec(conn, "SELECT NOW()");

    // Check if the query execution was successful
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Query execution failed: %s", PQresultErrorMessage(res));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }

    // Print the result
    printf("Current date and time: %s\n", PQgetvalue(res, 0, 0));

    // Clear the result and close the connection
    PQclear(res);
    PQfinish(conn);

    return 0;
}
