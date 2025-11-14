//go back n
#include <stdio.h>

#define W 4   // window size

int main() {
    int n, base = 1, i;
    int loss_done = 0;   // ensures frame 3 is lost ONLY once

    printf("Enter total number of frames: ");
    scanf("%d", &n);

    while (base <= n) {

        int win = (n - base + 1 < W) ? (n - base + 1) : W;

        printf("\nSender Window: [ ");
        for (i = 0; i < win; i++)
            printf("%d ", base + i);
        printf("]\n");

        int error = 0;

        for (i = 0; i < win; i++) {
            int f = base + i;

            // Fixed loss: ONLY once, ONLY for n=4, ONLY for frame 3
            if (n == 4 && f == 3 && loss_done == 0) {
                printf("Frame %d lost or corrupted!\n", f);
                error = f;
                loss_done = 1;   // loss happens only ONCE
                break;
            }

            printf("Frame %d sent successfully.\n", f);
        }

        if (!error) {
            printf("Receiver: ACK for all %d frames.\n", win);
            base += win;
        } else {
            printf("Receiver: NACK for frame %d. Go-Back-N triggered.\n", error);
            printf("Receiver: Discards all frames after and incl. frame %d.\n", error);
            base = error;   // go back to the lost frame ONCE
        }
    }

    printf("\nAll frames sent and acknowledged successfully!\n");
    return 0;
}
//broadcast tree
#include <stdio.h>
#define MAX 20
#define INF 9999

int main() {
    int n, i, j, u, v, min, total_cost = 0;
    int graph[MAX][MAX], visited[MAX] = {0}, edges = 0;

    printf("Enter the number of hosts (nodes): ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix (cost 0 for self, %d for no direct link):\n", INF);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    visited[0] = 1; // Start from host 0

    printf("\nEdges in the broadcast (spanning) tree:\n");

    while (edges < n - 1) {
        min = INF;

        for (i = 0; i < n; i++) {
            if (visited[i]) {
                for (j = 0; j < n; j++) {
                    if (!visited[j] && graph[i][j] < min && graph[i][j] != 0) {
                        min = graph[i][j];
                        u = i;
                        v = j;
                    }
                }
            }
        }

        printf("Host %d - Host %d : Cost = %d\n", u, v, min);
        total_cost += min;
        visited[v] = 1;
        edges++;
    }

    printf("Total cost of Broadcast Tree: %d\n", total_cost);

    return 0;
}
//Dijkatra's
#include <stdio.h>
#define MAX 100
#define INF 9999

int main() {
    int n, g[MAX][MAX], dist[MAX], vis[MAX]={0}, i, j, start, min, next;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix (use %d for infinity/no edge):\n", INF);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &g[i][j]);

    printf("Enter the source vertex (0 to %d): ", n - 1);
    scanf("%d", &start);

    for (i = 0; i < n; i++) dist[i] = g[start][i];
    dist[start] = 0;
    vis[start] = 1;

    for (i = 1; i < n; i++) {

        min = INF;  next = -1;

        for (j = 0; j < n; j++)
            if (!vis[j] && dist[j] < min)
                min = dist[j], next = j;

        if (next == -1) break;
        vis[next] = 1;

        for (j = 0; j < n; j++)
            if (!vis[j] && g[next][j] != INF &&
                dist[next] + g[next][j] < dist[j])
                dist[j] = dist[next] + g[next][j];
    }

    printf("\nShortest distances from source vertex %d:\n", start);
    for (i = 0; i < n; i++)
        printf("To vertex %d : %d\n", i, dist[i]);

    return 0;
}
//CRC
#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint16_t crc_calc(const uint8_t *data, size_t len,
                  uint16_t poly, uint16_t init, int bits) {

    uint16_t crc = init;

    for (size_t i = 0; i < len; i++) {

        crc ^= (data[i] << (bits - 8));     // align MSB

        for (int j = 0; j < 8; j++) {
            // If MSB is 1 → XOR with polynomial
            if (crc & (1 << (bits - 1)))
                crc = (crc << 1) ^ poly;
            else
                crc <<= 1;

            // Mask according to CRC bit size
            if (bits == 12)
                crc &= 0x0FFF;
            else
                crc &= 0xFFFF;
        }
    }
    return crc;
}

int main() {

    char input[128];

    printf("Enter the data string: ");
    scanf("%127s", input);

    size_t len = strlen(input);

    // CRC-12: poly = 0x180F, init = 0x0000, bits = 12
    uint16_t c12 = crc_calc((uint8_t *)input, len, 0x180F, 0x0000, 12);

    // CRC-16 (IBM): poly = 0x8005, init = 0xFFFF, bits = 16
    uint16_t c16 = crc_calc((uint8_t *)input, len, 0x8005, 0xFFFF, 16);

    // CRC-CCITT: poly = 0x1021, init = 0xFFFF, bits = 16
    uint16_t ccitt = crc_calc((uint8_t *)input, len, 0x1021, 0xFFFF, 16);

    printf("\nCRC Results:\n");
    printf("CRC-12   : 0x%03X (12 bits)\n", c12);
    printf("CRC-16   : 0x%04X (16 bits)\n", c16);
    printf("CRC-CCITT: 0x%04X (16 bits)\n", ccitt);

    return 0;
}
