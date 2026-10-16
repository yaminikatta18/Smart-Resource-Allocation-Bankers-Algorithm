#include <stdio.h>

#define P 5
#define R 3

int available[R] = {3, 3, 2};

int allocation[P][R] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

int maximum[P][R] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

int need[P][R];

void calculateNeed(void)
{
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] =
                maximum[i][j] - allocation[i][j];
        }
    }
}

void displayMatrices(void)
{
    printf("\nAvailable Resources: ");

    for (int j = 0; j < R; j++)
        printf("%d ", available[j]);

    printf("\n\nAllocation Matrix:\n");

    for (int i = 0; i < P; i++) {
        printf("P%d: ", i);

        for (int j = 0; j < R; j++)
            printf("%d ", allocation[i][j]);

        printf("\n");
    }

    printf("\nMaximum Matrix:\n");

    for (int i = 0; i < P; i++) {
        printf("P%d: ", i);

        for (int j = 0; j < R; j++)
            printf("%d ", maximum[i][j]);

        printf("\n");
    }

    printf("\nNeed Matrix:\n");

    for (int i = 0; i < P; i++) {
        printf("P%d: ", i);

        for (int j = 0; j < R; j++)
            printf("%d ", need[i][j]);

        printf("\n");
    }
}

int safetyCheck(int sequence[])
{
    int work[R];
    int finish[P] = {0};
    int completed = 0;

    for (int j = 0; j < R; j++)
        work[j] = available[j];

    while (completed < P) {
        int found = 0;

        for (int i = 0; i < P; i++) {
            if (finish[i])
                continue;

            int possible = 1;

            for (int j = 0; j < R; j++) {
                if (need[i][j] > work[j]) {
                    possible = 0;
                    break;
                }
            }

            if (possible) {
                for (int j = 0; j < R; j++)
                    work[j] += allocation[i][j];

                sequence[completed++] = i;
                finish[i] = 1;
                found = 1;
            }
        }

        if (!found)
            return 0;
    }

    return 1;
}

void checkSafeState(void)
{
    int sequence[P];

    if (safetyCheck(sequence)) {
        printf("\nSystem is in a SAFE STATE.\n");
        printf("Safe Sequence: ");

        for (int i = 0; i < P; i++)
            printf("P%d%s", sequence[i],
                   i == P - 1 ? "\n" : " -> ");
    } else {
        printf("\nSystem is in an UNSAFE STATE.\n");
    }
}

void requestResources(void)
{
    int pid;
    int request[R];

    printf("Enter process ID (0-4): ");

    if (scanf("%d", &pid) != 1 || pid < 0 || pid >= P) {
        printf("Invalid process ID.\n");
        return;
    }

    printf("Enter request for A, B, C: ");

    for (int j = 0; j < R; j++) {
        if (scanf("%d", &request[j]) != 1 ||
            request[j] < 0) {
            printf("Invalid resource request.\n");
            return;
        }
    }

    for (int j = 0; j < R; j++) {
        if (request[j] > need[pid][j]) {
            printf("Request denied: exceeds process need.\n");
            return;
        }
    }

    for (int j = 0; j < R; j++) {
        if (request[j] > available[j]) {
            printf("Resources unavailable. Process must wait.\n");
            return;
        }
    }

    for (int j = 0; j < R; j++) {
        available[j] -= request[j];
        allocation[pid][j] += request[j];
        need[pid][j] -= request[j];
    }

    int sequence[P];

    if (safetyCheck(sequence)) {
        printf("Request GRANTED: system remains safe.\n");
    } else {
        for (int j = 0; j < R; j++) {
            available[j] += request[j];
            allocation[pid][j] -= request[j];
            need[pid][j] += request[j];
        }

        printf("Request DENIED: system would become unsafe.\n");
    }
}

int main(void)
{
    int choice;

    calculateNeed();

    printf("\n====================================\n");
    printf(" SMART RESOURCE ALLOCATION MANAGER\n");
    printf(" BANKER'S ALGORITHM\n");
    printf("====================================\n");

    do {
        printf("\n1. Display Resource Matrices\n");
        printf("2. Check Safe State\n");
        printf("3. Request Resources\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
            return 1;

        switch (choice) {
            case 1:
                displayMatrices();
                break;

            case 2:
                checkSafeState();
                break;

            case 3:
                requestResources();
                break;

            case 4:
                printf("Exiting Resource Manager.\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 4);

    return 0;
}
