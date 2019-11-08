Program 5
#include &lt;iostream&gt;
#include &lt;cstdlib&gt; // or &lt;stdlib.h&gt; rand, srand
#include &lt;ctime&gt; // or &lt;time.h&gt; time
#include &lt;omp.h&gt;
#include &lt;math.h&gt;
#define K 4
using namespace std;
intnum_threads;
longnum_points;
long** points; // 2D array points[x][0] -&gt; point location, points[x][1] -&gt; distance from
cluster mean
int cluster[K][2] = {
{75, 25}, {25, 25}, {25, 75}, {75, 75}
};
longcluster_count[K];
voidpopulate_points() {
// Dynamically allocate points[num_points][2] 2D array
points = new long*[num_points];
for (long i=0; i&lt;num_points; i++)
points[i] = new long[2];
// Fill random points (0 to 100)
srand(time(NULL));
for (long i=0; i&lt;num_points; i++) {
points[i][0] = rand() % 100;
points[i][1] = rand() % 100;
}
// Initialize cluster_count
for (inti=0; i&lt;K; i++) {
cluster_count[i] = 0;
}
}
doubleget_distance(int x1, int y1, int x2, int y2) {
int dx = x2-x1, dy = y2-y1;
return (double)sqrt(dx*dx + dy*dy);
}

voidclassify_points() {
#pragma omp parallel for num_threads(num_threads)
for (long i=0; i&lt;num_points; i++) {
doublemin_dist = 1000, cur_dist = 1;
intcluster_index = -1;
for (int j=0; j&lt;K; j++) {
cur_dist = get_distance(
points[i][0], points[i][1],
cluster[j][0], cluster[j][1]
);
if (cur_dist&lt;min_dist) {
min_dist = cur_dist;
cluster_index = j;
}
}
cluster_count[cluster_index]++;
}
}
int main(intargc, char* argv[]) {
num_points = atol(argv[1]);
num_threads = atoi(argv[2]);
populate_points();
double t1 = omp_get_wtime();
classify_points();
double t2 = omp_get_wtime();
double t = (t2 - t1) * 1000;
cout&lt;&lt; &quot;Time Taken: &quot; &lt;&lt; t &lt;&lt; &quot;ms&quot; &lt;&lt;endl;
}
