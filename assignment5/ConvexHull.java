import java.util.*;

public class ConvexHull {

    public static void main(String[] args) {
        test();
        if(args.length == 3){
            int n = Integer.parseInt(args[0]);
            int s = Integer.parseInt(args[1]);
            int r = Integer.parseInt(args[2]);
            analysis(n, s, r);
        }else{
            analysis(20, 50000, 20);
        }

    }

    public static ArrayList<Point> GrahamScan(Point[] P){
        Point[] Q = P.clone();

        Point p0 = Q[0];
        int min = 0;
        for (int i = 1; i < Q.length; i++) {
            double y = Q[i].y;
            if(y<p0.y || (y == p0.y && Q[i].x<p0.x) ){
                p0 = Q[i];
                min = i;
            }
        }

        Point temp = Q[0];
        Q[0] = Q[min];
        Q[min] = temp;

        Arrays.sort(Q, 1, Q.length, new PointComparator(p0));

        int new_size = 1;
        for (int i=1; i<Q.length; i++) {
            while (i < Q.length-1 && Point.orientation(p0, Q[i], Q[i+1]) == 0)
                i++;

            Q[new_size] = Q[i];
            new_size++;
        }

        if(new_size<3)return null;
        ArrayList<Point>S = new ArrayList<>();
        S.add(Q[0]);
        S.add(Q[1]);
        S.add(Q[2]);

        for (int i = 3; i < new_size; i++)
        {
            while ( Point.orientation(S.get(S.size()-2), S.get(S.size()-1), Q[i]) != 2)
                S.remove(S.size()-1);
            S.add(Q[i]);
        }

        return S;
    }

    public static ArrayList<Point> JarvisMarch(Point[] Q){
        if (Q.length < 3) return null;

        ArrayList<Point> hull = new ArrayList<>();

        int l = 0;
        for (int i = 1; i < Q.length; i++)
            if (Q[i].x < Q[l].x)
                l = i;

        int p = l, q;
        do
        {
            hull.add(Q[p]);

            q = (p + 1) % Q.length;

            for (int i = 0; i < Q.length; i++)
            {
                if (Point.orientation(Q[p], Q[i], Q[q]) == 2)
                    q = i;
            }

            p = q;

        } while (p != l);

        return hull;
    }

    public static void test(){
        boolean res = true;
        for(int i=0; i<1000; i++) {
            Point[] points = Point.genRandomPoints(1000);
            ArrayList<Point> hull = GrahamScan(points);
            ArrayList<Point> hull1 = JarvisMarch(points);
            if(!hull.containsAll(hull1)){
                res = false;
                break;
            }
        }
        if(!res) System.out.println("Correctness Test: Fail");
    }

    public static void analysis(int n_data, int step_size, int reruns){
        int n = 0;
        double time1,time2,time3;
        long start, end;
        for(int i=0; i<n_data; i++){
            n += step_size;
            time1 = 0; time2 =0 ; time3 = 0;

            for(int r=0;r<reruns;r++){
                Point[] points = Point.genRandomPoints(n);

                start = System.nanoTime();
                ArrayList<Point> hull2 = JarvisMarch(points);
                end = System.nanoTime();
                time2 += end - start;

                start = System.nanoTime();
                ArrayList<Point> hull = GrahamScan(points);
                end = System.nanoTime();
                time1 += end - start;
                
                if(hull2.size()>n/2)System.out.println("hull big");

                time3 += (double)(end - start)/hull2.size();
            }
            time1 = time1/(reruns*1000000);
            time2 = time2/(reruns*1000000);
            time3 = time3/(reruns*1000000);
            System.out.format("%d, %f, %f, %f\n", n, time1, time2, time3);
        }

    }
}

class PointComparator implements Comparator<Point> {

    Point p0;
    PointComparator(Point p){
        p0 = p;
    }

    @Override
    public int compare(Point p1, Point p2) {

        // Find orientation
        int orientation = Point.orientation(p0, p1, p2);
        if (orientation == 0){
            return Double.compare(p0.euclidean(p1), p0.euclidean(p2));
        }else if(orientation == 1){
            return 1;
        }else {
            return -1;
        }

    }
}

class Point{
    double x, y;
    public Point(double x, double y){
        this.x = x;
        this.y = y;
    }

    @Override
    public boolean equals(Object obj) {
        Point p = (Point) obj;
        return x == p.x && y == p.y;
    }

    public double euclidean(Point p) {
        return Math.sqrt( Math.pow(x-p.x,2) + Math.pow(y-p.y,2) );
    }

    public String toString(){
        return String.format("(%f, %f)", x, y);
    }

    public static Point[] genRandomPoints(int n){
        Random rand = new Random();
        Point[] points = new Point[n];
        double x, y;

        for(int i=0;i<n;i++){
            x = (rand.nextDouble() - rand.nextDouble())*10000;
            y = (rand.nextDouble() - rand.nextDouble())*10000;
            points[i] = new Point(x, y);
        }

        return points;
    }

    public static int orientation(Point p, Point q, Point r) {
        double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

        if (val == 0) return 0;  // colinear
        return (val > 0)? 1: 2; // clock or counterclock wise
    }
}
