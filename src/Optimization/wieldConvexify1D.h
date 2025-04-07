#ifndef WIELD_OPTIMIZATION_CONVEXIFY1D_H
#define WIELD_OPTIMIZATION_CONVEXIFY1D_H
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "Reader/Reader.h"
#include "Utils/wieldEigen.h"
#include "Utils/wieldExceptions.h"
#include "Utils/wieldProgress.h"
#include "Utils/wieldRotations.h"
#include "Utils/wieldTypes.h"

namespace Wield
{
namespace Optimization
{
std::vector<double>
Convexify1D(std::vector<double> X, std::vector<double> Y)
{
    WIELD_EXCEPTION_TRY;
    if (X.size() != Y.size())
        WIELD_EXCEPTION_NEW("X and Y not the same size");

    std::vector<double> Yc;
    for (int i = 0; i < X.size(); i++)
    {
        double inf = Y[i];
        for (int j = 0; j < i; j++)
            for (int k = i + 1; k < X.size(); k++)
            {
                double lambda = (X[i] - X[j]) / (X[k] - X[j]);
                double w = (1 - lambda) * Y[j] + lambda * Y[k];
                if (w < inf)
                    inf = w;
            }
        Yc.push_back(inf);
    }
    return Yc;
    WIELD_EXCEPTION_CATCH;
}

std::vector<double>
Convexify1DAngles(std::vector<double> X, std::vector<double> Y, std::vector<double> &wulff, bool full = false)
{
    WIELD_EXCEPTION_TRY;
    if (X.size() != Y.size())
        WIELD_EXCEPTION_NEW("X and Y not the same size");

    std::vector<double> Yc;
    for (int i = 0; i < X.size(); i++) // With the simpler for loops, this has O(n^2) scaling
    {
        double inf = Y[i];
        double wulff_inf = inf;
        int jmin, jmax, kmin, kmax;

        // These for loop parameters gives an accurate
        // relaxation for *all* theta
        if (full)
        {
            jmin = 0;
            jmax = X.size();
            kmin = 0;
            kmax = X.size();
        }
        // But this one has O(n) scaling instead of O(n^2)
        else
        {
            jmin = 0;
            jmax = i;
            kmin = i + 1;
            kmax = X.size();
        }

        for (int j = jmin; j < jmax; j++)
            for (int k = kmin; k < kmax; k++)
            {
                if (j == k)
                    continue;
                double theta1 = X[j] * pi / 180, theta = X[i] * pi / 180, theta2 = X[k] * pi / 180;
                while (theta1 > theta)
                    theta1 -= pi;
                while (theta2 < theta)
                    theta2 += pi;
                double det = sin(theta1 - theta2);
                double lambda1 = sin(theta - theta2) / det;
                double lambda2 = sin(theta1 - theta) / det;
                double w = fabs(lambda1) * Y[j] + fabs(lambda2) * Y[k];
                double wulff1 = fabs(Y[j] / cos(theta - theta1)), wulff2 = fabs(Y[k] / cos(theta - theta2));
                double wulff_tmp;
                if (wulff1 < wulff2)
                    wulff_tmp = wulff1;
                else
                    wulff_tmp = wulff2;

                if (w < inf)
                    inf = w;
                if (wulff_tmp < wulff_inf)
                    wulff_inf = wulff_tmp;
            }
        Yc.push_back(inf);
        wulff.push_back(wulff_inf);
        WIELD_PROGRESS("Convexifying", i, X.size(), 1);
    }
    std::cout << std::endl;
    return Yc;
    WIELD_EXCEPTION_CATCH;
}
}
}

#endif
