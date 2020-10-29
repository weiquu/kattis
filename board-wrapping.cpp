#include <iostream> 
#include <stack> 
#include <stdlib.h> 
#include <cmath>
#include <iomanip>
using namespace std; 

struct Point { 
	double x, y; 
}; 

Point p0; 

Point nextToTop(stack<Point> &S) { 
	Point p = S.top(); 
	S.pop(); 
	Point res = S.top(); 
	S.push(p); 
	return res; 
} 

void swap(Point &p1, Point &p2) { 
	Point temp = p1; 
	p1 = p2; 
	p2 = temp; 
} 

double distSq(Point p1, Point p2) { 
	return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y); 
} 

int orientation(Point p, Point q, Point r) { 
	double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y); 

	if (val == 0) return 0; // colinear 
	return (val > 0)? 1: 2; // clock or counterclock wise 
} 

int compare(const void *vp1, const void *vp2) { 
    Point *p1 = (Point *)vp1; 
    Point *p2 = (Point *)vp2; 

    int o = orientation(p0, *p1, *p2); 
    if (o == 0) 
        return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1; 

    return (o == 2)? -1: 1; 
} 

double polygonArea(double X[], double Y[], int num) { 
    double area = 0.0;   
    int j = num - 1; 
    for (int i = 0; i < num; i++) { 
        area += (X[j] + X[i]) * (Y[j] - Y[i]); 
        j = i;
    }   
    return abs(area / 2.0); 
} 

double convexHull(Point points[], int n) { 
    double ymin = points[0].y;
    int min = 0;
    for (int i = 1; i < n; i++) { 
        double y = points[i].y; 
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x)) {
            ymin = points[i].y;
            min = i; 
        }
    } 

    swap(points[0], points[min]); 

    p0 = points[0]; 
    qsort(&points[1], n-1, sizeof(Point), compare); 

    int m = 1;
    for (int i=1; i<n; i++) { 
        while (i < n-1 && orientation(p0, points[i], 
                                        points[i+1]) == 0) 
            i++; 

        points[m] = points[i]; 
        m++;
    } 

    if (m < 3) return 0; 

    stack<Point> S; 
    S.push(points[0]); 
    S.push(points[1]); 
    S.push(points[2]); 

    for (int i = 3; i < m; i++) { 
        while (orientation(nextToTop(S), S.top(), points[i]) != 2) 
            S.pop(); 
        S.push(points[i]); 
    } 

    double xVals[S.size()];
    double yVals[S.size()];
    int val = 0;
    while (!S.empty()) { 
        Point p = S.top(); 
        xVals[val] = p.x;
        yVals[val] = p.y;
        S.pop(); 
        val++;
    } 
    int num = sizeof(xVals)/sizeof(xVals[0]);
    double area = polygonArea(xVals, yVals, num);
    return area;
} 

int main() { 
    int cases;
    cin >> cases;
    for (int i=0; i<cases; i++) {
        int boards;
        cin >> boards;
        Point points[boards*4];
        double totalBoards = 0;
        for (int j=0; j<boards; j++) {
            double x, y, w, h, v;
            cin >> x >> y >> w >> h >> v;
            double wx, wy, hx, hy, angle;
            angle = v*M_PI/180;
            wy = w*sin(angle)/2;
            wx = w*(-cos(angle))/2;
            hx = h*sin(angle)/2;
            hy = h*cos(angle)/2;
            points[j*4+0] = {x+wx+hx, y+wy+hy};
            points[j*4+1] = {x+wx-hx, y+wy-hy};
            points[j*4+2] = {x-wx+hx, y-wy+hy};
            points[j*4+3] = {x-wx-hx, y-wy-hy};
            totalBoards += w*h;
        }
        // for (int j=0; j<boards*4; j++) {
        //     cout << points[j].x << ", " << points[j].y << "\n";
        // }
        
        int n = sizeof(points)/sizeof(points[0]); 
        double area = convexHull(points, n);

        cout << fixed;
        cout << setprecision(1);
        cout << totalBoards*100/area << " %\n";
    }
} 
