/******************************************************************************
 * @author Vivian Zhang
 * @date 9/20/2020
 *
 *  Compilation:  javac-algs4 PercolationStats.java
 *  Execution:    java-algs4 PercolationStats n t
 *  Dependencies: Percolation.java
 *
 *  This program takes two integers a command-line argument.
 *  - The first integer n represents the dimension of the percolation grid.
 *  - The second integer t represents the number of trials to run.
 *
 * The program creates an n-by-n grid of sites (initially all
 * blocked) and opens random sites until the system percolates. After it
 * percolates, the proportion of open sites to total sites in the grid is
 * recorded. This is repeated for t trials.
 *
 * After all trials are complete, the program prints the resulting mean,
 * standard deviation, and 95% confidence interval of the proportion of open
 * sites needed to make the system percolate in all its trials.
 *
 ******************************************************************************/

import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdStats;
// import edu.princeton.cs.algs4.Stopwatch;

public class PercolationStats {
    private static final double CONFIDENCE_95 = 1.96;
    private final double[] threshold;
    private final int t;

    // perform independent trials on an n-by-n grid
    public PercolationStats(int n, int trials) {
        if (n <= 0) {
            throw new IllegalArgumentException("n must be greater than 0");
        }
        if (trials <= 0) {
            throw new IllegalArgumentException("trials must be greater than 0");
        }
        threshold = new double[trials];
        t = trials;
        for (int i = 0; i < trials; i++) {
            Percolation perc = new Percolation(n);
            while (!perc.percolates()) {
                int row = StdRandom.uniform(1, n + 1);
                int col = StdRandom.uniform(1, n + 1);
                perc.open(StdRandom.uniform(1, n + 1), StdRandom.uniform(1, n + 1));
                // wondering if there's a way to check if the site was already open before
                // to avoid calling percolates so many times
                // maybe just call percolates after at least n sites have been opened?
                /* if (perc.percolates()) {
                    break;
                } */
            }
            double sites = n * n;
            threshold[i] = perc.numberOfOpenSites() / (sites);
        }
    }

    // sample mean of percolation threshold
    public double mean() {
        return StdStats.mean(threshold);
    }

    // sample standard deviation of percolation threshold
    public double stddev() {
        return StdStats.stddev(threshold);
    }

    // low endpoint of 95% confidence interval
    public double confidenceLo() {
        return mean() - (CONFIDENCE_95 * stddev()) / Math.sqrt(t);
    }

    // high endpoint of 95% confidence interval
    public double confidenceHi() {
        return mean() + (CONFIDENCE_95 * stddev()) / Math.sqrt(t);
    }

    // test client (see below)
    public static void main(String[] args) {
        // Stopwatch time = new Stopwatch();
        int n = Integer.parseInt(args[0]);
        int trials = Integer.parseInt(args[1]);
        PercolationStats percolationStats = new PercolationStats(n, trials);
        StdOut.println("mean = " + percolationStats.mean());
        StdOut.println("stddev = " + percolationStats.stddev());
        StdOut.println("95% confidence interval = [" + percolationStats.confidenceLo() + ", " + percolationStats.confidenceHi() + ']');
        // StdOut.println("running time: " + time.elapsedTime());
    }
}
