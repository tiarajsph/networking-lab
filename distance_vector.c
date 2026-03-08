#include <stdio.h>

/*
INFINITY represents a very large cost.
In networking simulations, 9999 usually means
there is NO direct connection between routers.
*/
#define INFINITY 9999

/*
MAX defines the maximum number of routers
the program can handle.
*/
#define MAX 10

/*
cost[i][j]  -> direct cost from router i to router j
dist[i][j]  -> shortest distance from router i to router j
next_hop[i][j] -> next router to send packet to reach j from i
*/
int cost[MAX][MAX], dist[MAX][MAX], next_hop[MAX][MAX];

int nodes;   // number of routers in the network


/*
INITIALIZATION FUNCTION

This copies the initial cost matrix into the distance matrix.
At the beginning, routers only know their direct neighbors.

Also sets the next hop from i to j as j itself
because initially we assume the direct route.
*/
void initialize() {
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            dist[i][j] = cost[i][j];   // initial distance = direct cost
            next_hop[i][j] = j;        // next hop initially is destination itself
        }
    }
}


/*
UPDATE ROUTES FUNCTION

This implements the core of the Distance Vector Algorithm.

Each router checks if going through another router
gives a cheaper path to a destination.

If yes, update:
1. The distance
2. The next hop

The process repeats until no changes occur.
*/
void updateRoutes() {

    int updated;

    do {
        updated = 0;   // assume no updates in this iteration

        for (int i = 0; i < nodes; i++) {       // source router
            for (int j = 0; j < nodes; j++) {   // destination router
                for (int k = 0; k < nodes; k++) { // intermediate router

                    /*
                    Check if going from i → k → j
                    is cheaper than current route i → j
                    */

                    if (dist[i][j] > dist[i][k] + dist[k][j]) {

                        // update the new shortest distance
                        dist[i][j] = dist[i][k] + dist[k][j];

                        // update next hop to whatever router i uses to reach k
                        next_hop[i][j] = next_hop[i][k];

                        updated = 1;  // mark that a change occurred
                    }
                }
            }
        }

    } while (updated);  // repeat until no updates happen
}



/*
DISPLAY FUNCTION

Prints the routing table for each router.

Columns:
Destination -> target router
Cost        -> shortest distance
Next Hop    -> first router to forward packet to
*/
void display() {

    for (int i = 0; i < nodes; i++) {

        printf("\nRouter %d's Routing Table:\n", i + 1);
        printf("Destination\tCost\tNext Hop\n");

        for (int j = 0; j < nodes; j++) {

            printf("%d\t\t%d\t%d\n",
                   j + 1,           // destination router
                   dist[i][j],      // shortest cost
                   next_hop[i][j] + 1); // next router to send packet
        }
    }
}



int main() {

    printf("Enter the number of routers: ");
    scanf("%d", &nodes);

    /*
    User enters the cost matrix.

    Example:
    Router 1 to Router 2 = cost
    Router 1 to Router 3 = cost

    If routers are NOT directly connected,
    user enters 9999 (infinity).
    */
    printf("Enter the cost matrix (enter 9999 for no direct link):\n");

    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {

            scanf("%d", &cost[i][j]);

            /*
            Distance from a router to itself
            must always be 0.
            */
            if (i == j) {
                cost[i][j] = 0;
            }
        }
    }

    /*
    Step 1: Initialize routing tables
    */
    initialize();

    /*
    Step 2: Compute shortest routes
    */
    updateRoutes();

    /*
    Step 3: Display final routing tables
    */
    display();

    return 0;
}