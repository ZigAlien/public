/******************************************************************************
 * @author Vivian Zhang
 * @date 9/19/2020
 *
 *  Compilation:  javac-algs4 Percolation.java
 *  Execution:    java-algs4 Percolation n
 *  Dependencies: WeightedQuickUnionUF.java
 *
 *  This program takes an integer n as a command-line argument and creates an
 *  n-by-n grid of sites (initially all blocked)
 *
 *  This class contains methods to
 *    - open specific sites in the grid
 *    - check if a site is open
 *    - check if a site is full/blocked
 *    - find the number of open sites
 *    - check whether the system percolates
 *
 ******************************************************************************/

import edu.princeton.cs.algs4.WeightedQuickUnionUF;

public class Percolation {
    private final int size;
    private final boolean[][] grid;
    private final WeightedQuickUnionUF uf;
    private int opencount = 0;

    // creates n-by-n grid, with all sites initially blocked
    public Percolation(int n) {
        if (n <= 0) {
            throw new IllegalArgumentException("n too small");
        }
        grid = new boolean[n][n];
        uf = new WeightedQuickUnionUF(n * n);
        size = n;
    }

    // opens the site (row, col) if it is not open already
    public void open(int row, int col) {
        exception(row, col);
        if (!isOpen(row, col)) {
            grid[row - 1][col - 1] = true;
            opencount++;
            connect(row, col);
        }
    }

    // is the site (row, col) open?
    public boolean isOpen(int row, int col) {
        exception(row, col);
        return grid[row - 1][col - 1];
    }

    // is the site (row, col) full?
    public boolean isFull(int row, int col) {
        if (isOpen(row, col)) {
            for (int x = 1; x <= size; x++) {
                if (isOpen(1, x)) {
                    if (uf.find(reindex(1, x)) == uf.find(reindex(row, col))) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    // returns the number of open sites
    public int numberOfOpenSites() {
        return opencount;
    }

    // does the system percolate?
    public boolean percolates() {
        for (int i = 1; i <= size; i++) {
            if (isFull(size, i)) {
                return true;
            }
        }
        return false;
    }

    // connects two squares in the WeightedUnionQuickUF data structure
    private void connect(int row, int col) {
            rightconnect(row, col);
            leftconnect(row, col);
            upconnect(row, col);
            downconnect(row, col);
    }

    // check if square to the right -> is open
    private void rightconnect(int row, int col) {
        if (validate(row, col + 1) != 0) {
            return;
        }
        if (isOpen(row, col + 1)) {
            uf.union(reindex(row, col), reindex(row, col + 1));
        }
    }

    // check if square to the left <- is open
    private void leftconnect(int row, int col) {
        if (validate(row, col - 1) != 0) {
            return;
        }
        if (isOpen(row, col - 1)) {
            uf.union(reindex(row, col), reindex(row, col - 1));
        }
    }

    // check if square above ^ is open
    private void upconnect(int row, int col) {
        if (validate(row - 1, col) != 0) {
            return;
        }
        if (isOpen(row - 1, col)) {
            uf.union(reindex(row, col), reindex(row - 1, col));
        }
    }

    // check if square below v is openß
    private void downconnect(int row, int col) {
        if (validate(row + 1, col) != 0) {
            return;
        }
        if (isOpen(row + 1, col)) {
            uf.union(reindex(row, col), reindex(row + 1, col));
        }
    }

    // helper method, returns the number identifier of the site if each site was numbered with an integer
    private int reindex(int row, int col) {
        return (size * (row - 1)) + (col - 1);
    }

    // helper method, hvalidates row and column indices
    private int validate(int row, int col) {
        if (row > size || row <= 0) {
            return 1;
        }
        if (col > size || col <= 0) {
            return 2;
        }
        return 0;
    }

    private void exception(int row, int col) {
        if (validate(row, col) == 1) {
            throw new IllegalArgumentException("row index out of range");
        }
        if (validate(row, col) == 2) {
            throw new IllegalArgumentException("column index out of range");
        }
    }
}
