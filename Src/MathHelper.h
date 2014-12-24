/**
 * @file    MathHelper.h
 * @author  Amit Tomar
 * @version 1.0
 *
 * Class decleration for class MainWindow
 */

#ifndef MATHHELPER_H
#define MATHHELPER_H


/*
 * Calculates number of ways to choose r items from n distinct items
 *
 * @param  n Value to choose from
 * @param  r Number of values to choose
 */
int nCr( int n, int r )
{
    if (r > n) return 0;
    if (r * 2 > n) r = n-r;
    if (r == 0) return 1;

    int result = n;
    for( int i = 2; i <= r; ++i ) {
        result *= (n-i+1);
        result /= i;
    }
    return result;
}

#endif // MATHHELPER_H
