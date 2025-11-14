// char stuffed 
#include <stdio.h>

#include <string.h>

int main() {

 char input[30], stuffed[80] = "";

 char start_delim, end_delim;

 char temp[3], double_start[3], double_end[3];

 int i;

 // Input Section

 printf("Enter the data to be stuffed: ");

 scanf("%s", input);

 printf("Enter the starting delimiter character: ");

 scanf(" %c", &start_delim);

 printf("Enter the ending delimiter character: ");
 scanf(" %c", &end_delim);

 // Prepare delimiter substrings

 double_start[0] = double_start[1] = start_delim;

 double_start[2] = '\0';

 double_end[0] = double_end[1] = end_delim;

 double_end[2] = '\0';

 // Add starting delimiter

 strcat(stuffed, double_start);

 // Stuffing logic

 for(i = 0; i < strlen(input); i++) {

 temp[0] = input[i];

 temp[1] = '\0';

 if(input[i] == start_delim)

 strcat(stuffed, double_start); // Stuff start delimiter again

 else if(input[i] == end_delim)

 strcat(stuffed, double_end); // Stuff end delimiter again

 else

 strcat(stuffed, temp);

 }

 // Add ending delimiter

 strcat(stuffed, double_end);

 printf("Data after character stuffing: %s\n", stuffed);

 return 0;

}



//leaky bucket
#include <stdio.h>

int main() {
    int cap, rate, n;
    int in[50], bucket = 0;

    printf("Enter bucket capacity: ");
    scanf("%d", &cap);

    printf("Enter output rate: ");
    scanf("%d", &rate);

    printf("Enter number of time intervals: ");
    scanf("%d", &n);

    printf("Enter packets at each interval:\n");
    for(int i=0; i<n; i++)
        scanf("%d", &in[i]);

    printf("\nTime\tIn\tSent\tLeft\tDropped\n");

    for(int t=0; t<n; t++) {
        int dropped = 0;

        if (bucket + in[t] > cap) {
            dropped = (bucket + in[t]) - cap;
            bucket = cap;
        } else {
            bucket += in[t];
        }

        int sent = (bucket >= rate) ? rate : bucket;
        bucket -= sent;

        printf("%d\t%d\t%d\t%d\t%d\n",
            t+1, in[t], sent, bucke
t, dropped);
    }

    return 0;
}




// sliding window 
#include <stdio.h>

#define MAX 10

int main() {
    int total, win;
    int sent[ MAX ] = {0};
    int base = 0;

    printf("Total frames: ");
    scanf("%d", &total);
    printf("Window size: ");
    scanf("%d", &win);

    while (base < total) {
        // Send window frames
        for (int i = base; i < base + win && i < total; i++)
            if (!sent[i]) printf("Sent Frame %d\n", i);

        // Receiver input
        int r;
        printf("Received frame (-1 lost): ");
        scanf("%d", &r);

        if (r >= 0 && r < total) {
            printf("Ack sent for %d\n", r);
            sent[r] = 1;
        }

        // Slide window for in-order acks
        while (base < total && sent[base])
            base++;
    }

    printf("All frames
 transmitted!\n");
    return 0;
} 



//routing 
#include <stdio.h>
#define MAX 10
#define INF 9999

int main() {
    int n, i, j, k;
    int dist[MAX][MAX], via[MAX][MAX];

    printf("Enter number of nodes: ");
    scanf("%d",&n);

    printf("Enter adjacency matrix (0 for self, INF for no link):\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            scanf("%d",&dist[i][j]);
            if(i!=j && dist[i][j]==0) dist[i][j]=INF;
            via[i][j]= (dist[i][j]==INF)? -1 : j; /* next hop */
        }
    }

    /* Distance-vector (Bellman-Ford style iterative relaxation) */
    int changed;
    do {
        changed = 0;
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                for(k=0;k<n;k++){
                    if(dist[i][k] != INF && dist[k][j] != INF &&
                       dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        via[i][j]  = via[i][k];
                        changed = 1;
                    }
                }
            }
        }
    } while(changed);

    /* Print routing tables */
    for(i=0;i<n;i++){
        printf("\nRouting table for node %d:\n", i);
        printf("Dest\tNextHop\tCost\n");
        for(j=0;j<n;j++){
            if(i==j) printf("%d\t-\t0\n", j);
            else {
                if(dist[i][j]>=INF) printf("%d\t-\tINF\n", j);
                else printf("%d\t%d\t%d\n", j, via[i][j], dist[i][j]);
            }
        }
    }
    return 0;
}

