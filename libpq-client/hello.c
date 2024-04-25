#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

int main() {
    // Create a connection to the PostgreSQL database
    // PGconn *conn = PQconnectdb("dbname=postgres user=ldd password=ldd host=localhost port=5432");
    PGconn *conn = PQconnectdb("dbname=postgres user=ldd");

    // Check if the connection was successful
    if (PQstatus(conn) == CONNECTION_BAD) {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);
    }

    // Connection successful, print a "hello" message
    printf("Connected to PostgreSQL database!\n");

    // Close the connection
    PQfinish(conn);

    printf("Thread Safe: %d\n", PQisthreadsafe());

    return 0;
}
