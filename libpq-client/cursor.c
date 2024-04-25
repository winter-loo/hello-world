#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

void setup(PGconn*);
void teardown(PGconn*);

int main() {
    PGconn *conn;
    PGresult *res;
    const char *conninfo = "dbname=postgres user=ldd";

    // Establish connection to the database
    conn = PQconnectdb(conninfo);

    // Check if the connection was successful
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);
    }

    setup(conn);

    // Begin a transaction
    res = PQexec(conn, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }
    PQclear(res);

    // Declare and open a cursor
    res = PQexec(conn, "DECLARE mycursor CURSOR FOR SELECT a FROM test_table");
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "DECLARE CURSOR command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }
    PQclear(res);

    // Fetch data from the cursor
    res = PQexec(conn, "FETCH mycursor");
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "FETCH command failed: %s", PQresultErrorMessage(res));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }

    // Print the result
    printf("Current value: %s\n", PQgetvalue(res, 0, 0));

    // Close the cursor
    PQclear(res);

    // End the transaction
    res = PQexec(conn, "END");
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "END command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }
    PQclear(res);

    teardown(conn);

    // Close the connection
    PQfinish(conn);

    return 0;
}

void setup(PGconn *conn) {
    PGresult *res;

    // Create a table
    res = PQexec(conn, "CREATE TABLE IF NOT EXISTS test_table (a int)");
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "CREATE TABLE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }
    PQclear(res);

    // Insert some data
    res = PQexec(conn, "INSERT INTO test_table VALUES (1), (2), (3)");
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "INSERT command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }
    PQclear(res);
}

void teardown(PGconn *conn) {
    PGresult *res;

    // Drop the table
    res = PQexec(conn, "DROP TABLE IF EXISTS test_table");
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "DROP TABLE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }
    PQclear(res);
}
